double ZCalibrationFcn(double* x, double* p) {
    // x[0] = tof, x[1] = de2
    const double c_light = 299.792458;
    const double L = 56423;
    const double brho = 9.04;
    const double mass_unit = 931.494013;
    const double tof_offset = 270.69+971.983;

    // Compute beta and beta0
    double tof = x[0];
    double de2 = x[1];
    double beta = L / (c_light * (tof + tof_offset));
    double beta0 = (c_light * brho) / sqrt(9 * mass_unit * mass_unit + pow(brho * c_light, 2));

    if (beta <= 0 || beta >= 1) return 0;
    double logterm = (de2 + p[0]) / p[1]; // Z_A, Z_B
    if (logterm <= 0) return 0;

    double z0 = pow(beta / beta0, 1.3) * sqrt(logterm);
    return p[2] + p[3] * z0; // Z = a + b * z0
}

void Fit_ZCalibration_FromCuts() {
    const int numCuts = 6;
    TFile* f = new TFile("PID_graphical_flattened_interpolated.root", "READ");
    TH2D* h2 = (TH2D*)f->Get("PID_Implant_Original");

    std::vector<double> z_data, tof_data, de2_data;

    for (int i = 0; i < numCuts; ++i) {
        TFile* fcut = new TFile(Form("cut%d.root", i), "READ");
        TCutG* cut = (TCutG*)fcut->Get("CUTG");
        if (!cut) continue;
        int Zval = 13 - i;

        for (int x = 1; x <= h2->GetNbinsX(); ++x) {
            for (int y = 1; y <= h2->GetNbinsY(); ++y) {
                double content = h2->GetBinContent(x, y);
                if (content == 0) continue;

                double tof = h2->GetXaxis()->GetBinCenter(x);
                double de2 = h2->GetYaxis()->GetBinCenter(y);
                if (!cut->IsInside(tof, de2)) continue;

                for (int c = 0; c < (int)content; ++c) {
                    z_data.push_back(Zval);
                    tof_data.push_back(tof);
                    de2_data.push_back(de2);
                }
            }
        }
    }

    TGraph2D* gfit = new TGraph2D(z_data.size());
    for (size_t i = 0; i < z_data.size(); ++i)
        gfit->SetPoint(i, tof_data[i], de2_data[i], z_data[i]);

    TF2* fz = new TF2("fz", ZCalibrationFcn,
                      200, 400,   // TOF range (x)
                      1000, 4000, // DE2 range (y)
                      4);         // 4 parameters: Z_A, Z_B, offset, slope

    fz->SetParNames("Z_A", "Z_B", "Z_offset", "Z_slope");
    fz->SetParameters(10, 20, 0.0, 1.0);
    fz->SetParLimits(0, -500, 500);       // Z_A
fz->SetParLimits(1, 2, 100);         // Z_B
fz->SetParLimits(2, 0, 2);            // Z_offset
fz->SetParLimits(3, 0.8, 1.5);        // Z_slope

    gfit->Fit(fz, "Q");

    std::cout << "\n=== Fit Results ===\n";
    std::cout << "Z_A      = " << fz->GetParameter(0) << "\n";
    std::cout << "Z_B      = " << fz->GetParameter(1) << "\n";
    std::cout << "Z_offset = " << fz->GetParameter(2) << "\n";
    std::cout << "Z_slope  = " << fz->GetParameter(3) << "\n";

    TCanvas* can = new TCanvas("can", "Z Calibration Fit", 1000, 800);
    gfit->SetTitle("Z vs TOF & DE2;TOF;DE2;Z");
    gfit->Draw("surf1");
    fz->Draw("surf1 same");
 
}
