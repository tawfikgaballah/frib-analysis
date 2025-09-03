#define PID_Selector_cxx
// The class definition in PID_Selector.h has been generated automatically
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
// root> T->Process("PID_Selector.C")
// root> T->Process("PID_Selector.C","some options")
// root> T->Process("PID_Selector.C+")
//


#include "PID_Selector.h"
#include <TH2.h>
#include <TStyle.h>

const int tbins=1000; 
const int t_min=-100;
const int t_max=100;

const int ebins=1400; 
const int e_min=0;
const int e_max=1400; 

const int dbins=1400; 
const int d_min=0;
const int d_max=140000;  
void PID_Selector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void PID_Selector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
  PID=new TH2D("PID","PID",400,-1000,-950,1400,0,1400);
  GetOutputList()->Add(PID);


  Labr3_Ecal=new TH1D("Labr3_Ecal","Labr3_Ecal",ebins+2600, e_min, e_max+2600);
  
  Detector_Vs_Labr3_Ecal=new TH2D("Detector_Vs_Labr3_Ecal","Detector_Vs_Labr3_Ecal",ebins, e_min, e_max,16,0,16);
  Detector_Vs_TDynode_Offset=new TH2D("Detector_Vs_TDynode_Offset","Detector_Vs_TDynode_offset",tbins,t_min,t_max,15,0,15);
  LaBr3_TDiff=new TH1D("LaBr3_TDiff","LaBr3_TDiff",tbins,t_min,t_max);
  TDynode_Offset=new TH1D("TDynode_Offset","TDynode_Offset",tbins,t_min,t_max);
  LaBr3E_Vs_TDiff=new TH2D("LaBr3E_Vs_TDiff","LaBr3E_Vs_TDiff",tbins,t_min,t_max,ebins, e_min, e_max);
  LaBr3E_Vs_tdynode_offset=new TH2D("LaBr3E_Vs_tdynode_offset","LaBr3E_Vs_tdynode_offset",tbins,t_min,t_max,ebins, e_min, e_max);
  DyE_Vs_tdynode_offset=new TH2D("DyE_Vs_tdynode_offset","DyE_Vs_tdynode_offset",tbins,t_min,t_max,dbins, d_min, d_max);
  LaBr3_TDiff_Vs_E=new TH2D("LaBr3_TDiff_Vs_E","LaBr3_TDiff_Vs_E",ebins,e_min,e_max,tbins, t_min, t_max);
  LaBr3_tdynode_offset_Vs_E=new TH2D("LaBr3_tdynode_offset_Vs_E","LaBr3_tdynode_offset_Vs_E",ebins,e_min,e_max,tbins, t_min, t_max);
  GetOutputList()->Add(Labr3_Ecal);
  GetOutputList()->Add(LaBr3_TDiff);
  GetOutputList()->Add(TDynode_Offset);
  GetOutputList()->Add(Detector_Vs_TDynode_Offset);
  GetOutputList()->Add(LaBr3E_Vs_tdynode_offset);
   GetOutputList()->Add(DyE_Vs_tdynode_offset);
  GetOutputList()->Add(LaBr3E_Vs_TDiff);
  GetOutputList()->Add(LaBr3_tdynode_offset_Vs_E);
  GetOutputList()->Add(LaBr3_TDiff_Vs_E);
  GetOutputList()->Add(Detector_Vs_Labr3_Ecal);



  for(int i=0; i<16; i++){
    LaBr3E_Vs_tdynode_offset_Single[i]=new TH2D(Form("LaBr3E_Vs_tdynode_offset_%d",i),Form("LaBr3E_Vs_tdynode_offset_%d",i),tbins,t_min,t_max,ebins, e_min, e_max);
    TDynode_Offset_Single[i]=new TH1D(Form("TDynode_Offset_%d",i),Form("TDynode_Offset_%d",i),tbins,t_min,t_max);
    DyE_Vs_tdynode_offset_single[i]=new TH2D(Form("DyE_Vs_tdynode_offset_single_%d",i),Form("DyE_Vs_tdynode_offset_single_%d",i),tbins,t_min,t_max,dbins, d_min, d_max);
    GetOutputList()->Add(DyE_Vs_tdynode_offset_single[i]);
    GetOutputList()->Add(TDynode_Offset_Single[i]);
    GetOutputList()->Add(LaBr3E_Vs_tdynode_offset_Single[i]);
    

    for(int j=i+1; j<16; j++){
      LaBr3_TDiff_Single[i][j]=new TH1D(Form("LaBr3_TDiff_%d_%d",i,j),Form("LaBr3_TDiff_%d_%d",i,j),tbins,t_min,t_max);
      LaBr3E_Vs_TDiff_Single[i][j]=new TH2D(Form("LaBr3E_Vs_TDiff_%d_%d",i,j),Form("LaBr3E_Vs_TDiff_%d_%d",i,j),tbins,t_min,t_max,ebins, e_min, e_max);
      
      GetOutputList()->Add(LaBr3_TDiff_Single[i][j]);
      GetOutputList()->Add(LaBr3E_Vs_TDiff_Single[i][j]);
    }
  }
    
   TString option = GetOption();

}

Bool_t PID_Selector::Process(Long64_t entry)
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
  // fReader1.SetEntry(entry);
     auto cond =*corr_isdecay;
 
     double TOF = 0.0; // Initialize TOF with a default value
  double DE2 = 0.0; // Initialize DE2 with a default value

  // Check if implantlist1 is not null and has at least one element
   if (cond==1 && !implantlist1->empty()) {
      TOF = implantlist1->at(0).tof; // Safely access the first element's 'tof' member
      DE2 = implantlist1->at(0).de2; // Safely access the first element's 'de2' member
      PID->Fill(TOF,DE2);
  }




  // double dytime;
  // double dyenergy;
  // if( pspmthigh2_dyenergy.GetSize()>0 && pspmthigh2_dytime.GetSize()>0){
  //   dytime=pspmthigh2_dytime.At(0);
  //   dyenergy=pspmthigh2_dyenergy.At(0);
  //   if( dyenergy>15500 && dyenergy< 36000 && dytime>100){
  //     for(int i=0; i<16; i++){
  // 	if(labr_ecal[i]>50 && labr_time[i]>100 && labr_cfdfailbit[i]!=1 &&*pspmthigh2_dycfdfailbit!=1){
  // 	  Labr3_Ecal->Fill(labr_ecal[i]);
  // 	  Detector_Vs_Labr3_Ecal->Fill(labr_ecal[i],i);
  // 	  Double_t TDynode=labr_time[i]-dytime;
  // 	  // for(int index=0;index<pspmthigh2_dytime.GetSize(); index++){
  // 	  //   dytime=pspmthigh2_dytime.At(index);
  // 	  //   dyenergy=pspmthigh2_dyenergy.At(index);
  // 	  //   Double_t TDynode=1000.00;
  // 	  //   if( dyenergy>10000 &&dyenergy<60000 && dytime>100 &&abs(labr_time[i]-dytime)<TDynode){
  // 	  //     TDynode=labr_time[i]-dytime;
  // 	  //   }
	  
  // 	  //if((labr_ecal[i]>950||labr_ecal[i]<750)&&(labr_ecal[i]<1300)){
  // 	  Detector_Vs_TDynode_Offset->Fill(TDynode,i);
  // 	  LaBr3E_Vs_tdynode_offset->Fill(TDynode,labr_ecal[i]);
  // 	  DyE_Vs_tdynode_offset->Fill(TDynode,dyenergy);
  // 	  DyE_Vs_tdynode_offset_single[i]->Fill(TDynode,dyenergy);
  // 	  LaBr3_tdynode_offset_Vs_E->Fill(labr_ecal[i],TDynode);
  // 	  TDynode_Offset->Fill(TDynode);
  // 	  LaBr3E_Vs_tdynode_offset_Single[i]->Fill(TDynode,labr_ecal[i]);
  // 	  TDynode_Offset_Single[i]->Fill(TDynode);
	  
  // 	  for(int j=i+1; j<16; j++){
  // 	    if(labr_ecal[j]>50 && labr_time[j]>100 && labr_cfdfailbit[j]!=1){
  // 	      Double_t TDiff=labr_time[i]-labr_time[j];
  // 	      LaBr3_TDiff->Fill(TDiff);
  // 	      LaBr3E_Vs_TDiff->Fill(TDiff, labr_ecal[j]);
  // 	      LaBr3_TDiff_Vs_E->Fill(labr_ecal[j],TDiff);
  // 	      LaBr3_TDiff_Single[i][j]->Fill(TDiff);
  // 	      LaBr3E_Vs_TDiff_Single[i][j]->Fill(TDiff, labr_ecal[j]);
  // 	    }
  // 	  }
	  
  // 	}
  //     }
  //   }
  // }
  // }


  return kTRUE;
}

void PID_Selector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
}

void PID_Selector::Terminate()
{

  TFile* output=new TFile("PID_Decay.root","RECREATE");
  
//    fOutput->FindObject("Detector_Vs_TDynode_Offset")->Write();
//   fOutput->FindObject("LaBr3E_Vs_tdynode_offset")->Write();
//   fOutput->FindObject("LaBr3_TDiff")->Write();
//   fOutput->FindObject("TDynode_Offset")->Write();
//   fOutput->FindObject("LaBr3E_Vs_TDiff")->Write();
//   fOutput->FindObject("DyE_Vs_tdynode_offset")->Write();
// fOutput->FindObject("LaBr3_TDiff_Vs_E")->Write();
//  fOutput->FindObject("LaBr3_tdynode_offset_Vs_E")->Write();
// fOutput->FindObject("Labr3_Ecal")->Write();
// fOutput->FindObject("Detector_Vs_Labr3_Ecal")->Write();

//   output->mkdir("Labr3-Dynode");
//   output->mkdir("Labr3-Labr3");
//   for(int i=0; i<16; i++){
//     output->cd("Labr3-Dynode");
//     fOutput->FindObject(Form("TDynode_Offset_%d",i))->Write();
//     fOutput->FindObject(Form("LaBr3E_Vs_tdynode_offset_%d",i))->Write();
//     fOutput->FindObject(Form("DyE_Vs_tdynode_offset_single_%d",i))->Write();
     
//     for(int j=i+1; j<16; j++){
//       output->cd("Labr3-Labr3");
//       fOutput->FindObject(Form("LaBr3_TDiff_%d_%d",i,j))->Write();
//       fOutput->FindObject(Form("LaBr3E_Vs_TDiff_%d_%d",i,j))->Write();
//     }
//   }
   fOutput->FindObject("PID")->Write();
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
