#include"BatemanRate2.hpp"
#include"Nuclei.hpp"
#include"TextTools.hpp"
#include"RootTools_31F.hpp"
#include<TRandom.h>
#include<TGraph.h>
#include <algorithm> 
using namespace std;
using namespace batemanrate; 
Nucleus *nucl[5]; 
#define fitRange 30
double par[12];
double timeWin;

double halflife;
double chi2;
double NDF;
int numIterations = 10000; // Number of iterations for sampling
struct GausND {
 
   TVectorD X;
   TVectorD Mu;
   TMatrixDSym CovMat;
 
   GausND( int dim ) :
      X(TVectorD(dim)),
      Mu(TVectorD(dim)),
      CovMat(TMatrixDSym(dim) )
   {}
 
   double operator() (double *x, double *p) {
      int dim = X.GetNrows();
      int k = 0;
      for (int i = 0; i < dim; ++i) { 
         X[i] = x[i] - p[k]; // Subtract the mean
         k++;
      }
      for (int i = 0; i < dim; ++i) {
         CovMat(i,i) = p[k]*p[k]; // Variances
         k++;
      }
      for (int i = 0; i < dim; ++i) {
         for (int j = i+1; j < dim; ++j) {
            // Correlations
            CovMat(i,j) = p[k]*sqrt(CovMat(i,i)*CovMat(j,j));
            CovMat(j,i) = CovMat(i,j);
            k++;
         }
      }

      double det = CovMat.Determinant();
      if (det <= 0) {
         Fatal("GausND","Determinant is <= 0 det = %f",det);
         CovMat.Print();
         return 0;
      }
      double norm = std::pow( 2. * TMath::Pi(), dim/2) * sqrt(det);
      CovMat.Invert();
      double fval  = std::exp( - 0.5 * CovMat.Similarity(X) ) / norm;
 
      return fval;
   }
};
void FitBateman_Gauss_31F(const string nucleus_ = "31F") {
  
  gStyle->SetOptStat(0000000); 
  timeWin = fitRange;



  const int N = numIterations;  // Number of samples
   const int DIM = 8;  // We are working in 4 dimensions for B0, B1, B2, B3

   double xmin[] = {0, 0, 0, 0, 0, 0, 0, 0};   // Minimum values for B0, B1, B2, B3
   double xmax[] = {1, 1, 1, 1, 100, 100, 100, 100};   // Maximum values for B0, B1, B2, B3
                   //B0 B1    B2    B3    HL0  HLn  HL2n  HL3n
   double par0[] = { 0, 0.63, 0.17,0.2 , 3.4, 7.3, 14.0, 18.7, // means for B0, B1, B2, B3
		     0.2, 0.63, 0.17,0.2 , 0.8, 0.3, 0.5, 0.2, // sigmas (standard deviations)
		     //     -0.0, -0.0, .0, 0, 0, 0, 0, 0.0, 0.0, 0, 0, 0, 0, 0.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 
                      -0.1, -0.1, -.9, 0, 0, 0, 0, -0.1, -0.1, 0, 0, 0, 0, -0.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; 
   // correlations

   GausND gaus4d(8);
   TF1 * f = new TF1("functionND", gaus4d, 0, 1, 44);
   f->SetParameters(par0);

   TString name;

for (int i = 0; i < 44; ++i )  {
      if (i < DIM) f->SetParName(i, name.Format("mu_%d",i+1) );
      else if (i < 2*DIM) f->SetParName(i, name.Format("sig_%d",i-DIM+1) );
      else if (i < 2*DIM) f->SetParName(i, name.Format("sig_%d",i-2*DIM+1) );
   }
 
    ROOT::Math::DistSamplerOptions::SetDefaultSampler("Foam");
   ROOT::Math::DistSampler *sampler = ROOT::Math::Factory::CreateDistSampler();
   sampler->SetFunction(*f, DIM);
   sampler->SetRange(xmin, xmax);
   bool ret = sampler->Init();

   std::vector<double> data1(DIM * N);
   double v[DIM];

   if (!ret) {
      Error("Sampler::Init", "Error initializing sampler");
      return;
   }




   // double xmin_hl[] = {0, 0, 0, 0};   // Minimum values for B0, B1, B2, B3
   // double xmax_hl[] = {100, 100, 100, 100};   // Maximum values for B0, B1, B2, B3
   // double par0_hl[] = { 6.4, 7.2, 11.3, 44.9,  // means for B0, B1, B2, B3
   // 			1.5, 1.2, 0.6, 0.4, // sigmas (standard deviations)
   //                   0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; // correlations

   // GausND gaus4d_hl(4);
   // TF1 * f_hl = new TF1("functionND_hl", gaus4d_hl, 0, 1, 14);
   // f_hl->SetParameters(par0_hl);

   // TString name_hl;
   // for (int i = 0; i < 4; ++i) {
   //    f_hl->SetParName(i, name_hl.Format("mu_%d", i+1));
   //    f_hl->SetParName(i+4, name_hl.Format("sigma_%d", i+1));
   //    if (i < 3) f_hl->SetParName(i+8, name_hl.Format("corr_%d", i+1));
   // }


   // ROOT::Math::DistSampler *sampler_hl = ROOT::Math::Factory::CreateDistSampler();
   // sampler_hl->SetFunction(*f_hl, DIM);
   // sampler_hl->SetRange(xmin_hl, xmax_hl);
   // bool ret_hl = sampler_hl->Init();

   // std::vector<double> data1_hl(DIM * N);
   // double v_hl[DIM];

   // if (!ret) {
   //    Error("Sampler::Init", "Error initializing sampler");
   //    return;
   // }








  
  // TH1D *hDecayTime = (TH1D*)roottools::GetDecayTimeDistribution("/projects/e21062/tg/37Na_Setting/clover/decay_time_33Na/decay_time33Na_most_updated/33_37_Na_Decay_Time_PID_descale_6mm_corr_radius.root", "37Na");
    TH1D *hDecayTime = (TH1D*)roottools::GetDecayTimeDistribution("/projects/e21062/tg/37Na/decay_vs_radius_filtered_forward+reverse.root", "31F");
  hDecayTime->GetXaxis()->SetRangeUser(0, fitRange);
  hDecayTime->SetTitle(";Time (ms);Counts/0.5 ms");
  hDecayTime->Draw("hist PE");
  hDecayTime->SetMinimum(5e-1);
    
  // Parse the nucleus details
  string element = texttools::GetTextFromStrings(nucleus_);
  unsigned int iniA = texttools::GetIntegersFromStrings(nucleus_);
  unsigned int iniZ = texttools::FindElementZ(element);
  unsigned int iniN = iniA - iniZ;
    
  // Mother and daughter nuclei
  nucl[0] = roottools::GetNucleus(iniZ, iniN);
  nucl[1] = roottools::GetNucleus(iniZ+1, iniN-1);
  nucl[2] = roottools::GetNucleus(iniZ+1, iniN-2);
  nucl[3] = roottools::GetNucleus(iniZ+1, iniN-3);
  nucl[4] = roottools::GetNucleus(iniZ+1, iniN-4);
  for(int i = 0; i < 5; i++) {
    nucl[i]->PrintName();
    nucl[i]->PrintBranchingRatios();
  }

  // Calculate branching ratios
  nucl[0]->CalculateBranchingRatios();
  nucl[1]->CalculateBranchingRatios();
  nucl[2]->CalculateBranchingRatios();
  nucl[3]->CalculateBranchingRatios();
  nucl[4]->CalculateBranchingRatios();
  // Initial parameters
  par[0]  = exp(2.91360)/10;
  par[1]  =35;
  par[2]  = 0.693 / nucl[0]->halflife;  // Halflife for the mother nucleus
  par[3]  = 0.63;  // B1 branching ratio
  par[4]  = 0.17;  // B2 branching ratio
  par[5]  = 0.2;  // B3 branching ratio
  par[6]  = 0.693 / nucl[1]->halflife; // Daughter 1 halflife
  par[7]  = 0.693 / nucl[2]->halflife; // Daughter 2 halflife
  par[8]  = 0.693 / nucl[3]->halflife; // Daughter 3 halflife
  par[9]  = 0.693 / nucl[4]->halflife; // Daughter 4 halflife
  par[10]  = 1.67361e-03;//7.93642e-04; // Background parameter
  par[11]=0;
    
  // Arrays to store results
  vector<double> halflifeArray;
  vector<double> chi2Array;

  // Gaussian random number generator
  TRandom randomB1;
  TRandom randomB2;
  TRandom randomB3;
  TRandom random37Mg;
  TRandom random36Mg;
  TRandom random35Mg;
  TRandom random34Mg;
  TRandom randomp0;
  TRandom randomp1;
  TRandom randomp10;
  double sigmap0=.29;
  double sigmap1=4.35;
  double sigmap10=2.78323e-03;
  double sigmaB1 = 1* par[3];  // Standard deviation for B1 (adjust as needed)
  double sigmaB2 =  1* par[4];  // Standard deviation for B2 (adjust as needed)
  double sigmaB3 = 1* par[5];
  double sigma37Mg= 1*(1.5);
  double sigma36Mg= 1*(1.2);
  double sigma35Mg= 1*(.6);
   double sigma34Mg=1*(.4);
  // Iterative fitting process
  TFile* output=new TFile("systimatics_35Na.root", "recreate");
  double chi2;
  long int index;
  double parent_integral;
  double total_integral;
  double Par[12]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  TTree* data=new TTree("fitpar", "fitpar");
  data->Branch("Par", Par, "Par[12]/D");
  data->Branch("chi2", &chi2, "chi2/D");
  data->Branch("index", &index, "index/I");
  data->Branch("parent_integral", &parent_integral, "parent_integral/D");
  data->Branch("total_integral", &total_integral, "total_integral/D");
  TH2D* chi2_vs_hl=new TH2D("Chi2_Vs_HL;Fit Half-Life [ms]","Chi2_Vs_HL;Fit Half-Life [ms]", 500, 0, 5, 500, 0,500);
  TH2D* par_vs_hl=new TH2D("par_vs_hl","par_vs_hl", 2000, 0, 20, 300, 0,30);
  TH1D* HL=new TH1D("Half-Life Distribution; Fit Half-Life  [ms]","Half-Life Distribution; Fit Half-Life  [ms]", 500,0,5);
  TH1D* P_Int=new TH1D("Parent Integral Distribution","Parent Integral Distribution", 1000,10000,20000);
  TH1D* Tot_Int=new TH1D("Total Integral Distribution","Total Integral Distribution", 1000,20000,30000);












  
  for (int i = 0; i < numIterations; ++i) {

  sampler->Sample(v);
    double     B0 = v[0];
        double B1 = v[1];
        double B2 = v[2];
        double B3 = v[3];
      	 double sum = B0 + B1 + B2 + B3;
       B0 /= sum;
       B1 /= sum;
      B2 /= sum;
      B3 /= sum;  
      

      
  
      double    new37Mg = v[4];
        double  new36Mg = v[5];
        double  new35Mg = v[6];
        double  new34Mg = v[7];
	  


    
   
       if (i % (numIterations / 10) == 0) {
            cout << "Progress: " << (100 * i) / numIterations << "% complete" << endl;
        }
      // Sample new values for par[3] and par[4] (B1 and B2)
     // double newB1 = randomB1.Gaus(par[3], sigmaB1);
     // //  double newB1 = par[3];
     // double newB2 = randomB2.Gaus(par[4], sigmaB2);
     //  double newB3 = randomB3.Gaus(par[5], sigmaB3);
       double newB0=B0;
       double newB1=B1;
       double newB2=B2;
       double newB3=B3;
       double newp0=randomp0.Gaus(par[0], sigmap0);
       double newp1=randomp1.Gaus(par[1], sigmap1);
       double newp10=randomp10.Gaus(par[10], sigmap10);
     //double newB2 = par[4];
    // double new37Mg=random37Mg.Gaus(0.693/par[6], sigma37Mg);
    // double new36Mg=random36Mg.Gaus(0.693/par[7], sigma36Mg);
    // double new35Mg=random35Mg.Gaus(0.693/par[8], sigma35Mg);
    // double new34Mg=random34Mg.Gaus(0.693/par[9], sigma34Mg);
     if(     (newB1 + newB2+newB3) <1 &&
	    (newB1>=0) &&(newB2>=0) && newB3>=0 &&
	     new37Mg>0  &&new36Mg>0 && new35Mg>0 &&new34Mg>0
	 ){ 
    TF1 *fTotal = new TF1("fTotal", batemanrate::TotalRate, 0, timeWin+0, 12);
    fTotal->SetParameters(par);
    fTotal->SetLineColor(2);
    fTotal->SetMinimum(0.001);
   // Enforce constraint
    // Set fit parameters and limits
    //fTotal->SetParLimits(0, 0, 10);
    fTotal->FixParameter(0, par[0]);
    // fTotal->FixParameter(0, newp0);
    fTotal->FixParameter(1, par[1]);
    //  fTotal->FixParameter(1, newp1);
    //fTotal->SetParLimits(1,0 , 100);
    // fTotal->SetParLimits(0, 1, 5);
    fTotal->SetParLimits(2, par[2]/10, par[2]*10); // Halflife
    //  fTotal->FixParameter(3, par[3]);
    //  fTotal->FixParameter(4, par[4]);
     fTotal->FixParameter(3, newB1);
     fTotal->FixParameter(4, newB2);
      fTotal->FixParameter(5, newB3);
      //fTotal->FixParameter(6, par[6]);
	   fTotal->FixParameter(6, 0.693/new37Mg);
	//fTotal->FixParameter(7, par[7]);
      fTotal->FixParameter(7, 0.693/new36Mg);
    // fTotal->FixParameter(8, par[8]);
       fTotal->FixParameter(8, 0.693/new35Mg); 
    // fTotal->FixParameter(9, par[9]);
       fTotal->FixParameter(9, 0.693/new34Mg); 
       fTotal->FixParameter(10, par[10]);
       // fTotal->FixParameter(10, newp10);
     fTotal->FixParameter(11, newB0);
    

    // Update the parameters
        

    // Perform the fit
 int fitStatus =hDecayTime->Fit(fTotal, "ROLLNQS");  // Quiet fit, store the status
TF1 *fMother = new TF1("fMother", batemanrate::MotherRate, 0, timeWin+0, 12);

    for(int i = 0; i < 12; i++) {
    fMother->FixParameter(i,fTotal->GetParameter(i));
    }
    // hDecayTime->Fit(fMother, "QROLN");
        // Check if the fit converged

    bool limit=false;
    double lowerLimit, upperLimit;
double epsilon = 1e-6;  // Tolerance to check if parameter is very close to the limit

 // for (int i = 1; i <2; ++i) {
 //    // Get parameter limits
 //    fTotal->GetParLimits(i, lowerLimit, upperLimit);
    
 //    // Get the current value of the parameter
 //    double parValue = fTotal->GetParameter(i);
    
 //    // Check if the parameter is near the lower or upper limit
 //    if (fabs(parValue - lowerLimit) < epsilon) {
 //        std::cout << "Parameter " << i << " is at or near the lower limit: " << lowerLimit << std::endl;
 // 	limit=true;
 //    } 
 //    if (fabs(parValue - upperLimit) < epsilon) {
 //        std::cout << "Parameter " << i << " is at or near the upper limit: " << upperLimit << std::endl;
 // 	limit=true;
 //    }
 // }
    if (fitStatus==0 &&limit==false// &&(fTotal->Integral(0,15)/hDecayTime->GetBinWidth(1))<=(hDecayTime->Integral(hDecayTime->FindBin(0),hDecayTime->FindBin(15)))
	// &&fMother->Integral(0,15)/hDecayTime->GetBinWidth(1)>30 && fMother->Integral(0,15)/hDecayTime->GetBinWidth(1)<70
	) {
      // Retrieve fitted halflife and chi-square if the fit converged
      double fittedHalflife = 0.693 / fTotal->GetParameter(2);  // Half-life is related to par[2]
      double fitChi2 = fTotal->GetChisquare();
      double Par_[12];
      fTotal->GetParameters(Par_);
      Par_[2]= 0.693 / fTotal->GetParameter(2);
      Par_[6]= 0.693 / fTotal->GetParameter(6);
      Par_[7]= 0.693 / fTotal->GetParameter(7);
      Par_[8]= 0.693 / fTotal->GetParameter(8);
      Par_[9]= 0.693 / fTotal->GetParameter(9);
      std::copy(std::begin(Par_), std::end(Par_), Par);
      chi2=fitChi2;
      // Store results
      // halflifeArray.push_back(fittedHalflife);
      // chi2Array.push_back(fitChi2);
      chi2_vs_hl->Fill(fittedHalflife, fitChi2);
      par_vs_hl->Fill(fittedHalflife, 0.693/fTotal->GetParameter(5));
      total_integral=fTotal->Integral(0,7.5)/hDecayTime->GetBinWidth(1);
 
      parent_integral=fMother->Integral(0,7.5)/hDecayTime->GetBinWidth(1);
      HL->Fill(Par[2]);
      P_Int->Fill(parent_integral);
      Tot_Int->Fill(total_integral);
	   
    } else {
  
   chi2=-1;
   	      }


    delete fTotal;
    delete fMother;

     }
       index=i;
 data->Fill();

std::fill(std::begin(Par), std::end(Par), -1);
 chi2=-1;
 parent_integral=-1;
 total_integral=-1;
 
}

// Create a graph of halflife vs chi-square
//   TGraph *gr = new TGraph(sizeof( halflifeArray), &halflifeArray[0], &chi2Array[0]);
// gr->SetTitle("Chi-Square vs Half-Life ;Half-Life (ms);Chi-Square");
// gr->SetMarkerStyle(20);
// gr->Draw("AP");

   gStyle->SetOptStat(111111111);
  TCanvas* canvas= new TCanvas("");
  canvas->Divide(2,2);
  canvas->cd(1);
  chi2_vs_hl->Draw("colz");
  chi2_vs_hl->SetStats(kTRUE);
  par_vs_hl->SetStats(kTRUE);
  gPad->Update();
  gPad->Modified();
  chi2_vs_hl->Write();

  canvas->cd(2);
  HL->Draw("");
  HL->SetStats(kTRUE);
  HL->SetStats(kTRUE);
  gPad->Update();
  gPad->Modified();
  HL->Write();

  canvas->cd(3);
  P_Int->Draw("");
  P_Int->SetStats(kTRUE);
  P_Int->SetStats(kTRUE);
  gPad->Update();
  gPad->Modified();
  P_Int->Write();
  
  canvas->cd(4);
  Tot_Int->Draw("");
  Tot_Int->SetStats(kTRUE);
  Tot_Int->SetStats(kTRUE);
  gPad->Update();
  gPad->Modified();
  Tot_Int->Write();
  
  data->Write();
}
