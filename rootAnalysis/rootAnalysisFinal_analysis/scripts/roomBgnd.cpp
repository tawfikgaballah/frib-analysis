#include <sys/time.h>

void roomBgnd(){
time_t start, stop;
	start = time(0);

	// Progress tracking
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;	
		
	string tfile = "/projects/e21062/aad/rootAnalysisFinal/histograms/bDecay/roomBgnd.root";

	TFile *fout = new TFile(tfile.c_str(),"UPDATE");
		
	TChain *ch = new TChain("data"); // chain for the data
	// List of run numbers for analysis. 63 total. List from TChaine21062RSL.C, 42Si runs
	std::vector<int>filelist = {327};

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
		ch->Add(filein.str().c_str());
	}

	cout << "Data files successfully added." << endl;
		
	int nentries = ch->GetEntries();
	cout << "nentries = " << nentries << endl;
	int toread = nentries;
	//int toread = 10000000;

	cout << "Saving output to " << tfile << endl;

	cout << "------------------------------------------------" << endl;

	ch->GetEntry(0);
	TTreeReader fReader(ch);
	TTreeReaderArray<Double_t> clover_ecal = {fReader, "rootout.clover.ecal[52]"};
		
	// Instantiate histograms
	TH1D *ecal = new TH1D("roomBgnd", "Room background clover spectrum", 8000, 1, 8001);

	cout << "Filling histograms for " << toread << " entries..." << endl;
		
	int counter = 0;
	while(fReader.Next() && counter < toread){
		counter++;
		for(int j = 0; j < 52; j++){
			if(clover_ecal[j] > 10)	
				ecal->Fill(clover_ecal[j]);
		}
		
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
	}

		
	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();
	ecal->GetXaxis()->SetTitle("keV");
	ecal->GetYaxis()->SetTitle("counts / keV");
	ecal->Draw("hist");

	ecal->Write();
	fout->Write();
	fout->Close();	
	
	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;


}
