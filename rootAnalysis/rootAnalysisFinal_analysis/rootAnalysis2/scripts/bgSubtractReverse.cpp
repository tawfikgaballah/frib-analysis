//p0 = constant multiple, p1 = mean, p2 = sigma, p3 = bgnd slope, p4 = bgnd intercept
double gaussian(double *x, double *p){return p[0]*exp(-0.5*pow((x[0]-p[1])/p[2], 2)) + p[3]*x[0] + p[4];}

void bgSubtractReverse(){

	//TFile *ffwd = new TFile("/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/bDecay/d30Ne-37ms-2mm.root");
	//TFile *frvs = new TFile("/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/reverse/d30Ne-37ms-2mm-reverse.root");
	TFile *ffwd = new TFile("/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/bDecay/d30Ne-37ms-3mm.root");
	TFile *frvs = new TFile("/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/reverse/d30Ne-37ms-3mm-reverse.root");


	TH1D *hfwd = (TH1D*)ffwd->Get("clover_ecal");
	TH1D *hrvs = (TH1D*)frvs->Get("clover_ecal");

	bool rebin = false;

	// Step 1: Fit BG peak in fwd spectrum

	if(rebin == true){
		hfwd->Rebin(2);
		hfwd->GetYaxis()->SetTitle("counts / 2 keV");
	}

	gStyle->SetOptStat(0);
	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();
	hfwd->GetXaxis()->SetRangeUser(1600, 1700);
	hfwd->Draw();

	c->Update();
	c->Modified();
	c->WaitPrimitive();

	TF1* funcFwd = new TF1("funcFwd", gaussian, 1, 8001, 5);
	funcFwd->SetParName(0, "Constant");
	funcFwd->SetParName(1, "Mean");
	funcFwd->SetParName(2, "Sigma");
	funcFwd->SetParName(3, "BgndSlope");
	funcFwd->SetParName(4, "BgndIntercept");

	funcFwd->SetParameter(0, 6);
	//funcFwd->SetParameter(1, 617);	
	//funcFwd->SetParameter(1, 1633);
	funcFwd->SetParameter(1, 1672);
	funcFwd->SetParameter(2, 1);
	funcFwd->FixParameter(3, 0);
	funcFwd->SetParameter(4, 2);
	
	//funcFwd->SetRange(580, 660);
	//funcFwd->SetRange(600, 630);
	//funcFwd->SetRange(1657, 1695);
	funcFwd->SetRange(1662, 1692);	
	//funcFwd->SetRange(1600, 1646);

	hfwd->Fit(funcFwd, "LR");	

	int fitpts= funcFwd->GetNumberFitPoints();
	cout << "fitpts = " << fitpts << endl;


	funcFwd->Draw("same");

	c->Update();
	c->Modified();
	c->WaitPrimitive();

	// Step 2: Fit BG peak in reverse spectrum

	if(rebin == true){
		hrvs->Rebin(2);
		hrvs->GetYaxis()->SetTitle("counts / 2 keV");	
	}

	gStyle->SetOptStat(0);
	TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
	c2->cd();
	hrvs->GetXaxis()->SetRangeUser(1600, 1700);
	hrvs->Draw();

	c2->Update();
	c2->Modified();
	c2->WaitPrimitive();

	TF1* funcRvs = new TF1("funcRvs", gaussian, 1, 8001, 5);
	funcRvs->SetParName(0, "Constant");
	funcRvs->SetParName(1, "Mean");
	funcRvs->SetParName(2, "Sigma");
	funcRvs->SetParName(3, "BgndSlope");
	funcRvs->SetParName(4, "BgndIntercept");

	funcRvs->SetParameter(0, 50);
	//funcRvs->SetParameter(1, 617);
	//funcRvs->SetParameter(1, 1633);
	funcRvs->SetParameter(1, 1672);
	funcRvs->SetParameter(2, 1);
	funcRvs->FixParameter(3, 0);
	funcRvs->SetParameter(4, 10);
	
	//funcRvs->SetRange(600, 630);
	funcRvs->SetRange(1657, 1695);
	//funcRvs->SetRange(1623, 1646);

	hrvs->Fit("funcRvs", "LR");

	
	funcRvs->Draw("same");

	c2->Update();
	c2->Modified();
	c2->WaitPrimitive();

	// Step 3: Take ratio of constants to get scale factor

	double cf = funcFwd->GetParameter(0);
	double cr = funcRvs->GetParameter(0);
	double sigf = funcFwd->GetParameter(2);
	double sigr = funcRvs->GetParameter(2);

	double errcf = funcFwd->GetParError(0);
	double errcr = funcRvs->GetParError(0);
	double errsigf = funcFwd->GetParError(2);
	double errsigr = funcRvs->GetParError(2);

	double areaFwd = pow(2*M_PI, 0.5)*cf*sigf;
	double areaRvs = pow(2*M_PI, 0.5)*cr*sigr;

	double scale = areaFwd / areaRvs;
	double errScale = scale*sqrt(pow(errcf/cf, 2)+pow(errcr/cr, 2)+pow(errsigf/sigf, 2)+pow(errsigr/sigr, 2));

	//scale = 0.1;
	//errScale = scale * 0.37;

	cout << "scale = " << scale << " +/- " << errScale << endl;

	// Step 4: Subtract scaled background from fwd histogram

	TH1D* hscale = (TH1D*)hrvs->Clone();
	hscale->Scale(scale);

	TH1D *hsub = new TH1D("hsub", "hsub", hfwd->GetNbinsX(), 1, 8001);
	hsub->Add(hfwd, hrvs, 1, -scale);

	for(int i = 1; i < hsub->GetNbinsX(); i++){
		double Nf = hfwd->GetBinContent(i);
		double Nr = hrvs->GetBinContent(i);
		double err = sqrt(Nf+Nr*pow(scale, 2)+pow(Nr*errScale, 2));
		hsub->SetBinError(i, err);
	}

	TCanvas *c3 = new TCanvas("c3", "c3", 800, 600);
	c3->cd(); c3->Divide(2, 2);

	c3->cd(1);
	hrvs->SetLineColor(kRed);
	hrvs->SetTitle("Forward and reverse");
	hrvs->Draw("hist");
	hfwd->SetLineColor(kBlue);
	hfwd->Draw("hist same");
	c3->cd(2);
	hscale->SetTitle("Forward and scaled reverse");
	hscale->SetLineColor(kOrange+7);
	hscale->Draw("hist");
	hfwd->Draw("hist same");	
	c3->cd(3);
	hfwd->SetTitle("Forward and subtracted");
	hfwd->Draw("hist");
	hsub->SetLineColor(kBlack);
	hsub->Draw("hist same");
	c3->cd(4);
	hsub->SetTitle("Subtracted clover spectrum");
	//hsub->SetMarkerStyle(7);
	hsub->GetXaxis()->SetTitle("Clover energy, keV");
	if(rebin == true)		
		hsub->GetYaxis()->SetTitle("counts / 2 keV");
	else
		hsub->GetYaxis()->SetTitle("counts / 1 keV");
	hsub->Draw("hist");

	TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg->AddEntry(hfwd, "Forward", "l");	
	leg->AddEntry(hrvs, "Reverse", "l");
	leg->AddEntry(hscale, "Scaled reverse", "l");
	leg->AddEntry(hsub, "Subtracted", "l");
	c3->cd(2);
	leg->Draw("same");




	


}
