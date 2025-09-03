#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TString.h"
#include "TSystem.h"
#include "TCutG.h"
#include "/projects/e21062/aad/e21062B/rootAnalysisFinal/include/TPID.h"
#include <vector>
#include <map>
#include <iostream>
#include <cmath>

void Filtered() {
  gStyle->SetOptStat(11111111);
  gSystem->Load("/projects/e21062/aad/e21062B/rootAnalysisFinal/libTParameters.so");
  // gSystem->Load("libDict.so");
  gSystem->Load("/projects/e21062/aad/e21062B/rootAnalysisFinal/include/");
  // Open the directory
  void* dir = gSystem->OpenDirectory("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/");
  const char* file;
  std::vector<int> runNumbers;

  // Iterate over files in the directory
  while ((file = gSystem->GetDirEntry(dir))) {
    TString fileName = TString(file);
    if (fileName.BeginsWith("run-") && fileName.EndsWith("-sorted.root")) {
      TString runNumberStr = fileName(4, fileName.Length() - 13); 
      int runNumber = runNumberStr.Atoi();
      if (//(runNumber == 1281 || runNumber == 1282 || runNumber == 1283) &&
	  runNumber != 1398 && runNumber != 1335 && runNumber != 1332 && runNumber != 1289) {
	runNumbers.push_back(runNumber); 
      }
    }
  }
  gSystem->FreeDirectory(dir);

  // // Setup the histograms
  // TH2D* PID_Implant = new TH2D("PID_Implant", "PID_Implant", 1000, -1000, -900, 1400, 0, 1400);
  // PID_Implant->GetXaxis()->SetTitle("tof");
  // PID_Implant->GetYaxis()->SetTitle("de2");



  TFile* output = new TFile("LaBr3_run_by_run.root", "recreate");
  TH2D* Run_Vs_E[16];
  TH2D* Detector_Vs_E=new TH2D("Detector_Vs_E","Detector_Vs_E",3000,0,3000,16,0,16);
  for(int i=0; i<16; i++){
    Run_Vs_E[i]= new TH2D(Form("Run_Vs_E_%d", i), Form("Run_Vs_E_%d", i), 3000, 0, 3000, 152, 1281, 1433);
  }
  // Sort run numbers
  std::sort(runNumbers.begin(), runNumbers.end());

  // Process each run
  for (int runnumber : runNumbers) {
    TString filePath = TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/run-%d-sorted.root", runnumber);
    TFile* filter = TFile::Open(filePath);
    TTree* data = (TTree*)filter->Get("trimmed_data");

    // TFile* friendfile = TFile::Open(TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files_Clover_LaBr3run-%d-sorted.root", runnumber));
    // TTree* data_friend = (TTree*)friendfile->Get("trimmed_data");
    // data_friend->SetTitle("Gamma");
    // data_friend->SetName("Gamma");

    std::cout << "Added file: " << filePath.Data() << std::endl;

    // data->AddFriend(data_friend, "Gamma");







    double labr_ecal[16];
    int corr_isdecay;
    double labr_time[16];
    int labr_cfd[16];
    data->SetBranchAddress("labr_ecal[16]", labr_ecal);
    data->SetBranchAddress("corr_isdecay", &corr_isdecay);
   

    long int totalentries = data->GetEntries();
    std::cout << "Processing Run: " << runnumber << " with Entries: " << totalentries << '\n';

    // Loop through the entries
    for (long int entry = 0; entry < totalentries; ++entry) {
      data->GetEntry(entry);
      for (int j=0; j<16; j++){
if(labr_ecal[j] > 10){
	Run_Vs_E[j]->Fill(labr_ecal[j], runnumber);
	Detector_Vs_E->Fill(labr_ecal[j], j);
 }
 }
    }
    filter->Close();
    // friendfile->Close();
    delete filter;
    // delete friendfile;
    //  delete data;
    // delete data_friend;
    std::cout<<"done"<<'\n';
  }
   
  output->cd();
  for(int i=0; i<16; i++){
    Run_Vs_E[i]->Write();
  }
  Detector_Vs_E->Write();
  output->Close();
}

