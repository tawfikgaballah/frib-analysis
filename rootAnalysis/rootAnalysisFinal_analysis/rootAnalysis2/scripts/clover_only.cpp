//p0 = constant multiple, p1 = mean, p2 = sigma, p4 = bgnd 
double gaussian(double *x, double *p){return p[0]*exp(-0.5*pow((x[0]-p[1])/p[2], 2)) + p[3];}

void clover_only(){
		
	//TFile *f42 = new TFile("/projects/e21062/aad/rootanalysis/root_files/gamma_implant_hists/i42Si_2D.root");
	TFile *f41 = new TFile("/projects/e21062/aad/rootanalysis/root_files/gamma_implant_hists/i41Si_2D.root");
	//TFile *f40 = new TFile("/projects/e21062/aad/rootanalysis/root_files/gamma_implant_hists/i40Si_2D.root");

	//auto *h42 = (TH2F*)f42->Get("h");
	auto *h41 = (TH2F*)f41->Get("h");
	//auto *h40 = (TH2F*)f40->Get("h");

	//TH1D *ecal_42 = h42->ProjectionY("ecal_42", 1000, 2000);
	//TH1D *ecal_42_scale = (TH1D*)ecal_42->Clone("ecal_42_scale");
	//ecal_42_scale->Scale(4);
	TH1D *ecal_41 = h41->ProjectionY("ecal_41", 1051, 2000);
	//TH1D *ecal_40 = h40->ProjectionY("ecal_40", 1101, 2000); 
	
	// Fitting
	
	TF1* func = new TF1("func", gaussian, 1, 8001, 5);
	func->SetParName(0, "Constant");
	func->SetParName(1, "Mean");
	func->SetParName(2, "Sigma");
	func->SetParName(3, "Bgnd");
	
	func->SetRange(540, 570);
	func->SetParameters(6, 553, 1, 1);
	ecal_41->Fit("func", "QR");

	// Copy the fit parameters needed for further calculations, and their errors
	double fconst = func->GetParameter(0);
	double econst = func->GetParError(0);
	double fmean = func->GetParameter(1);
	double emean = func->GetParError(1);
	double fsig = func->GetParameter(2);
	double esig = func->GetParError(2);
	double fbgndintercept = func->GetParameter(3);
	double ebgndintercept = func->GetParError(3);

	// Manual integration
	double integral = pow(2*M_PI, 0.5)*fconst*fsig;
	double eintegral = integral * pow(pow(esig/fsig,2) + pow(econst/fconst,2) ,0.5);

	cout << "--------------------RESULTS---------------------" << endl;
	cout << "Mean = " << fmean << " +/- " << emean <<  " keV" << endl;
	cout << "Sigma = " << fsig << " +/- " << esig << " keV" << endl;
	cout << "Constant = " << fconst << " +/- " << econst << " counts/keV" << endl;
	cout << "BgndIntercept = " << fbgndintercept << " +/- " << ebgndintercept << " counts/keV " << endl;
	cout << "N_counts = " << integral << " +/- " << eintegral << " counts" << endl;
	cout << "------------------------------------------------" << endl;
	

	gStyle->SetOptStat(0);
	TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
	c1->cd();
	ecal_41->SetLineColor(kBlack);
	ecal_41->SetTitle("Clover energies, 41Si ion gate, 0.5-10 us time gate");
	ecal_41->GetYaxis()->SetTitle("counts/keV");
	ecal_41->GetXaxis()->SetTitle("keV");
	ecal_41->GetXaxis()->SetRangeUser(1400, 1500);	
	ecal_41->Draw("hist");
	func->Draw("same");

	/*
	TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
	c2->cd();
	ecal_42->SetLineColor(kRed);
	ecal_42->SetTitle("Clover energies, 42Si ion gate, 0-10 us time gate");
	ecal_42->GetYaxis()->SetTitle("counts/keV");
	ecal_42->GetXaxis()->SetTitle("keV");
	ecal_42->GetXaxis()->SetRangeUser(1400, 1500);	
	ecal_42->Draw("hist");
	
	TCanvas *c3 = new TCanvas("c3", "c3", 800, 600);
	c3->cd();
	ecal_42_scale->SetLineColor(kRed);
	ecal_42_scale->SetTitle("Clover energies, 42Si ion gate, 0-10 us time gate. Scale = 4.3");
	ecal_42_scale->GetYaxis()->SetTitle("counts/keV");
	ecal_42_scale->GetXaxis()->SetTitle("keV");
	ecal_42_scale->GetXaxis()->SetRangeUser(1400, 1500);	
	ecal_42_scale->Draw("hist");
	ecal_41->Draw("same");

	TCanvas *c4 = new TCanvas("c4", "c4", 800, 600);
	c4->cd();
	ecal_40->SetLineColor(kBlue);
	ecal_40->SetTitle("Clover energies, 40Si ion gate, 1-10 us time gate");
	ecal_40->GetYaxis()->SetTitle("counts/keV");
	ecal_40->GetXaxis()->SetTitle("keV");
	ecal_40->GetXaxis()->SetRangeUser(500, 600);	
	ecal_40->Draw("hist");
	*/
}
