#include <string>

void file_update(){

	string ion;
	cout << "Enter ion to add to file: ";
	cin >> ion;

	TFile *fold = new TFile("/projects/e21062/aad/rootanalysis/root_files/bdelayed_hists/i32Na_e_vs_t.root");
	TFile *fnew = TFile::Open("/projects/e21062/aad/rootanalysis/root_files/bdelayed_hists/clover_vs_decay_time.root", "UPDATE");

	TH2D *h = (TH2D*)fold->Get("h");
	
	double xbins = (h->GetXaxis()->GetXmax() - h->GetXaxis()->GetXmin())/h->GetNbinsX();  // in ms
	double ybins = (h->GetYaxis()->GetXmax() - h->GetYaxis()->GetXmin())/h->GetNbinsY();  // in keV

	h->SetName(Form("i%s", ion.c_str()));
	h->SetTitle(Form("Clover energy versus time between %s implant and beta decay", ion.c_str()));
	h->GetXaxis()->SetTitle(Form("counts / %5.3f ms", xbins));
	h->GetYaxis()->SetTitle(Form("counts / %3.1f keV", ybins));
	
	h->Write();
	fnew->Write();
	fnew->Close();
	fold->Close();


}
