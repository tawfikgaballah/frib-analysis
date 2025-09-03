#include "TFile.h"
#include "TH1.h"
#include "TSpectrum.h"
#include "TF1.h"
#include "TCanvas.h"

void auto_fitter() {
  // Open the ROOT file
  TFile *file = new TFile("output_Co_calibration_e21062-a_run1240.root", "READ");

  if (!file || file->IsZombie()) {
    std::cerr << "Error opening file" << std::endl;
    return;
  }

  // Retrieve the histogram
  TH1D *hist = (TH1D*)file->Get("/raw_time/LaBr3_Energy");

  if (!hist) {
    std::cerr << "Histogram not found" << std::endl;
    return;
  }

  // Create a canvas to display the histogram and fits
  TCanvas *canvas = new TCanvas("canvas", "Fit Histogram with Gaussians", 800, 600);
  hist->Draw();

  // Use TSpectrum to find peaks
  TSpectrum *spectrum = new TSpectrum(3*3);  // Number of peaks to look for can be specified as an argument
  Int_t nPeaks = spectrum->Search(hist,5,"", 0.005); // Adjust parameters as needed

  // Retrieve the positions of the found peaks
  Double_t *xPeaks = spectrum->GetPositionX();

  for (int i = 0; i < nPeaks; i++) {
      // Define a Gaussian function for each peak
      TF1 *gauss = new TF1(Form("gauss%d", i), "gaus", xPeaks[i] - 15, xPeaks[i] + 15);
      gauss->SetParameters(hist->GetBinContent(hist->GetXaxis()->FindBin(xPeaks[i])), xPeaks[i], 5);
        
      // Fit the histogram with the Gaussian function
      hist->Fit(gauss, "R+"); // "R" means fit in the specified range, "+" to add the fit to the histogram

      gauss->SetLineColor(i + 1); // Set different colors for each fit
      gauss->Draw("same");
  }

  canvas->Update();
}

