void addPIDCorr(){
time_t start, stop;
	start = time(0);

	// Progress tracking
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;

	int runNum = 1282;

	// Get TOF Offset & dE Scaling 

	Double_t TOFoffset = 0.;
	Double_t deScale = 1.;

	std::ifstream pidcorr;
	pidcorr.open("/projects/e21062/aad/e21062B/rootAnalysisFinal/pid_corr.txt");
	if(pidcorr.is_open()){
		bool flag = false;
		while(!pidcorr.eof()){
			char temp[10];
			pidcorr >> temp;		
			// Encounters # "comment" delimiter
			if(temp[0] == '#'){
				pidcorr.ignore(1000, '\n');
				continue;
			}
			else if(std::stof(temp) == std::stof(runnumber)){
				flag = true;
				pidcorr >> temp;
				TOFoffset = std::stof(temp); // temp, convert to double
				pidcorr >> temp;
				deScale = std::stof(temp); // temp, convert to double
				break;
			}
		}
		
		if(flag == false){
			std::cout << "Error: No PID Correction found for run " << runnumber << ". Exiting." << std::endl;
			exit(1);
			//std::cout << "Warning: No PID Correction found for run " << runnumber << ". Setting TOF offset = 0 and deScale = 1." << std::endl;
		}
		
		else{
			std::cout << "Found PID corrections. TOF offset = " << TOFoffset << " and deScale = " << deScale << std::endl;
		}
		
	}
	else{
		std::cout << "Error: PID Corrections file not open. Exiting." << std::endl;
		exit(1);
	}

	//
	// END Get TOF Offset & dE Scaling
	
	stringstream fileInName;
	fileInName << "/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/run-";
	fileInName << runNum;
	fileInName << "-sorted.root";	
	
	TFile *fileIn = new TFile(fileInName.str().c_str());

	cout << "Added file " << fileInName.str() << endl;

	TTree *treeIn = (TTree*)fileIn->Get("data");
	TTree *treeOut = treeIn->CloneTree();

	int nentries = treeIn->GetEntries();
	cout << "nentries = " << nentries << endl;
	int toread = nentries;
	//int toread = 100000;

	treeIn->GetEntry(0);
	TTreeReader fReader(treeIn);
	TTreeReaderValue<Double_t> de1 = {fReader, "rootout.pid.de1"};
	TTreeReaderValue<Double_t> tof = {fReader, "rootout.pid.tof"};

	TH2D *uncorrected = new TH2D("uncorrected", Form("Run %d Uncorrected PID", runNum), 500, -1000, -900, 1300, 0, 1300);
	TH2D *corrected = new TH2D("corrected", Form("Run %d Corrected PID", runNum), 500, -1000, -900, 1300, 0, 1300);
	
	cout << "Filling histograms for " << toread << " entries..." << endl;	

	int counter = 0;
	// Event loop
	while(fReader.Next() && counter < toread){
		counter++;
		
		uncorrected->Fill(*tof, *de1);
		corrected->Fill(*tof-tofOffset, *de1*deScale);
				
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
	}  // End event loop

	stringstream fileOutName;
	fileOutName << "/projects/e21062/aad/e21062B/rootAnalysisFinal/histograms/run";
	fileOutName << runNum;
	fileOutName << "-pid.root";

	TFile *fileOut = new TFile(fileOutName.str().c_str(), "RECREATE");

	TCanvas *c = new TCanvas("c", "c", 1200, 600);
	c->cd(); c->Divide(2, 1);
	c->cd(1);
	gPad->SetLogz();
	uncorrected->GetXaxis()->SetTitle("ToF");
	uncorrected->GetYaxis()->SetTitle("dE1");
	uncorrected->Draw("colz");
	c->cd(2);
	gPad->SetLogz();
	corrected->GetXaxis()->SetTitle("ToF");
	corrected->GetYaxis()->SetTitle("dE1");
	corrected->Draw("colz");

	/*
	gPad->Modified();
  	gPad->Update();
  	gPad->WaitPrimitive();
	*/
	
	corrected->Write();
	fileOut->Write();
	fileOut->Close();

	fileIn->Close();
	



}
