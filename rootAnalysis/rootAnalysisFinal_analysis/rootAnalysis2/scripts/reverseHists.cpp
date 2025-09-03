/* Script to make all the histograms I typically want to look at for a beta-delayed spectrum. This includes a plain clover spectrum, a 2D energy vs time clover spectrum, and a coincidence spectrum. The root output files will then be named after the gating isotope, and the histograms will be accessed from within those files. */

// NB: .L libTParameters.so before running!

#include <sys/time.h>

// Clover energy threshold; energies below thresh will not be added to histograms
const double thresh = 10;

void reverseHists(){
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
		1281, 1282, 1283, 1284, 1285, 1286, 1287, 1288,
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
		1430, 1431, 1432, 1433};

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
	//int toread = 100000000;

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

	// Instantiate histograms
	// NB: If any binnings are changed here, be sure to change the axis labels to reflect that!
	TH1D *ecal = new TH1D("clover_ecal", Form("Clover energy, gated on %s decays (reverse correlated)", gateName.c_str()), 8000, 1, 8001);  // 1 keV binning	
	TH1D *allDecays = new TH1D("allDecays", Form("%s total decay curve, reverse correlated", gateName.c_str()), 1750, 0, 1750);  // 1 ms binning	

	double timeCorr = 1750;
	double posCorr = 2;

	cout << "Correlation window = " << timeCorr << " ms and " << posCorr << " mm radius" << endl;

	// Fill histograms
	alldata->GetEntry(0);
	TTreeReader fReader(alldata);
	TTreeReaderValue<std::vector<TPID>> implantlist = {fReader, "implantlist"};	
	TTreeReaderArray<Double_t> clover_ecal = {fReader, "rootout.clover.ecal[52]"};
	TTreeReaderArray<Double_t> clover_time = {fReader, "rootout.clover.time[52]"};
	TTreeReaderValue<Double_t> corr_dtime = {fReader, "rootout.corr.dtime"};
	TTreeReaderValue<Double_t> corr_dxpos = {fReader, "rootout.corr.dxpos"};
	TTreeReaderValue<Double_t> corr_dypos = {fReader, "rootout.corr.dypos"};
	TTreeReaderValue<Int_t> corr_flag = {fReader, "rootout.corr.flag"};

	cout << "Filling histograms for " << toread << " entries..." << endl;	

	int counter = 0;
	// Event loop
	while(fReader.Next() && counter < toread){
		counter++;

		int len = implantlist->size();		

		if(len > 0){
			
			//for(int i = 0; i < implantlist->size(); i++){
				//cout << "Implant " << i << ": time = " << *corr_dtime - implantlist->at(i).time << endl;
			//}
	

			double ix = implantlist->at(0).xpos;
			double iy = implantlist->at(0).ypos;	
			double dx = *corr_dxpos;
			double dy = *corr_dypos;
			double distance = pow(pow(dx-ix, 2) + pow(dy-iy, 2), 0.5);

			if(gate->IsInside((implantlist->at(len-1)).tof, (implantlist->at(len-1)).de2)){
				if(distance < posCorr && (*corr_dtime - (implantlist->at(len-1)).time) < timeCorr){
					for(int j = 0; j < 52; j++){
						if(clover_ecal[j] > thresh){	
							ecal->Fill(clover_ecal[j]);
						}  // End clover 1 thresh check
					}  // End clover 1 loop
					
					allDecays->Fill(abs(*corr_dtime - (implantlist->at(len-1)).time));
				}
			}  // End decay gate check
		} // End implant existence check
		
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
	fileOutPath << "/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/reverse/d";
	fileOutPath << gateName;	
	fileOutPath << "-";
	fileOutPath << timeCorr;
	fileOutPath << "ms-";
	fileOutPath << posCorr;
	fileOutPath << "mm-reverse.root";

	TFile *fileOut = new TFile(fileOutPath.str().c_str(), "RECREATE");
	

	cout << "Writing output to " << fileOutPath.str() << endl;

	// Draw histograms
	TCanvas *c0 = new TCanvas("c0", "c0", 800, 600);
	c0->cd();
	ecal->GetXaxis()->SetTitle("keV");
	ecal->GetYaxis()->SetTitle("counts / 1 keV");
	ecal->Draw("hist");

	TCanvas *c3 = new TCanvas("c3", "c3", 800, 600);
	c3->cd();
	allDecays->GetYaxis()->SetTitle("counts / 1 ms");
	allDecays->GetXaxis()->SetTitle("abs(#beta time - implant time (ms))");
	allDecays->Draw("hist");

	// Uncomment to look at histograms before the program ends
	
	gPad->Modified();
  	gPad->Update();
  	gPad->WaitPrimitive();
	

	ecal->Write();
	allDecays->Write();
	fileOut->Write();
	fileOut->Close();
	gates->Close();

	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;

}
