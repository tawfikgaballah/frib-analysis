// This is a script to fit the decay half-life
// from the decay time distribution
// using activity function as solutions of
// Bateman equation
// Author: Yongchi Xiao
// Date: 07/17/2019


/* #include"BatemanNumber2.hpp" */
#include"BatemanRate2.hpp"
#include"Nuclei.hpp"
#include"TextTools.hpp"
#include"RootTools_31F.hpp"

using namespace std;
using namespace batemanrate; 
Nucleus *nucl[5];
#define fitRange 30
double par[12];
double timeWin;
// activities
TF1 *fTotal;
TF1 *fMother;
TF1 *fDaughter1;
TF1 *fGranddaughter1;
TF1 *fDaughter2;
TF1 *fDaughter3;
TF1 *fDaughter4;
TF1 *fConstBackground;
TF1 *fExpBackground;
double halflife;
  double halflifeError;
  double chi2NDF;
   double chi2;
   double NDF;




#include <fstream>
void TH1DToText(TH1D* hist, const char* filename) {
    // Open the output file
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write header
    outfile << "# BinCenter\tBinContent\tBinError" << std::endl;

    // Loop over the bins and write the data
    for (int i = 1; i <= hist->GetNbinsX(); ++i) { // Bins start at 1 in ROOT
        double binCenter = hist->GetBinCenter(i);
        double binContent = hist->GetBinContent(i);
        double binError =TMath::Sqrt(hist->GetBinContent(i)) ;
	// if (binError!=0 && binContent!=0)
        outfile << binCenter << "\t," << binContent << "\t," << binError << std::endl;
    }

    // Close the file
    outfile.close();
    std::cout << "Histogram saved to " << filename << std::endl;
}




void TF1ToText(TF1* func, const char* filename, double xMin, double xMax, int numPoints) {
    // Open the output file
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write header
    outfile << "# x\tf(x)" << std::endl;

    // Calculate step size
    double step = (xMax - xMin) / (numPoints - 1);

    // Loop over points and evaluate the function
    for (int i = 0; i < numPoints; ++i) {
        double x = xMin + i * step;
        double y = func->Eval(x);
        outfile << x << "\t" << y << std::endl;
    }

    // Close the file
    outfile.close();
    std::cout << "Function saved to " << filename << std::endl;
}

void FitBateman_31F(const string nucleus_ = "31F") {
  // gStyle->SetOptStat(0000000); 
  timeWin=fitRange;

  // parse the name of the nucleus
  string element    = texttools::GetTextFromStrings(nucleus_);
  unsigned int iniA = texttools::GetIntegersFromStrings(nucleus_); 
  unsigned int iniZ = texttools::FindElementZ(element);
  unsigned int iniN = iniA - iniZ;
	
  // mother
  nucl[0] = roottools::GetNucleus(iniZ, iniN);
  // daughter
  nucl[1] = roottools::GetNucleus(iniZ+1, iniN-1); 
   nucl[2] = roottools::GetNucleus(iniZ+1, iniN-2);
  // //B2n
   nucl[3] = roottools::GetNucleus(iniZ+1, iniN-3);
   //B3n
    nucl[4] = roottools::GetNucleus(iniZ+1, iniN-4);
  // granddaughter
  //nucl[2] = roottools::GetNucleus(iniZ+2, iniN-2); 
  // nucl[5] = roottools::GetNucleus(iniZ+2, iniN-3); 
  // nucl[6] = roottools::GetNucleus(iniZ+2, iniN-4);

  for(int i = 0; i <4 ; i++) {
    nucl[i]->PrintName();
    nucl[i]->PrintBranchingRatios(); 
  }
  nucl[0]->CalculateBranchingRatios();
  nucl[1]->CalculateBranchingRatios();
  nucl[2]->CalculateBranchingRatios();
  nucl[3]->CalculateBranchingRatios();
  nucl[4]->CalculateBranchingRatios();

  par[0]  = 1.97953;
   par[1]  = 35;
   par[2]  = 0.693/nucl[0]->halflife;
   par[3]  = nucl[0]->B1;
   par[4] = nucl[0]->B2;
   par[5] = .2;
	// daughter 1
  par[6]  = 0.693/nucl[1]->halflife;
   par[7]  =0.693/nucl[2]->halflife;
   par[8]=0.693/nucl[3]->halflife;
   par[9]=0.693/nucl[4]->halflife;
   par[10]=0.0019177;
   par[11]=0;



  fTotal = new TF1("fTotal",
		   batemanrate::TotalRate,
		   -5, timeWin+0, 12);
  fTotal->SetParameters(par);
  fTotal->SetLineColor(2);
  fTotal->SetMinimum(0.001); 
  // // mother
  fMother = new TF1("fMother",
		    batemanrate::MotherRate,
		    -5, timeWin+0, 12);
  fMother->SetParameters(par);
  fMother->SetLineColor(48);

  fDaughter1 = new TF1("fDaughter1",
		       batemanrate::Daughter1Rate,
		       0, timeWin+0, 12);
  fDaughter1->SetParameters(par);
  fDaughter1->SetLineColor(20);

   fDaughter2 = new TF1("fDaughter2",
		       batemanrate::Daughter2Rate,
		       0, timeWin+0, 12);
  fDaughter2->SetParameters(par);
  fDaughter2->SetLineColor(9);

   fDaughter3 = new TF1("fDaughter3",
		       batemanrate::Daughter3Rate,
		       0, timeWin+0, 12);
  fDaughter3->SetParameters(par);
  fDaughter3->SetLineColor(6);

   fDaughter4 = new TF1("fDaughter4",
		       batemanrate::Daughter4Rate,
		       0, timeWin+0, 12);
  fDaughter4->SetParameters(par);
  fDaughter4->SetLineColor(3);

  fExpBackground = new TF1("fExpBackground",
							 batemanrate::ExpBackground,
							 0, timeWin+0, 12);
	fExpBackground->SetParameters(par);
	fExpBackground->SetLineColor(1); 
		fTotal->FixParameter(0,par[0]);
		//		fTotal->SetParLimits(0, 0,5);

		fTotal->SetParLimits(1, 1e0, 1000);
		//			fTotal->FixParameter(1,par[1]);
 
    fTotal->SetParLimits(2,par[2]/100,par[2]*100);// halflife

     fTotal->FixParameter(3,par[3]);
    // fTotal->SetParLimits(3,0,nucl[0]->B1*10);
      fTotal->FixParameter(4,par[4]);
      // fTotal->SetParLimits(4,0,nucl[0]->B2*10);
      fTotal->FixParameter(5,par[5]);
      //    fTotal->SetParLimits(5,0,.25*2);
  fTotal->FixParameter(6,par[6]);
  fTotal->FixParameter(7,par[7]);
  fTotal->FixParameter(8,par[8]);
  fTotal->FixParameter(9,par[9]);
   fTotal->FixParameter(10,par[10]);
     fTotal->FixParameter(11,par[11]);
   //     fTotal->SetParLimits(10,-2, par[10]*10);



  

  TCanvas *c = new TCanvas("c",
			   "", 
			   800, 600);
  c->Draw();
  // TH1D *hDecayTime = (TH1D*)roottools::GetDecayTimeDistribution("/projects/e21062/tg/37Na_Setting/clover/decay_time_33Na/decay_time33Na_most_updated/33_37_Na_Decay_Time_PID_descale_6mm_corr_radius.root", "37Na");
  // TH1D *hDecayTime = (TH1D*)roottools::GetDecayTimeDistribution("/projects/e21062/tg/37Na/Decay_Vs_Radius_Reverse_31F.root", "31F");
  TH1D *hDecayTime = (TH1D*)roottools::GetDecayTimeDistribution("/mnt/analysis/e21062/tg/batch_analysis/analyzed/merged_decay_analysis.root", "31F");
  //hDecayTime->RebinX(5);
  hDecayTime->GetXaxis()->SetRangeUser(-5,fitRange);
  // for(long int i = 0; i < 10000000000; ++i) {

  //         hDecayTime->Fill(fTotal->GetRandom());
  //     }
  //  const Long64_t totalEntries = 10000000000;
  const Int_t chunkSize = 1000000; // Fill in chunks to avoid overflow

  // // Fill the histogram using the custom function
  // for (Long64_t i = 0; i < totalEntries; i += chunkSize) {
  //     hDecayTime->FillRandom("fTotal", chunkSize);
  // }
	
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

  hDecayTime->SetTitle(";Time (ms);Counts/0.5 ms"); 
  hDecayTime->Draw("hist PE");
   hDecayTime->SetMinimum(5e-1);

  auto fitresult1= hDecayTime->Fit(fTotal, "ROWLLS");
  
  fTotal->Draw("same"); // this is where to the the parameters and errors
  for(int i = 0; i < 9; i++) {
    fMother->FixParameter(i,fTotal->GetParameter(i));
    fDaughter1->FixParameter(i,fTotal->GetParameter(i));
    fDaughter2->FixParameter(i,fTotal->GetParameter(i));
    fDaughter3->FixParameter(i,fTotal->GetParameter(i));
     fDaughter4->FixParameter(i,fTotal->GetParameter(i));
    fExpBackground->FixParameter(i,fTotal->GetParameter(i));
  }
 hDecayTime->Fit(fMother, "QROWL");
  fMother->Draw("same");
  hDecayTime->Fit(fDaughter1, "QROWL");
  fDaughter1->Draw("same"); 
 hDecayTime->Fit(fDaughter2, "QROWL");
  fDaughter2->Draw("same");
  hDecayTime->Fit(fDaughter3, "QROWL");
  fDaughter3->Draw("same");

   hDecayTime->Fit(fDaughter4, "QROWL");
  fDaughter4->Draw("same");
  hDecayTime->Fit(fDaughter3, "QROWL");
  fExpBackground->Draw("same");


 // TF1ToText(fTotal,"fTotal_31F.txt", -10, 60, 300);
 // TF1ToText(fMother,"fMother_31F.txt", -10, 60, 300);
 //   TF1ToText(fDaughter1,"fDaughter1_31F.txt", 0, 60, 300);
 //   TF1ToText(fDaughter2,"fDaughter2_31F.txt", 0, 60, 300);
 //   TF1ToText(fDaughter3,"fDaughter3_31F.txt", 0, 60, 300);
 //     TF1ToText(fDaughter4,"fDaughter4_31F.txt", 0, 60, 300);
 //     TF1ToText(fExpBackground,"fExpBackground_31F.txt", 0, 60, 300);
     TH1DToText(hDecayTime, "hist_31F.csv");
  TLegend *tl = new TLegend(0.7, 0.6,
			    0.925, 0.9); 
  tl->AddEntry(fMother->GetName(),
	       nucl[0]->name.c_str(),
	       "l");
  // tl->AddEntry(fDaughter1->GetName(),
  // 	       nucl[1]->name.c_str(),
  // 	       "l"); 
  
  tl->AddEntry(fDaughter2->GetName(),
	       nucl[2]->name.c_str(),
	       "l");
  tl->AddEntry(fDaughter3->GetName(),
	       nucl[3]->name.c_str(),
	       "l");
   tl->AddEntry(fDaughter4->GetName(),
	       nucl[4]->name.c_str(),
	       "l"); 
   tl->AddEntry(fTotal->GetName(), "Total Fit", "l");
   tl->AddEntry(fExpBackground->GetName(), "Exp Background", "l"); 
   
	
   tl->Draw("same");



halflife = (0.693/fTotal->GetParameter(2));
  halflifeError = (fTotal->GetParError(2)/fTotal->GetParameter(2)*0.693/fTotal->GetParameter(2));
	chi2NDF = fTotal->GetChisquare() / fTotal->GetNDF();
	chi2 = fTotal->GetChisquare();
	NDF = fTotal->GetNDF();



	 TPaveText *pt = new TPaveText(0.1, 0.1, 0.2, 0.2, "brNDC"); // Adjust coordinates as needed
pt->AddText(Form("^{31}F: T_{1/2} = %.2lf #pm %.2lf ms", halflife, halflifeError));
 pt->AddText(Form("#beta_{0n}=%.2lf, #beta_{n}=%.2lf, #beta_{2n}=%.2lf,  #beta_{3n}=%.2lf", 1 - fTotal->GetParameter(3) - fTotal->GetParameter(4)-fTotal->GetParameter(5),fTotal->GetParameter(3),fTotal->GetParameter(4),fTotal->GetParameter(5)));
 pt->AddText(Form("Chi2NDF= %.2lf, NDF= %d", fTotal->GetChisquare()/fTotal->GetNDF(), fTotal->GetNDF())); 
pt->Draw("same");
 
  c->Update();





 p2->cd();
    int NBins=(int)fitRange*(int)hDecayTime->GetNbinsX()/200;
  std::cout<<"number of bins="<< hDecayTime->GetNbinsX()<<'\n';
  double Bin= hDecayTime->GetBinWidth(0);
  TH1D *h2 = new TH1D("h2",
		      "",
		      (int)NBins+25, -5, NBins*Bin);
 
  std::cout<<"Bin Width:"<<Bin<<'\n';

  TH1D* h3=new TH1D("h3","h3",600,-3,3);

  for(double i = -5+Bin / 2.000000; i <= fitRange - Bin / 2.000000; i += Bin) {
    int binIndex = hDecayTime->FindBin(i);
    double binContent = hDecayTime->GetBinContent(binIndex);
      if(binContent != 0 &&i>0){
      double residual = (-abs(fTotal->Eval(i)) + binContent) / hDecayTime->GetBinError(binIndex);
        h2->SetBinContent(h2->FindBin(i), residual);
        h2->SetBinError(h2->FindBin(i), 0);  // You could also consider setting a meaningful error if applicable
	//std::cout<<Form("Residual %d:",i)<<residual<<'\n';
	h3->Fill(residual);
    }
    else{
      h2->SetBinContent(h2->FindBin(i),110000);
    }
}
  h2->SetTitle(";Time (ms);#splitline{Normalized}{Fit Residual}"); 
  h2->SetMarkerStyle(21); 
  h2->Draw(" pe");
 std::cout<<"number of bins="<< h2->GetNbinsX()<<'\n';	
  h2->GetXaxis()->SetLabelSize(0.11);
  h2->GetXaxis()->SetNdivisions(108);
  // h2->GetXaxis()->SetTitleSize(0.12);
  // h2->GetXaxis()->SetTitleOffset(0.90); 
  h2->GetXaxis()->CenterTitle(true);
  //
  h2->GetYaxis()->SetRangeUser(-3, 3); 
  // h2->GetYaxis()->SetLabelSize(0.1);
  // h2->GetYaxis()->SetNdivisions(105);
  //  h2->GetYaxis()->SetTitleSize(0.7);
  // h2->GetYaxis()->SetTitleOffset(0.4); 
  h2->GetYaxis()->CenterTitle(true);
	
  TF1 *fBaseline = new TF1("fBaseline", "[0]", 0, 1000);
  fBaseline->SetParameter(0, 0);
  fBaseline->SetLineColor(kRed);
  fBaseline->Draw("same"); 
	
  c->Update();

  TCanvas* canvas=new TCanvas();
  canvas->cd();
  h3->Draw("");


  
auto covMatrix1 = fitresult1->GetCovarianceMatrix();
 double sigma_integral1 = fTotal->IntegralError(0,7.5,fitresult1->GetParams(),covMatrix1.GetMatrixArray());
printf("=====================================\n"); 
	printf("Mother nucleus: %s\nExpected halflife = %.2lf\n",
		  nucl[0]->name.c_str(),
		  nucl[0]->halflife);
	printf("Measured halflife = %.2lf (pm) %.2lf (ms) \n",
		   halflife,
		   halflifeError); 
	printf("=====================================\n");

		printf("chi2NDF =  %.2lf  \n",chi2NDF
		   ); 
	printf("=====================================\n");

			printf("chi2 =  %.2lf  \n",chi2
		   ); 
	printf("=====================================\n");

			printf("NDF =  %.2lf  \n",NDF
		   ); 
	printf("=====================================\n");

	printf("Integral =  %.2lf  \n",fMother->Integral(0,7.5)/hDecayTime->GetBinWidth(1)
	       );
	printf("Integral Total =  %.2lf +/- %.2lf \n",fTotal->Integral(0,7.5)/hDecayTime->GetBinWidth(1), sigma_integral1/hDecayTime->GetBinWidth(1)
	       
	       );
	printf("Integral Hist =  %.2lf  \n",hDecayTime->Integral(hDecayTime->FindBin(0),hDecayTime->FindBin(7.5))
	       
	       );
  
}



