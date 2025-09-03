#include <sys/time.h>
#include <TRandom3.h>

// FIT FUNCTIONS
// -------------------------------------------------------------------------------------------------------
// Parameters:
//	0 Background activity; 1 Background HL; 2 Parent HL; 3 Initial Activity; 4 Daughter HL;
//	5 Beta-n HL; 6 Beta-2n HL; 7 Pbn; 8 Pb2n; 9 Background constant

// Daughter Functions
Double_t growInDecayDaughter(const double & A, const double & pHL, const double & dHL, const double & t){
         return A*pHL/(pHL-dHL)*(pow(0.5, t/pHL)-pow(0.5, t/dHL));
}  

// Background Component
Double_t bgnd(Double_t *x, Double_t *p){
	//Comment for e16032	
	//return p[0]*pow(0.5, x[0]/p[1]);
	return p[0]*pow(0.5, x[0]/p[1])+p[9];
}

// Parent decays
Double_t parentDecays(Double_t *x, Double_t *p){return p[3]*pow(0.5, x[0]/p[2]);}

// Daughter decays
Double_t daughterDecays(Double_t *x, Double_t *p){return (1-p[7]-p[8])*growInDecayDaughter(p[3], p[2], p[4], x[0]);}

// Beta-n Daughter decays
Double_t betaNDecays(Double_t *x, Double_t *p){return p[7]*growInDecayDaughter(p[3], p[2], p[5], x[0]);}

// Beta-2n Daughter decays
Double_t beta2NDecays(Double_t *x, Double_t *p){return p[8]*growInDecayDaughter(p[3], p[2], p[6], x[0]);}

Double_t totalFit(Double_t *x, Double_t *p){return bgnd(x,p)+parentDecays(x,p)+daughterDecays(x,p)+betaNDecays(x,p)+beta2NDecays(x,p);}

Double_t reverseBG(Double_t *x, Double_t *p){return p[0]*pow(0.5, x[0]/p[1]) + p[2];}

double gaussian(double *x, double *p){return p[0]*exp(-0.5*pow((x[0]-p[1])/p[2], 2));}
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
	fittingDataFile.open("/projects/e21062/aad/rootAnalysisFinal/scripts/fittingDataFile.txt");	
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
		cout << "Pn = " << data.pbn << " +/- " << data.pbnErr << endl;
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

double getBgHL(string parentName){
	
	TFile *fBG = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/reverse/d%s-reverse.root", parentName.c_str()));
	TH1D *histBG = (TH1D*)fBG->Get("allDecays");

	histBG->Rebin(2);

	int nBinsBg = histBG->GetNbinsX();
	TH1D *bgShift = new TH1D("bgShift", "bgShift", nBinsBg, 0, 1750);
	for(int i = 1; i <= nBinsBg; i++){
		bgShift->SetBinContent(i, histBG->GetBinContent(i)+1750);
	}

	TF1 *bgFunc = new TF1("bgFunc", reverseBG, 200, 1750, 3);
	bgFunc->SetParameters(10000, 300, 1000);

	bgShift->Fit(bgFunc, "QN");

	TCanvas *cBG = new TCanvas("cBG", "cBG", 800, 600);
	cBG->cd();
	bgShift->GetXaxis()->SetTitle("#beta time - implant time + 1750 (ms)");
	double binWidth =(bgShift->GetXaxis()->GetXmax() - bgShift->GetXaxis()->GetXmin())/ nBinsBg;
	bgShift->GetYaxis()->SetTitle(Form("counts / %f ms", binWidth));
	bgShift->Draw("hist");
	bgFunc->Draw("same");

	cBG->Update();
	cBG->Modified();

	double bgHL = bgFunc->GetParameter(1);

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

double getChiSquare(TH1D* hist, TF1* func){

	//Comment for e16032
	//double nBins = hist->GetXaxis()->GetNbins();
	double nBins = 100/2;  //Rebinned

	double chiSquare = 0;
	for (int i = 1; i <= nBins; i++){
		double x = hist->GetXaxis()->GetBinCenter(i);
		double yFit = func->Eval(x);
		double yReal = hist->GetBinContent(i);
		double yRealErr = pow(hist->GetBinContent(i), 0.5);
	
		// First is my chiSquare def'n and second is the one from Tawfik's code
		chiSquare += pow(yReal-yFit, 2)/abs(yFit);
		//chiSquare += pow((yReal-yFit)/yRealErr, 2);
	}

	double nPar = func->GetNpar();
	double chiSquareNDF = chiSquare / (nBins - nPar);

	//Comment for e16032
	//return chiSquareNDF;
	return chiSquare;
}


vector<double> fitSample(DecayData data, double bgHL, bool toDraw){

	// Get histogram
	//Comment for e16032	
	//TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/bDecay/d%s.root", data.parentName.c_str()));
	TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/d%s-e16032.root", data.parentName.c_str()));
	TH1D *htime = (TH1D*)f->Get("allDecays");
	
	//Comment for e16032
	htime->Rebin(2);

	//Comment for e16032
	//TF1 *fitFunc = new TF1("Total Fit", totalFit, 0, 100, 9);
	TF1 *fitFunc = new TF1("Total Fit", totalFit, 0, 100, 10);
	
	int npts = htime->GetNbinsX();
	for(int i = 1; i <=npts; i++){
		htime->SetBinError(i, pow(htime->GetBinContent(i), 0.5));
	}

	double binWidth =(htime->GetXaxis()->GetXmax() - htime->GetXaxis()->GetXmin())/(htime->GetXaxis()->GetNbins());

	// FIT
	// Fit limits, not plot limits
	// Comment for e16032
	double upper, lower;
	lower = 0;
	upper = 100;	
	//lower = 0;	
	//upper = npts*binWidth;

	fitFunc->SetParName(0, "Background Activity");
	fitFunc->SetParName(1, "Background Half-life");
	fitFunc->SetParName(2, "Parent Half-Life");
	fitFunc->SetParName(3, "Initial Activity");
	fitFunc->SetParName(4, "Daughter Half-life");
	fitFunc->SetParName(5, "Beta-N Daughter Half-life");
	fitFunc->SetParName(6, "Beta-2N Daughter Half-life");
	fitFunc->SetParName(7, "1-neutron emission probability");
	fitFunc->SetParName(8, "2-neutron emission probability");
	//For e16032
	fitFunc->SetParName(9, "Background constant");

	// Parameter guesses
	// Bg params from reverse correlation
	// Comment for e16032	
	//fitFunc->SetParameter(0, 1000);
	//fitFunc->FixParameter(1, bgHL);
	fitFunc->FixParameter(0, 181.001*2);
	fitFunc->FixParameter(1, 1577.23);
	fitFunc->FixParameter(9, 1861.72*2);
	fitFunc->SetParameter(2, 15);
	fitFunc->SetParameter(3, 1000);
	fitFunc->FixParameter(4, data.dHL);
	fitFunc->FixParameter(5, data.bnHL);
	fitFunc->FixParameter(6, data.b2nHL);
	fitFunc->FixParameter(7, data.pbn);
	fitFunc->FixParameter(8, data.pb2n);

	htime->Fit(fitFunc, "Q0R");

	double chi2NDF = getChiSquare(htime, fitFunc);
	double pHL = fitFunc->GetParameter(2);

	
	if(toDraw == true){
		
		cout << endl;
		cout << "-------------------------SAMPLE------------------------------" << endl;
		cout << "Parent HL = " << pHL << endl;
		cout << "Daughter HL = " << data.dHL << " ms" << endl;
		cout << "Beta-N daughter HL = " << data.bnHL << " ms" << endl;
		cout << "Beta-2N daughter HL = " << data.b2nHL << " ms" << endl;
		cout << "Pn = " << data.pbn << endl;
		cout << "P2n = " << data.pb2n << endl;
		cout << "-------------------------------------------------------------" << endl;
			
		TCanvas *c0 = new TCanvas("c0", "c0", 800, 600);				
		c0->cd();
		fitFunc->SetLineColor(kRed);
		//Comment for e16032		
		//fitFunc->SetTitle(Form("HL = %f ms, #chi^{2}/NDF = %f", pHL, chi2NDF));
		fitFunc->SetTitle(Form("HL = %f ms, #chi^{2} = %f", pHL, chi2NDF));
		fitFunc->GetXaxis()->SetTitle("Decay time, ms");
		fitFunc->GetYaxis()->SetTitle(Form("counts / %5.3f ms", binWidth));
		fitFunc->Draw();
		htime->Draw("same PL");	
		// Need to draw fitFunc before htime in order to get 9 unique canvases.
		// Drawing fitFunc again here so that it's on top of htime.
		// Really silly but I can't think of a better way to do this	
		fitFunc->Draw("same");

		gPad->Modified();
		gPad->Update();

		cout << "Enter any number to continue: ";
		int blah;
		cin >> blah;
		
		//gPad->WaitPrimitive();

		delete c0;
	}
				


	vector<double> fitResult = {pHL, chi2NDF};

	delete fitFunc;
	delete htime;
	f->Close();

	return fitResult;
}

void newErrorCalc(){

	// Progress tracking
	time_t start, stop;
	start = time(0);
	timeval tvelapsed_c, tvelapsed_o;
	gettimeofday (&tvelapsed_o, NULL);
  	Long64_t eventcounter = 0;
  	
  	// First, which parent should we look at?
  	string parentName;
	cout << "Enter name of parent ion: ";
	cin >> parentName;

	DecayData data = getDecayData(parentName);

	// Comment for e16032
	//double bgHL = getBgHL(parentName);
	double bgHL = 0;

	vector<double> fitAdopt = fitSample(data, bgHL, true);
	double adoptHL = fitAdopt.at(0);
	
	// Setting plotting range to 3% of adopted half-life based on apparent optimal ranges for a few examples
	// Won't be perfect every time
	double lowerHL = adoptHL*(1-0.03);
	double upperHL = adoptHL*(1+0.03);
	int nBins = 60;

	cout << "Adopted HL = " << adoptHL << " ms" << endl;

	// Make histograms, graphs for needed results
	TH1D *h = new TH1D("h", "h", nBins, lowerHL, upperHL);
	TGraph *gDHL = new TGraph();
	TGraph *gDNHL = new TGraph();
	TGraph *gD2NHL = new TGraph();
	TGraph *gPN = new TGraph();
	TGraph *gP2N = new TGraph();
	TGraph *gChi2 = new TGraph();
	
	TH1D *sDHL = new TH1D("sDHL", Form("Samples - %s half-life", data.daughterName.c_str()), 100, data.dHL-3*data.dHLErr, data.dHL+3*data.dHLErr);
	TH1D *sDNHL = new TH1D("sDNHL", Form("Samples - %s half-life", data.betaNName.c_str()), 100, data.bnHL-3*data.bnHLErr, data.bnHL+3*data.bnHLErr);
	TH1D *sD2NHL = new TH1D("sD2NHL", Form("Samples - %s half-life", data.beta2NName.c_str()), 100, data.b2nHL-3*data.b2nHLErr, data.b2nHL+3*data.b2nHLErr);
	TH1D *sPN = new TH1D("sPN", "Samples - 1-neutron emission probability", 100, 100*(data.pbn-3*data.pbnErr), 100*(data.pbn+3*data.pbnErr));
	TH1D *sP2N = new TH1D("sP2N", "Samples - 2-neutron emission probability", 100, 100*(data.pb2n-3*data.pb2nErr),100*(data.pb2n+3*data.pb2nErr));

	// Misc.
	TRandom3 *rndm = new TRandom3(0);
	int samples = 5000;
	int counter = 0;
	int skipped = 0;
	int nDrawn = 0;
	int nFail = 0;

	while(counter < samples){

		DecayData sData;

		sData.dHL = rndm->Gaus(data.dHL, data.dHLErr);
		sData.bnHL = rndm->Gaus(data.bnHL, data.bnHLErr);
		sData.b2nHL = rndm->Gaus(data.b2nHL, data.b2nHLErr);
		sData.pbn = rndm->Gaus(data.pbn, data.pbnErr);
		sData.pb2n = rndm->Gaus(data.pb2n, data.pb2nErr);
		
		sData.parentName = data.parentName;
		sData.daughterName = data.daughterName;
		sData.betaNName = data.betaNName;
		sData.beta2NName = data.beta2NName;
		sData.pbnErr = data.pbnErr;
		sData.pb2nErr = data.pb2nErr;
		sData.dHLErr = data.dHLErr;
		sData.bnHLErr = data.bnHLErr;
		sData.b2nHLErr = data.b2nHLErr;

		// Reject non-physical random samples
		bool fitFlag;
		if(sData.dHL < 0 || sData.bnHL < 0 || sData.b2nHL < 0)
			fitFlag = false;
		else if(sData.pbn < 0 || sData.pbn > 1 || sData.pb2n < 0 || sData.pb2n > 1)
			fitFlag = false;
		else if(sData.pbn + sData.pb2n > 1)
			fitFlag = false;
		else
			fitFlag = true;
			
		if(fitFlag == true){

			// Randomly sample in order to draw 9 random fits. Probability of yes should be 9/samples = 0.09%
			// Set probability = 13/samples
			// According to the binomial distribution, we should get at least 9 samples 90% of the time
			// The second condition guarantees we'll always have 9 samples
			double rand = rndm->Integer(samples);
			bool toDraw = false;
			if(nDrawn < 9 && (rand < 13 || counter > samples - 9)){
				toDraw = true;
				nDrawn++;
			}
		
			vector<double> fitResult = fitSample(sData, bgHL, toDraw);

			double pHL = fitResult.at(0);
			double chi2NDF = fitResult.at(1);			
			//double iA = fitFunc->GetParameter(3);
			//double bgndInt = fitFunc->GetParameter(0);
			//double bgndSlope = fitFunc->GetParameter(1);

			h->Fill(pHL);

			gDHL->AddPoint(sData.dHL, pHL);
			gDNHL->AddPoint(sData.bnHL, pHL);
			gD2NHL->AddPoint(sData.b2nHL, pHL);
			gPN->AddPoint(sData.pbn*100, pHL);
			gP2N->AddPoint(sData.pb2n*100, pHL);
			// Protect against INF/NaN errors	
			if((chi2NDF > 0 && chi2NDF < 10000) && (pHL > 0 && pHL < 1000)){
				gChi2->AddPoint(pHL, chi2NDF);			
			}		
			else
				nFail++;

			sDHL->Fill(sData.dHL);
			sDNHL->Fill(sData.bnHL);
			sD2NHL->Fill(sData.b2nHL);
			sPN->Fill(sData.pbn*100);
			sP2N->Fill(sData.pb2n*100);
			
			
			// Progress bar
			if(counter > 0 && (counter % (int)(samples * 0.01)) == 0) {
			
				gettimeofday(&tvelapsed_c, NULL);			

				double rate = eventcounter/(((tvelapsed_c.tv_sec+tvelapsed_c.tv_usec/1.e6)-(tvelapsed_o.tv_sec+tvelapsed_o.tv_usec/1.e6)));
				double remaining = (samples - counter) / rate / 60;		

				cout << "Processed " << counter << " samples. " << (int)(counter/(int)(samples*0.01));
				cout << "% done. Current rate: " << rate << " sample per second. Estimated time remaining: "; 
				cout << remaining << " minutes.\r" << flush;

				gettimeofday(&tvelapsed_o, NULL);
				eventcounter = 0;
			}
			eventcounter++;	
			//
			counter++;
		}
		else{
			skipped++;	
		}
	}
	cout << endl << "Skipped " << skipped << " total non-physical samples." << endl;		
	
	gStyle->SetOptStat("111111");

	TF1* func = new TF1("func", gaussian, lowerHL, upperHL, 3);
	func->SetParName(0, "Height");
	func->SetParName(1, "Centroid");
	func->SetParName(2, "Sigma");

	int x, y, z; 
	h->GetMaximumBin(x, y, z);
	double height = h->GetBinContent(x);
	double sigma = 1;

	func->SetParameters(height, h->GetBinCenter(x), sigma);

	h->Fit("func", "RN0");

	TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
	c1->Divide(3, 2);
	c1->cd(1);
	gDHL->GetXaxis()->SetTitle(Form("%s half-life, ms", data.daughterName.c_str()));
	gDHL->GetYaxis()->SetTitle(Form("%s half-life, ms", parentName.c_str()));
	gDHL->GetYaxis()->SetRangeUser(lowerHL, upperHL);
	gDHL->SetMarkerStyle(1);
	gDHL->Draw("AP");
	c1->cd(2);
	gDNHL->GetXaxis()->SetTitle(Form("%s half-life, ms", data.betaNName.c_str()));
	gDNHL->GetYaxis()->SetTitle(Form("%s half-life, ms", parentName.c_str()));
	gDNHL->GetYaxis()->SetRangeUser(lowerHL, upperHL);
	gDNHL->SetMarkerStyle(1);	
	gDNHL->Draw("AP");
	c1->cd(3);
	gD2NHL->GetXaxis()->SetTitle(Form("%s half-life, ms", data.beta2NName.c_str()));
	gD2NHL->GetYaxis()->SetTitle(Form("%s half-life, ms", parentName.c_str()));
	gD2NHL->GetYaxis()->SetRangeUser(lowerHL, upperHL);	
	gD2NHL->SetMarkerStyle(1);
	gD2NHL->Draw("AP");
	c1->cd(4);
	gPN->GetXaxis()->SetTitle("Neutron emission probability, %");
	gPN->GetYaxis()->SetTitle(Form("%s half-life, ms", parentName.c_str()));
	gPN->GetYaxis()->SetRangeUser(lowerHL, upperHL);
	gPN->SetMarkerStyle(1);
	gPN->Draw("AP");
	c1->cd(5);
	gP2N->GetXaxis()->SetTitle("2-Neutron emission probability, %");
	gP2N->GetYaxis()->SetTitle(Form("%s half-life, ms", parentName.c_str()));
	gP2N->GetYaxis()->SetRangeUser(lowerHL, upperHL);
	gP2N->SetMarkerStyle(1);
	gP2N->Draw("AP");
	c1->cd(6);
	gChi2->GetYaxis()->SetTitle("Fit #chi^{2}");
	gChi2->GetXaxis()->SetTitle(Form("%s half-life, ms", parentName.c_str()));
	// Comment for e16032	
	//gChi2->GetXaxis()->SetRangeUser(lowerHL, upperHL);
	//gChi2->GetYaxis()->SetRangeUser(0, 3);
	gChi2->SetMarkerStyle(1);
	gChi2->Draw("AP");

	TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
	c2->Divide(3, 2);
	c2->cd(1);
	sDHL->GetXaxis()->SetTitle(Form("%s half-life (ms)", data.daughterName.c_str()));
	sDHL->GetYaxis()->SetTitle(Form("Counts / %5.3f ms", (sDHL->GetXaxis()->GetXmax()-sDHL->GetXaxis()->GetXmin())/sDHL->GetNbinsX()));

	sDHL->Draw("hist");
	c2->cd(2);
	sDNHL->GetXaxis()->SetTitle(Form("%s half-life (ms)", data.betaNName.c_str()));
	sDNHL->GetYaxis()->SetTitle(Form("Counts / %5.3f ms", (sDNHL->GetXaxis()->GetXmax()-sDNHL->GetXaxis()->GetXmin())/sDNHL->GetNbinsX()));
	sDNHL->Draw("hist");
	c2->cd(3);
	sD2NHL->GetXaxis()->SetTitle(Form("%s half-life (ms)", data.beta2NName.c_str()));
	sD2NHL->GetYaxis()->SetTitle(Form("Counts / %5.3f ms", (sD2NHL->GetXaxis()->GetXmax()-sD2NHL->GetXaxis()->GetXmin())/sD2NHL->GetNbinsX()));
	sD2NHL->Draw("hist");
	c2->cd(4);
	sPN->GetXaxis()->SetTitle("1-neutron emission probability (%)");
	sPN->GetYaxis()->SetTitle("Counts / 1%");
	sPN->GetYaxis()->SetTitle(Form("Counts / %5.3f percent", (sPN->GetXaxis()->GetXmax()-sPN->GetXaxis()->GetXmin())/sPN->GetNbinsX()));
	sPN->Draw("hist");
	c2->cd(5);
	sP2N->GetXaxis()->SetTitle("2-neutron emission probability (%)");
	sP2N->GetYaxis()->SetTitle(Form("Counts / %5.3f percent", (sP2N->GetXaxis()->GetXmax()-sP2N->GetXaxis()->GetXmin())/sP2N->GetNbinsX()));
	sP2N->Draw("hist");
	c2->cd(6);	
	h->SetTitle(Form("Outcomes - %s half-life", parentName.c_str()));
	h->GetXaxis()->SetTitle(Form("%s half-life, ms", parentName.c_str()));
	h->GetYaxis()->SetTitle(Form("Counts / %5.3f ms", (h->GetXaxis()->GetXmax()-h->GetXaxis()->GetXmin())/h->GetNbinsX()));
	h->Draw("hist");
	func->SetLineColor(kRed);
	func->Draw("same");

	cout << "---------------------RESULTS---------------------" << endl;
	//cout << "Adopted parent half-life = " << adoptHL << " ms" << endl;
	cout << "Centroid = " << func->GetParameter(1) << " +/- " << func->GetParError(1) << " ms" <<endl;
	cout << "Sigma = " << func->GetParameter(2) << " +/- " << func->GetParError(2) << " ms" << endl;
	cout << "Height = " << func->GetParameter(0) << " +/- " << func->GetParError(0) << endl;
	cout << "Overflows = " << h->GetBinContent(nBins+1) << endl;
	cout << "Underflows = " << h->GetBinContent(0) << endl;
	cout << nFail << " event(s) with chi2/NDF > 2" << endl;
	cout << "-------------------------------------------------" << endl;

	stop = time(0);
	cout << "Done with " << samples << " samples after " << difftime(stop, start)/60 << " minutes." << endl;
}

