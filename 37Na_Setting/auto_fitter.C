#include "TFile.h"
#include "TH1.h"
#include "TSpectrum.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TTree.h"
#include "TBranch.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TMarker.h"
const int nPeaks=3;
const int nCrystals=16; //number of labr3 

void auto_fitter(TFile* output, TFile* file1,std::vector<std::vector<std::vector<Double_t>>> xPeaks_3D, int run){
  Double_t calibration_parameters[16][2]; 
  TCanvas *canvas = new TCanvas("canvas", "Fit Histogram with Gaussians", 800, 600);
  canvas->Divide(4,4);

  TCanvas *canvas1 = new TCanvas("canvas1", "Calibration_Fit", 800, 600);
  canvas1->Divide(4,4);




  TH1D *hclover_cross_amplitude[16];
  TH1D* hclover_cross_amplitude_calibrated[16];
  TH1D *hclover_cross_amplitude_full =new TH1D("hclover_cross_amplitude_test_full","hclover_cross_amplitude_test_full",3000,0,3000);
  TH1D *hclover_cross_amplitude_full_calibrated=new TH1D("hclover_cross_amplitude_test_full_calibrated","hclover_cross_amplitude_test_full_calibrated",3000,0,3000);
  for(int i = 0; i < 16; i++){
    hclover_cross_amplitude[i] = new TH1D(Form("hclover_cross_amplitude_test_%d",i),Form("hclover_cross_amplitude_test_%d",i),3000,0,3000);
    hclover_cross_amplitude_calibrated[i] = new TH1D(Form("hclover_cross_amplitude_test_calibrated_%d",i),Form("hclover_cross_amplitude_test_calibrated_%d",i),3000,0,3000);
  }

 


  
  TTree *data = dynamic_cast<TTree*>(file1->Get("data"));
  
  // Check if the tree exists
  if (!data) {
    std::cerr << "Tree 'clover' not found in the file!" << std::endl;
    file1->Close();
  }

  TTreeReader reader(data);
  
  TTreeReaderArray<Double_t>labr_ecal(reader,"labr.energy[16]");

  long int nEntries= data->GetEntries();
  int count=0;
  int progressInterval = nEntries / 100; 
  while(reader.Next()){
    // data->GetEntry(i);
    for (int j = 0; j < 16; ++j) {
      //clover detectors
      double Ej=labr_ecal.At(j)/10;
     
      if(Ej > 10){
	hclover_cross_amplitude[j]->Fill(Ej);

	hclover_cross_amplitude_full->Fill(Ej);

	
      }
      
    }
    count++;
    int oneper = (int)(nEntries * 0.01);
    int fiveper = (int)(nEntries * 0.05);
    if( (count % oneper) == 0) {
      cout << "Events processed " << count << " - percent done " << (int)(count/oneper)*1 << "%"<<endl;
      if (count/oneper==5)
	break;
    }
  }
  count=0;

  output->mkdir("raw");
  output->mkdir("cal");

  output->cd("raw");
  for (int j = 0; j < 16; ++j) {
    //clover detectors
     
    hclover_cross_amplitude[j]->Write();



	
      
  }
  hclover_cross_amplitude_full->Write();


  
  for(int crystal=0; crystal<nCrystals;crystal++){
    canvas->cd(crystal+1);
 
    hclover_cross_amplitude[crystal]->Draw();
    hclover_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(20,70);
    // Use TSpectrum to find peaks
    TSpectrum *spectrum_75 = new TSpectrum(1);  // Number of peaks to look for can be specified as an argument
    Int_t nPeaks_75=spectrum_75->Search(hclover_cross_amplitude[crystal],1,"",.1);
    hclover_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(1000,2000);
    TSpectrum *spectrum_1500 = new TSpectrum(2);  // Number of peaks to look for can be specified as an argument
    Int_t nPeaks_1500=spectrum_1500->Search(hclover_cross_amplitude[crystal],5,"",1);
    Double_t *xPeaks_1500 = spectrum_1500->GetPositionX();
    hclover_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(1100,xPeaks_1500[0]-100);
    spectrum_1500->Draw("same");
    TSpectrum *spectrum_1332 = new TSpectrum(2);  // Number of peaks to look for can be specified as an argument
    Int_t nPeaks_1332=spectrum_1332->Search(hclover_cross_amplitude[crystal],3,"",.5);
    // Retrieve the positions of the found peaks
    Double_t *xPeaks_75 = spectrum_75->GetPositionX();
    Double_t *xPeaks_1332 = spectrum_1332->GetPositionX();
    std::vector<Double_t> xPeaks;
    xPeaks.push_back(xPeaks_75[0]);
    xPeaks.push_back(xPeaks_1332[0]);
    xPeaks.push_back(xPeaks_1332[1]);
    xPeaks_3D[run][crystal] = xPeaks;
    // xPeaks.push_back(xPeaks_1500[0]);
    // xPeaks.push_back(xPeaks_1500[1]);
    // TMarker *marker = new TMarker(xPeaks[3], hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[3])), 20);
    //  marker->Draw("SAME");
    //  TMarker *marker1 = new TMarker(xPeaks[4], hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[4])), 20);
    //   marker1->Draw("SAME");
     
    hclover_cross_amplitude[crystal]->GetXaxis()->UnZoom();
    double x[5];
    double y[5]={75,1173.2,1332.5,1435,1461};
   
    for (int i = 0; i < 3; i++) {
    
      if(i<3){
	// Define a Gaussian function for each peak
	TF1 *gauss = new TF1(Form("gauss%d", i), "gaus(0)+pol1(3)", xPeaks[i] - 40, xPeaks[i] + 40);
	gauss->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i])));
	gauss->FixParameter(2,2);
	gauss->FixParameter(1, xPeaks[i]);
	hclover_cross_amplitude[crystal]->Fit(gauss, "MLISRNQ");
      
	TF1 *gauss1 = new TF1(Form("gauss1%d", i), "gaus(0)+pol1(3)", xPeaks[i] - 40, xPeaks[i] + 40);
	gauss1->SetParameters(gauss->GetParameters());
	gauss1->FixParameter(1,xPeaks[i]);
	gauss1->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i])));
	hclover_cross_amplitude[crystal]->Fit(gauss1, "MLISRNQ");

	TF1 *gauss2 = new TF1(Form("gauss2%d", i), "gaus(0)+pol1(3)", xPeaks[i] - 40, xPeaks[i] + 40);
	gauss2->SetParameters(gauss1->GetParameters());
	gauss2->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i])));
	hclover_cross_amplitude[crystal]->Fit(gauss2, "MLISRNQ");
	TF1 *gauss3 = new TF1(Form("gauss3%d", i), "gaus(0)+pol1(3)", xPeaks[i] - 40, xPeaks[i] + 40);
	gauss3->SetParameters(gauss2->GetParameters());
	hclover_cross_amplitude[crystal]->Fit(gauss3, "MLISRNQ");
       
	// if(i>=1){
	x[i]=gauss3->GetParameter(1);
	// Fit the histogram with the Gaussian function
	gauss3->SetLineColor(i + 2); // Set different colors for each fit
	// hclover_cross_amplitude[crystal]->Draw();
	gauss3->Draw("same");
   
	delete gauss;
	delete gauss1;
	delete gauss2;

      }
      //      else{
      // TF1 *gauss = new TF1(Form("gauss%d", i), "gaus(0)+gaus(3)+pol1(6)", xPeaks[i] - 60, xPeaks[i] + 60);
      // if(xPeaks[i]>xPeaks[i-1]){
      //      gauss->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i])));
      //      gauss->FixParameter(1, xPeaks[i]);
      // }
      //      gauss->FixParameter(2,15);
     
      //      if(xPeaks[i+1]>xPeaks[i-1]){
      //      gauss->FixParameter(3,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i+1])));
      //      gauss->FixParameter(4, xPeaks[i+1]);
      //      }
      //      gauss->FixParameter(5,15);
     
      //      hclover_cross_amplitude[crystal]->Fit(gauss, "MLISRNQ");
      
      //      TF1 *gauss1 = new TF1(Form("gauss1%d", i), "gaus(0)+gaus(3)+pol1(6)", xPeaks[i] - 60, xPeaks[i] + 60);
      //      gauss1->SetParameters(gauss->GetParameters());
      //      if(xPeaks[i]>xPeaks[i-1]){
      //      gauss1->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i])));
      //      gauss1->FixParameter(1, xPeaks[i]);
      //      }
      //      if(xPeaks[i+1]>xPeaks[i-1]){
      //      gauss1->FixParameter(3,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i+1])));
      //      gauss1->FixParameter(4, xPeaks[i+1]);
      //      }
      //      hclover_cross_amplitude[crystal]->Fit(gauss1, "MLISRNQ");

      //      TF1 *gauss2 = new TF1(Form("gauss2%d", i), "gaus(0)+gaus(3)+pol1(6)", xPeaks[i] - 60, xPeaks[i] + 60);
      //      gauss2->SetParameters(gauss1->GetParameters());
      //      if(xPeaks[i]>xPeaks[i-1]){
      //      gauss2->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i])));
      //      }
      //      if(xPeaks[i]>xPeaks[i+1]){
      //      gauss2->FixParameter(3,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i+1])));
      //      }
      //      hclover_cross_amplitude[crystal]->Fit(gauss2, "MLISRNQ");
      //      TF1 *gauss3 = new TF1(Form("gauss3%d", i), "gaus(0)+gaus(3)+pol1(6)", xPeaks[i] - 60, xPeaks[i] + 60);
      //      gauss3->SetParameters(gauss2->GetParameters());
      //      hclover_cross_amplitude[crystal]->Fit(gauss3, "MLISRNQ");
      //      x[i]=gauss3->GetParameter(1);
      //      x[i+1]=gauss3->GetParameter(4);
      //            // Fit the histogram with the Gaussian function
      //      gauss3->SetLineColor(i + 2); // Set different colors for each fit
      //      // hclover_cross_amplitude[crystal]->Draw();
      //      gauss3->Draw("same");
   
      //      delete gauss;
      //      delete gauss1;
      //      delete gauss2;

      //      }



	
      // x_low_energy[i]=gauss3->GetParameter(1);
      // x_low_energy_error[i]=gauss3->GetParError(1);
     
      // delete gauss3;
    
   
      
    }


  
    hclover_cross_amplitude[crystal]->GetXaxis()->UnZoom();
    canvas->Update();
    gPad-> SetLogy();
    canvas1->cd(crystal+1);
    TGraph* graph=new TGraph(5,x,y);
    graph->SetName(Form("Calibration_of_Crystal_#_%d",crystal));
    graph->SetTitle(Form("Calibration_of_Crystal_#_%d",crystal));
    TF1 *linear = new TF1(Form("linear%d", crystal), "pol1",x[1],x[4]);
    double slope=(y[0]-y[1])/(x[0]-x[1]);
    graph->Fit(linear,"MLISR");
    // linear->SetParameter(0,0);
    // linear->SetParameter(1,slope);
    TF1 *linear1 = new TF1(Form("linear1%d", crystal), "pol1",x[1],x[4]);
    linear1->SetParameter(0,linear->GetParameter(0));
    linear1->SetParameter(1,linear->GetParameter(1));
    // linear1->SetParameter(2,linear->GetParameter(2));
    graph->Fit(linear1,"MLISR");
    calibration_parameters[crystal][0]=linear1->GetParameter(0);
    calibration_parameters[crystal][1]=linear1->GetParameter(1);
    // calibration_parameters[crystal][2]=linear1->GetParameter(2);
    // calibration_parameters[crystal][3]=linear1->GetParameter(3);

    // calibration_parameters[crystal][2]=linear1->GetParameter(2);
    graph->SetMarkerSize();
    graph->SetMarkerStyle(20);
    graph->Draw("AP");
    canvas1->Update();
    delete linear;
    delete linear1;
    // delete temp
    // delete gauss;
    // gPad->SetLimits(1500,1800);
  }
  // canvas->SetLogy();
  count=0;
  Double_t labr3_ecal[16];
  TTree* data_cal=new TTree("data_cal","labr_ecal");
  data_cal->Branch("labr3_ecal",&labr3_ecal,"labr3_ecal[16]/D");
  
  //  reader.SetEntry(0);
  // while(reader.Next()){
  //    // data->GetEntry(i);
  //    for (int j = 0; j < 16; ++j) {
  //      //clover detectors
  //      double Ej=(labr_ecal.At(j)/10);
     
  //      if(Ej > 10){
  // 	labr3_ecal[j]=calibration_parameters[j][0]+calibration_parameters[j][1]*Ej;
  // 	hclover_cross_amplitude_calibrated[j]->Fill(labr3_ecal[j]);

  // 	hclover_cross_amplitude_full_calibrated->Fill(labr3_ecal[j]);

	
  //      }
      
  //    }
  //    data_cal->Fill();
  //    count++;
  //    int oneper = (int)(nEntries * 0.01);
  //    int fiveper = (int)(nEntries * 0.05);
  //    if( (count % oneper) == 0) {
  //      cout << "Events processed " << count << " - percent done " << (int)(count/oneper)*1 << "%"<<endl;
  //    }
  //    // if(count/oneper==110)
  //    //   break;
    
  //  }

  output->cd("cal");
  for (int j = 0; j < 16; ++j) {
    //clover detectors
     
    hclover_cross_amplitude_calibrated[j]->Write();



	
      
  }
  hclover_cross_amplitude_full_calibrated->Write();

  data_cal->Write();
}

int main(){
std::vector<std::vector<std::vector<Double_t>>> xPeaks_3D;
  int count=0;
  for(int i:{1240,1423,1434}){

    TFile* output=new TFile(Form("calibration_test_run_%d_linear_two_points.root",i),"recreate");
    TFile* file1=new TFile(Form("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-%d-sorted.root",i),"READ");
    auto_fitter(output,file1,xPeaks_3D,count);
		count+=1;
  }
  return 0;

}

