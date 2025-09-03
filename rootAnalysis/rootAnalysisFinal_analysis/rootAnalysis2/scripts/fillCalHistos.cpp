#include <sys/time.h>

void fillCalHistos(){
	time_t start, stop;

	start = time(0);

	// Progress tracking
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;

	const int nclover = 52;
	const int runnum = 1240;

	// Set checkCal = true to load in a cal file and check if it worked; false to fill raw histos
	bool checkCal = true;
	
	// Instantiate data to fill histograms
	TFile *f = new TFile(Form("/mnt/analysis/e21062/aad/e21062B/sorted/run-%d-sorted.root", runnum));
	TTree *data = (TTree*)f->Get("data");

	TH1D *energy[nclover];
	TH1D *energyAll;
	
	if(checkCal == true){
		energyAll = new TH1D("energyAll", "Raw Clover Energy (All crystals)", 3000, 0, 3000);
		for(int j = 0; j < nclover; j++)
			energy[j] = new TH1D(Form("energy%d", j), Form("Raw Clover %d Energy", j), 3000, 0, 3000);	
	}
	else{
		energyAll = new TH1D("energyAll", "Raw Clover Energy (All crystals)", 10000, 0, 15000);
		for(int j = 0; j < nclover; j++)
			energy[j] = new TH1D(Form("energy%d", j), Form("Raw Clover %d Energy", j), 10000, 0, 15000);	
	}


	int nentries = data->GetEntries();
	cout << "nentries = " << nentries << endl;
	int toread = nentries;
	//int toread = 1000;

	data->GetEntry(0);
	TTreeReader fReader(data);
	TTreeReaderArray<Double_t> clover_energy = {fReader, "rootout.clover.energy[52]"};

	double slope[52];
	double intercept[52];	

	if(checkCal == true){
		// Get calibration parameters
		ifstream fcal;
		//fcal.open(Form("/projects/e21062/aad/e21062B/rootAnalysisFinal/cal-final-forreal/CloverInit_%d.txt", runnum));
		fcal.open("/projects/e21062/aad/e21062B/rootAnalysisFinal/cal-final-forreal/CloverInit_1238.txt");

		int iclover = 0;

		while(!fcal.eof()){
			char temp[10];
			fcal >> temp;
			fcal >> intercept[iclover];
			fcal >> slope[iclover];
			iclover++;
		}
	}
	else{
		for(int iclover = 0; iclover < nclover; iclover++){
			slope[iclover] = 1;
			intercept[iclover] = 0;
		}
	}

	cout << "Filling histograms for " << toread << " entries..." << endl;	

	int counter = 0;
	// Event loop
	while(fReader.Next() && counter < toread){
		counter++;		
		for(int j = 0; j < nclover; j++){
			energyAll->Fill(slope[j]*clover_energy[j]+intercept[j]);
			energy[j]->Fill(slope[j]*clover_energy[j]+intercept[j]);
		}  // End clover 1 loop
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
		// End progress bar
	} // End event loop
	cout << endl << "Done filling" << endl;	

	TString fileName;

	if(checkCal == true)
		fileName = Form("/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/run%d-60Co-calibrated.root", runnum);
	else
		fileName = Form("/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/run%d-60Co.root", runnum);
	TFile *fout = new TFile(fileName, "RECREATE");

	for(int j = 0; j < nclover; j++)
		energy[j]->Write();
	energyAll->Write();
	fout->Write();
	fout->Close();

	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;

}
