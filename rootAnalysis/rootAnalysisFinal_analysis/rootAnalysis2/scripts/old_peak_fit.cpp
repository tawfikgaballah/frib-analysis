//p0 = height, p1 = mean, p2 = standard deviation, p3 = bgnd
double gaussian(double *x, double *p){return p[0]*exp(-0.5*pow((x[0]-p[1])/p[2], 2)) + p[3];}

void peak_fit(){
	time_t start, stop;
	start = time(0);

	// MAKE HISTOGRAMS & FIT FUNCTION
			
	//TFile *f = new TFile("histograms.root");

	//TH2D *ecal_vs_t_32Na = (TH2D*)f->Get("ecal_vs_t_32Na");
	//TH1D *ecal = new TH1D("ecal", "Clover energy, for 2 us < tdiff < 50 us", 250, 200, 450);	
	//ecal = ecal_vs_t_32Na->ProjectionY("ecal", 2, 25);

	TF1* f223 = new TF1("f223", gaussian, 213, 233, 4);
	f223->SetParName(0, "Height");
	f223->SetParName(1, "Mean");
	f223->SetParName(2, "StdDev");
	f223->SetParName(3, "Bgnd");

	TF1* f401 = new TF1("f401", gaussian, 391, 411, 4);
	f401->SetParName(0, "Height");
	f401->SetParName(1, "Mean");
	f401->SetParName(2, "StdDev");
	f401->SetParName(3, "Bgnd");

	// PERFORM FITS	
	f223->SetParameters(ecal->GetBinContent(223), 223, 1, 90);
	ecal->Fit("f223", "R");

	f401->SetParameters(ecal->GetBinContent(401), 401, 1, 30);
	ecal->Fit("f401", "R");

	// DRAW
	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();
	ecal->GetXaxis()->SetRangeUser(200, 450);
	ecal->Draw("hist");
	f223->Draw("same");
	f401->Draw("same");	

	stop = time(0);
	cout << "Done after " << difftime(stop, start)/60 << " minutes." << endl;
}
