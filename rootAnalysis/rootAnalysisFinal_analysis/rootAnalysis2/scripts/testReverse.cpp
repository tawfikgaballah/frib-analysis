#include <sys/time.h>

void testReverse(){

time_t start, stop;
	start = time(0);

	// Progress tracking
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;

	// Create TChain

	TChain *alldata = new TChain("data"); // chain for the data
	// List of run numbers for analysis
	std::vector<int>filelist = {
		/*1281,*/ 1282/*, 1283, 1284, 1285, 1286, 1287, 1288,
		1290, 1291, 1292, 1293, 1294, 1295, 1296, 1297, 
		1298, 1299, 1300, 1301, 1302, 1303, 1304, 1305, 
		1306, 1307, 1308, 1309, 1310, 1311, 1312, 1313, 
		1314, 1315, 1316, 1317, 1318, 1319, 1320, 1321, 
		1322, 1323, 1324, 1325,	1326, 1327, 1328, 1329, 
		1330, 1331, 1333, 1334, 1336, 1337, 1392, 1393, 
		1394, 1396, 1397, 1399, 1400, 1401, 1403, 1404, 
		1405, 1406, 1407, 1408, 1409, 1410, 1411, 1412, 
		1413, 1414, 1415, 1416, 1417, 1418, 1419, 1420, 
		1421, 1422, 1424, 1425, 1426, 1427, 1428, 1429, 
		1430, 1431, 1432, 1433*/};

	// Number of run files
	int totalfiles = filelist.size();

	cout << "Number of data files to be added: " << totalfiles << endl;

	// Loop over all run files and add to TChain
	for(int i=0; i<totalfiles; i++){
		stringstream filein;
		filein << "/mnt/analysis/e21062/aad/e21062B/reverse/run-";
		filein << filelist[i];
		filein << "-sorted.root";
		//filein << "-sorted-reverse.root";


		string tfile = filein.str();
	
		cout << "Adding file " << filein.str() << " to chain." << endl;

		alldata->Add(filein.str().c_str());
	}

	cout << "Data files successfully added." << endl;
	
	int nentries = alldata->GetEntries();
	cout << "nentries = " << nentries << endl;
	//int toread = nentries;
	int toread = 1000;

	cout << "------------------------------------------------" << endl;

	TFile *gates = new TFile("/projects/e21062/aad/e21062B/rootAnalysisFinal/gates/gates.root");

	// PID
	string gateVar = "gate0";
	TCutG *gate = (TCutG*)gates->Get(gateVar.c_str());

	TH1D *decays = new TH1D("decays", "decays", 1750, 0, 1750);

	// Fill histograms
	alldata->GetEntry(0);
	TTreeReader fReader(alldata);
	TTreeReaderValue<std::vector<TPID>> implantlist = {fReader, "implantlist"};
	TTreeReaderValue<Double_t> corr_dtime = {fReader, "rootout.corr.dtime"};

	cout << "Filling histograms for " << toread << " entries..." << endl;	

	int counter = 0;
	// Event loop
	while(fReader.Next() && counter < toread){
		counter++;

		int len = implantlist->size();

		if(len > 0){
			if(gate->IsInside((implantlist->at(len-1)).tof, (implantlist->at(len-1)).de2)){
				cout << "corr.dtime = " << *corr_dtime << endl;
				for(int i= 0; i < len; i++){
					cout << "implantlist[" << i << "].time = " << implantlist->at(i).time << ", beta time - implant time = " << *corr_dtime - (implantlist->at(i)).time << endl;
				}
				decays->Fill(abs(*corr_dtime - (implantlist->at(len-1)).time));
			}  // End decay gate check
		} // End implant existence check
		// Progress bar
		if(counter > 0 && (counter % (int)(toread * 0.01)) == 0) {
			
			gettimeofday(&tvelapsed_c, NULL);			

			double rate = eventcounter/(((tvelapsed_c.tv_sec+tvelapsed_c.tv_usec/1.e6)-(tvelapsed_o.tv_sec+tvelapsed_o.tv_usec/1.e6)));
			double remaining = (toread - counter) / rate / 60;		

			//cout << "Processed " << counter << " events. " << (int)(counter/(int)(toread*0.01)) << "% done. Current rate: " << rate << " events per second. Estimated time remaining: " << remaining << " minutes.\r" << flush;

			gettimeofday(&tvelapsed_o, NULL);
			eventcounter = 0;
 		}
		eventcounter++;	
		//
	} // End event loop

	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();
	decays->GetYaxis()->SetTitle("counts / 1 ms");
	decays->GetXaxis()->SetTitle("abs(#beta time - implant time (ms))");
	decays->Draw("hist");
}
