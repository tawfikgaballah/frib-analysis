//p0 = constant multiple, p1 = mean, p2 = sigma, p3 = constant multiple, p4 = mean, p5 = bgnd slope, p6 = bgnd intercept
double gauss2(double *x, double *p){

	// If needed, to reject peaks that get in the way of good fits
	
	if((x[0] > 243 && x[0] < 246) || (x[0] > 257 && x[0] < 259)){
		TF1::RejectPoint();
		return 0;
	}
	
	
	return p[0]*exp(-0.5*pow((x[0]-p[1])/p[2], 2)) + p[3]*exp(-0.5*pow((x[0]-p[4])/p[2], 2)) + p[5]*x[0] + p[6];
}

void double_gauss(){
	
	char gatename[5] = "25F";

	TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/bDecay/d%s.root", gatename));
	TH1D *ecal = (TH1D*)f->Get("clover_ecal");

	// SET BIN ERRORS
	int npts = ecal->GetNbinsX();
	for(int i = 1; i <=npts; i++){
		if(ecal->GetBinContent(i) > 0)
			ecal->SetBinError(i, pow(ecal->GetBinContent(i), 0.5));
		else
			ecal->SetBinError(i, 1);	
	}

	TF1* func = new TF1("func", gauss2, 1, 8001, 7);
	func->SetParName(0, "Constant1");
	func->SetParName(1, "Mean1");
	func->SetParName(2, "Sigma");
	func->SetParName(3, "Constant2");
	func->SetParName(4, "Mean2");
	func->SetParName(5, "BgndSlope");
	func->SetParName(6, "BgndIntercept");

	// PARAMETER GUESSES
	double constant1 = 9;
	double mean1 = 2231.5;
	//func->SetParLimits(1, 199, 202);
	double sigma = 0.7;
	//func->SetParLimits(2, 0.3, 1.4);
	double constant2 = 16;
	double mean2 = 2234.5;
	//func->SetParLimits(4, 202, 204);
	//func->SetParLimits(5, 0.5, 1.5);
	double bgndSlope = 0;
	double bgndIntercept = 3;

	// Try fitting the second peak alone, then bounding the 3 parameters I get there
	//double constant2 = 18;
	//func->SetParLimits(3, 12, 24);
	//double mean2 = 203.2;
	//func->SetParLimits(4, 202.9, 203.5);
	//double sigma2 = 0.9;
	//func->SetParLimits(5, 0.5, 1.3);

	// Fit limits
	int low = 2205;
	int high = 2240;

	func->SetParameters(constant1, mean1, sigma, constant2, mean2, bgndSlope, bgndIntercept);
	func->SetRange(low, high);

	// Comment if you want a linear bgnd:
	
	cout << "Fixing bgnd slope = 0" << endl;
	func->FixParameter(5, 0);
	
	// Try fitting the second peak alone, then fixing the 3 parameters I get there
	/*	
	func->FixParameter(3, 17.8523);
	func->FixParameter(4, 203.18);
	func->FixParameter(5, 0.915204);	
	*/

	gStyle->SetOptStat(0);

	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();
	ecal->GetXaxis()->SetTitle("keV");
	ecal->GetYaxis()->SetTitle("counts / keV");
	ecal->GetXaxis()->SetRangeUser(2200, 2260);
	ecal->Draw("hist");
	func->SetLineColor(kRed);
	func->SetLineStyle(9);
	func->Draw("same");
	c->Update();
	c->Modified();

	int blah;
	cout << "Enter any number to perform fit: ";
	cin >> blah;

	//cout << "Fitting with log likelihood fit method..." << endl;
	ecal->Fit("func", "QR");

	func->SetLineStyle(1);
	c->Update();
	c->Modified();

	// Copy the fit parameters needed for further calculations, and their errors
	double fconst1 = func->GetParameter(0);
	double econst1 = func->GetParError(0);
	double fmean1 = func->GetParameter(1);
	double emean1 = func->GetParError(1);
	double fsig = func->GetParameter(2);
	double esig = func->GetParError(2);
	double fconst2 = func->GetParameter(3);
	double econst2 = func->GetParError(3);
	double fmean2 = func->GetParameter(4);
	double emean2 = func->GetParError(4);
	double fbgndslope = func->GetParameter(5);
	double ebgndslope = func->GetParError(5);
	double fbgndintercept = func->GetParameter(6);
	double ebgndintercept = func->GetParError(6);

	// Manual integration
	double integral1 = pow(2*M_PI, 0.5)*fconst1*fsig;
	double eintegral1 = integral1 * pow(pow(esig/fsig,2) + pow(econst1/fconst1,2) ,0.5);
	double integral2 = pow(2*M_PI, 0.5)*fconst2*fsig;
	double eintegral2 = integral2 * pow(pow(esig/fsig,2) + pow(econst2/fconst2,2) ,0.5);

	cout << "--------------------RESULTS---------------------" << endl;
	cout << "Mean1 = " << fmean1 << " +/- " << emean1 <<  " keV" << endl;
	cout << "Constant1 = " << fconst1 << " +/- " << econst1 << " counts/keV" << endl;
	cout << "N1 = " << integral1 << " +/- " << eintegral1 << " counts" << endl;
	cout << "Mean2 = " << fmean2 << " +/- " << emean2 <<  " keV" << endl;
	cout << "Constant2 = " << fconst2 << " +/- " << econst2 << " counts/keV" << endl;
	cout << "N2 = " << integral2 << " +/- " << eintegral2 << " counts" << endl;
	cout << "Sigma = " << fsig << " +/- " << esig << " keV" << endl;
	cout << "BgndSlope = " << fbgndslope << " +/- " << ebgndslope << " counts/keV^2" << endl;
	cout << "BgndIntercept = " << fbgndintercept << " +/- " << ebgndintercept << " counts/keV " << endl;

}
