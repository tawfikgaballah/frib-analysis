void e16032Test(){

	TFile *f = new TFile("histograms/d31Na-e16032.root");

	TH1D *h = (TH1D*)f->Get("");

	delete fTotal;

	TCanvas *c = new TCanvas("c", "c", 800, 600);
	h->Draw();

}
