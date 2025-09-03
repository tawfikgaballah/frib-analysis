#include <TCanvas.h>
#include <TFile.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TF1.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TMath.h>
#include <RQ_OBJECT.h>
#include <iostream>
class FitApp {
    RQ_OBJECT("FitApp")  // Required for signal-slot connections

public:
    TCanvas* c = nullptr;
    TH2D* h2 = nullptr;
    TH1D* h1 = nullptr;
    int ybin = 1;
    TF1* fitfunc = nullptr;
    int nClick=0;

    FitApp(const std::string& filename, const std::string& histname) {
        TFile* f = TFile::Open(filename.c_str());
        if (!f || f->IsZombie()) {
            std::cerr << "Error: Cannot open file\n";
            return;
        }

        h2 = dynamic_cast<TH2D*>(f->Get(histname.c_str()));
        if (!h2) {
            std::cerr << "Histogram not found\n";
            return;
        }

        std::cout << "Enter starting Y bin: ";
        std::cin >> ybin;

        h1 = h2->ProjectionX("proj", ybin, ybin);
        h1->SetTitle(Form("crystal_%f",h2->GetYaxis()->GetBinCenter(ybin)));

        c = new TCanvas("c", "Double Click to Fit", 800, 600);
        h1->Draw();

        c->Connect("ProcessedEvent(Int_t, Int_t, Int_t, TObject*)",
                   "FitApp", this, "ClickFit(Int_t, Int_t, Int_t, TObject*)");

        std::cout << "Double-click on the histogram to fit.\n";
    }

    void ClickFit(Int_t event, Int_t px, Int_t py, TObject* selected) {
        if (event != kButton1Double || !h1) return;

        double x = gPad->AbsPixeltoX(px);
        double xval = gPad->PadtoX(x);
        double range = 50;
        double xlow = xval - range;
        double xhigh = xval + range;

        fitfunc = new TF1("fitfunc", "[0]+[1]*x+[2]*exp(-0.5*((x-[3])/[4])^2)", xlow, xhigh);
        fitfunc->SetParameters(1, 0, h1->GetMaximum(), xval, 3.0);

        h1->Fit(fitfunc, "R");
        c->Update();



    nClick+=1;



    }
};

void fit_click_tawfik() {
    new FitApp("run-0909-sorted_test_clover.root", "Clover_Chn_Vs_E");
}
