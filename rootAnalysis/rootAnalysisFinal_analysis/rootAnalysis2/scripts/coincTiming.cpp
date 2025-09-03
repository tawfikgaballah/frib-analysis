#include <sys/time.h>

void coincTiming(){
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
		237, 238, 241, 244, 246, 247, 248, 249, 250 ,251, 252, 253, 
		254, 255, 256, 257, 261, 262, 263, 264, 266, 267, 268, 269,
		270, 271, 280, 283, 284, 285, 286, 287, 288, 290, 292, 294, 
		295, 296, 298, 299, 300, 301, 302, 303, 304, 306, 309, 310, 
		311, 312, 313, 314, 315, 317, 318, 319, 320, 321, 322, 323, 
		324, 325, 326};

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

		alldata->Add(filein.str().c_str());
	}

	cout << "Data files successfully added." << endl;
	
	int nentries = alldata->GetEntries();
	cout << "nentries = " << nentries << endl;
	int toread = nentries;
	//int toread = 1000000;

	cout << "------------------------------------------------" << endl;

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

	// Instantiate histograms
	TH1D* decayTime = new TH1D("decayTime", "decayTime", 400, 0, 100);

	// Fill histograms
	alldata->GetEntry(0);
	TTreeReader fReader(alldata);
	TTreeReaderValue<std::vector<TPID>> implantlist = {fReader, "implantlist"};	
	TTreeReaderArray<Double_t> clover_ecal = {fReader, "rootout.clover.ecal[52]"};
	TTreeReaderValue<Double_t> corr_dtime = {fReader, "rootout.corr.dtime"};

	cout << "Filling histograms for " << toread << " entries..." << endl;	

	int counter = 0;
	// Event loop
	while(fReader.Next() && counter < toread){
		counter++;
		if(implantlist->size() > 0){
			if(gate->IsInside((implantlist->at(0)).tof, (implantlist->at(0)).de2)){
				for(int j = 0; j < 52; j++){
					if(clover_ecal[j] > 441 && clover_ecal[j] < 445){	
						for(int k = j+1; k < 52; k++){
							if(clover_ecal[k] > 242 && clover_ecal[k] < 245){
								decayTime->Fill(*corr_dtime-(implantlist->at(0)).time);
							}  // End 2nd gamma check - 243
						}  // End clover 2 loop
					}  // End 1st gamma check - 443
					else if(clover_ecal[j] > 242 && clover_ecal[j] < 245){
						for(int k = j+1; k < 52; k++){
							if(clover_ecal[k] > 441 && clover_ecal[k] < 445){
								decayTime->Fill(*corr_dtime-(implantlist->at(0)).time);
							}  // End 2nd gamma check - 443
						}  // End clover 2 loop					
					}  // End 1st gamma check - 243
				}  // End clover 1 loop
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

	TCanvas *c = new TCanvas("c0", "c0", 800, 600);
	c->cd();
	decayTime->SetTitle("^{28}Ne decay gate, 243 + 443 #gamma-#gamma coincidence gate");
	decayTime->GetXaxis()->SetTitle("Decay time, ms");
	decayTime->GetYaxis()->SetTitle("Counts / 0.25 ms");
	decayTime->Draw("hist");

	gPad->Modified();
  	gPad->Update();
  	gPad->WaitPrimitive();

	gates->Close();

	stop = time(0);
	cout << "Done processing " << toread << " entries after " << difftime(stop, start)/60 << " minutes." << endl;


}
