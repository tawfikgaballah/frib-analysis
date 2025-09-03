#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TSpectrum.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TTree.h"
#include "TBranch.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TMarker.h"
#include "TGraphErrors.h"
#include <algorithm>
const int nPeaks=3;
const int nCrystals=16; //number of labr3 
const int nRuns=1;
void auto_fitter(TFile* output, string path, Double_t xPeaks_3D[nRuns][16][3],Double_t xPeaks_3D_error[nRuns][16][3],int run){
  Double_t calibration_parameters[16][5]; 
  TCanvas *canvas = new TCanvas("canvas", "Fit Histogram with Gaussians_Doublet", 800, 600);
  canvas->Divide(4,4);

  TCanvas *canvas2 = new TCanvas("canvas2", "Fit Histogram with Gaussians_511", 800, 600);
  canvas2->Divide(4,4);
  TCanvas *canvas3 = new TCanvas("canvas3", "Fit Histogram with Gaussians_35.5", 800, 600);
  canvas3->Divide(4,4);
  TCanvas *canvas1 = new TCanvas("canvas1", "Calibration_Fit", 800, 600);
  canvas1->Divide(4,4);

  double x[4];
  double xe[4];
  TFile* histin=new TFile("calibration_test_full_decay.root","read");

  TH1D *hlabr_cross_amplitude[16];
  TH1D* hlabr_cross_amplitude_calibrated[16];
  TH1D *hlabr_cross_amplitude_full =new TH1D("/raw/hlabr_cross_amplitude_test_full","hlabr_cross_amplitude_test_full",3000,0,3000);
  TH1D *hlabr_cross_amplitude_full_calibrated=new TH1D("/cal/hlabr_cross_amplitude_test_full_calibrated","hlabr_cross_amplitude_test_full_calibrated",3000,0,3000);
  for(int i = 0; i < 16; i++){
    hlabr_cross_amplitude[i] = (TH1D*)histin->Get(Form("/raw/hlabr_cross_amplitude_test_%d",i));
    hlabr_cross_amplitude_calibrated[i] = (TH1D*)histin->Get(Form("/cal/hlabr_cross_amplitude_test_calibrated_%d",i));
  }


 
  TH2D* Detector_Vs_E=(TH2D*)histin->Get("/raw/Detector_Vs_E");
  TH2D* Detector_Vs_E_Cal=(TH2D*)histin->Get("/cal/Detector_Vs_E_Cal");
  



  
  for(int crystal=0; crystal<nCrystals;crystal++){
    canvas->cd(crystal+1);
 
   
    hlabr_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(1100,1700);
    hlabr_cross_amplitude[crystal]->Draw();
    // Use TSpectrum to find peaks
   
  
    TSpectrum *s = new TSpectrum(8); // Adjust the number according to your expected number of peaks
    Int_t nFound = s->Search(hlabr_cross_amplitude[crystal], 1, "nobackground", 0.05); // Adjust parameters as needed

    Double_t *xPositions = s->GetPositionX();
    std::vector<std::pair<Double_t, Double_t>> peaks; // Pair of position and height

    // Retrieve positions and heights
    for (int i = 0; i < nFound; ++i) {
      Double_t height = hlabr_cross_amplitude[crystal]->GetBinContent(hlabr_cross_amplitude[crystal]->GetXaxis()->FindBin(xPositions[i]));
      peaks.push_back(std::make_pair(xPositions[i], height));
    }
    delete s;


    // if (!peaks.empty()) {
    //     highestPeak = peaks.front();
    //     // The rest of your logic here
    // } else {
    //     std::cout << "No peaks found in crystal " << crystal << std::endl;
    std::pair<Double_t, Double_t> xPeaks;
    // }
    if (!peaks.empty()) {
      std::sort(peaks.begin(), peaks.end(), [](const std::pair<Double_t, Double_t> &a, const std::pair<Double_t, Double_t> &b) {
					      return a.second > b.second; // Assuming you want to sort by the second element in the pair
					    });
 
      auto highestPeak = peaks.front();
      auto it = std::find_if(peaks.begin(), peaks.end(), [&](const std::pair<Double_t, Double_t> &peak)  {
							   // if(highestPeak.second>=1.2*peak.second &&highestPeak.second<1.5*peak.second){
							   return (highestPeak.first - peak.first) >= 10 && (highestPeak.first - peak.first)<=20 && (highestPeak.second<=3*peak.second)&&(highestPeak.second-peak.second)>=25;
							   //   else{
							   // 	return highestPeak.first-peak.first>=10;
							   //   }
							 });

   


      // Now draw the histogram and markers
      // TCanvas *c1 = new TCanvas("c1", "Peaks", 80, 60);
      hlabr_cross_amplitude[crystal]->Draw("");

    
      if (it != peaks.end()) {
	// Highest peak marker
	TMarker *marker1 = new TMarker(highestPeak.first, highestPeak.second, 20);
	marker1->SetMarkerColor(kGreen);
	marker1->Draw();

	// First peak to the left marker
	TMarker *marker2 = new TMarker(it->first, it->second, 20);
	marker2->SetMarkerColor(kBlue);
	marker2->Draw();

	std::cout << "Highest peak: Position = " << highestPeak.first << ", Height = " << highestPeak.second << std::endl;
	std::cout << "First peak to the left at least 15 units away: Position = " << it->first << ", Height = " << it->second << std::endl;
	
	xPeaks={highestPeak.first,it->first};
      } else {
	
	auto highestPeak = peaks.front();
	auto it = std::find_if(peaks.begin(), peaks.end(), [&](const std::pair<Double_t, Double_t> &peak)  {
							     // if(highestPeak.second>=1.2*peak.second &&highestPeak.second<1.5*peak.second){
							     return (highestPeak.first - peak.first) >= 10 &&(highestPeak.first - peak.first)<=40 &&(highestPeak.second<=3*peak.second)&&(highestPeak.second-peak.second)>=50;
							     // Highest peak marker
							   });
	TMarker *marker1 = new TMarker(highestPeak.first, highestPeak.second, 20);
	marker1->SetMarkerColor(kGreen);
	marker1->Draw();

	// First peak to the left marker
	TMarker *marker2 = new TMarker(it->first, it->second, 20);
	marker2->SetMarkerColor(kBlue);
	marker2->Draw();

	std::cout << "Highest peak: Position = " << highestPeak.first << ", Height = " << highestPeak.second << std::endl;
	std::cout << "First peak to the left at least 15 units away: Position = " << it->first << ", Height = " << it->second << std::endl;
	xPeaks={highestPeak.first,it->first};
	//   else{
	// 	return highestPeak.first-peak.first>=10;
	//   }
	std::cout << "No peak found at least 15 units to the left of the highest peak." << std::endl;
      
      }

      // Cleanup
  
      // Note: c1 and the markers should not be deleted here if you want them to stay visible.
      // ROOT takes ownership of the markers because they are drawn on the canvas.
      auto originalHistogram = (TH1*)hlabr_cross_amplitude[crystal]->Clone("originalHistogram");
      hlabr_cross_amplitude[crystal]->Rebin(4);
      hlabr_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(1100,1700);
      //  if (!xPeaks.second)
      //      xPeaks.second=xPeaks.first-150;
      double par[6]={hlabr_cross_amplitude[crystal]->GetBinContent(hlabr_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks.first)),xPeaks.first,13,hlabr_cross_amplitude[crystal]->GetBinContent(hlabr_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks.second)),xPeaks.second,16};
      
      TF1 *gauss = new TF1(Form("gauss%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 240, xPeaks.first + 160);

      gauss->FixParameter(0,par[0]);
      gauss->FixParameter(1, par[1]);
      gauss->FixParameter(2,par[2]);
      gauss->FixParameter(3,par[3]);
      gauss->FixParameter(4, par[4]);
      gauss->FixParameter(5,par[5]);
     
      hlabr_cross_amplitude[crystal]->Fit(gauss, "MLESRNQ0+");
      
      TF1 *gauss1 = new TF1(Form("gauss1%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 240, xPeaks.first + 160);
      gauss1->SetParameters(gauss->GetParameters());
      
      gauss1->FixParameter(0,par[0]);
      gauss1->FixParameter(1, par[1]);
      gauss1->FixParameter(2,par[2]);
      gauss1->FixParameter(4, par[4]);
      gauss1->FixParameter(5,par[5]);
      hlabr_cross_amplitude[crystal]->Fit(gauss1, "MLESRNQ+");

      TF1 *gauss2 = new TF1(Form("gauss2%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 240, xPeaks.first + 160);
      gauss2->SetParameters(gauss1->GetParameters());
   
     
      gauss2->FixParameter(1, par[1]);
      gauss2->FixParameter(4, par[4]);
     
      gauss2->FixParameter(5,par[5]);
      gauss2->FixParameter(2,par[2]);


      hlabr_cross_amplitude[crystal]->Fit(gauss2, "MLESRNQ+");
      TF1 *gauss3 = new TF1(Form("gauss3%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 240, xPeaks.first + 160);
      gauss3->SetParameters(gauss2->GetParameters());
      
      gauss3->FixParameter(1, par[1]);
      gauss3->FixParameter(5, par[5]);
      gauss3->FixParameter(2,par[2]);
      

      hlabr_cross_amplitude[crystal]->Fit(gauss3, "MLESRNQ+");

      TF1 *gauss4 = new TF1(Form("gauss4%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 240, xPeaks.first + 160);
      gauss4->SetParameters(gauss3->GetParameters());
      
      gauss4->FixParameter(5,par[5]);
      gauss4->FixParameter(2, par[2]);

      

      hlabr_cross_amplitude[crystal]->Fit(gauss4, "MLESRNQ+");
       
      TF1 *gauss5 = new TF1(Form("gauss5%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 240, xPeaks.first + 160);
      gauss5->SetParameters(gauss4->GetParameters());
      
      gauss5->FixParameter(2,par[2]);

      hlabr_cross_amplitude[crystal]->Fit(gauss5, "MLESRNQ");
      TF1 *gauss6 = new TF1(Form("gauss6%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 240, xPeaks.first + 160);
      gauss6->SetParameters(gauss5->GetParameters());
      
      hlabr_cross_amplitude[crystal]->Fit(gauss6, "MLESRNQ0+");
      x[3]=gauss6->GetParameter(1);
      xe[3]=gauss6->GetParError(1);
      x[2]=gauss6->GetParameter(4);
      xe[2]=gauss6->GetParError(4);
      // if(x[1]>x[2]){
      // 	double value=x[1];
      // 	x[1]=x[2];
      // 	x[2]=value;
      // }
      // x[i+1]=gauss3->GetParameter(4);
      // Fit the histogram with the Gaussian function
      //  gauss3->SetLineColor(crystal+1); // Set different colors for each fit
      // hlabr_cross_amplitude[crystal]->Draw();
      gauss6->Draw("same");
      canvas->Update();
      delete gauss;
      delete gauss1;
      delete gauss2;
      delete gauss3;
      delete gauss4;
      delete gauss5;
      canvas2->cd(crystal+1);
      // originalHistogram->Rebin(4);
      
      hlabr_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(400,700);
      hlabr_cross_amplitude[crystal]->Draw("");
      TSpectrum *s_511 = new TSpectrum(3); // Adjust the number according to your expected number of peaks
      Int_t nFound_511 = s_511->Search(hlabr_cross_amplitude[crystal], 1, "", 0.05); // Adjust parameters as needed

      Double_t *xPositions_511 = s_511->GetPositionX();
      // std::vector<Double_t> peaks_150;
      // peaks_150.push_back(xPositions_511[0]);
      std::vector<std::pair<Double_t, Double_t>> peaks_511; // Pair of position and height

      // Retrieve positions and heights
      for (int i = 0; i < nFound_511; ++i) {
	Double_t height = hlabr_cross_amplitude[crystal]->GetBinContent(hlabr_cross_amplitude[crystal]->GetXaxis()->FindBin(xPositions_511[i]));
	peaks_511.push_back(std::make_pair(xPositions_511[i], height));
      }

      if (!peaks_511.empty()) {
	std::sort(peaks_511.begin(), peaks_511.end(), [](const std::pair<Double_t, Double_t> &a, const std::pair<Double_t, Double_t> &b) {
							return a.second > b.second; // Assuming you want to sort by the second element in the pair
						      });
 
	Double_t highestPeak_1500 = (peaks_511.front()).first;


    
  	TF1 *gauss111 = new TF1(Form("gauss111%d", crystal), "gaus(0)+pol1(3)", highestPeak_1500 - 40, highestPeak_1500 + 40);
  	gauss111->FixParameter(0,hlabr_cross_amplitude[crystal]->GetBinContent(hlabr_cross_amplitude[crystal]->GetXaxis()->FindBin(highestPeak_1500))-60);
  	gauss111->FixParameter(2,25);
  	gauss111->FixParameter(1, highestPeak_1500);
  	hlabr_cross_amplitude[crystal]->Fit(gauss111, "MLEISRNQ0+");
      
  	TF1 *gauss11 = new TF1(Form("gauss11%d", crystal), "gaus(0)+pol1(3)", highestPeak_1500 - 40, highestPeak_1500 + 40);
  	gauss11->SetParameters(gauss111->GetParameters());
  	gauss11->FixParameter(1,highestPeak_1500);
	gauss11->FixParameter(2,25);
	//	gauss11->FixParameter(0,hlabr_cross_amplitude[crystal]->GetBinContent(hlabr_cross_amplitude[crystal]->GetXaxis()->FindBin(highestPeak_1500))-600);
  	hlabr_cross_amplitude[crystal]->Fit(gauss11, "MLISRNQE+");

  	TF1 *gauss12 = new TF1(Form("gauss12%d", crystal), "gaus(0)+pol1(3)", highestPeak_1500 - 40, highestPeak_1500 + 40);
  	gauss12->SetParameters(gauss11->GetParameters());
        gauss12->FixParameter(1,highestPeak_1500);
  	hlabr_cross_amplitude[crystal]->Fit(gauss12, "MLISRNQ+");
  	TF1 *gauss13 = new TF1(Form("gauss13%d", crystal), "gaus(0)+pol1(3)", highestPeak_1500 - 40, highestPeak_1500 + 40);
  	gauss13->SetParameters(gauss12->GetParameters());
  	hlabr_cross_amplitude[crystal]->Fit(gauss13, "MLISRNQE");
       
  	// if(i>=1){
	x[1]=gauss13->GetParameter(1);
	xe[1]=gauss13->GetParError(1);
  	// double error=gauss13->GetParError(1);
  	// xPeaks_3D[run][crystal][i]=x[i];
  	// xPeaks_3D_error[run][crystal][i]=error;
  	// // Fit the histogram with the Gauss1ian function
	gauss13->SetLineColor(3); // Set different colors for each fit
  	// // hlabr_cross_amplitude[crystal]->Draw();
  	gauss13->Draw("same");
	canvas2->Update();
  	delete gauss111;
  	delete gauss11;
  	delete gauss12;
      }
    

      canvas3->cd(crystal+1);
      originalHistogram->GetXaxis()->SetRangeUser(20,60);
      originalHistogram->Draw("");

      TSpectrum *s_35 = new TSpectrum(1); // Adjust the number according to your expected number of peaks
      Int_t nFound_35 = s_35->Search(originalHistogram, 1, "", 0.05); // Adjust parameters as needed

      Double_t *xPositions_35 = s_35->GetPositionX();
      // std::vector<Double_t> peaks_1500;
      // peaks_1500.push_back(xPositions_511[0]);
      std::vector<std::pair<Double_t, Double_t>> peaks_35; // Pair of position and height

      // Retrieve positions and heights
      for (int i = 0; i < nFound_35; ++i){ 
	Double_t height = originalHistogram->GetBinContent(originalHistogram->GetXaxis()->FindBin(xPositions_35[i]));
	peaks_35.push_back(std::make_pair(xPositions_35[i], height));
      }

      if (!peaks_35.empty()) {
	// std::sort(peaks_511.begin(), peaks_511.end(), [](const std::pair<Double_t, Double_t> &a, const std::pair<Double_t, Double_t> &b) {
	// 						return a.second > b.second; // Assuming you want to sort by the second element in the pair
	// 					      });
 
	Double_t highestPeak_35 = (peaks_35.front()).first;


    
  	TF1 *gauss_first = new TF1(Form("gauss_first%d", crystal), "gaus(0)+pol1(3)", highestPeak_35 - 10, highestPeak_35 + 10);
  	gauss_first->FixParameter(0,originalHistogram->GetBinContent(originalHistogram->GetXaxis()->FindBin(highestPeak_35)));
  	gauss_first->FixParameter(2,25);
  	gauss_first->FixParameter(1, highestPeak_35);
  	originalHistogram->Fit(gauss_first, "MLEISRNQ0+");
      
  	TF1 *gauss_second = new TF1(Form("gauss_second%d", crystal), "gaus(0)+pol1(3)", highestPeak_35 - 10, highestPeak_35 + 10);
  	gauss_second->SetParameters(gauss_first->GetParameters());
  	gauss_second->FixParameter(1,highestPeak_35);
	gauss_second->FixParameter(2,25);
	//	gauss_second->FixParameter(0,originalHistogram->GetBinContent(originalHistogram->GetXaxis()->FindBin(highestPeak_35))-600);
  	originalHistogram->Fit(gauss_second, "MLISRNQE+");

  	TF1 *gauss_third = new TF1(Form("gauss_third%d", crystal), "gaus(0)+pol1(3)", highestPeak_35 - 10, highestPeak_35 + 10);
  	gauss_third->SetParameters(gauss_second->GetParameters());
        gauss_third->FixParameter(1,highestPeak_35);
  	originalHistogram->Fit(gauss_third, "MLISRNQE+");
  	TF1 *gauss_fourth = new TF1(Form("gauss_fourth%d", crystal), "gaus(0)+pol1(3)", highestPeak_35 - 10, highestPeak_35 + 10);
  	gauss_fourth->SetParameters(gauss_third->GetParameters());
  	originalHistogram->Fit(gauss_fourth, "MLISRNQE");
       
  	// if(i>=1){
	x[0]=gauss_fourth->GetParameter(1);
	xe[0]=gauss_fourth->GetParError(1);
  	// double error=gauss_fourth->GetParError(1);
  	// xPeaks_3D[run][crystal][i]=x[i];
  	// xPeaks_3D_error[run][crystal][i]=error;
  	// // Fit the histogram with the Gauss1ian function
	gauss_fourth->SetLineColor(3); // Set different colors for each fit
  	// // originalHistogram->Draw();
  	gauss_fourth->Draw("same");
	canvas3->Update();
  	delete gauss_first;
  	delete gauss_second;
  	delete gauss_third;
      }








      
      
    }
    double y[4]={35.5,511,1436,1461};
    // y[2]=(y[2]+y[3])/2;
    // x[2]=(x[2]+x[3])/2;
    double ye[4]={0,0,0,0};
    canvas1->cd(crystal+1);
    TGraph* graph = new TGraph(4, x, y);
    graph->SetName(Form("Calibration_of_Crystal_#_%d",crystal));
    graph->SetTitle(Form("Calibration_of_Crystal_#_%d",crystal));
 
    TF1 *linear = new TF1(Form("linear%d", crystal), "pol1",x[0],x[1]);
  
    graph->Fit(linear,"QR");
    // linear->SetParameter(0,0);
    // linear->SetParameter(1,slope);
    TF1 *linear1 = new TF1(Form("linear1%d", crystal), "pol1",x[0],x[1]);
    linear1->SetParameter(0,linear->GetParameter(0));
    linear1->SetParameter(1,linear->GetParameter(1));
      // linear1->SetParameter(2,linear->GetParameter(2));
    graph->Fit(linear,"QR");
    calibration_parameters[crystal][0]=linear1->GetParameter(0);
    calibration_parameters[crystal][1]=linear1->GetParameter(1);
      // calibration_parameters[crystal][2]=linear1->GetParameter(2);
    // calibration_parameters[crystal][3]=linear1->GetParameter(3);
    // calibration_parameters[crystal][4]=linear1->GetParameter(4);
    // calibration_parameters[crystal][2]=linear1->GetParameter(2);
    // calibration_parameters[crystal][3]=linear1->GetParameter(3);

    // calibration_parameters[crystal][2]=linear1->GetParameter(2);
    graph->SetMarkerStyle(7);
    graph->SetMarkerColor(kBlue);
    graph->Draw("AP");
    canvas1->Update();
    delete linear;
    delete linear1;




 TF1 *linear_highenergy = new TF1(Form("linear_highenergy%d", crystal), "pol1",x[2],x[3]);
   
    double slope=(y[0]-y[1])/(x[0]-x[1]);
    graph->Fit(linear_highenergy,"QR");
    // linear_highenergy->SetParameter(0,0);
    // linear_highenergy->SetParameter(1,slope);
    TF1 *linear_highenergy1 = new TF1(Form("linear_highenergy1%d", crystal), "pol1",x[2],x[3]);
    linear_highenergy1->SetParameter(0,linear_highenergy->GetParameter(0));
    linear_highenergy1->SetParameter(1,linear_highenergy->GetParameter(1));
    
    graph->Fit(linear_highenergy,"QR");
    calibration_parameters[crystal][3]=linear_highenergy1->GetParameter(0);
    calibration_parameters[crystal][4]=linear_highenergy1->GetParameter(1);
    std::cout<< crystal<<"   "<<calibration_parameters[crystal][3]<<"    "<<calibration_parameters[crystal][4]<<'\n';
    graph->SetMarkerStyle(7);
    graph->SetMarkerColor(kBlue);
    graph->Draw("AP");
    canvas1->Update();
    delete linear_highenergy;
    delete linear_highenergy1;



    
    // delete temp
    // delete gauss;
    // gPad->SetLimits(1500,1800);
  



    
  }
 
  // count=0;
  // Double_t labr3_ecal[16];
  // output->cd();
  // TTree* data_cal=new TTree("data_cal","labr_ecal");
  // data_cal->Branch("labr3_ecal",&labr3_ecal,"labr3_ecal[16]/D");
  

  // for(int i=0; i<nEntries; i++){
  //   data->GetEntry(i);
  //   for (int j = 0; j < 16; ++j) {
  //     //labr detectors
  //     double Ej=(labr_ecal.At(j));
     
  //     if(Ej > 10){
  // 	if(Ej<800)
  // 	  labr3_ecal[j]=calibration_parameters[j][0]+calibration_parameters[j][1]*Ej // +calibration_parameters[j][2]*pow(Ej,2)
  // 	    ;
  // 	else
  // 	  labr3_ecal[j]=calibration_parameters[j][3]+calibration_parameters[j][4]*Ej;
  // 	hlabr_cross_amplitude_calibrated[j]->Fill(labr3_ecal[j]);

  // 	hlabr_cross_amplitude_full_calibrated->Fill(labr3_ecal[j]);
  // 	Detector_Vs_E_Cal->Fill(labr3_ecal[j],j);
	
  //     }
      
  //   }
  //   data_cal->Fill();
  //   count++;
  //   int oneper = (int)(nEntries * 0.01);
  //   int fiveper = (int)(nEntries * 0.05);
  //   if( (count % oneper) == 0) {
  //     cout << "Events processed " << count << " - percent done " << (int)(count/oneper)*1 << "%"<<endl;
  //   }
  //   // if(count/oneper==110)
  //   //   break;
    
  // }
 
  // output->cd("cal");
  // for (int j = 0; j < 16; ++j) {
  //   //labr detectors
     
  //   hlabr_cross_amplitude_calibrated[j]->Write();
  // }
  // Detector_Vs_E_Cal->Write();
  // hlabr_cross_amplitude_full_calibrated->Write();
  // output->cd();
  // canvas->Write();
  // canvas1->Write();
  // data_cal->Write();
  // output->Close();
  // file1->Close();
}

void auto_fitter_summed(){
  TFile *graphs=new TFile("./analyzing_calibration.root","recreate");

  // No explicit size for the innermost vector since it will hold a dynamic number of peaks
  Double_t xPeaks_3D[nRuns][16][3];
  Double_t xPeaks_3D_error[nRuns][16][3];
  int counter=0;


    TFile* output=new TFile("calibration_test_run_full_linear_two_points_test.root","recreate");
    auto_fitter(output,"/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/",xPeaks_3D,xPeaks_3D_error,counter);
    counter+=1;
 

}

