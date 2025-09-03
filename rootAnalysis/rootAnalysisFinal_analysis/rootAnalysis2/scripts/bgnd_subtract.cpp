void bgnd_subtract(){

	TFile *f = new TFile("/projects/e21062/aad/rootanalysis/root_files/hist_32Na.root");

	TH2D *ecal_vs_t_32Na = (TH2D*)f->Get("ecal_vs_t_32Na");
	TH1D *bgnd = new TH1D("bgnd", "Gamma background from -10->0 us", 8000, 1, 8001);
	TH1D *bgnd_scaled = new TH1D("bgnd_scaled", "Scaled gamma background from -10->0 us", 8000, 1, 8001);
	TH1D *ecal = new TH1D("ecal", "Decays + background from 1->150 us", 8000, 1, 8001);
	TH1D *ecal_sub = new TH1D("ecal_sub", "Bgnd subtracted energies", 8000, 1, 8001);

	bgnd = ecal_vs_t_32Na->ProjectionY("bgnd", 161, 200);
	bgnd_scaled = ecal_vs_t_32Na->ProjectionY("bgnd_scaled", 161, 200);
	ecal = ecal_vs_t_32Na->ProjectionY("ecal", 205, 800);
	bgnd_scaled->Scale(15);

	for(int i = 1; i <= 8000; i++){
		double content, error;
		content = ecal->GetBinContent(i) - 15*(bgnd->GetBinContent(i));
		ecal_sub->SetBinContent(i, content);

		error = pow(ecal->GetBinContent(i) + pow(15, 2)*bgnd->GetBinContent(i), 0.5);
		ecal_sub->SetBinError(i, error);

		ecal->SetBinError(i, pow(ecal->GetBinContent(i), 0.5));

		bgnd->SetBinError(i, pow(bgnd->GetBinContent(i), 0.5));

		bgnd_scaled->SetBinError(i, pow(bgnd_scaled->GetBinContent(i), 0.5));
		
	}	
	
	//ecal_sub->Add(ecal, bgnd, 1, -15);

	
	gStyle->SetOptStat(0);
	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();
	ecal->SetLineColor(kRed);
	ecal->SetMarkerStyle(7);
	ecal->SetMarkerColor(kRed);
	ecal->GetXaxis()->SetRangeUser(200, 450);
	//ecal->Draw("PE");
	bgnd->SetLineColor(kBlack);
	bgnd->SetMarkerStyle(7);
	bgnd->SetMarkerColor(kBlack);	
	bgnd->Draw("same PE");
	bgnd_scaled->SetLineColor(kBlue);
	bgnd_scaled->SetMarkerStyle(7);
	bgnd_scaled->SetMarkerColor(kBlue);
	bgnd_scaled->Draw("same PE");
	ecal_sub->SetLineColor(kGreen);
	ecal_sub->SetMarkerStyle(7);
	ecal_sub->SetMarkerColor(kGreen);
	//ecal_sub->Draw("same PE");
	
	TLegend *leg = new TLegend(0.5, 0.8, 0.9, 0.9);
	//leg->AddEntry(ecal, "Unsubtracted clover spectrum", "pl");
	leg->AddEntry(bgnd, "Unscaled background", "pl");
	leg->AddEntry(bgnd_scaled, "Scaled background", "pl");
	//leg->AddEntry(ecal_sub, "Background subtracted clover spectrum", "pl");
	leg->Draw("same");

	//TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
	//c2->cd();
	//ecal_vs_t_32Na->Draw("colz");

}
