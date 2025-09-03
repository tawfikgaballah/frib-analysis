#define e21062_selector_basic_cxx
// The class definition in e21062_selector_basic.h has been generated automatically
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
// root> T->Process("e21062_selector_basic.C")
// root> T->Process("e21062_selector_basic.C","some options")
// root> T->Process("e21062_selector_basic.C+")
//


#include "e21062_selector_basic.h"
#include <TH2.h>
#include <TStyle.h>

void e21062_selector_basic::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void e21062_selector_basic::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   // PID_Implant=new TH2D("PID_Implant","PID_Implant",1000,-1000,-900,1400,0,1400);
   // PID_Implant->GetXaxis()->SetTitle("tof");
   // PID_Implant->GetYaxis()->SetTitle("de2");
   // GetOutputList()->Add(PID_Implant);

   // PID_Decay=new TH2D("PID_Decay","PID_Decay",1000,-1000,-900,1400,0,1400);
   // PID_Decay->GetXaxis()->SetTitle("tof");
   // PID_Decay->GetYaxis()->SetTitle("de2");
   // GetOutputList()->Add(PID_Decay);


   
   // PID_Implant_Forward=new TH2D("PID_Implant_Forward","PID_Implant_Forward",1000,-1000,-900,1400,0,1400);
   // PID_Implant_Forward->GetXaxis()->SetTitle("tof");
   // PID_Implant_Forward->GetYaxis()->SetTitle("de2");
   // GetOutputList()->Add(PID_Implant_Forward);

   // PID_Decay_Forward=new TH2D("PID_Decay_Forward","PID_Decay_Forward",1000,-1000,-900,1400,0,1400);
   // PID_Decay_Forward->GetXaxis()->SetTitle("tof");
   // PID_Decay_Forward->GetYaxis()->SetTitle("de2");
   // GetOutputList()->Add(PID_Decay_Forward);



   // PID_Implant_Reverse=new TH2D("PID_Implant_Reverse","PID_Implant_Reverse",1000,-1000,-900,1400,0,1400);
   // PID_Implant_Reverse->GetXaxis()->SetTitle("tof");
   // PID_Implant_Reverse->GetYaxis()->SetTitle("de2");
   // GetOutputList()->Add(PID_Implant_Reverse);

   // PID_Decay_Reverse=new TH2D("PID_Decay_Reverse","PID_Decay_Reverse",1000,-1000,-900,1400,0,1400);
   // PID_Decay_Reverse->GetXaxis()->SetTitle("tof");
   // PID_Decay_Reverse->GetYaxis()->SetTitle("de2");
   // GetOutputList()->Add(PID_Decay_Reverse);





    for (const auto& entry : nuclei) {
     int i = std::get<0>(entry.first);
     int j = std::get<1>(entry.first);
     std::string nucl = std::get<2>(entry.first);
     const char* nucl_name = entry.second.c_str();
     // File operations and object manipulations
     if (blobs->IsOpen()) {
       iongates[entry.first] = (TCutG*)blobs->Get(Form("%d%d%s_Decay", i, j, nucl.c_str()));
       if (iongates[entry.first]) {
	 GetOutputList()->Add(iongates[entry.first]);
	 // h2CloverNaAll[entry.first]=new TH2D(Form("DecayTime_Vs_Clover_^{%d%d}%s",i,j,nucl.c_str()),
	 // 				     Form("Total Clover Spectrum, gated on #beta-decays of ^{%d%d}%s",i,j,nucl.c_str()),
	 // 				     4500, 0, 4500,300,0,100);
	 // GetOutputList()->Add(h2CloverNaAll[entry.first]);
	 hIonDecayTime[entry.first]=new TH1D(Form("hIonDecayTime_^{%d%d}%s",i,j,nucl.c_str()),Form("hIonDecayTime_^{%d%d}%s",i,j,nucl.c_str()),2000,-100,100);
	 GetOutputList()->Add(hIonDecayTime[entry.first]);
       }
     }
   }


   
}

Bool_t e21062_selector_basic::Process(Long64_t entry)
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
  // PID_Implant->Fill(*corr_itof, *corr_ide2);
  // if(*corr_isforward==1){
  //   PID_Implant_Forward->Fill(*corr_itof,*corr_ide2);
  // }
  // else if (*corr_isreverse==1){
  //   PID_Implant_Reverse->Fill(*corr_itof, *corr_ide2);
  // };
  bool isGoodCorr = (*corr_isdecay==1);
  for (auto implant:*implantlist){
    double TOF=implant.tof;
    double DE2=implant.de2;
    double ixpos=implant.xpos;
    double iypos=implant.ypos;
    double itime= implant.time;
    double dtimecal=*corr_dtime-itime;
    if(sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2))<=6){
      // PID_Decay->Fill(TOF, DE2);
      for (const auto& entry : nuclei) {
  	int i = std::get<0>(entry.first);
  	int j = std::get<1>(entry.first);
  	std::string nucl = std::get<2>(entry.first);
  	const char* nucl_name = entry.second.c_str();
  	if (iongates[entry.first]->IsInside(TOF, DE2) && isGoodCorr) {
  	  hIonDecayTime[entry.first]->Fill(dtimecal);
  	}
      }

      // if(*corr_isforward==1){
      // 	PID_Decay_Forward->Fill(TOF, DE2);}
      // else if (*corr_isreverse==1){
      // 	PID_Decay_Reverse->Fill(TOF, DE2);
      // }
    }
  }






  
  return kTRUE;
}

void e21062_selector_basic::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void e21062_selector_basic::Terminate()
{
  
  TFile* fOutputFile=new TFile("./Amelia_files_33_37_Na_Decay_Time_1.root","RECREATE");
  // fOutput->FindObject("PID_Implant")->Write();
  // fOutput->FindObject("PID_Decay")->Write();

  //   fOutput->FindObject("PID_Implant_Forward")->Write();
  // fOutput->FindObject("PID_Decay_Forward")->Write();

    // fOutput->FindObject("PID_Implant_Reverse")->Write();
  // fOutput->FindObject("PID_Decay_Reverse")->Write();



for (const auto& entry : nuclei) {
   int i = std::get<0>(entry.first);
   int j = std::get<1>(entry.first);
   std::string nucl = std::get<2>(entry.first);
   const char* nucl_name = entry.second.c_str();
   // fOutputFile->mkdir(Form("3%dNa",i));
   // fOutputFile->cd(Form("3%dNa",i));
   //  fOutput->FindObject(Form("iongates_3%dNa",i));
   // // fOutput->FindObject(Form("I3%dNa.",i));
   // // fOutput->FindObject(Form("DecayTime_Vs_Clover_^{3%d}Na",i));
   
   // fOutput->FindObject(Form("hIonDecayTime_^{3%d}Na",i));
   // fOutput->FindObject(Form("Clover_^{3%d}Na_Vs_Time",i));

   fOutputFile->mkdir(Form("%d%d%s",i,j,nucl.c_str()));
   fOutputFile->cd(Form("%d%d%s",i,j,nucl.c_str()));
   // fOutput->FindObject(Form("iongates_3%dNe",i));
  /*  fOutput->FindObject(Form("DecayTime_Vs_Clover_^{%d%d}%s",i,j,nucl.c_str())); */
     MakeOutput(Form("hIonDecayTime_^{%d%d}%s",i,j,nucl.c_str()));
   // fOutputFile->cd();
   // hIonDecayTime[entry.first]->Write();
 }
  // MakeOutput("hIonDecayTime_^{37}Na");
   fOutputFile->Close();
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
