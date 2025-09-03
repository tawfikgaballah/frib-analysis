#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "/projects/e21062/tg/rootAnalysis/rootAnalysisFinal/include/TPID.h"
void Reader(){
  gStyle->SetOptStat(11111111);
  TChain *data = new TChain("data");


  // Open the directory
    void* dir = gSystem->OpenDirectory("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/RSL/rootanalysis-Amelia-Sept2024/forwardCorr/");
    const char* file;

    // Create a vector to hold the valid run numbers
    std::vector<int> runNumbers;

    // Iterate over all files in the directory
    while ((file = gSystem->GetDirEntry(dir))) {
        TString fileName = TString(file);
        
        // Check if the file name matches the "run-*-sorted.root" format and extract the run number
        if (fileName.BeginsWith("run-") && fileName.EndsWith("-sorted.root")) {
            TString runNumberStr = fileName(4, fileName.Length() - 16); // Extract the run number between "run-" and "-sorted.root"
            int runNumber = runNumberStr.Atoi();
            
            // Exclude run 1398
            if (runNumber !=1398 // &&(runNumber == 1281 || runNumber==1282 || runNumber==1283)
		) {
                runNumbers.push_back(runNumber); // Add valid run number to the vector
            }
        }
    }

    // Sort the run numbers in ascending order
    std::sort(runNumbers.begin(), runNumbers.end());

    // Add the files to the TChain in the sorted order
    for (int runNumber : runNumbers) {

        TString filePath = TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/RSL/rootanalysis-Amelia-Sept2024/forwardCorr/run-%d-sorted.root", runNumber);
        
        // Add the file to the TChain
        data->Add(filePath);

        // Print the added file path
        std::cout << "Added file: " << filePath.Data() << std::endl;
    }

    // Close the directory
    gSystem->FreeDirectory(dir);
 


TH2D* PID_Implant=nullptr;
  TH2D* PID_Decay=nullptr;
   TH2D* PID_Implant_Forward=nullptr;
  TH2D* PID_Decay_Forward=nullptr;
   TH2D* PID_Implant_Reverse=nullptr;
  TH2D* PID_Decay_Reverse=nullptr;



  PID_Implant=new TH2D("PID_Implant","PID_Implant",1000,-1000,-900,1400,0,1400);
  PID_Implant->GetXaxis()->SetTitle("tof");
  PID_Implant->GetYaxis()->SetTitle("de2");

  PID_Decay=new TH2D("PID_Decay","PID_Decay",1000,-1000,-900,1400,0,1400);
  PID_Decay->GetXaxis()->SetTitle("tof");
  PID_Decay->GetYaxis()->SetTitle("de2");


  PID_Decay_Forward=new TH2D("PID_Decay_Forward","PID_Decay_Forward",1000,-1000,-900,1400,0,1400);
  PID_Decay_Forward->GetXaxis()->SetTitle("tof");
  PID_Decay_Forward->GetYaxis()->SetTitle("de2");

  
std::map<std::tuple<int, int, std::string>, std::string> nuclei = {
    /* {{2, 9, "Ne"}, "29Ne"},
    {{2, 9, "F"}, "29F"},
    {{2, 7, "F"}, "27F"},
    {{2, 6, "F"}, "26F"},
    {{4, 1, "Al"}, "41Al"},
    {{4, 0, "Al"}, "40Al"},
    {{3, 9, "Al"}, "39Al"}, */
    {{3, 3, "Na"}, "33Na"},
    {{3, 7, "Na"}, "37Na"}
   /*  {{3, 7, "Na"}, "37Na"} */
};
TFile* blobs=new TFile("./iongates_6mm_radius.root","Read");
std::map<std::tuple<int, int, std::string>, TH1D*> hIonDecayTime;
std::map<std::tuple<int, int, std::string>, TCutG*> iongates;

 
for (const auto& entry : nuclei) {
     int i = std::get<0>(entry.first);
     int j = std::get<1>(entry.first);
     std::string nucl = std::get<2>(entry.first);
     const char* nucl_name = entry.second.c_str();
     // File operations and object manipulations
     if (blobs->IsOpen()) {
       iongates[entry.first] = (TCutG*)blobs->Get(Form("%d%d%s_Decay", i, j, nucl.c_str()));
       if (iongates[entry.first]) {
     
	 // h2CloverNaAll[entry.first]=new TH2D(Form("DecayTime_Vs_Clover_^{%d%d}%s",i,j,nucl.c_str()),
	 // 				     Form("Total Clover Spectrum, gated on #beta-decays of ^{%d%d}%s",i,j,nucl.c_str()),
	 // 				     4500, 0, 4500,300,0,100);
	 // GetOutputList()->Add(h2CloverNaAll[entry.first]);
	 hIonDecayTime[entry.first]=new TH1D(Form("hIonDecayTime_^{%d%d}%s",i,j,nucl.c_str()),Form("hIonDecayTime_^{%d%d}%s",i,j,nucl.c_str()),2000,-100,100);
	
       }
     }
   }





    
   TFile *output =new TFile("Amelia_Files_33_37_Na_PID_6mm.root","recreate");
  
  // Initialize TTreeReader using the TChain
  TTreeReader fReader(data);

  // Reading values from the TTree
  TTreeReaderValue<std::vector<TPID>> implantlist(fReader, "implantlist");
  TTreeReaderValue<double> corr_dxpos(fReader, "corr.dxpos");
  TTreeReaderValue<double> corr_dypos(fReader, "corr.dypos");
  TTreeReaderValue<double> corr_dtime(fReader, "corr.dtime");
  TTreeReaderValue<double> corr_itof(fReader, "corr.itof");
  TTreeReaderValue<double> corr_ide2(fReader, "corr.ide2");
  TTreeReaderValue<int> corr_isdecay(fReader, "corr.isdecay");
  TTreeReaderValue<int> corr_isimplant(fReader, "corr.isimplant");
  
  //  TTreeReaderValue<int> pspmtlow1_dyhit(fReader, "pspmtlow1.dyhit");
  // TTreeReaderArray<Double_t> clover_ecal(fReader, "clover.ecal[52]");
  // TH1D* clover_E=new TH1D("Total Clover Spectrum, gated on #beta-decays of ^{30}Ne","Total Clover Spectrum, gated on #beta-decays of ^{30}Ne",4500,0,4500);
  // Iterating through the implant list
  long int totalentries= data->GetEntries();


  long int counter=0; 
  while (fReader.Next()) {
   // Calculate the integer percentage
    int percentage = (counter * 100) / totalentries;

    // Only print if the percentage is an exact integer and counter matches that percentage
    if (counter % (totalentries / 100) == 0 && percentage > 0) {
        std::cout << "Percentage done: " << percentage << "%" << std::endl;
    }

    counter++;
    if(*corr_isimplant==1)
    PID_Implant->Fill(*corr_itof, *corr_ide2);
    
bool isGoodCorr = (*corr_isdecay==1);
  for (auto implant:*implantlist){
    double TOF=implant.tof;
    double DE2=implant.de2;
    double ixpos=implant.xpos;
    double iypos=implant.ypos;
    double itime= implant.time;
    double dtimecal=*corr_dtime-itime;
    if(sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2))<=3 &&dtimecal<=100){
      // PID_Decay->Fill(TOF, DE2);
      for (const auto& entry : nuclei) {
      	int i = std::get<0>(entry.first);
      	int j = std::get<1>(entry.first);
      	std::string nucl = std::get<2>(entry.first);
      	const char* nucl_name = entry.second.c_str();
      	if (iongates[entry.first]->IsInside(TOF, DE2) && isGoodCorr) {
      	  hIonDecayTime[entry.first]->Fill(dtimecal);
      	}
      }
      PID_Decay_Forward->Fill(TOF,DE2);
      // if(*corr_isforward==1){
      // 	PID_Decay_Forward->Fill(TOF, DE2);}
      // else if (*corr_isreverse==1){
      // 	PID_Decay_Reverse->Fill(TOF, DE2);
      // }
    }
  }






    
    // for (auto& implant : *implantlist) {
    //   double tof1 = implant.tof;
    //   double DE2 = implant.de2;
    //   double ixpos=implant.xpos;
    //   double iypos= implant.ypos;
    //   if(D30Ne_neutron->IsInside(tof1, DE2) && (sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2)))<=10){
    // 	for(int i=0; i<52; i++){
    // 	  if(clover_ecal[i]>20){
    // 	    clover_E->Fill(clover_ecal[i]);
    // 	  }
    // 	}
    //   }
    // }
  }
  output->cd();
 for (const auto& entry : nuclei) {
   int i = std::get<0>(entry.first);
   int j = std::get<1>(entry.first);
   std::string nucl = std::get<2>(entry.first);
   const char* nucl_name = entry.second.c_str();
   // fOutputFile->mkdir(Form("3%dNa",i));
   // fOutputFile->cd(Form("3%dNa",i));
   //  fOutput->FindObject(Form("iongates_3%dNa",i));
   // // fOutput->FindObject(Form("I3%dNa.",i));
   // // fOutput->FindObject(Form("DecayTime_Vs_Clover_^{3%d}Na",i));
   
   // fOutput->FindObject(Form("hIonDecayTime_^{3%d}Na",i));
   // fOutput->FindObject(Form("Clover_^{3%d}Na_Vs_Time",i));

   output->mkdir(Form("%d%d%s",i,j,nucl.c_str()));
   output->cd(Form("%d%d%s",i,j,nucl.c_str()));
   // fOutput->FindObject(Form("iongates_3%dNe",i));
  /*  fOutput->FindObject(Form("DecayTime_Vs_Clover_^{%d%d}%s",i,j,nucl.c_str())); */
   hIonDecayTime[entry.first]->Write();
   // fOutputFile->cd();
   // hIonDecayTime[entry.first]->Write();
 }
 output->cd();
  PID_Decay_Forward->Write();
  PID_Implant->Write();
  output->Close();
}
