// NB: Load fitTotalDecays.cpp first!

#include <sys/time.h>
#include <TRandom3.h>
//#include "fitTotalDecays.hpp"

class DecayData{
	public:
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

DecayData getDecayData(string parentName){
	DecayData data;
	
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

// FUNCTIONS
//-------------------------------------------------------------------------------------------------------
double gaussian(double *x, double *p){return p[0]*exp(-0.5*pow((x[0]-p[1])/p[2], 2));}

// Daughter Functions
Double_t growInDecayDaughter(const double & A, const double & pHL, const double & dHL, const double & t){
         return A*pHL/(pHL-dHL)*(pow(0.5, t/pHL)-pow(0.5, t/dHL));
}  

// Background Component
Double_t bgnd(Double_t *x, Double_t *p){
   return p[0]+p[1]*x[0];
   //return p[0]*pow(0.5, x[0]/p[8]);
}

// Parent decays
Double_t parentDecays(Double_t *x, Double_t *p){

   double pHL = p[2];
   double A = p[3];
   double t = x[0];
   
   return A*pow(0.5, t/pHL); 
}

// Daughter decays
Double_t daughterDecays(Double_t *x, Double_t *p){

   double pHL = p[2];
   double A = p[3];
   double dHL = p[4];
   double t = x[0];

   return (1-p[7]-p[8])*growInDecayDaughter(A, pHL, dHL, t);
}

// Beta-n Daughter decays
Double_t betaNDecays(Double_t *x, Double_t *p){

   double pHL = p[2];
   double A = p[3];
   double bnHL = p[5];
   double t = x[0];

      
   return p[7]*growInDecayDaughter(A, pHL, bnHL, t);
}

// Beta-2n Daughter decays
Double_t beta2NDecays(Double_t *x, Double_t *p){

   double pHL = p[2];
   double A = p[3];
   double b2nHL = p[6];
   double t = x[0];
      
   return p[8]*growInDecayDaughter(A, pHL, b2nHL, t);
}

Double_t totalFit(Double_t *x, Double_t *p){
   return bgnd(x,p)
          +parentDecays(x,p)
          +daughterDecays(x,p)
          +betaNDecays(x,p)
          +beta2NDecays(x,p);        
}

// END FUNCTIONS
//-------------------------------------------------------------------------------------------------------

void errorCalc(){

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

	// Get histogram
	TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/bDecay/d%s.root", parentName.c_str()));
	TH1D *htime = (TH1D*)f->Get("allDecays");

	//htime->Rebin(8);
	
	// Get "adopted" value
	TF1 *fitAdopt = new TF1("Adopted Fit", totalFit, 0, 100, 8);	
	//double chi2NDF = doFit(htime, fitAdopt, data);

	int npts = htime->GetNbinsX();
	for(int i = 1; i <=npts; i++){
		htime->SetBinError(i, pow(htime->GetBinContent(i), 0.5));
	}

	double binWidth =(htime->GetXaxis()->GetXmax() - htime->GetXaxis()->GetXmin())/(htime->GetXaxis()->GetNbins());

	// FIT
	// Fit limits, not plot limits
	double upper, lower;
	lower = 0;	
	upper = npts*binWidth;

	fitAdopt->SetParName(0, "Background Intercept");
	fitAdopt->SetParName(1, "Background Slope");
	fitAdopt->SetParName(2, "Parent Half-Life");
	fitAdopt->SetParName(3, "Initial Activity");
	fitAdopt->SetParName(4, "Daughter Half-life");
	fitAdopt->SetParName(5, "Beta-N Daughter Half-life");
	fitAdopt->SetParName(6, "Beta-2N Daughter Half-life");
	fitAdopt->SetParName(7, "1-neutron emission probability");
	fitAdopt->SetParName(8, "2-neutron emission probability");

	// Parameter guesses
	// Bg params from 37Al reverse correlation
	fitAdopt->FixParameter(0, 4742.59);
	fitAdopt->FixParameter(1, -8.48164);
	fitAdopt->SetParameter(2, 10);
	fitAdopt->SetParameter(3, 5000);
	fitAdopt->FixParameter(4, data.dHL);
	fitAdopt->FixParameter(5, data.bnHL);
	fitAdopt->FixParameter(6, data.b2nHL);
	fitAdopt->FixParameter(7, data.pbn);
	fitAdopt->FixParameter(8, data.pb2n);

	TFitResultPtr fitResult = htime->Fit(fitAdopt, "Q0RSWL");

	double chi2NDFAdopt = fitResult->Chi2()/fitResult->Ndf();


	// Setting plotting range to 3% of adopted half-life based on apparent optimal ranges for a few examples
	// Won't be perfect every time
	double lowerHL = fitAdopt->GetParameter(1)*(1-0.03);
	double upperHL = fitAdopt->GetParameter(1)*(1+0.03);
	double adoptHL = fitAdopt->GetParameter(1);
	int nBins = 60;

	delete fitAdopt;
	delete htime;
	f->Close();

	// Histograms, graphs, etc. for plotting sampling results
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

	TCanvas *c0 = new TCanvas("c0", "c0", 800, 600);
	c0->Divide(3, 3);
	
	// Misc.
	TRandom3 *rndm = new TRandom3(0);
	int samples = 100;
	int counter = 0;
	int skipped = 0;
	int nDrawn = 0;
	int nFail = 0;

	while(counter < samples){

		double dHL = rndm->Gaus(data.dHL, data.dHLErr);
		double bnHL = rndm->Gaus(data.bnHL, data.bnHLErr);
		double b2nHL = rndm->Gaus(data.b2nHL, data.b2nHLErr);
		double pbn = rndm->Gaus(data.pbn, data.pbnErr);
		double pb2n = rndm->Gaus(data.pb2n, data.pb2nErr);

		// Reject non-physical random samples
		bool fitFlag;
		if(dHL < 0 || bnHL < 0 || b2nHL < 0)
			fitFlag = false;
		else if(pbn < 0 || pbn > 1 || pb2n < 0 || pb2n > 1)
			fitFlag = false;
		else if(pbn + pb2n > 1)
			fitFlag = false;
		else
			fitFlag = true;
			
		if(fitFlag == true){
		
			// Get histogram
			TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/bDecay/d%s.root", parentName.c_str()));
			TH1D *htime = (TH1D*)f->Get("allDecays");
			
			TF1 *fitFunc = new TF1("Total Fit", totalFit, 0, 100, 8);
			
			int npts = htime->GetNbinsX();
			for(int i = 1; i <=npts; i++){
				htime->SetBinError(i, pow(htime->GetBinContent(i), 0.5));
			}

			double binWidth =(htime->GetXaxis()->GetXmax() - htime->GetXaxis()->GetXmin())/(htime->GetXaxis()->GetNbins());

			// FIT
			// Fit limits, not plot limits
			double upper, lower;
			lower = 0;	
			upper = npts*binWidth;

			fitFunc->SetParName(0, "Background Intercept");
			fitFunc->SetParName(1, "Background Slope");
			fitFunc->SetParName(2, "Parent Half-Life");
			fitFunc->SetParName(3, "Initial Activity");
			fitFunc->SetParName(4, "Daughter Half-life");
			fitFunc->SetParName(5, "Beta-N Daughter Half-life");
			fitFunc->SetParName(6, "Beta-2N Daughter Half-life");
			fitFunc->SetParName(7, "1-neutron emission probability");
			fitFunc->SetParName(8, "2-neutron emission probability");

			// Parameter guesses
			// Bg params from 37Al reverse correlation
			fitFunc->FixParameter(0, 4742.59);
			fitFunc->FixParameter(1, -8.48164);
			fitFunc->SetParameter(2, 15);
			fitFunc->SetParameter(3, 50000);
			fitFunc->FixParameter(4, data.dHL);
			fitFunc->FixParameter(5, data.bnHL);
			fitFunc->FixParameter(6, data.b2nHL);
			fitFunc->FixParameter(7, data.pbn);
			fitFunc->FixParameter(8, data.pb2n);

			TFitResultPtr fitResult = htime->Fit(fitFunc, "Q0RSWL");

			double chi2NDF = fitResult->Chi2()/fitResult->Ndf();

			//double chi2NDF = doFit(htime, fitFunc, data);

			double pHL = fitFunc->GetParameter(2);
			double iA = fitFunc->GetParameter(3);
			double bgndInt = fitFunc->GetParameter(0);
			double bgndSlope = fitFunc->GetParameter(1);
			if(chi2NDF > 2)
				nFail++;

			h->Fill(pHL);

			gDHL->AddPoint(dHL, pHL);
			gDNHL->AddPoint(bnHL, pHL);
			gD2NHL->AddPoint(b2nHL, pHL);
			gPN->AddPoint(pbn*100, pHL);
			gP2N->AddPoint(pb2n*100, pHL);
			gChi2->AddPoint(pHL, chi2NDF);
		
			sDHL->Fill(dHL);
			sDNHL->Fill(bnHL);
			sD2NHL->Fill(b2nHL);
			sPN->Fill(pbn*100);
			sP2N->Fill(pb2n*100);
	
			// Randomly sample in order to draw 9 random fits. Probability of yes should be 9/samples = 0.09%
			// Set probability = 13/samples
			// According to the binomial distribution, we should get at least 9 samples 90% of the time
			// The second condition guarantees we'll always have 9 samples
			double rand = rndm->Integer(samples);
			if(nDrawn < 9){
				if(rand < 13 || (counter > samples-9)){
					
					cout << endl;
					cout << "-------------------------SAMPLE #" << counter << "-------------------------" << endl;
					cout << "Parent HL = " << pHL << endl;
					cout << "Daughter HL = " << dHL << " ms" << endl;
					cout << "Beta-N daughter HL = " << bnHL << " ms" << endl;
					cout << "Beta-2N daughter HL = " << b2nHL << " ms" << endl;
					cout << "Pn = " << pbn << endl;
					cout << "P2n = " << pb2n << endl;
					cout << "-------------------------------------------------------------" << endl;
										
					c0->cd(nDrawn+1);
					fitFunc->SetLineColor(kRed);
					fitFunc->SetTitle(Form("Sample number %d, HL = %f ms, #chi^{2}/NDF = %f", counter, pHL, chi2NDF));
					fitFunc->GetXaxis()->SetTitle("Decay time, ms");
					fitFunc->GetYaxis()->SetTitle("counts / 0.25 ms");
					fitFunc->Draw();
					htime->Draw("same PL");	
					// Need to draw fitFunc before htime in order to get 9 unique canvases.
					// Drawing fitFunc again here so that it's on top of htime.
					// Really silly but I can't think of a better way to do this	
					fitFunc->Draw("same");
					
					nDrawn++;

					gPad->Modified();
  					gPad->Update();
  					gPad->WaitPrimitive();
				}
				
			}

			delete fitFunc;			
			delete htime;
			f->Close();

			cout << "Deleted." << endl;


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
			cout << "Skipping..." << endl;
			skipped++;	
		}
		cout << "Time for next sample..." << endl;
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
	gChi2->GetXaxis()->SetRangeUser(lowerHL, upperHL);
	//gChi2->GetXaxis()->SetRangeUser(0, 3);
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
	cout << "Adopted parent half-life = " << adoptHL << " ms" << endl;
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
