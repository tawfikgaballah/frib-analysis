/*
An attempt to extract lifetimes from fitting a LaBr3-PSPMT time difference histrogram with a gaussian 
convoluted with an exponential function. Try to measure the gamma transition rate independently 
of the electrons.
-- ASC 7/20/21
 */

TH1D *hpeak, *hbg;
const Double_t sqrt2 = sqrt(2.0);

/* Gaussian convolved with exponential + background
 * Parameters:
 *    0: amplitude
 *    1: gaussian mean
 *    2: gaussian sigma
 *    3: exp tau
 *    4: background scale
 *    5: background shift
 */
Double_t fconvgaus(Double_t* x, Double_t* par)
{
  Int_t bin = hbg->GetXaxis()->FindBin(x[0]);
  //Double_t bg = par[4]*hbg->GetBinContent(bin-par[5]); // background term
  Double_t bg = par[4]*hbg->GetBinContent(bin); // background term
  Double_t xx = x[0]-par[1];
  Double_t func = par[0]*exp(0.5*pow(par[2]/par[3],2)-xx/par[3])*(1.0-erf((par[2]*par[2]-xx*par[3])/(sqrt2*par[2]*par[3])));
  return func + bg;
  
}

void FitLifetime()
{
  TString fname = "run_199.root_V3";

  TFile* f = new TFile(fname,"READ");
  
  // Remove statistics box and title
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetFrameBorderMode(0);

  // Setup canvas
  TCanvas* c = new TCanvas("c","c",1200,1000);
  c->SetLeftMargin(0.125);
  c->SetRightMargin(0.025);
  c->SetTopMargin(0.01);
  c->SetBottomMargin(0.125);
  c->SetLogy();
  c->cd();

  TH2D* h1 = (TH2D*)f->Get("Summed_Comparisons/LaBr3_v_Tdiff_G_Dyenergy2");

  //81 keV
  // Double_t fitmin = 980;
  // Double_t fitmax = 1100;

  Double_t fitmin = 985;
  Double_t fitmax = 1090;
  
  // here's the projection
  //133Ba
  hpeak = (TH1D*)h1->ProjectionX("hpeak",9,17); // 81  keV; 1:6 keV
  hpeak->SetLineColor(kBlack);
  hpeak->GetXaxis()->SetRangeUser(fitmin,fitmax);
  hpeak->GetXaxis()->SetTitleSize(0.05);
  hpeak->GetXaxis()->SetTitle("t_{LaBr_{3}}-t_{PSPMT} [ns]");
  hpeak->GetXaxis()->CenterTitle();
  hpeak->GetYaxis()->SetTitleSize(0.05);
  hpeak->GetYaxis()->SetTitle("Counts/0.5 ns");
  hpeak->GetYaxis()->CenterTitle();
  hpeak->SetLineWidth(2);
  hpeak->Draw();

  // background from above the peak
  //133Ba
  hbg = (TH1D*)h1->ProjectionX("hbg",27,35); // high portion 81 keV most recent
  
  hbg->SetLineColor(kBlue);

  // fitting functon
  //In a perfect world
  //Double_t centroid = 1000;
  // Double_t sigma = 0.8;
  Double_t halflife_guess = 6; //133Ba 81 keV state 
  
  //60Co Prompt Peak Fit
  //Double_t centroid = 1000.13;
  //Double_t sigma = 0.81;

  //60Co Prompt Peak Fit - Gated!
  Double_t centroid = 999.848;
  //Double_t sigma = 0.35;
  Double_t sigma = 0.332;
  
  TF1* fitf = new TF1("fitf",fconvgaus,fitmin,fitmax,5);
  fitf->SetParameter(0,100);
  fitf->FixParameter(1,centroid);
  fitf->FixParameter(2,sigma);
  fitf->SetParameter(3,halflife_guess/log(2));
  
  fitf->SetParameter(4,1);
  //fitf->SetParameter(5,0.5);
  //fitf->SetParLimits(5,0,1);
  hpeak->Fit("fitf","REML0");

  TF1* conv = new TF1("conv",fconvgaus,fitmin,fitmax,5);
  conv->SetParameters(fitf->GetParameter(0),fitf->GetParameter(1),fitf->GetParameter(2),fitf->GetParameter(3),0.0/*,fitf->GetParameter(5)*/);
  conv->SetNpx(10000); //smoother looking curve

  //TH1D* hfitf = new TH1D("hfitf","hfitf",hpeak->GetNbinsX(),-1000,1000);
  TH1D* hfitf = new TH1D("hfitf","hfitf",hpeak->GetNbinsX(),600,1400);
  for(Int_t i=0; i<hfitf->GetNbinsX(); i++) {
    Double_t xi = hfitf->GetXaxis()->GetBinCenter(i);
    hfitf->SetBinContent(i,fitf->Eval(xi));
  }
  hfitf->SetLineWidth(2);
  hfitf->SetLineColor(kCyan);

  hbg->Scale(fitf->GetParameter(4)); // scale bg by bg best fit amplitude
  hbg->SetLineWidth(2);
  conv->SetLineWidth(2);
  conv->Draw("same"); // exp conv. gaussian only
  hbg->Draw("hist e same"); // scaled bg
  hfitf->Draw("hist same"); // full fit function as a histo

  Double_t halflife = log(2)*fitf->GetParameter(3);
  Double_t ehalflife = halflife*(fitf->GetParError(3)/fitf->GetParameter(3));
  cout << "HL: " << halflife << " +/- " << ehalflife << endl;
  cout << "Chisq: " << fitf->GetChisquare() << " NDF: " << fitf->GetNDF() << " Red. Chisq: " <<  fitf->GetChisquare()/fitf->GetNDF() << endl;
  cout << "HL with inflated errors: " << halflife << " +/- " << sqrt((fitf->GetChisquare()/fitf->GetNDF()))*ehalflife << endl;

}
