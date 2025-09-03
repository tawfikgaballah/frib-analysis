#include <vector>
#include "/projects/e21062/aad/e21062B/rootAnalysisFinal/include/TPID.h"
#include <sys/time.h>

void cloverCal(){
	time_t start, stop;
	start = time(0);

	// Progress tracking
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;
	
	TChain *ch = new TChain("data");
	
	std::vector<int>filelist = {
		1281, 1282, 1283, 1284, 1285, 1286, 1287, 1288,
		1290, 1291, 1292, 1293, 1294, 1295, 1296, 1297,
		1298, 1299, 1300, 1301, 1302, 1303, 1304, 1305,
		1306, 1307, 1308, 1309, 1310, 1311, 1312, 1313,
		1314, 1315, 1316, 1317, 1318, 1319, 1320, 1321,
		1325, 1326, 1327, 1328, 1329, 1331, 1333, 1334,
		1335};

	// Number of run files
	int totalfiles = filelist.size();

	cout << "Number of data files to be added: " << totalfiles << endl;

	// Loop over all run files and add to TChain
	for(int i=0; i<totalfiles; i++){
		stringstream filein;
		filein << "/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/run-";
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
	//int toread = 100000;

	cout << "------------------------------------------------" << endl;

	/*
	string gateName;
	cout << "Enter name of ion for beta gating (e.g. 24F, 31Na, etc.): ";
	cin >> gateName;

	// Get gates
	
	cout << "Retrieving " << gateName << " decay gate.." << endl;
	TFile *gates = new TFile("/projects/e21062/aad/rootAnalysisFinal/gates/gates.root");
	// Get map - gate number to isotope name	
	ifstream gate_map;
	gate_map.open("/projects/e21062/aad/rootAnalysisFinal/gates/gate_isotope_map.txt");	
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
	*/
	ch->GetEntry(0);
	TTreeReader fReader(ch);
	TTreeReaderArray<Double_t> clover_ecal = {fReader, "rootout.clover.ecal[52]"};
	TTreeReaderValue<std::vector<TPID>> implantlist = {fReader, "implantlist"};

	// Instantiate histograms
  	//TH2D *ecal_vs_nclover = new TH2D("ecal_vs_nclover", Form(" %s clover energy versus detector number", gateName.c_str()), 8000, 1, 8001, 52, 0, 52);
	TH2D *ecal_vs_nclover = new TH2D("ecal_vs_nclover", "Clover energy versus detector number", 8000, 1, 8001, 52, 0, 52);

	cout << "Filling histograms for " << toread << " entries..." << endl;	

	int counter = 0;
	while(fReader.Next() && counter < toread){
		counter++;
		
		if(implantlist->size() > 0){
			//if(gate->IsInside((implantlist->at(0)).tof, (implantlist->at(0)).de2)){
				for(int j = 0; j < 52; j++){	
					if(clover_ecal[j] > 10) {
						ecal_vs_nclover->Fill(clover_ecal[j], j);
					} // end clover energy check					
				} // end clover loop
			//} // end gate check		
		} // end implant size check
		
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

	string output_file_path = "/projects/e21062/aad/rootAnalysisFinal/histograms/bDecay/";
	//TFile *fout = new TFile(Form("%sd%s-clover-ecal-vs-detector.root",output_file_path.c_str(), gateName.c_str()), "RECREATE");
	TFile *fout = new TFile(Form("%sungated-clover-ecal-vs-detector.root",output_file_path.c_str()), "RECREATE");

	//cout << "Writing output to " << output_file_path << "d" << gateName << "-clover-ecal-vs-detector.root" << endl;

	// Draw histograms
	TCanvas *c0 = new TCanvas("c0", "c0", 800, 600);
	c0->cd();
	ecal_vs_nclover->GetXaxis()->SetTitle("counts / 1 keV");
	ecal_vs_nclover->GetYaxis()->SetTitle("Detector number");
	ecal_vs_nclover->Draw("colz");

	ecal_vs_nclover->Write();
	fout->Write();
	fout->Close();
	//gates->Close();

	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;

}
