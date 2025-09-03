#include <sys/time.h>

void decayCurve(){

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
		1281, 1282, 1283, 1284, 1285, 1286, 1287, 1288,
		1290, 1291, 1292, 1293, 1294, 1295, 1296, 1297, 
		1298, 1299, 1300, 1301, 1302, 1303, 1304, 1305, 
		1306, 1307, 1308, 1309, 1310, 1311, 1312, 1313, 
		1314, 1315, 1316, 1317, 1318, 1319, 1320, 1321, 
		1322, 1323, 1324, 1325,	1326, 1327, 1328, 1329, 
		1330, 1331, 1333, 1334, 1336, 1337, 1392, 1393, 
		1394, 1395, 1396, 1397, 1398, 1399, 1400, 1401, 
		1402, 1403, 1404, 1405, 1406, 1407, 1408, 1409, 
		1410, 1411, 1412, 1413, 1414, 1415, 1416, 1417, 
		1418, 1419, 1420, 1421, 1422, 1424, 1425, 1426, 
		1427, 1428, 1429, 1430, 1431, 1432, 1433};

	// Number of run files
	int totalfiles = filelist.size();

	cout << "Number of data files to be added: " << totalfiles << endl;

	// Loop over all run files and add to TChain
	for(int i=0; i<totalfiles; i++){
		stringstream filein;
		filein << "/mnt/analysis/e21062/aad/e21062B/reverse/run-";
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
	//int toread = 1000;

	cout << "------------------------------------------------" << endl;

	string gateName;
	cout << "Enter name of ion for beta gating (e.g. 24F, 31Na, etc.): ";
	cin >> gateName;

	// Get gates
	
	cout << "Retrieving " << gateName << " decay gate.." << endl;
	TFile *gates = new TFile("/projects/e21062/aad/e21062B/rootAnalysisFinal/gates/gates.root");
	// Get map - gate number to isotope name	
	ifstream gate_map;
	gate_map.open("/projects/e21062/aad/e21062B/rootAnalysisFinal/gates/gate_isotope_map.txt");	
	if(!gate_map.is_open()){
		cout << "Error: Gate map file not opened. Exiting" << endl;	
		exit(EXIT_FAILURE);
	}

	// First, figure out which isotope is in which gate
	bool flag = false;  // tracks whether we've found the gate yet.
	string gateNum;
	string prev = "";
	while(!gate_map.eof() && flag == false){	
		char temp[10];
		gate_map >> temp;
		// Encounters # "comment" delimiter
		if(temp[0] == '#'){
			gate_map.ignore(1000, '\n');		
			continue;
		}
		else if(strcmp(temp, gateName.c_str()) == 0){
			flag = true;
			gateNum = prev;
		}
		else{
			prev = temp;		
		}
	}
	if(flag == true)
		cout << gateName << " gate found. gateNum = " << gateNum << endl;
	else if (flag == false){
		cout << "Error: Gate not found. Exiting." << endl;
		exit(EXIT_FAILURE);
	}
	gate_map.close();

	string gateVar = "gate" + gateNum;
	TCutG *gate = (TCutG*)gates->Get(gateVar.c_str());

	TH1D *allDecays = new TH1D("allDecays", Form("%s total decay curve", gateName.c_str()), 500, 0, 500);  // 2 ms binning

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
		//if(len > 0){		
		for(int i = 0; i < len; i++){
			if(gate->IsInside((implantlist->at(i)).tof, (implantlist->at(i)).de2)){
				allDecays->Fill(abs(*corr_dtime - (implantlist->at(i)).time));
			}  // End decay gate check
		} // End implant loop

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

	stringstream fileOutPath;
	fileOutPath << "/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/bDecay/d";
	fileOutPath << gateName;
	fileOutPath << "-test-allimplantst-rvs.root";

	TFile *fileOut = new TFile(fileOutPath.str().c_str(), "RECREATE");

	cout << "Writing output to " << fileOutPath.str() << endl;

	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();
	allDecays->GetYaxis()->SetTitle("counts / 1 ms");
	allDecays->GetXaxis()->SetTitle("#beta time - implant time");
	allDecays->Draw("hist");

	allDecays->Write();
	fileOut->Write();
	fileOut->Close();
	gates->Close();

	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;

}
