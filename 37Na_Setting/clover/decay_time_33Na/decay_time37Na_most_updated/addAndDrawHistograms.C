#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include <iostream>
#include <iomanip>

void addAndDrawHistograms() {
    // List of file names
    const char* filenames[5] = {
        "systimatics_37Na_B0n\=0.05.root",
        "systimatics_37Na_B0n\=0.1.root",
        "systimatics_37Na_B0n\=0.15.root",
        "systimatics_37Na_B0n\=0.2.root",
        "systimatics_37Na_B0n\=0.25.root"
    };

    // Names of the histograms to be retrieved from each file
    const char* histNames[4] = { "Half-Life Distribution", "Parent Integral Distribution", "Total Integral Distribution", "Chi2_Vs_HL"};  // Replace with actual histogram names

    // Arrays to store the added histograms
    TH1D* addedHists1D[3] = {nullptr, nullptr, nullptr};  // For the 1D histograms
    TH2D* addedHist2D = nullptr;  // For the 2D histogram

    // Loop over the 1D histograms (first 3 are 1D)
    for (int h = 0; h < 3; h++) {
        for (int i = 0; i < 5; i++) {
            // Open each file
            TFile* file = TFile::Open(filenames[i], "READ");
            if (!file || file->IsZombie()) {
                std::cerr << "Error opening file: " << filenames[i] << std::endl;
                continue;
            }

            // Get the 1D histogram from the file
            TH1D* hist = (TH1D*)file->Get(histNames[h]);
            if (!hist) {
                std::cerr << "Error retrieving histogram: " << histNames[h] << " from file: " << filenames[i] << std::endl;
                file->Close();
                continue;
            }

            // Add histograms with the same name
            if (addedHists1D[h] == nullptr) {
                // Clone the first histogram found
                addedHists1D[h] = (TH1D*)hist->Clone();
                addedHists1D[h]->SetDirectory(0);  // Disconnect from file to avoid memory issues
            } else {
                // Add the current histogram to the sum
                addedHists1D[h]->Add(hist);
            }

            // Close the file
            file->Close();
        }
    }

    // Handle the 2D histogram
    for (int i = 0; i < 5; i++) {
        // Open each file
        TFile* file = TFile::Open(filenames[i], "READ");
        if (!file || file->IsZombie()) {
            std::cerr << "Error opening file: " << filenames[i] << std::endl;
            continue;
        }

        // Get the 2D histogram from the file
        TH2D* hist2D = (TH2D*)file->Get(histNames[3]);  // The 4th histogram is the 2D one
        if (!hist2D) {
            std::cerr << "Error retrieving 2D histogram: " << histNames[3] << " from file: " << filenames[i] << std::endl;
            file->Close();
            continue;
        }

        // Add the 2D histograms
        if (addedHist2D == nullptr) {
            // Clone the first 2D histogram found
            addedHist2D = (TH2D*)hist2D->Clone();
            addedHist2D->SetDirectory(0);  // Disconnect from file to avoid memory issues
        } else {
            // Add the current 2D histogram to the sum
            addedHist2D->Add(hist2D);
        }

        // Close the file
        file->Close();
    }

    // Draw the histograms on a canvas
    TCanvas* canvas = new TCanvas("canvas", "Added Histograms", 1200, 800);
    canvas->Divide(2, 2);  // Divide canvas into 2x2 sub-pads for 3x 1D histograms and 1x 2D histogram

    // Draw the 1D histograms
    for (int h = 0; h < 3; h++) {
        canvas->cd(h + 1);
        if (addedHists1D[h]) {
            addedHists1D[h]->SetLineColor(h + 1);  // Set different colors for each histogram
            addedHists1D[h]->Draw();
        } else {
            std::cerr << "1D Histogram " << histNames[h] << " could not be added." << std::endl;
        }
    }

    // Draw the 2D histogram in the last pad
    canvas->cd(4);  // Move to the 4th sub-pad
    if (addedHist2D) {
        addedHist2D->Draw("COLZ");  // Draw as a color plot
    } else {
        std::cerr << "2D Histogram " << histNames[3] << " could not be added." << std::endl;
    }

    // Save the canvas as a PNG file
    canvas->SaveAs("added_histograms.png");
}
