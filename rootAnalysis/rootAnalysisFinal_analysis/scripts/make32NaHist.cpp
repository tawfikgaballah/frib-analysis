// NB: Need to load gates first!
#include <string>

void make32NaHist(){
	
	time_t start, stop;
	start = time(0);
	
	TChain *alldata = new TChain("data"); // chain for the data
	// List of run numbers for analysis. 63 total. List from TChaine21062RSL.C, 42Si runs
	std::vector<int>filelist = {
		237, 238, 241, 244, 246, 247, 248, 249, 250 ,251, 252, 253, 
		254, 255, 256, 257, 261, 262, 263, 264, 266, 267, 268, 269,
		270, 271, 280, 283, 284, 285, 286, 287, 288, 290, 292, 294, 
		295, 296, 298, 299, 300, 301, 302, 303, 304, 306, 309, 310, 
		311, 312, 313, 314, 315, 317, 318, 319, 320, 321, 322, 323, 
		324, 325, 326};

	// Number of run files
	int totalfiles = filelist.size();

	cout << "Number of data files to be added: " << totalfiles << endl;

	// Loop over all run files and add to TChain
	for(int i=0; i<totalfiles; i++){
		stringstream filein;
		filein << "/mnt/analysis/e21062/aad/sortedFinal/run-0";
		filein << filelist[i];
		filein << "-sorted.root";

		string tfile = filein.str();
	
		cout << "Adding file " << filein.str() << " to chain." << endl;

		alldata->Add(filein.str().c_str());
	}

	cout << "Data files successfully added." << endl;
	
	int nentries = alldata->GetEntries();
	cout << "nentries = " << nentries << endl;
	int toread = nentries;
	//int toread = 1000000;

	cout << "------------------------------------------------" << endl;

	string output_file_path = "/projects/e21062/aad/rootAnalysisFinal/histograms/implantCorr/";
  	string output_file_name = "i32Na.root";
  	string output_file = output_file_path + output_file_name;
	TFile *fout = new TFile(output_file.c_str(),"RECREATE");

	cout << "Writing output histograms to " << output_file << endl;

	// Get beta decay parameters from TChain
	TROOTDataOut *bdecay = new TROOTDataOut();
	alldata->SetBranchAddress("rootout", &bdecay);
	
	// Set gating variables
	gi32Na->SetVarX("(bdecay->corr.gtof)");
  gi32Na->SetVarY("(bdecay->corr.gde2)");
	i32Na_2->SetVarX("(bdecay->corr.itof)");
  i32Na_2->SetVarY("(bdecay->corr.ide2)");
  
  // Instantiate histograms
  TH2D *ecal_vs_t_raw = new TH2D("ecal_vs_t_raw", "Clover energy versus time since implant", 1240, -10, 300, 4000, 1, 4001);
  TH2D *ecal_vs_t_32Na = new TH2D("ecal_vs_t_32Na", "Clover energy versus time since implant, 32Na gate", 1240, -10, 300, 4000, 1, 4001);
  TH1D *ecal_raw = new TH1D("ecal_raw", "Clover energy", 8000, 1, 8001);
  TH1D *ecal_32Na = new TH1D("ecal_32Na", "Clover energy, 32Na gate", 8000, 1, 8001);
  TH1D *ecal_32Na_delayed = new TH1D("ecal_32Na_delayed", "Clover energy, 32Na gate, delayed gammas only", 8000, 1, 8001);
	TH1D *time_raw = new TH1D("time_raw", "Clover time minus implant time", 1240, -10, 300);
	TH1D *time_32Na = new TH1D("time_32Na", "Clover time minus implant time, 32Na gate", 1240, -10, 300);
	TH1D *time_32Na_223 = new TH1D("time_32Na_223", "Clover time minus implant time, 32Na gate, 223 keV gamma gate", 1240, -10, 300);
	TH1D *time_32Na_401 = new TH1D("time_32Na_401", "Clover time minus implant time, 32Na gate, 401 keV gamma gate", 1240, -10, 300);
	TH1D *time_32Na_223_401 = new TH1D("time_32Na_223_401", "Clover time minus implant time, 32Na gate, 223 & 401 keV gamma gates", 1240, -10, 300);
	TH2D *gg_coinc_32Na = new TH2D("gg_coinc_32Na", "#gamma-#gamma coincidences", 8000, 1, 8001, 8000, 1, 8001);

	cout << "Filling histograms for " << toread << " entries..." << endl;
	for(int i = 0; i < toread; i++){
		alldata->GetEntry(i);
		
		// Raw histograms
		for(int j = 0 ; j < 52; j++){
			if(bdecay->clover.ecal[j] > 0){
				double tdiff = (bdecay->clover.time[j] - bdecay->pin02.time)/1000;
				if(tdiff < 10 && tdiff > 0){
					ecal_vs_t_raw->Fill(tdiff, bdecay->clover.ecal[j]);
					time_raw->Fill(tdiff);
				}
				else if(bdecay->corr.gitdiff > 0 && bdecay->corr.gitdiff*1000 < 300){
					ecal_vs_t_raw->Fill(bdecay->corr.gitdiff*1000, bdecay->clover.ecal[j]);
					time_raw->Fill(bdecay->corr.gitdiff*1000);
				}
				ecal_raw->Fill(bdecay->clover.ecal[j]);
			}
		}
		
		// Gated - inside event window
		if(i32Na_2->IsInside(bdecay->corr.itof, bdecay->corr.ide2)){
			for(int j = 0; j < 52; j++){
				double tdiff = (bdecay->clover.time[j] - bdecay->pin02.time)/1000;
				if(bdecay->clover.time[j] != 0 && bdecay->pin02.time !=0 && bdecay->clover.ecal[j] > 0){
					ecal_vs_t_32Na->Fill(tdiff, bdecay->clover.ecal[j]);
					ecal_32Na->Fill(bdecay->clover.ecal[j]);
					time_32Na->Fill(tdiff);
					if(tdiff > 0.5){
						ecal_32Na_delayed->Fill(bdecay->clover.ecal[j]);
					}		
					if(bdecay->clover.ecal[j] >= 222 && bdecay->clover.ecal[j] < 225){
						time_32Na_223->Fill(tdiff);
					}
					if(bdecay->clover.ecal[j] >= 399 && bdecay->clover.ecal[j] < 403){
						time_32Na_401->Fill(tdiff);
					}
					if((bdecay->clover.ecal[j] >= 222 && bdecay->clover.ecal[j] < 225) || (bdecay->clover.ecal[j] >= 399 && bdecay->clover.ecal[j] < 403)){
						time_32Na_223_401->Fill(tdiff);
					}
				}
				
				// Fill g-g coincidence plot
				double thresh = 10;
				if(bdecay->clover.ecal[j] > thresh){
					for(int k = j+1; k < 52; k++){
						if(bdecay->clover.ecal[k] > thresh){
							gg_coinc_32Na->Fill(bdecay->clover.ecal[j], bdecay->clover.ecal[k]);
							gg_coinc_32Na->Fill(bdecay->clover.ecal[k], bdecay->clover.ecal[j]);
						}
					}
				}
			}		
		}
		
		// Gated - outside event window
		else if(gi32Na->IsInside(bdecay->corr.gtof, bdecay->corr.gde2)){
			for(int j = 0; j < 52; j++){
				if(bdecay->corr.gitdiff > 0 && bdecay->clover.ecal[j] > 0){
					ecal_vs_t_32Na->Fill(bdecay->corr.gitdiff*1000, bdecay->clover.ecal[j]);
					ecal_32Na->Fill(bdecay->clover.ecal[j]);
					if(bdecay->corr.gitdiff*1000 > 0.5 && bdecay->corr.gitdiff*1000 < 50){
						ecal_32Na_delayed->Fill(bdecay->clover.ecal[j]);	
					}
					time_32Na->Fill(bdecay->corr.gitdiff*1000);
					if(bdecay->clover.ecal[j] >= 222 && bdecay->clover.ecal[j] < 225){
						time_32Na_223->Fill(bdecay->corr.gitdiff*1000);
					}
					if(bdecay->clover.ecal[j] >= 399 && bdecay->clover.ecal[j] < 403){
						time_32Na_401->Fill(bdecay->corr.gitdiff*1000);
					}
					if((bdecay->clover.ecal[j] >= 222 && bdecay->clover.ecal[j] < 225) || (bdecay->clover.ecal[j] >= 399 && bdecay->clover.ecal[j] < 403)){
						time_32Na_223_401->Fill(bdecay->corr.gitdiff*1000);
					}
				}

				// Fill g-g coincidence plot
				double thresh = 10;
				if(bdecay->clover.ecal[j] > thresh){
					for(int k = j+1; k < 52; k++){
						if(bdecay->clover.ecal[k] > thresh & bdecay->corr.gitdiff*1000 < 67){
							gg_coinc_32Na->Fill(bdecay->clover.ecal[j], bdecay->clover.ecal[k]);
							gg_coinc_32Na->Fill(bdecay->clover.ecal[k], bdecay->clover.ecal[j]);
						}
					}
				}
			}
		}

		// Progress bar
		if(i > 0 && (i % (int)(toread * 0.01)) == 0) {
			cout << "Processed " << i << " events. " << (int)(i/(int)(toread*0.01)) << "% done.\r" << flush;
 		}
		//
	}

  fout->Write();
  fout->Close();
	
	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;

}
