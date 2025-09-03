void blurg(){

	string parentName = "24F";	

	TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/bDecay/d%s.root", parentName.c_str()));
	TH2D *h2 = (TH2D*)f->Get("coinc");

	int projMin = 3101;
	int projMax = 3103;

	TH1D *h = h2->ProjectionX("h", projMin, projMax-1);
	
	gStyle->SetOptStat(0);

	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();
	h->SetTitle(Form("#gamma-#gamma coincidences in %s gate, %d-%d keV #gamma gate", parentName.c_str(), projMin, projMax));
	h->GetXaxis()->SetTitle("keV");
	//h->GetXaxis()->SetRangeUser(450, 650);
	h->GetYaxis()->SetTitle("Counts / 2 keV");
	h->Draw("hist");



}
