#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "/projects/e21062/tg/rootAnalysis/rootAnalysisFinal/include/TPID.h"
#include "/projects/e21062/tg/rootAnalysis/rootAnalysisFinal/include/TClover.h"
void Reader_Individual(){
  gStyle->SetOptStat(11111111);




 // gSystem->Load("/projects/e21062/aad/e21062B/rootAnalysisFinal/libTParameters.so");
 //  // gSystem->Load("libDict.so");
 //   gSystem->Load("/projects/e21062/aad/e21062B/rootAnalysisFinal/include/");





  // Open the directory
  void* dir = gSystem->OpenDirectory("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/");
  //void* dir = gSystem->OpenDirectory("/mnt/analysis/e21062/aad/e21062B/sortedNew/");
  
  const char* file;

  // Create a vector to hold the valid run numbers
  std::vector<int> runNumbers;

  // Iterate over all files in the directory
  while ((file = gSystem->GetDirEntry(dir))) {
    TString fileName = TString(file);

    // Check if the file name matches the "run-*-sorted.root" format and extract the run number
    if (fileName.BeginsWith("filtered_filesrun-")  && fileName.EndsWith("-sorted.root.root")){
// && fileName.EndsWith("-sorted.root")	) {
      TString runNumberStr = fileName(18, fileName.Length() - 17); // Extract the run number between "run-" and "-xscintT-sipm-sorted-TG-48-10mm.root"
      int runNumber = runNumberStr.Atoi();

      // Exclude run 1398
      if ((runNumber == 1281 || runNumber==1282 || runNumber==1283)&&
	  runNumber != 1398 && runNumber != 1335 && runNumber != 1332 && runNumber != 1289) {
	runNumbers.push_back(runNumber); // Add valid run number to the vector
      }
    }
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
									{{2, 6, "F"}, "26F"},*/
								     // {{4, 1, "Al"}, "41Al"},
								     // {{4, 0, "Al"}, "40Al"}
								     {{3, 2, "Na"}, "32Na"},
								     {{3, 3, "Na"}, "33Na"},
								     {{3, 4, "Na"}, "34Na"},
								     {{3, 5, "Na"}, "35Na"},
								     {{3, 6, "Na"}, "36Na"},
								     {{3, 7, "Na"}, "37Na"},
								     {{3, 8, "Na"}, "38Na"}
  };
  TFile* blobs=new TFile("./iongates_6mm_radius.root","Read");
  std::map<std::tuple<int, int, std::string>, TH1D*> hIonDecayTime;
  std::map<std::tuple<int, int, std::string>, TH2D*> h2decay_Vs_clover;
  std::map<std::tuple<int, int, std::string>, TH2D*> h2radius_Vs_clover;
  std::map<std::tuple<int, int, std::string>, TH2D*> h2decay_Vs_radius;
  std::map<std::tuple<int, int, std::string>, TH2D*> h2clover_Vs_tdiff;
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

	// h2decay_Vs_clover[entry.first]=new TH2D(Form("DecayTime_Vs_Clover_^{%d%d}%s",i,j,nucl.c_str()),
	// 					Form("DecayTime_Vs_Clover_^{%d%d}%s",i,j,nucl.c_str()),
	// 					4500, 0, 4500,200,-100,100);

	h2clover_Vs_tdiff[entry.first]=new TH2D(Form("Clover_Vs_TDiff_^{%d%d}%s",i,j,nucl.c_str()),
						Form("Clover_Vs_TDiff_^{%d%d}%s",i,j,nucl.c_str()),
						2000,-50,150,4500, 0, 4500);
	// h2radius_Vs_clover[entry.first]=new TH2D(Form("Radius_Vs_Clover_^{%d%d}%s",i,j,nucl.c_str()),
	// 					 Form("Radius_Vs_Clover_^{%d%d}%s",i,j,nucl.c_str()),
	// 					 9000, -4500, 4500,80,0,8);

	// h2decay_Vs_radius[entry.first]=new TH2D(Form("DecayTime_Vs_Radius_^{%d%d}%s",i,j,nucl.c_str()),
	// 					Form("DecayTime_Vs_Radius_^{%d%d}%s",i,j,nucl.c_str()),
	// 					80,0,8,200,-100,100);
	// hIonDecayTime[entry.first]=new TH1D(Form("hIonDecayTime_^{%d%d}%s",i,j,nucl.c_str()),Form("hIonDecayTime_^{%d%d}%s",i,j,nucl.c_str()),200,-100,100);

      }
    }
  }






  TFile *output =new TFile("clover_Vs_tdiff_trimmed_files.root","recreate");



















  // Sort the run numbers in ascending order
  std::sort(runNumbers.begin(), runNumbers.end());

  // Add the files to the TChain in the sorted order
  for (int runnumber : runNumbers) {
    TString filePath = TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_filesrun-%d-sorted.root.root", runnumber);
    TFile* filter=TFile::Open(filePath);
    // Add the file to the TChain
    TTree *data = (TTree*)filter->Get("trimmed_data");			

    TFile* friendfile=TFile::Open(TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files_Clover_LaBr3run-%d-sorted.root", runnumber));
    TTree *data_friend = (TTree*)friendfile->Get("trimmed_data");

    // Print the added file path
    std::cout << "Added file: " << filePath.Data() << std::endl;
    double TOFoffset, deScale;

    // std::ifstream pidcorr;
    // pidcorr.open("/projects/e21062/tg/rootAnalysis/rootAnalysisFinal/pid_corr.txt");
    // if(pidcorr.is_open()){
    //   bool flag = false;
    //   while(!pidcorr.eof()){
    // 	char temp[10];
    // 	pidcorr >> temp;		
    // 	// Encounters # "comment" delimiter
    // 	if(temp[0] == '#'){
    // 	  pidcorr.ignore(1000, '\n');
    // 	  continue;
    // 	}
    // 	else if(std::stof(temp) == std::stof(std::to_string(runnumber))){
    // 	  flag = true;
    // 	  pidcorr >> temp;
    // 	  TOFoffset = std::stof(temp); // temp, convert to double
    // 	  pidcorr >> temp;
    // 	  deScale = std::stof(temp); // temp, convert to double
    // 	  break;
    // 	}
    //   }

    //   if(flag == false){
    // 	//std::cout << "Error: No PID Correction found for run " << runnumber << ". Exiting." << std::endl;
    // 	//std::exit(EXIT_FAILURE);
    // 	std::cout << "Warning: No PID Correction found for run " << runnumber << ". Setting TOF offset = 0 and deScale = 1." << std::endl;
    //   }

    //   else{
    // 	std::cout << "Found PID corrections. TOF offset = " << TOFoffset << " and deScale = " << deScale << std::endl;
    //   }

    // }
    // else{
    //   std::cout << "Error: PID Corrections file not open. Exiting." << std::endl;
    //   std::exit(EXIT_FAILURE);
    // }

    //
    // END Get TOF Offset & dE Scaling
    // ___________________________________________________________________  













// data->SetBranchStatus("*", 0);

// // Now, selectively enable only the branches you need
// data->SetBranchStatus("implantlist", 1);
// data->SetBranchStatus("corr.dxpos", 1);
// data->SetBranchStatus("corr.dypos", 1);
// data->SetBranchStatus("corr.dtime", 1);
// data->SetBranchStatus("corr.isdecay", 1);
// data->SetBranchStatus("corr.itof", 1);
// data->SetBranchStatus("corr.ide2", 1);
// data->SetBranchStatus("corr.isimplant", 1);
// data->SetBranchStatus("pspmtlow1.dytime", 1);
// data->SetBranchStatus("pspmthigh1.dytime", 1);
// data->SetBranchStatus("pspmtlow1.dyenergy", 1);
// data->SetBranchStatus("pspmthigh1.dyenergy", 1);
// data->SetBranchStatus("pspmtlow1.dyhit", 1);
// data->SetBranchStatus("pspmthigh1.dyhit", 1);
// data->SetBranchStatus("pspmtlow1.dycfdfailbit", 1);
// data->SetBranchStatus("pspmthigh1.dycfdfailbit", 1);
// data->SetBranchStatus("clover.ecal", 1);
// data->SetBranchStatus("clover.timecal", 1);
// data->SetBranchStatus("clover.cfdfailbit", 1);



    data->AddFriend(data_friend, "Gamma");






  
    TTreeReader* fReader = new TTreeReader(data);
    // Reading values from the TTree
     TTreeReaderValue<std::vector<TPID>> implantlist(*fReader, "implantlist");
    // TTreeReaderValue<std::vector<double>> corr_radius(*fReader, "corr_radius");
    TTreeReaderValue<double> corr_dxpos(*fReader, "corr_dxpos");
    TTreeReaderValue<double> corr_dypos(*fReader, "corr_dypos");
    TTreeReaderValue<double> corr_dtime(*fReader, "corr_dtime");
    TTreeReaderValue<int> corr_isdecay(*fReader, "corr_isdecay");
    TTreeReaderValue<double> corr_itof(*fReader, "corr_itof");
    TTreeReaderValue<double> corr_ide2(*fReader, "corr_ide2");
    TTreeReaderValue<int> corr_isimplant(*fReader, "corr_isimplant");
    // TTreeReaderValue<int> corr_isforward(*fReader, "corr_isforward");
    TTreeReaderArray<double> pspmtlow1_dytime(*fReader, "pspmtlow1_dytime");
    TTreeReaderArray<double> pspmthigh1_dytime(*fReader, "pspmthigh1_dytime");
    TTreeReaderArray<double> pspmtlow1_dyenergy(*fReader, "pspmtlow1_dyenergy");
    TTreeReaderArray<double> pspmthigh1_dyenergy(*fReader, "pspmthigh1_dyenergy");
    TTreeReaderValue<Int_t> pspmtlow1_dyhit(*fReader, "pspmtlow1_dyhit");
    TTreeReaderValue<Int_t> pspmthigh1_dyhit(*fReader, "pspmthigh1_dyhit");
    TTreeReaderValue<Int_t> pspmtlow1_dycfdfailbit(*fReader, "pspmtlow1_dycfdfailbit");
    TTreeReaderValue<Int_t> pspmthigh1_dycfdfailbit(*fReader, "pspmthigh1_dycfdfailbit");
    TTreeReaderArray<Double_t> clover_ecal(*fReader, "Gamma.clover_ecal[52]");
    TTreeReaderArray<Double_t> clover_timecal(*fReader, "Gamma.clover_timecal[52]");
    TTreeReaderArray<int> clover_cfdfailbit(*fReader, "Gamma.clover_cfdfailbit[52]");
   
    // TH1D* clover_E=new TH1D("Total Clover Spectrum, gated on #beta-decays of ^{30}Ne","Total Clover Spectrum, gated on #beta-decays of ^{30}Ne",4500,0,4500);
    // Iterating through the implant list
    long int totalentries= data->GetEntries();
    std::cout<<"Processing Run: "<<runnumber<<" with Entries: "<< totalentries<<'\n';

    long int counter=0;
    fReader->Restart();
    while (fReader->Next()) {
       std::cout<<"stuck"<<'\n';
      // Calculate the integer percentage
      int percentage = (counter * 100) / totalentries;

      // Only print if the percentage is an exact integer and counter matches that percentage
      if (counter % (totalentries / 100) == 0 && percentage > 0) {
      	std::cout << "Percentage done: " << percentage << "%" << std::endl;
      }

      counter++;

      // if(*corr_isimplant==1 &&*corr_isforward==1)
      // 	PID_Implant->Fill(*corr_itof, (*corr_ide2)*deScale);
      bool isGoodCorr = (*corr_isdecay==1);
      int implant_count=0;
   
      for (auto implant:*implantlist){
      	double TOF=implant.tof;
      	double DE2=(implant.de2);
      	double ixpos=implant.xpos;
      	double iypos=implant.ypos;
      	double itime= implant.time;
      	double dtimecal=*corr_dtime-itime;
	 
    
   
      	//	if( sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2))<=6 &&dtimecal<=100){
      	for (const auto& entry : nuclei) {
      	  int i = std::get<0>(entry.first);
      	  int j = std::get<1>(entry.first);
      	  std::string nucl = std::get<2>(entry.first);
      	  const char* nucl_name = entry.second.c_str();
      	  if (iongates[entry.first]->IsInside(TOF, DE2) && isGoodCorr &&dtimecal<=100) {
      	    // h2decay_Vs_radius[entry.first]->Fill(sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2)),dtimecal);
      	    for(int i=0; i<sizeof(clover_ecal); i++){
      	      if(clover_ecal[i]>20 && clover_cfdfailbit[i]!=1 && clover_timecal[i]>20){
      		if(sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2))<=3)
      		  // h2decay_Vs_*clover[entry.first]->Fill(*clover_ecal[i], dtimecal);
      		  // if(dtimecal<=60){
      		  if(// *corr_isforward==1 &&
      		     pspmthigh1_dytime.GetSize()>0 && pspmthigh1_dytime[0]>10 && pspmthigh1_dyenergy[0]>10){
      		    // h2radius_Vs_*clover[entry.first]->Fill(*clover_ecal[i],sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2)) );
      		    h2clover_Vs_tdiff[entry.first]->Fill(((clover_timecal[i])-pspmthigh1_dytime[0])/1.e03, clover_ecal[i]);
      		  }
      		  else if(// *corr_isforward==1 &&
      			  pspmtlow1_dytime.GetSize()>0 && pspmtlow1_dytime[0]>10 && pspmtlow1_dyenergy[0]>10){
      		    h2clover_Vs_tdiff[entry.first]->Fill(((clover_timecal[i])-pspmtlow1_dytime[0])/1.e03, clover_ecal[i]);
      		  }
      		// else
      		//     h2radius_Vs_*clover[entry.first]->Fill(-*clover_ecal[i],sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2)) );
      		// }
      	      }
      	    }
		  
      	    // hIonDecayTime[entry.first]->Fill(dtimecal);
      	  }
      	}
      	// if(*corr_isforward==1){
      	//   PID_Decay_Forward->Fill(TOF,DE2);
      	// }
      	// PID_Decay->Fill(TOF, DE2);
      	//implant_count++;
	   
      	//	}
      }
     






      // for (auto& implant : *implantlist) {
      //   double tof1 = implant.tof;
      //   double DE2 = implant.de2;
      //   double ixpos=implant.xpos;
      //   double iypos= implant.ypos;
      //   if(D30Ne_neutron->IsInside(tof1, DE2) && (sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2)))<=10){
      // 	for(int i=0; i<52; i++){
      // 	  if(*clover_ecal[i]>20){
      // 	    *clover_E->Fill(*clover_ecal[i]);
      // 	  }
      // 	}
      //   }
      // }
    }
    delete data;
    delete data_friend;
    delete fReader;
    TOFoffset=0;
    deScale=0;
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
    // hIonDecayTime[entry.first]->Write();
    // fOutputFile->cd();
    // hIonDecayTime[entry.first]->Write();

    // h2decay_Vs_clover[entry.first]->Write();
    // h2radius_Vs_clover[entry.first]->Write();
    // h2decay_Vs_radius[entry.first]->Write();
    h2clover_Vs_tdiff[entry.first]->Write();
	
  }
  output->cd();
  // PID_Decay_Forward->Write();
  // PID_Decay->Write();
  // PID_Implant->Write();
  output->Close();
}
