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
void auto_fitter(TFile* output, TFile* file1,Double_t xPeaks_3D[nRuns][16][3],Double_t xPeaks_3D_error[nRuns][16][3],int run){
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


  TH1D *hclover_cross_amplitude[16];
  TH1D* hclover_cross_amplitude_calibrated[16];
  TH1D *hclover_cross_amplitude_full =new TH1D("hclover_cross_amplitude_test_full","hclover_cross_amplitude_test_full",3000,0,30000);
  TH1D *hclover_cross_amplitude_full_calibrated=new TH1D("hclover_cross_amplitude_test_full_calibrated","hclover_cross_amplitude_test_full_calibrated",3000,0,3000);
  for(int i = 0; i < 16; i++){
    hclover_cross_amplitude[i] = new TH1D(Form("hclover_cross_amplitude_test_%d",i),Form("hclover_cross_amplitude_test_%d",i),3000,0,30000);
    hclover_cross_amplitude_calibrated[i] = new TH1D(Form("hclover_cross_amplitude_test_calibrated_%d",i),Form("hclover_cross_amplitude_test_calibrated_%d",i),3000,0,3000);
  }


 
  TH2D* Detector_Vs_E=new TH2D("Detector_Vs_E","Detector_Vs_E",3000,0,30000,16,0,16);
  TH2D* Detector_Vs_E_Cal=new TH2D("Detector_Vs_E_Cal","Detector_Vs_E_Cal",3000,0,3000,16,0,16);
  
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
      double Ej=labr_ecal.At(j);
     
      if(Ej > 10){
	hclover_cross_amplitude[j]->Fill(Ej);

	hclover_cross_amplitude_full->Fill(Ej);
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
    //clover detectors
     
    hclover_cross_amplitude[j]->Write();

    

	
      
  }
  Detector_Vs_E->Write();
  hclover_cross_amplitude_full->Write();


  
  for(int crystal=0; crystal<nCrystals;crystal++){
    canvas->cd(crystal+1);
 
   
    hclover_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(14000,18000);
    hclover_cross_amplitude[crystal]->Draw();
    // Use TSpectrum to find peaks
   
  
    TSpectrum *s = new TSpectrum(8); // Adjust the number according to your expected number of peaks
    Int_t nFound = s->Search(hclover_cross_amplitude[crystal], 1, "nobackground", 0.05); // Adjust parameters as needed

    Double_t *xPositions = s->GetPositionX();
    std::vector<std::pair<Double_t, Double_t>> peaks; // Pair of position and height

    // Retrieve positions and heights
    for (int i = 0; i < nFound; ++i) {
      Double_t height = hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPositions[i]));
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
							   return (highestPeak.first - peak.first) >= 200 && (highestPeak.first - peak.first)<=400 && (highestPeak.second<=3*peak.second)&&(highestPeak.second-peak.second)>=50;
							   //   else{
							   // 	return highestPeak.first-peak.first>=10;
							   //   }
							 });

   


      // Now draw the histogram and markers
      // TCanvas *c1 = new TCanvas("c1", "Peaks", 800, 600);
      hclover_cross_amplitude[crystal]->Draw("");

    
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
							     return (highestPeak.first - peak.first) >= 100 &&(highestPeak.first - peak.first)<=400 &&(highestPeak.second<=3*peak.second)&&(highestPeak.second-peak.second)>=50;
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
      auto originalHistogram = (TH1*)hclover_cross_amplitude[crystal]->Clone("originalHistogram");
      hclover_cross_amplitude[crystal]->Rebin(4);
      hclover_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(14000,18000);
      //  if (!xPeaks.second)
      //      xPeaks.second=xPeaks.first-150;
      double par[6]={hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks.first)),xPeaks.first,130,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks.second)),xPeaks.second,160};
      
      TF1 *gauss = new TF1(Form("gauss%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 2400, xPeaks.first + 1600);

      gauss->FixParameter(0,par[0]);
      gauss->FixParameter(1, par[1]);
      gauss->FixParameter(2,par[2]);
      gauss->FixParameter(3,par[3]);
      gauss->FixParameter(4, par[4]);
      gauss->FixParameter(5,par[5]);
     
      hclover_cross_amplitude[crystal]->Fit(gauss, "MLESRNQ0+");
      
      TF1 *gauss1 = new TF1(Form("gauss1%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 2400, xPeaks.first + 1600);
      gauss1->SetParameters(gauss->GetParameters());
      
      gauss1->FixParameter(0,par[0]);
      gauss1->FixParameter(1, par[1]);
      gauss1->FixParameter(2,par[2]);
      gauss1->FixParameter(4, par[4]);
      gauss1->FixParameter(5,par[5]);
      hclover_cross_amplitude[crystal]->Fit(gauss1, "MLESRNQ+");

      TF1 *gauss2 = new TF1(Form("gauss2%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 2400, xPeaks.first + 1600);
      gauss2->SetParameters(gauss1->GetParameters());
   
     
      gauss2->FixParameter(1, par[1]);
      gauss2->FixParameter(4, par[4]);
     
      gauss2->FixParameter(5,par[5]);
      gauss2->FixParameter(2,par[2]);


      hclover_cross_amplitude[crystal]->Fit(gauss2, "MLESRNQ+");
      TF1 *gauss3 = new TF1(Form("gauss3%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 2400, xPeaks.first + 1600);
      gauss3->SetParameters(gauss2->GetParameters());
      
      gauss3->FixParameter(1, par[1]);
      gauss3->FixParameter(5, par[5]);
      gauss3->FixParameter(2,par[2]);
      

      hclover_cross_amplitude[crystal]->Fit(gauss3, "MLESRNQ+");

      TF1 *gauss4 = new TF1(Form("gauss4%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 2400, xPeaks.first + 1600);
      gauss4->SetParameters(gauss3->GetParameters());
      
      gauss4->FixParameter(5,par[5]);
      gauss4->FixParameter(2, par[2]);

      

      hclover_cross_amplitude[crystal]->Fit(gauss4, "MLESRNQ+");
       
      TF1 *gauss5 = new TF1(Form("gauss5%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 2400, xPeaks.first + 1600);
      gauss5->SetParameters(gauss4->GetParameters());
      
      gauss5->FixParameter(2,par[2]);

      hclover_cross_amplitude[crystal]->Fit(gauss5, "MLESRNQ");
      TF1 *gauss6 = new TF1(Form("gauss6%d", crystal), "gaus(0)+gaus(3)+expo(6)", xPeaks.first - 2400, xPeaks.first + 1600);
      gauss6->SetParameters(gauss5->GetParameters());
      
      hclover_cross_amplitude[crystal]->Fit(gauss6, "MLESRNQ0+");
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
      // hclover_cross_amplitude[crystal]->Draw();
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
      
      hclover_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(4900,7000);
      hclover_cross_amplitude[crystal]->Draw("");
      TSpectrum *s_511 = new TSpectrum(3); // Adjust the number according to your expected number of peaks
      Int_t nFound_511 = s_511->Search(hclover_cross_amplitude[crystal], 1, "", 0.05); // Adjust parameters as needed

      Double_t *xPositions_511 = s_511->GetPositionX();
      // std::vector<Double_t> peaks_1500;
      // peaks_1500.push_back(xPositions_511[0]);
      std::vector<std::pair<Double_t, Double_t>> peaks_511; // Pair of position and height

      // Retrieve positions and heights
      for (int i = 0; i < nFound_511; ++i) {
	Double_t height = hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPositions_511[i]));
	peaks_511.push_back(std::make_pair(xPositions_511[i], height));
      }

      if (!peaks_511.empty()) {
	std::sort(peaks_511.begin(), peaks_511.end(), [](const std::pair<Double_t, Double_t> &a, const std::pair<Double_t, Double_t> &b) {
							return a.second > b.second; // Assuming you want to sort by the second element in the pair
						      });
 
	Double_t highestPeak_1500 = (peaks_511.front()).first;


    
  	TF1 *gauss111 = new TF1(Form("gauss111%d", crystal), "gaus(0)+pol1(3)", highestPeak_1500 - 400, highestPeak_1500 + 400);
  	gauss111->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(highestPeak_1500))-600);
  	gauss111->FixParameter(2,25);
  	gauss111->FixParameter(1, highestPeak_1500);
  	hclover_cross_amplitude[crystal]->Fit(gauss111, "MLEISRNQ0+");
      
  	TF1 *gauss11 = new TF1(Form("gauss11%d", crystal), "gaus(0)+pol1(3)", highestPeak_1500 - 400, highestPeak_1500 + 400);
  	gauss11->SetParameters(gauss111->GetParameters());
  	gauss11->FixParameter(1,highestPeak_1500);
	gauss11->FixParameter(2,25);
	//	gauss11->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(highestPeak_1500))-600);
  	hclover_cross_amplitude[crystal]->Fit(gauss11, "MLISRNQE+");

  	TF1 *gauss12 = new TF1(Form("gauss12%d", crystal), "gaus(0)+pol1(3)", highestPeak_1500 - 400, highestPeak_1500 + 400);
  	gauss12->SetParameters(gauss11->GetParameters());
        gauss12->FixParameter(1,highestPeak_1500);
  	hclover_cross_amplitude[crystal]->Fit(gauss12, "MLISRNQE+");
  	TF1 *gauss13 = new TF1(Form("gauss13%d", crystal), "gaus(0)+pol1(3)", highestPeak_1500 - 400, highestPeak_1500 + 400);
  	gauss13->SetParameters(gauss12->GetParameters());
  	hclover_cross_amplitude[crystal]->Fit(gauss13, "MLISRNQE");
       
  	// if(i>=1){
	x[1]=gauss13->GetParameter(1);
	xe[1]=gauss13->GetParError(1);
  	// double error=gauss13->GetParError(1);
  	// xPeaks_3D[run][crystal][i]=x[i];
  	// xPeaks_3D_error[run][crystal][i]=error;
  	// // Fit the histogram with the Gauss1ian function
	gauss13->SetLineColor(3); // Set different colors for each fit
  	// // hclover_cross_amplitude[crystal]->Draw();
  	gauss13->Draw("same");
	canvas2->Update();
  	delete gauss111;
  	delete gauss11;
  	delete gauss12;
      }
    

      canvas3->cd(crystal+1);
      originalHistogram->GetXaxis()->SetRangeUser(200,600);
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


    
  	TF1 *gauss_first = new TF1(Form("gauss_first%d", crystal), "gaus(0)+pol1(3)", highestPeak_35 - 100, highestPeak_35 + 100);
  	gauss_first->FixParameter(0,originalHistogram->GetBinContent(originalHistogram->GetXaxis()->FindBin(highestPeak_35)));
  	gauss_first->FixParameter(2,25);
  	gauss_first->FixParameter(1, highestPeak_35);
  	originalHistogram->Fit(gauss_first, "MLEISRNQ0+");
      
  	TF1 *gauss_second = new TF1(Form("gauss_second%d", crystal), "gaus(0)+pol1(3)", highestPeak_35 - 100, highestPeak_35 + 100);
  	gauss_second->SetParameters(gauss_first->GetParameters());
  	gauss_second->FixParameter(1,highestPeak_35);
	gauss_second->FixParameter(2,25);
	//	gauss_second->FixParameter(0,originalHistogram->GetBinContent(originalHistogram->GetXaxis()->FindBin(highestPeak_35))-600);
  	originalHistogram->Fit(gauss_second, "MLISRNQE+");

  	TF1 *gauss_third = new TF1(Form("gauss_third%d", crystal), "gaus(0)+pol1(3)", highestPeak_35 - 100, highestPeak_35 + 100);
  	gauss_third->SetParameters(gauss_second->GetParameters());
        gauss_third->FixParameter(1,highestPeak_35);
  	originalHistogram->Fit(gauss_third, "MLISRNQE+");
  	TF1 *gauss_fourth = new TF1(Form("gauss_fourth%d", crystal), "gaus(0)+pol1(3)", highestPeak_35 - 100, highestPeak_35 + 100);
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
  
    graph->Fit(linear,"MER");
    // linear->SetParameter(0,0);
    // linear->SetParameter(1,slope);
    TF1 *linear1 = new TF1(Form("linear1%d", crystal), "pol1",x[0],x[1]);
    linear1->SetParameter(0,linear->GetParameter(0));
    linear1->SetParameter(1,linear->GetParameter(1));
      // linear1->SetParameter(2,linear->GetParameter(2));
    graph->Fit(linear,"R");
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
    graph->Fit(linear_highenergy,"MER");
    // linear_highenergy->SetParameter(0,0);
    // linear_highenergy->SetParameter(1,slope);
    TF1 *linear_highenergy1 = new TF1(Form("linear_highenergy1%d", crystal), "pol1",x[2],x[3]);
    linear_highenergy1->SetParameter(0,linear_highenergy->GetParameter(0));
    linear_highenergy1->SetParameter(1,linear_highenergy->GetParameter(1));
    
    graph->Fit(linear_highenergy,"R");
    calibration_parameters[crystal][3]=linear_highenergy1->GetParameter(0);
    calibration_parameters[crystal][4]=linear_highenergy1->GetParameter(1);
    
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
  // hclover_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(500,1800);
  // TSpectrum *spectrum_1500 = new TSpectrum(2);  // Number of peaks to look for can be specified as an argument
  // Int_t nPeaks_1500=spectrum_1500->Search(hclover_cross_amplitude[crystal],5,"",1);
  // Double_t *xPeaks_1500 = spectrum_1500->GetPositionX();
  // hclover_cross_amplitude[crystal]->GetXaxis()->SetRangeUser(1100,xPeaks_1500[0]-100);
  // spectrum_1500->Draw("same");
  // TSpectrum *spectrum_1332 = new TSpectrum(2);  // Number of peaks to look for can be specified as an argument
  // Int_t nPeaks_1332=spectrum_1332->Search(hclover_cross_amplitude[crystal],3,"",.5);
  // // Retrieve the positions of the found peaks
  // Double_t *xPeaks_75 = spectrum_75->GetPositionX();
  // Double_t *xPeaks_1332 = spectrum_1332->GetPositionX();
  // std::vector<Double_t> xPeaks;
  // xPeaks.push_back(xPeaks_75[0]);
  // xPeaks.push_back(xPeaks_1332[0]);
  // xPeaks.push_back(xPeaks_1332[1]);
  // xPeaks.push_back(xPeaks_1500[0]);
  // xPeaks.push_back(xPeaks_1500[1]);
  // TMarker *marker = new TMarker(xPeaks[3], hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[3])), 20);
  //  marker->Draw("SAME");
  //  TMarker *marker1 = new TMarker(xPeaks[4], hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[4])), 20);
  //   marker1->Draw("SAME");
     
  // hclover_cross_amplitude[crystal]->GetXaxis()->UnZoom();
  
  // double y[3]={75,1173.2,1332.5};
   
  //   for (int i = 0; i < 3; i++) {
    
  //     if(i<3){
  // 	// Define a Gaussian function for each peak
  // 	TF1 *gauss = new TF1(Form("gauss%d", i), "gaus(0)+pol1(3)", xPeaks[i] - 40, xPeaks[i] + 40);
  // 	gauss->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i])));
  // 	gauss->FixParameter(2,2);
  // 	gauss->FixParameter(1, xPeaks[i]);
  // 	hclover_cross_amplitude[crystal]->Fit(gauss, "MLISRNQ");
      
  // 	TF1 *gauss1 = new TF1(Form("gauss1%d", i), "gaus(0)+pol1(3)", xPeaks[i] - 40, xPeaks[i] + 40);
  // 	gauss1->SetParameters(gauss->GetParameters());
  // 	gauss1->FixParameter(1,xPeaks[i]);
  // 	gauss1->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i])));
  // 	hclover_cross_amplitude[crystal]->Fit(gauss1, "MLISRNQ");

  // 	TF1 *gauss2 = new TF1(Form("gauss2%d", i), "gaus(0)+pol1(3)", xPeaks[i] - 40, xPeaks[i] + 40);
  // 	gauss2->SetParameters(gauss1->GetParameters());
  // 	gauss2->FixParameter(0,hclover_cross_amplitude[crystal]->GetBinContent(hclover_cross_amplitude[crystal]->GetXaxis()->FindBin(xPeaks[i])));
  // 	hclover_cross_amplitude[crystal]->Fit(gauss2, "MLISRNQ");
  // 	TF1 *gauss3 = new TF1(Form("gauss3%d", i), "gaus(0)+pol1(3)", xPeaks[i] - 40, xPeaks[i] + 40);
  // 	gauss3->SetParameters(gauss2->GetParameters());
  // 	hclover_cross_amplitude[crystal]->Fit(gauss3, "MLISRNQ");
       
  // 	// if(i>=1){
  // 	x[i]=gauss3->GetParameter(1);
  // 	double error=gauss3->GetParError(1);
  // 	xPeaks_3D[run][crystal][i]=x[i];
  // 	xPeaks_3D_error[run][crystal][i]=error;
  // 	// Fit the histogram with the Gaussian function
  // 	gauss3->SetLineColor(i + 2); // Set different colors for each fit
  // 	// hclover_cross_amplitude[crystal]->Draw();
  // 	gauss3->Draw("same");
   
  // 	delete gauss;
  // 	delete gauss1;
  // 	delete gauss2;

  //     }
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
    
   
      
  // }


  
  //  hclover_cross_amplitude[crystal]->GetXaxis()->UnZoom();
  //   canvas->Update();
  //   gPad-> SetLogy();
  //   canvas1->cd(crystal+1);
  //   TGraph* graph=new TGraph(3,x,y);
  //   graph->SetName(Form("Calibration_of_Crystal_#_%d",crystal));
  //   graph->SetTitle(Form("Calibration_of_Crystal_#_%d",crystal));
  //   TF1 *linear = new TF1(Form("linear%d", crystal), "pol1",x[1],x[2]);
  //   double slope=(y[0]-y[1])/(x[0]-x[1]);
  //   graph->Fit(linear,"MLISRNQ");
  //   // linear->SetParameter(0,0);
  //   // linear->SetParameter(1,slope);
  //   TF1 *linear1 = new TF1(Form("linear1%d", crystal), "pol1",x[1],x[2]);
  //   linear1->SetParameter(0,linear->GetParameter(0));
  //   linear1->SetParameter(1,linear->GetParameter(1));
  //   // linear1->SetParameter(2,linear->GetParameter(2));
  //   graph->Fit(linear1,"MLISRNQ");
  //   calibration_parameters[crystal][0]=linear1->GetParameter(0);
  //   calibration_parameters[crystal][1]=linear1->GetParameter(1);
  //   // calibration_parameters[crystal][2]=linear1->GetParameter(2);
  //   // calibration_parameters[crystal][3]=linear1->GetParameter(3);

  //   // calibration_parameters[crystal][2]=linear1->GetParameter(2);
  //   graph->SetMarkerSize();
  //   graph->SetMarkerStyle(20);
  //   graph->Draw("AP");
  //   canvas1->Update();
  //   delete linear;
  //   delete linear1;
  //   // delete temp
  //   // delete gauss;
  //   // gPad->SetLimits(1500,1800);
  // }
  // // canvas->SetLogy();
  count=0;
  Double_t labr3_ecal[16];
  output->cd();
  TTree* data_cal=new TTree("data_cal","labr_ecal");
  data_cal->Branch("labr3_ecal",&labr3_ecal,"labr3_ecal[16]/D");
  
  reader.SetEntry(0);
  while(reader.Next()){
    // data->GetEntry(i);
    for (int j = 0; j < 16; ++j) {
      //clover detectors
      double Ej=(labr_ecal.At(j));
     
      if(Ej > 100){
	if(Ej<8000)
	  labr3_ecal[j]=calibration_parameters[j][0]+calibration_parameters[j][1]*Ej // +calibration_parameters[j][2]*pow(Ej,2)
	    ;
	else
	  labr3_ecal[j]=calibration_parameters[j][3]+calibration_parameters[j][4]*Ej;
  	hclover_cross_amplitude_calibrated[j]->Fill(labr3_ecal[j]);

  	hclover_cross_amplitude_full_calibrated->Fill(labr3_ecal[j]);
	Detector_Vs_E_Cal->Fill(labr3_ecal[j],j);
	
      }
      
    }
    data_cal->Fill();
    count++;
    int oneper = (int)(nEntries * 0.01);
    int fiveper = (int)(nEntries * 0.05);
    if( (count % oneper) == 0) {
      cout << "Events processed " << count << " - percent done " << (int)(count/oneper)*1 << "%"<<endl;
    }
    // if(count/oneper==110)
    //   break;
    
  }
 
  output->cd("cal");
  for (int j = 0; j < 16; ++j) {
    //clover detectors
     
    hclover_cross_amplitude_calibrated[j]->Write();
  }
  Detector_Vs_E_Cal->Write();
  hclover_cross_amplitude_full_calibrated->Write();
  output->cd();
  canvas->Write();
  canvas1->Write();
  data_cal->Write();
  // output->Close();
  // file1->Close();
}

void auto_fitter_summed_experimental_data(){
  TFile *graphs=new TFile("./analyzing_calibration.root","recreate");

  // No explicit size for the innermost vector since it will hold a dynamic number of peaks
  Double_t xPeaks_3D[nRuns][16][3];
  Double_t xPeaks_3D_error[nRuns][16][3];
  int counter=0;
  for(int i:{1430}){

    TFile* output=new TFile(Form("calibration_test_run_%d_linear_two_points_test.root",i),"recreate");
    TFile* file1=new TFile(Form("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resortedNewCal37Na/run-%d-sorted.root",i),"READ");
    auto_fitter(output,file1,xPeaks_3D,xPeaks_3D_error,counter);
    counter+=1;
  }
  //  TCanvas* canvas_shift = new TCanvas("canvas_shift", "1173.2_across_runs", 800, 600);
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


  // TCanvas* canvas_shift1 = new TCanvas("canvas_shift1", "1332.5_across_runs", 800, 600);
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

