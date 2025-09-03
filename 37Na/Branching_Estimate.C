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






{


 gStyle->SetOptStat(11111111);
  gSystem->Load("/projects/e21062/aad/e21062B/rootAnalysisFinal/libTParameters.so");
  // gSystem->Load("libDict.so");
  gSystem->Load("/projects/e21062/aad/e21062B/rootAnalysisFinal/include/");


   TString filePath = TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/run-%d-sorted.root", 1430);
    TFile* filter = TFile::Open(filePath);
    TTree* data = (TTree*)filter->Get("trimmed_data");

     std::vector<TPID>* implantlist = nullptr;
    double corr_dxpos, corr_dypos, corr_dtime, corr_itof, corr_ide2, corr_gtof, corr_gde2, corr_gitime;
    int corr_isdecay, corr_isimplant, corr_hasclover;
    std::vector<double> *pspmtlow1_dytime = nullptr, *pspmthigh1_dytime = nullptr;
    std::vector<double> *pspmtlow1_dyenergy = nullptr, *pspmthigh1_dyenergy = nullptr;
    Int_t pspmtlow1_dyhit, pspmthigh1_dyhit, pspmtlow1_dycfdfailbit, pspmthigh1_dycfdfailbit;
    Double_t clover_ecal[52], clover_timecal[52];
    int clover_cfdfailbit[52];



    

    
    data->SetBranchAddress("implantlist_nonnull", &implantlist);
    data->SetBranchAddress("corr_dxpos", &corr_dxpos);
    data->SetBranchAddress("corr_dypos", &corr_dypos);
    data->SetBranchAddress("corr_dtime", &corr_dtime);
    data->SetBranchAddress("corr_isdecay", &corr_isdecay);
    data->SetBranchAddress("corr_itof", &corr_itof);
    data->SetBranchAddress("corr_ide2", &corr_ide2);
    data->SetBranchAddress("corr_gtof", &corr_gtof);
    data->SetBranchAddress("corr_gde2", &corr_gde2);
    data->SetBranchAddress("corr_gitime", &corr_gitime);
    data->SetBranchAddress("corr_hasclover", &corr_hasclover);
    data->SetBranchAddress("corr_isimplant", &corr_isimplant);
    data->SetBranchAddress("pspmtlow1_dytime_nonnull", &pspmtlow1_dytime);
    data->SetBranchAddress("pspmthigh1_dytime_nonnull",&pspmthigh1_dytime);
    data->SetBranchAddress("pspmtlow1_dyenergy_nonnull", &pspmtlow1_dyenergy);
    data->SetBranchAddress("pspmthigh1_dyenergy_nonnull", &pspmthigh1_dyenergy);
    data->SetBranchAddress("pspmtlow1_dyhit", &pspmtlow1_dyhit);
    data->SetBranchAddress("pspmthigh1_dyhit", &pspmtlow1_dyhit);
    data->SetBranchAddress("pspmtlow1_dycfdfailbit", &pspmtlow1_dycfdfailbit);
    data->SetBranchAddress("pspmthigh1_dycfdfailbit", &pspmthigh1_dycfdfailbit);
    data->SetBranchAddress("clover_ecal[52]", &clover_ecal);
    data->SetBranchAddress("clover_timecal[52]", &clover_timecal);
    data->SetBranchAddress("clover_cfdfailbit[52]", &clover_cfdfailbit);



 TFile* blobs = new TFile("./iongates_6mm_radius.root", "Read");
 
 TCutG* Na_33 = (TCutG*)blobs->Get("35Na_Implant");

 TH2D* PID=new TH2D("PID","PID", 1000,-1000,-900,1400,0,1400);

std::vector<Long64_t> ievent_list;

// Loop over entries and check against the TCutG
Long64_t nentries = data->GetEntries();
for (Long64_t i = 0; i < nentries; i++) {
    data->GetEntry(i);
    if (Na_33->IsInside(corr_itof, corr_ide2)) {  // Assuming corr.itime is relevant for the cut
        ievent_list.push_back(i);
    }
}


 for (auto ievent : ievent_list) {
    // Define the lower and upper bounds for filtering
    Long64_t upper_bound = ievent + 200;
    Long64_t lower_bound = ievent + 100;

    // Ensure that the bounds are within valid entry numbers
    for (Long64_t i = lower_bound; i <= upper_bound; i++) {
        if (i >= 0 && i < nentries) {  // Ensure the event number is valid
            data->GetEntry(i);
	    PID->Fill(corr_itof, corr_ide2);
            // Process the filtered entries as needed, e.g., store, print, analyze
        }
    }
}


 PID->Draw("colz");
}
