#define Selector_60Co_cxx
// The class definition in Selector_60Co.h has been generated automatically
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
// root> T->Process("Selector_60Co.C")
// root> T->Process("Selector_60Co.C","some options")
// root> T->Process("Selector_60Co.C+")
//

#include "Selector_60Co.h"
#include <TH2.h>
#include <TStyle.h>


const int tbins=2000; 
const int t_min=-100;
const int t_max=100;

const int ebins=70; 
const int e_min=0;
const int e_max=1400; 

const int dbins=1000; 
const int d_min=0;
const int d_max=10000;  
void Selector_60Co::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_60Co::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).


  Detector_Vs_TDynode_Offset=new TH2D("Detector_Vs_TDynode_Offset","Detector_Vs_TDynode_offset",tbins,t_min,t_max,15,0,15);
  LaBr3E_Vs_tdynode_offset=new TH2D("LaBr3E_Vs_tdynode_offset","LaBr3E_Vs_tdynode_offset",tbins,t_min,t_max,ebins, e_min, e_max);
  LaBr3_TDiff=new TH1D("LaBr3_TDiff","LaBr3_TDiff",tbins,t_min,t_max);
  TDynode_Offset=new TH1D("TDynode_Offset","TDynode_Offset",tbins,t_min,t_max);
  LaBr3E_Vs_TDiff=new TH2D("LaBr3E_Vs_TDiff","LaBr3E_Vs_TDiff",tbins,t_min,t_max,ebins, e_min, e_max);

  GetOutputList()->Add(LaBr3_TDiff);
  GetOutputList()->Add(TDynode_Offset);
  GetOutputList()->Add(Detector_Vs_TDynode_Offset);
  GetOutputList()->Add(LaBr3E_Vs_tdynode_offset);
  GetOutputList()->Add(LaBr3E_Vs_TDiff);


  
  TString option = GetOption();

}

Bool_t Selector_60Co::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_60Co::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

  for(int i=0; i<16; i++){
    if(labr_ecal[i]>0 && labr_timecal[i]>10 && labr_cfdfailbit[i]!=1 &&pspmthigh2_dycfdfailbit!=1 && pspmthigh2_dyenergy>10 && pspmthigh2_dytime>10){
      Double_t TDynode=labr_timecal[i]-pspmthigh2_dytime;
      Detector_Vs_TDynode_Offset->Fill(TDynode,i);
      LaBr3E_Vs_tdynode_offset->Fill(TDynode,labr_ecal[i]);
      TDynode_Offset->Fill(TDynode);
      for(int j=i+1; j<16; j++){
	if(labr_ecal[j]>0 && labr_timecal[j]>10 && labr_cfdfailbit[j]!=1){
	  Double_t TDiff=labr_timecal[i]-labr_timecal[j];
	  LaBr3_TDiff->Fill(TDiff);
	  LaBr3E_Vs_TDiff->Fill(TDiff, labr_ecal[j]);
	}
      }
	  
    }
  }
   return kTRUE;
}

void Selector_60Co::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_60Co::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.




  TFile* fOutputFile=new TFile("./Co_1240.root","RECREATE");

  // OutputObject("tdynode_offset");
  // OutputObject("LaBr3E_Vs_tdynode_offset");
  // OutputObject("DynodeE_Vs_tdynode_offset");
  // OutputObject("tdynode_offset_cut");
  // OutputObject("LaBr3E_Vs_tdynode_offset_cut");
  // OutputObject("DynodeE_Vs_tdynode_offset_cut");

  fOutput->FindObject("Detector_Vs_TDynode_Offset")->Write();
  fOutput->FindObject("LaBr3E_Vs_tdynode_offset")->Write();
  fOutput->FindObject("LaBr3_TDiff")->Write();
  fOutput->FindObject("TDynode_Offset")->Write();
  fOutput->FindObject("LaBr3E_Vs_TDiff")->Write();
  // OutputObject("DynodeE_Vs_tlabr3_offset_cut");




  
}
