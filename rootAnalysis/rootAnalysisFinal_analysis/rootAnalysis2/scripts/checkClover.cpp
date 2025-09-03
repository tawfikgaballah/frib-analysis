#include <vector>
#include "/projects/e21062/aad/e21062B/rootAnalysisFinal/include/TPID.h"
#include <sys/time.h>

void checkClover(){
	time_t start, stop;
	start = time(0);

	// Progress tracking
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;
	
	TChain *ch = new TChain("data");
	
	int runNum;
	cout << "Which run number? ";
	cin >> runNum;	
	
	// Number of run files
	int totalfiles = 1;

	cout << "Number of data files to be added: " << totalfiles << endl;

	stringstream filein;
	filein << "/mnt/analysis/e21062/aad/e21062B/sorted/run-";
	filein << runNum;
	filein << "-sorted.root";
	cout << "Adding file " << filein.str() << " to chain." << endl;
	ch->Add(filein.str().c_str());

	cout << "Data files successfully added." << endl;

	int nentries = ch->GetEntries();
	cout << "nentries = " << nentries << endl;
	int toread = nentries;
	//int toread = 100000;

	cout << "------------------------------------------------" << endl;

	ch->GetEntry(0);
	TTreeReader fReader(ch);
	TTreeReaderArray<Double_t> clover_ecal = {fReader, "rootout.clover.ecal[52]"};

	// Instantiate histograms
  	//TH2D *ecal_vs_nclover = new TH2D("ecal_vs_nclover", Form(" %s clover energy versus detector number", gateName.c_str()), 8000, 1, 8001, 52, 0, 52);
	TH2D *ecal_vs_nclover = new TH2D("ecal_vs_nclover", "Clover energy versus detector number", 3000, 1, 3001, 52, 0, 52);

	cout << "Filling histograms for " << toread << " entries..." << endl;	

	int counter = 0;
	while(fReader.Next() && counter < toread){
		counter++;
			for(int j = 0; j < 52; j++){	
				if(clover_ecal[j] > 10) {
					ecal_vs_nclover->Fill(clover_ecal[j], j);
				} // end clover energy check					
			} // end clover loop
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

	} // end event loop

	// Draw histograms
	TCanvas *c0 = new TCanvas("c0", "c0", 800, 600);
	c0->cd();
	ecal_vs_nclover->GetXaxis()->SetTitle("counts / 1 keV");
	ecal_vs_nclover->GetYaxis()->SetTitle("Detector number");
	ecal_vs_nclover->GetXaxis()->SetRangeUser(2500, 2700);
	ecal_vs_nclover->Draw("colz");

	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;

}
