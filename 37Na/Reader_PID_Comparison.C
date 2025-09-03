#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "/projects/e21062/tg/rootAnalysis/rootAnalysisFinal/include/TPID.h"
void Reader_PID_Comparison(){
  gStyle->SetOptStat(11111111);

  // Open the directory
  void* dir = gSystem->OpenDirectory("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/");
  const char* file;

  // Create a vector to hold the valid run numbers
  std::vector<int> runNumbers;

  // Iterate over all files in the directory
  while ((file = gSystem->GetDirEntry(dir))) {
    TString fileName = TString(file);

    // Check if the file name matches the "run-*-sorted.root" format and extract the run number
    if (fileName.BeginsWith("run-") && fileName.EndsWith("-xscintT-sipm-sorted-TG-48-10mm-fixed-correlator.root")) {
      TString runNumberStr = fileName(4, fileName.Length() - 16); // Extract the run number between "run-" and "-xscintT-sipm-sorted-TG-48-10mm.root"
      int runNumber = runNumberStr.Atoi();

      // Exclude run 1398
      if ( // (runNumber == 1281 || runNumber==1282 || runNumber==1283)&&
	  runNumber != 1335 && runNumber != 1332 && runNumber != 1289 && runNumber != 1433) {
	runNumbers.push_back(runNumber); // Add valid run number to the vector
      }
    }
  }
  // Close the directory
  gSystem->FreeDirectory(dir);


 
     
  // Sort the run numbers in ascending order
  std::sort(runNumbers.begin(), runNumbers.end());

  // Add the files to the TChain in the sorted order
  for (int runnumber : runNumbers) {

    TH2D* PID_Implant_U=new TH2D("PID_Implant_U_Gamma","PID_Implant_U_Gamma",1000,-1010,-910,1400,0,1400);
     PID_Implant_U->GetXaxis()->SetTitle("tof=sipm.time-DB3PPACUAnT.time");
     PID_Implant_U->GetYaxis()->SetTitle("de2");

     TH2D* PID_Implant_D=new TH2D("PID_Implant_D_Gamma","PID_Implant_D_Gamma",1000,-1010,-910,1400,0,1400);
    PID_Implant_D->GetXaxis()->SetTitle("tof=sipm.time-DB3PPACDAnT.time");
    PID_Implant_D->GetYaxis()->SetTitle("de2");

     TH2D* PID_Implant_UN=new TH2D("PID_Implant_U_Neutron","PID_Implant_U_Neutron",1000,-1500,-1400,1400,0,1400);
    PID_Implant_UN->GetXaxis()->SetTitle("tof=sipm.time-DB3PPACUAnT.time");
    PID_Implant_UN->GetYaxis()->SetTitle("de2");
    TString filePath = TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-%d-xscintT-sipm-sorted-TG-48-10mm-fixed-correlator.root", runnumber);
    TFile *output =new TFile(Form("PID_Comparison_neutron_pin_run_%d.root", runnumber),"recreate");
    
    // Add the file to the TChain
    TChain *data = new TChain("data");			
    data->Add(filePath);

    // Print the added file path
    std::cout << "Added file: " << filePath.Data() << std::endl;
    double TOFoffset, deScale;

    std::ifstream pidcorr;
    pidcorr.open("/projects/e21062/tg/rootAnalysis/rootAnalysisFinal/pid_corr.txt");
    if(pidcorr.is_open()){
      bool flag = false;
      while(!pidcorr.eof()){
	char temp[10];
	pidcorr >> temp;		
	// Encounters # "comment" delimiter
	if(temp[0] == '#'){
	  pidcorr.ignore(1000, '\n');
	  continue;
	}
	else if(std::stof(temp) == std::stof(std::to_string(runnumber))){
	  flag = true;
	  pidcorr >> temp;
	  TOFoffset = std::stof(temp); // temp, convert to double
	  pidcorr >> temp;
	  deScale = std::stof(temp); // temp, convert to double
	  break;
	}
      }

      if(flag == false){
	//std::cout << "Error: No PID Correction found for run " << runnumber << ". Exiting." << std::endl;
	//std::exit(EXIT_FAILURE);
	std::cout << "Warning: No PID Correction found for run " << runnumber << ". Setting TOF offset = 0 and deScale = 1." << std::endl;
      }

      else{
	std::cout << "Found PID corrections. TOF offset = " << TOFoffset << " and deScale = " << deScale << std::endl;
      }

    }
    else{
      std::cout << "Error: PID Corrections file not open. Exiting." << std::endl;
      std::exit(EXIT_FAILURE);
    }

    //
    // END Get TOF Offset & dE Scaling
    // ___________________________________________________________________ 

    TTreeReader* fReader = new TTreeReader(data);
    // Reading values from the TTree
    TTreeReaderValue<int> corr_isimplant(*fReader, "corr.isimplant");
    TTreeReaderValue<int> corr_isforward(*fReader, "corr.isforward");
    TTreeReaderValue<double> sipm_time(*fReader, "sipm.time");
    TTreeReaderValue<double> DB3PPACDAnT_time(*fReader, "DB3PPACDAnT.time");
    TTreeReaderValue<double> DB3PPACUAnT_time(*fReader, "DB3PPACUAnT.time");
    TTreeReaderValue<double> DB3PPACULT_time(*fReader, "DB3PPACULT.time");
    TTreeReaderValue<double> pin02_ecal(*fReader, "pin02.ecal");
    TTreeReaderValue<double> xpin2_ecal(*fReader, "xpin2.ecal");
    TTreeReaderValue<int> sipm_hit(*fReader, "sipm.hit");
    TTreeReaderValue<int> DB3PPACDAnT_hit(*fReader, "DB3PPACDAnT.hit");
    TTreeReaderValue<int> DB3PPACUAnT_hit(*fReader, "DB3PPACUAnT.hit");
    TTreeReaderValue<int> DB3PPACULT_hit(*fReader, "DB3PPACULT.hit");
    TTreeReaderValue<int> pspmtlow1_hit(*fReader, "pspmtlow1.hit");
    TTreeReaderValue<int> vetoR_hit(*fReader, "vetoR.hit");
    TTreeReaderValue<int> pin02_hit(*fReader, "pin02.hit");
    TTreeReaderValue<int> xpin2_hit(*fReader, "xpin2.hit");
    
    long int totalentries= data->GetEntries();
    std::cout<<"Processing Run: "<<runnumber<<" with Entries: "<< totalentries<<'\n';

    long int counter=0; 
    while (fReader->Next()) {
      // Calculate the integer percentage
      int percentage = (counter * 100) / totalentries;

      // // Only print if the percentage is an exact integer and counter matches that percentage
      // if (counter % (totalentries / 100) == 0 && percentage > 0) {
      // 	std::cout << "Percentage done: " << percentage << "%" << std::endl;
      // }

      // counter++;

      if(*corr_isimplant==1 &&*corr_isforward==1 &&*pin02_hit==1 &&*sipm_hit==1){
	if(*DB3PPACDAnT_hit==1)
	  PID_Implant_D->Fill(*sipm_time-*DB3PPACDAnT_time+TOFoffset,*pin02_ecal*deScale);
	if(*DB3PPACUAnT_hit==1)
	  PID_Implant_U->Fill(*sipm_time-*DB3PPACUAnT_time,*pin02_ecal);
	
      }  
      if(*xpin2_ecal>240 &&*corr_isforward==1 &&*xpin2_hit==1 &&*sipm_hit==1 &&*vetoR_hit!=1 &&*pspmtlow1_hit==1){
if(*DB3PPACULT_hit==1)
	  PID_Implant_UN->Fill(*sipm_time-*DB3PPACULT_time,*xpin2_ecal);
 }
    }
    delete data;
    delete fReader;
    TOFoffset=0;
    deScale=0;
    output->cd();
    PID_Implant_U->Write();
    PID_Implant_D->Write();
    PID_Implant_UN->Write();
    output->Close();
    delete output;
    PID_Implant_U->Reset();
    PID_Implant_D->Reset();
    PID_Implant_UN->Reset();
    delete  PID_Implant_U;
    delete  PID_Implant_D;
    delete  PID_Implant_UN;
    
  }

}
