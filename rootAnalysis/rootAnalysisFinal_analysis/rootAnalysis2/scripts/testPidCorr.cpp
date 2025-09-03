#include <sys/time.h>

void testPidCorr(){
time_t start, stop;
	start = time(0);

	// Progress tracking
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;

	TFile *f1294 = new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/run-1294-sorted.root");
	TFile *f1294 = new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/run-1294-sorted.root");

	// Create TChain
	/*
	TChain *alldata = new TChain("data"); // chain for the data
	// List of run numbers for analysis. 63 total. 42Si runs
	std::vector<int>filelist = {
		1281, 1282 ,1283, 1284, 1285, 1286, 1287, 1288,
		1290, 1291, 1292, 1293, 1294, 1295, 1296, 1297,
		1298, 1299, 1300, 1301, 1302, 1303, 1304, 1305,
		1306, 1307, 1308, 1309};

	// Number of run files
	int totalfiles = filelist.size();

	cout << "Number of data files to be added: " << totalfiles << endl;

	// Loop over all run files and add to TChain
	for(int i=0; i<totalfiles; i++){
		stringstream filein;
		filein << "/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/run-";
		//filein << "/mnt/analysis/e21062/aad/sortedFinalReverseLongCorr/run-0";
		filein << filelist[i];
		filein << "-sorted.root";
		//filein << "-sorted-reverse.root";


		string tfile = filein.str();
	
		cout << "Adding file " << filein.str() << " to chain." << endl;

		alldata->Add(filein.str().c_str());
	}

	cout << "Data files successfully added." << endl;
	*/	

	int nentries = alldata->GetEntries();
	cout << "nentries = " << nentries << endl;
	//int toread = nentries;
	int toread = 10000000;

	cout << "------------------------------------------------" << endl;

	// Instantiate histograms
	TH2D *uncorrected = new TH2D("uncorrected", "Uncorrected PID", 1000, -1050, -850, 1500, 0, 1500);
	TH2D *corrected = new TH2D

	alldata->GetEntry(0);
	TTreeReader fReader(alldata);
	TTreeReaderValue<Double_t> de1 = {fReader, "rootout.pid.de1"};
	TTreeReaderValue<Double_t> tof = {fReader, "rootout.pid.tof"};

cout << "Filling histograms for " << toread << " entries..." << endl;	

	int counter = 0;
	// Event loop
	while(fReader.Next() && counter < toread){
		counter++;
		/*
		if(*tof != 0){
			cout << endl << "ToF = " << *tof << endl;
		}
					
		if(*de1 != 0){
			cout << endl << "de1 = " << *de1 << endl;
		}
		*/

		uncorrected->Fill(*tof, *de1);
				
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

	TCanvas *c0 = new TCanvas("c0", "c0", 800, 600);
	c0->cd();
	uncorrected->GetXaxis()->SetTitle("ToF");
	uncorrected->GetYaxis()->SetTitle("dE1");
	uncorrected->Draw("colz");

}
