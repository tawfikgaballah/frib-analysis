#include <TCanvas.h>
#include <TH2D.h>
#include <TCutG.h>
#include <TRandom.h>
#include <TROOT.h>

void hist_gate() {
    // Step 1: Create and define a TCutG
   TCutG *cutg = new TCutG("CUTG",23);
   cutg->SetVarX("Total Clover Spectrum, gated on #beta-decays Vs (TClover-TDynode)");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,-59.0909,3953.9);
   cutg->SetPoint(1,-60.7438,3471.63);
   cutg->SetPoint(2,-59.9174,3003.55);
   cutg->SetPoint(3,-65.7025,2209.22);
   cutg->SetPoint(4,-50.8264,1769.5);
   cutg->SetPoint(5,-35.124,1436.17);
   cutg->SetPoint(6,-27.686,1329.79);
   cutg->SetPoint(7,-25.2066,890.071);
   cutg->SetPoint(8,1.23967,656.028);
   cutg->SetPoint(9,77.2727,457.447);
   cutg->SetPoint(10,141.736,287.234);
   cutg->SetPoint(11,243.388,152.482);
   cutg->SetPoint(12,294.628,74.4681);
   cutg->SetPoint(13,292.975,31.9149);
   cutg->SetPoint(14,-30.9917,17.7305);
   cutg->SetPoint(15,-83.8843,88.6525);
   cutg->SetPoint(16,-103.719,159.574);
   cutg->SetPoint(17,-106.198,769.504);
   cutg->SetPoint(18,-106.198,1386.52);
   cutg->SetPoint(19,-102.893,2911.35);
   cutg->SetPoint(20,-102.066,3932.62);
   cutg->SetPoint(21,-55.7851,3925.53);
   cutg->SetPoint(22,-59.0909,3953.9);
    // Step 2: Create a TH2D histogram and fill it with data
   // TFile* file = new TFile("beta_delayed_gamma_gated_on_decay_events.root","READ");
    TFile* file = new TFile("decaytime_CorrSorted37Na-Win3-all-beta-delayed-gamma-no-implantlist.root","READ");
  
   // TH2D *h2 = (TH2D*) file->Get("Total Clover Spectrum, gated on #beta-decays Vs (TClover-TDynode)");
       TH2D *h2 = (TH2D*) file->Get("Clover_Vs_TDiff");
 
    // Step 3: Filter the histogram entries using the TCutG
    TH2D *h2_cut = (TH2D*)h2->Clone("h2_cut");
    h2_cut->Reset(); // Clear the cloned histogram

    for (int i = 1; i <= h2->GetNbinsX(); ++i) {
        for (int j = 1; j <= h2->GetNbinsY(); ++j) {
            double x = h2->GetXaxis()->GetBinCenter(i);
            double y = h2->GetYaxis()->GetBinCenter(j);
            if (cutg->IsInside(x, y)) {
                double content = h2->GetBinContent(i, j);
                h2_cut->SetBinContent(i, j, content);
            }
        }
    }

    // Step 4: Draw the filtered histogram
    TCanvas *c1 = new TCanvas("c1", "Canvas", 800, 600);
    TH1D* h1=h2_cut->ProjectionY();
    //  h2->Draw("COLZ");
     // h2_cut->Draw("COLZ");
    h1->Draw("COLZ");
}

// int main() {
//     TApplication app("app", 0, nullptr);
//     drawTH2DWithTCutG();
//     app.Run();
//     return 0;
// }
