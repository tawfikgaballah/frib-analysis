double funky(double *x, double *p){
	double xmod = x[0]*0.05;
	return exp(p[0]+p[1]*xmod+p[2]*log(xmod)/xmod+p[3]/xmod+p[4]/(xmod*xmod)+p[5]/(xmod*xmod*xmod));
}

void efficiencyFit(){

	double ecal[] = {/*39.8,*/ 121.7, 244.8, 344.3, 778.8, 867.3, 1213.0, 1299.2, 1408.0};
	double eff[] = {/*1502,*/ 40637, 29135, 22523, 11671, 10737, 8337, 7884, 7561};

	TGraph *gr = new TGraph(8, ecal, eff);

	TF1 *func = new TF1("func", funky, 0, 2000, 6);
	gr->Fit(func);

	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd();	

	gr->SetMarkerStyle(3);
	gr->GetXaxis()->SetRangeUser(0, 2000);
	gr->Draw("AP");

}
