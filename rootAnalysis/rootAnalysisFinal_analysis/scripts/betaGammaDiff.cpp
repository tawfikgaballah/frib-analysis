// NB: .L libTParameters.so before running!

#include <sys/time.h>

// Clover energy threshold; energies below thresh will not be added to histograms
const double thresh = 10;

void betaGammaDiff(){
	time_t start, stop;
	start = time(0);

	// Progress tracking
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;

	// Create TChain

	TChain *alldata = new TChain("data"); // chain for the data
	// List of run numbers for analysis. 63 total. 42Si runs
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
	//int toread = 100000;

	cout << "------------------------------------------------" << endl;

	// Instantiate histograms
	// NB: If any binnings are changed here, be sure to change the axis labels to reflect that!
	TH1D *BGTime = new TH1D("BGTime", "#gamma time - #beta time", 502, -0.04, 10);  // 20 ns binning
	TH2D *ecalVsBGTime = new TH2D("ecalVsBGTime", "#gamma time - #beta time versus gamma energy", 502, -0.04, 10, 4000, 1, 4001); // 20 ns, 1 keV
	TH2D *detectorVsBGTime = new TH2D("detectorVsBGTime", "#gamma time - #beta time versus clover detector number", 502, -0.04, 10, 52, 0, 52); // 20 ns, 1 clover crystal	
	

	// Fill histograms
	alldata->GetEntry(0);
	TTreeReader fReader(alldata);
	TTreeReaderArray<Double_t> clover_time = {fReader, "rootout.clover.time[52]"};
	TTreeReaderArray<Double_t> clover_ecal = {fReader, "rootout.clover.ecal[52]"};
	TTreeReaderValue<Double_t> corr_dtime = {fReader, "rootout.corr.dtime"};

	cout << "Filling histograms for " << toread << " entries..." << endl;	

	int counter = 0;
	// Event loop
	while(fReader.Next() && counter < toread){
		counter++;
		for(int j = 0; j < 52; j++){
			if(clover_ecal[j] > 10 && clover_time[j] != 0 && *corr_dtime != 0){	
				BGTime->Fill(clover_time[j]/1000-*corr_dtime*1000);
				ecalVsBGTime->Fill(clover_time[j]/1000-*corr_dtime*1000, clover_ecal[j]);
				detectorVsBGTime->Fill(clover_time[j]/1000-*corr_dtime*1000, j);
			}  // End time != 0 check
		}  // End clover loop
		
		// Progress bar
		if(counter > 0 && (counter % (int)(toread * 0.01)) == 0) {
			
			gettimeofday(&tvelapsed_c, NULL);			

			double rate = eventcounter/(((tvelapsed_c.tv_sec+tvelapsed_c.tv_usec/1.e6)-(tvelapsed_o.tv_sec+tvelapsed_o.tv_usec/1.e6)));
			double remaining = (toread - counter) / rate / 60;		

			cout << "Processed " << counter << " events. " << (int)(counter/(int)(toread*0.01)) << "% done. Current rate: " << rate << " events per second. Estimated time remaining: " << remaining << " minutes.\r" << flush;

			gettimeofday(&tvelapsed_o, NULL);
			eventcounter = 0;
 		}
		eventcounter++;	
		//	
	} // End event loop	

	string output_file_path = "/projects/e21062/aad/rootAnalysisFinal/histograms/";
	TFile *fout = new TFile(Form("%sbetaGammaTime.root",output_file_path.c_str()), "RECREATE");

	cout << "Writing output to " << output_file_path << "betaGammaTime.root" << endl;

	BGTime->GetXaxis()->SetTitle("#mus");
	BGTime->GetYaxis()->SetTitle("counts / 20 ns");
	ecalVsBGTime->GetXaxis()->SetTitle("counts / 20 ns");
	ecalVsBGTime->GetYaxis()->SetTitle("counts / 1 keV");
	detectorVsBGTime->GetXaxis()->SetTitle("counts / 20 ns");
	detectorVsBGTime->GetYaxis()->SetTitle("Detector #");

	BGTime->Write();
	ecalVsBGTime->Write();
	detectorVsBGTime->Write();
	fout->Write();
	fout->Close();
	
	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;

}
