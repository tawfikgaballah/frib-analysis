#define clover_cxx
// The class definition in clover.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("clover.C")
// root> T->Process("clover.C","some options")
// root> T->Process("clover.C+")
//


#include "clover.h"
#include <TH2.h>
#include <TStyle.h>
#include <chrono>

void clover::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void clover::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

  
  // PID_Implant = new TH2D("PID_Implant",
  // 		     "PID_Implant",
  // 		     500,-1000,-950,1400,0,1400);
  // GetOutputList()->Add(PID_Implant);

  //  PID_Decay = new TH2D("PID_Decay",
  // 		     "PID_Decay",
  // 		     500,-1000,-950,1400,0,1400);
  // GetOutputList()->Add(PID_Decay);

  // PID_implantlist = new TH2D("PID_implantlist",
  // 		     "PID_implantlist",
  // 		     500,-1000,-950,1400,0,1400);
  // GetOutputList()->Add(PID_implantlist);  TString option = GetOption();


  // h2CloverNaAll_Sum=new TH2D("Clover_Vs_TDiff",
  // 			       "Total Clover Spectrum, gated on #beta-decays_Vs_TDiff",
  // 			     2000,-500,1500,4500, 0, 4500);
  // GetOutputList()->Add(h2CloverNaAll_Sum);
  
  // h2CloverNaAll_1D=new TH1D("Clover",
  // 			       "Total Clover Spectrum, gated on #beta-decays",
  // 			    4500, 0, 4500);
  // GetOutputList()->Add(h2CloverNaAll_1D);



  
  //  for ( int i:{7,5,4,3,2,1,0}){
  //   // iongates[3][i]=(TCutG*)blobs->Get(Form("iongates_3%dNa",i));
  //   // iongates[3][i]=(TCutG*)blobs->Get(Form("iongates_3%dNa",i));
  //   // GetOutputList()->Add(iongates[3][i]);
  //   // hIonDecayTime[3][i]=new TH1D(Form("hIonDecayTime_^{3%d}Na",i),Form("hIonDecayTime_^{3%d}Na",i),1000,0,100);
  //   // GetOutputList()->Add(hIonDecayTime[3][i]);

  //   // h2CloverNaAll[3][i]=new TH2D(Form("DecayTime_Vs_Clover_^{3%d}Na",i),
  //   // 				 Form("Total Clover Spectrum, gated on #beta-decays of ^{3%d}Na",i),
  //   // 				 4500, 0, 4500,300,0,100);
  //   // GetOutputList()->Add(h2CloverNaAll[3][i]);
  //   // h2CloverNaAll_implant[3][i]=new TH2D(Form("Clover_^{3%d}Na_Vs_Time",i),
  //   // 					 Form("Total Clover Spectrum_Vs_Time_Since_Last_Implant_gated_on_#beta-decays of ^{3%d}Na",i),
  //   // 					 2000,-500,1500,4500,0,4500);
  //   // GetOutputList()->Add(h2CloverNaAll_implant[3][i]);
  //   if (i==0 ||i==1){
  //     iongates[3][i]=(TCutG*)blobs->Get(Form("iongates_3%dNe",i));
  //     GetOutputList()->Add(iongates[3][i]);
  //     h2CloverNaAll[3][i]=new TH2D(Form("DecayTime_Vs_Clover_^{3%d}Ne",i),
  // 				   Form("Total Clover Spectrum, gated on #beta-decays of ^{3%d}Ne",i),
  // 				   4500, 0, 4500,300,0,100);
  //     GetOutputList()->Add(h2CloverNaAll[3][i]);
  //   }


  // }

   for (const auto& entry : nuclei) {
     int i = std::get<0>(entry.first);
     int j = std::get<1>(entry.first);
     std::string nucl = std::get<2>(entry.first);
     const char* nucl_name = entry.second.c_str();
     // File operations and object manipulations
     if (blobs->IsOpen()) {
       iongates[entry.first] = (TCutG*)blobs->Get(Form("iongates_%d%d%s", i, j, nucl.c_str()));
       if (iongates[entry.first]) {
	 GetOutputList()->Add(iongates[entry.first]);
	 h2CloverNaAll[entry.first]=new TH2D(Form("DecayTime_Vs_Clover_^{%d%d}%s",i,j,nucl.c_str()),
					     Form("Total Clover Spectrum, gated on #beta-decays of ^{%d%d}%s",i,j,nucl.c_str()),
					     4500, 0, 4500,300,0,100);
	 GetOutputList()->Add(h2CloverNaAll[entry.first]);
	 hIonDecayTime[entry.first]=new TH1D(Form("hIonDecayTime_^{%d%d}%s",i,j,nucl.c_str()),Form("hIonDecayTime_^{%d%d}%s",i,j,nucl.c_str()),1000,0,100);
	 GetOutputList()->Add(hIonDecayTime[entry.first]);
       }
     }
   }



   
}

Bool_t clover::Process(Long64_t entry)
{
 
 
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
    fReader.SetLocalEntry(entry);
    
     Entry+=1;
      std::chrono::time_point<std::chrono::high_resolution_clock>  startTime = std::chrono::high_resolution_clock::now();
    
if (Entry % 1000 == 0 || Entry == totalEntries - 1) {
  double progress = static_cast<double>(Entry) / totalEntries;
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count(); // Time elapsed in seconds
        double estimatedTotalTime = elapsed / progress; // Estimate total time required
        double estimatedTimeLeft = estimatedTotalTime - elapsed; // Time remaining in seconds

        // Format estimated time left as hh:mm:ss
        int hours = static_cast<int>(estimatedTimeLeft / 3600);
        int minutes = static_cast<int>((static_cast<int>(estimatedTimeLeft) % 3600) / 60);
        int seconds = static_cast<int>(static_cast<int>(estimatedTimeLeft) % 60);

        std::cout << "Processing entry " << Entry << " of " << totalEntries << " (" 
                  << std::fixed << std::setprecision(1) << progress * 100 << "%) "
                  << "Time left: " << std::setw(2) << std::setfill('0') << hours << ":"
                  << std::setw(2) << std::setfill('0') << minutes << ":"
                  << std::setw(2) << std::setfill('0') << seconds << "\r";
        std::cout.flush(); // Ensure the output is shown immediately
    }

  
   bool isGoodCorr = (*corr_isdecay==1);
   int counter=0;
 /*   for (auto& implant : *implantlist){ */
    for (auto rit = implantlist->rbegin(); rit != implantlist->rend(); ++rit) {
    auto& implant = *rit;  
    double tof1 = implant.tof;
    if(counter>0)
    break; 
  else{
     double tof1 = implant.tof;
     double DE2 = implant.de2;
     double dtimecal = *corr_dtime - implant.time;
     /* double ixpos = implant.xpos;
     double iypos = implant.ypos;
     double dxpos= *corr_dxpos;
     double dypos= *corr_dypos;
     double RadX= dxpos-ixpos;
     double RadY= dypos-iypos;
     double distance = std::sqrt(std::pow((RadX),2.0) + std::pow((RadY),2.0));  */
   //  if(distance<3){
       for (const auto& entry : nuclei) {
	 int i = std::get<0>(entry.first);
	 int j = std::get<1>(entry.first);
	 std::string nucl = std::get<2>(entry.first);
	 const char* nucl_name = entry.second.c_str();
	 if (iongates[entry.first]->IsInside(tof1, DE2) && isGoodCorr) {
	     hIonDecayTime[entry.first]->Fill(-dtimecal);
	   /* for(int s=0; s<52;s++){
	     if(clover_ecal[s]>10 && clover_timecal[s]>10 &&clover_cfdfailbit[s]!=1 &&(s!=26 && s!=24 &&s!=25 && s!=27 &&s!=45 && s!=46 &&s!=19 &&s!=20)){
	       // for(int s=0; s<13;s++){
	       //   if(clover_ecalab[s]>10 && clover_timecalab[s]>10&&clover_cfdfailbitab[s]!=1){

	       if (isGoodCorr){
		 h2CloverNaAll[entry.first]->Fill(clover_ecal[s],dtimecal);
		 //h2CloverNaAll_Sum->Fill(clover_ecal[s],dtimecal);
	       }
	     	
	     }
	   } */
	 }
       }
     //}
  }
     counter+=1;
   }

 // double tof1 = *corr_itof;
 // double DE2 =*corr_ide2;

 // fo// r ( int i:{7,5,4,3,2}){
 // 	   if (// iongates[3][i]->IsInside(tof1, DE2)&&
 // 	       pspmthigh2_dyecal.GetSize()>0) {
 // 	     if(pspmthigh2_dytime[0]>0 &&pspmthigh2_dyecal[0]>0&&*pspmthigh2_dycfdfailbit!=1){
 // 	       for(int s=0; s<52;s++){
 // 		 if(clover_ecal[s]>10 && clover_timecal[s]>10 &&clover_cfdfailbit[s]!=1 &&(s!=26 && s!=24 &&s!=25 && s!=27 &&s!=45 && s!=46 &&s!=19 &&s!=20)){
 // 		   // for(int s=0; s<13;s++){
 // 		   //   if(clover_ecalab[s]>10 && clover_timecalab[s]>10&&clover_cfdfailbitab[s]!=1){

 // 		   // h2CloverNaAll_implant[3][i]->Fill(clover_timecal[s]-pspmthigh2_dytime[0],clover_ecal[s]);
 // 		   if (isGoodCorr){
 // 		 // h2CloverNaAll[3][i]->Fill(clover_ecal[s],dtimecal);
 // 		     h2CloverNaAll_Sum->Fill(clover_timecal[s]-pspmthigh2_dytime[0],clover_ecal[s]);
 // 		     h2CloverNaAll_1D->Fill(clover_ecal[s]);
 // 		   }
	     	
 // 		 }
 // 	       }
 // 	     }
 // 	   }
 // // }
   
  //  if(*corr_isdecay==1 && *corr_flag==32){
  // PID_Decay->Fill(*corr_dtof,*corr_dde2);
  //  }
  //  if(*corr_isimplant==1){
  // PID_Implant->Fill(*corr_itof,*corr_ide2);
  //  }
   // if(implantlist->size()>2){
   //   std::cout<<implantlist->at(2).tof<<'\n';
   // }
   //  }
   return kTRUE;
}

void clover::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void clover::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
// TFile *outroot = new TFile("./PID_CorrSorted37Na-Win3_noproof.root","RECREATE");
//    fOutput->FindObject("PID_Implant")->Write();
//   fOutput->FindObject("PID_Decay")->Write();
//   fOutput->FindObject("PID_implantlist")->Write();


TFile *outroot = new TFile("./clover-spectra-Win3-30Ne_33Na_Reverse_implantlist[n-1].root","RECREATE");
 // MakeOutput("Clover_Vs_TDiff");
 // MakeOutput("Clover");
 for (const auto& entry : nuclei) {
   int i = std::get<0>(entry.first);
   int j = std::get<1>(entry.first);
   std::string nucl = std::get<2>(entry.first);
   const char* nucl_name = entry.second.c_str();
   // outroot->mkdir(Form("3%dNa",i));
   // outroot->cd(Form("3%dNa",i));
   //  MakeOutput(Form("iongates_3%dNa",i));
   // // MakeOutput(Form("I3%dNa.",i));
   // // MakeOutput(Form("DecayTime_Vs_Clover_^{3%d}Na",i));
   
   // MakeOutput(Form("hIonDecayTime_^{3%d}Na",i));
   // MakeOutput(Form("Clover_^{3%d}Na_Vs_Time",i));

   outroot->mkdir(Form("%d%d%s",i,j,nucl.c_str()));
   outroot->cd(Form("%d%d%s",i,j,nucl.c_str()));
   // MakeOutput(Form("iongates_3%dNe",i));
  /*  MakeOutput(Form("DecayTime_Vs_Clover_^{%d%d}%s",i,j,nucl.c_str())); */
   MakeOutput(Form("hIonDecayTime_^{%d%d}%s",i,j,nucl.c_str()));
  
 }

 outroot->Close();
 delete outroot;
}
