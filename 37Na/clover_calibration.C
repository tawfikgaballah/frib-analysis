#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TH1D.h>
#include <TSpectrum.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <vector>
#include <fstream>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <TList.h>
#include <TFile.h>

void clover_calibration() {
  // Create cumulative histograms for time differences before and after calibration
  TH1D* h_before_sum = new TH1D("h_before_sum", "Summed Time Difference Before Calibration", 100, -1000, 1400);
  TH1D* h_after_sum = new TH1D("h_after_sum", "Summed Time Difference After Calibration", 100, -1000, 1400);

  // Directory containing the ROOT files
  TString dirPath = "/mnt/analysis/e21062/aad/e21062B/sortedNew/";

  // Get the list of ROOT files in the directory
  TSystemDirectory dir("TG", dirPath);
  TList* files = dir.GetListOfFiles();
  if (!files) {
    std::cerr << "No files found in the directory!" << std::endl;
    return;
  }

  // Loop through all the files in the directory
  TSystemFile* file;
  TIter next(files);
  while ((file = (TSystemFile*)next())) {
    TString filename = file->GetName();
        
    // Process only ROOT files that match the pattern (e.g., run-xxxx)
    if (!file->IsDirectory() && filename.EndsWith(".root") && filename.Contains("run-")) {
      TString fullPath = dirPath + filename;
      TChain* data = new TChain("data");
      data->Add(fullPath);

      TTreeReader *reader=new TTreeReader(data);
      TTreeReaderArray<double> pspmtlow1_dytime(*reader, "pspmtlow1.dytime");
      TTreeReaderArray<double> pspmthigh1_dytime(*reader, "pspmthigh1.dytime");
      TTreeReaderArray<double> pspmtlow1_dyenergy(*reader, "pspmtlow1.dyenergy");
      TTreeReaderArray<double> pspmthigh1_dyenergy(*reader, "pspmthigh1.dyenergy");
      TTreeReaderValue<Int_t> pspmtlow1_dyhit(*reader, "pspmtlow1.dyhit");
      TTreeReaderValue<Int_t> pspmthigh1_dyhit(*reader, "pspmthigh1.dyhit");
      TTreeReaderValue<Int_t> pspmtlow1_dycdailbit(*reader, "pspmtlow1.dycfdfailbit");
      TTreeReaderValue<Int_t> pspmthigh1_dycfdfailbit(*reader, "pspmthigh1.dycfdfailbit");
      TTreeReaderArray<Double_t> clover_ecal(*reader, "clover.ecal[52]");
      TTreeReaderArray<Double_t> clover_timecal(*reader, "clover.timecal[52]");
      TTreeReaderArray<int> clover_cfdfailbit(*reader, "clover.cfdfailbit[52]");

      std::vector<double> centroids;
      std::vector<int> detector_numbers;

      // Loop over each detector (52 detectors)
      for (int i = 0; i < 52; i++) {
	TH1D* h = new TH1D(Form("h%d", i), Form("h%d", i), 100, -1000, 1400);
	reader->Restart();
	// Fill the histogram with the time difference
	while (reader->Next()) {
	  if(clover_ecal[i]>20 &&clover_cfdfailbit[i]!=1 &&clover_timecal[i]>20){
	    if(// *corr_isforward==1 &&
	       pspmthigh1_dytime.GetSize()>0 && pspmthigh1_dytime[0]>10 && pspmthigh1_dyenergy[0]>10){
	      double time_diff = clover_timecal[i] - pspmthigh1_dytime[0];
	      h->Fill(time_diff);
	      h_before_sum->Fill(time_diff); // Fill summed before calibration histogram
	    }
	    else if(// *corr_isforward==1 &&
		    pspmtlow1_dytime.GetSize()>0 && pspmtlow1_dytime[0]>10 && pspmtlow1_dyenergy[0]>10){
	      double time_diff = clover_timecal[i] - pspmtlow1_dytime[0];
	      h->Fill(time_diff);
	      h_before_sum->Fill(time_diff); // Fill summed before calibration histogram
	    }
	  }
	}

	// Use TSpectrum to identify the peak with the highest amplitude
	TSpectrum *spectrum= new TSpectrum(1);  // Only searching for 1 peak
	int nPeaks = spectrum->Search(h, 2, "", 0.05);  // Adjust the threshold as needed

	if (nPeaks > 0) {
	  double* peaks = spectrum->GetPositionX();
	  double peakPosition = peaks[0];

	  // Fit the peak with a Gaussian in the range [peak-150, peak+150]
	  TF1* gaus = new TF1("gaus", "gaus", peakPosition - 150, peakPosition + 150);
	  h->Fit(gaus, "R");

	  // Get the centroid of the peak
	  double centroid = gaus->GetParameter(1);  // The mean (centroid) of the Gaussian
	  centroids.push_back(centroid);
	  detector_numbers.push_back(i);
	  reader->Restart();
	  // Fill after calibration histogram
	  while (reader->Next()) {
	    if(clover_ecal[i]>20 &&clover_cfdfailbit[i]!=1 &&clover_timecal[i]>20){
	      if(// *corr_isforward==1 &&
		 pspmthigh1_dytime.GetSize()>0 && pspmthigh1_dytime[0]>10 && pspmthigh1_dyenergy[0]>10){
		double calibrated_time_diff = clover_timecal[i] - pspmthigh1_dytime[0] - centroid;
		h_after_sum->Fill(calibrated_time_diff);
	      }
	      else if(// *corr_isforward==1 &&
		      pspmtlow1_dytime.GetSize()>0 && pspmtlow1_dytime[0]>10 && pspmtlow1_dyenergy[0]>10){
		double calibrated_time_diff = clover_timecal[i] - pspmtlow1_dytime[0] - centroid;
		h_after_sum->Fill(calibrated_time_diff);
	      }
	    }
	  }
	 
	 
	}
	delete spectrum; 
	delete h;  // Clean up the histogram for the next iteration
	std::cout<<i;
      }
      	TString runNumber = filename(filename.Index("run-") + 4, 4);  // Extract the run number from filename
	std::ofstream outfile(Form("centroids_run_%s.txt", runNumber.Data()));
	for (size_t i = 0; i < centroids.size(); i++) {
	  outfile << "Detector " << detector_numbers[i] << ": " << centroids[i] << std::endl;
	}
	outfile.close();
	std::cout << "Processed file: " << filename << std::endl;
        delete reader; 
    }
  
  }
  // Save the summed histograms to a ROOT file
  TFile outFile("summed_time_diff_histograms.root", "RECREATE");
  h_before_sum->Write();
  h_after_sum->Write();
  outFile.Close();

  // Plot the summed histograms
  TCanvas* c = new TCanvas("c_summed", "Summed Time Differences Before and After Calibration", 1200, 600);
  c->Divide(2, 1);  // Divide canvas into two sections

  // Draw before calibration
  c->cd(1);
  h_before_sum->SetLineColor(kRed);
  h_before_sum->Draw("");

  // Draw after calibration
  c->cd(2);
  h_after_sum->SetLineColor(kBlue);
  h_after_sum->Draw("");

  // Save the canvas as a PNG image
  // c->SaveAs("summed_time_diff_before_after.png");

  // Clean up
  // delete h_before_sum;
  // delete h_after_sum;
  delete files;
}
