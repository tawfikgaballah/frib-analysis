#include <TFile.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TProfile.h>
#include <iostream>

void straighten_PID(const char* filename = "Amelia_Files_33_37_Na_PID_6mm.root") {
    // Load file and histogram
    TFile* f = TFile::Open(filename, "READ");
    if (!f || f->IsZombie()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    TH2D* hPID = dynamic_cast<TH2D*>(f->Get("PID_Decay_Forward"));
    if (!hPID) {
        std::cerr << "Histogram 'PID_Decay_Forward' not found!" << std::endl;
        f->Close();
        return;
    }

    // Project profile: mean dE vs ToF
    TProfile* prof = hPID->ProfileX("prof", 1, -1, "s");

    // Fit the tilt: linear trend in ΔE vs ToF
    TF1* linFit = new TF1("linFit", "[0]*x + [1]", prof->GetXaxis()->GetXmin(), prof->GetXaxis()->GetXmax());
    prof->Fit(linFit, "RQ");

    double slope = linFit->GetParameter(0);
    double intercept = linFit->GetParameter(1);

    std::cout << "Fitted tilt: ΔE = " << slope << " * ToF + " << intercept << std::endl;

    // Prepare corrected histogram: A/Q vs corrected ΔE
    int nbinsX = hPID->GetNbinsX();
    int nbinsY = hPID->GetNbinsY();
    TH2D* hPID_corrected = new TH2D("hPID_corrected", "PID: A/Q vs Corrected #DeltaE",
                                    nbinsX, 0.0, 2.0,  // A/Q axis (approx)
                                    nbinsY, -1000, 1000); // ΔE_corr range  adjust as needed

    hPID_corrected->GetXaxis()->SetTitle("A/Q");
    hPID_corrected->GetYaxis()->SetTitle("Corrected #DeltaE");

    // Simple A/Q estimate from ToF (you can refine this)
    auto ToF_to_AQ = [](double tof) {
        double a = -8e-5, b = -0.1238, c = -43.813;
        return a * tof * tof + b * tof + c;
    };

    // Loop and correct each bin
    for (int ix = 1; ix <= nbinsX; ++ix) {
        double tof = hPID->GetXaxis()->GetBinCenter(ix);
        double aq = ToF_to_AQ(tof);

        for (int iy = 1; iy <= nbinsY; ++iy) {
            double dE = hPID->GetYaxis()->GetBinCenter(iy);
            double content = hPID->GetBinContent(ix, iy);
            if (content <= 0) continue;

            // Shear correction (flatten ΔE vs ToF trend)
            double dE_corr = dE - (slope * tof + intercept);
            hPID_corrected->Fill(aq, dE_corr, content);
        }
    }

    // Plot results
    TCanvas* c1 = new TCanvas("c1", "Corrected PID", 1000, 800);
    hPID_corrected->Draw("COLZ");

  
}
