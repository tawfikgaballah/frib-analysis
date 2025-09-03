/* The purpose of this script is to
 * add analysed root files. The best way
 * is to split a single run into several 
 * parts (each part contains several segments
 */
#include <iostream>
#include <cstdlib>

using namespace std;

#include "TH1.h"
#include "TH2.h"
#include "TList.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include <sstream>


void AddRootFiles(TChain *chain, int runNum, int startNum, int endNum) {
 
 
   

  string dir = "/mnt/analysis/e16032/tg1250/rootfiles/2004/";
  
  for(int i = startNum; i <= endNum; i++) {
    string fileName; 

    if(runNum < 100) {
      if(i < 10) {
    	fileName = Form("run-00%d-0%d-tg1250.root", runNum, i);
      } else if(i < 1000) {
    	fileName = Form("run-00%d-%d-tg1250.root", runNum, i);
      }
    } else if(runNum < 1000) {
      if(i < 10) {
    	fileName = Form("run-0%d-%d-tg1250.root", runNum, i);
      } else if(i < 1000) {
    	fileName = Form("run-0%d-%d-tg1250.root", runNum, i);
      }
      else if(i > 1000) {
    	fileName = Form("run-0%d-%d-tg1250.root", runNum, i);
      }
    } else if(runNum >= 1000) {
      if(i < 10) {
    	fileName = Form("run-%d-0%d-tg1250.root", runNum, i);
      } else if(i < 1000) {
    	fileName = Form("run-%d-%d-tg1250.root", runNum, i);
      }
    }
    fileName = dir + fileName;
  
    // check if the file exists
    std::ifstream infile(fileName.c_str());
    if(!infile.good()) {
      cout << ":((((((    CANNOT FIND FILE: "
  	   << fileName.c_str() << endl;

      //      exit(EXIT_FAILURE); 
    } else {
      //      cout << "File found! Now processing..." << endl;
      chain->AddFile(fileName.c_str());
      cout << "File "
  	   << fileName.c_str() << " loaded!" << endl;

    }

  }
}

// TTree* ConvertChainToTree(TChain *chain, TTree* outputTree)
// {
//     // Create a new TTree with the specified name

//    Long64_t nentries = chain->GetEntries();
// outputTree->CopyTree("data","",nentries);

     
//     return outputTree;
// }
