#include <sys/time.h>

void checkEfficiency(){
	time_t start, stop;

	start = time(0);

	// Progress tracking
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;

	const int nclover = 52;
	const int runnum = 1240;
	
	// Instantiate data to fill histograms
	TFile *f = new TFile(Form("/mnt/analysis/e21062/aad/e21062B/sorted/run-%d-sorted.root", runnum));
	TTree *data = (TTree*)f->Get("data");

	TH1D *ecal = new TH1D("ecal", "Detectors 5, 6, and 7", 3000, 0, 3000);

	int nentries = data->GetEntries();
	cout << "nentries = " << nentries << endl;
	int toread = nentries;
	//int toread = 1000;

	data->GetEntry(0);
	TTreeReader fReader(data);
	TTreeReaderArray<Double_t> clover_energy = {fReader, "rootout.clover.energy[52]"};

	double slope[52];
	double intercept[52];	

	
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

	cout << "Filling histograms for " << toread << " entries..." << endl;	

	int counter = 0;
	// Event loop
	while(fReader.Next() && counter < toread){
		counter++;		
		for(int j = 0; j < nclover; j++){
			if(j == 4 || j == 5 || j == 6){
				ecal->Fill(slope[j]*clover_energy[j]+intercept[j]);
			}
			
			//double energy1 = slope[j]*clover_energy[j]+intercept[j];
			//if(energy1 > 242 && energy1 < 247){
				//for(int k = 0; k < nclover; k++){
					//if(k != j)	
						//coinc->Fill(slope[k]*clover_energy[k]+intercept[k]);
				//} // End clover 2 loop
				//break;
			//} // End energy check
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

	fileName = Form("/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/run%d-60Co-det567.root", runnum);

	TFile *fout = new TFile(fileName, "RECREATE");

	ecal->Write();
	fout->Write();
	fout->Close();

	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;

}
