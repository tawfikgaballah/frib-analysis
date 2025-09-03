#include <string>

// fitFuncExp and fitFuncConst refer to the type of background function used, constant or exponentially decaying
double funcDecay(double *x, double *p){return (p[0]*pow(0.5, x[0]/p[1]));}
double funcConstBgnd(double *x, double *p){return (p[0]);}
double fitFuncExp(double *x, double *p){return (p[0]*pow(0.5, x[0]/p[1]) + p[2]*pow(0.5, x[0]/p[3]));}
double fitFuncConst(double *x, double *p){return (p[0]*pow(0.5, x[0]/p[1]) + p[2]);}

void do_fit(TCanvas *c, TH1 *htime, TF1 *fitFunc, TF1 *bgnd, TF1 *decay, int newBinWidth, int npars){

	double THalf;
	cout << "Guess the decay half-life (ms): ";
	cin >> THalf;

	double bgndHeight;
	cout << "Guess the background height (counts/bin): ";
	cin >> bgndHeight;

	double N0 = htime->GetBinContent(1);
	cout << "Guessing N0 = " << N0 << " counts/bin" << endl;

	if(npars == 4){
		double bgTHalf = 1500;
		cout << "Guessing background half-life = " << bgTHalf << " ms" << endl;
		fitFunc->SetParameters(N0, THalf, bgndHeight, bgTHalf);
		fitFunc->SetParLimits(3, 50, 1000000000);
	}

	else
		fitFunc->SetParameters(N0, THalf, bgndHeight);
		
	fitFunc->SetLineColor(kRed);
	fitFunc->SetLineStyle(9);
	fitFunc->Draw("same");
	c->Update();
	c->Modified();

	int blah;
	cout << "Enter any number to fit: ";
	cin >> blah;

	htime->Fit(fitFunc, "QRWL");
	//htime->Fit(fitFunc, "QR");

	fitFunc->SetLineStyle(1);

	

	if(npars == 4)
		bgnd->SetParameters(fitFunc->GetParameter(2), fitFunc->GetParameter(3));
	else
		bgnd->SetParameter(0, fitFunc->GetParameter(2));
	bgnd->SetLineColor(kGreen);
	bgnd->SetLineStyle(1);
	bgnd->Draw("same");

	decay->SetParameters(fitFunc->GetParameter(0), fitFunc->GetParameter(1));
	decay->SetLineColor(kBlue);
	decay->SetLineStyle(1);
	decay->Draw("same");

	TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg->AddEntry(decay, "Decay", "l");
	leg->AddEntry(bgnd, "Background", "l");
	leg->AddEntry(fitFunc, "Decay + Bgnd", "l");
	leg->Draw("same");
	

	c->Update();
	c->Modified();

	// Counting statistics
	double fN0 = fitFunc->GetParameter(0);
	double eN0 = fitFunc->GetParError(0);
	double fHalfLife = fitFunc->GetParameter(1);
	double eHalfLife = fitFunc->GetParError(1);

	double NDecays = fN0 / newBinWidth * fHalfLife / log(2) * (1 - pow(2, -100 / fHalfLife));
	double NBgnd;

	if(npars == 3){
		double fBgnd = fitFunc->GetParameter(2);
		double eBgnd = fitFunc->GetParError(2);
		NBgnd = fBgnd * 100 / newBinWidth;
	}
	

	// WRITE PARAMS
	cout << "--------------------RESULTS---------------------" << endl;
	cout << "N0 = " << fitFunc->GetParameter(0) << " +/- " << fitFunc->GetParError(0) << " counts / " << newBinWidth << " ms" << endl;
	cout << "Half-life = " << fitFunc->GetParameter(1) << " +/- " << fitFunc->GetParError(1) << " ms" << endl;
	if(npars == 4){
		cout << "Bgnd N0 = " << fitFunc->GetParameter(2) << " +/- " << fitFunc->GetParError(2) << " counts / " << newBinWidth << " ms" << endl;
		cout << "Bgnd Half-life = " << fitFunc->GetParameter(3) << " +/- " << fitFunc->GetParError(3) << " ms" << endl;
	
	}
	else{
		cout << "Bgnd = " << fitFunc->GetParameter(2) << " +/- " << fitFunc->GetParError(2) << " counts / " << newBinWidth << " ms" << endl;
		cout << "NBgnd = " << NBgnd << " +/- " << fitFunc->GetParError(2) * 100 / newBinWidth << " counts" << endl;	
	}
	cout << "NDecays = " << NDecays << " counts" << endl;	
	cout << "------------------------------------------------" << endl;
		
}

void half_life(){
	time_t start, stop;
	start = time(0);

	// GET HISTOGRAMS
	// For beta delayed gammas

	string gate;

	cout << "Enter the decay gate (e.g. 24F, 42Si, etc.): ";
	cin >> gate;

	cout << "Reading 2D energy vs. decay time for the " << gate << " gate." << endl;


	
	TFile *f = new TFile(Form("/projects/e21062/aad/e21062B/rootAnalysisFinal/histograms/bDecay/d%s.root", gate.c_str()));
	TH2D *ecal_vs_t = (TH2D*)f->Get("clover_ecal_vs_time");
	
	// For implant correlated gammas
	/*
	TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/implantCorr/i%s.root", gate.c_str()));
	TH1D *htime = (TH1D*)f->Get("time_32Na_223_401");
	*/
	//TH2D *ecal_vs_t = (TH2D*)f->Get("h");	
	

	// For adding gates
	/*
	TH1D *htime1 = ecal_vs_t->ProjectionX("htime1", 145, 148);
	TH1D *htime2 = ecal_vs_t->ProjectionX("htime2", 172, 174);
	TH1D *htime3 = ecal_vs_t->ProjectionX("htime3", 1675, 1678);
	//TH1D *htime4 = ecal_vs_t->ProjectionX("htime4", 516, 519);
	//TH1D *htime5 = ecal_vs_t->ProjectionX("htime5", 202, 204);
	TH1D *htime = new TH1D("htime", "htime", 400, 0, 100);

	TList *list = new TList;
	list->Add(htime1);
	list->Add(htime2);
	//list->Add(htime3);
	//list->Add(htime4);
	//list->Add(htime5);
	htime->Merge(list);	
	//htime->Add(htime1, htime2);

	int low = 0;
	int high = 0;	
	*/

	// USUAL PROCEDURE
	
	bool endflag = true;
	while (endflag == true){

		
		int low, high;


		cout << "Enter the projection lower limit (integer value, in keV): ";
		cin >> low;
		cout << "Enter the projection upper limit (integer value, in keV): ";
		cin >> high;	

		TH1D *htime = ecal_vs_t->ProjectionX("htime",low, high-1); 	
		

		// SET BIN ERRORS
		int npts = htime->GetNbinsX();
		for(int i = 1; i <=npts; i++){
				htime->SetBinError(i, pow(htime->GetBinContent(i), 0.5));
		}

		double binWidth =(htime->GetXaxis()->GetXmax() - htime->GetXaxis()->GetXmin())/(htime->GetXaxis()->GetNbins());

		// INITIAL DRAW
		TCanvas *c = new TCanvas("c", "c", 800, 600);
		c->cd(); 	
		gStyle->SetOptStat(0);

		//htime->GetXaxis()->SetRangeUser(-10, 300);
		//htime->GetYaxis()->SetRangeUser(0, 70);
		htime->SetMarkerStyle(7);


		// For implant correlated gammas
		/*
		htime->GetXaxis()->SetTitle("Time of #gamma-ray since implant (#mus)");
		//htime->SetTitle(Form("%s ion gate, %d - %d keV gamma gate", gate.c_str(), low, high));
		htime->SetTitle("^{32}Na ion gate, 223 + 401 keV #gamma-ray gates");
		htime->GetYaxis()->SetTitle(Form("Counts / %5.2f us", binWidth));
		*/
		// For beta delayed gammas
			
		htime->GetXaxis()->SetTitle("Time of beta decay since implant (ms)");
		htime->GetYaxis()->SetTitle(Form("Counts / %5.2f ms", binWidth));
		htime->SetTitle(Form("%s decay gate, %d - %d keV gamma gate", gate.c_str(), low, high));	

		htime->Draw("PE");
		c->Update();
		c->Modified();
		
		double newBinWidth;
		cout << "Currently binned at " << binWidth << " ms/bin. Enter the new bin width, in ms: ";				
		cin >> newBinWidth;
		double NGroups = newBinWidth / binWidth;
		if(static_cast<int>(NGroups) == NGroups && static_cast<int>(npts/newBinWidth) == npts/newBinWidth){	
			htime->Rebin(NGroups);
			//ecal_vs_t->Rebin2D(NGroups, 1);
		
		}
		else{
			cout << "Error: newBinWidth must be an integer multiple of " << binWidth << " and must go evenly into " << npts << ". Continuing without rebinning." << endl;
			newBinWidth = binWidth;
		}

		// RESET BIN ERRORS
		int npts2 = htime->GetNbinsX();
		for(int i = 1; i <=npts2; i++){
				htime->SetBinError(i, pow(htime->GetBinContent(i), 0.5));
		}

		//htime->GetYaxis()->SetTitle(Form("Counts / %5.2f #mus", newBinWidth));
		htime->GetYaxis()->SetTitle(Form("Counts / %5.2f ms", newBinWidth));
		c->Update();
		c->Modified();

		// FIT
		// Fit limits, not plot limits
		double upper, lower;
		lower = 0;	
		upper = npts*binWidth;

		auto *fitConst = new TF1("fitConst", fitFuncConst, lower, upper, 3);
		fitConst->SetParName(0, "N0");
		fitConst->SetParName(1, "Half-life");
		fitConst->SetParName(2, "Bgnd");
		//fitConst->SetParameters(10, 20, 2);	

		auto *fitExp = new TF1("fitExp", fitFuncExp, lower, upper, 4);
		fitExp->SetParName(0, "N0");
		fitExp->SetParName(1, "Half-life");
		fitExp->SetParName(2, "Bgnd N0");
		fitExp->SetParName(3, "Bgnd Half-life");
		//sum->SetParameters(10, 20, 2);

		auto *fConst = new TF1("fConst", funcConstBgnd, lower, upper, 1);
		fConst->SetParName(0, "Constant");

		auto *fDecay = new TF1("fDecay", funcDecay, lower, upper, 2);
		fDecay->SetParName(0, "N0");
		fDecay->SetParName(1, "Half-life");

		auto *fDecayBgnd = new TF1("fDecayBgnd", funcDecay, lower, upper, 2);
		fDecayBgnd->SetParName(0, "Bgnd N0");
		fDecayBgnd->SetParName(1, "Bgnd Half-life");

		int bgndType;
		cout << "Enter 1 to use a constant background, or any other number to use an exponentially decaying background: ";
		cin >> bgndType;

		if(bgndType == 1)
			do_fit(c, htime, fitConst, fConst, fDecay, newBinWidth, 3);
		else
			do_fit(c, htime, fitExp, fDecayBgnd, fDecay, newBinWidth, 4);

		int blurg;
		cout << "Enter 1 to do another fit, or any other number to quit: ";
		cin >> blurg;
		if (blurg != 1)
			endflag = false;
	}

	stop = time(0);
	cout << "Done after " << difftime(stop, start)/60 << " minutes." << endl;

}
