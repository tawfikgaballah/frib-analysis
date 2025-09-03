#include <TFile.h>
#include <TH2.h>
#include <TCanvas.h>
#include <iostream>
#include <cmath>

void convert_PID_AoverQ(const char* filename = "Amelia_Files_33_37_Na_PID_6mm.root") {
    // Open ROOT file
    TFile* f = TFile::Open(filename, "READ");
    if (!f || f->IsZombie()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Load original PID histogram: ToF (x) vs ΔE (y)
    TH2D* hPID = dynamic_cast<TH2D*>(f->Get("PID_Decay_Forward"));
    if (!hPID) {
        std::cerr << "Histogram 'PID_Decay_Forward' not found in file!" << std::endl;
        f->Close();
        return;
    }

    int nbinsX = hPID->GetNbinsX();
    int nbinsY = hPID->GetNbinsY();

    // Create output histogram: Z vs A/Q
    TH2D* hPID_Z_AQ = new TH2D("hPID_Z_AQ", "PID: Z vs A/Q",
                               nbinsX, 0.0, 5.0,    // A/Q range
                               nbinsY, 0.0, 30.0);  // Z range

    hPID_Z_AQ->GetXaxis()->SetTitle("A/Q");
    hPID_Z_AQ->GetYaxis()->SetTitle("Z");

    // ToF → A/Q calibration
    auto ToF_to_AQ = [](double tof) {
        double a = -8e-5, b = -0.1238, c = -43.813;
        return a * tof * tof + b * tof + c;
    };

    // ToF correction function: sqrt(dE) vs ToF
 

auto fit_function = [](double tof) {
    return 5.3838 * tof + 5727.8;
};

const double f_ref = fit_function(24.0);  // Normalize to typical ToF

    // Corrected ΔE → Z calibration
    auto dE_to_Z = [](double dE_corr) {
        double p0 = 0.6746, p1 = -3.7612, p2 = -0.0026;
        return p0 * std::sqrt(dE_corr) + p1 + p2 * dE_corr;
    };

    // Loop over histogram bins
    for (int ix = 1; ix <= nbinsX; ++ix) {
        double tof = hPID->GetXaxis()->GetBinCenter(ix);
        double aq = ToF_to_AQ(tof);

        for (int iy = 1; iy <= nbinsY; ++iy) {
            double dE = hPID->GetYaxis()->GetBinCenter(iy);
            double content = hPID->GetBinContent(ix, iy);

            if (content <= 0 || dE <= 0) continue;
double scale = fit_function(tof) / f_ref;
 double dE_corr =dE-fit_function(tof);

            //

            // Convert to Z
            double z = dE_to_Z(dE);
	    std::cout<<dE_corr<<"    "<<dE<<'\n';
            // Fill new histogram
            hPID_Z_AQ->Fill(aq, z, content);
        }
    }

    // Draw the result
    TCanvas* c1 = new TCanvas("c1", "PID: Z vs A/Q", 900, 700);
    hPID_Z_AQ->Draw("COLZ");

}
