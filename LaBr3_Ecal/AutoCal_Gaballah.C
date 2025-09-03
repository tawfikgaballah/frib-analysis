// Author: Sean Liddick, 2016-09-14
//
// Start point for automatic calibration routine for a set of spectra.

Double_t fBgd(Double_t *x, Double_t *par){
  Double_t xx = x[0];  //this is the value of the independent var
  Double_t f = par[0]*xx+par[1];
  return f;
}


Double_t fPeak(Double_t *x, Double_t *par){
  Double_t xx = x[0];  //this is the value of the independent var
  Double_t f = par[0]*TMath::Exp(-0.5*((xx-par[1])/par[2])*((xx-par[1])/par[2]));
  return f;
}

Double_t fSumTwoPeak(Double_t *x, Double_t *par){

  Double_t f = fPeak(x,&par[0]) + fPeak(x,&par[3]);
  return f;
}


Double_t fSumPeakBgd(Double_t *x, Double_t *par){

  Double_t f = fPeak(x,&par[0]) + fBgd(x,&par[3]);
  return f;
}

double FittingDemoGausLin(TH1D* hist, int lo, int hi,double cent,double amp, int color){
  
  TF1* f1=new TF1(Form("FittingDemoGausLin_%d",color/2), fSumPeakBgd, lo, hi,5);
 

  TF1* Fpeak= new TF1(Form("Fpeak_%d",color/2), fPeak, lo, hi, 3);
  Fpeak->SetParameters(amp,cent,5);
  TF1* Fbgd=new TF1(Form("Fbgd_%d",color/2), fBgd, lo,hi, 2);
  Fbgd->SetLineColor(1);
  hist->Fit(Form("Fbgd_%d",color/2),"QRN");
  const Double_t* Fbgd_par=Fbgd->GetParameters();
  const Double_t* Fbgd_pare = Fbgd->GetParErrors();
  hist->Fit(Form("Fpeak_%d", color/2),"QRN");
  const Double_t* Fpeak_par=Fpeak->GetParameters();
  const Double_t* Fpeak_pare = Fpeak->GetParErrors();

  f1->SetParameters(Fpeak_par[0]+Fbgd->Eval(Fpeak_par[1]), Fpeak_par[1], Fpeak_par[2], Fbgd_par[0], Fbgd_par[1]);
  f1->SetParNames("height","mean","sigma","slope","intercept");
  f1->SetLineColor(color+2);
  hist->Fit(Form("FittingDemoGausLin_%d", color/2),"QRN");

  f1->Draw("same");
  gPad->SetLogy();
  gPad->Update();
  return f1->GetParameter(1);
  delete f1;
  delete Fpeak;
  delete Fbgd;
  delete hist; 
    
}








void FindPeaks(TH1D* hist, int id, double lo, double hi, double res, double amp, Int_t Peak, Int_t MaxPeak, TCanvas* Graphs, Double_t p0[16], Double_t p1[16], Double_t p2[16], Double_t p3[16]){

  hist->GetXaxis()->SetRangeUser(lo, hi);
  
  TSpectrum* s= new TSpectrum(MaxPeak);
  Int_t nfound = s->Search(hist,res,"",amp);
  Double_t *xpeaks = s->GetPositionX();
  Double_t *ypeaks = s->GetPositionY();
  // if(id==4 || id==11)
    std::cout<< "number of peaks"<< nfound<<'\n';

  for(int i=0; i<sizeof(xpeaks); i++){
    // if(id==4 || id==11)
      std::cout<<Form("X_Coordinate_for_peak_%d: ",i)<<xpeaks[i]<<", "<<Form("Y_Coordinate_for_peak_%d: ",i)<<ypeaks[i]<<'\n';
  }
  Double_t *maxXPeak = std::max_element(xpeaks, xpeaks + nfound);
  Double_t *maxYPeak = std::max_element(ypeaks, ypeaks + nfound);


  //initial two point calibration 
  double raw_E[2]={xpeaks[maxYPeak-ypeaks], xpeaks[maxXPeak-xpeaks]};
  double raw_Amp[2]={ypeaks[maxYPeak-ypeaks], ypeaks[maxXPeak-xpeaks]};
  double cal_E[2]={35.5, 617};
  double slope = (cal_E[1] - cal_E[0]) / (raw_E[1] - raw_E[0]);
  double offset = cal_E[0] - slope * raw_E[0];
  // if(id==4 || id==11){
    std::cout<<" 511 is at: "<<(-offset+511)/slope<<'\n';
    std::cout<<" 372 is at: "<<(-offset+372)/slope<<'\n';
  // }

  double other_Xpeaks[2];
  double other_Ypeaks[2];
  int counter=0; 
  for(double value:{372,511}){
    double target = (-offset + value) / slope;

    // Define the 0.5% range
    double lowerBound = target * (1 - 0.05);
    double upperBound = target * (1 + 0.05);
    // if(id==4 || id==11){
      std::cout << "Target value: " << target << std::endl;
      std::cout << "Search range: [" << lowerBound << ", " << upperBound << "]" << std::endl;
    // }
    // Search for values in xpeaks within the 0.5% range
    bool found = false;
    for (int i = 0; i < nfound; i++) {
      if (xpeaks[i] >= lowerBound && xpeaks[i] <= upperBound) {
	// if(id==4 || id==11)
	  std::cout << "Found value in range: " << xpeaks[i] << " at index " << i << std::endl;
	found = true;
	other_Xpeaks[counter]=xpeaks[i];
	other_Ypeaks[counter]=ypeaks[i];
      }
    }

    if (!found) {
      if(id==4 || id==11)
        std::cout << "No values found in the range." << std::endl;
    }
    counter++;
  }




  //Final values for calibration points 
   
  double raw_E_Centroid[4]={raw_E[0], other_Xpeaks[0],other_Xpeaks[1], raw_E[1]};
 
  double raw_E_Amplitude[4]={raw_Amp[0], other_Ypeaks[0],other_Ypeaks[1], raw_Amp[1]};

  double raw_E_Fit_Centroids[4];
  hist->Draw("");


  //Fitting the four peaks after obtaining the initial values and then getting the centroids from the fits.
  for(int i=0; i<4; i++){
    // raw_E_Fit_Centroids[i]=FittingDemoGausLin(hist,raw_E_Centroid[i]-60,raw_E_Centroid[i]+60,raw_E_Centroid[i],raw_E_Amplitude[i],i*2);


	TF1 *gauss111 = new TF1(Form("gauss111%d", i), "gaus(0)+pol1(3)", raw_E_Centroid[i] - 40, raw_E_Centroid[i] + 40);
  	gauss111->FixParameter(0,hist->GetBinContent(hist->GetXaxis()->FindBin(raw_E_Centroid[i]))-60);
  	gauss111->FixParameter(2,25);
  	gauss111->FixParameter(1, raw_E_Centroid[i]);
  	hist->Fit(gauss111, "MLEISRNQ0+");
      
  	TF1 *gauss11 = new TF1(Form("gauss11%d", i), "gaus(0)+pol1(3)", raw_E_Centroid[i] - 40, raw_E_Centroid[i] + 40);
  	gauss11->SetParameters(gauss111->GetParameters());
  	gauss11->FixParameter(1,raw_E_Centroid[i]);
	gauss11->FixParameter(2,25);
	//	gauss11->FixParameter(0,hist->GetBinContent(hist->GetXaxis()->FindBin(raw_E_Centroid[i]))-600);
  	hist->Fit(gauss11, "MLISRNQE+");

  	TF1 *gauss12 = new TF1(Form("gauss12%d", i), "gaus(0)+pol1(3)", raw_E_Centroid[i] - 40, raw_E_Centroid[i] + 40);
  	gauss12->SetParameters(gauss11->GetParameters());
        gauss12->FixParameter(1,raw_E_Centroid[i]);
  	hist->Fit(gauss12, "MLISRNQE+");
  	TF1 *gauss13 = new TF1(Form("gauss13%d", i), "gaus(0)+pol1(3)", raw_E_Centroid[i] - 40, raw_E_Centroid[i] + 40);
  	gauss13->SetParameters(gauss12->GetParameters());
  	hist->Fit(gauss13, "MLISRNQE");
	raw_E_Fit_Centroids[i]=gauss13->GetParameter(1);
	gauss13->SetLineColor(i*2+2);
	gauss13->Draw("same");
	gPad->SetLogy();
	gPad->Update();
	// canvas->Update();
	delete gauss111;
	delete gauss11;
	delete gauss12;
	// delete gauss13;

  }
  //Plot the centroids against the real values in keV
  double cal_E_Centroids[4]={35.5, 372, 511, 617};
  Graphs->cd(id+1);
  TGraph* graph=new TGraph(4, raw_E_Fit_Centroids, cal_E_Centroids);
  graph->SetName(Form("Four Point Calibration hsegaE_%d",id));
  graph->SetTitle(Form("Four Point Calibration hsegaE_%d",id));
  graph->GetXaxis()->SetTitle("Raw Energy Values [ADC Units]");
  graph->GetYaxis()->SetTitle("Reference Values [keV]");
  graph->SetMarkerSize();
  graph->SetMarkerStyle(20);
  graph->Fit("pol1","Q");
  TF1* polfit = graph->GetFunction("pol1");
   p0[id] = polfit->GetParameter(0);
   p1[id] = polfit->GetParameter(1);
   // p2[id] = polfit->GetParameter(2);
   // p3[id] = polfit->GetParameter(3);
  graph->Draw("AP");
  gPad->Update();
  delete polfit;
  // delete graph;
  delete s;
}
bool check_outside_range(const std::array<double, 52>& arr) {
  for (int i = 0; i < 52; ++i) {
    if (arr[i] >= 1432 && arr[i] <= 1440) {
      return false; // Return false if any element is within the range
    }
  }
  return true; // Return true if all elements are outside the range
}



void AutoCal_Gaballah(string filein="calibration_test_full_decay.root"){









  
  const Int_t nDetLabr = 16;
  Double_t p0[nDetLabr], p1[nDetLabr], p2[nDetLabr], p3[nDetLabr];

  // we know we are looking for 16 Labr detectors
  TH1D *hlabr[nDetLabr];
  TH1D *hlabr_[nDetLabr];
  TH1D* hlabr_calibrated[nDetLabr]; // Calibrated histograms
 
  
  //open a file
  TFile *f = new TFile(filein.c_str());
  TFile* fout=new TFile("calibration_check.root","recreate");
  for(int i = 0; i < 16; i++){
    hlabr[i] = (TH1D*)f->Get(Form("/raw/hlabr_cross_amplitude_test_%d",i));
    hlabr_calibrated[i]=new TH1D(Form("/cal/hlabr_cross_amplitude_test_calibrated_%d",i),Form("/cal/hlabr_cross_amplitude_test_calibrated_%d",i), 3000, 0, 3000);
      hlabr_[i]=new TH1D(Form("/raw/hlabr_cross_amplitude_test_%d",i),Form("/raw/hlabr_cross_amplitude_test_%d",i), 3000, 0, 3000);
  }
  TH1D* hlabr_full_calibrated=new TH1D("hlabr_cross_amplitude_test_calibrated_full", "hlabr_cross_amplitude_test_calibrated_full", 3000,0,3000);
  TH1D* hlabr_full=new TH1D("hlabr_cross_amplitude_test_full", "hlabr_cross_amplitude_test_full", 3000,0,3000);
  // hlabr[2]->Draw("");
  TCanvas* Fits=new TCanvas("Fit Inspection", "Fit Inspection",600,800);
  Fits->Divide(4,4);

  TCanvas* Graphs=new TCanvas("Four Point Calibration", "Four Point Calibration",600,800);
  Graphs->Divide(4,4);
  for(int i=0; i<nDetLabr; i++){
    Fits->cd(i+1);

    //For Det#(0,5), 1332 is higher than 1173, had to rebin by a factor of two 
    // if(i==0 ||i==5)
    hlabr[i]->RebinX(2);
    if(i!=13){
      FindPeaks(hlabr[i],i,10, 680,1, .0000005, .5, 15, Graphs, p0, p1, p2, p3);
      // for (int bin = 1; bin <= hlabr[i]->GetNbinsX(); bin++) {
      //           // Get raw ADC value (bin center)
      //           Double_t raw_adc = hlabr[i]->GetXaxis()->GetBinCenter(bin);

      //           // Apply pol3 calibration
      //           Double_t calibrated_energy = p0[i] + p1[i] * raw_adc // + p2[i] * raw_adc * raw_adc + p3[i] * raw_adc * raw_adc * raw_adc
      // 		  ;
      // 		std::cout<<calibrated_energy<<'\n';
      //           // Fill the calibrated histogram with recalibrated energy and the same bin content
      //           hlabr_calibrated[i]->Fill(calibrated_energy, hlabr[i]->GetBinContent(bin));
      //       }
    }
      
    Fits->Update();
    Graphs->Update();
  }
  fout->cd();
 
  TH2D* Detector_Vs_E=new TH2D("Detector_Vs_E","Detector_Vs_E",3000,0,3000,16,0,16);
  TH2D* Detector_Vs_E_Cal=new TH2D("Detector_Vs_E_Cal","Detector_Vs_E_Cal",3000,0,3000,16,0,16);
  
  TChain* data=new TChain("trimmed_data");
  data->Add("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/run-*");

  double labr_ecal[16];
  int corr_isdecay;
  double labr_time[16];
  int labr_cfd[16];
  data->SetBranchAddress("labr_ecal[16]", labr_ecal);
  data->SetBranchAddress("corr_isdecay", &corr_isdecay);
  long int nEntries= data->GetEntries();
  int count=0;
  int progressInterval = nEntries / 100; 
  for(int i=0; i<nEntries; i++){
    data->GetEntry(i);
    for (int j = 0; j < 16; ++j) {
      //labr detectors
      double Ej=labr_ecal[j];
     
      if(Ej > 10){
        hlabr_[j]->Fill(Ej);

	hlabr_full->Fill(Ej);
	Detector_Vs_E->Fill(Ej,j);
	
      }

      double Ecal=p0[j]+labr_ecal[j]*p1[j];
     
      if(Ecal > 10){
	hlabr_calibrated[j]->Fill(Ecal);

	hlabr_full_calibrated->Fill(Ecal);
	Detector_Vs_E_Cal->Fill(Ecal,j);
	
      }
      
    }
    count++;
    int oneper = (int)(nEntries * 0.01);
    int fiveper = (int)(nEntries * 0.05);
    if( (count % oneper) == 0) {
      cout << "Events processed " << count << " - percent done " << (int)(count/oneper)*1 << "%"<<endl;
      // if (count/oneper==1)
      // 	break;
    }
  }
  count=0;

  fout->mkdir("raw");
  fout->mkdir("cal");

  for (int j = 0; j < 16; ++j) {
    //labr detectors
    fout->cd("raw");
    hlabr_[j]->Write();
    fout->cd("cal");
    hlabr_calibrated[j]->Write();
  }
  fout->cd("cal");
  hlabr_full_calibrated->Write();
  Detector_Vs_E_Cal->Write();
  fout->cd("raw");
  hlabr_full->Write();
  Detector_Vs_E->Write();


}







