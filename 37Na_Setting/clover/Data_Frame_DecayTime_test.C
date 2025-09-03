

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
#include <chrono>
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



void Data_Frame_DecayTime_test(){
  // gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/include/");
  // gInterpreter->AddIncludePath("/user/gaballah/ddasfitclasses/");
  // gSystem->Load("/user/gaballah/ddasfitclasses/libDDASFitClasses.so");
  //  gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/libTParameters.so");
  ROOT::EnableImplicitMT(4);
  ROOT::RDataFrame df("data", "/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resortedNewCal37Na/run*.root",{"corr.flag","corr.isdecay","corr.isimplant","corr.dxpos", "corr.dypos", "corr.dtime", "implantlist"});
  //   std::cout<<"done"<<'\n';
  auto df_filtered=df;
  //   auto df_filtered2=df.Filter("corr.flag==32 && corr.isdecay==1");
   int totalEntries = df_filtered.Count().GetValue();
   auto startTime = std::chrono::steady_clock::now();
  // // auto decayTimes = df_filtered.Take<double>("corr.dtime").GetValue();
  // // auto implantTimes = df_filtered.Take<double>("implantlist.time").GetValue();
  //  auto tof = df_filtered.Take<double>("implantlist[0].tof").GetValue();
  //  auto de2 = df_filtered.Take<double>("implantlist[0].de2").GetValue();
  //  double HL[6]={1,1.8,5,8.1,13.2,17.4};
 
  //  TCutG* iongates[4][8];
  //  TH2D* h2CloverNaAll[4][8];
  //  TH1D*  hIonDecayTime[4][8];
  // TFile* blobs=new TFile("./../iongates.root","Read");
  //   for ( int i:{7,5,4,3,2,1}){
  //     iongates[3][i]=(TCutG*)blobs->Get(Form("iongates_3%dNa",i));
  //     hIonDecayTime[3][i]=new TH1D(Form("hIonDecayTime_^{3%d}Na",i),Form("hIonDecayTime_^{3%d}Na",i),1000,0,100);
  
  //  }
  // TH2D* PID_Implant=new TH2D("PID_Implant","PID_Implant",500,-1000,-950,1400,0,1400);
  // TH2D* PID_Decay=new TH2D("PID_Decay","PID_Decay",500,-1000,-950,1400,0,1400);
  //  auto histo1=df_filtered.Histo2D({"PID_Decay","PID_Decay",500,-1000,-950,1400,0,1400},"corr.dtof","corr.dde2");
  // auto histo=df_filtered.Histo2D({"PID_Implant","PID_Implant",500,-1000,-950,1400,0,1400},"corr.itof","corr.ide2");
   auto df_filtered1=df.Filter({"corr.isdecay==1"});
   auto histo1=df_filtered1.Histo2D({"PID_Decay_implantlist","PID_Decay_implantlist",500,-1000,-950,1400,0,1400},"implsntlist[0].tof","implantlist[0].de2");
  
  auto histo=df_filtered.Histo2D({"PID_Implant_implantlist","PID_Implant_implantlist",500,-1000,-950,1400,0,1400},"implantlist[0].tof","implantlist[0].de2");

//   int processed=0;

//    // // Progress reporting
//     // Adjust this based on how often you want to report
//    //  df_filtered.OnPartialResult(reportFrequency, [&totalEntries](const ROOT::RDF::RResultPtr<TH2D>& /*result*/) {
//    //      static size_t calls = 0;
//    //      calls++;
//    //      std::cout << "Processed " << calls * reportFrequency << " entries (approx.)" << std::endl;
//    //  });
//   int reportFrequency = 100000;
// auto reportProgress = [&processed, reportFrequency, totalEntries](unsigned int /*slot*/, ULong64_t /*entry*/) {
//         processed += reportFrequency;
//         if (processed % reportFrequency == 0 || processed >= totalEntries) {
//             std::cout << "Processed " << processed << " entries (approx.)" << std::endl;
//         }
//     };

//     // Apply the reporting during event processing
//     df_filtered.Foreach(reportProgress, {"entry"});

  
  // histo->Draw("colz");
  //   PID_Implant->Fill(tof,de2);


  // auto PID_Implant = df.Filter("implantlist.size() > 0 && corr.flag == 32 && corr.isdecay == 1")
  //                     .Histo2D({"PID_Implant", "PID of Implants", 500, -1000, -950, 1400, 0, 1400},
  //                              "implantlist.de2", "implantlist[0].tof");
  // int processed = 0;
  // std::atomic<int> processed(0);

  // auto processEntry = [&] ( int corr_flag, int corr_isdecay, int corr_isimplant,
  // 			    double corr_dxpos_x, double corr_dypos_y,
  // 			    double corr_dtime, ROOT::VecOps::RVec<TPID> implants) {
  // 		        printProgressBar(++processed, totalEntries,startTime);
  // 			//	std::cout<<implants.size()<<"     "<<pspmthigh2_dytime.size()<<'\n';
  // 			//	 if(corr_flag==32 && corr_isdecay==1 ){
  // 			int counter=0; 
  // 			for (const auto& implant : implants) {
  // 			  if(counter>=1)
  // 			    break;
  // 			  double tof1 =implant.tof;
  // 			  double DE2=implant.de2;
  // 			  PID_Implant->Fill(tof1, DE2);
  // 			  if(corr_isdecay==1 ){
  // 			    PID_Decay->Fill(tof1, DE2);
			      
  // 			  }
  // 			  // double dx = corr_dxpos_x - implant.xpos;
  // 			  // double dy = corr_dypos_y - implant.ypos;
  // 			  // double Radius = TMath::Sqrt(dx * dx + dy * dy);
  // 			  // double dtimecal = corr_dtime - implant.time;
                
  // 			  // for (int i : {7,5,4,3,2,1}) {
  // 			  //   if (iongates[3][i]->IsInside(tof1, DE2)) {
  // 			  // 	hIonDecayTime[3][i]->Fill(dtimecal);
  // 			  //   }
  // 			  // }
  // 			  counter++;
  // 			}
  // 			//	}
  // 		      };

		      
  // df_filtered.Foreach(processEntry,{"corr.flag","corr.isdecay","corr.isimplant","corr.dxpos", "corr.dypos",
  // 				    "corr.dtime", "implantlist"});

  TFile *outroot = new TFile("./PID_Implant_Decay_implantlist[0]_resortedNewCal37Na.root","RECREATE");
 


  // //  for ( int i:{7,5,4,3,2,1}){
  // //    outroot->mkdir(Form("3%dNa",i));
  // //    outroot->cd(Form("3%dNa",i));
  // //    hIonDecayTime[3][i]->Write();
  // //    iongates[3][i]->Write();
  
  // //  }
  // //  outroot->Close();
  histo->Write();
  histo1->Write();
  // PID_Decay->Write();
  // PID_Implant->Write();
 
}
