
void InitNames(TF1* fitFunc)
{

  fitFunc->SetParName(0, "Height");
  fitFunc->SetParName(1, "centroid");
  fitFunc->SetParName(2, "sigma");
  fitFunc->SetParName(3, "beta");
  fitFunc->SetParName(4, "R");
  fitFunc->SetParName(5, "step");
  fitFunc->SetParName(6, "A");
  fitFunc->SetParName(7, "B");
  fitFunc->SetParName(8, "C");
  fitFunc->SetParName(9, "bg_offset");
   
}

Bool_t InitParams(TH1* fitHist, TF1* fitFunc, Double_t xlow, Double_t xhigh)
{
  // Makes initial guesses at parameters for the fit. Uses the histogram to
  if(fitHist == nullptr) {
    return false;
  }
  Double_t low, high;
  fitFunc->GetRange(xlow, xhigh);
  Int_t bin     = fitHist->FindBin(fitFunc->GetParameter("centroid"));
  Int_t binlow  = fitHist->GetXaxis()->FindBin(xlow);
  Int_t binhigh = fitHist->GetXaxis()->FindBin(xhigh);
  fitFunc->SetParLimits(0, 0, fitHist->GetMaximum());
  fitFunc->GetParLimits(1, low, high);
  if(low == high && low == 0.) fitFunc->SetParLimits(1, xlow, xhigh);
  fitFunc->GetParLimits(2, low, high);
  if(low == high && low == 0.)
    fitFunc->SetParLimits(2, 0.5, (xhigh - xlow)); // sigma should be less than the window width - JKS
  fitFunc->SetParLimits(3, 0.000001, 10);
  fitFunc->SetParLimits(4, 0.000001, 100); // this is a percentage. no reason for it to go to 500% - JKS
  // Step size is allow to vary to anything. If it goes below 0, the code will fix it to 0
  fitFunc->SetParLimits(5, 0.0, 1.0E2);
  fitFunc->SetParLimits(6, 0.0, fitHist->GetBinContent(bin) * 100.);
  fitFunc->SetParLimits(9, xlow, xhigh);

  // Make initial guesses
  // Actually set the parameters in the photopeak function
  // Fixing has to come after setting
  // Might have to include bin widths eventually
  // The centroid should already be set by this point in the ctor
  fitFunc->SetParameter("Height", fitHist->GetBinContent(bin));
  fitFunc->SetParameter("centroid", fitFunc->GetParameter("centroid"));
  fitFunc->SetParameter("sigma", TMath::Sqrt(9.0 + 4. * fitFunc->GetParameter("centroid") / 1000.) / 2.355);
  fitFunc->SetParameter("beta", fitFunc->GetParameter("sigma") / 2.0);
  fitFunc->SetParameter("R", 0.001);
  fitFunc->SetParameter("step", 1.0);
  // Low limit of A is 0, initial guess at limit is bad --ASC 4/4/2019
  if(fitHist->GetBinContent(binhigh) > 0) // So use high range when its > 0
    fitFunc->SetParameter("A", fitHist->GetBinContent(binhigh));
  else if (fitHist->GetBinContent(binlow) > 0) // Else use half of low range
    fitFunc->SetParameter("A", 0.5*fitHist->GetBinContent(binlow)); // Else guess a small number
  else
    fitFunc->SetParameter("A", 0.5); // Else something small
  fitFunc->SetParameter("B", (fitHist->GetBinContent(binlow) - fitHist->GetBinContent(binhigh)) / (xlow - xhigh));
  fitFunc->SetParameter("C", 0.0000);   
  fitFunc->SetParameter("bg_offset", fitFunc->GetParameter("centroid"));
  fitFunc->FixParameter(7, 0.00); // linear bg term
  fitFunc->FixParameter(8, 0.00); // quadratic bg term
  fitFunc->FixParameter(3, fitFunc->GetParameter("beta"));
  fitFunc->FixParameter(4, 0.00);

  // Print out initial guesses
  Bool_t vprint = false;
  if(vprint) {
    cout << "Initial parameter guesses are:" << endl;
    cout << "Height:    " << fitFunc->GetParameter(0) << endl;
    cout << "Centroid:  " << fitFunc->GetParameter(1) << endl;
    cout << "Sigma:     " << fitFunc->GetParameter(2) << endl;
    cout << "Beta:      " << fitFunc->GetParameter(3) << endl;
    cout << "R:         " << fitFunc->GetParameter(4) << endl;
    cout << "Step:      " << fitFunc->GetParameter(5) << endl;
    cout << "A:         " << fitFunc->GetParameter(6) << endl;
    cout << "B:         " << fitFunc->GetParameter(7) << endl;
    cout << "C:         " << fitFunc->GetParameter(8) << endl;
    cout << "BG offset: " << fitFunc->GetParameter(9) << endl;
  }

  return true;
}

// Some fit functions adopted from the GRSIsort TGRSIFunctions
// Essentially a copy of the TPeak fitting routine. TPeaks are
// used to fit photopeaks to a Gaussian + skewed gaussian.
// The background includes a step function.  

Double_t Gaus(Double_t* dim, Double_t* par)
{
  // This is a gaussian that has been scaled to match up with Radware photopeak results.
  // It contains a scaling factor for the relative height of the skewed gaussian to the
  // normal gaussian. Requires the following parameters:
  //   - dim[0]:  channels being fit
  //   - par[0]:  height of photopeak
  //   - par[1]:  centroid of gaussian
  //   - par[2]:  standard deviation of gaussian
  //   - par[4]:  relative height of skewed gaus to gaus

  Double_t x      = dim[0]; // channel number used for fitting
  Double_t height = par[0]; // height of photopeak
  Double_t c      = par[1]; // Peak Centroid of non skew gaus
  Double_t sigma  = par[2]; // standard deviation of gaussian
  Double_t R      = par[4]; // relative height of skewed gaussian

  return height * (1.0 - R / 100.0) * TMath::Gaus(x, c, sigma);
}

Double_t SkewedGaus(Double_t* dim, Double_t* par)
{
  // This function uses the same parameters as the photopeak and gaussian. This is because in the photopeak,
  // the shapes are correlated.
  // Requires the following parameters:
  //   - dim[0]:  channels being fit
  //   - par[0]:  height of photopeak
  //   - par[1]:  centroid of gaussian
  //   - par[2]:  standard deviation of gaussian
  //   - par[3]:  "skewedness" of the skewed gaussin
  //   - par[4]:  relative height of skewed gaus to gaus

  Double_t x      = dim[0]; // channel number used for fitting
  Double_t height = par[0]; // height of photopeak
  Double_t c      = par[1]; // Peak Centroid of non skew gaus
  Double_t sigma  = par[2]; // standard deviation  of gaussian
  Double_t beta   = par[3]; // "skewedness" of the skewed gaussian
  Double_t R      = par[4]; // relative height of skewed gaussian
  if(beta == 0.0) {
    return 0.0;
  }

  return R * height / 100.0 * (TMath::Exp((x - c) / beta)) *
    (TMath::Erfc(((x - c) / (TMath::Sqrt(2.0) * sigma)) + sigma / (TMath::Sqrt(2.0) * beta)));
}

Double_t StepFunction(Double_t* dim, Double_t* par)
{
  // This function uses the same parameters as the photopeak and gaussian. This is because in the photopeak,
  // the shapes are correlated.
  // Requires the following parameters:
  //   - dim[0]:  channels being fit
  //   - par[0]:  height of photopeak
  //   - par[1]:  centroid of gaussian
  //   - par[2]:  standard deviation of gaussian
  //   - par[5]:  Size of the step in the step function

  Double_t x      = dim[0];
  Double_t height = par[0];
  Double_t c      = par[1];
  Double_t sigma  = par[2];
  Double_t step   = par[5];

  return TMath::Abs(step) * height / 100.0 * TMath::Erfc((x - c) / (TMath::Sqrt(2.0) * sigma));
}

Double_t PolyBg(Double_t* x, Double_t* par, Int_t order)
{
  // Polynomial function of the form SUM(par[i]*(x - shift)^i). The shift is done to match parameters with Radware
  // output.

  Double_t result = 0.0;
  for(Int_t i = 0; i <= order; i++) {
    result += par[i] * TMath::Power(x[0] - par[order + 1], i);
  }
  return result;
}

Double_t PhotoPeakBG(Double_t* dim, Double_t* par)
{
  // Returns a single RadWare style peak
  return Gaus(dim, par) + SkewedGaus(dim, par) + StepFunction(dim, par) + PolyBg(dim, &par[6], 0);
}

void calibrate(int runnum){

	
	const int nclover = 52;
	
	
	TH1D* energy[nclover];
	TFile *f = new TFile("/projects/e21062/aad/e21062B/rootAnalysisFinal/myHistos/run1238-152Eu.root");

	// Start calibration by finding peaks
	Double_t slope[nclover] = {0.};
	Double_t intercept[nclover]={0.};

	for(int j = 0; j < nclover; j++){
		energy[j] = (TH1D*)f->Get(Form("energy%d", j));
		if(energy[j]->Integral() > 0){
			TCanvas *c = new TCanvas("c", "c", 200, 10, 1500, 700);
			energy[j]->GetXaxis()->SetRangeUser(100, 15000);
		
			int npeaks = 20;
			double sensitivity = 0.0005;
			double sigma = 5.;

			TSpectrum *spec = new TSpectrum();
			int nfound = spec->Search(energy[j], sigma, "", sensitivity);
			while(nfound > npeaks){				
				sigma += 0.1;
				sensitivity += 0.0005;
				nfound = spec->Search(energy[j], sigma, "", sensitivity);
			}

			energy[j]->Draw();	

			double *xpos = spec->GetPositionX();
			double *ypos = spec->GetPositionY();

			// Sort in order of x position
			bool swapped = false;
			for(int i = 0; i < nfound - 1; i++){
				swapped = false;
				for(int k = 0; k < nfound - 1; k++){
					double xtemp = 0.;
					double ytemp = 0.;
					if(xpos[k] > xpos[k+1]){
						xtemp = xpos[k];
						xpos[k] = xpos[k+1];
						xpos[k+1] = xtemp;
						ytemp = ypos[k];
						ypos[k] = ypos[k+1];
						ypos[k+1] = ytemp;
						swapped = true;
					}
				}
				if(swapped == false)
					break;
			}
	
			cout << "Found " << nfound << " peaks." << endl;
			for(int i = 0; i < nfound; i++)
				cout << "xpos["<< i << "] = " << xpos[i] << " ypos[" << i << "] = " << ypos[i] << endl;

			TF1 *peakFit[npeaks];
			TFitResultPtr fitResult[npeaks];
			
			double range = 30.;
			for(int i = 0; i < nfound; i++){
				peakFit[i] = new TF1(Form("Peak fit %d", i), PhotoPeakBG, xpos[i] - range, xpos[i] + range, 10);
				InitNames(peakFit[i]);
				peakFit[i]->SetParameter("Height", ypos[i]);	
				peakFit[i]->SetParameter("centroid", xpos[i]);
				InitParams(energy[j], peakFit[i], xpos[i]-range, xpos[i]+range);
				fitResult[i] = energy[j]->Fit(peakFit[i], "SEMRLQ");
				cout << "Fit " << i << endl;
			}

			// Do calibration

			const int npts = 4;

			double calE[npts] = {121.78, 344.28, 964.08, 1408.00};
			double dcalE[npts] = {0.01, 0.01, 0.01, 0.01};
			double chan[npts] = {0};
			double dchan[npts] = {0};

			// Find the right peaks
			// We'll set the last peak = 1408
			// In special cases, 2nd to last peak
			
			double eslope, eoffset;

			eslope = calE[3]/xpos[nfound-1];
			eoffset = 0;
			cout << "Last peak E = 1408 @ " << xpos[nfound-2] << " slope = " << eslope << endl;
			chan[3] = fitResult[nfound-2]->Parameter(peakFit[nfound-2]->GetParNumber("centroid"));
			dchan[3] = fitResult[nfound-2]->ParError(peakFit[nfound-2]->GetParNumber("centroid"));

			// Now look for 964 to get a better slope

			double xp, yp;
			double ediff_low = 1000.;
			for(int k = 0; k < nfound; k++){
				double ediff = ((xpos[k]*eslope-964)*100/964);
				if(ediff < 0)
					ediff = -ediff;
				if((ediff < 50.) && (ediff < ediff_low)){
					xp = xpos[k];
					yp = ypos[k];
					ediff_low = ediff;				
				}
			}

			eslope = (1408 - 964)/(xpos[nfound-2]-xp);
			eoffset = (964 - xp*eslope);

			cout << "new crude cal " << eslope << " " << eoffset << endl;
			
			// Now find all the calibration points;

			range = 10;
			for(int i = 0; i < nfound; i++){
				double ediff_low = 1000.;
				// loop over all peaks found
				for(int k = 0; k < npts; k++){
					double ediff = ((fitResult[i]->Parameter(peakFit[i]->GetParNumber("centroid"))*eslope+eoffset)-calE[k]);
					cout << "Peak #" << i << " CalPoint #" << k << " EnergyDiff = " << ediff << " Centroid = " << fitResult[i]->Parameter(peakFit[i]->GetParNumber("centroid")) <<endl;
					if(ediff<0) 
						ediff=-ediff;
					if ((ediff<range) && (ediff < ediff_low)){
						chan[k] = fitResult[i]->Parameter(peakFit[i]->GetParNumber("centroid"));
						dchan[k] = fitResult[i]->ParError(peakFit[i]->GetParNumber("centroid"));
						ediff_low = ediff;
					}				
				}
			}
			
			for (Int_t ncal=0; ncal<npts; ncal++)
				cout <<"Calibration point at " << calE[ncal] << " found at " << chan[ncal] << endl;

			c->Update();
			c->Modified();
			cout << "Pausing for inspection of fit results. Hit enter to continue." << endl;
			c->WaitPrimitive();

			TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 700, 500);
			TGraphErrors *gr = new TGraphErrors(npts, chan, calE, dchan, dcalE);
			gr->SetMarkerStyle(20);
			gr->Draw("AP");

			TF1 *linCal = new TF1("linCal", "pol1");
			linCal->SetRange(25, 25000);
			TFitResultPtr linCalResult = gr->Fit(linCal, "SQR");
			cout << "Crystal #" << j << " cal pars:\t intercerpt: " << linCalResult->Parameter(0) << "\t\t slope: " << linCalResult->Parameter(1) << endl;
			
			intercept[j] = linCalResult->Parameter(0);
			slope[j] = linCalResult->Parameter(1); 

			
			
		} // end check if has counts
	} // end clover loop

	TString outName;
	outName = Form("/projects/e21062/aad/e21062B/rootAnalysisFinal/cal-final-forreal/CloverInit_%d_2.txt", runnum);

	ofstream output(outName.Data());

	if(output.is_open()) {
		cout << "Output file opened correctly, writing calibration parameters to " << outName.Data() << "..." << endl;
		for(Int_t i=0; i<nclover; i++) 
			output << i+1 << " " << intercept[i] << " " << slope[i] << endl;
	}      
	output.close();

	//else {
		//cout << "ERROR: Output file not open! Something has gone wrong! Exiting... "<< endl;
		//exit(EXIT_FAILURE);
	//}


}
