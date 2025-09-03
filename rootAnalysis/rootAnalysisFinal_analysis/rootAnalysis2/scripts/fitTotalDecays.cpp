#include "fitTotalDecays.hpp"





void fitBgnd(TH1D *bgndShift, TF1* bgFunc){

	TCanvas *c2 = new TCanvas ("c2", "c2", 800, 600);
	c2->cd();

	bgndShift->SetLineColor(kBlue);
	bgndShift->Draw("hist");

	bgFunc->SetParName(0, "Initial Background Activity");
	bgFunc->SetParName(1, "Background Half-life");

	bgFunc->SetParameters(600, 200);

	bgndShift->Fit(bgFunc, "RS");

	bgFunc->SetLineColor(kAzure+10);
	bgFunc->Draw("same");
}



void MakeResidualPlot(TH1* htime, TF1* fitFunc){
	gStyle->SetOptStat(0);
	auto resid_canvas = new TCanvas("resid_canvas", "Residuals of Fit");
	int size = htime->GetNbinsX();
	double x[size], y[size];

	for(int i=0; i<size; ++i) {
		if(i<2) {
			x[i] = 0;
			y[i] = 0;
		}
		else {
			x[i] = htime->GetXaxis()->GetBinCenter(i);
			y[i] = (htime->GetBinContent(i) - fitFunc->Eval(x[i]))/TMath::Sqrt(htime->GetBinContent(i));
		}
	}

	TGraph *tg = new TGraph(size,x,y);

	tg->Draw("A*");
	//TRatioPlot *rp1 = new TRatioPlot(hist_to_fit,"",fit_result.Get());
   /*rp1->Draw();
   rp1->GetLowerRefYaxis()->SetTitle("ratio");
   rp1->GetUpperRefYaxis()->SetTitle("entries");*/
	//cout <<"Or here?" << endl;
   //resid_canvas->Update();
	//cout<<"and finally?"<<endl;
}

void fitTotalDecays(){

  	// First, which parent should we look at?
  	string parentName;
	cout << "Enter name of parent ion: ";
	cin >> parentName;

	DecayData data = getDecayData(parentName);

	// Get histograms, binnings, etc.
	TFile *f = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/bDecay/d%s.root", parentName.c_str()));
	TH1D *htime = (TH1D*)f->Get("allDecays");

	/*
	TFile *fRvrs = new TFile(Form("/projects/e21062/aad/rootAnalysisFinal/histograms/reverse/d%s-reverse.root", parentName.c_str()));
	TH1D *bgndRvrs = (TH1D*)fRvrs->Get("allDecays");

	int nBinsBg = bgndRvrs->GetNbinsX();
	TH1D *bgndShift = new TH1D("bgndShift", "bgndShift", nBinsBg, 0, 100);
	for(int i = 1; i <= nBinsBg; i++){
		bgndShift->SetBinContent(i, bgndRvrs->GetBinContent(i)+100);
	}
	*/

	int npts = htime->GetNbinsX();
	double binWidth =(htime->GetXaxis()->GetXmax() - htime->GetXaxis()->GetXmin())/(htime->GetXaxis()->GetNbins());

	
	/*
	if(npts != nBinsBg){
		cout << "WARNING: Background and decay spectra binned differently." << endl;
	}
	*/

	// Initial draw
	TCanvas *c = new TCanvas("c", "c", 800, 600);
	c->cd(); 	
	gStyle->SetOptStat(0);

	htime->SetLineColor(kBlack);
	htime->GetXaxis()->SetTitle("Decay time (ms)");
	htime->GetYaxis()->SetTitle(Form("counts / %5.2f ms", binWidth));
	htime->SetTitle(Form("%s decay gate", parentName.c_str()));	
	htime->Draw("hist");

	/*	
	bgndShift->SetLineColor(kBlue);
	bgndShift->Draw("hist same");
	*/
	
	c->Update();
	c->Modified();

	// Rebin
	double newBinWidth;
	cout << "Currently binned at " << binWidth << " ms/bin. Enter the new bin width, in ms: ";				
	cin >> newBinWidth;
	double NGroups = newBinWidth / binWidth;
	if(static_cast<int>(NGroups) == NGroups && static_cast<int>(npts/newBinWidth) == npts/newBinWidth){	
		htime->Rebin(NGroups);
		//bgndShift->Rebin(NGroups);
	}
	else{
		cout << "Error: newBinWidth must be an integer multiple of " << binWidth << " and must go evenly into " << npts << ". Continuing without rebinning." << endl;
		newBinWidth = binWidth;
	}

	// Set bin errors
	int npts2 = htime->GetNbinsX();
	for(int i = 1; i <=npts2; i++){
			htime->SetBinError(i, pow(htime->GetBinContent(i), 0.5));
			//bgndShift->SetBinError(i, pow(bgndShift->GetBinContent(i), 0.5));
	}

	htime->GetYaxis()->SetTitle(Form("Counts / %5.2f ms", newBinWidth));
	c->Update();
	c->Modified();


	//First we'll fit the background
	//TF1 *bgFit = new TF1("Background fit", expBgnd, 0, 100, 2);

	//fitBgnd(bgndShift, bgFit);	

	// Create fit function
	TF1 *fitFunc = new TF1("Total Fit", totalFit, 0, 100, 9);
	
	double chi2NDF = doFit(htime, fitFunc, data);

	c->cd();

	fitFunc->SetLineColor(kRed);
	fitFunc->SetNpx(5000);
	fitFunc->Draw("same");	
	TF1* parentFunc = DrawComponent(fitFunc, kRed, parentDecays, parentName.c_str());
	TF1* daughterFunc = DrawComponent(fitFunc, kGreen+1, daughterDecays, data.daughterName.c_str());
	TF1* betaNFunc = DrawComponent(fitFunc, kMagenta, betaNDecays, data.betaNName.c_str());
	TF1* beta2NFunc = DrawComponent(fitFunc, kCyan+1, beta2NDecays, data.beta2NName.c_str());
	TF1* bgndFunc = DrawComponent(fitFunc, kBlue-7, bgnd, "Background");

	TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg->AddEntry(htime, "Data", "l");	
	leg->AddEntry(parentFunc, parentName.c_str(), "l");
	leg->AddEntry(daughterFunc, data.daughterName.c_str(), "l");
	leg->AddEntry(betaNFunc, data.betaNName.c_str(), "l");
	leg->AddEntry(beta2NFunc, data.beta2NName.c_str(), "l");
	leg->AddEntry(bgndFunc, "Bgnd", "l");
	leg->Draw("same");
	
	gPad->SetLogy();

	double iA = fitFunc->GetParameter(2) / newBinWidth;
	double diA = fitFunc->GetParError(2) / newBinWidth;
	double pHL = fitFunc->GetParameter(1);
	double dpHL = fitFunc->GetParError(1);
	double nParentDecays = iA * pHL / log(2) * (1 - pow(2, -100/pHL));
	double errParentDecays = sqrt(pow(nParentDecays * diA / iA , 2) + pow(iA, 2)*pow(dpHL, 2)*pow(1/log(2) - pow(2, -100/pHL)*(1/log(2)+100/pHL), 2));
	double nDaughterDecays = (1-data.pbn-data.pb2n)*iA*pHL/log(2)/(pHL-data.dHL)*(data.dHL*(pow(2, -100/data.dHL)-1)-pHL*(pow(2, -100/pHL)-1));
	double nDaughterNDecays = data.pbn*iA*pHL/log(2)/(pHL-data.bnHL)*(data.bnHL*(pow(2, -100/data.bnHL)-1)-pHL*(pow(2, -100/pHL)-1));
	double nDaughter2NDecays = data.pb2n*iA*pHL/log(2)/(pHL-data.b2nHL)*(data.b2nHL*(pow(2, -100/data.b2nHL)-1)-pHL*(pow(2, -100/pHL)-1));

	// WRITE PARAMS
	cout << "------------------------RESULTS-------------------------" << endl;
	cout << "Initial activity = " << fitFunc->GetParameter(2) << " +/- " << fitFunc->GetParError(2) << " counts / " << newBinWidth << " ms" << endl;
	cout << "Parent HL = " << fitFunc->GetParameter(1) << " +/- " << fitFunc->GetParError(1) << " ms" << endl;
	cout << "Bgnd initial activity = " << fitFunc->GetParameter(0) << " +/- " << fitFunc->GetParError(0) << " counts / " << newBinWidth << " ms" << endl;
	cout << "Bgnd HL = " << fitFunc->GetParameter(8) << " +/- " << fitFunc->GetParError(8) << " counts / 0.25 ms" << endl;
	cout << "NUMBER OF DECAYS: " << endl;
	cout << "Parent decays = " << nParentDecays << " +/- " << errParentDecays << " decays" << endl;
	cout << "Daughter decays = " << nDaughterDecays << endl;
	cout << "Beta-N daughter decays = " << nDaughterNDecays << endl;
	cout << "Beta-2N daughter decays = " << nDaughter2NDecays << endl;	
	cout << "FIXED PARAMETERS:" << endl;
	cout << "P0n = " << (1-data.pbn-data.pb2n)*100 << "%" << endl;	
	cout << "P1n = " << data.pbn*100 << "%" << endl;
	cout << "P2n = " << data.pb2n*100 << "%" << endl;
	cout << "Daughter HL = " << data.dHL << " ms" << endl;	
	cout << "Beta-1n daughter HL = " << data.bnHL << " ms" << endl;	
	cout << "Beta-2n daughter HL  = " << data.b2nHL << " ms" << endl;
	cout << "Chi2/NDF = " << chi2NDF << endl;	
	cout << "--------------------------------------------------------" << endl;

	MakeResidualPlot(htime, fitFunc);

	//Un-comment for errorCalc
	/*
	delete htime;
	delete fitFunc;
	f->Close();
	*/
 
}
