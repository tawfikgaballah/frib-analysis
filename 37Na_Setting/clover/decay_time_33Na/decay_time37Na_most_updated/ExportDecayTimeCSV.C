// ExportDecayTimeCSV.C
#include <TFile.h>
#include <TDirectory.h>
#include <TKey.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TMath.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

// ---------- CSV writer ----------
void TH1DToText(TH1D* hist, const char* filename) {
    if (!hist) {
        std::cerr << "Error: null histogram passed to TH1DToText.\n";
        return;
    }
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }
    outfile << "BinCenter,BinContent,BinError\n";
    for (int i = 1; i <= hist->GetNbinsX(); ++i) {
        const double c  = hist->GetBinCenter(i);
        const double y  = hist->GetBinContent(i);
        const double ey = TMath::Sqrt(std::max(0.0, y));
        outfile << std::setprecision(12) << c << "," << y << "," << ey << "\n";
    }
    outfile.close();
    std::cout << "Histogram saved to " << filename << std::endl;
}

// ---------- Find nuclei that have a DecayTime_Vs_Radius* TH2D ----------
std::vector<std::string> ListAvailableNuclei(TFile* f, const char* base = "DecayTime_Vs_Radius") {
    std::vector<std::string> nuclei;
    if (!f || f->IsZombie()) return nuclei;

    TIter nextKey(f->GetListOfKeys());
    while (TKey* key = (TKey*)nextKey()) {
        if (!key->IsFolder()) continue;
        const char* dname = key->GetName();
        TDirectory* d = f->GetDirectory(dname);
        if (!d) continue;

        bool found = false;
        TIter sub(d->GetListOfKeys());
        while (TKey* sk = (TKey*)sub()) {
            if (strcmp(sk->GetClassName(), "TH2D") != 0) continue;
            TString hname = sk->GetName();
            if (hname.BeginsWith(base)) { found = true; break; }
        }
        if (found) nuclei.emplace_back(dname);
    }
    return nuclei;
}

void ExportDecayTimeCSV() {
    const char* filepath = "/mnt/analysis/e21062/tg/batch_analysis/analyzed/merged_decay_analysis_1_percent.root";
    TFile* f = TFile::Open(filepath, "READ");
    if (!f || f->IsZombie()) { std::cerr << "Error: Could not open " << filepath << "\n"; return; }

    // 1) List nuclei
    std::vector<std::string> nuclei = ListAvailableNuclei(f);
    if (nuclei.empty()) { std::cerr << "No DecayTime_Vs_Radius* TH2D found.\n"; f->Close(); return; }

    std::cout << "Available nuclei (" << nuclei.size() << "):\n";
    for (size_t i = 0; i < nuclei.size(); ++i) std::cout << "  [" << i << "] " << nuclei[i] << "\n";

    // 2) Choose nucleus
    int choice = -1;
    std::cout << "Enter the index of the desired nucleus: ";
    std::cin >> choice;
    if (choice < 0 || (size_t)choice >= nuclei.size()) { std::cerr << "Invalid choice.\n"; f->Close(); return; }
    const std::string nucleus = nuclei[choice];

    // 3) Get the histogram directory
    TDirectory* d = f->GetDirectory(nucleus.c_str());
    if (!d) d = dynamic_cast<TDirectory*>(f->Get(nucleus.c_str()));
    if (!d) { std::cerr << "Error: Could not access directory \"" << nucleus << "\"\n"; f->Close(); return; }

    // 4) Find TH2D named like DecayTime_Vs_Radius*
    d->cd();
    TH2D* h2 = nullptr;
    {
        TIter sub(d->GetListOfKeys());
        while (TKey* sk = (TKey*)sub()) {
            if (strcmp(sk->GetClassName(), "TH2D") != 0) continue;
            TString hname = sk->GetName();
            if (hname.BeginsWith("DecayTime_Vs_Radius")) {
                h2 = (TH2D*)d->Get(hname);
                if (h2) break;
            }
        }
    }
    if (!h2) {
        std::cerr << "Error: Could not find a TH2D starting with 'DecayTime_Vs_Radius' in \"" << nucleus << "\"\n";
        f->Close();
        return;
    }

    // 5) Show binning
    const int    nxb = h2->GetNbinsX();
    const double xmin = h2->GetXaxis()->GetXmin();
    const double xmax = h2->GetXaxis()->GetXmax();
    const double xwidth = (xmax - xmin) / nxb;

    const int    nyb = h2->GetNbinsY();
    const double ymin = h2->GetYaxis()->GetXmin();
    const double ymax = h2->GetYaxis()->GetXmax();
    const double ywidth = (ymax - ymin) / nyb;

    std::cout << "\nSelected nucleus: " << nucleus << "\n";
    std::cout << "TH2D: " << h2->GetName() << "\n";
    std::cout << "X (radius) bins: " << nxb << "  [" << xmin << ", " << xmax << "]  bin width ~ " << xwidth << "\n";
    std::cout << "Y (decay time) bins: " << nyb << "  [" << ymin << ", " << ymax << "]  bin width ~ " << ywidth << "\n";

    // 6) Ask for desired radius on X, map 1 unit = 10 X-bins (outer radius), then PROJECT ONTO Y
    double radius = 0.0;
    std::cout << "\nEnter desired radius (0 to 5, where 1 radius unit = 10 X-bins): ";
    std::cin >> radius;
    if (radius < 0.0) radius = 0.0;
    if (radius > 5.0) radius = 5.0;

    int xHigh = TMath::Nint(radius * 10.0);
    if (xHigh < 1) { std::cerr << "Radius corresponds to zero X-bins; increasing to 1.\n"; xHigh = 1; }
    if (xHigh > nxb) xHigh = nxb;

    // ProjectionY takes inclusive X-bin indices [xfirst, xlast]
    TH1D* hy = h2->ProjectionY(
        TString::Format("h_%s_r%.1f_py", nucleus.c_str(), radius),
        /*xfirst=*/1,
        /*xlast=*/xHigh,
        "e" // keep errors
    );
    if (!hy) { std::cerr << "Error: ProjectionY failed.\n"; f->Close(); return; }
    hy->SetDirectory(nullptr); // detach

    // 7) Ask desired bin width along Y and rebin accordingly
    std::cout << "\nCurrent Y bin width ≈ " << ywidth << "\n";
    std::cout << "Enter desired Y bin width (must be an integer multiple of current Y bin width): ";
    double desired_bw = ywidth;
    std::cin >> desired_bw;
    if (desired_bw < ywidth) {
        std::cerr << "Desired bin width is smaller than current Y bin width. No rebinning will be done.\n";
        desired_bw = ywidth;
    }

    int rebinFactor = TMath::Nint(desired_bw / ywidth);
    if (rebinFactor < 1) rebinFactor = 1;

    if (std::abs(desired_bw / ywidth - rebinFactor) > 1e-9) {
        std::cout << "Note: desired width not exact multiple. Using nearest factor = "
                  << rebinFactor << " (final width ≈ " << rebinFactor * ywidth << ")\n";
    }
    if (hy->GetNbinsX() % rebinFactor != 0) {
        std::cout << "Warning: NbinsY (" << hy->GetNbinsX()
                  << ") not divisible by factor (" << rebinFactor
                  << "). ROOT will drop remainder bins.\n";
    }

    if (rebinFactor > 1) {
        TH1* hreb = hy->Rebin(rebinFactor, TString::Format("%s_reb", hy->GetName()));
        if (hreb) { delete hy; hy = (TH1D*)hreb; }
        else { std::cerr << "Rebin failed; proceeding with original binning.\n"; }
    }

    // --- Draw the histogram ---
    TCanvas* c1 = new TCanvas("c1", "Projected Decay Time", 800, 600);
    hy->SetLineColor(kBlue+1);
    hy->SetLineWidth(2);
    hy->SetMarkerStyle(20);
    hy->SetMarkerSize(0.7);
    hy->SetTitle(Form("%s: Decay Time (Radius ≤ %.1f)", nucleus.c_str(), radius));
    hy->GetXaxis()->SetTitle("Decay Time");
    hy->GetYaxis()->SetTitle("Counts");
    hy->Draw("E");

    // 8) Save as CSV
    TString outname = TString::Format("%s_DecayTime_radius%.1f_Ybw%.6g.csv",
                                      nucleus.c_str(), radius, (rebinFactor * ywidth));
    TH1DToText(hy, outname.Data());
    std::cout << "Done.\n";


    // delete hy;
    // f->Close();
}
