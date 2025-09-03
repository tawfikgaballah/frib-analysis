#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "TGraphErrors.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
double cutoff(int N, int Z){
  double r=5.7, s=0.120, t=8.05, h=6.49, I=(N-Z)/(N+Z), /*Bs=0.0919,*/ Bs=0.1094;
  double npg=((r*Bs)/pow(N,1/3))*exp((-s*I-t*pow(I,2)));
  double ppg=((r*Bs)/pow(Z,1/3))*exp((s*I-t*pow(I,2)));
  double rnp=h/(pow((N+Z),2/3)*Bs);
  if(N%2==0 &&Z%2==0)
    return 0;
  else if (N%2!=0 &&Z%2==0)
    return npg;  
  else if (N%2==0 &&Z%2!=0)
    return ppg;
  else if (N%2!=0 &&Z%2!=0)
    return ppg+npg-
      rnp;
  else return 0;

}
void Gross_theory() {
  // Open the CSV file
  std::ifstream file("data_full.csv");
  if (!file.is_open()) {
    std::cerr << "Error: Could not open the file!" << std::endl;
    return;
  }

  // Variables to store data
  std::vector<double> QB, d_QB, HL, d_HL;
  std::vector<int> Z, N;
  std::string line;

  // Skip the header
  std::getline(file, line);

  // Read the data
  while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::string value;
    double qb, d_qb, hl, d_hl, z, n;
        
    try {
      // Parse the columns
      std::getline(ss, value, ','); // Skip the name
      std::getline(ss, value, ','); z = std::stod(value); // Column 2: Z
      std::getline(ss, value, ',');  n = std::stod(value); 
      std::getline(ss, value, ','); qb = std::stod(value) / 1000.0; // Column 4: QB in MeV
      std::getline(ss, value, ','); d_qb = std::stod(value) / 1000.0; // Column 5: d-QB in MeV
      std::getline(ss, value, ','); 
      if (value == "STABLE" || value.empty()) continue; // Skip "STABLE" or empty values
      hl = std::stod(value) * 1000; // Column 6: HL in ms
      std::getline(ss, value, ','); 
      if (value.empty()) continue; // Skip if d-HL is missing
      d_hl = std::stod(value) * 1000; // Column 7: d-HL in ms

      // Add valid data
      QB.push_back(qb);
      d_QB.push_back(d_qb);
      HL.push_back(hl);
      d_HL.push_back(d_hl);
      Z.push_back(z);
      N.push_back(n);
    } catch (const std::invalid_argument& e) {
      // Skip invalid rows
      continue;
    }
  }

  file.close();

  // Create a TGraphErrors
  TGraphErrors* graph = new TGraphErrors();
  int pointIndex = 0;

  // Colors for grouping
  std::vector<int> colors = {kRed, kBlue, kGreen, kMagenta, kOrange, kCyan};
  int nColors = colors.size();

  // Add points to the graph
  std::cout<<QB.size()<<'\n';
  for (size_t i = 0; i < QB.size(); ++i) {
    double C=0;
    if(Z[i]==9
       ){
      // if(N[i]%2==0&& Z[i]%2==0)
      //   C=0;
      // else if((N[i]+Z[i])%2!=0)
      //   C=13/sqrt(N[i]+Z[i]);
      // else if(N[i]%2!=0&& Z[i]%2!=0)
      // C=12.84/sqrt(N[i]+Z[i]);
      C=cutoff(N[i],Z[i]);
      std::cout<<C<<'\n';
      QB[i]-=C;
      graph->SetPoint(pointIndex, QB[i], HL[i]);
      graph->SetPointError(pointIndex, d_QB[i], d_HL[i]);
      pointIndex++;
      
      // Set marker color based on Z value
      int colorIndex = static_cast<int>(Z[i]) % nColors;

      graph->SetMarkerColor(kBlue);
      graph->GetXaxis()->SetTitle("QB-C (MeV)");
      graph->GetYaxis()->SetTitle("HL (ms)");
      graph->SetMarkerStyle(20); // Circle marker
      graph->SetMarkerSize(.5);
    }
  }
 
  // Fit the data
  TF1* fit = new TF1("fit", "[0]*pow((x),-4)", 0, 20);
  fit->SetParameter(0,7.07e05); // Initial parameter guesses
  graph->Fit(fit, "RO");

  // Draw the graph
  TCanvas* canvas = new TCanvas("canvas", "Fit Graph with Groups", 800, 600);
  // gStyle->SetOptFit(1); // Show fit results;
  gPad->SetLogx();
  gPad->SetLogy();
  graph->Draw("AP");
  canvas->SaveAs("fit_graph.pdf"); // Save the output as a PDF
 std::cout<<cutoff(11,26)<<'\n';
 std::cout<<"37Na HL: "<<fit->GetParameter(0)*pow((24.9-cutoff(26,11)),-4)<<'\n';
 std::cout<<"31F HL: "<<fit->GetParameter(0)*pow((25.6-cutoff(22,9)),-4)<<'\n';
}
