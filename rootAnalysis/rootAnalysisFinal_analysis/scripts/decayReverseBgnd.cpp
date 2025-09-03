double expDecay(double *x, double *p){
	return p[0]*pow(0.5, x[0]/p[1])+p[2]+p[3]*x[0];
}

void decayReverseBgnd(){

	string parentName = "28Ne";

	TFile *fRvrs = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/reverse/d%s-reverse.root", parentName.c_str()));

	TH1D *bgnd = (TH1D*)fRvrs->Get("allDecays");
	

	int nBinsBg = bgnd->GetNbinsX();
	TH1D *bgndShift = new TH1D("bgndShift", "bgndShift", nBinsBg, 0, 1750);
	for(int i = 1; i <= nBinsBg; i++){
		bgndShift->SetBinContent(i, bgnd->GetBinContent(i)+1750);
	}

	TF1 *decayFunc = new TF1("decayFunc", expDecay, 200, 1750, 3);
	decayFunc->SetParameters(25000, 400, 4000);

	gStyle->SetOptStat(0);

	TCanvas *c2 = new TCanvas("c2", "c2", 944, 600);
	c2->cd();
	bgndShift->GetXaxis()->SetTitle("(#beta time - implant time) + 1750 ms");
	bgndShift->GetYaxis()->SetTitle("counts / 5 ms");
	bgndShift->Draw();
	decayFunc->Draw("same");

	bgndShift->Fit(decayFunc, "R");

	TLatex lx;
	lx.SetTextSize(0.03);
	lx.SetTextAlign(12);
	lx.DrawLatexNDC(0.5, 0.85, Form("HL = %4.1f +/- %3.1f ms", decayFunc->GetParameter(1), decayFunc->GetParError(1)));
	lx.DrawLatexNDC(0.5, 0.8, Form("Amplitude = %5.0f  +/- %2.0f counts / 5 ms", decayFunc->GetParameter(0), decayFunc->GetParError(0)));
	lx.DrawLatexNDC(0.5, 0.75, Form("Const. term = %4.0f +/- %1.0f counts / 5 ms", decayFunc->GetParameter(2), decayFunc->GetParError(2)));
	//lx.DrawLatexNDC(0.5, 0.7, Form("Slope = %4.3f +/- %4.3f", decayFunc->GetParameter(3), decayFunc->GetParError(3)));
	lx.DrawLatexNDC(0.5, 0.7, Form("#chi^{2} / NDF = %4.3f", decayFunc->GetChisquare() / decayFunc->GetNDF()));
	lx.DrawLatexNDC(0.5, 0.65, Form("Total counts = %7.0f", bgndShift->Integral()));

	bgndShift->SetTitle(Form("%s decay curve, reverse correlation", parentName.c_str()));


	
	cout << "chi2 / NDF = " << decayFunc->GetChisquare() / decayFunc->GetNDF() << endl;



	
}
