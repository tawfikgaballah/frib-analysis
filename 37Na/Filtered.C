#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TString.h"
#include "TSystem.h"
#include "TCutG.h"
#include "/projects/e21062/tg/rootAnalysis/betasort1/include/TPID.h"
#include <vector>
#include <map>
#include <iostream>
#include <cmath>

void Filtered() {
  gStyle->SetOptStat(11111111);
  gSystem->Load("/projects/e21062/tg/rootAnalysis/betasort1/libTParameters.so");
  // gSystem->Load("libDict.so");
  gSystem->Load("/projects/e21062/tg/rootAnalysis/betasort1/include/");
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
      if ( //(runNumber == 1281 || runNumber == 1282 || runNumber == 1283) &&
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


  std::map<std::tuple<int, int, std::string>, std::string> nuclei = {
								      /* {{3, 2, "Na"}, "32Na"}, {{3, 3, "Na"}, "33Na"}, {{3, 4, "Na"}, "34Na"},
								      {{3, 5, "Na"}, "35Na"}// , {{3, 6, "Na"}, "36Na"}, */
								       {{3, 7, "Na"}, "37Na"},
								       {{3, 1, "F"}, "31F"}
								     // {{3, 8, "Na"}, "38Na"}
  };

  TFile* blobs = new TFile("./iongates_6mm_radius.root", "Read");
  std::map<std::tuple<int, int, std::string>, TCutG*> iongates;
  std::map<std::tuple<int, int, std::string>, TH2D*> h2clover_Vs_tdiff;
  std::map<std::tuple<int, int, std::string>,TH1D*> hclover;
  std::map<std::tuple<int, int, std::string>,TH2D*> h2clover;
  std::map<std::tuple<int, int, std::string>,TH2D*> h2clover1;
  std::map<std::tuple<int, int, std::string>, TH2D*> h2decay_Vs_radius;
  for (const auto& entry : nuclei) {
    int i = std::get<0>(entry.first);
    int j = std::get<1>(entry.first);
    std::string nucl = std::get<2>(entry.first);
    if (blobs->IsOpen()) {
      iongates[entry.first] = (TCutG*)blobs->Get(Form("%d%d%s_Decay", i, j, nucl.c_str()));
      if (iongates[entry.first]) {
	h2clover_Vs_tdiff[entry.first] = new TH2D(Form("Clover_Vs_TDiff_^{%d%d}%s", i, j, nucl.c_str()),
						  Form("Clover_Vs_TDiff_^{%d%d}%s", i, j, nucl.c_str()),
						  2200, -1000, 10000, 4500, 0, 4500);
	hclover[entry.first]=new TH1D(Form("Clover_Spectrum_Following_the_Decay_^{%d%d}%s", i, j, nucl.c_str()),
				     Form("Clover_Spectrum_Following_the_Decay_^{%d%d}%s", i, j, nucl.c_str()),
				      4500, 0, 4500);
	h2clover[entry.first]=new TH2D(Form("h2_Clover_Spectrum_Following_the_Decay_^{%d%d}%s", i, j, nucl.c_str()),
				       Form("h2_Clover_Spectrum_Following_the_Decay_^{%d%d}%s", i, j, nucl.c_str()),
				       4500, 0, 4500,4500,0,4500);

	h2clover1[entry.first]=new TH2D(Form("Prompt_h2_Clover_Spectrum_Following_the_Decay_^{%d%d}%s", i, j, nucl.c_str()),
					Form("Prompt_h2_Clover_Spectrum_Following_the_Decay_^{%d%d}%s", i, j, nucl.c_str()),
					4500, 0, 4500,4500,0,4500);

	h2decay_Vs_radius[entry.first]=new TH2D(Form("DecayTime_Vs_Radius_^{%d%d}%s",i,j,nucl.c_str()),
						Form("DecayTime_Vs_Radius_^{%d%d}%s",i,j,nucl.c_str()),
						80,0,8,2000,-100,100);
      }
    }
  }
  TH2D* PID_Implant=new TH2D("PID_Implant", "PID_Implant; tof; de2", 1000, -1000, -900, 1400, 0, 1400);
  TH2D* PID_Decay=new TH2D("PID_Decay", "PID_Decay; tof; de2", 1000, -1000, -900, 1400, 0, 1400);

  TFile* output = new TFile("decay_vs_radius_filtered_forward+reverse_cutondyenergy.root", "recreate");
  // Sort run numbers
  std::sort(runNumbers.begin(), runNumbers.end());

  // Process each run
  for (int runnumber : runNumbers) {
    //TString filePath = TString::Format("/mnt/analysis/e21062/aad/e21062B/sortedNewCal/run-%d-sorted.root", runnumber);
    TString filePath = TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/reverse_run-%d-sorted.root", runnumber);
    TFile* filter = TFile::Open(filePath);
    TChain* data = new TChain("trimmed_data");
    data->Add(TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/*run-%d-sorted.root", runnumber));

    // TFile* friendfile = TFile::Open(TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files_Clover_LaBr3run-%d-sorted.root", runnumber));
    // TTree* data_friend = (TTree*)friendfile->Get("trimmed_data");
    // data_friend->SetTitle("Gamma");
    // data_friend->SetName("Gamma");

    std::cout << "Added file: " << filePath.Data() << std::endl;

    // data->AddFriend(data_friend, "Gamma");

    // Set branch addresses
    std::vector<TPID>* implantlist = nullptr;
    double corr_dxpos, corr_dypos, corr_dtime, corr_itof, corr_ide2, corr_gtof, corr_gde2, corr_gitime;
    int corr_isdecay, corr_isimplant, corr_hasclover;
    std::vector<double> *pspmtlow1_dytime = nullptr, *pspmthigh1_dytime = nullptr;
    std::vector<double> *pspmtlow1_dyenergy = nullptr, *pspmthigh1_dyenergy = nullptr;
    Int_t pspmtlow1_dyhit, pspmthigh1_dyhit, pspmtlow1_dycfdfailbit, pspmthigh1_dycfdfailbit;
    Double_t clover_ecal[52], clover_timecal[52];
    int clover_cfdfailbit[52];
    // data->SetBranchStatus("*", 0);

    // data->SetBranchStatus("implantlist", 1);
    // data->SetBranchStatus("corr.dxpos", 1);
    // data->SetBranchStatus("corr.dypos",1);
    // data->SetBranchStatus("corr.dtime", 1);
    // data->SetBranchStatus("corr.isdecay", 1);
    // data->SetBranchStatus("corr.itof", 1);
    // data->SetBranchStatus("corr.ide2",1);
    // data->SetBranchStatus("corr.gtof", 1);
    // data->SetBranchStatus("corr.gde2",1);
    // data->SetBranchStatus("corr.gitime", 1);
    // data->SetBranchStatus("corr.hasclover", 1);
    // data->SetBranchStatus("corr.isimplant", 1);
    // data->SetBranchStatus("pspmtlow1.dytime", 1);
    // data->SetBranchStatus("pspmthigh1.dytime",1);
    // data->SetBranchStatus("pspmtlow1.dyenergy", 1);
    // data->SetBranchStatus("pspmthigh1.dyenergy", 1);
    // data->SetBranchStatus("pspmtlow1.dyhit", 1);
    // data->SetBranchStatus("pspmthigh1.dyhit", 1);
    // data->SetBranchStatus("pspmtlow1.dycfdfailbit", 1);
    // data->SetBranchStatus("pspmthigh1.dycfdfailbit", 1);
    // data->SetBranchStatus("clover.ecal[52]", 1);
    // data->SetBranchStatus("clover.timecal[52]", 1);
    // data->SetBranchStatus("clover.cfdfailbit[52]",1);







    
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



    
  /*   
    data->SetBranchAddress("implantlist", &implantlist);
    data->SetBranchAddress("corr.dxpos", &corr_dxpos);
    data->SetBranchAddress("corr.dypos", &corr_dypos);
    data->SetBranchAddress("corr.dtime", &corr_dtime);
    data->SetBranchAddress("corr.isdecay", &corr_isdecay);
    data->SetBranchAddress("corr.itof", &corr_itof);
    data->SetBranchAddress("corr.ide2", &corr_ide2);
    data->SetBranchAddress("corr.gtof", &corr_gtof);
    data->SetBranchAddress("corr.gde2", &corr_gde2);
    data->SetBranchAddress("corr.gitime", &corr_gitime);
    data->SetBranchAddress("corr.hasclover", &corr_hasclover);
    data->SetBranchAddress("corr.isimplant", &corr_isimplant);
    data->SetBranchAddress("pspmtlow1.dytime", &pspmtlow1_dytime);
    data->SetBranchAddress("pspmthigh1.dytime",&pspmthigh1_dytime);
    data->SetBranchAddress("pspmtlow1.dyenergy", &pspmtlow1_dyenergy);
    data->SetBranchAddress("pspmthigh1.dyenergy", &pspmthigh1_dyenergy);
    data->SetBranchAddress("pspmtlow1.dyhit", &pspmtlow1_dyhit);
    data->SetBranchAddress("pspmthigh1.dyhit", &pspmtlow1_dyhit);
    data->SetBranchAddress("pspmtlow1.dycfdfailbit", &pspmtlow1_dycfdfailbit);
    data->SetBranchAddress("pspmthigh1.dycfdfailbit", &pspmthigh1_dycfdfailbit);
    data->SetBranchAddress("clover.ecal[52]", &clover_ecal);
    data->SetBranchAddress("clover.timecal[52]", &clover_timecal);
    data->SetBranchAddress("clover.cfdfailbit[52]", &clover_cfdfailbit); */


    long int totalentries = data->GetEntries();
    std::cout << "Processing Run: " << runnumber << " with Entries: " << totalentries << '\n';

    // Loop through the entries
    for (long int entry = 0; entry < totalentries; ++entry) {
      data->GetEntry(entry);
      if(corr_isimplant==1 &&(pspmtlow1_dyenergy->at(0)>50) &&entry<totalentries/2)
       	PID_Implant->Fill(corr_itof, corr_ide2);
      if (corr_isdecay == 1) {
	for (int i=0; i<implantlist->size(); i++) {
	  double TOF = implantlist->at(i).tof;
	  double DE2 = implantlist->at(i).de2;
	  double ixpos = implantlist->at(i).xpos;
	  double iypos = implantlist->at(i).ypos;
	  double itime = implantlist->at(i).time;
	  double dtimecal = corr_dtime - itime;
	  // double TOF = corr_gtof;
	  // double DE2 = corr_gde2;
	  if(/* sqrt(pow((ixpos-corr_dxpos),2)+pow((iypos-corr_dypos),2))<=3 &&  */abs(dtimecal) <= 100){
	    if(sqrt(pow((ixpos-corr_dxpos),2)+pow((iypos-corr_dypos),2))<=3&&(pspmthigh1_dyenergy->at(0)>50 || pspmtlow1_dyenergy->at(0)>50) &&(dtimecal) >=0)
	     PID_Decay->Fill(TOF, DE2);
	    for (const auto& entry : nuclei) {
	      int i = std::get<0>(entry.first);
	      int j = std::get<1>(entry.first);
        bool cond=false; 
	      std::string nucl = std::get<2>(entry.first);
        // if (nucl=="F") std::cout<<"true"<<'\n';
        if((nucl=="F" && TOF>=-957&&TOF<=-953 &&DE2>=458.5 &&DE2<=500)||(nucl=="Na" && TOF>=-959&&TOF<=-956.5 &&DE2>=695 &&DE2<=750))
        cond=true;
	if (iongates[entry.first]->IsInside(TOF, DE2) && cond==true &&(pspmthigh1_dyenergy->at(0)>50 || pspmtlow1_dyenergy->at(0)>50)
		  ) {
		     h2decay_Vs_radius[entry.first]->Fill(sqrt(pow((ixpos-corr_dxpos),2)+pow((iypos-corr_dypos),2)),dtimecal);
		/* for (int i = 0; i < 52; ++i) {
		  if (clover_ecal[i] > 20 && clover_timecal[i] > 20) {
		    hclover[entry.first]->Fill(clover_ecal[i]);
		    for (int j = i+1; j < 52; ++j) {
		      if (clover_ecal[j] > 20 &&  clover_timecal[j] > 20) {
			h2clover[entry.first]->Fill(clover_ecal[i], clover_ecal[j]);
			h2clover[entry.first]->Fill(clover_ecal[j], clover_ecal[i]);
		      }
		    }
		  }
		} */
	      }
	    }
	  }
	  // double dx = ixpos - corr_dxpos;
	  // double dy = iypos - corr_dypos;
	  // if(// *corr_isforward==1 &&
	  //   pspmthigh1_dytime->size() > 0 && pspmthigh1_dytime->at(0)>10 && pspmthigh1_dyenergy->at(0)>10){
	  //   // h2radius_Vs_*clover[entry.first]->Fill(*clover_ecal[i],sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2)) );
	  //   h2clover_Vs_tdiff[entry.first]->Fill(((clover_timecal[i])-pspmthigh1_dytime->at(0)), clover_ecal[i]);
	  // }
	  // else if(// *corr_isforward==1 &&
	  //  pspmtlow1_dytime->size() > 0 && pspmtlow1_dytime->at(0)>10 && pspmtlow1_dyenergy->at(0)>10){
	  //   h2clover_Vs_tdiff[entry.first]->Fill(((clover_timecal[i])-pspmtlow1_dytime->at(0)), clover_ecal[i]);
	  // }
	  // h2clover_Vs_tdiff[entry.first]->Fill(clover_timecal[i]-corr_dtime*1.e06, clover_ecal[i]);

        
		  
	  //	h2clover_Vs_tdiff[entry.first]->Fill(clover_timecal[i]/1.e03-corr_gitime*1.e03, clover_ecal[i]);
		  
	  
	
	  // else if((clover_timecal[i]-corr_dtime*1.e06)<150 &&(clover_timecal[i]-corr_dtime*1.e06)>0){
	  // 	 h2clover1[entry.first]->Fill(clover_ecal[i], clover_ecal[j]);
	  // 	 h2clover1[entry.first]->Fill(clover_ecal[j], clover_ecal[i]);
	  // }
	  //   }
	  // }
	  //	}
	  //  }
	  //  }
	  //  }//end iongates loop 
	}//end implantlist loop 
      }//end event check 
    }
    filter->Close();
    // friendfile->Close();
    delete filter;
    // delete friendfile;
    // delete data;
    // delete data_friend;
    std::cout<<"done"<<'\n';
  }
   
  output->cd();
  for (const auto& entry : nuclei) {
    int i = std::get<0>(entry.first);
    int j = std::get<1>(entry.first);
    std::string nucl = std::get<2>(entry.first);
    output->mkdir(Form("%d%d%s", i, j, nucl.c_str()));
    output->cd(Form("%d%d%s", i, j, nucl.c_str()));
     // h2clover_Vs_tdiff[entry.first]->Write();
    // hclover[entry.first]->Write();
     // h2clover1[entry.first]->Write();
       //h2clover[entry.first]->Write();
      h2decay_Vs_radius[entry.first]->Write();
  }
  PID_Implant->Write();
  PID_Decay->Write();
  output->Close();
}
