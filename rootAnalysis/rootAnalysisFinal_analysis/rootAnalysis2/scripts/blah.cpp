void blah(){

	TFile *f = new TFile("/projects/e21062/aad/rootanalysis/root_files/gamma_implant_hists/i32Na_hists.root");

	TH2D *hist = (TH2D*)f->Get("ecal_vs_t_32Na");

	TH2D *hist2 = new TH2D("h", "Clover energy versus time since ^{32}Na implant", 1240, -10, 300, 4000, 1, 4001);

	for(int i=161; i<1400; i++){
		for(int j = 1; j < 4000; j++){
		
		}
		
	}

	hist2->Draw("colz");


}
