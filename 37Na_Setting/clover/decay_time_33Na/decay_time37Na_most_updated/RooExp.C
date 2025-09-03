#include "TCanvas.h"
#include "TH1D.h"
#include "TF1.h"
#include "TFile.h"
#include "TMath.h"
#include "RootTools.hpp"

void RooExp() {
    // Step 1: Get the decay time distribution histogram (TH1D)
    TH1D *h1 = (TH1D*)roottools::GetDecayTimeDistribution("/projects/e21062/tg/37Na/Decay_Vs_Radius_Reverse1_31F.root", "37Na");

    // Set the histogram range to be between 0 and 100
    h1->GetXaxis()->SetRangeUser(-100, 0);

    // Step 2: Define the exponential function A0 * exp(lambda * x)
    // A0 is the amplitude, and lambda is the decay constant
    TF1 *expFunc = new TF1("expFunc", "[0]*exp([1]*x)", -100,0);  // [0]: A0 (amplitude), [1]: lambda (decay constant)

    // Set initial parameter guesses: [0] for amplitude and [1] for decay constant
    expFunc->SetParameters(10, -0.0005);  // Initial guesses: A0 = 10, lambda = -0.05

    // Step 3: Fit the function to the histogram data
    h1->Fit(expFunc, "RLLOEMC");  // "R" means use the defined fit range [0, 100]

    // Step 4: Create a canvas to draw the result
    TCanvas* c1 = new TCanvas("c1", "Exponential Decay Fit with TF1", 800, 600);
    h1->Draw();           // Draw the histogram
    expFunc->Draw("same"); // Draw the fitted exponential function on the same plot

    // Step 5: Save the canvas as an image file
    c1->SaveAs("exponential_fit_TF1.png");

    // Clean up (optional)
   
}
