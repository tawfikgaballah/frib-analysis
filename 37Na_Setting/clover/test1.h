//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb  9 10:00:46 2023 by ROOT version 6.10/02
// from TTree data/data
// found on file: /mnt/analysis/e21062/snl/sorted/run-0248-sorted.root
//////////////////////////////////////////////////////////

#ifndef test1_h
#define test1_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>
#include <TH1D.h>
#include <TH2D.h>
#include <TCutG.h>
#include <TH3D.h>
#include <TAxis.h>
#include <vector>
#include "/projects/e21062/snl/rootanalysis/include/TPID.h"
/* #include "TParameters.h" */


/* #include "/projects/e21062/snl/rootanalysis/include/TPSPMT.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TPSPMTUTK.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TPulser.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TSSSD.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TTAC.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TTrace.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TADC.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TClock.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TClover.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TCorrelation.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TDDASDiagnostics.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TDSSD.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TLaBr3.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TLinearSolver.h" */
/* #include "/projects/e21062/snl/rootanalysis/include/TModule.h" */

/* #include "/projects/e21062/snl/rootanalysis/include/TPIN.h" */




/* #include "/projects/e21062/TG/rootanalysisAFit/include/TParameters.h" */
#define RUNNUM 248
#define DYELOW 1200
#define DYEHIGH 10000
#define PSPMTMULT 70 


TH1D *h1Clover32NaAll=nullptr;
TH2D *h2Clover32NaAll=nullptr;
TH1D *h1Clover32NaAll_AB=nullptr;
TH2D *h2Clover32NaAll_AB=nullptr;
TH2D *h2E_Vs_id_AB=nullptr;
TH2D *h2E_Vs_id=nullptr;
TH2D *clover_Vs_time=nullptr;
TH2D *clover_Vs_time_ab=nullptr;
class test1 : public TSelector {
 public :

  //TFile* inroot = new TFile("/projects/e16032/0710analysis_YX/analysis/extract_analysis/XBlobs.root.249", "READ");
  TCutG* iongates=nullptr;

  TFile* inroot3 = new TFile("/projects/e16032/0710analysis_YX/analysis/extract_analysis/coincidence_cuts.root", "READ");
   TCutG *coincCut=nullptr;
  TCutG* coincCut_ab=nullptr;
  /* TCutG *cut = (TCutG*)inroot->Get("blob23"); */
 
  TH2D* PIDhist=nullptr;
  
  TTreeReader     fReader;  //!the tree reader
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
  
  // Readers to access the data (delete the ones you do not need).
  TTreeReaderValue<unsigned int> fUniqueID = {fReader, "fUniqueID"};
  TTreeReaderValue<unsigned int> fBits = {fReader, "fBits"};
  TTreeReaderValue<unsigned int> ddasdiagnostics_fUniqueID = {fReader, "ddasdiagnostics.fUniqueID"};
  TTreeReaderValue<unsigned int> ddasdiagnostics_fBits = {fReader, "ddasdiagnostics.fBits"};
  TTreeReaderValue<Int_t> ddasdiagnostics_cmult = {fReader, "ddasdiagnostics.cmult"};
  TTreeReaderValue<Double_t> ddasdiagnostics_eventlength = {fReader, "ddasdiagnostics.eventlength"};
  TTreeReaderValue<Double_t> ddasdiagnostics_tdiffevent = {fReader, "ddasdiagnostics.tdiffevent"};
  TTreeReaderArray<int> ddasdiagnostics_chanhit = {fReader, "ddasdiagnostics.chanhit"};
  TTreeReaderValue<unsigned int> clock_fUniqueID = {fReader, "clock.fUniqueID"};
  TTreeReaderValue<unsigned int> clock_fBits = {fReader, "clock.fBits"};
  TTreeReaderValue<Double_t> clock_current = {fReader, "clock.current"};
  TTreeReaderValue<Double_t> clock_initial = {fReader, "clock.initial"};
  TTreeReaderValue<unsigned int> pspmthigh1_fUniqueID = {fReader, "pspmthigh1.fUniqueID"};
  TTreeReaderValue<unsigned int> pspmthigh1_fBits = {fReader, "pspmthigh1.fBits"};
  TTreeReaderValue<Double_t> pspmthigh1_dyenergy = {fReader, "pspmthigh1.dyenergy"};
  TTreeReaderValue<Double_t> pspmthigh1_dyecal = {fReader, "pspmthigh1.dyecal"};
  TTreeReaderValue<Double_t> pspmthigh1_dytime = {fReader, "pspmthigh1.dytime"};
  TTreeReaderValue<unsigned int> pspmthigh1_dytimecfd = {fReader, "pspmthigh1.dytimecfd"};
  TTreeReaderValue<Int_t> pspmthigh1_dycfdfailbit = {fReader, "pspmthigh1.dycfdfailbit"};
  TTreeReaderValue<Int_t> pspmthigh1_dyoverflow = {fReader, "pspmthigh1.dyoverflow"};
  TTreeReaderValue<Int_t> pspmthigh1_dymult = {fReader, "pspmthigh1.dymult"};
  TTreeReaderArray<Double_t> pspmthigh1_dyenergies = {fReader, "pspmthigh1.dyenergies[16]"};
  TTreeReaderArray<Double_t> pspmthigh1_dytimes = {fReader, "pspmthigh1.dytimes[16]"};
  TTreeReaderValue<Double_t> pspmthigh1_dychisq_single = {fReader, "pspmthigh1.dychisq_single"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1_single = {fReader, "pspmthigh1.dyE1_single"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1real_single = {fReader, "pspmthigh1.dyE1real_single"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1cal_single = {fReader, "pspmthigh1.dyE1cal_single"};
  TTreeReaderValue<Double_t> pspmthigh1_dyT1_single = {fReader, "pspmthigh1.dyT1_single"};
  TTreeReaderValue<Double_t> pspmthigh1_dyoffset_single = {fReader, "pspmthigh1.dyoffset_single"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1steepness_single = {fReader, "pspmthigh1.dyE1steepness_single"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1decay_single = {fReader, "pspmthigh1.dyE1decay_single"};
  TTreeReaderValue<Double_t> pspmthigh1_dychisq_double = {fReader, "pspmthigh1.dychisq_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1_double = {fReader, "pspmthigh1.dyE1_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1real_double = {fReader, "pspmthigh1.dyE1real_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1cal_double = {fReader, "pspmthigh1.dyE1cal_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyT1_double = {fReader, "pspmthigh1.dyT1_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1steepness_double = {fReader, "pspmthigh1.dyE1steepness_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1decay_double = {fReader, "pspmthigh1.dyE1decay_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE2_double = {fReader, "pspmthigh1.dyE2_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE2real_double = {fReader, "pspmthigh1.dyE2real_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE2cal_double = {fReader, "pspmthigh1.dyE2cal_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyT2_double = {fReader, "pspmthigh1.dyT2_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE2steepness_double = {fReader, "pspmthigh1.dyE2steepness_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE2decay_double = {fReader, "pspmthigh1.dyE2decay_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyoffset_double = {fReader, "pspmthigh1.dyoffset_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dytdiffE1E2 = {fReader, "pspmthigh1.dytdiffE1E2"};
  TTreeReaderValue<Double_t> pspmthigh1_dytdiffE1E2cal = {fReader, "pspmthigh1.dytdiffE1E2cal"};
  TTreeReaderArray<Double_t> pspmthigh1_aenergy = {fReader, "pspmthigh1.aenergy[4]"};
  TTreeReaderArray<Double_t> pspmthigh1_aecal = {fReader, "pspmthigh1.aecal[4]"};
  TTreeReaderArray<Double_t> pspmthigh1_aenergy_qdc = {fReader, "pspmthigh1.aenergy_qdc[4]"};
  TTreeReaderValue<Double_t> pspmthigh1_asum = {fReader, "pspmthigh1.asum"};
  TTreeReaderValue<Double_t> pspmthigh1_asum_qdc = {fReader, "pspmthigh1.asum_qdc"};
  TTreeReaderArray<Double_t> pspmthigh1_atime = {fReader, "pspmthigh1.atime[4]"};
  TTreeReaderArray<Double_t> pspmthigh1_atimecal = {fReader, "pspmthigh1.atimecal[4]"};
  TTreeReaderArray<Int_t> pspmthigh1_aoverflow = {fReader, "pspmthigh1.aoverflow[4]"};
  TTreeReaderValue<Int_t> pspmthigh1_aoverflowcount = {fReader, "pspmthigh1.aoverflowcount"};
  TTreeReaderValue<Int_t> pspmthigh1_amultraw = {fReader, "pspmthigh1.amultraw"};
  TTreeReaderValue<Int_t> pspmthigh1_amult = {fReader, "pspmthigh1.amult"};
  TTreeReaderArray<Int_t> pspmthigh1_pixelmult = {fReader, "pspmthigh1.pixelmult[4]"};
  TTreeReaderValue<Double_t> pspmthigh1_xpos = {fReader, "pspmthigh1.xpos"};
  TTreeReaderValue<Double_t> pspmthigh1_ypos = {fReader, "pspmthigh1.ypos"};
  TTreeReaderValue<Int_t> pspmthigh1_dyhit = {fReader, "pspmthigh1.dyhit"};
  TTreeReaderArray<Int_t> pspmthigh1_ahit = {fReader, "pspmthigh1.ahit[4]"};
  TTreeReaderValue<Int_t> pspmthigh1_hit = {fReader, "pspmthigh1.hit"};
  TTreeReaderValue<unsigned int> pspmthigh2_fUniqueID = {fReader, "pspmthigh2.fUniqueID"};
  TTreeReaderValue<unsigned int> pspmthigh2_fBits = {fReader, "pspmthigh2.fBits"};
  TTreeReaderValue<Double_t> pspmthigh2_dyenergy = {fReader, "pspmthigh2.dyenergy"};
  TTreeReaderValue<Double_t> pspmthigh2_dyecal = {fReader, "pspmthigh2.dyecal"};
  TTreeReaderValue<Double_t> pspmthigh2_dytime = {fReader, "pspmthigh2.dytime"};
  TTreeReaderValue<unsigned int> pspmthigh2_dytimecfd = {fReader, "pspmthigh2.dytimecfd"};
  TTreeReaderValue<Int_t> pspmthigh2_dycfdfailbit = {fReader, "pspmthigh2.dycfdfailbit"};
  TTreeReaderValue<Int_t> pspmthigh2_dyoverflow = {fReader, "pspmthigh2.dyoverflow"};
  TTreeReaderValue<Int_t> pspmthigh2_dymult = {fReader, "pspmthigh2.dymult"};
  TTreeReaderArray<Double_t> pspmthigh2_dyenergies = {fReader, "pspmthigh2.dyenergies[16]"};
  TTreeReaderArray<Double_t> pspmthigh2_dytimes = {fReader, "pspmthigh2.dytimes[16]"};
  TTreeReaderValue<Double_t> pspmthigh2_dychisq_single = {fReader, "pspmthigh2.dychisq_single"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1_single = {fReader, "pspmthigh2.dyE1_single"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1real_single = {fReader, "pspmthigh2.dyE1real_single"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1cal_single = {fReader, "pspmthigh2.dyE1cal_single"};
  TTreeReaderValue<Double_t> pspmthigh2_dyT1_single = {fReader, "pspmthigh2.dyT1_single"};
  TTreeReaderValue<Double_t> pspmthigh2_dyoffset_single = {fReader, "pspmthigh2.dyoffset_single"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1steepness_single = {fReader, "pspmthigh2.dyE1steepness_single"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1decay_single = {fReader, "pspmthigh2.dyE1decay_single"};
  TTreeReaderValue<Double_t> pspmthigh2_dychisq_double = {fReader, "pspmthigh2.dychisq_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1_double = {fReader, "pspmthigh2.dyE1_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1real_double = {fReader, "pspmthigh2.dyE1real_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1cal_double = {fReader, "pspmthigh2.dyE1cal_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyT1_double = {fReader, "pspmthigh2.dyT1_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1steepness_double = {fReader, "pspmthigh2.dyE1steepness_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1decay_double = {fReader, "pspmthigh2.dyE1decay_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE2_double = {fReader, "pspmthigh2.dyE2_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE2real_double = {fReader, "pspmthigh2.dyE2real_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE2cal_double = {fReader, "pspmthigh2.dyE2cal_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyT2_double = {fReader, "pspmthigh2.dyT2_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE2steepness_double = {fReader, "pspmthigh2.dyE2steepness_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE2decay_double = {fReader, "pspmthigh2.dyE2decay_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyoffset_double = {fReader, "pspmthigh2.dyoffset_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dytdiffE1E2 = {fReader, "pspmthigh2.dytdiffE1E2"};
  TTreeReaderValue<Double_t> pspmthigh2_dytdiffE1E2cal = {fReader, "pspmthigh2.dytdiffE1E2cal"};
  TTreeReaderArray<Double_t> pspmthigh2_aenergy = {fReader, "pspmthigh2.aenergy[4]"};
  TTreeReaderArray<Double_t> pspmthigh2_aecal = {fReader, "pspmthigh2.aecal[4]"};
  TTreeReaderArray<Double_t> pspmthigh2_aenergy_qdc = {fReader, "pspmthigh2.aenergy_qdc[4]"};
  TTreeReaderValue<Double_t> pspmthigh2_asum = {fReader, "pspmthigh2.asum"};
  TTreeReaderValue<Double_t> pspmthigh2_asum_qdc = {fReader, "pspmthigh2.asum_qdc"};
  TTreeReaderArray<Double_t> pspmthigh2_atime = {fReader, "pspmthigh2.atime[4]"};
  TTreeReaderArray<Double_t> pspmthigh2_atimecal = {fReader, "pspmthigh2.atimecal[4]"};
  TTreeReaderArray<Int_t> pspmthigh2_aoverflow = {fReader, "pspmthigh2.aoverflow[4]"};
  TTreeReaderValue<Int_t> pspmthigh2_aoverflowcount = {fReader, "pspmthigh2.aoverflowcount"};
  TTreeReaderValue<Int_t> pspmthigh2_amultraw = {fReader, "pspmthigh2.amultraw"};
  TTreeReaderValue<Int_t> pspmthigh2_amult = {fReader, "pspmthigh2.amult"};
  TTreeReaderArray<Int_t> pspmthigh2_pixelmult = {fReader, "pspmthigh2.pixelmult[4]"};
  TTreeReaderValue<Double_t> pspmthigh2_xpos = {fReader, "pspmthigh2.xpos"};
  TTreeReaderValue<Double_t> pspmthigh2_ypos = {fReader, "pspmthigh2.ypos"};
  TTreeReaderValue<Int_t> pspmthigh2_dyhit = {fReader, "pspmthigh2.dyhit"};
  TTreeReaderArray<Int_t> pspmthigh2_ahit = {fReader, "pspmthigh2.ahit[4]"};
  TTreeReaderValue<Int_t> pspmthigh2_hit = {fReader, "pspmthigh2.hit"};
  TTreeReaderValue<unsigned int> pspmtlow1_fUniqueID = {fReader, "pspmtlow1.fUniqueID"};
  TTreeReaderValue<unsigned int> pspmtlow1_fBits = {fReader, "pspmtlow1.fBits"};
  TTreeReaderValue<Double_t> pspmtlow1_dyenergy = {fReader, "pspmtlow1.dyenergy"};
  TTreeReaderValue<Double_t> pspmtlow1_dyecal = {fReader, "pspmtlow1.dyecal"};
  TTreeReaderValue<Double_t> pspmtlow1_dytime = {fReader, "pspmtlow1.dytime"};
  TTreeReaderValue<unsigned int> pspmtlow1_dytimecfd = {fReader, "pspmtlow1.dytimecfd"};
  TTreeReaderValue<Int_t> pspmtlow1_dycfdfailbit = {fReader, "pspmtlow1.dycfdfailbit"};
  TTreeReaderValue<Int_t> pspmtlow1_dyoverflow = {fReader, "pspmtlow1.dyoverflow"};
  TTreeReaderValue<Int_t> pspmtlow1_dymult = {fReader, "pspmtlow1.dymult"};
  TTreeReaderArray<Double_t> pspmtlow1_dyenergies = {fReader, "pspmtlow1.dyenergies[16]"};
  TTreeReaderArray<Double_t> pspmtlow1_dytimes = {fReader, "pspmtlow1.dytimes[16]"};
  TTreeReaderValue<Double_t> pspmtlow1_dychisq_single = {fReader, "pspmtlow1.dychisq_single"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1_single = {fReader, "pspmtlow1.dyE1_single"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1real_single = {fReader, "pspmtlow1.dyE1real_single"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1cal_single = {fReader, "pspmtlow1.dyE1cal_single"};
  TTreeReaderValue<Double_t> pspmtlow1_dyT1_single = {fReader, "pspmtlow1.dyT1_single"};
  TTreeReaderValue<Double_t> pspmtlow1_dyoffset_single = {fReader, "pspmtlow1.dyoffset_single"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1steepness_single = {fReader, "pspmtlow1.dyE1steepness_single"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1decay_single = {fReader, "pspmtlow1.dyE1decay_single"};
  TTreeReaderValue<Double_t> pspmtlow1_dychisq_double = {fReader, "pspmtlow1.dychisq_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1_double = {fReader, "pspmtlow1.dyE1_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1real_double = {fReader, "pspmtlow1.dyE1real_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1cal_double = {fReader, "pspmtlow1.dyE1cal_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyT1_double = {fReader, "pspmtlow1.dyT1_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1steepness_double = {fReader, "pspmtlow1.dyE1steepness_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1decay_double = {fReader, "pspmtlow1.dyE1decay_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE2_double = {fReader, "pspmtlow1.dyE2_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE2real_double = {fReader, "pspmtlow1.dyE2real_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE2cal_double = {fReader, "pspmtlow1.dyE2cal_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyT2_double = {fReader, "pspmtlow1.dyT2_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE2steepness_double = {fReader, "pspmtlow1.dyE2steepness_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE2decay_double = {fReader, "pspmtlow1.dyE2decay_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyoffset_double = {fReader, "pspmtlow1.dyoffset_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dytdiffE1E2 = {fReader, "pspmtlow1.dytdiffE1E2"};
  TTreeReaderValue<Double_t> pspmtlow1_dytdiffE1E2cal = {fReader, "pspmtlow1.dytdiffE1E2cal"};
  TTreeReaderArray<Double_t> pspmtlow1_aenergy = {fReader, "pspmtlow1.aenergy[4]"};
  TTreeReaderArray<Double_t> pspmtlow1_aecal = {fReader, "pspmtlow1.aecal[4]"};
  TTreeReaderArray<Double_t> pspmtlow1_aenergy_qdc = {fReader, "pspmtlow1.aenergy_qdc[4]"};
  TTreeReaderValue<Double_t> pspmtlow1_asum = {fReader, "pspmtlow1.asum"};
  TTreeReaderValue<Double_t> pspmtlow1_asum_qdc = {fReader, "pspmtlow1.asum_qdc"};
  TTreeReaderArray<Double_t> pspmtlow1_atime = {fReader, "pspmtlow1.atime[4]"};
  TTreeReaderArray<Double_t> pspmtlow1_atimecal = {fReader, "pspmtlow1.atimecal[4]"};
  TTreeReaderArray<Int_t> pspmtlow1_aoverflow = {fReader, "pspmtlow1.aoverflow[4]"};
  TTreeReaderValue<Int_t> pspmtlow1_aoverflowcount = {fReader, "pspmtlow1.aoverflowcount"};
  TTreeReaderValue<Int_t> pspmtlow1_amultraw = {fReader, "pspmtlow1.amultraw"};
  TTreeReaderValue<Int_t> pspmtlow1_amult = {fReader, "pspmtlow1.amult"};
  TTreeReaderArray<Int_t> pspmtlow1_pixelmult = {fReader, "pspmtlow1.pixelmult[4]"};
  TTreeReaderValue<Double_t> pspmtlow1_xpos = {fReader, "pspmtlow1.xpos"};
  TTreeReaderValue<Double_t> pspmtlow1_ypos = {fReader, "pspmtlow1.ypos"};
  TTreeReaderValue<Int_t> pspmtlow1_dyhit = {fReader, "pspmtlow1.dyhit"};
  TTreeReaderArray<Int_t> pspmtlow1_ahit = {fReader, "pspmtlow1.ahit[4]"};
  TTreeReaderValue<Int_t> pspmtlow1_hit = {fReader, "pspmtlow1.hit"};
  TTreeReaderValue<unsigned int> pspmtlow2_fUniqueID = {fReader, "pspmtlow2.fUniqueID"};
  TTreeReaderValue<unsigned int> pspmtlow2_fBits = {fReader, "pspmtlow2.fBits"};
  TTreeReaderValue<Double_t> pspmtlow2_dyenergy = {fReader, "pspmtlow2.dyenergy"};
  TTreeReaderValue<Double_t> pspmtlow2_dyecal = {fReader, "pspmtlow2.dyecal"};
  TTreeReaderValue<Double_t> pspmtlow2_dytime = {fReader, "pspmtlow2.dytime"};
  TTreeReaderValue<unsigned int> pspmtlow2_dytimecfd = {fReader, "pspmtlow2.dytimecfd"};
  TTreeReaderValue<Int_t> pspmtlow2_dycfdfailbit = {fReader, "pspmtlow2.dycfdfailbit"};
  TTreeReaderValue<Int_t> pspmtlow2_dyoverflow = {fReader, "pspmtlow2.dyoverflow"};
  TTreeReaderValue<Int_t> pspmtlow2_dymult = {fReader, "pspmtlow2.dymult"};
  TTreeReaderArray<Double_t> pspmtlow2_dyenergies = {fReader, "pspmtlow2.dyenergies[16]"};
  TTreeReaderArray<Double_t> pspmtlow2_dytimes = {fReader, "pspmtlow2.dytimes[16]"};
  TTreeReaderValue<Double_t> pspmtlow2_dychisq_single = {fReader, "pspmtlow2.dychisq_single"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1_single = {fReader, "pspmtlow2.dyE1_single"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1real_single = {fReader, "pspmtlow2.dyE1real_single"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1cal_single = {fReader, "pspmtlow2.dyE1cal_single"};
  TTreeReaderValue<Double_t> pspmtlow2_dyT1_single = {fReader, "pspmtlow2.dyT1_single"};
  TTreeReaderValue<Double_t> pspmtlow2_dyoffset_single = {fReader, "pspmtlow2.dyoffset_single"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1steepness_single = {fReader, "pspmtlow2.dyE1steepness_single"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1decay_single = {fReader, "pspmtlow2.dyE1decay_single"};
  TTreeReaderValue<Double_t> pspmtlow2_dychisq_double = {fReader, "pspmtlow2.dychisq_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1_double = {fReader, "pspmtlow2.dyE1_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1real_double = {fReader, "pspmtlow2.dyE1real_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1cal_double = {fReader, "pspmtlow2.dyE1cal_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyT1_double = {fReader, "pspmtlow2.dyT1_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1steepness_double = {fReader, "pspmtlow2.dyE1steepness_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1decay_double = {fReader, "pspmtlow2.dyE1decay_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE2_double = {fReader, "pspmtlow2.dyE2_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE2real_double = {fReader, "pspmtlow2.dyE2real_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE2cal_double = {fReader, "pspmtlow2.dyE2cal_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyT2_double = {fReader, "pspmtlow2.dyT2_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE2steepness_double = {fReader, "pspmtlow2.dyE2steepness_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE2decay_double = {fReader, "pspmtlow2.dyE2decay_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyoffset_double = {fReader, "pspmtlow2.dyoffset_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dytdiffE1E2 = {fReader, "pspmtlow2.dytdiffE1E2"};
  TTreeReaderValue<Double_t> pspmtlow2_dytdiffE1E2cal = {fReader, "pspmtlow2.dytdiffE1E2cal"};
  TTreeReaderArray<Double_t> pspmtlow2_aenergy = {fReader, "pspmtlow2.aenergy[4]"};
  TTreeReaderArray<Double_t> pspmtlow2_aecal = {fReader, "pspmtlow2.aecal[4]"};
  TTreeReaderArray<Double_t> pspmtlow2_aenergy_qdc = {fReader, "pspmtlow2.aenergy_qdc[4]"};
  TTreeReaderValue<Double_t> pspmtlow2_asum = {fReader, "pspmtlow2.asum"};
  TTreeReaderValue<Double_t> pspmtlow2_asum_qdc = {fReader, "pspmtlow2.asum_qdc"};
  TTreeReaderArray<Double_t> pspmtlow2_atime = {fReader, "pspmtlow2.atime[4]"};
  TTreeReaderArray<Double_t> pspmtlow2_atimecal = {fReader, "pspmtlow2.atimecal[4]"};
  TTreeReaderArray<Int_t> pspmtlow2_aoverflow = {fReader, "pspmtlow2.aoverflow[4]"};
  TTreeReaderValue<Int_t> pspmtlow2_aoverflowcount = {fReader, "pspmtlow2.aoverflowcount"};
  TTreeReaderValue<Int_t> pspmtlow2_amultraw = {fReader, "pspmtlow2.amultraw"};
  TTreeReaderValue<Int_t> pspmtlow2_amult = {fReader, "pspmtlow2.amult"};
  TTreeReaderArray<Int_t> pspmtlow2_pixelmult = {fReader, "pspmtlow2.pixelmult[4]"};
  TTreeReaderValue<Double_t> pspmtlow2_xpos = {fReader, "pspmtlow2.xpos"};
  TTreeReaderValue<Double_t> pspmtlow2_ypos = {fReader, "pspmtlow2.ypos"};
  TTreeReaderValue<Int_t> pspmtlow2_dyhit = {fReader, "pspmtlow2.dyhit"};
  TTreeReaderArray<Int_t> pspmtlow2_ahit = {fReader, "pspmtlow2.ahit[4]"};
  TTreeReaderValue<Int_t> pspmtlow2_hit = {fReader, "pspmtlow2.hit"};
  TTreeReaderValue<unsigned int> SIPMT_fUniqueID = {fReader, "SIPMT.fUniqueID"};
  TTreeReaderValue<unsigned int> SIPMT_fBits = {fReader, "SIPMT.fBits"};
  TTreeReaderValue<Double_t> SIPMT_energy = {fReader, "SIPMT.energy"};
  TTreeReaderValue<Double_t> SIPMT_ecal = {fReader, "SIPMT.ecal"};
  TTreeReaderValue<Double_t> SIPMT_time = {fReader, "SIPMT.time"};
  TTreeReaderValue<Int_t> SIPMT_hit = {fReader, "SIPMT.hit"};
  TTreeReaderValue<unsigned int> PIN01T_fUniqueID = {fReader, "PIN01T.fUniqueID"};
  TTreeReaderValue<unsigned int> PIN01T_fBits = {fReader, "PIN01T.fBits"};
  TTreeReaderValue<Double_t> PIN01T_energy = {fReader, "PIN01T.energy"};
  TTreeReaderValue<Double_t> PIN01T_ecal = {fReader, "PIN01T.ecal"};
  TTreeReaderValue<Double_t> PIN01T_time = {fReader, "PIN01T.time"};
  TTreeReaderValue<Int_t> PIN01T_hit = {fReader, "PIN01T.hit"};
  TTreeReaderValue<unsigned int> SCLT_fUniqueID = {fReader, "SCLT.fUniqueID"};
  TTreeReaderValue<unsigned int> SCLT_fBits = {fReader, "SCLT.fBits"};
  TTreeReaderValue<Double_t> SCLT_energy = {fReader, "SCLT.energy"};
  TTreeReaderValue<Double_t> SCLT_ecal = {fReader, "SCLT.ecal"};
  TTreeReaderValue<Double_t> SCLT_time = {fReader, "SCLT.time"};
  TTreeReaderValue<Int_t> SCLT_hit = {fReader, "SCLT.hit"};
  TTreeReaderValue<unsigned int> SCRT_fUniqueID = {fReader, "SCRT.fUniqueID"};
  TTreeReaderValue<unsigned int> SCRT_fBits = {fReader, "SCRT.fBits"};
  TTreeReaderValue<Double_t> SCRT_energy = {fReader, "SCRT.energy"};
  TTreeReaderValue<Double_t> SCRT_ecal = {fReader, "SCRT.ecal"};
  TTreeReaderValue<Double_t> SCRT_time = {fReader, "SCRT.time"};
  TTreeReaderValue<Int_t> SCRT_hit = {fReader, "SCRT.hit"};
  TTreeReaderValue<unsigned int> PPACUT_fUniqueID = {fReader, "PPACUT.fUniqueID"};
  TTreeReaderValue<unsigned int> PPACUT_fBits = {fReader, "PPACUT.fBits"};
  TTreeReaderValue<Double_t> PPACUT_energy = {fReader, "PPACUT.energy"};
  TTreeReaderValue<Double_t> PPACUT_ecal = {fReader, "PPACUT.ecal"};
  TTreeReaderValue<Double_t> PPACUT_time = {fReader, "PPACUT.time"};
  TTreeReaderValue<Int_t> PPACUT_hit = {fReader, "PPACUT.hit"};
  TTreeReaderValue<unsigned int> PPACDT_fUniqueID = {fReader, "PPACDT.fUniqueID"};
  TTreeReaderValue<unsigned int> PPACDT_fBits = {fReader, "PPACDT.fBits"};
  TTreeReaderValue<Double_t> PPACDT_energy = {fReader, "PPACDT.energy"};
  TTreeReaderValue<Double_t> PPACDT_ecal = {fReader, "PPACDT.ecal"};
  TTreeReaderValue<Double_t> PPACDT_time = {fReader, "PPACDT.time"};
  TTreeReaderValue<Int_t> PPACDT_hit = {fReader, "PPACDT.hit"};
  TTreeReaderValue<unsigned int> PPACLT_fUniqueID = {fReader, "PPACLT.fUniqueID"};
  TTreeReaderValue<unsigned int> PPACLT_fBits = {fReader, "PPACLT.fBits"};
  TTreeReaderValue<Double_t> PPACLT_energy = {fReader, "PPACLT.energy"};
  TTreeReaderValue<Double_t> PPACLT_ecal = {fReader, "PPACLT.ecal"};
  TTreeReaderValue<Double_t> PPACLT_time = {fReader, "PPACLT.time"};
  TTreeReaderValue<Int_t> PPACLT_hit = {fReader, "PPACLT.hit"};
  TTreeReaderValue<unsigned int> PPACRT_fUniqueID = {fReader, "PPACRT.fUniqueID"};
  TTreeReaderValue<unsigned int> PPACRT_fBits = {fReader, "PPACRT.fBits"};
  TTreeReaderValue<Double_t> PPACRT_energy = {fReader, "PPACRT.energy"};
  TTreeReaderValue<Double_t> PPACRT_ecal = {fReader, "PPACRT.ecal"};
  TTreeReaderValue<Double_t> PPACRT_time = {fReader, "PPACRT.time"};
  TTreeReaderValue<Int_t> PPACRT_hit = {fReader, "PPACRT.hit"};
  TTreeReaderValue<unsigned int> NPPACLT_fUniqueID = {fReader, "NPPACLT.fUniqueID"};
  TTreeReaderValue<unsigned int> NPPACLT_fBits = {fReader, "NPPACLT.fBits"};
  TTreeReaderValue<Double_t> NPPACLT_energy = {fReader, "NPPACLT.energy"};
  TTreeReaderValue<Double_t> NPPACLT_ecal = {fReader, "NPPACLT.ecal"};
  TTreeReaderValue<Double_t> NPPACLT_time = {fReader, "NPPACLT.time"};
  TTreeReaderValue<Int_t> NPPACLT_hit = {fReader, "NPPACLT.hit"};
  TTreeReaderValue<unsigned int> NPPACRT_fUniqueID = {fReader, "NPPACRT.fUniqueID"};
  TTreeReaderValue<unsigned int> NPPACRT_fBits = {fReader, "NPPACRT.fBits"};
  TTreeReaderValue<Double_t> NPPACRT_energy = {fReader, "NPPACRT.energy"};
  TTreeReaderValue<Double_t> NPPACRT_ecal = {fReader, "NPPACRT.ecal"};
  TTreeReaderValue<Double_t> NPPACRT_time = {fReader, "NPPACRT.time"};
  TTreeReaderValue<Int_t> NPPACRT_hit = {fReader, "NPPACRT.hit"};
  TTreeReaderValue<unsigned int> pin01_fUniqueID = {fReader, "pin01.fUniqueID"};
  TTreeReaderValue<unsigned int> pin01_fBits = {fReader, "pin01.fBits"};
  TTreeReaderValue<Double_t> pin01_energy = {fReader, "pin01.energy"};
  TTreeReaderValue<Double_t> pin01_ecal = {fReader, "pin01.ecal"};
  TTreeReaderValue<Double_t> pin01_time = {fReader, "pin01.time"};
  TTreeReaderValue<Int_t> pin01_hit = {fReader, "pin01.hit"};
  TTreeReaderValue<unsigned int> pin02_fUniqueID = {fReader, "pin02.fUniqueID"};
  TTreeReaderValue<unsigned int> pin02_fBits = {fReader, "pin02.fBits"};
  TTreeReaderValue<Double_t> pin02_energy = {fReader, "pin02.energy"};
  TTreeReaderValue<Double_t> pin02_ecal = {fReader, "pin02.ecal"};
  TTreeReaderValue<Double_t> pin02_time = {fReader, "pin02.time"};
  TTreeReaderValue<Int_t> pin02_hit = {fReader, "pin02.hit"};
  TTreeReaderValue<unsigned int> sipm_fUniqueID = {fReader, "sipm.fUniqueID"};
  TTreeReaderValue<unsigned int> sipm_fBits = {fReader, "sipm.fBits"};
  TTreeReaderValue<Double_t> sipm_energy = {fReader, "sipm.energy"};
  TTreeReaderValue<Double_t> sipm_ecal = {fReader, "sipm.ecal"};
  TTreeReaderValue<Double_t> sipm_time = {fReader, "sipm.time"};
  TTreeReaderValue<Int_t> sipm_hit = {fReader, "sipm.hit"};
  TTreeReaderValue<unsigned int> xscintB_fUniqueID = {fReader, "xscintB.fUniqueID"};
  TTreeReaderValue<unsigned int> xscintB_fBits = {fReader, "xscintB.fBits"};
  TTreeReaderValue<Double_t> xscintB_energy = {fReader, "xscintB.energy"};
  TTreeReaderValue<Double_t> xscintB_ecal = {fReader, "xscintB.ecal"};
  TTreeReaderValue<Double_t> xscintB_time = {fReader, "xscintB.time"};
  TTreeReaderValue<Int_t> xscintB_hit = {fReader, "xscintB.hit"};
  TTreeReaderValue<unsigned int> xscintT_fUniqueID = {fReader, "xscintT.fUniqueID"};
  TTreeReaderValue<unsigned int> xscintT_fBits = {fReader, "xscintT.fBits"};
  TTreeReaderValue<Double_t> xscintT_energy = {fReader, "xscintT.energy"};
  TTreeReaderValue<Double_t> xscintT_ecal = {fReader, "xscintT.ecal"};
  TTreeReaderValue<Double_t> xscintT_time = {fReader, "xscintT.time"};
  TTreeReaderValue<Int_t> xscintT_hit = {fReader, "xscintT.hit"};
  TTreeReaderValue<unsigned int> xpin1_fUniqueID = {fReader, "xpin1.fUniqueID"};
  TTreeReaderValue<unsigned int> xpin1_fBits = {fReader, "xpin1.fBits"};
  TTreeReaderValue<Double_t> xpin1_energy = {fReader, "xpin1.energy"};
  TTreeReaderValue<Double_t> xpin1_ecal = {fReader, "xpin1.ecal"};
  TTreeReaderValue<Double_t> xpin1_time = {fReader, "xpin1.time"};
  TTreeReaderValue<Int_t> xpin1_hit = {fReader, "xpin1.hit"};
  TTreeReaderValue<unsigned int> xpin2_fUniqueID = {fReader, "xpin2.fUniqueID"};
  TTreeReaderValue<unsigned int> xpin2_fBits = {fReader, "xpin2.fBits"};
  TTreeReaderValue<Double_t> xpin2_energy = {fReader, "xpin2.energy"};
  TTreeReaderValue<Double_t> xpin2_ecal = {fReader, "xpin2.ecal"};
  TTreeReaderValue<Double_t> xpin2_time = {fReader, "xpin2.time"};
  TTreeReaderValue<Int_t> xpin2_hit = {fReader, "xpin2.hit"};
  TTreeReaderValue<unsigned int> vetoR_fUniqueID = {fReader, "vetoR.fUniqueID"};
  TTreeReaderValue<unsigned int> vetoR_fBits = {fReader, "vetoR.fBits"};
  TTreeReaderValue<Double_t> vetoR_energy = {fReader, "vetoR.energy"};
  TTreeReaderValue<Double_t> vetoR_ecal = {fReader, "vetoR.ecal"};
  TTreeReaderValue<Double_t> vetoR_time = {fReader, "vetoR.time"};
  TTreeReaderValue<Int_t> vetoR_hit = {fReader, "vetoR.hit"};
  TTreeReaderValue<unsigned int> vetoF_fUniqueID = {fReader, "vetoF.fUniqueID"};
  TTreeReaderValue<unsigned int> vetoF_fBits = {fReader, "vetoF.fBits"};
  TTreeReaderValue<Double_t> vetoF_energy = {fReader, "vetoF.energy"};
  TTreeReaderValue<Double_t> vetoF_ecal = {fReader, "vetoF.ecal"};
  TTreeReaderValue<Double_t> vetoF_time = {fReader, "vetoF.time"};
  TTreeReaderValue<Int_t> vetoF_hit = {fReader, "vetoF.hit"};
  TTreeReaderValue<unsigned int> tacP1SL_fUniqueID = {fReader, "tacP1SL.fUniqueID"};
  TTreeReaderValue<unsigned int> tacP1SL_fBits = {fReader, "tacP1SL.fBits"};
  TTreeReaderValue<Double_t> tacP1SL_energy = {fReader, "tacP1SL.energy"};
  TTreeReaderValue<Double_t> tacP1SL_time = {fReader, "tacP1SL.time"};
  TTreeReaderValue<Double_t> tacP1SL_hit = {fReader, "tacP1SL.hit"};
  TTreeReaderValue<unsigned int> tacSIPMSL_fUniqueID = {fReader, "tacSIPMSL.fUniqueID"};
  TTreeReaderValue<unsigned int> tacSIPMSL_fBits = {fReader, "tacSIPMSL.fBits"};
  TTreeReaderValue<Double_t> tacSIPMSL_energy = {fReader, "tacSIPMSL.energy"};
  TTreeReaderValue<Double_t> tacSIPMSL_time = {fReader, "tacSIPMSL.time"};
  TTreeReaderValue<Double_t> tacSIPMSL_hit = {fReader, "tacSIPMSL.hit"};
  TTreeReaderValue<unsigned int> tacPPACUD_fUniqueID = {fReader, "tacPPACUD.fUniqueID"};
  TTreeReaderValue<unsigned int> tacPPACUD_fBits = {fReader, "tacPPACUD.fBits"};
  TTreeReaderValue<Double_t> tacPPACUD_energy = {fReader, "tacPPACUD.energy"};
  TTreeReaderValue<Double_t> tacPPACUD_time = {fReader, "tacPPACUD.time"};
  TTreeReaderValue<Double_t> tacPPACUD_hit = {fReader, "tacPPACUD.hit"};
  TTreeReaderValue<unsigned int> tacPPACLR_fUniqueID = {fReader, "tacPPACLR.fUniqueID"};
  TTreeReaderValue<unsigned int> tacPPACLR_fBits = {fReader, "tacPPACLR.fBits"};
  TTreeReaderValue<Double_t> tacPPACLR_energy = {fReader, "tacPPACLR.energy"};
  TTreeReaderValue<Double_t> tacPPACLR_time = {fReader, "tacPPACLR.time"};
  TTreeReaderValue<Double_t> tacPPACLR_hit = {fReader, "tacPPACLR.hit"};
  TTreeReaderValue<unsigned int> NtacPPACLR_fUniqueID = {fReader, "NtacPPACLR.fUniqueID"};
  TTreeReaderValue<unsigned int> NtacPPACLR_fBits = {fReader, "NtacPPACLR.fBits"};
  TTreeReaderValue<Double_t> NtacPPACLR_energy = {fReader, "NtacPPACLR.energy"};
  TTreeReaderValue<Double_t> NtacPPACLR_time = {fReader, "NtacPPACLR.time"};
  TTreeReaderValue<Double_t> NtacPPACLR_hit = {fReader, "NtacPPACLR.hit"};
  TTreeReaderValue<unsigned int> pid_fUniqueID = {fReader, "pid.fUniqueID"};
  TTreeReaderValue<unsigned int> pid_fBits = {fReader, "pid.fBits"};
  TTreeReaderValue<Double_t> pid_de1 = {fReader, "pid.de1"};
  TTreeReaderValue<Double_t> pid_de2 = {fReader, "pid.de2"};
  TTreeReaderValue<Double_t> pid_tof = {fReader, "pid.tof"};
  TTreeReaderValue<Double_t> pid_scintScintTOF = {fReader, "pid.scintScintTOF"};
  TTreeReaderValue<Double_t> pid_tof_pin01i2n = {fReader, "pid.tof_pin01i2n"};
  TTreeReaderValue<Double_t> pid_tof_pin01i2s = {fReader, "pid.tof_pin01i2s"};
  TTreeReaderValue<Double_t> pid_tof_pin02i2n = {fReader, "pid.tof_pin02i2n"};
  TTreeReaderValue<Double_t> pid_tof_pin02i2s = {fReader, "pid.tof_pin02i2s"};
  TTreeReaderValue<Double_t> pid_tof_pin01xfp = {fReader, "pid.tof_pin01xfp"};
  TTreeReaderValue<Double_t> pid_tof_pin02xfp = {fReader, "pid.tof_pin02xfp"};
  TTreeReaderValue<Double_t> pid_tof_pin01rf = {fReader, "pid.tof_pin01rf"};
  TTreeReaderValue<Double_t> pid_time = {fReader, "pid.time"};
  TTreeReaderValue<Int_t> pid_xpos = {fReader, "pid.xpos"};
  TTreeReaderValue<Int_t> pid_ypos = {fReader, "pid.ypos"};
  TTreeReaderValue<unsigned int> corr_fUniqueID = {fReader, "corr.fUniqueID"};
  TTreeReaderValue<unsigned int> corr_fBits = {fReader, "corr.fBits"};
  TTreeReaderValue<Double_t> corr_idyecal = {fReader, "corr.idyecal"};
  TTreeReaderValue<Double_t> corr_itime = {fReader, "corr.itime"};
  TTreeReaderValue<Double_t> corr_ide1 = {fReader, "corr.ide1"};
  TTreeReaderValue<Double_t> corr_ide2 = {fReader, "corr.ide2"};
  TTreeReaderValue<Double_t> corr_itof = {fReader, "corr.itof"};
  TTreeReaderValue<Double_t> corr_itofpin01i2n = {fReader, "corr.itofpin01i2n"};
  TTreeReaderValue<Double_t> corr_itofpin01i2s = {fReader, "corr.itofpin01i2s"};
  TTreeReaderValue<Double_t> corr_itofpin02i2n = {fReader, "corr.itofpin02i2n"};
  TTreeReaderValue<Double_t> corr_itofpin02i2s = {fReader, "corr.itofpin02i2s"};
  TTreeReaderValue<Double_t> corr_itofpin01xfp = {fReader, "corr.itofpin01xfp"};
  TTreeReaderValue<Double_t> corr_itofpin02xfp = {fReader, "corr.itofpin02xfp"};
  TTreeReaderValue<Double_t> corr_itofpin01rf = {fReader, "corr.itofpin01rf"};
  TTreeReaderValue<Double_t> corr_dtimplant = {fReader, "corr.dtimplant"};
  TTreeReaderValue<Double_t> corr_ixpos = {fReader, "corr.ixpos"};
  TTreeReaderValue<Double_t> corr_iypos = {fReader, "corr.iypos"};
  TTreeReaderValue<Double_t> corr_idychisq_single = {fReader, "corr.idychisq_single"};
  TTreeReaderValue<Double_t> corr_idyE1real_single = {fReader, "corr.idyE1real_single"};
  TTreeReaderValue<Double_t> corr_idyE1cal_single = {fReader, "corr.idyE1cal_single"};
  TTreeReaderValue<Double_t> corr_idyT1_single = {fReader, "corr.idyT1_single"};
  TTreeReaderValue<Double_t> corr_idyE1steepness_single = {fReader, "corr.idyE1steepness_single"};
  TTreeReaderValue<Double_t> corr_idyE1decay_single = {fReader, "corr.idyE1decay_single"};
  TTreeReaderValue<Double_t> corr_idychisq_double = {fReader, "corr.idychisq_double"};
  TTreeReaderValue<Double_t> corr_idyE1real_double = {fReader, "corr.idyE1real_double"};
  TTreeReaderValue<Double_t> corr_idyE1cal_double = {fReader, "corr.idyE1cal_double"};
  TTreeReaderValue<Double_t> corr_idyE1steepness_double = {fReader, "corr.idyE1steepness_double"};
  TTreeReaderValue<Double_t> corr_idyE1decay_double = {fReader, "corr.idyE1decay_double"};
  TTreeReaderValue<Double_t> corr_idyT1_double = {fReader, "corr.idyT1_double"};
  TTreeReaderValue<Double_t> corr_idyE2real_double = {fReader, "corr.idyE2real_double"};
  TTreeReaderValue<Double_t> corr_idyE2cal_double = {fReader, "corr.idyE2cal_double"};
  TTreeReaderValue<Double_t> corr_idyE2steepness_double = {fReader, "corr.idyE2steepness_double"};
  TTreeReaderValue<Double_t> corr_idyE2decay_double = {fReader, "corr.idyE2decay_double"};
  TTreeReaderValue<Double_t> corr_idyT2_double = {fReader, "corr.idyT2_double"};
  TTreeReaderValue<Double_t> corr_idytdiffE1E2cal = {fReader, "corr.idytdiffE1E2cal"};
  TTreeReaderValue<Double_t> corr_ddyecal = {fReader, "corr.ddyecal"};
  TTreeReaderValue<Double_t> corr_dtime = {fReader, "corr.dtime"};
  TTreeReaderValue<Double_t> corr_dxpos = {fReader, "corr.dxpos"};
  TTreeReaderValue<Double_t> corr_dypos = {fReader, "corr.dypos"};
  TTreeReaderValue<Double_t> corr_ddychisq_single = {fReader, "corr.ddychisq_single"};
  TTreeReaderValue<Double_t> corr_ddyE1real_single = {fReader, "corr.ddyE1real_single"};
  TTreeReaderValue<Double_t> corr_ddyE1cal_single = {fReader, "corr.ddyE1cal_single"};
  TTreeReaderValue<Double_t> corr_ddyT1_single = {fReader, "corr.ddyT1_single"};
  TTreeReaderValue<Double_t> corr_ddyE1steepness_single = {fReader, "corr.ddyE1steepness_single"};
  TTreeReaderValue<Double_t> corr_ddyE1decay_single = {fReader, "corr.ddyE1decay_single"};
  TTreeReaderValue<Double_t> corr_ddychisq_double = {fReader, "corr.ddychisq_double"};
  TTreeReaderValue<Double_t> corr_ddyE1real_double = {fReader, "corr.ddyE1real_double"};
  TTreeReaderValue<Double_t> corr_ddyE1cal_double = {fReader, "corr.ddyE1cal_double"};
  TTreeReaderValue<Double_t> corr_ddyE1steepness_double = {fReader, "corr.ddyE1steepness_double"};
  TTreeReaderValue<Double_t> corr_ddyE1decay_double = {fReader, "corr.ddyE1decay_double"};
  TTreeReaderValue<Double_t> corr_ddyT1_double = {fReader, "corr.ddyT1_double"};
  TTreeReaderValue<Double_t> corr_ddyE2real_double = {fReader, "corr.ddyE2real_double"};
  TTreeReaderValue<Double_t> corr_ddyE2cal_double = {fReader, "corr.ddyE2cal_double"};
  TTreeReaderValue<Double_t> corr_ddyE2steepness_double = {fReader, "corr.ddyE2steepness_double"};
  TTreeReaderValue<Double_t> corr_ddyE2decay_double = {fReader, "corr.ddyE2decay_double"};
  TTreeReaderValue<Double_t> corr_ddyT2_double = {fReader, "corr.ddyT2_double"};
  TTreeReaderValue<Double_t> corr_ddytdiffE1E2cal = {fReader, "corr.ddytdiffE1E2cal"};
  TTreeReaderValue<Int_t> corr_ifrontch = {fReader, "corr.ifrontch"};
  TTreeReaderValue<Int_t> corr_ibackch = {fReader, "corr.ibackch"};
  TTreeReaderValue<Int_t> corr_ddfrontch = {fReader, "corr.ddfrontch"};
  TTreeReaderValue<Int_t> corr_ddbackch = {fReader, "corr.ddbackch"};
  TTreeReaderValue<Int_t> corr_flag = {fReader, "corr.flag"};
  TTreeReaderValue<Int_t> corr_isdecay = {fReader, "corr.isdecay"};
  TTreeReaderValue<Int_t> corr_isimplant = {fReader, "corr.isimplant"};
  TTreeReaderValue<Int_t> corr_islightion = {fReader, "corr.islightion"};
  TTreeReaderValue<Int_t> corr_isdynovflnopins = {fReader, "corr.isdynovflnopins"};
  TTreeReaderValue<unsigned int> clover_fUniqueID = {fReader, "clover.fUniqueID"};
  TTreeReaderValue<unsigned int> clover_fBits = {fReader, "clover.fBits"};
  TTreeReaderArray<Double_t> clover_time = {fReader, "clover.time[52]"};
  TTreeReaderArray<unsigned int> clover_timecfd = {fReader, "clover.timecfd[52]"};
  TTreeReaderArray<Int_t> clover_cfdfailbit = {fReader, "clover.cfdfailbit[52]"};
  TTreeReaderArray<Double_t> clover_timecal = {fReader, "clover.timecal[52]"};
  TTreeReaderArray<Double_t> clover_energy = {fReader, "clover.energy[52]"};
  TTreeReaderArray<Double_t> clover_ecal = {fReader, "clover.ecal[52]"};
  TTreeReaderValue<Int_t> clover_mult = {fReader, "clover.mult"};
  TTreeReaderArray<Double_t> clover_timeab = {fReader, "clover.timeab[13]"};
  TTreeReaderArray<Double_t> clover_timecalab = {fReader, "clover.timecalab[13]"};
  TTreeReaderArray<Int_t> clover_cfdfailbitab = {fReader, "clover.cfdfailbitab[13]"};
  TTreeReaderArray<Double_t> clover_ecalab = {fReader, "clover.ecalab[13]"};
  TTreeReaderArray<Int_t> clover_posmult = {fReader, "clover.posmult[13]"};
  TTreeReaderValue<Int_t> clover_multab = {fReader, "clover.multab"};
  TTreeReaderValue<Int_t> clover_hit = {fReader, "clover.hit"};
  TTreeReaderValue<unsigned int> labr_fUniqueID = {fReader, "labr.fUniqueID"};
  TTreeReaderValue<unsigned int> labr_fBits = {fReader, "labr.fBits"};
  TTreeReaderArray<Double_t> labr_energy = {fReader, "labr.energy[15]"};
  TTreeReaderArray<Double_t> labr_ecal = {fReader, "labr.ecal[15]"};
  TTreeReaderArray<Double_t> labr_time = {fReader, "labr.time[15]"};
  TTreeReaderArray<unsigned int> labr_timecfd = {fReader, "labr.timecfd[15]"};
  TTreeReaderArray<Int_t> labr_cfdfailbit = {fReader, "labr.cfdfailbit[15]"};
  TTreeReaderArray<Double_t> labr_timecal = {fReader, "labr.timecal[15]"};
  TTreeReaderValue<Int_t> labr_mult = {fReader, "labr.mult"};
  TTreeReaderValue<Int_t> labr_hit = {fReader, "labr.hit"};
  /* TTreeReaderArray<unsigned int> implantlist_fUniqueID = {fReader, "implantlist.fUniqueID"}; */
  /* TTreeReaderArray<unsigned int> implantlist_fBits = {fReader, "implantlist.fBits"}; */
  /* TTreeReaderArray<Double_t> implantlist_de1 = {fReader, "implantlist.de1"}; */
  /* TTreeReaderArray<Double_t> implantlist_de2 = {fReader, "implantlist.de2"}; */
  /* TTreeReaderArray<Double_t> implantlist_tof = {fReader, "implantlist.tof"}; */
  /* TTreeReaderArray<Double_t> implantlist_scintScintTOF = {fReader, "implantlist.scintScintTOF"}; */
  /* TTreeReaderArray<Double_t> implantlist_tof_pin01i2n = {fReader, "implantlist.tof_pin01i2n"}; */
  /* TTreeReaderArray<Double_t> implantlist_tof_pin01i2s = {fReader, "implantlist.tof_pin01i2s"}; */
  /* TTreeReaderArray<Double_t> implantlist_tof_pin02i2n = {fReader, "implantlist.tof_pin02i2n"}; */
  /* TTreeReaderArray<Double_t> implantlist_tof_pin02i2s = {fReader, "implantlist.tof_pin02i2s"}; */
  /* TTreeReaderArray<Double_t> implantlist_tof_pin01xfp = {fReader, "implantlist.tof_pin01xfp"}; */
  /* TTreeReaderArray<Double_t> implantlist_tof_pin02xfp = {fReader, "implantlist.tof_pin02xfp"}; */
  /* TTreeReaderArray<Double_t> implantlist_tof_pin01rf = {fReader, "implantlist.tof_pin01rf"}; */
  /* TTreeReaderArray<Double_t> implantlist_time = {fReader, "implantlist.time"}; */
  /* TTreeReaderArray<Int_t> implantlist_xpos = {fReader, "implantlist.xpos"}; */
  /* TTreeReaderArray<Int_t> implantlist_ypos = {fReader, "implantlist.ypos"}; */

  TTreeReaderValue<std::vector<TPID>> implantlist = {fReader,"implantlist"}; 





 
  test1(TTree * /*tree*/ =0) { }
  virtual ~test1() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();


  void MakeOutput(const char *objname) {
    if(fOutput->FindObject(objname)) {
      fOutput->FindObject(objname)->Write();
    } else {
      printf("CANNOT FIND THIS FILE! \n");
    }
  }
  void MakeTH1DOutput(const char *objname) {
    if(fOutput->FindObject(objname)
       && ((TH1D*)fOutput->FindObject(objname))->Integral() > 0) {
      fOutput->FindObject(objname)->Write();
    } 
  }




   
  ClassDef(test1,0);

};

#endif

#ifdef test1_cxx
void test1::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the reader is initialized.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  fReader.SetTree(tree);
}

Bool_t test1::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}


#endif // #ifdef test1_cxx
