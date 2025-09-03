#include <TH2D.h>
#include <TCanvas.h>

void FlipYAxis(TH2D* hist) {
    if (!hist) return;

    int nBinsX = hist->GetNbinsX();
    int nBinsY = hist->GetNbinsY();

    // Create a new histogram with flipped y-axis
    TH2D* flippedHist = new TH2D("flippedHist", hist->GetTitle(),
                                 nBinsX, hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax(),
                                 nBinsY, -hist->GetYaxis()->GetXmax(), -hist->GetYaxis()->GetXmin());

    // Loop over the bins and set the content with the y-axis flipped
    for (int i = 1; i <= nBinsX; ++i) {
        for (int j = 1; j <= nBinsY; ++j) {
            int flippedYBin = nBinsY - j + 1;  // Flip y-bin index
            double content = hist->GetBinContent(i, j);
	      double error = hist->GetBinError(i, j);
            flippedHist->SetBinContent(i, flippedYBin, content);
	    flippedHist->SetBinError(i, flippedYBin, error);
        }
    }
 flippedHist->SetEntries(hist->GetEntries());
    // Draw the original and flipped histograms
    TCanvas* canvas = new TCanvas("canvas", "Flipped Y-axis", 800, 600);
    canvas->Divide(2, 1);
    canvas->cd(1);
    hist->Draw("COLZ");
    canvas->cd(2);
    flippedHist->Draw("COLZ");
}

void FlipHist() {
    // Example usage
  TFile* file=new TFile("/projects/e21062/tg/37Na/Decay_Vs_Radius_Reverse.root", "read");
  TH2D* hist = (TH2D*)file->Get("/37Na/DecayTime_Vs_Radius_\^\{37\}Na");

    FlipYAxis(hist);
}
