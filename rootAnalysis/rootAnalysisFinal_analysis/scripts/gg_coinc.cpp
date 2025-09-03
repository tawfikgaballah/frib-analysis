#include "/projects/e21062/aad/rootanalysis/include/TPID.h"
#include "/projects/e21062/aad/rootanalysis/src/TPID.cpp"
#include <vector>

// Load gates first!
// To change gate: load whichever gate you want, but make sure you replace every single instance of the old gate name with the new gate name! Even in stuff like names of histograms. 
void gg_coinc(){
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
		filein << "/mnt/analysis/e21062/aad/sorted_fixed/run-0";
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
	//int toread = 10000000;

	cout << "------------------------------------------------" << endl;

	string output_file_path = "/projects/e21062/aad/rootanalysis/root_files/bdelayed_hists/";
  	string output_file_name = "31Na_coinc.root";
  	string output_file = output_file_path + output_file_name;
	TFile *fout = new TFile(output_file.c_str(),"RECREATE");

	cout << "Writing output histograms to " << output_file << endl;

	alldata->GetEntry(0);
	TTreeReader fReader(alldata);
	TTreeReaderValue<std::vector<TPID>> implantlist = {fReader, "implantlist"};	
	TTreeReaderArray<Double_t> clover_ecal = {fReader, "rootout.clover.ecal[52]"};
	
	// Instantiate histograms
  	TH2D *gg_coinc = new TH2D("gg_coinc", "Gamma-gamma coincidences in 31Na correlated beta decays", 2000, 1, 4001, 4000, 1, 4001);

	cout << "Filling histograms for " << toread << " entries..." << endl;
	
	int counter = 0;
	while(fReader.Next() && counter < toread){

		counter++;
		
		if(implantlist->size() > 0){
			if(i31Na->IsInside((implantlist->at(0)).tof, (implantlist->at(0)).de2)){
				for(int j = 0; j < 52; j++){	
					// Fill g-g coincidence plot
					double thresh = 10;
					if(clover_ecal[j] > thresh){
						for(int k = j+1; k < 52; k++){
							if(clover_ecal[k] > thresh){
								gg_coinc->Fill(clover_ecal[j], clover_ecal[k]);
								gg_coinc->Fill(clover_ecal[k], clover_ecal[j]);
							}
						}
					}
				}
			}
		}
		
		// Progress bar
		if(counter > 0 && (counter % (int)(toread * 0.01)) == 0) {
			cout << "Processed " << counter << " events. " << (int)(counter/(int)(toread*0.01)) << "% done.\r" << flush;
 		}
		//	
	}

	fout->Write();
	fout->Close();

	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;

}
