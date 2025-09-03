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
void auto_fitter(TFile* output, string path,Double_t xPeaks_3D[nRuns][16][3],Double_t xPeaks_3D_error[nRuns][16][3],int run){
  Double_t calibration_parameters[16][5]; 
  // TCanvas *canvas = new TCanvas("canvas", "Fit Histogram with Gaussians_Doublet", 800, 600);
  // canvas->Divide(4,4);

  // TCanvas *canvas2 = new TCanvas("canvas2", "Fit Histogram with Gaussians_511", 800, 600);
  // canvas2->Divide(4,4);
  // TCanvas *canvas3 = new TCanvas("canvas3", "Fit Histogram with Gaussians_35.5", 800, 600);
  // canvas3->Divide(4,4);
  // TCanvas *canvas1 = new TCanvas("canvas1", "Calibration_Fit", 800, 600);
  // canvas1->Divide(4,4);

  double x[4];
  double xe[4];


  TH1D *hlabr_cross_amplitude[16];
  TH1D* hlabr_cross_amplitude_calibrated[16];
  TH1D *hlabr_cross_amplitude_full =new TH1D("hlabr_cross_amplitude_test_full","hlabr_cross_amplitude_test_full",3000,0,3000);
  TH1D *hlabr_cross_amplitude_full_calibrated=new TH1D("hlabr_cross_amplitude_test_full_calibrated","hlabr_cross_amplitude_test_full_calibrated",3000,0,3000);
  for(int i = 0; i < 16; i++){
    hlabr_cross_amplitude[i] = new TH1D(Form("hlabr_cross_amplitude_test_%d",i),Form("hlabr_cross_amplitude_test_%d",i),3000,0,3000);
    hlabr_cross_amplitude_calibrated[i] = new TH1D(Form("hlabr_cross_amplitude_test_calibrated_%d",i),Form("hlabr_cross_amplitude_test_calibrated_%d",i),3000,0,3000);
  }


 
  TH2D* Detector_Vs_E=new TH2D("Detector_Vs_E","Detector_Vs_E",3000,0,3000,16,0,16);
  TH2D* Detector_Vs_E_Cal=new TH2D("Detector_Vs_E_Cal","Detector_Vs_E_Cal",3000,0,3000,16,0,16);
  
 

  TChain* data=new TChain("trimmed_data");
   data->Add((path+"run-1422*").c_str());
  // data->Add((path+"run-1406*").c_str());
  
  // TTreeReaderArray<Double_t>labr_ecal(reader,"labr_ecal[16]");
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
     
      if(Ej > 10 &&corr_isdecay==1){
	hlabr_cross_amplitude[j]->Fill(Ej);

	hlabr_cross_amplitude_full->Fill(Ej);
	Detector_Vs_E->Fill(Ej,j);
	
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

  output->mkdir("raw");
  output->mkdir("cal");

  output->cd("raw");
  for (int j = 0; j < 16; ++j) {
    //labr detectors
     
    hlabr_cross_amplitude[j]->Write();

    

	
      
  }
  Detector_Vs_E->Write();
  hlabr_cross_amplitude_full->Write();


}

void Calibration(){
  //TFile *graphs=new TFile("./analyzing_calibration_1405.root","recreate");

  // No explicit size for the innermost vector since it will hold a dynamic number of peaks
  Double_t xPeaks_3D[nRuns][16][3];
  Double_t xPeaks_3D_error[nRuns][16][3];
  int counter=0;
  // for(int i:{1405}){

    TFile* output=new TFile("calibration_test_1422_decay.root","recreate");
    // TFile* file1=new TFile(Form("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/run-%d-sorted.root",i),"READ");
    auto_fitter(output,"/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/",xPeaks_3D,xPeaks_3D_error,counter);
  //   counter+=1;
  // }

    
  //  TCanvas* canvas_shift = new TCanvas("canvas_shift", "1173.2_across_runs", 80, 60);
  //   canvas_shift->Divide(4,4);
  //   double x_values[3]={1240,1423,1434};
  //   for (int i=0; i<16; i++){
  //     canvas_shift->cd(i+1);
  //     double peaks[3];
  //     double peaks_error[3];
  //     for(int j=0; j<3; j++){
  //       // if (xPeaks_3D[j][i].size() > 0 &&xPeaks_3D_error[j][i].size() > 0) {
  // 	peaks[j] = xPeaks_3D[j][i][1];
  // 	peaks_error[j] = xPeaks_3D_error[j][i][1];
  //       // } else {
  //       // 	// Handle the case where the peak does not exist, perhaps by setting a default value
  //       // 	peaks[j] = 0;
  //       // 	peaks_error[j] = 0;
  //       // }
  //     }
  //     TGraphErrors* graphResiduals = new TGraphErrors(3, x_values, peaks, nullptr, peaks_error); 
  // graphResiduals->SetMarkerStyle(7);
  //  graphResiduals->SetMarkerColor(2);
  // graphResiduals->Draw("AP");
  //  canvas_shift->Update();
  //   }


  // TCanvas* canvas_shift1 = new TCanvas("canvas_shift1", "1332.5_across_runs", 80, 60);
  //   canvas_shift1->Divide(4,4);
  //   // double x_values[3]={1240,1423,1434};
  //   for (int i=0; i<16; i++){
  //     canvas_shift1->cd(i+1);
  //     double peaks[3];
  //     double peaks_error[3];
  //     for(int j=0; j<3; j++){
  //       // if (xPeaks_3D[j][i].size() > 0 &&xPeaks_3D_error[j][i].size() > 0) {
  // 	peaks[j] = xPeaks_3D[j][i][2];
  // 	peaks_error[j] = xPeaks_3D_error[j][i][2];
  //       // } else {
  //       // 	// Handle the case where the peak does not exist, perhaps by setting a default value
  //       // 	peaks[j] = 0;
  //       // 	peaks_error[j] = 0;
  //       // }
  //     }
  //     TGraphErrors* graphResiduals = new TGraphErrors(3, x_values, peaks, nullptr, peaks_error); 
  // graphResiduals->SetMarkerStyle(7);
  //  graphResiduals->SetMarkerColor(2);
  // graphResiduals->Draw("AP");
  //  canvas_shift1->Update();
  // }



  
  // graphs->cd();
  // canvas_shift->Write();
  // canvas_shift1->Write();
  // graphs->Close();

}

