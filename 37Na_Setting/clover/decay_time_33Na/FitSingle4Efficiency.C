// This is a script to fit the decay half-life
// from the decay time distribution
// using activity function as solutions of
// Bateman equation
// Author: Yongchi Xiao
// Date: 07/17/2019


// header files needed by this script
#include"DecayCascade.hpp"
#include"Fitter.hpp"

// nuclei of interest
// 30Ne, 29Ne, 28Ne,
// 33Na, 32Na, 31Na,
// 36Mg, 35Mg, 34Mg,
// 38Al, 37Al,
// 40Si

#define fixedMotherNuclHalflife 1000
#define fitRange 100
void ZeroNegativeBins(TH1* hist) {
    int nBins = hist->GetNbinsX();
    for (int i = 1; i <= nBins; ++i) {
        if (hist->GetBinContent(i) < 0) {
            hist->SetBinContent(i, 0);
        }
    }
}

using namespace std;

// const string motherNucl = "31Na"; 
const string dir = "./"; ///home/yongchi/data/research/nscl2018/e16032/process_root_files/Correlator2/";

// @UPDATE 04/2020
const string rootName = "./33Na_Decay_Curve.root"; 
// const string rootName = "0720.decaytime.root.run199.1500ms.mg"; 

void FitSingle4Efficiency(const string motherNucl = "33Na", 
			  double NHALFLIFE = 10.0) {
  gStyle->SetOptStat(0000); 

  //_____Prepare decay cascade_____
  DecayCascade *dc = new DecayCascade(100, motherNucl);
  dc->SetTimeWin(fitRange); // fit range in ms 

  //_____Fit_____
  Fitter *f =	new Fitter(dc,	
			   (dir+rootName).c_str(), 
			   "RO");
  //_____Plot____
  TCanvas *c = new TCanvas("c",
			   "", 
			   800, 600);
  c->Draw();

  int shift[11] = {0, 0, 0,
		  0, 0, 0,
		   0, 0, 0, 0,0}; 
	
  TPad *p1 = new TPad("p1", "",
		      0.0, 0.4,
		      1.0, 1.0); 
  p1->Draw();
  p1->SetBottomMargin(0.);
  p1->SetLeftMargin(0.12);
  p1->SetRightMargin(0.075); 
  TPad *p2 = new TPad("p2", "",
		      0.0, 0.0,
		      1.0, 0.4); 
  p2->Draw();
  p2->SetTopMargin(0.);
  p2->SetBottomMargin(0.4);
  p2->SetLeftMargin(0.12); 
  p2->SetRightMargin(0.075); 

  p1->cd();
  p1->SetLogy();
  TH1D *hDecayTime = new TH1D();

	
  //_____Prepare decay cascade_____
  dc->GetParShift(shift);
  dc->AddParShift();
  dc->InitializeParams();
  dc->InitializeActivities(); 

  hDecayTime = f->GetHistogram();
  
  f->ConstrainParams(fixedMotherNuclHalflife); // true = explicitly fix decay halflife of the mother nucleus
  f->Fit(); 
  hDecayTime->GetXaxis()->SetRangeUser(0, dc->GetTimeWin()); 
  hDecayTime->Draw("PE");
  hDecayTime->GetYaxis()->CenterTitle(true); 
  hDecayTime->SetMinimum(5e-1);
  //
  hDecayTime->GetXaxis()->SetNdivisions(108);
  //
  hDecayTime->GetYaxis()->CenterTitle(true);
  hDecayTime->GetYaxis()->SetNdivisions(505);
  hDecayTime->GetYaxis()->SetTitleSize(0.08);
  hDecayTime->GetYaxis()->SetTitleOffset(0.66); 
  hDecayTime->GetYaxis()->SetLabelSize(0.08);

  //_____Functions_____
  // TF1 *fTotal = f->GetFitFunction(); 
  // TF1 *fMother = f->GetDecayCascade()->GetMotherActiv();
  // TF1 *fDaughter1 = f->GetDecayCascade()->GetDaughterActiv(1);
  // TF1 *fDaughter2 = f->GetDecayCascade()->GetDaughterActiv(2);
  // TF1 *fGranddaughter1 = f->GetDecayCascade()->GetGranddaughterActiv(1);
  // TF1 *fGranddaughter2 = f->GetDecayCascade()->GetGranddaughterActiv(2);
  // TF1 *fGranddaughter3 = f->GetDecayCascade()->GetGranddaughterActiv(3);
  // TF1 *fExpBackground = f->GetDecayCascade()->GetExpBackground();


	
  // record fit result
  printf("\n--- %.1lf (pm) %.1lf \n",
	 f->GetHalflife(),
	 f->GetHalflifeErr()); 

		   

  TF1 *fTotal = f->GetFitFunction(); 
  fTotal->Draw("same"); // this is where to the the parameters and errors
  TF1 *fMother = f->GetDecayCascade()->GetMotherActiv();
  fMother->Draw("same");
  TF1 *fDaughter1 = f->GetDecayCascade()->GetDaughterActiv(1);
  fDaughter1->Draw("same"); 
  TF1 *fDaughter2 = f->GetDecayCascade()->GetDaughterActiv(2);
  fDaughter2->Draw("same");
  TF1 *fDaughter3 = f->GetDecayCascade()->GetDaughterActiv(3);
  fDaughter3->Draw("same");
  // TF1 *fGranddaughter1 = f->GetDecayCascade()->GetGranddaughterActiv(1);
  // fGranddaughter1->Draw("same"); 
  // TF1 *fGranddaughter2 = f->GetDecayCascade()->GetGranddaughterActiv(2);
  // fGranddaughter2->Draw("same"); 
  // TF1 *fGranddaughter3 = f->GetDecayCascade()->GetGranddaughterActiv(3);
  // fGranddaughter3->Draw("same");
  // TF1 *fConstBackground = f->GetDecayCascade()->GetConstBackground();
  // fConstBackground->Draw("same");
  
   TF1 *fExpBackground = f->GetDecayCascade()->GetExpBackground();
   fExpBackground->Draw("same"); 

  // verbose: statistics
  ROOT::Math::WrappedTF1 wMotherNucl(*fMother);
  ROOT::Math::GaussIntegrator ig;
  ig.SetFunction(wMotherNucl);
  ig.SetRelTolerance(0.001); 
  std::cout<<0.693/fTotal->GetParameter(8)<<'\n';		
  printf("--- Total number of mother nucleus %s: \n\t%.1lf (<50x halflife); \n\t%.1lf (<%.1lfx halflife)\n",
	 motherNucl.c_str(),
	 // fTotal->GetParameter(1)*f->GetHalflife()/0.693,
	 // sqrt(fTotal->GetParError(1)*f->GetHalflife()/0.693)
	 // ig.Integral(0, f->GetHalflife()*50),
	 hDecayTime->GetEntries(),
	 (ig.Integral(0, 50))//-hDecayTime->GetEntries() )/hDecayTime->GetEntries()
	 ,
	 NHALFLIFE 
	 ); 

  // prepare to calculate the error of the integration
  double pp1 = fTotal->GetParameter(1);
  double dpp1 = fTotal->GetParError(1);
  double pp2 = fTotal->GetParameter(2);
  double dpp2 = fTotal->GetParError(2);
  double t = 5; 
  printf("Within 5x the halflife, the error of the integrated number is %.1lf \n",
	 // pp1*sqrt(pow((dpp1/pp1), 2.0) + pow(((t*exp(-pp2*t)*dpp2)/(1-exp(-pp2*t))), 2.0))
	 pp1*sqrt((dpp1/pp1)*(dpp1/pp1) + (t*exp(-pp2*t)*dpp2/(1-exp(-pp2*t)))*(t*exp(-pp2*t)*dpp2/(1-exp(-pp2*t))))
	 ); 
	
	
  // hDecayTime->SetTitle(Form("%s: Known T_{1/2}=%.1lf#pm%.1lf(ms), fit T_{1/2}=%.1lf#pm%.1lf(ms);Time (ms);Counts/ms",
  // 						  f->GetDecayCascade()->GetMotherNucleus()->name.c_str(),
  // 						  f->GetDecayCascade()->GetMotherNucleus()->halflife,
  // 						  f->GetDecayCascade()->GetMotherNucleus()->halflifeError, 
  // 						  f->GetHalflife(),
  // 						  f->GetHalflifeErr()));
  hDecayTime->SetTitle(";Time (ms);Counts/.4ms"); 
  hDecayTime->SetMaximum(f->GetFitFunction()->Eval(0)*2);
  TLegend *tl = new TLegend(0.7, 0.6,
			    0.925, 0.9); 
  tl->AddEntry(fMother->GetName(),
  			 f->GetDecayCascade()->GetNucleus(0)->name.c_str(),
  			 "l");
  tl->AddEntry(fDaughter1->GetName(),
  			 f->GetDecayCascade()->GetNucleus(1)->name.c_str(),
  			 "l"); 
  tl->AddEntry(fDaughter2->GetName(),
  			 f->GetDecayCascade()->GetNucleus(2)->name.c_str(),
  			 "l");

   tl->AddEntry(fDaughter3->GetName(),
   			 f->GetDecayCascade()->GetNucleus(3)->name.c_str(),
   			 "l");
  // tl->AddEntry(fGranddaughter1->GetName(),
  // 			 f->GetDecayCascade()->GetNucleus(4)->name.c_str(),
  // 			 "l"); 
  // tl->AddEntry(fGranddaughter2->GetName(),
  // 			 f->GetDecayCascade()->GetNucleus(5)->name.c_str(),
  // 			 "l"); 
  // tl->AddEntry(fGranddaughter3->GetName(),
  // 			 f->GetDecayCascade()->GetNucleus(6)->name.c_str(),
  //  			 "l"); 
  tl->AddEntry(fTotal->GetName(), "Total"); 
  tl->AddEntry(fExpBackground->GetName(), "Background");
 
	
  tl->Draw("same"); 


  // for(int i = 1; i < 6; i++) {
  //   tlx[i] = new TLatex(100+i*5, 500,
  // 			Form("%d", i));
  //   tlx[i]->SetTextFont(41);
  //   tlx[i]->SetTextSize(0.09);
  //   // tlx[i]->Draw("same"); 
  // }

  // TLatex *tlx[6] = {};
  // tlx[0] = new TLatex(100, 1000,
  // 					Form("^{33}Na: T_{1/2} = %.1lf #pm %.1lf ms",
  // 						 f->GetHalflife(),
  // 						 f->GetHalflifeErr())
  // 					);
  // tlx[0]->SetTextFont(41);
  // tlx[0]->SetTextSize(0.12);
  // tlx[0]->SetTextColor(kRed); 
  // tlx[0]->Draw(); 


TLatex *tlx[6] = {};
tlx[0] = new TLatex(0.5, 0.8, // Changed coordinates for typical NDC positions
                    Form("^{33}Na: T_{1/2} = %.2lf #pm %.2lf ms",
                         f->GetHalflife(),
                         f->GetHalflifeErr()));
tlx[0]->SetTextFont(42); // Changed font to Helvetica
tlx[0]->SetTextColor(kBlack); // Ensure the color is visible
tlx[0]->SetTextSize(0.05); // Adjusted text size to a typical relative size
 // tlx[0]->SetNDC(0,0);
 // Use Normalized Device Coordinates for positioning
 tlx[0]->SetX(20);
 tlx[0]->SetY(50);
tlx[0]->Draw("same");

  
  //_____Check Fit Residuals_____	
  p2->cd();
 /*  TH1D *h2 = new TH1D("h2",
		      "",
		      (int)fitRange+1, 0, (int)fitRange+1);
  for(int i =0; i < hDecayTime->GetNbinsX(); i++) {
       if((hDecayTime->GetBinError(hDecayTime->GetXaxis()->FindBin(i)))!=0){
        h2->Fill(i, (fTotal->Eval(i)-hDecayTime->GetBinContent(hDecayTime->GetXaxis()->FindBin(i))) /hDecayTime->GetBinError(hDecayTime->GetXaxis()->FindBin(i))
         );
     }
  // else 
	//   h2->Fill(i, (fTotal->Eval(i)-hDecayTime->GetBinContent(hDecayTime->GetXaxis()->FindBin(i))));
  } */


  int NBins=(int)fitRange*(int)hDecayTime->GetNbinsX()/100;
  std::cout<<"number of bins="<< hDecayTime->GetNbinsX()<<'\n';
  double Bin= hDecayTime->GetBinWidth(0);
  TH1D *h2 = new TH1D("h2",
		      "",
		      (int)NBins, 0, NBins*Bin);
 
  std::cout<<"Bin Width:"<<Bin<<'\n';

  for(double i = Bin / 2.000000; i <= fitRange - Bin / 2.000000; i += Bin) {
    int binIndex = hDecayTime->FindBin(i);
    double binContent = hDecayTime->GetBinContent(binIndex);
      if(binContent != 0){
      double residual = (-abs(fTotal->Eval(i)) + binContent) / hDecayTime->GetBinError(binIndex);
        h2->SetBinContent(h2->FindBin(i), residual);
        h2->SetBinError(h2->FindBin(i), 0);  // You could also consider setting a meaningful error if applicable
	//std::cout<<Form("Residual %d:",i)<<residual<<'\n';
    }
    else{
      h2->SetBinContent(h2->FindBin(i),110000);
    }
}
	
  h2->SetTitle(";Time (ms);#splitline{Normalized}{Fit Residual}"); 
  h2->SetMarkerStyle(21); 
  h2->Draw("hist p");
	
  h2->GetXaxis()->SetLabelSize(0.11);
  h2->GetXaxis()->SetNdivisions(108);
  h2->GetXaxis()->SetTitleSize(0.12);
  h2->GetXaxis()->SetTitleOffset(0.90); 
  h2->GetXaxis()->CenterTitle(true);
  //
  h2->GetYaxis()->SetRangeUser(-7, 7); 
  h2->GetYaxis()->SetLabelSize(0.12);
  h2->GetYaxis()->SetNdivisions(105);
  h2->GetYaxis()->SetTitleSize(0.12);
  h2->GetYaxis()->SetTitleOffset(0.4); 
  h2->GetYaxis()->CenterTitle(true);
	
  TF1 *fBaseline = new TF1("fBaseline", "[0]", 0, 1000);
  fBaseline->SetParameter(0, 0);
  fBaseline->SetLineColor(kRed);
  fBaseline->Draw("same"); 
	
  c->Update(); 

  //  TCanvas *canvas1 = new TCanvas("canvas1",
  // 			   "", 
  // 			   800, 600);
  // canvas1->cd();
  // h2->Draw("");
}
