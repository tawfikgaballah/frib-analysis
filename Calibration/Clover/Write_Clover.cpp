
// Include the TLinearSolver header file
#include <vector>
#include <iostream>
#include <cmath>
#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "TF2.h"
#include "/usr/opt/ddastoys/6.2-001/include/DDASRootFitEvent.h"
#include "/usr/opt/ddastoys/6.2-001/include/DDASRootFitHit.h"
using namespace ddastoys;
// DDAS/NSCLDAQ




#include "TInterpreter.h"
#include "TSystem.h"
// ROOT includes
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TFile.h"
#include "TClass.h"
TApplication* theApp;

void ResetChannelList(std::vector<DDASRootFitHit*>  channellist, std::vector<DDASRootFitHit*>::iterator channellist_it) 
{
  channellist_it = channellist.begin();
  
  for (channellist_it = channellist.begin(); channellist_it < channellist.end(); channellist_it++){
    delete *channellist_it;
  }
  channellist.clear();
}

void displayProgressBar(float progress) {
  int barWidth = 70;
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
int main(int argc, char* argv[]) {
  gSystem->Load("libDDASRootFitFormat.so");
   gInterpreter->Declare("#include \"DDASRootFitEvent.h\"");
    gInterpreter->Declare("#include \"DDASRootFitHit.h\"");
    // gInterpreter->Declare("#include \"RootHitExtension.h\"");
    // gInterpreter->Declare("#include \"RootFit1Info.h\"");
    // gInterpreter->Declare("#include \"RootFit2Info.h\"");
    // gInterpreter->Declare("#include \"RootPulseDescription.h\"");

  if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <start_run> <end_run>" << std::endl;
        return 1;
    }

    int start = std::stoi(argv[1]);
    int end = std::stoi(argv[2]);
  // std::string start;
  //   char choice;

  //   std::cout << "Enter run numbers to sort. Type 'q' when you are done.\n";

  //   while (true) {
  //       std::cout << "Enter a number (or 'q' to quit): ";
  //       std::cin >> input;
  // 	if (input == "q" || input == "Q") {
  //           break;
  //       }
  //       // If input is invalid, clear the error and check for 'q'
  //       if (std::cin.fail()) {
  //           std::cin.clear(); // Clear the error state
  //           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
  //           std::cout << "Enter 'q' to quit or try entering a valid number again.\n";
  //           continue;
  //       }
  // 	int number = std::stod(input);
  //       // Add the valid number to the vector
  //       runnumbers.push_back(number);
  //   }

  

  // Generate range of numbers
  std::vector<int> runnumbers;
  for (int i = start; i <= end; ++i) {
    runnumbers.push_back(i);
  }

  for (int i:runnumbers) {
    // if (theApp == nullptr) theApp = new TApplication("theApp", nullptr, nullptr);

    // Output ROOT file and Tree
    TFile* output = new TFile(Form("run-0%d-sorted_test_clover.root", i), "RECREATE");

    // histos
    TH2D* Clover_E=new TH2D("Clover_Chn_Vs_E","Clover_Chn_Vs_E", 6554, 0, 65540, 64, 256,319);
    TH2D* Clover_Ecal=new TH2D("Clover_Chn_Vs_Ecal","Clover_Chn_Vs_Ecal", 10000,0,10000, 64, 256,319);
    TH2D* Anode_E=new TH2D("Anode_Chn_Vs_E","Anode_Chn_Vs_E", 6554, 0, 65540, 256, 416,671);


	
    TChain* data = new TChain("DDASFit");
    data->Add(Form("/mnt/analysis/e23055/eeconverted/run-0%d-*-fitted-converted.root", i));
    //data->Add("/mnt/analysis/e16032/rootfiles/run-2004-150.root");
    std::cout << "Input data chain has " << data->GetEntries() << " events" << std::endl;

    std::vector<DDASRootFitHit*> channellist;
    std::vector<DDASRootFitHit*>::iterator channellist_it;
    DDASRootFitEvent* rawhits = new DDASRootFitEvent();
      TBranch* aRawHitsevent = data->GetBranch("RawHits");
	     
      aRawHitsevent->SetAddress(&rawhits);
	 
    // std::vector<RootHitExtension>* fitdata(0);
    // data->SetBranchAddress("HitFits", &fitdata);

    int totalEntries = data->GetEntries();

    // Event loop
    for (int evt = 0; evt < totalEntries*1; ++evt) {
         ResetChannelList(channellist,channellist_it); 
      
	displayProgressBar(static_cast<float>(evt) / totalEntries);
     	   
      
      std::cout<<"Done"<<'\n';
      data->GetEntry(evt);
      


 
	


      // channellist = rawhits->GetData();
      // int eventsize = channellist.size();
      // // std::cout<<"working"<<'\n';
      //  if(eventsize > 0) {
      // // for (auto channellist_it = channellist.begin(); channellist_it < channellist.end(); channellist_it++) {
      // 	for (long unsigned int i = 0; i < channellist.size(); i++) {
      // 	int crateid = channellist[i]->getCrateID();
      // 	int slotid = channellist[i]->getSlotID();
      // 	int channum = channellist[i]->getChannelID();
      // 	double energy = channellist[i]->getEnergy();
      // 	double time = channellist[i]->getTime();// - (*channellist_it)->coarsetime
      // 	// double timecfd = (*channellist_it)->timecfd;
      // 	// int cfdfailbit=(*channellist_it)->cfdfailbit;
      // 	// int trigsource=(*channellist_it)->cfdtrigsourcebit;
	
      // 	int id = 208 * crateid + 16 * (slotid - 2) + channum;
		
      // 	if (id>=256 && id<=319){
      // 	  Clover_E->Fill(energy, id);
	
      // 	}
               
      // }
      //  }
      delete rawhits;
      delete aRawHitsevent;
    }
    // Write everything to the file
    Clover_E->Write();
    Clover_Ecal->Write();
    output->Close();
    delete output;
   
      
	
  }

  // theApp->Terminate();
  return 0;
}
