Double_t crystalBall(Double_t *x, Double_t *par) {
  // par[0] = alpha (defines the point where the function changes from a Gaussian to a power law)
  // par[1] = n (defines the exponent of the power law tail)
  // par[2] = mean (location of the peak)
  // par[3] = sigma (width of the Gaussian)
  // par[4] = normalization factor
  Double_t t = (x[0]-par[2])/par[3];
  if (par[0] < 0) t = -t;
  Double_t absAlpha = std::abs(par[0]);
  if (t >= -absAlpha) {
    return par[4]*exp(-0.5*t*t);
  }
  else {
    Double_t a =  TMath::Power(par[1]/absAlpha,par[1])*exp(-0.5*absAlpha*absAlpha);
    Double_t b= par[1]/absAlpha - absAlpha; 
    return par[4]*(a/TMath::Power(b - t, par[1]));
  }
}

void crystalball_fit(){

TFile* file= new TFile("./calibration_test_run_1420_linear_two_points_test.root","read");
TH1D* histogram=(TH1D*)file->Get("/cal/hclover_cross_amplitude_test_full_calibrated");

 TF1 *fitFunc = new TF1("fitFunc", crystalBall, 750, 850, 5);
 fitFunc->SetParameters(805, .5, 790, 10, 1);
 histogram->Fit(fitFunc, "RQ");

TF1 *fitFunc1 = new TF1("fitFunc1", crystalBall, 750, 850, 5);
 fitFunc1->SetParameters(fitFunc->GetParameters());

 histogram->Fit(fitFunc1, "RQ");
 

 
histogram->Draw();
fitFunc1->Draw("same");
}
