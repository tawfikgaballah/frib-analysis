#include <string>
#include <fstream>
#include <sys/time.h>

void implantCorrHists(){
	
	time_t start, stop;
	start = time(0);

	// Progress tracking
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;
	
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
		filein << "/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resortedNewCal37Na/run-";
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
	cout << "Enter name of ion for implant gating (e.g. 24F, 31Na, etc.): ";
	cin >> gateName;
	
	cout << "Retrieving " << gateName << " implant gate.." << endl;
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

	// Get beta decay parameters from TChain
	TROOTDataOut *bdecay = new TROOTDataOut();
	alldata->SetBranchAddress("rootout", &bdecay);	

	bool beyondEvtWin = false;
	double upper, lower;
	int nBins;

	if(beyondEvtWin==false){
		cout << "Including only gammas within the event window." << endl;
		upper = 10;  // us
		lower = -10;   // us
		nBins = 320;
	}
	else{
		cout << "Including beyond event window correlations." << endl;
		upper = 1000;  // us
		lower = -10;   // us
		nBins = 1010;
	}
	
	// Histograms
	TH2D *ecal_vs_t = new TH2D("ecal_vs_t", Form("Clover energy versus time since implant, %s gated", gateName.c_str()), nBins, lower, upper, 4000, 1, 4001);	

	double binWidth = (upper-lower)/nBins;

  	// Fill histograms
  	cout << "Filling histograms for " << toread << " entries..." << endl;
	for(int i = 0; i < toread; i++){
		alldata->GetEntry(i);
		//for(int ig = 0; ig < ngates; ig++){
		// Gated - inside event window
		if(gate->IsInside(bdecay->corr.itof, bdecay->corr.ide2)){
			for(int ic = 0; ic < 52; ic++){
				double tdiff = (bdecay->clover.time[ic] - bdecay->pin02.time)/1000;
				if(bdecay->clover.time[ic] != 0 && bdecay->pin02.time !=0 && bdecay->clover.ecal[ic] > 0){
					ecal_vs_t->Fill(tdiff, bdecay->clover.ecal[ic]);
				}
			}
		}
		// Gated - outside event window
		else if(beyondEvtWin==true && gate->IsInside(bdecay->corr.gtof, bdecay->corr.gde2)){
			for(int ic = 0; ic < 52; ic++){
				if(bdecay->corr.gitdiff > 0 && bdecay->clover.ecal[ic] > 0){
					ecal_vs_t->Fill(bdecay->corr.gitdiff*1000, bdecay->clover.ecal[ic]);
				}
			}
		}
		//}

				// Progress bar
		if(i > 0 && (i % (int)(toread * 0.01)) == 0) {
			
			gettimeofday(&tvelapsed_c, NULL);			

			double rate = eventcounter/(((tvelapsed_c.tv_sec+tvelapsed_c.tv_usec/1.e6)-(tvelapsed_o.tv_sec+tvelapsed_o.tv_usec/1.e6)));
			double remaining = (toread - i) / rate / 60;		

			cout << "Processed " << i << " events. " << (int)(i/(int)(toread*0.01)) << "% done. Current rate: " << rate << " events per second. Estimated time remaining: " << remaining << " minutes.\r" << flush;

			gettimeofday(&tvelapsed_o, NULL);
			eventcounter = 0;
 		}
		eventcounter++;	
		//
	}


	stringstream outFilePath;;
	outFilePath << "/projects/e21062/aad/e21062B/rootAnalysisFinal/histograms/implantCorr/i";
	outFilePath << gateName;
	if(beyondEvtWin == true)
		outFilePath << "-beyond-evt-win.root";
	else
		outFilePath << ".root";

 	TFile *fout = new TFile(outFilePath.str().c_str(),"RECREATE");

	cout << "Writing output histograms to " << outFilePath.str() << endl;

	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();
	ecal_vs_t->GetXaxis()->SetTitle(Form("counts / %4.2f #mus", binWidth));
	ecal_vs_t->GetYaxis()->SetTitle("counts / 1 keV");
	ecal_vs_t->Draw("colz");

	ecal_vs_t->Write();
	fout->Write();
	fout->Close();

	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;

}
