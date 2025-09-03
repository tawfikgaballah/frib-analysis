#include <vector>
#include <string>
#include <fstream>
#include <sstream>

//p0 = constant multiple, p1 = mean, p2 = sigma, p3 = bgnd slope, p4 = bgnd intercept
double gaussian(double *x, double *p){

	// If needed, to reject peaks that get in the way of good fits
	/*
	if((x[0] > 1252 && x[0] < 1257) || (x[0] > 1272 && x[0] < 1274)){
		TF1::RejectPoint();
		return 0;
	}
	*/
	
	return p[0]*exp(-0.5*pow((x[0]-p[1])/p[2], 2)) + p[3]*x[0] + p[4];
}

//p0 = constant multiple, p1 = mean, p2 = sigma, p3 = constant multiple, p4 = mean, p5 = sigma, p6 = bgnd
double gaussian2(double *x, double *p){

	// If needed, to reject peaks that get in the way of good fits
	
	if((x[0] > 53 && x[0] < 57)){
		TF1::RejectPoint();
		return 0;
	}
	
	
	return p[0]*exp(-0.5*pow((x[0]-p[1])/p[2], 2)) + p[3]*exp(-0.5*pow((x[0]-p[4])/p[5], 2)) + + p[4];
}

void do_fit(int lower, int upper, int mean, TH1D *ecal, TF1 *func, TCanvas *c, int save, bool rebin, ofstream &fileOut){

	func->SetRange(lower, upper);

	c->Update();
	c->Modified();

	int method;
	for(int i = lower; i < upper; i++){
		if(ecal->GetBinContent(ecal->FindBin(i)) == 0){
			cout << "Caution: empty bins in fit region. Enter 1 to use log likelihood fit method, or any other number to use chi squared fit method: ";
			cin >> method; 	
			break;					
		}
	}

	double bgnd = 0;
	if(lower < mean - 2){
		for(int i = lower; i < mean - 2; i++){
			bgnd += ecal->GetBinContent(ecal->FindBin(i));
		}	
		bgnd = bgnd / (mean - 2 - lower);
	}
	else{
		for(int i = upper; i > mean + 2; i--){
			bgnd += ecal->GetBinContent(ecal->FindBin(i));
		}
		bgnd = bgnd / (upper - (mean + 2));
	}

	double constant = ecal->GetBinContent(ecal->FindBin(mean)) - bgnd;
	if(constant < 0){
		bgnd = 10;
		constant = ecal->GetBinContent(ecal->FindBin(mean));
	}


	/*	
	cout << "Guess the height of the background: ";
	cin >> bgnd;
	cout << "Guess the constant multiple parameter: ";
	cin >> constant;
	*/
	
	int bg_flag;
	cout << "Enter 1 to use a linear background, or any other number to use a constant background: ";
	cin >> bg_flag;

	double bgnd_slope = 0;
	if(bg_flag == 1){
		cout << "Guessing bgnd slope = -0.1" << endl;
		bgnd_slope = -0.1;
		bgnd = bgnd - mean*bgnd_slope;
	}

	cout << "Guessing bgnd = " << bgnd << endl;
	cout << "Guessing scale = " << constant << endl;
	cout << "Guessing sigma = 1" << endl;
	cout << "Drawing guess..." << endl;

	func->SetParameters(constant, mean, 1, bgnd_slope, bgnd);

	if(bg_flag != 1){
		cout << "Fixing bgnd slope = 0" << endl;
		func->FixParameter(3, 0);
	}	
	

	func->SetLineColor(kRed);
	func->SetLineStyle(9);
	func->Draw("same");
	c->Update();
	c->Modified();

	int blah;
	cout << "Enter any number to perform fit: ";
	cin >> blah;

	if(method == 1){
		TFitResultPtr r = ecal->Fit("func", "SQRWWLL");
		cout << "Fitting with log likelihood fit method..." << endl;
	}	
	else{	
		TFitResultPtr r = ecal->Fit("func", "SQR");
		cout << "Fitting with chi squared fit method..." << endl;
	}	
	func->SetLineStyle(1);
	c->Update();
	c->Modified();

	// Copy the fit parameters needed for further calculations, and their errors
	double fconst = func->GetParameter(0);
	double econst = func->GetParError(0);
	double fmean = func->GetParameter(1);
	double emean = func->GetParError(1);
	double fsig = func->GetParameter(2);
	double esig = func->GetParError(2);
	double fbgndslope = func->GetParameter(3);
	double ebgndslope = func->GetParError(3);
	double fbgndintercept = func->GetParameter(4);
	double ebgndintercept = func->GetParError(4);

	// Numerical integration
	/*
	double lower_bound = fmean - 2*fsig;
	double upper_bound = fmean + 2*fsig;
	double integral = func->Integral(lower_bound, upper_bound);
	double integral_error = func->IntegralError(lower_bound, upper_bound, r->GetParams(), r->GetCovarianceMatrix().GetMatrixArray());

	// Background subtract the integral
	double tot_bgnd = fbgnd*4*fsig;  // this is the total amount of background in the integration region
	double int_sub_error = pow(pow(integral_error, 2)+pow(4*fsig*fbgnd, 2)*(pow(esig/fsig, 2) + pow(ebgnd/fbgnd, 2)), 0.5);
	*/

	if (rebin == true){
		// Manual integration
		double integral = pow(2*M_PI, 0.5)*fconst*fsig/2;
		double eintegral = integral * pow(pow(esig/fsig,2) + pow(econst/fconst,2) ,0.5);

		double chisquare = func->GetChisquare();
		double ndf = func->GetNDF();

		

		cout << "--------------------RESULTS---------------------" << endl;
		cout << "Mean = " << fmean << " +/- " << emean <<  " keV" << endl;
		cout << "Sigma = " << fsig << " +/- " << esig << " keV" << endl;
		cout << "Constant = " << fconst/2 << " +/- " << econst/2 << " counts/keV" << endl;
		cout << "BgndSlope = " << fbgndslope/4 << " +/- " << ebgndslope/4 << " counts/keV^2" << endl;
		cout << "BgndIntercept = " << fbgndintercept/2 << " +/- " << ebgndintercept/2 << " counts/keV " << endl;
		cout << "N_counts = " << integral << " +/- " << eintegral << " counts" << endl;
		cout << "Chi^2/NDF = " << chisquare / ndf << endl;
		cout << "------------------------------------------------" << endl;

		if(save == 1){
			int savethis;
			cout << "Save this fit to file? Enter 1 for yes, or any other number for no: ";
			cin >> savethis;
			if(savethis == 1){
				fileOut << fmean << " " << emean << " " << fsig <<" " << esig << " " << fconst/2 << " " << econst/2 << " " << fbgndslope/4 <<" ";
				fileOut << ebgndslope/4 << " " << fbgndintercept/2 << " " << ebgndintercept/2 << " " << integral << " " << eintegral << "\n";
			}
		}
	}

	else{
		// Manual integration
		double integral = pow(2*M_PI, 0.5)*fconst*fsig;
		double eintegral = integral * pow(pow(esig/fsig,2) + pow(econst/fconst,2) ,0.5);

		double chisquare = func->GetChisquare();
		double ndf = func->GetNDF();

		

		cout << "--------------------RESULTS---------------------" << endl;
		cout << "Mean = " << fmean << " +/- " << emean <<  " keV" << endl;
		cout << "Sigma = " << fsig << " +/- " << esig << " keV" << endl;
		cout << "Constant = " << fconst << " +/- " << econst << " counts/keV" << endl;
		cout << "BgndSlope = " << fbgndslope << " +/- " << ebgndslope << " counts/keV^2" << endl;
		cout << "BgndIntercept = " << fbgndintercept << " +/- " << ebgndintercept << " counts/keV " << endl;
		cout << "N_counts = " << integral << " +/- " << eintegral << " counts" << endl;
		cout << "Chi^2/NDF = " << chisquare / ndf << endl;
		cout << "------------------------------------------------" << endl;

		if(save == 1){
			int savethis;
			cout << "Save this fit to file? Enter 1 for yes, or any other number for no: ";
			cin >> savethis;
			if(savethis == 1){
				fileOut << fmean << " " << emean << " " << fsig <<" " << esig << " " << fconst << " " << econst << " " << fbgndslope <<" ";
				fileOut << ebgndslope << " " << fbgndintercept << " " << ebgndintercept << " " << integral << " " << eintegral << "\n";
			}
		}
	}

	if(bg_flag != 1){
		func->ReleaseParameter(3);
	}
}

void peakFit(){

	string gatename;

	cout << "Enter the gate name (e.g. 28Ne, 24F, etc.): ";
	cin >> gatename;

	


	
	TFile *f = new TFile(Form("/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/bDecay/d%s-18ms-3mm-subtracted.root", gatename.c_str()));
	//TH1D *ecal = (TH1D*)f->Get("clover_ecal_time_cut");
	//TH1D *ecal = (TH1D*)f->Get("clover_ecal");
	TH1D *ecal = (TH1D*)f->Get("hsub");

	bool rebin = true;
	if(rebin == true){	
		cout << "Rebinning to 2 keV / bin... " << endl;	
		//ecal->Rebin(2);
	}	

	cout << "Reading spectra from " << gatename << " decay gate." << endl;
	
	int save;	
	cout << "Enter 1 if you'd like to save any results to a text file, or any other number if not: ";
	cin >> save;

	ostringstream fileOutName;
	fileOutName << "/projects/e21062/aad/e21062B/rootAnalysisFinal/scripts/fit_results_" << gatename << ".txt";
	ofstream fileOut((fileOutName.str()).c_str());
	if(save == 1){
		cout << "Printing output to " << fileOutName.str() << endl;
		fileOut << "Mean err(Mean) Sigma err(Sigma) Constant err(Constant) Bgnd_Slope  err(Bgnd_Slope) Bgnd_Intercept err(Bgnd_Intercept) Area err(Area)\n";
	}	

	/*
	TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/implantCorr/i%s.root", gatename));
	TH1D *ecal = (TH1D*)f->Get("ecal_32Na_delayed");
	*/

	// SET BIN ERRORS
	int npts = ecal->GetNbinsX();
	for(int i = 1; i <=npts; i++){
			ecal->SetBinError(i, pow(ecal->GetBinContent(i), 0.5));
	}
	
	gStyle->SetOptStat(0);
	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();
	ecal->GetXaxis()->SetTitle("keV");
	if (rebin == true)
		ecal->GetYaxis()->SetTitle("counts / 2 keV");
	else
		ecal->GetYaxis()->SetTitle("counts / keV");
	ecal->Draw("hist");
	c->Update();
	c->Modified();
	
	TF1* func = new TF1("func", gaussian, 1, 8001, 5);
	func->SetParName(0, "Constant");
	func->SetParName(1, "Mean");
	func->SetParName(2, "Sigma");
	func->SetParName(3, "BgndSlope");
	func->SetParName(4, "BgndIntercept");

	TF1* func2 = new TF1("func2", gaussian2, 1, 8001, 7);
	func2->SetParName(0, "Constant");
	func2->SetParName(1, "Mean");
	func2->SetParName(2, "Sigma");
	func2->SetParName(3, "Constant2");
	func2->SetParName(4, "Mean2");
	func2->SetParName(5, "Sigma2");
	func2->SetParName(6, "Bgnd");


	// Perform peak fits

	int mean;

	cout << "Guess the (integer) energy of the peak to be fit, or enter 0 to quit: ";	
	cin >> mean;

	while(mean != 0){
		c->Clear();

		ecal->GetXaxis()->SetRangeUser(mean - 30, mean + 30);
		ecal->Draw("hist");
		c->Update();
		c->Modified();

		int choice;
		cout << "Enter the lower bound, enter 1 to use a +/- 10 keV fitting range, or enter 2 to use a +/- 20 keV fitting range." << endl;
		cout << "Lower bound: ";
		cin >> choice;		
		if(choice == 1)
			do_fit(mean-10, mean+10, mean, ecal, func, c, save, rebin, fileOut);
		else if(choice == 2)
			do_fit(mean-20, mean+20, mean, ecal, func, c, save, rebin, fileOut);
		else{
			int lower, upper;
			lower = choice;
			cout << "Upper bound: ";
			cin >> upper;
			do_fit(lower, upper, mean, ecal, func, c, save, rebin, fileOut);
		}

		cout << "Guess the (integer) energy of the peak to be fit, or enter 0 to quit: ";	
		cin >> mean;
	}

	fileOut.close();

}
