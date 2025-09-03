#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"

void ReadFromtxt() {
    // Prompt the user for input
    std::string nucleus;
    std::cout << "Which nucleus do you want to process? (e.g., 37Na or 31F): ";
    std::cin >> nucleus;

    // File names based on user input
    std::string histFile;
    std::vector<std::string> funcFiles;

    if (nucleus == "37Na") {
        histFile = "hist_37Na.txt";
        funcFiles = {
            "fTotal_37Na.txt",
            "fDaughter1_37Na.txt",
            "fDaughter2_37Na.txt",
            "fDaughter3_37Na.txt",
            "fDaughter4_37Na.txt",
            "fMother_37Na.txt",
            "fExpBackground_37Na.txt"
        };
    } else if (nucleus == "31F") {
        histFile = "hist_31F.txt";
        funcFiles = {
            "fTotal_31F.txt",
            "fDaughter1_31F.txt",
            "fDaughter2_31F.txt",
            "fDaughter3_31F.txt",
            "fDaughter4_31F.txt",
            "fMother_31F.txt",
            "fExpBackground_31F.txt"
        };
    } else {
        std::cerr << "Error: Unknown nucleus " << nucleus << std::endl;
        return;
    }
    double binwidth;
    std::cout << "Enter the bin width in ms: ";
    std::cin >> binwidth;
    if(binwidth<0.1){
       std::cerr << "Error: Bin width can't be less than 0.1 ms " << std::endl;
        return;
    }
    // Read histogram
    TH1D* hDecayTime = nullptr;
    std::ifstream infileHist(histFile);
    if (!infileHist.is_open()) {
        std::cerr << "Error: Could not open file " << histFile << " for reading." << std::endl;
        return;
    }

    std::string line;
    std::getline(infileHist, line); // Skip header
    std::vector<double> binCenters, binContents, binErrors;

    while (std::getline(infileHist, line)) {
        std::istringstream ss(line);
        double binCenter, binContent, binError;
        ss >> binCenter >> binContent >> binError;
        binCenters.push_back(binCenter);
        binContents.push_back(binContent);
        binErrors.push_back(binError);
    }
    infileHist.close();

    int nBins = binCenters.size();
    double xMin = binCenters.front() - (binCenters[1] - binCenters[0]) / 2.0;
    double xMax = binCenters.back() + (binCenters[1] - binCenters[0]) / 2.0;
    hDecayTime = new TH1D("hDecayTime", ("Decay Curve and Fit Functions for " + nucleus).c_str(), nBins, xMin, xMax);

    for (int i = 0; i < nBins; ++i) {
        hDecayTime->SetBinContent(i + 1, binContents[i]);
        hDecayTime->SetBinError(i + 1, binErrors[i]);
    }

    // Read and create TGraph for each TF1
    std::vector<TGraph*> graphs;
    int funcIndex = 0;

    for (const auto& funcFile : funcFiles) {
        std::ifstream infileFunc(funcFile);
        if (!infileFunc.is_open()) {
            std::cerr << "Error: Could not open file " << funcFile << " for reading." << std::endl;
            continue;
        }

        // Read the TF1 data as points
        std::vector<double> x, y;
        while (std::getline(infileFunc, line)) {
            std::istringstream ss(line);
            double xi, yi;
            ss >> xi >> yi;
            x.push_back(xi);
            y.push_back(yi);
        }
        infileFunc.close();

        // Create TGraph
        TGraph* graph = new TGraph(x.size(), &x[0], &y[0]);
        graph->SetLineColor(2 + funcIndex); // Different color for each function
        graph->SetLineWidth(2);
        graphs.push_back(graph);
        funcIndex++;
    }


  TCanvas *c = new TCanvas("c",
			   "", 
			   800, 600);
  c->Draw();
  hDecayTime->Rebin(int(binwidth/0.1));

  gPad->SetLogy();
  hDecayTime->SetTitle(";Time (ms);Activity / 0.1 ms"); 
  hDecayTime->Draw("hist PE");
   hDecayTime->SetMinimum(5e-1);
 for (auto* graph : graphs) {
        graph->Draw("L same"); // Draw as a line on the same canvas
    }

}
