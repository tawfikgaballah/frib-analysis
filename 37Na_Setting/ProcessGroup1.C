/* This script utilizes AddFiles.h
 * so that several analysed root files 
 * can be loaded to TChain object at
 * the same time
 */
#include <TObject.h>
#include "TTree.h"
{

  gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/include/");
  gInterpreter->AddIncludePath("/user/e21062/HLC/ddasfitclasses/");
  gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/libTParameters.so");
    gROOT->ProcessLine(".L AddFiles1.C+"); // load // // the files that you want to look at
    // gROOT->ProcessLine(".L BetaDecaySelector.C+");
     gROOT->ProcessLine(".L labr_selector.C+");
   // TFile *input=new TFile("/mnt/analysis/e16032/tg1250/rootfiles/2004/run-2004-tg1250.root", "READ");
   TChain *data = new TChain("data");
   // TChain *data_cal = new TChain("data_cal");
// data->Add("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1423-sorted.root");
// data_cal->Add("/projects/e21062/tg/37Na_Setting/calibration_test_run_1423_linear_two_points.root");
   AddRootFiles(data,1420,1420);
   // AddRootFiles_Cal(data_cal,1420,1420);
   // std::cout<<data->GetEntries()<<'\n';
   // std::cout<<data_cal->GetEntries()<<'\n';
   // data->AddFriend(data_cal,"data_cal");

    TProof *proof = TProof::Open("workers=40");
   data->SetProof();

  //12/29/21
     data->Process("labr_selector.C+");
    // data->Process("BetaDecaySelector.C+");
  
  
  // detach from current PROOF session
  data->SetProof(0);

  
  //display process details
    gProof->GetQueryResult()->Print();

  

  
}
