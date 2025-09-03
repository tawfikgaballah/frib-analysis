
#ifndef __PID_CORRECTION_H__
#define __PID_CORRECTION_H__


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TTree.h"


/* #include "TFile.h" */
#include "TH1.h"
 #include "TSpectrum.h" 
#include "TF1.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TTree.h"
#include "TBranch.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TTreeReaderValue.h"
#include <fstream>
#include <iostream>
#include "TPID.h"

using namespace std;

//Variables
int rnum; //Run Number
Double_t DE2;
Double_t TOF;
vector<int> rnums;  //RunNumbers
std::map<int, std::vector<std::pair<double, double>>> dataMap;
//Files
TFile *fout;  //output file 


#endif // __PID_CORRECTION_H__
