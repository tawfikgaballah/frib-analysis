#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TH1D.h"
#include "TString.h"
#include "TSystem.h"
#include "TCutG.h"
#include "TStyle.h"     // ADD THIS
#include "TChain.h"     // ADD THIS
#include "TROOT.h"      // ADD THIS
#include "/projects/e21062/tg/rootAnalysis/betasort1/include/TPID.h"
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
void AnalyzeDecay(int runnumber){
  // Nuclei of interest
  std::map<std::tuple<int, int, std::string>, std::string> nuclei = {
    {{3, 8, "Na"}, "38Na"},
    {{3, 6, "Na"}, "36Na"},
    {{3, 1, "F"}, "31F"},
    {{3, 0, "F"}, "30F"},
    {{3, 2, "F"}, "32F"},
    {{3, 4, "Na"}, "34Na"},
    {{3, 5, "Na"}, "35Na"},
    {{3, 2, "Na"}, "32Na"},
    {{3, 3, "Na"}, "33Na"},
    {{3, 7, "Na"}, "37Na"}
  };
  // Constants (hardcoded from FDSiParameters / calibrator)
    const double L =  56423;         // mm
    const double brho = 9.04 ;           // Tm
    const double c = 299.792458;       // mm/ns
    const double Z_slope = 1.4116;
    const double Z_offset =0;
    const double Z_log_beta = 1.1739;

    // z0 formula constants
    const double z0_A = 50.4562;
    const double z0_B =10.495;
    const double mass_unit = 931.494013;   // MeV/c^2
    double denom = sqrt(9.0 * mass_unit * mass_unit + brho * brho * c * c);
    double beta0 = (c * brho) / denom;
    const int xbins = 1000, ybins = 1000;
    const double min_AoQ = 1.5, max_AoQ = 3.5;
    const double min_Z = 0, max_Z = 30;

  // Load ion gates
  TFile* blobs = new TFile("./iongates_6mm_radius.root", "READ");
  std::map<std::tuple<int, int, std::string>, TCutG*> iongates;
  std::map<std::tuple<int, int, std::string>, TH2D*> h2decay_Vs_radius;
  std::map<std::tuple<int, int, std::string>, TH1D*> pspmtlow;
  std::map<std::tuple<int, int, std::string>, TH1D*> pspmthigh;
  for (const auto& entry : nuclei) {
    int i = std::get<0>(entry.first);
    int j = std::get<1>(entry.first);
    std::string nucl = std::get<2>(entry.first);
    iongates[entry.first] = (TCutG*)blobs->Get(Form("%d%d%s_Decay", i, j, nucl.c_str()));
    h2decay_Vs_radius[entry.first] = new TH2D(Form("DecayTime_Vs_Radius_^{%d%d}%s",i,j,nucl.c_str()),
                                              Form("DecayTime_Vs_Radius_^{%d%d}%s",i,j,nucl.c_str()),
                                              80,0,8,2000,-100,100);
    pspmtlow[entry.first] = new TH1D(Form("pspmtlow_^{%d%d}%s",i,j,nucl.c_str()),
				     Form("pspmtlow_^{%d%d}%s",i,j,nucl.c_str()),
				     65536,0,65536);
    pspmthigh[entry.first] = new TH1D(Form("pspmthigh_^{%d%d}%s",i,j,nucl.c_str()),
				      Form("pspmthigh_^{%d%d}%s",i,j,nucl.c_str()),
				      65536,0,65536);
  }

  TH2D* PID_Implant=new TH2D("PID_Implant", "PID_Implant; tof; de2", 1000, -1000, -900, 1400, 0, 1400);
  TH2D* PID_Decay=new TH2D("PID_Decay", "PID_Decay; tof; de2", 1000, -1000, -900, 1400, 0, 1400);

   TH2D* PID_Implant_zaq=new TH2D("PID_Implant_zaq", "PID_Implant_zaq; tof; de2", 1000, 1.5, 3.5, 1000, 0, 30);
  TH2D* PID_Decay_zaq=new TH2D("PID_Decay_zaq", "PID_Decay_zaq; tof; de2", 1000, 1.5, 3.5, 1000, 0, 30);

  TFile* output = new TFile(Form("/mnt/analysis/e21062/tg/batch_analysis/analyzed/decay_vs_radius_1_percent_run%d.root", runnumber), "RECREATE");


  TString filePath = TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/reverse_run-%d-sorted.root", runnumber);
  
  TChain* data = new TChain("trimmed_data");
  data->Add(TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/run-%d-sorted.root", runnumber));
  data->Add(TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/reverse_run-%d-sorted.root", runnumber));

  // Declare and set branch addresses like you already do...
  // Set branch addresses
  std::vector<TPID>* implantlist = nullptr;
  double corr_dxpos, corr_dypos, corr_dtime, corr_itof, corr_ide2, corr_gtof, corr_gde2, corr_gitime;
  int corr_isdecay, corr_isimplant, corr_hasclover;
  std::vector<double> *pspmtlow1_dytime = nullptr, *pspmthigh1_dytime = nullptr;
  std::vector<double> *pspmtlow1_dyenergy = nullptr, *pspmthigh1_dyenergy = nullptr;
  Int_t pspmtlow1_dyhit, pspmthigh1_dyhit, pspmtlow1_dycfdfailbit, pspmthigh1_dycfdfailbit;
  Double_t clover_ecal[52], clover_timecal[52];
  int clover_cfdfailbit[52];
  // [Keep the same variables and SetBranchAddress calls from your original code]
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
  data->SetBranchAddress("pspmthigh1_dyhit", &pspmthigh1_dyhit);
  data->SetBranchAddress("pspmtlow1_dycfdfailbit", &pspmtlow1_dycfdfailbit);
  data->SetBranchAddress("pspmthigh1_dycfdfailbit", &pspmthigh1_dycfdfailbit);
  data->SetBranchAddress("clover_ecal[52]", &clover_ecal);
  data->SetBranchAddress("clover_timecal[52]", &clover_timecal);
  data->SetBranchAddress("clover_cfdfailbit[52]", &clover_cfdfailbit);

  long int totalentries = data->GetEntries();
  std::cout << "Processing Run: " << runnumber << " with Entries: " << totalentries << '\n';
  for (long int entry = 0; entry < totalentries; ++entry) {
    data->GetEntry(entry);
    if(corr_isimplant==1 &&(pspmtlow1_dyenergy->at(0)>50) &&entry<totalentries/2){
      PID_Implant->Fill(corr_itof, corr_ide2);
      double beta = L / ((corr_itof+971.983+270.69) * c);
      if (beta >= 0 && beta <= 1){

	double beta2 = beta * beta;
	double gamma = 1.0 / sqrt(1.0 - beta2);

	// Step 2: AoQ
	double aoq = (c * brho) / (beta * gamma * mass_unit);
	if (aoq > 1.5 && aoq < 3.5){

	  // Step 3: z0
	  double logterm = ((corr_ide2) + z0_A) / z0_B;
	  if (logterm >= 0){

            double z0 = pow(beta / beta0, 1.3) * sqrt(logterm);

            // Step 4: final Z
            double Z = Z_offset + Z_slope * z0;
            if (Z > 0 && Z < 30) {
	      PID_Implant_zaq->Fill(aoq,Z);
	    }
	  }
	}
      }
    }
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
	  if(sqrt(pow((ixpos-corr_dxpos),2)+pow((iypos-corr_dypos),2))<=3&&(pspmthigh1_dyenergy->at(0)>50 || pspmtlow1_dyenergy->at(0)>50) &&(dtimecal) >=0){
	    PID_Decay->Fill(TOF, DE2);
	    double beta = L / ((TOF+971.983+270.69) * c);
	    if (beta >= 0 && beta <= 1){

	      double beta2 = beta * beta;
	      double gamma = 1.0 / sqrt(1.0 - beta2);

	      // Step 2: AoQ
	      double aoq = (c * brho) / (beta * gamma * mass_unit);
	      if (aoq > 1.5 && aoq < 3.5){

		// Step 3: z0
		double logterm = ((DE2) + z0_A) / z0_B;
		if (logterm >= 0){

		  double z0 = pow(beta / beta0, 1.3) * sqrt(logterm);

		  // Step 4: final Z
		  double Z = Z_offset + Z_slope * z0;
		  if (Z > 0 && Z < 30) {
		    PID_Decay_zaq->Fill(aoq,Z);
		  }
		}
	      }
	    }
	  }
	  for (const auto& entry : nuclei) {
	    bool cond=false; 
	    std::string nucl = entry.second;
	    // if (nucl=="F") std::cout<<"true"<<'\n';
	    if((nucl=="31F" && TOF>=-957&&TOF<=-953 &&DE2>=458.5 &&DE2<=500)||(nucl=="37Na" && TOF>=-959&&TOF<=-956.5 &&DE2>=695 &&DE2<=750))
	      cond=true;
	    if (iongates[entry.first]->IsInside(TOF, DE2)// && (cond==true||(cond==false&& nucl!="31F" &&nucl!="37Na"))
		){
	      pspmtlow[entry.first]->Fill(pspmtlow1_dyenergy->at(0));
	      pspmthigh[entry.first]->Fill(pspmthigh1_dyenergy->at(0));
	    }
	    if (iongates[entry.first]->IsInside(TOF, DE2) // && (cond==true||(cond==false&& nucl!="31F" &&nucl!="37Na"))
		&&(pspmthigh1_dyenergy->at(0)>50 || pspmtlow1_dyenergy->at(0)>50)
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
  

  output->cd();
  for (const auto& entry : nuclei) {
    int i = std::get<0>(entry.first);
    int j = std::get<1>(entry.first);
    std::string nucl = std::get<2>(entry.first);
    output->mkdir(Form("%d%d%s", i, j, nucl.c_str()));
    output->cd(Form("%d%d%s", i, j, nucl.c_str()));
    h2decay_Vs_radius[entry.first]->Write();
    pspmtlow[entry.first]->Write();
    pspmthigh[entry.first]->Write();
    
  }

  PID_Implant->Write();
  PID_Decay->Write();
  PID_Implant_zaq->Write();
  PID_Decay_zaq->Write();
  output->Close();

}




void AnalyzeClover(int runnumber){
  // Nuclei of interest
  std::map<std::tuple<int, int, std::string>, std::string> nuclei = {
    {{3, 2, "Na"}, "32Na"},
    {{3, 3, "Na"}, "33Na"},
    {{3, 4, "Na"}, "34Na"},
    {{3, 5, "Na"}, "35Na"}
  };

  TFile* blobs = new TFile("./iongates_6mm_radius.root", "READ");
  std::map<std::tuple<int, int, std::string>, TCutG*> iongates;
  std::map<std::tuple<int, int, std::string>, TH2D*> h2clover_Vs_low, h2clover_Vs_high;
  std::map<std::tuple<int, int, std::string>, TH1D*> hclover_forward, hclover_reverse;
   std::map<std::tuple<int, int, std::string>, TH1D*> hclover_forward_implant, hclover_reverse_implant;
  std::map<std::tuple<int, int, std::string>, TH2D*> h2clover_Vs_tdiff_implant, h2clover_Vs_tdiff_decay;
  std::map<std::tuple<int, int, std::string>, TH3D*> h3clover_Vs_tdiff_decay;
  for (const auto& entry : nuclei) {
    int i = std::get<0>(entry.first);
    int j = std::get<1>(entry.first);
    std::string nucl = std::get<2>(entry.first);

    iongates[entry.first] = (TCutG*)blobs->Get(Form("%d%d%s_Decay", i, j, nucl.c_str()));

    // h2clover_Vs_low[entry.first] = new TH2D(Form("clover_vs_low_%d%d%s", i, j, nucl.c_str()),
    // 					    Form("clover_vs_low_%d%d%s", i, j, nucl.c_str()),
    // 					    4000, 0, 4000, 6500, 0, 65000);

    // h2clover_Vs_high[entry.first] = new TH2D(Form("clover_vs_high_%d%d%s", i, j, nucl.c_str()),
    // 					     Form("clover_vs_high_%d%d%s", i, j, nucl.c_str()),
    // 					     4000, 0, 4000, 6500, 0, 65000);

    hclover_forward[entry.first] = new TH1D(Form("clover_forward_%d%d%s", i, j, nucl.c_str()),
					    Form("clover_forward_%d%d%s", i, j, nucl.c_str()),
					    4000, 0, 4000);

    hclover_reverse[entry.first] = new TH1D(Form("clover_reverse_%d%d%s", i, j, nucl.c_str()),
					    Form("clover_reverse_%d%d%s", i, j, nucl.c_str()),
					    4000, 0, 4000);

    hclover_forward_implant[entry.first] = new TH1D(Form("clover_forward_implant_%d%d%s", i, j, nucl.c_str()),
					    Form("clover_forward_implant_%d%d%s", i, j, nucl.c_str()),
					    4000, 0, 4000);

    hclover_reverse_implant[entry.first] = new TH1D(Form("clover_reverse_implant%d%d%s", i, j, nucl.c_str()),
					    Form("clover_reverse_implant%d%d%s", i, j, nucl.c_str()),
					    4000, 0, 4000);

    h2clover_Vs_tdiff_implant[entry.first] = new TH2D(Form("clover_vs_tdiff_implant_%d%d%s", i, j, nucl.c_str()),
						      Form("clover_vs_tdiff_implant_%d%d%s", i, j, nucl.c_str()),
						      2000, -1000, 1000, 4000, 0, 4000);

    h2clover_Vs_tdiff_decay[entry.first] = new TH2D(Form("clover_vs_tdiff_decay_%d%d%s", i, j, nucl.c_str()),
						    Form("clover_vs_tdiff_decay_%d%d%s", i, j, nucl.c_str()),
						    2000, -1000, 1000, 4000, 0, 4000);
    h3clover_Vs_tdiff_decay[entry.first] = new TH3D(Form("clover_vs_tdiff_decay_vs_dtime%d%d%s", i, j, nucl.c_str()),
						    Form("clover_vs_tdiff_decay_vs_dtime%d%d%s", i, j, nucl.c_str()),
						    500, 0, 500, 5000, -2500, 2500, 100,-100,100);
  }

  TFile* output = new TFile(Form("/mnt/analysis/e21062/tg/batch_analysis/analyzed/clover_analysis_run%d.root", runnumber), "RECREATE");

  TChain* data = new TChain("trimmed_data");
  data->Add(TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/run-%d-sorted.root", runnumber));
  data->Add(TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/reverse_run-%d-sorted.root", runnumber));

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
  data->SetBranchAddress("pspmthigh1_dyhit", &pspmthigh1_dyhit);
  data->SetBranchAddress("pspmtlow1_dycfdfailbit", &pspmtlow1_dycfdfailbit);
  data->SetBranchAddress("pspmthigh1_dycfdfailbit", &pspmthigh1_dycfdfailbit);
  data->SetBranchAddress("clover_ecal[52]", clover_ecal);
  data->SetBranchAddress("clover_timecal[52]", clover_timecal);
  data->SetBranchAddress("clover_cfdfailbit[52]", clover_cfdfailbit);

  long int totalentries = data->GetEntries();
  std::cout << "Processing Run: " << runnumber << " with Entries: " << totalentries << '\n';

  for (long int entry = 0; entry < totalentries; ++entry) {
    data->GetEntry(entry);
    for (int k = 0; k < 52; ++k) {
      if (clover_ecal[k] > 20 && clover_timecal[k] > 20) {
	for (const auto& nucleus : nuclei) {
	  int i = std::get<0>(nucleus.first);
	  int j = std::get<1>(nucleus.first);
	  std::string nucl = nucleus.second;
	  if (corr_isimplant == 1 &&iongates[nucleus.first]->IsInside(corr_itof,corr_ide2)) {
	    if(entry<(totalentries/2)){
	      h2clover_Vs_tdiff_implant[nucleus.first]->Fill(pspmtlow1_dytime->at(0) - clover_timecal[k], clover_ecal[k]);
	      hclover_forward_implant[nucleus.first]->Fill(clover_ecal[k]);
	    }
	    else if(entry>=(totalentries/2))
	      hclover_reverse_implant[nucleus.first]->Fill(clover_ecal[k]);
	      
	    }
   
	  if (corr_isdecay == 1) {
	    for (int i = 0; i < implantlist->size(); i++) {
	      double TOF = implantlist->at(i).tof;
	      double DE2 = implantlist->at(i).de2;
	      double ixpos = implantlist->at(i).xpos;
	      double iypos = implantlist->at(i).ypos;
	      double itime = implantlist->at(i).time;
	      double dtimecal = corr_dtime - itime;
	      if (iongates[nucleus.first]->IsInside(TOF, DE2) &&sqrt(pow((ixpos-corr_dxpos),2)+pow((iypos-corr_dypos),2))<=3){
		double energy= clover_ecal[k];
		if (dtimecal<0)
		  energy=-energy;
		h3clover_Vs_tdiff_decay[nucleus.first]->Fill(pspmtlow1_dytime->at(0) - clover_timecal[k], energy,dtimecal);
	      }
	      if (iongates[nucleus.first]->IsInside(TOF, DE2) &&sqrt(pow((ixpos-corr_dxpos),2)+pow((iypos-corr_dypos),2))<=3 &&abs(dtimecal)<=30) {
	 
	    

		if(dtimecal>=0){
		  hclover_forward[nucleus.first]->Fill(clover_ecal[k]);
		  h2clover_Vs_tdiff_decay[nucleus.first]->Fill(pspmtlow1_dytime->at(0) - clover_timecal[k], clover_ecal[k]);
		  // h2clover_Vs_low[nucleus.first]->Fill(clover_ecal[k], pspmtlow1_dyenergy->at(0));
		  // h2clover_Vs_high[nucleus.first]->Fill(clover_ecal[k], pspmthigh1_dyenergy->at(0));
		}
		else if(dtimecal<0)
		  hclover_reverse[nucleus.first]->Fill(clover_ecal[k]);
	      }
	    }
	  }
	}
      }
    }
  }

  output->cd();
  for (const auto& entry : nuclei) {
    int i = std::get<0>(entry.first);
    int j = std::get<1>(entry.first);
    std::string nucl = std::get<2>(entry.first);
    output->mkdir(Form("%d%d%s", i, j, nucl.c_str()));
    output->cd(Form("%d%d%s", i, j, nucl.c_str()));
    // h2clover_Vs_low[entry.first]->Write();
    // h2clover_Vs_high[entry.first]->Write();
    hclover_forward[entry.first]->Write();
    hclover_reverse[entry.first]->Write();
    hclover_forward_implant[entry.first]->Write();
    hclover_reverse_implant[entry.first]->Write();
    h2clover_Vs_tdiff_implant[entry.first]->Write();
    h2clover_Vs_tdiff_decay[entry.first]->Write();
    h3clover_Vs_tdiff_decay[entry.first]->Write();
  }

  output->Close();
}



  
void FilteredSingleRun(int runnumber) {
  gStyle->SetOptStat(11111111);
  gSystem->Load("/projects/e21062/tg/rootAnalysis/betasort1/libTParameters.so");

   AnalyzeDecay(runnumber);
   //AnalyzeClover(runnumber);
}
