/* This script utilizes AddFiles.h
 * so that several analysed root files 
 * can be loaded to TChain object at
 * the same time
 */
#include <TObject.h>
#include "TTree.h"
{
  gSystem->Load("/projects/e21062/tg/rootAnalysis/rootAnalysisFinal/include/");
 // gInterpreter->AddIncludePath("/user/gaballah/ddasfitclasses/");
 // gSystem->Load("/user/gaballah/ddasfitclasses/libDDASFitClasses.so");
  gSystem->Load("/projects/e21062/tg/rootAnalysis/rootAnalysisFinal/libTParameters.so");
    gROOT->ProcessLine(".L ./AddFiles1.C+");
 
  gROOT->ProcessLine(".L ./clover.C+");

  // TFile *input=new TFile("/mnt/analysis/e16032/tg1250/rootfiles/2004/run-2004-tg1250.root", "READ");
  TChain* dataref=new TChain("data");
  // TChain *data_cal = new TChain("data_cal");
  // data->Add("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1423-sorted.root");
  // data_cal->Add("/projects/e21062/tg/37Na_Setting/calibration_test_run_1423_linear_two_points.root");
  AddRootFiles(dataref,1422,1422);
     // TChain* dataref=(TChain*)data->Clone();
     // dataref->SetDirectory(0);
    //  AddRootFiles(data,1300,1433);
  // data1->Add("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resortedNewCal37Na/run-1420-sorted.root");
  // ConvertChainToTree(data1,dataref);
  // dataref->Add("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/CorrSorted37Na-Reverse-Win3/run*");
  // AddRootFiles_Cal(data_cal,1281,1283);
  // std::cout<<data->GetEntries()<<'\n';
  // std::cout<<data_cal->GetEntries()<<'\n';
  // data->AddFriend(data_cal,"data_cal");

  //  TProof *proof = TProof::Open("workers=10");
  // dataref->SetProof();
std::cout<<dataref->GetEntries()<<'\n';
  //12/29/21
  dataref->Process("./clover.C++");
  // data->Process("BetaDecaySelector.C+");
  
  
  // // detach from current PROOF session
  // dataref->SetProof(0);

  
  // //display process details
  //   gProof->GetQueryResult()->Print();

  

  
}
