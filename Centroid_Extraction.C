#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TList.h>
#include <iomanip>
#include <chrono>
#include <thread>
#include <iostream>
// #include"TProof.h"
// #include "TProofServ.h"
#include "TChain.h"
#include<TF1.h>
#include<TCanvas.h>
#include<TH1.h>
#include<TH2.h>
#include<TGraphErrors.h>

void Stuff(TFile* input, TTree* data, TH2D *hist[15][15], const char *branchname, TH2D* A7A,TH1D* Zibby[15][15], TH1D* Zobry, int minbin, int maxbin, int minbine, int maxbine){

  TTreeReader reader(data);
  TTreeReaderValue<Int_t> index_i{reader, "index_i"};
  TTreeReaderValue<Double_t> Ei{reader, "Ei"};
  TTreeReaderValue<Double_t> Ej{reader, "Ej"};
  TTreeReaderValue<Int_t> index_j{reader, "index_j"};
  TTreeReaderValue<Double_t> T_Diff_Corrected{reader, branchname};

  double T; 
  double E;
  
  while (reader.Next()) {
    const  auto Index_i = *index_i;
    const  auto EI = *Ei;
    const  auto EJ = *Ej;
    const  auto Index_j = *index_j;
    const  auto TDiff = *T_Diff_Corrected;
    if(EJ>=minbine && EJ<=maxbine &&TDiff>=minbin &&TDiff<=maxbin){
      A7A->Fill(TDiff,EJ);
      Zobry->Fill(TDiff);
      for(int i=0; i<15; i++){
	for(int j=0; j<15; j++){
	  if(Index_i==i && Index_j==j && i!=j){
	   
	    hist[i][j]->Fill(TDiff,EJ);
	    Zibby[i][j]->Fill(TDiff);
	  }
	  // if(Index_i==j && Index_j==i){
	  //   hist[i][j]->Fill(TDiff,EJ);
	  //   Zibby[i][j]->Fill(TDiff);
	  // }

	}
      }
    }

  }
  





}



void Centroid_Extraction(){

  TFile* input=new TFile("./output_Co_calibration_e21062-b_run1281.root","READ");
  // TFile* input1=new TFile("/data/e16032/tg1250/ML_From_HPCC/Co_2004_Calibration_Comparison.root","READ");

 
  double x[16];
  double xe[16];
  double y[16];
  double ye[16];
  double y1[16];
  double ye1[16];
  TCanvas* canvas = new TCanvas("canvas", "4x4 Histograms", 800, 800);
    canvas->Divide(4, 4); // Divide into 4x4 pads
  for(int i=0; i<16; i++){
    canvas->cd(i+1);
    TH1D* hist=(TH1D*)input->Get(Form("/raw_individual/tdynode_%d",i));
    TH1D* hist1 = (TH1D*)hist->Rebin(10, "histRebinned");
    TH1D* hist10 = (TH1D*)hist->Rebin(2, "histRebinned_10");
    Int_t binNumber = hist1->GetMaximumBin(); // Get the bin number with the maximum content
    Double_t binmax = hist1->GetXaxis()->GetBinCenter(binNumber);
    TF1* funcx=new TF1("funcx","gaus",binmax-10,binmax+10);
    TF1* funcx1=new TF1("funcx1","gaus",binmax-10,binmax+10);
    funcx1->SetLineColor(kRed);
    hist10->Fit("funcx","RMELI");
    x[i]=i;
    xe[i]=0;
    y[i]=funcx->GetParameter(1);
    ye[i]=funcx->GetParError(1);
    hist10->Fit("funcx1","RMELI");
    y1[i]=funcx->GetParameter(2);
    ye1[i]=funcx->GetParError(2);
    hist10->GetXaxis()->SetRangeUser(binmax-15,binmax+15);
    hist10->Draw();
    
    delete funcx;
    delete funcx1;
  }
 // canvas->SaveAs("Co_pre_Calibration.png");
  
  for(int i=0; i<16; i++){
    
    std::cout<<y[i]<<", "; 
  }

  // canvas->cd(16);
  // TH1D* hist_tdynode_full=(TH1D*)input1->Get("tdynode_full");
  // TF1*




  TCanvas* graphCanvas = new TCanvas("graphCanvas", "Fit Parameters", 600, 600);
 
  TGraphErrors* graph=new TGraphErrors(16,x,y,xe,ye);
 graph->SetMarkerStyle(20);
 graph->SetMarkerSize(0.7);
 graph->Draw("AP");


 TCanvas* graphCanvas1 = new TCanvas("graphCanvas1", "Fit Parameters1", 600, 600);
 TGraphErrors* graph1=new TGraphErrors(16,x,y1,xe,ye1);
 graph1->SetMarkerStyle(20);
 graph1->SetMarkerSize(0.7);
 graph1->Draw("AP");

}
