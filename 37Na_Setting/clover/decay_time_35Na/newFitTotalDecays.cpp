// FIT FUNCTIONS
// -------------------------------------------------------------------------------------------------------
// Parameters:
//	0 Background intercept; 1 Background slope; 2 Parent HL; 3 Initial Activity; 4 Daughter HL;
//	5 Beta-n HL; 6 Beta-2n HL; 7 Pbn; 8 Pb2n

// Daughter Functions
Double_t growInDecayDaughter(const double & A, const double & pHL, const double & dHL, const double & t){
         return A*pHL/(pHL-dHL)*(pow(0.5, t/pHL)-pow(0.5, t/dHL));
}  

// Background Component
Double_t bgnd(Double_t *x, Double_t *p){
	//Comment for e16032	
	return p[0]*pow(0.5, x[0]/p[1]);
	//return p[0];

}

// Parent decays
Double_t parentDecays(Double_t *x, Double_t *p){return p[3]*pow(0.5, x[0]/p[2]);}

// Daughter decays
Double_t daughterDecays(Double_t *x, Double_t *p){return (1-p[7]-p[8])*growInDecayDaughter(p[3], p[2], p[4], x[0]);}

// Beta-n Daughter decays
Double_t betaNDecays(Double_t *x, Double_t *p){return p[7]*growInDecayDaughter(p[3], p[2], p[5], x[0]);}

// Beta-2n Daughter decays
Double_t beta2NDecays(Double_t *x, Double_t *p){return p[8]*growInDecayDaughter(p[3], p[2], p[6], x[0]);}

Double_t totalFit(Double_t *x, Double_t *p){return bgnd(x,p)+parentDecays(x,p)/+daughterDecays(x,p)+betaNDecays(x,p)+beta2NDecays(x,p);}

Double_t reverseBG(Double_t *x, Double_t *p){return p[0]*pow(0.5, x[0]/p[1]) + p[2];}

// END FIT FUNCTIONS
// -------------------------------------------------------------------------------------------------------

// This class holds all the "fixed" data for a given parent decay
class DecayData{
	public:
		string parentName;
		string daughterName;
		string betaNName;
		string beta2NName;
		double pbn;
		double pbnErr;
		double pb2n;
		double pb2nErr;
		double dHL;
		double dHLErr;
		double bnHL;
		double bnHLErr;
		double b2nHL;
		double b2nHLErr;
};

// Fill an object of class DecayData by searching the fitting data file
DecayData getDecayData(string parentName){
	DecayData data;
	data.parentName = parentName;
	
	// Get data file	
	ifstream fittingDataFile;
	cout << "Opening fitting data file..." << endl;
	fittingDataFile.open("./fittingDataFile.txt");	
	if(!fittingDataFile.is_open()){
		cout << "Error: Fitting data file not opened. Exiting" << endl;	
		exit(EXIT_FAILURE);
	}

	// These are the data we'll find in the data file, in the order we'll find them
	// Errors only needed for HL fit with systematic error calc. But they're in the datafile so we'll read them anyways.

	cout << "Data file found. Searching file for " << parentName << " parent..." << endl;


	// Find our parent in the data file
	bool flag = false;  // tracks whether we've found the parent yet
	while(!fittingDataFile.eof() && flag == false){	
		
		char temp[10];
		fittingDataFile >> temp;
		// Encounters # "comment" delimiter
		if(temp[0] == '#'){
			fittingDataFile.ignore(1000, '\n');		
			continue;
		}
		else if(strcmp(temp, parentName.c_str()) != 0){
			fittingDataFile.ignore(1000, '\n');
		}
		else{
			flag = true;
			fittingDataFile >> data.daughterName >> data.betaNName >> data.beta2NName >> data.pbn;
			fittingDataFile >> data.pbnErr >> data.pb2n >> data.pb2nErr >> data.dHL >> data.dHLErr >> data.bnHL;
			fittingDataFile >> data.bnHLErr >> data.b2nHL >> data.b2nHLErr;
			break;
		}
		
	}
	
	if(flag == true){
		cout << parentName << " data found." << endl;
		cout << "----------------------DECAY DATA------------------------" << endl;
		cout << "Daughter name = " << data.daughterName << endl;
		cout << "Beta-N daughter name = " << data.betaNName << endl;
		cout << "Beta-2N daughter name = " << data.beta2NName << endl;		
		cout << "P1n = " << data.pbn << " +/- " << data.pbnErr << endl;
		cout << "P2n = " << data.pb2n << " +/- " << data.pb2nErr << endl;
		cout << "Daughter half-life = " << data.dHL << " +/- " << data.dHLErr << " ms" << endl;
		cout << "Beta-N daughter half-life = " << data.bnHL << " +/- " << data.bnHLErr << " ms" << endl;
		cout << "Beta-2N daughter half-life = " << data.b2nHL << " +/- " << data.b2nHLErr << " ms" << endl;
		cout << "---------------------------------------------------------" << endl;
	}
	else if(flag == false){
		cout << "Error: Parent " << parentName << " not found. Exiting." << endl;
		exit(EXIT_FAILURE);
	}
	fittingDataFile.close();

	return data;
}

TF1* DrawComponent(TF1* fit, int color, Double_t(*fitFunc)(Double_t *, Double_t*),const char *name){
  double low=0;
  double high=100;
   static int line_style = 2;
   fit->GetRange(low, high);
   //Comment for e16032
   TF1 *drawFunc = new TF1(name, fitFunc, low, high,9);
   //TF1 *drawFunc = new TF1(name, fitFunc, low, high,10);
   for(int i = 0; i < fit->GetNpar();++i){
      drawFunc->SetParameter(i,fit->GetParameter(i));
   }
   drawFunc->SetLineStyle(line_style++);
   drawFunc->SetLineColor(color);
   //drawFunc->Print();
   drawFunc->Draw("same");

   return drawFunc;
}

void residuals(TF1 *fitFunc, TH1D *htime){
	
	TGraph *resid = new TGraph();

	int npts = htime->GetNbinsX();

	for(int i = 1; i <= npts; i++){
	  if(pow(htime->GetBinContent(i), 0.5)){
	    resid->AddPoint(htime->GetXaxis()->GetBinCenter(i), (htime->GetBinContent(i)-fitFunc->Eval(htime->GetXaxis()->GetBinCenter(i)))/pow(htime->GetBinContent(i), 0.5));
	  }
	}
	TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
	c2->cd();
	
	resid->GetXaxis()->SetTitle("Decay time (ms)");
	resid->GetYaxis()->SetTitle("Normalized residual");
	resid->SetMarkerStyle(3);
	resid->Draw("AP");
	TF1 *fBaseline = new TF1("fBaseline", "[0]", 0, 100);
	fBaseline->SetParameter(0, 0);
	fBaseline->SetLineColor(kRed);
	fBaseline->Draw("same");
}

double getBgHL(string parentName){
	TFile *fBG = new TFile("./../position_Vs_decaytime_37Na_33Na_Decay.root");
	
	TH2D *histBG_2d = (TH2D*)fBG->Get("Position_Vs_hIonDecayTime_37Na");
	histBG_2d->GetXaxis()->SetRangeUser(0,200);
	histBG_2d->GetYaxis()->SetRangeUser(0,3.5);
	TH1D *histBG = (TH1D*)histBG_2d->ProjectionX();
	// histBG->Rebin(5);

	int nBinsBg = histBG->GetNbinsX();
	TH1D *bgShift = new TH1D("bgShift", "bgShift", nBinsBg, 0, 100);
	for(int i = 1; i <= nBinsBg; i++){
		bgShift->SetBinContent(i, histBG->GetBinContent(i)+100);
	}

	TF1 *bgFunc = new TF1("bgFunc", reverseBG,0, 100, 3);
	//TF1 *bgFunc = new TF1("bgFunc", reverseBG, 0, 1750, 3);
	// bgFunc->SetParameters(1);

	bgShift->Fit(bgFunc, "RO");

	double bgHL = bgFunc->GetParameter(1);

	TCanvas *cBG = new TCanvas("cBG", "cBG", 950, 600);
	cBG->cd();
	bgShift->GetXaxis()->SetTitle("#beta time - implant time + 1750 (ms)");
	double binWidth =(bgShift->GetXaxis()->GetXmax() - bgShift->GetXaxis()->GetXmin())/ nBinsBg;
	bgShift->GetYaxis()->SetTitle(Form("counts / %4.2f ms", binWidth));
	bgShift->SetTitle(Form("Background HL = %4.1f ms", bgHL));
	bgShift->Draw("hist");
	bgFunc->Draw("same");

	cBG->Update();
	cBG->Modified();

	cout << "Background half-life = " << bgHL << " ms" << endl;
	cout << "Background fit is drawn. Enter any number to continue: ";
	int blah;
	cin >> blah;	

	delete bgFunc;
	delete bgShift;
	delete histBG;
	delete cBG;
	fBG->Close();

	return bgHL;
}


void newFitTotalDecays(){
	// First, which parent should we look at?
  	string parentName;
	cout << "Enter name of parent ion: ";
	cin >> parentName;

	DecayData data = getDecayData(parentName);

	// Comment for e16032
	//double bgHL = getBgHL(parentName);
	double bgHL = 0;

	// Comment for e16032
	TFile *f = new TFile("./../position_Vs_decaytime_37Na_33Na_Decay.root");
	// TH1D *htime = (TH1D*)f->Get("Positionn_Vs_hIonDecayTime_37Na");
	TH2D *htime_2d = (TH2D*)f->Get("Position_Vs_hIonDecayTime_37Na");
	htime_2d->GetXaxis()->SetRangeUser(0,200);
	htime_2d->GetYaxis()->SetRangeUser(0,3.5);
	TH1D *htime = (TH1D*)htime_2d->ProjectionX();
	//TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/bDecay/d%s.root", parentName.c_str()));
	//TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/d%s-e16032.root", parentName.c_str()));
	//TH1D *htime = (TH1D*)f->Get("allDecays");

	int npts = htime->GetNbinsX();
	double binWidth = htime->GetXaxis()->GetBinWidth(2);
	double newBinWidth;

	TCanvas *c = new TCanvas("c", "c", 950, 600);
	c->cd();
	gStyle->SetOptStat(0);
	htime->SetTitle(Form("%s total decay curve                ", parentName.c_str()));
	htime->GetYaxis()->SetTitle(Form("counts / %4.2f ms", binWidth));
	htime->SetLineColor(kBlack);
	htime->Draw("PE");

	c->Modified();
	c->Update();

	cout << "Current bin width = " << binWidth << " ms. Enter new bin width, in ms: ";
	cin >> newBinWidth;

	double NGroups = newBinWidth / binWidth;
	if(static_cast<int>(NGroups) == NGroups && static_cast<int>(npts/newBinWidth) == npts/newBinWidth){	
		htime->Rebin(NGroups);
	}
	else{
		cout << "Error: newBinWidth must be an integer multiple of " << binWidth << " and must go evenly into " << npts << ". Continuing without rebinning." << endl;
		newBinWidth = binWidth;
	}

	npts = htime->GetNbinsX();
	for (int i = 1; i <= npts; i++){
		htime->SetBinError(i, pow(htime->GetBinContent(i), 0.5));
	}


	//Comment for e16032
	TF1 *fitFunc = new TF1("fitFunc", totalFit, 0, 100, 9);
	//TF1 *fitFunc = new TF1("fitFunc", totalFit, 0, 200, 10);
	fitFunc->SetParName(0, "Background activity");
	fitFunc->SetParName(1, "Background HL");
	fitFunc->SetParName(2, "Parent HL");
	fitFunc->SetParName(3, "Initial activity");
	fitFunc->SetParName(4, "Daughter HL");
	fitFunc->SetParName(5, "Beta-n HL");
	fitFunc->SetParName(6, "Beta-2n HL");
	fitFunc->SetParName(7, "Pbn");
	fitFunc->SetParName(8, "Pb2n");	
	//For e16032
	//fitFunc->SetParName(9, "Background constant");

	//Comment for e16032
	fitFunc->SetParameter(0, .5);
	fitFunc->SetParameter(1, 300);	
	//fitFunc->FixParameter(1, bgHL);
	//fitFunc->FixParameter(0, 181.001*NGroups);
	//fitFunc->FixParameter(1, 1577.23);
	//fitFunc->FixParameter(9, 1861.72*NGroups);
	fitFunc->SetParameter(2, 3.96);
	fitFunc->SetParameter(3, 5);
	fitFunc->FixParameter(4, data.dHL);
	fitFunc->FixParameter(5, data.bnHL);
	fitFunc->FixParameter(6, data.b2nHL);
	fitFunc->FixParameter(7, data.pbn);
	fitFunc->FixParameter(8, data.pb2n);

	cout << "Drawing initial guess..." << endl;

	gPad->SetLogy();
	htime->GetYaxis()->SetRangeUser(1, 2*htime->GetBinContent(1));
	htime->GetYaxis()->SetTitle(Form("counts / %4.2f 4ms", newBinWidth));
	fitFunc->Draw("same");

	c->Update();
	c->Modified();

	int blah;
	cout << "Enter any number to fit: ";
	cin >> blah;

	htime->Fit(fitFunc, "R");
	htime->SetTitle(Form("%s total decay curve - HL = %5.2f ms", parentName.c_str(), fitFunc->GetParameter(2)));

	TF1* parentFunc = DrawComponent(fitFunc, kRed, parentDecays, parentName.c_str());
	TF1* daughterFunc = DrawComponent(fitFunc, kGreen+1, daughterDecays, data.daughterName.c_str());
	TF1* betaNFunc = DrawComponent(fitFunc, kMagenta, betaNDecays, data.betaNName.c_str());
	TF1* beta2NFunc = DrawComponent(fitFunc, kCyan+1, beta2NDecays, data.beta2NName.c_str());
	TF1* bgndFunc = DrawComponent(fitFunc, kBlue-7, bgnd, "Background");

	TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg->AddEntry(htime, "Data", "l");	
	leg->AddEntry(parentFunc, parentName.c_str(), "l");
	leg->AddEntry(daughterFunc, data.daughterName.c_str(), "l");
	leg->AddEntry(betaNFunc, data.betaNName.c_str(), "l");
	leg->AddEntry(beta2NFunc, data.beta2NName.c_str(), "l");
	leg->AddEntry(bgndFunc, "Bgnd", "l");
	leg->Draw("same");

	c->Update();
	c->Modified();
	
	residuals(fitFunc, htime);

	double chi2NDF = fitFunc->GetChisquare() / fitFunc->GetNDF();

	double iA = fitFunc->GetParameter(3) / newBinWidth;
	double diA = fitFunc->GetParError(3) / newBinWidth;
	double pHL = fitFunc->GetParameter(2);
	double dpHL = fitFunc->GetParError(2);
	double nParentDecays = iA * pHL / log(2) * (1 - pow(2, -100/pHL));
	double errParentDecays = sqrt(pow(nParentDecays * diA / iA , 2) + pow(iA, 2)*pow(dpHL, 2)*pow(1/log(2) - pow(2, -100/pHL)*(1/log(2)+100/pHL), 2));
	double nDaughterDecays = (1-data.pbn-data.pb2n)*iA*pHL/log(2)/(pHL-data.dHL)*(data.dHL*(pow(2, -100/data.dHL)-1)-pHL*(pow(2, -100/pHL)-1));
	double nDaughterNDecays = data.pbn*iA*pHL/log(2)/(pHL-data.bnHL)*(data.bnHL*(pow(2, -100/data.bnHL)-1)-pHL*(pow(2, -100/pHL)-1));
	double nDaughter2NDecays = data.pb2n*iA*pHL/log(2)/(pHL-data.b2nHL)*(data.b2nHL*(pow(2, -100/data.b2nHL)-1)-pHL*(pow(2, -100/pHL)-1));

//	0 Background intercept; 1 Background slope; 2 Parent HL; 3 Initial Activity; 4 Daughter HL;
//	5 Beta-n HL; 6 Beta-2n HL; 7 Pbn; 8 Pb2n

	// WRITE PARAMS
	cout << "------------------------RESULTS-------------------------" << endl;
	cout << "Initial activity = " << fitFunc->GetParameter(3) << " +/- " << fitFunc->GetParError(3) << " counts / " << newBinWidth << " ms" << endl;
	cout << "Parent HL = " << fitFunc->GetParameter(2) << " +/- " << fitFunc->GetParError(2) << " ms" << endl;
	cout << "Bgnd initial activity = " << fitFunc->GetParameter(0) << " +/- " << fitFunc->GetParError(0) << " counts / " << newBinWidth << " ms" << endl;
	cout << "Bgnd HL = " << fitFunc->GetParameter(1) << " +/- " << fitFunc->GetParError(1) << " ms" << endl;
	cout << "--------------------NUMBER OF DECAYS--------------------" << endl;
	cout << "Parent decays = " << nParentDecays << " +/- " << errParentDecays << endl;
	cout << "Daughter decays = " << nDaughterDecays << endl;
	cout << "Beta-N daughter decays = " << nDaughterNDecays << endl;
	cout << "Beta-2N daughter decays = " << nDaughter2NDecays << endl;	
	cout << "Chi2/NDF = " << chi2NDF << endl;	
	cout << "--------------------------------------------------------" << endl;

}
