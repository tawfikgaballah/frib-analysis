#define Myselector_cxx
// The class definition in Myselector.h has been generated automatically
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
// root> T->Process("Myselector.C")
// root> T->Process("Myselector.C","some options")
// root> T->Process("Myselector.C+")
//


#include "e21062_selector_basic_amelia.h"
#include <TH2.h>
#include <TStyle.h>

void e21062_selector_basic_amelia::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void e21062_selector_basic_amelia::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).



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



  
   TString option = GetOption();

}

Bool_t e21062_selector_basic_amelia::Process(Long64_t entry)
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






 bool isGoodCorr = (*corr_isdecay==1);
  for (auto implant:*implantlist){
    double TOF=implant.tof;
    double DE2=implant.de2;
    double ixpos=implant.xpos;
    double iypos=implant.ypos;
    double itime= implant.time;
    double dtimecal=*corr_dtime-itime;
    if(sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2))<=3){
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

void e21062_selector_basic_amelia::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void e21062_selector_basic_amelia::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
TFile* fOutputFile=new TFile("./Amelia_files_33_37_Na_Decay_Time.root","RECREATE");
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
