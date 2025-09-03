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



void DataFrame_Clover(){
 // gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/include/");
 // gInterpreter->AddIncludePath("/user/gaballah/ddasfitclasses/");
 // gSystem->Load("/user/gaballah/ddasfitclasses/libDDASFitClasses.so");
 //  gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/libTParameters.so");
  ROOT::EnableImplicitMT(4);
  ROOT::RDataFrame df("data", "/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/CorrSorted37Na-Win7/run*.root",{"corr.flag","corr.isdecay","corr.isimplant","corr.dxpos", "corr.dypos",
                          "clover.ecal[52]", "clover.timecal[52]", "clover.cfdfailbit[52]",
																       "corr.dtime", "implantlist","pspmthigh2.dytime","pspmthigh2.dyenergy","pspmthigh2.dycfdfailbit"});
  auto df_filtered=df.Filter("corr.flag==32");
 int totalEntries = df_filtered.Count().GetValue();
 auto startTime = std::chrono::steady_clock::now();

 double HL[6]={1,1.8,5,8.1,13.2,17.4};
 
 TCutG* iongates[4][8];
 TH2D* h2CloverNaAll[4][8];
 TH2D* h2CloverNaAll_implant[4][8];
TFile* blobs=new TFile("./../iongates.root","Read");
  for ( int i:{7,5,4,3,2,1}){
    iongates[3][i]=(TCutG*)blobs->Get(Form("iongates_3%dNa",i));
 

    h2CloverNaAll[3][i]=new TH2D(Form("DecayTime_Vs_Clover_3%dNa",i),
 				 Form("Total Clover Spectrum, gated on #beta-decays of ^{3%d}Na",i),
 			     4500, 0, 4500,300,0,100);


   h2CloverNaAll_implant[3][i]=new TH2D(Form("Clover_3%dNa_Vs_Time",i),
 				 Form("Total Clover Spectrum_Vs_Time_Since_Last_Implant_gated_on_#beta-decays of ^{3%d}Na",i),
 					2000,-500,1500,4500,0,4500);
  
 }
  // int processed = 0;
  std::atomic<int> processed(0);

  auto processEntry = [&] ( int corr_flag, int corr_isdecay, int corr_isimplant,
			    double corr_dxpos_x, double corr_dypos_y,
			    ROOT::VecOps::RVec<double>& clover_ecal, 
			    ROOT::VecOps::RVec<double>& clover_timecal, 
			    ROOT::VecOps::RVec<int>& clover_cfdfailbit, 
			    double corr_dtime, ROOT::VecOps::RVec<TPID> implants,  ROOT::VecOps::RVec<double> &pspmthigh2_dytime, ROOT::VecOps::RVec<double> &pspmthigh2_dyenergy, int pspmthigh2_dycfdfailbit) {
			// if (pspmthigh2_dytime.size()>0){
			//   auto dyTime=pspmthigh2_dytime[0];
			//   std::cout<<dyTime<<'\n';
			// }
			// // std::cout<<dyTime<<'\n';
			static const std::vector<int> badChannels = {26, 24, 25, 27, 45, 46, 19, 20};
		        printProgressBar(++processed, totalEntries,startTime);
			//	std::cout<<implants.size()<<"     "<<pspmthigh2_dytime.size()<<'\n';
			if(pspmthigh2_dytime.size()>0 && corr_flag==32 && corr_isdecay==1 ){
			  for (const auto& implant : implants) {
			    if(pspmthigh2_dytime[0]>100 && pspmthigh2_dyenergy[0]>100 && pspmthigh2_dycfdfailbit!=1){
			      double tof1 =implant.tof;
			      double DE2=implant.de2;
			      // double dx = corr_dxpos_x - implant.xpos;
			      // double dy = corr_dypos_y - implant.ypos;
			      // double Radius = TMath::Sqrt(dx * dx + dy * dy);
			      double dtimecal = corr_dtime - implant.time;

			      for (size_t s = 0; s < clover_ecal.size(); ++s) {
			      	if (clover_ecal[s] > 10 && clover_timecal[s] > 10 &&
			      	    clover_cfdfailbit[s] != 1 && std::find(badChannels.begin(), badChannels.end(), s) == badChannels.end()) {
                
			      	  for (int i : {7,5,4,3,2,1}) {
			      	    if (iongates[3][i]->IsInside(tof1, DE2)) {
			      	      // std::cout<<"True:"<<i<<'\n';
			      	      //   if (dx >= -1 && dx <= 2 && dy >= -1 && dy <= 2) {
			      	      // if (corr_isdecay==1){
			      	      //   h2CloverNaAll[3][i]->Fill(clover_ecal[s],dtimecal);
			      	      // }
   		 
			      	      //  }
				      if (dtimecal<=3*HL[i]){
					 
					h2CloverNaAll_implant[3][i]->Fill(pspmthigh2_dytime[0]-clover_timecal[s],clover_ecal[s]);
			      	      }
			      	    }
			      	  }
			      	}
			      }
			    }
			  
			  }
			}
	        
		      };
		      
 df_filtered.Foreach(processEntry,{"corr.flag","corr.isdecay","corr.isimplant","corr.dxpos", "corr.dypos",
                          "clover.ecal[52]", "clover.timecal[52]", "clover.cfdfailbit[52]",
				   "corr.dtime", "implantlist","pspmthigh2.dytime","pspmthigh2.dyenergy","pspmthigh2.dycfdfailbit"});

TFile *outroot = new TFile("./Clover_Spectra_Data_Frame_Time_Since_Last_Implant_pspmthigh2_7mm.root","RECREATE");
 


 for ( int i:{7,5,4,3,2,1}){
   outroot->mkdir(Form("3%dNa",i));
   outroot->cd(Form("3%dNa",i));
   h2CloverNaAll_implant[3][i]->Write();
   // h2CloverNaAll[3][i]->Write();
   iongates[3][i]->Write();
  
 }
 outroot->Close();


 
}
