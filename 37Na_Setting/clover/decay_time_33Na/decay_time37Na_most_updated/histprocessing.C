TH1D* FlipHistogramSign(TH1D* originalHist) {
    // Get the number of bins and the range of the original histogram
    int nBins = originalHist->GetNbinsX();
    double xMin = originalHist->GetXaxis()->GetXmin();
    double xMax = originalHist->GetXaxis()->GetXmax();

    // Create a new histogram with inverted x-axis limits
    TH1D* flippedHist = new TH1D("flippedHist", "Flipped Histogram;X axis;Counts",
                                 nBins, -xMax, -xMin);

    // Loop over each bin of the original histogram
    for (int i = 1; i <= nBins; i++) {
        // Get the content of the current bin
        double content = originalHist->GetBinContent(i);
	if(content!=0){
        // Calculate the corresponding bin in the new histogram
        int newBinIndex = nBins - i + 1;

        // Set the content of the corresponding bin in the new histogram
        flippedHist->SetBinContent(newBinIndex, content);
	}
    }

    // Optionally, draw the new histogram
    flippedHist->Draw();
    return flippedHist;
}




void histprocessing(int i=35, int j=34){

  TCanvas* canvas=new TCanvas("","");
  canvas->Divide(3);
  canvas->cd(1);
  TFile* file=new TFile(Form("./../position_Vs_decaytime_%dNa_%dNa_Decay_3mmReverse.root",i,j),"READ");
  TH2D* hist2d=(TH2D*)file->Get(Form("Position_Vs_hIonDecayTime_%dNa",i));
TH1D* myHist=(TH1D*)hist2d->ProjectionX();
// Now flip the histogram
 TH1D* myHist_37=(TH1D*) myHist;

 TFile* file1=new TFile(Form("./../position_Vs_decaytime_%dNa_%dNa_Decay_3mm.root",i,j),"READ");
 TH2D* hist2d1=(TH2D*)file1->Get(Form("Position_Vs_hIonDecayTime_%dNa",i));
TH1D* myHist1_37=(TH1D*)hist2d1->ProjectionX();
 TH1D* clone=(TH1D*)myHist1_37->Clone();
 canvas->cd(2);
 clone->Draw();
 // myHist1_37->Rebin(5);
 // myHist_37->Rebin(5);
 // myHist1_37->Add(myHist_37,-1);
 canvas->cd(3);
 myHist1_37->Draw();

 myHist1_37->SetName(Form("Position_Vs_hIonDecayTime_%dNa",i));
 myHist_37->SetName(Form("Position_Vs_hIonDecayTime_%dNa_Reverse",i));

 TFile* output=new TFile("./../position_Vs_decaytime_35Na_34Na_Decay_Forward-Reverse-3mm.root","UPDATE");
 myHist_37->Write();
 myHist1_37->Write();
 
 
}
