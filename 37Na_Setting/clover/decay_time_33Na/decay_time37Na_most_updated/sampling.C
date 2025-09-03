#include "TMath.h"
#include "TF1.h"
#include "TStopwatch.h"
#include "Math/DistSampler.h"
#include "Math/DistSamplerOptions.h"
#include "Math/MinimizerOptions.h"
#include "Math/Factory.h"
#include "TKDTreeBinning.h"
#include "TTree.h"
#include "TFile.h"
#include "TMatrixDSym.h"
#include "TVectorD.h"
#include "TCanvas.h"
#include <cmath>

// Define the GausND structure for 4 dimensions (B0, B1, B2, B3)
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
// Function to display the progress bar
void showProgress(int current, int total) {
    int barWidth = 70;
    float progress = float(current) / float(total);
    
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}
void sampling() {

   const int N = 10000;  // Number of samples
   const int DIM = 4;  // We are working in 4 dimensions for B0, B1, B2, B3

   double xmin[] = {0, 0, 0, 0};   // Minimum values for B0, B1, B2, B3
   double xmax[] = {1, 1, 1, 1};   // Maximum values for B0, B1, B2, B3
   double par0[] = { 0, 0.51, 0.24, 0.25,  // means for B0, B1, B2, B3
                     0.25, 0.51, 0.24, 0.25, // sigmas (standard deviations)
                     -0.1, -0.1, -0.1, -0.1, -0.1, -0.1}; // correlations

   GausND gaus4d(4);
   TF1 * f = new TF1("functionND", gaus4d, 0, 1, 14);
   f->SetParameters(par0);

   TString name;
   for (int i = 0; i < 4; ++i) {
      f->SetParName(i, name.Format("mu_%d", i+1));
      f->SetParName(i+4, name.Format("sigma_%d", i+1));
      if (i < 3) f->SetParName(i+8, name.Format("corr_%d", i+1));
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

   // Generate the samples and ensure sum ~= 1 for B0, B1, B2, B3
   TFile *file = new TFile("multiDimSampling_B.root", "RECREATE");
   TTree *t1 = new TTree("t1", "Tree from Gaussian Sampling");
   double B0, B1, B2, B3;
   t1->Branch("B0", &B0, "B0/D");
   t1->Branch("B1", &B1, "B1/D");
   t1->Branch("B2", &B2, "B2/D");
   t1->Branch("B3", &B3, "B3/D");

   const double epsilon = 1e-6; // Tolerance for sum check
   for (int i = 0; i < N; ++i) {
     //  do {
         sampler->Sample(v);
         B0 = v[0];
         B1 = v[1];
         B2 = v[2];
         B3 = v[3];
	 double sum = B0 + B1 + B2 + B3;
      B0 /= sum;
      B1 /= sum;
      B2 /= sum;
      B3 /= sum;
      //}  while (std::abs(B0 + B1 + B2 + B3 - 1) >= epsilon);  // Check sum

      t1->Fill();
      // Update progress bar
      showProgress(i + 1, N);
   }

   // Save to file
   t1->Write();
   file->Close();
}
