#include <ROOT/RDataFrame.hxx>
#include <TMath.h>
#include <iostream>
#include <vector>
#include <algorithm>  // Include for std::find
#include <iomanip>
#include <atomic>
#include <mutex>
#include <TCutG.h>
// #include "/user/e21062/Analysis/ddasfitclasses/DDASRootFitHit.h"
// #include "/user/e21062/Analysis/ddasfitclasses/DDASFitHit.h"
#include "/projects/e21062/Offline-Analysis/rootAnalysis/include/TPID.h"
// #include "/projects/e21062/Offline-Analysis/rootAnalysis/Constants.h"
#include "/projects/e21062/tg/rootAnalysis/include/TPSPMTUTK.h"
std::mutex output_mutex;

void printProgressBar(int completed, int total, std::chrono::steady_clock::time_point startTime) {
    using namespace std::chrono;
    std::lock_guard<std::mutex> lock(output_mutex); // Lock for safe output

    float progress = float(completed) / total;
    int barWidth = 70;
    
    auto now = steady_clock::now();
    auto time_elapsed = duration_cast<seconds>(now - startTime).count();
    int time_remaining = (progress > 0.01) ? (int)(time_elapsed / progress) - time_elapsed : 0;

    std::cout << "\r";  // Clear the current line
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " % ";
    std::cout << "Elapsed: " << time_elapsed << "s ";
    if (progress > 0.01) {
        std::cout << "Remaining: " << time_remaining << "s";
    }
    std::cout.flush();  // Flush to make sure output is written immediately
}





struct TDY {
  double dytime;
  double dyenergy;
  int dycfdfailbit;
};

// struct TPID {
//     double xpos;
//     double ypos;
//     double tof;
//     double de2;
//     double time;
// };



void Data_Frame_DecayTime(){
 // gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/include/");
 // gInterpreter->AddIncludePath("/user/gaballah/ddasfitclasses/");
 // gSystem->Load("/user/gaballah/ddasfitclasses/libDDASFitClasses.so");
 //  gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/libTParameters.so");
  ROOT::EnableImplicitMT(4);
  ROOT::RDataFrame df("data", "/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/CorrSorted37Na-Reverse-Win3/run*.root",{"corr.flag","corr.isdecay","corr.isimplant","corr.dxpos", "corr.dypos", "corr.dtime", "implantlist"});
  auto df_filtered=df.Filter("corr.flag==32");
 int totalEntries = df_filtered.Count().GetValue();
 auto startTime = std::chrono::steady_clock::now();

 double HL[6]={1,1.8,5,8.1,13.2,17.4};
 
 TCutG* iongates[4][8];
 TH2D* h2CloverNaAll[4][8];
 TH1D*  hIonDecayTime[4][8];
TFile* blobs=new TFile("./../iongates.root","Read");
  for ( int i:{7,5,4,3,2,1}){
    if(i==7){
      iongates[3][i]=new TCutG(Form("iongates_3%dNa",i),9);
  
   iongates[3][i]->SetVarX("implantlist[0].tof");
   iongates[3][i]->SetVarY("implantlist[0].de2");
   iongates[3][i]->SetTitle(Form("iongates_3%dNa",i));
   iongates[3][i]->SetFillStyle(1000);
   iongates[3][i]->SetPoint(0,-957.306,770.85);
   iongates[3][i]->SetPoint(1,-956.459,728.34);
   iongates[3][i]->SetPoint(2,-957.045,696.457);
   iongates[3][i]->SetPoint(3,-957.86,691.144);
   iongates[3][i]->SetPoint(4,-958.088,714.17);
   iongates[3][i]->SetPoint(5,-958.12,744.281);
   iongates[3][i]->SetPoint(6,-957.632,769.079);
   iongates[3][i]->SetPoint(7,-957.143,767.308);
   iongates[3][i]->SetPoint(8,-957.306,770.85);
    }
    else{
    iongates[3][i]=(TCutG*)blobs->Get(Form("iongates_3%dNa",i));
    }
    hIonDecayTime[3][i]=new TH1D(Form("hIonDecayTime_^{3%d}Na",i),Form("hIonDecayTime_^{3%d}Na",i),1000,0,100);
  
 }
  // int processed = 0;
  std::atomic<int> processed(0);

  auto processEntry = [&] ( int corr_flag, int corr_isdecay, int corr_isimplant,
			    double corr_dxpos_x, double corr_dypos_y,
			    double corr_dtime, ROOT::VecOps::RVec<TPID> implants) {
		        printProgressBar(++processed, totalEntries,startTime);
			//	std::cout<<implants.size()<<"     "<<pspmthigh2_dytime.size()<<'\n';
			if(corr_flag==32 && corr_isdecay==1 ){
			  for (const auto& implant : implants) {
			    double tof1 =implant.tof;
			    double DE2=implant.de2;
			    // double dx = corr_dxpos_x - implant.xpos;
			    // double dy = corr_dypos_y - implant.ypos;
			    // double Radius = TMath::Sqrt(dx * dx + dy * dy);
			    double dtimecal = corr_dtime - implant.time;
                
			    for (int i : {7}) {
			      if (iongates[3][i]->IsInside(tof1, DE2)) {
				hIonDecayTime[3][i]->Fill(-dtimecal);
			      }
			    }
			  }
			}
		      };

		      
 df_filtered.Foreach(processEntry,{"corr.flag","corr.isdecay","corr.isimplant","corr.dxpos", "corr.dypos",
				   "corr.dtime", "implantlist"});

TFile *outroot = new TFile("./Decay_Curve_37Na_3mm_Reverse.root","RECREATE");
 


 for ( int i:{7}){
   outroot->mkdir(Form("3%dNa",i));
   outroot->cd(Form("3%dNa",i));
   hIonDecayTime[3][i]->Write();
   iongates[3][i]->Write();
  
 }
 outroot->Close();


 
}
