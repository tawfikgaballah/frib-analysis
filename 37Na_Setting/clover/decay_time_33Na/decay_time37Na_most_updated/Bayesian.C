#include <TH1D.h>
#include <TF1.h>
#include <cmath>
#include <vector>
#include "RootTools.hpp"
#include "TSystem.h"

// #include "bat/usr/local/bin/include/BAT/BCModel.h"
#include "BAT/BCHistogramFitter.h"
#include "BAT/BCMath.h"
#include "BAT/BCParameter.h"
#include "BAT/BCEngineMCMC.h"
// Define the Bateman function for the total rate calculation
double TotalRate(double *x, double *par) {
    double t = x[0];  // Time (ms)

    // Parameters
    double N0 = par[0];
    double N1 = par[1];  // Normalization constant

    double lambda_mother = par[2];  // Decay constant of the mother nucleus
    double B1 = par[3];  // Branching ratio for the first daughter (1n)
    double B2 = par[4];  // Branching ratio for the second daughter (2n)
    double B3 = par[5];  // Branching ratio for the third daughter (3n)

    double lambda_daughter1 = par[6];  // Decay constant of first daughter (1n)
    double lambda_daughter2 = par[7];  // Decay constant of second daughter (2n)
    double lambda_daughter3 = par[8];  // Decay constant of third daughter (3n)
    double lambda_daughter4 = par[9];  // Decay constant of fourth daughter (B3n)

    // Background contribution
    double bg_exp = par[10];  // Exponential background



const double epsilon = 1e-10;  // Small constant to avoid zero or negative values

    // if (lambda_mother <= 0 || lambda_daughter1 <= 0 || lambda_daughter2 <= 0 || 
    //     lambda_daughter3 <= 0 || lambda_daughter4 <= 0 || N0 <= 0 || N1 <= 0 ||(B1+B2+B3)>1) {
    //     return 0;  // Return 0 if any invalid parameters are found
    // }


    
    // Bateman equation terms
    double mother_contrib = N1 * lambda_mother * exp(-lambda_mother * t);
    double daughter1_contrib = lambda_daughter1 * N1 * (1 - B1 - B2 - B3) * (lambda_mother / (lambda_mother - lambda_daughter1)) *
                               (-exp(-lambda_daughter1 * t) + exp(-lambda_mother * t));
    double daughter2_contrib = lambda_daughter2 * N1 * B1 * (lambda_mother / (lambda_mother - lambda_daughter2)) *
                               (-exp(-lambda_daughter2 * t) + exp(-lambda_mother * t));
    double daughter3_contrib = lambda_daughter3 * N1 * B2 * (lambda_mother / (lambda_mother - lambda_daughter3)) *
                               (-exp(-lambda_daughter3 * t) + exp(-lambda_mother * t));
    double daughter4_contrib = lambda_daughter4 * N1 * B3 * (lambda_mother / (lambda_mother - lambda_daughter4)) *
                               (-exp(-lambda_daughter4 * t) + exp(-lambda_mother * t));
    double background_contrib = N0 * exp(-bg_exp * t);

    // Total rate
    double total_rate = mother_contrib + daughter1_contrib + daughter2_contrib +
                        daughter3_contrib + daughter4_contrib + background_contrib;



 // if (std::isnan(total_rate) || std::isinf(total_rate)) {
 //        return 0;  // Return 0 if the result is NaN or inf
 //    }

 // if (total_rate < 0) {
 //        total_rate = 0;
 //    }
    
    return total_rate;
}

void Bayesian() {
  gSystem->AddLinkedLibs("bat/usr/local/bin/lib/");
   gSystem->AddIncludePath("bat/BAT/");
  // gSystem->AddIncludePath("-I./bat/usr/local/bin/include/BAT/");
  // gSystem->Load("./bat/usr/local/bin/lib/libBATmodels.so");
  // gSystem->Load("./bat/usr/local/bin/lib/libBAT.so");
 

    // Load the decay time distribution from a ROOT file
    TH1D* hDecayTime = roottools::GetDecayTimeDistribution("/projects/e21062/tg/37Na/DecayTime_Vs_Radius.root", "37Na");

    // Create the TF1 object for the Bateman equation model
    TF1* fTotal = new TF1("fTotal", TotalRate, 0, 30, 11);

   

    // // Set parameter ranges (directly accessing the TF1 object you passed)
    // fTotal->SetParLimits(0, 0.1, 10.0);  // N0
    // fTotal->SetParLimits(1, 0.1, 50.0); // N1
    // fTotal->SetParLimits(2, 0.1, 100);  // Lambda mother (converted from halflife)
    // fTotal->SetParLimits(3, 0.0, 1.0);   // B1
    // fTotal->SetParLimits(4, 0.0, 1.0);   // B2
    // fTotal->SetParLimits(5, 0.0, 1.0);   // B3
    // fTotal->SetParLimits(6, 0.001, 1.0); // Lambda daughter 1
    // fTotal->SetParLimits(7, 0.001, 1.0); // Lambda daughter 2
    // fTotal->SetParLimits(8, 0.001, 1.0); // Lambda daughter 3
    // fTotal->SetParLimits(9, 0.001, 1.0); // Lambda daughter 4
    // fTotal->SetParLimits(10,0, 0.00003); // Exponential background



    // fTotal->FixParameter(0, 9.89481e-01);   // Initial guess for N0
    // fTotal->SetParameter(1, 3.56588e01);  // Initial guess for N1
    // fTotal->SetParameter(2, 0.693/3);   // Initial guess for Lambda mother
    // fTotal->FixParameter(3, 0.51);   // Initial guess for B1
    // fTotal->FixParameter(4, 0.24);   // Initial guess for B2
    // fTotal->FixParameter(5, 0.25);   // Initial guess for B3
    // fTotal->FixParameter(6, 1.08281e-01);   // Initial guess for Lambda daughter 1
    // fTotal->FixParameter(7, 9.62500e-02);   // Initial guess for Lambda daughter 2
    // fTotal->FixParameter(8, 6.13274e-02);   // Initial guess for Lambda daughter 3
    // fTotal->FixParameter(9, 3.46500e-02);   // Initial guess for Lambda daughter 4
    // fTotal->FixParameter(10, 8.94449e-04); // Initial guess for Exponential background


    hDecayTime->GetXaxis()->SetRangeUser(0,30);
     // Create a histogram fitter
    BCHistogramFitter histFitter(*hDecayTime, *fTotal);



   //  histFitter.MarginalizeAll();

 //    // Print summary of the results
 //    histFitter.PrintSummary();

 //    // // Clean up
 //    // delete fTotal;
 // // Optionally, you can also visualize the marginalized posterior distributions
 //    histFitter.PrintAllMarginalized("marginalized_plots.pdf");








     // set Metropolis as marginalization method
    histFitter.SetMarginalizationMethod(BCIntegrate::kMargMetropolis);



    //  // Enable adaptive proposal to improve convergence
    // histFitter.SetFlagAdaptiveProposal(true);

    // // Set the number of iterations for the pre-run to allow the sampler to adapt
    // histFitter.SetNIterationsPreRun(3000);

    // **Edit 3: Define parameter ranges and priors**
    // Set parameter ranges and, where appropriate, Gaussian priors
    // Parameter 0: N0 (Background normalization)
    histFitter.GetParameter(0).SetLimits(0.1, 10.0);
    // histFitter.GetParameter(0).SetPrior(new BCPriorGauss(0.989481, 0.1)); // Mean and standard deviation

    // Parameter 1: N1 (Normalization constant)
    histFitter.GetParameter(1).SetLimits(0.1, 50.0);
    // histFitter.GetParameter(1).SetPrior(new BCPriorGauss(35.6588, 1.0));

    // Parameter 2: lambda_mother (Decay constant of the mother nucleus)
    histFitter.GetParameter(2).SetLimits(0.01, 10.0);
    histFitter.GetParameter(2).SetPriorConstant(); // Uniform prior

    // Parameters 3-5: Branching ratios B1, B2, B3
    // Fix these parameters if they are well-known
    histFitter.GetParameter(3).Fix(0.51); // B1
    histFitter.GetParameter(4).Fix(0.24); // B2
    histFitter.GetParameter(5).Fix(0.25); // B3

    // Parameters 6-9: Decay constants of daughters
    // Fix these parameters if they are well-known
    histFitter.GetParameter(6).Fix(0.108281); // lambda_daughter1
    histFitter.GetParameter(7).Fix(0.09625);  // lambda_daughter2
    histFitter.GetParameter(8).Fix(0.0613274);// lambda_daughter3
    histFitter.GetParameter(9).Fix(0.03465);  // lambda_daughter4

    // Parameter 10: Exponential background
    histFitter.GetParameter(10).SetLimits(0.0, 0.003);
    // histFitter.GetParameter(10).SetPrior(new BCPriorGauss(8.94449e-04, .0001)); // Uniform prior

    // // set precision
    // histFitter.SetPrecision(BCEngineMCMC::kQuick);

    // integrate function over bin (true) or use linear interpolation
    histFitter.SetFlagIntegration(false);

    // set priors
    histFitter.GetParameters().SetPriorConstantAll();

    // perform fit
    histFitter.Fit();

    // calculate p value...
    double p = histFitter.CalculatePValueFast(histFitter.GetBestFitParameters());
    double p_corrected = BCMath::CorrectPValue(p, histFitter.GetNFreeParameters(), hDecayTime->GetNbinsX());
     std::cout << "p-value: " << p << ", Corrected p-value: " << p_corrected << std::endl;


    // and correct for the degrees of freedom to yield an approximately
    // uniformly distributed p value for the true model
    // cout << "p value " << p << ", corrected for degrees of freedom " << BCMath::CorrectPValue(p, histFitter.GetNFreeParameters(), hDecayTime->GetNbinsX()) << endl;
     histFitter.PrintSummary();
    // print marginalized distributions
    histFitter.PrintAllMarginalized("distributions.pdf");

    // print data and fit
    TCanvas c1("c1");
    histFitter.DrawFit("", true); // draw with a legend
    c1.Print("fit.pdf");
}
