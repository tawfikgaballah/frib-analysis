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

std::vector<int> excludedValues = {1289,1332,1335,1398,1423,1405,1409};
void AddRootFiles(TChain *chain, int startNum, int endNum) {
 
 
   

  // string dir = "/mnt/analysis/e21062/aad/e21062B/sorted/";
  string dir ="/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resortedNewCal37Na/";
  for(int i = startNum; i <= endNum; i++) {
    if ((std::find(excludedValues.begin(), excludedValues.end(), i) == excludedValues.end())&&(i<1338 ||i>1391)) {
      string fileName; 
      fileName = Form("run-%d-sorted.root", i);
    
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
}





void AddRootFiles_Cal(TChain *chain, int startNum, int endNum) {

 
   

  string dir = "/projects/e21062/tg/37Na_Setting/";
  
  for(int i = startNum; i <= endNum; i++) {
    if ((std::find(excludedValues.begin(), excludedValues.end(), i) == excludedValues.end())&&(i<1338 ||i>1391)) {
      string fileName; 
      // fileName = Form("run%d_PID_Calibration.root", i);
      fileName = Form("calibration_test_run_%d_linear_two_points_test.root", i);
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
}




// TTree* ConvertChainToTree(TChain *chain, TTree* outputTree)
// {
//     // Create a new TTree with the specified name

//    Long64_t nentries = chain->GetEntries();
// outputTree->CopyTree("data","",nentries);

     
//     return outputTree;
// }
