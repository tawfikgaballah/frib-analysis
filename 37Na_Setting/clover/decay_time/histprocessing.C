TH1D* FlipHistogramSign(TH1D* originalHist) {
    // Get the number of bins and the range of the original histogram
    int nBins = originalHist->GetNbinsX();
    double xMin = originalHist->GetXaxis()->GetXmin();
    double xMax = originalHist->GetXaxis()->GetXmax();

    // Create a new histogram with inverted x-axis limits
    TH1D* flippedHist = new TH1D("flippedHist", "Flipped Histogram;X axis;Counts",
                                 nBins, -xMax, -xMin);

    // // Loop over each bin of the original histogram
    // for (int i = 0; i <= originalHist->GetEntries(); i++) {
    //     // Get the content of the current bin
       
    //   flippedHist->Fill((originalHist->GetEntry(i))*-1);
    // 	// }
    // }
    flippedHist->Add(originalHist,+1);
    // Optionally, draw the new histogram
    flippedHist->Draw();
    return flippedHist;
}




void histprocessing(){

  TCanvas* canvas=new TCanvas("","");
  canvas->Divide(3);
  canvas->cd(1);
TFile* file=new TFile("./../decaytime_35Na_34Na_Decay_3mm_Reverse.root","READ");
  TH1D* myHist=(TH1D*)file->Get("hIonDecayTime_35Na");
// TH1D* myHist=(TH1D*)hist2d->ProjectionX();
// Now flip the histogram
 TH1D* myHist_37=(TH1D*) FlipHistogramSign(myHist);

 TFile* file1=new TFile("./../decaytime_35Na_34Na_Decay_3mm.root","READ");
 TH1D* myHist1_37=(TH1D*)file1->Get("hIonDecayTime_35Na");
// TH1D* myHist1_37=(TH1D*)hist2d1->ProjectionX();
 TH1D* clone=(TH1D*)myHist1_37->Clone();
 canvas->cd(2);
 clone->Draw();
 // myHist1_37->Rebin(5);
 // myHist_37->Rebin(5);
 // myHist1_37->Add(myHist_37,-1);
 canvas->cd(3);
 myHist1_37->Draw();

 myHist1_37->SetName("Position_Vs_hIonDecayTime_35Na");
 myHist1_37->SetName("Position_Vs_hIonDecayTime_35Na");

  myHist_37->SetName("Position_Vs_hIonDecayTime_35Na_Reverse");
 myHist_37->SetName("Position_Vs_hIonDecayTime_35Na_Reverse");

 TFile* output=new TFile("./../decaytime_35Na_34Na_Decay_Forward-Reverse-3mm.root","RECREATE");
 myHist1_37->Write();
 myHist_37->Write();
 
 
 
}
