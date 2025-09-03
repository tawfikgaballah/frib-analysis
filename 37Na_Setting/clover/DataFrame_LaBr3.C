#include <ROOT/RDataFrame.hxx>
#include <TMath.h>
#include <iostream>
#include <vector>
#include <algorithm>  // Include for std::find
#include <iomanip>
#include <atomic>
#include <mutex>
#include "/projects/e21062/Offline-Analysis/rootAnalysis/include/TPID.h"
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






// struct TPID {
//     double xpos;
//     double ypos;
//     double tof;
//     double de2;
//     double time;
// };



void DataFrame_LaBr3(){
  
  ROOT::EnableImplicitMT(4);
  ROOT::RDataFrame df("data", "/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/CorrSorted37Na-Win3/*.root",{"corr.flag","corr.isdecay","corr.isimplant","corr.dxpos", "corr.dypos",
                          "labr.energy[16]", "labr.time[16]", "labr.cfdfailbit[16]",
				       "corr.dtime", "implantlist"});
  auto df_filtered=df.Filter("corr.flag==32 && corr.isdecay==1");
  
 int totalEntries = df_filtered.Count().GetValue();
 auto startTime = std::chrono::steady_clock::now();


 
 TCutG* iongates[4][8];
 TH2D* h2LaBr3NaAll[16];
 TH2D* h2LaBr3NaAll_implant[4][8];
TFile* blobs=new TFile("./../iongates.root","Read");
 for (int j=0; j<16; j++){
    h2LaBr3NaAll[j]=new TH2D(Form("DecayTime_Vs_LaBr3_33Na_%d",j),
 				 Form("Total LaBr3 Spectrum, gated on #beta-decays of ^{33}Na_%d",j),
 			     4500, 0, 45000,300,0,100);
 }
  for ( int i:{7,5,4,3,2,1}){
    iongates[3][i]=(TCutG*)blobs->Get(Form("iongates_3%dNa",i));
 



   h2LaBr3NaAll_implant[3][i]=new TH2D(Form("LaBr3_3%dNa_Vs_Time",i),
 				 Form("Total LaBr3 Spectrum_Vs_Time_Since_Last_Implant_gated_on_#beta-decays of ^{3%d}Na",i),
 					2000,-50,150,4500,0,45000);
  
 }
  // int processed = 0;
  std::atomic<int> processed(0);

  auto processEntry = [&] ( int corr_flag, int corr_isdecay, int corr_isimplant,
			    double corr_dxpos_x, double corr_dypos_y,
			    ROOT::VecOps::RVec<double>& LaBr3_ecal, 
			    ROOT::VecOps::RVec<double>& LaBr3_timecal, 
			    ROOT::VecOps::RVec<int>& LaBr3_cfdfailbit, 
			    double corr_dtime, ROOT::VecOps::RVec<TPID> implants) {
			static const std::vector<int> badChannels = {26, 24, 25, 27, 45, 46, 19, 20};
			printProgressBar(++processed, totalEntries,startTime); 
			for (const auto& implant : implants) {
			  double tof1 =implant.tof;
			  double DE2=implant.de2;
			  double dx = corr_dxpos_x - implant.xpos;
			  double dy = corr_dypos_y - implant.ypos;
			  double Radius = TMath::Sqrt(dx * dx + dy * dy);
			  double dtimecal = corr_dtime - implant.time;

			  for (size_t s = 0; s < LaBr3_ecal.size(); ++s) {
			    if (LaBr3_ecal[s] > 100 && LaBr3_timecal[s] > 100 &&
				LaBr3_cfdfailbit[s] != 1 && std::find(badChannels.begin(), badChannels.end(), s) == badChannels.end()) {
                
			      for (int i : {3}) {
				if (iongates[3][i]->IsInside(tof1, DE2)) {
				  // std::cout<<"True:"<<i<<'\n';
				  //   if (dx >= -1 && dx <= 2 && dy >= -1 && dy <= 2) {
				     if (corr_flag==32 && corr_isdecay==1){
				      h2LaBr3NaAll[s]->Fill(LaBr3_ecal[s],dtimecal);
				     }
   		 
				    //  }
				  // if (corr_flag==32){
				    // h2LaBr3NaAll_implant[3][i]->Fill(LaBr3_timecal[s]/1e03-implant.time*1e03,LaBr3_ecal[s]);
				    //}
				}
			      }
			    }
			  }
			}
		      };

 df_filtered.Foreach(processEntry,{"corr.flag","corr.isdecay","corr.isimplant","corr.dxpos", "corr.dypos",
                          "labr.energy[16]", "labr.time[16]", "labr.cfdfailbit[16]",
				       "corr.dtime", "implantlist"});

TFile *outroot = new TFile("./LaBr3_Spectra_Data_Frame.root","RECREATE");
 
 for(int i=0; i<16; i++){
   h2LaBr3NaAll[i]->Write();
 }

 // for ( int i:{7,5,4,3,2,1}){
 //   outroot->mkdir(Form("3%dNa",i));
 //   outroot->cd(Form("3%dNa",i));
 //   // h2CloverNaAll_implant[3][i]->Write();
 //   h2LaBr3NaAll[3][i]->Write();
 //   iongates[3][i]->Write();
  
 // }
 outroot->Close();


 
}
