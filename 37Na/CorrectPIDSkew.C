void CorrectPIDSkew() {
    // Load original histogram
    TFile* fin = new TFile("decay_vs_radius_filtered_forward+reverse_cutondyenergy.root", "READ");
    TH2D* h2 = (TH2D*)fin->Get("/37Na/PID_Implant");
    if (!h2) {
        std::cerr << "PID_Implant not found!\n";
        return;
    }

    // Constants (hardcoded from FDSiParameters / calibrator)
    const double L = 56423;         // mm
    const double brho = 9.04;           // Tm
    const double c = 299.792458;       // mm/ns
    const double Z_slope = 1.4116;
    const double Z_offset =0;
    const double Z_log_beta = 1.1739;

    // z0 formula constants
    const double z0_A = 50.4562;
    const double z0_B =10.495;
    const double mass_unit = 931.494013;   // MeV/c^2
    double denom = sqrt(9.0 * mass_unit * mass_unit + brho * brho * c * c);
    double beta0 = (c * brho) / denom;
    const int xbins = 1000, ybins = 1000;
    const double min_AoQ = 1.5, max_AoQ = 3.5;
    const double min_Z = 0, max_Z = 30;

    // Output histogram: Z (y), AoQ (x)
    TH2D* h2_aoq_z = new TH2D("PID_AoQ_Z", "PID_AoQ_Z;A/Q;Z",
                              xbins, min_AoQ, max_AoQ,
                              ybins, min_Z, max_Z);

    int nx = h2->GetNbinsX();
    int ny = h2->GetNbinsY();

    for (int ix = 1; ix <= nx; ++ix) {
        for (int iy = 1; iy <= ny; ++iy) {
            double tof = h2->GetXaxis()->GetBinCenter(ix); // ns
            double de2 = h2->GetYaxis()->GetBinCenter(iy);
            double content = h2->GetBinContent(ix, iy);
            if (content == 0) continue;

            // Calculate beta and gamma
            double beta = L / ((tof+971.983+270.69) * c);
            if (beta <= 0 || beta >= 1) continue;

            double beta2 = beta * beta;
            double gamma = 1.0 / sqrt(1.0 - beta2);

            // Step 2: AoQ
            double aoq = (c * brho) / (beta * gamma * mass_unit);
            if (aoq < 1.5 || aoq > 3.5) continue;

            // Step 3: z0
            double logterm = ((de2) + z0_A) / z0_B;
            if (logterm <= 0) continue;

            double z0 = pow(beta / beta0, 1.3) * sqrt(logterm);

            // Step 4: final Z
            double Z = Z_offset + Z_slope * z0;
            if (Z < 0 || Z > 30) continue;
            

            h2_aoq_z->Fill(aoq, Z, content);
        }
    }

    TFile* fout = new TFile("PID_AoQ_Z.root", "RECREATE");
    h2->Write("PID_Implant_Original");
    h2_aoq_z->Write();
    fout->Close();

    std::cout << "DONE: Wrote PID_AoQ_Z.root\n";
}
