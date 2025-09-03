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

void AddRootFiles(TChain *chain, int runNum, int startNum, int endNum) {
  // string dir = "/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/newTau-cal/";
 string dir ="/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resortedNewCal37Na";
  for(int i = startNum; i <= endNum; i++) {
    string fileName; 
    if(runNum < 100) {
      if(i < 10) {
	fileName = Form("run-00%d-sorted.root", runNum, i);
      } else if(i < 1000) {
	fileName = Form("run-00%d-sorted.root", runNum, i);
      } else if(i > 1000) {
	fileName = Form("run-00%d-sorted.root", runNum, i);	
      }
    } else if(runNum < 1000) {
      if(i < 10) {
	fileName = Form("run-0%d-sorted.root", runNum, i);
      } else if(i < 1000) {
	fileName = Form("run-0%d-sorted.root", runNum, i);
      } else if(i > 1000) {
	fileName = Form("run-0%d-sorted.root", runNum, i);	
      }
    } else if(runNum >= 1000) {
      if(i < 10) {
	fileName = Form("run-%d-sorted.root", runNum, i);
      } else if(i < 1000) {
	fileName = Form("run-%d-sorted.root", runNum, i);
      } else if(i > 1000) {
	fileName = Form("run-%d-sorted.root", runNum, i);	
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
