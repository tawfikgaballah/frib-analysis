//
// Analysis code for sorting NSCLDAQ data into Beta Group detector classes.
// Developed for analyzing data taken during the 2019-2020 clover campaign
// with the intention of being back-portable for (at least) e16032 analysis.
// The code assumes that there is fit information present in the input data.
//
// The structure of (some of) the code is shamelessly ripped off from GRSISort:
//   https://github.com/GRIFFINCollaboration/GRSISort
// developed by (among others) P. Bender, R. Dunlop and V. Bildstein.
// Structural elemnets have also been adopted from previous Beta Group
// analysis codes, specifically those by B. Lewis, A. Richard and B. Crider.
// 
// --A. Chester, 3/10/2020
//

#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

#include "TAnalyzer.h"

/**
 * Usage:
 *    This outputs an error message that shows how the program should be used
 *     and exits using std::exit().
 *
 * @param o   - references the stream on which the error message is printed.
 * @param msg - Error message that precedes the usage information.
 */
static void
usage(std::ostream& o, const char* msg, bool sortsubrun)
{
  o << msg << std::endl;
  o << "Usage:\n";
  if(sortsubrun)
    o << "  betasort <infiledir> <outfiledir> <runnumber> <subrun>\n";
  else
    o << "  betasort <infiledir> <outfiledir> <runnumber>\n";
  o << "      <infile>: File dir for the dumped file to be analyzed\n";
  o << "      <outfile>: File dir for the analyzed file to be saved\n";
  o << "      <runnumber>: run number to be analyzed\n";
  if(sortsubrun)
    o << "      <subrun>: subrun number to be analyzed\n";
  std::exit(EXIT_FAILURE);
}

inline bool exists_test (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

// Main
//
// Function:
//   - creates input/output data structures
//   - calls analyzer to build/fill detector classes
//   - writes output
//
// Params:
//   - none
//
// Return:
//   - 0 on success
//   - 1 on failure
//


bool isValidCondition(const std::string& cond) {
  return cond == "sipm" || cond == "xscintB" || cond == "SIPMT" || cond == "xscintT";
}

bool isValidCondition_beta(const std::string& cond) {
  return cond == "sipm" || cond == "xscintB" || cond == "SIPMT" || cond == "xscintT"|| cond=="PIN";
}
int main(int argc, char **argv) 
{
  // // Make sure we have enough command line parameters.
  // if (argc != 4) {
  //   usage(std::cerr, "Not enough command line parameters",false);
  // }

  // added for subrun sorting calibration data
  if (argc != 7 ) {
    std::cerr << "Usage: " << argv[0] << " <infiledir> <outfiledir> <runnumber> <beta_gate> <tofv>\n";
    std::cerr << "       beta_gate, tofv are conditions ('sipm', 'xscintB', 'SIPMT', 'xscintT').\n";
    std::exit(EXIT_FAILURE);
   /*  usage(std::cerr, "Not enough command line parameters",true); */
  }
  
  using std::cout;
  using std::endl; 
  using std::string;

  // If we're happy how this is working, we can make a chain
  // for a single run number including all the segments and
  // write out one output, see FilterDDAS.cpp for an example.
  // The inputs and data processing have to be changed a little bit.
  // --ASC 2/21/20
  TFile *rootfile_out;
  TTree *tree_out;

  //need chain with name of data tree
  TChain * chain_in = new TChain("DDASFit");
  
  TAnalyzer analyzer; // for sorting data

  string fileInDir(argv[1]);
  string fileOutDir(argv[2]);
  string runnumber(argv[3]);
 std::string beta_gate = argv[5]; // Condition 1 as a string
  std::string tofv = argv[6]; // Condition 2 as a string
 

  if (!isValidCondition_beta(beta_gate) || !isValidCondition(tofv)) {
    std::cerr << "Invalid condition values!!. Please choose from 'sipm', 'xscintB', 'SIPMT', or 'xscintT'.\n";
    std::cout << "input: " << beta_gate << " and " << tofv << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::cout << "Running analysis with conditions: " << beta_gate << " and " << tofv << std::endl;
  if(stoi(runnumber) < 10) {
    runnumber.insert(0,"000");
  } else if(stoi(runnumber) >= 10 && stoi(runnumber)< 100) {
    runnumber.insert(0,"00");
  } else if(stoi(runnumber) >= 100 && stoi(runnumber)< 1000) {
    runnumber.insert(0,"0");
  }
  
  cout << "Input file dir: " << fileInDir  << endl;

  //find subrun files and add them to TChain
  //int subrun = 0;
  int subrun = atoi(argv[4]); // added for subrun sorting calibration data
  bool havedata = false;
  if (subrun == 0) { subrun = 1; }
  for(int sr=0; sr<subrun; sr++) {
    std::ostringstream inputfileName;
    if(sr/*subrun*/ < 10) {
      inputfileName << fileInDir << "run-" << runnumber << "-0" << /*subrun*/sr << "-fitted.root";

      if(exists_test(inputfileName.str())) {
  	chain_in->AddFile(inputfileName.str().c_str());
  	std::cout << "Added " << inputfileName.str() << " to TChain" << std::endl;
        havedata = true;
      } else {
	break;
      }
    } else {
      inputfileName << fileInDir << "run-" << runnumber << "-" << sr << "-fitted.root";
      if(exists_test(inputfileName.str())) {
  	chain_in->AddFile(inputfileName.str().c_str());
  	std::cout << "Added " << inputfileName.str() << " to TChain" << std::endl;
        havedata = true;
      }
      else {
	break;
      }
    }
  }

  if(!havedata){
    cout << "ERROR: Cannot find runfile in " << fileInDir << "!" << endl;
    cout << "Exiting..." << endl;
    exit(1);
  }
  
  time_t start, stop;
  time(&start);    

  // Output file and tree
  std::ostringstream outputfileName;
  outputfileName << fileOutDir << "run-" << runnumber <<"-"<<beta_gate<<"-"<<tofv<< "-sorted-TG-48-10mm-fixed-correlator.root";

  cout << "Output filename: " << outputfileName.str() << endl;  
  rootfile_out = new TFile(outputfileName.str().c_str(), "RECREATE");
  tree_out = new TTree("data","data");
  
  // Go through the data in the file
  if(havedata) {
    // Call the analyzer to map channels and sort data
    // Since AnalyzeData is template we need to specify if a tree or chain is put in
    // e.g. analyzer.AnalyzeData<TTree>(tree_in, tree_out, runnumber);
    analyzer.AnalyzeData<TChain>(chain_in, tree_out, runnumber,beta_gate,tofv);
    
  }

  // Write Output
  rootfile_out->cd();
  tree_out->Write();
  rootfile_out->Close();
  
  time(&stop);
  float diff = difftime(stop,start);
  cout << endl << endl;
  cout << "Elapsed time = " << diff << " seconds" << endl;
    
  return 0;
}

