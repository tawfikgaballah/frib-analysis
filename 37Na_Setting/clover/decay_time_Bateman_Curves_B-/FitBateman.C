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
#include"RootTools.hpp"

using namespace std;
using namespace batemanrate; 
Nucleus *nucl[4]; 
#define fitRange 5000000
double par[9];
double timeWin;
// activities
TF1 *fTotal;
TF1 *fMother;
TF1 *fDaughter1;
TF1 *fDaughter2;
TF1 *fDaughter3;
TF1 *fGranddaughter1;
TF1 *fExpBackground;
TF1 *fExpBackground; 
void FitBateman(const string nucleus_ = "64As") {
  gStyle->SetOptStat(0000000); 
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
   nucl[3] = roottools::GetNucleus(iniZ+1, iniN+3);
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

  par[0]  =3300;
   par[1]  = 12000;
   par[2]  = 0.693/nucl[0]->halflife;
   par[3]  = nucl[0]->B1;
   par[4] = nucl[0]->B2;
	// daughter 1
  par[5]  = 0.693/nucl[1]->halflife;
   par[6]  =0.693/nucl[2]->halflife;
   par[7]=0.693/nucl[3]->halflife;
   par[8]=6.19870e-05; 


  fTotal = new TF1("fTotal",
		   batemanrate::TotalRate,
		   0, timeWin+0, 9);
  fTotal->SetParameters(par);
  fTotal->SetLineColor(2);
  fTotal->SetMinimum(0.001); 
  // // mother
  fMother = new TF1("fMother",
		    batemanrate::MotherRate,
		    0, timeWin+0, 9);
  fMother->SetParameters(par);
  fMother->SetLineColor(48);

  fDaughter1 = new TF1("fDaughter1",
		       batemanrate::Daughter1Rate,
		       0, timeWin+0, 9);
  fDaughter1->SetParameters(par);
  fDaughter1->SetLineColor(3);

   fDaughter2 = new TF1("fDaughter2",
		       batemanrate::Daughter2Rate,
		       0, timeWin+0, 9);
  fDaughter2->SetParameters(par);
  fDaughter2->SetLineColor(9);

   fDaughter3 = new TF1("fDaughter3",
		       batemanrate::Daughter3Rate,
		       0, timeWin+0, 9);
  fDaughter3->SetParameters(par);
  fDaughter3->SetLineColor(6);

  fExpBackground = new TF1("fExpBackground",
							 batemanrate::ExpBackground,
							 0, timeWin+0, 9);
	fExpBackground->SetParameters(par);
	fExpBackground->SetLineColor(1); 
  
  fTotal->SetParLimits(1, 1e0, 1e6);
  //fTotal->FixParameter(1,parFit[1]);
  if(MHT > 999) 
    fTotal->SetParLimits(2,par[2]/10,par[2]*10);// halflife
  else
    fTotal->FixParameter(2, 0.693/MHT); 
  fTotal->FixParameter(3,par[3]);
  //fTotal->SetParLimits(3,nucl[0]->B1/10,nucl[0]->B1*1.5);
  fTotal->FixParameter(4,par[4]);
  // fTotal->SetParLimits(4,nucl[0]->B2/10,nucl[0]->B2*5);
  fTotal->FixParameter(5,par[5]);
  fTotal->FixParameter(6,par[6]);
  fTotal->FixParameter(7,par[7]);
  fTotal->FixParameter(8,par[8]);




  

  TCanvas *c = new TCanvas("c",
			   "", 
			   800, 600);
  c->Draw();
  TH1D *hDecayTime = new TH1D("hDecay_Time","hDecay_Time", 100000,0,10000000);
  // for(long int i = 0; i < 10000000000; ++i) {

  //         hDecayTime->Fill(fTotal->GetRandom());
  //     }
  //  const Long64_t totalEntries = 10000000000;
  const Int_t chunkSize = 1000000; // Fill in chunks to avoid overflow

  // // Fill the histogram using the custom function
  // for (Long64_t i = 0; i < totalEntries; i += chunkSize) {
  //     hDecayTime->FillRandom("fTotal", chunkSize);
  // }


  hDecayTime->SetTitle(";Time (ms);Counts/1 ms"); 
  hDecayTime->Draw("PE");

  hDecayTime->Fit(fTotal, "RO");
  
  fTotal->Draw("same"); // this is where to the the parameters and errors
  for(int i = 0; i < 7; i++) {
    fMother->FixParameter(i,fTotal->GetParameter(i));
    fDaughter1->FixParameter(i,fTotal->GetParameter(i));
    fDaughter2->FixParameter(i,fTotal->GetParameter(i));
    fDaughter3->FixParameter(i,fTotal->GetParameter(i));
    fExpBackground->FixParameter(i,fTotal->GetParameter(i));
  }
  hDecayTime->Fit(fMother, "RO");
  fMother->Draw("same");
  hDecayTime->Fit(fDaughter1, "RO");
  fDaughter1->Draw("same"); 
 hDecayTime->Fit(fDaughter2, "RO");
  fDaughter2->Draw("same");
  hDecayTime->Fit(fDaughter3, "RO");
  fDaughter3->Draw("same"); 
  fExpBackground->Fit(fDaughter3, "RO");
  fExpBackground->Draw("same")
  TLegend *tl = new TLegend(0.7, 0.6,
			    0.925, 0.9); 
  tl->AddEntry(fMother->GetName(),
	       nucl[0]->name.c_str(),
	       "l");
  tl->AddEntry(fDaughter1->GetName(),
	       nucl[1]->name.c_str(),
	       "l"); 
  
  tl->AddEntry(fGranddaughter1->GetName(),
	       nucl[2]->name.c_str(),
	       "l");
  tl->AddEntry(fGranddaughter1->GetName(),
	       nucl[3]->name.c_str(),
	       "l"); 
  tl->AddEntry(fTotal->GetName(), "fExpBackground");
   tl->AddEntry(fExp->GetName(), "Total"); 
 
	
  tl->Draw("same"); 






  c->Update();
}
