

void SaveTH2DAsMatrix(TH2D* hist, const char* filename) {
    // Open the output file
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Get the number of bins in X and Y
    int nBinsX = hist->GetNbinsX();
    int nBinsY = hist->GetNbinsY();

    // Write the first row (X bin centers)
    outfile << "\t"; // Leave the first cell empty for Y bin centers
    for (int i = 1; i <= nBinsX; ++i) {
        double xCenter = hist->GetXaxis()->GetBinCenter(i);
        outfile << xCenter;
        if (i < nBinsX) {
            outfile << "\t"; // Tab separator
        }
    }
    outfile << std::endl;

    // Write the matrix with Y bin centers as the first column
    for (int j = 1; j <= nBinsY; ++j) { // Loop over Y bins (rows)
        // Write the Y bin center
        double yCenter = hist->GetYaxis()->GetBinCenter(j);
        outfile << yCenter << "\t";

        // Write the bin contents for each X bin
        for (int i = 1; i <= nBinsX; ++i) { // Loop over X bins (columns)
            double content = hist->GetBinContent(i, j);
            outfile << content;
            if (i < nBinsX) {
                outfile << "\t"; // Tab separator
            }
        }
        outfile << std::endl; // New line after each row
    }

    // Close the file
    outfile.close();
    std::cout << "Histogram saved as a matrix with bin centers in " << filename << std::endl;
}

void TH2DToText(const char* histname="P';
;kghID_Decay_Forward", const char* rootdfile="Amelia_Files_33_37_Na_PID_6mm.root", const char* filename="PID_corr.dat") {
  TFile* file=new TFile(rootfile, "read");
  TH2D* hist=(TH2D*)file->Get(histname);


  // Open the output file
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write header
    outfile << "# x\ty\tbin_content" << std::endl;

    // Get the number of bins in x and y
    int nBinsX = hist->GetNbinsX();
    int nBinsY = hist->GetNbinsY();

    // Loop over all bins in x and y
    for (int i = 1; i <= nBinsX; ++i) { // Bin index starts at 1
        for (int j = 1; j <= nBinsY; ++j) {
            // Get the bin centers
            double x = hist->GetXaxis()->GetBinCenter(i);
            double y = hist->GetYaxis()->GetBinCenter(j);

            // Get the bin content
            double content = hist->GetBinContent(i, j);

            // Write to file
            outfile << x << "\t" << y << "\t" << content << std::endl;
        }
    }

    // Close the file
    outfile.close();
    std::cout << "Histogram saved to " << filename << std::endl;
    SaveTH2DAsMatrix(hist, "PID_matrix_corr.dat");
}
