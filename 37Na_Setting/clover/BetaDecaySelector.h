//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Apr  1 16:35:39 2024 by ROOT version 6.28/04
// from TTree data/data
// found on file: /mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resortedNewCal37Na/run-1420-sorted.root
//////////////////////////////////////////////////////////

#ifndef BetaDecaySelector_h
#define BetaDecaySelector_h

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
#include "/projects/e21062/Offline-Analysis/rootAnalysis/include/TPID.h"

class BetaDecaySelector : public TSelector {
public :
  TTreeReader     fReader;  //!the tree reader
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain


  TH1D *h1Clover32NaAll=nullptr;
  TH2D *h2Clover32NaAll=nullptr;
  TH1D *h1Clover32NaAll_AB=nullptr;
  TH2D *h2Clover32NaAll_AB=nullptr;
  TH2D *h2E_Vs_id_AB=nullptr;
  TH2D *h2E_Vs_id=nullptr;
  TH2D *clover_Vs_time=nullptr;
  TH2D *clover_Vs_time_ab=nullptr;
  TH2D *position_37=nullptr;
  TH2D *position_33=nullptr;
  TH2D *radius_37=nullptr;
  TH2D *radius_33=nullptr;
  TCutG* iongates_37=nullptr;
  TCutG* iongates_33=nullptr;
  TH1D* hIonDecayTime_35Na=nullptr;
  TH1D* hIonDecayTime_34Na=nullptr;

  TCutG* iongates_35=nullptr;
  TCutG* iongates_34=nullptr;
  
   TCutG* iongates_decay_37=nullptr;
  TCutG* iongates_decay_33=nullptr;
public:
  TCutG *cut;

 public:
  TH2D *Position_Vs_hIonDecayTime_37Na;
 TH2D *Position_Vs_hIonDecayTime_33Na;
  TH2D* PIDhist=nullptr;
  
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
  TTreeReaderArray<unsigned short> pspmthigh1_dytrace = {fReader, "pspmthigh1.dytrace"};
  TTreeReaderArray<double> pspmthigh1_dyenergy = {fReader, "pspmthigh1.dyenergy"};
  TTreeReaderArray<double> pspmthigh1_dyecal = {fReader, "pspmthigh1.dyecal"};
  TTreeReaderArray<double> pspmthigh1_dytime = {fReader, "pspmthigh1.dytime"};
  TTreeReaderValue<unsigned int> pspmthigh1_dytimecfd = {fReader, "pspmthigh1.dytimecfd"};
  TTreeReaderValue<Int_t> pspmthigh1_dycfdfailbit = {fReader, "pspmthigh1.dycfdfailbit"};
  TTreeReaderValue<Int_t> pspmthigh1_dyoverflow = {fReader, "pspmthigh1.dyoverflow"};
  TTreeReaderValue<Int_t> pspmthigh1_dymult = {fReader, "pspmthigh1.dymult"};
  TTreeReaderArray<Double_t> pspmthigh1_dyenergies = {fReader, "pspmthigh1.dyenergies[16]"};
  TTreeReaderArray<Double_t> pspmthigh1_dytimes = {fReader, "pspmthigh1.dytimes[16]"};
  TTreeReaderArray<double> pspmthigh1_dychisq_single = {fReader, "pspmthigh1.dychisq_single"};
  TTreeReaderArray<double> pspmthigh1_dyE1_single = {fReader, "pspmthigh1.dyE1_single"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1real_single = {fReader, "pspmthigh1.dyE1real_single"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1cal_single = {fReader, "pspmthigh1.dyE1cal_single"};
  TTreeReaderArray<double> pspmthigh1_dyT1_single = {fReader, "pspmthigh1.dyT1_single"};
  TTreeReaderArray<double> pspmthigh1_dyoffset_single = {fReader, "pspmthigh1.dyoffset_single"};
  TTreeReaderArray<double> pspmthigh1_dyE1steepness_single = {fReader, "pspmthigh1.dyE1steepness_single"};
  TTreeReaderArray<double> pspmthigh1_dyE1decay_single = {fReader, "pspmthigh1.dyE1decay_single"};
  TTreeReaderArray<double> pspmthigh1_dychisq_double = {fReader, "pspmthigh1.dychisq_double"};
  TTreeReaderArray<double> pspmthigh1_dyE1_double = {fReader, "pspmthigh1.dyE1_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1real_double = {fReader, "pspmthigh1.dyE1real_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE1cal_double = {fReader, "pspmthigh1.dyE1cal_double"};
  TTreeReaderArray<double> pspmthigh1_dyT1_double = {fReader, "pspmthigh1.dyT1_double"};
  TTreeReaderArray<double> pspmthigh1_dyE1steepness_double = {fReader, "pspmthigh1.dyE1steepness_double"};
  TTreeReaderArray<double> pspmthigh1_dyE1decay_double = {fReader, "pspmthigh1.dyE1decay_double"};
  TTreeReaderArray<double> pspmthigh1_dyE2_double = {fReader, "pspmthigh1.dyE2_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE2real_double = {fReader, "pspmthigh1.dyE2real_double"};
  TTreeReaderValue<Double_t> pspmthigh1_dyE2cal_double = {fReader, "pspmthigh1.dyE2cal_double"};
  TTreeReaderArray<double> pspmthigh1_dyT2_double = {fReader, "pspmthigh1.dyT2_double"};
  TTreeReaderArray<double> pspmthigh1_dyE2steepness_double = {fReader, "pspmthigh1.dyE2steepness_double"};
  TTreeReaderArray<double> pspmthigh1_dyE2decay_double = {fReader, "pspmthigh1.dyE2decay_double"};
  TTreeReaderArray<double> pspmthigh1_dyoffset_double = {fReader, "pspmthigh1.dyoffset_double"};
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
  TTreeReaderArray<unsigned short> pspmthigh2_dytrace = {fReader, "pspmthigh2.dytrace"};
  TTreeReaderArray<double> pspmthigh2_dyenergy = {fReader, "pspmthigh2.dyenergy"};
  TTreeReaderArray<double> pspmthigh2_dyecal = {fReader, "pspmthigh2.dyecal"};
  TTreeReaderArray<double> pspmthigh2_dytime = {fReader, "pspmthigh2.dytime"};
  TTreeReaderValue<unsigned int> pspmthigh2_dytimecfd = {fReader, "pspmthigh2.dytimecfd"};
  TTreeReaderValue<Int_t> pspmthigh2_dycfdfailbit = {fReader, "pspmthigh2.dycfdfailbit"};
  TTreeReaderValue<Int_t> pspmthigh2_dyoverflow = {fReader, "pspmthigh2.dyoverflow"};
  TTreeReaderValue<Int_t> pspmthigh2_dymult = {fReader, "pspmthigh2.dymult"};
  TTreeReaderArray<Double_t> pspmthigh2_dyenergies = {fReader, "pspmthigh2.dyenergies[16]"};
  TTreeReaderArray<Double_t> pspmthigh2_dytimes = {fReader, "pspmthigh2.dytimes[16]"};
  TTreeReaderArray<double> pspmthigh2_dychisq_single = {fReader, "pspmthigh2.dychisq_single"};
  TTreeReaderArray<double> pspmthigh2_dyE1_single = {fReader, "pspmthigh2.dyE1_single"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1real_single = {fReader, "pspmthigh2.dyE1real_single"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1cal_single = {fReader, "pspmthigh2.dyE1cal_single"};
  TTreeReaderArray<double> pspmthigh2_dyT1_single = {fReader, "pspmthigh2.dyT1_single"};
  TTreeReaderArray<double> pspmthigh2_dyoffset_single = {fReader, "pspmthigh2.dyoffset_single"};
  TTreeReaderArray<double> pspmthigh2_dyE1steepness_single = {fReader, "pspmthigh2.dyE1steepness_single"};
  TTreeReaderArray<double> pspmthigh2_dyE1decay_single = {fReader, "pspmthigh2.dyE1decay_single"};
  TTreeReaderArray<double> pspmthigh2_dychisq_double = {fReader, "pspmthigh2.dychisq_double"};
  TTreeReaderArray<double> pspmthigh2_dyE1_double = {fReader, "pspmthigh2.dyE1_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1real_double = {fReader, "pspmthigh2.dyE1real_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE1cal_double = {fReader, "pspmthigh2.dyE1cal_double"};
  TTreeReaderArray<double> pspmthigh2_dyT1_double = {fReader, "pspmthigh2.dyT1_double"};
  TTreeReaderArray<double> pspmthigh2_dyE1steepness_double = {fReader, "pspmthigh2.dyE1steepness_double"};
  TTreeReaderArray<double> pspmthigh2_dyE1decay_double = {fReader, "pspmthigh2.dyE1decay_double"};
  TTreeReaderArray<double> pspmthigh2_dyE2_double = {fReader, "pspmthigh2.dyE2_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE2real_double = {fReader, "pspmthigh2.dyE2real_double"};
  TTreeReaderValue<Double_t> pspmthigh2_dyE2cal_double = {fReader, "pspmthigh2.dyE2cal_double"};
  TTreeReaderArray<double> pspmthigh2_dyT2_double = {fReader, "pspmthigh2.dyT2_double"};
  TTreeReaderArray<double> pspmthigh2_dyE2steepness_double = {fReader, "pspmthigh2.dyE2steepness_double"};
  TTreeReaderArray<double> pspmthigh2_dyE2decay_double = {fReader, "pspmthigh2.dyE2decay_double"};
  TTreeReaderArray<double> pspmthigh2_dyoffset_double = {fReader, "pspmthigh2.dyoffset_double"};
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
  TTreeReaderArray<unsigned short> pspmtlow1_dytrace = {fReader, "pspmtlow1.dytrace"};
  TTreeReaderArray<double> pspmtlow1_dyenergy = {fReader, "pspmtlow1.dyenergy"};
  TTreeReaderArray<double> pspmtlow1_dyecal = {fReader, "pspmtlow1.dyecal"};
  TTreeReaderArray<double> pspmtlow1_dytime = {fReader, "pspmtlow1.dytime"};
  TTreeReaderValue<unsigned int> pspmtlow1_dytimecfd = {fReader, "pspmtlow1.dytimecfd"};
  TTreeReaderValue<Int_t> pspmtlow1_dycfdfailbit = {fReader, "pspmtlow1.dycfdfailbit"};
  TTreeReaderValue<Int_t> pspmtlow1_dyoverflow = {fReader, "pspmtlow1.dyoverflow"};
  TTreeReaderValue<Int_t> pspmtlow1_dymult = {fReader, "pspmtlow1.dymult"};
  TTreeReaderArray<Double_t> pspmtlow1_dyenergies = {fReader, "pspmtlow1.dyenergies[16]"};
  TTreeReaderArray<Double_t> pspmtlow1_dytimes = {fReader, "pspmtlow1.dytimes[16]"};
  TTreeReaderArray<double> pspmtlow1_dychisq_single = {fReader, "pspmtlow1.dychisq_single"};
  TTreeReaderArray<double> pspmtlow1_dyE1_single = {fReader, "pspmtlow1.dyE1_single"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1real_single = {fReader, "pspmtlow1.dyE1real_single"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1cal_single = {fReader, "pspmtlow1.dyE1cal_single"};
  TTreeReaderArray<double> pspmtlow1_dyT1_single = {fReader, "pspmtlow1.dyT1_single"};
  TTreeReaderArray<double> pspmtlow1_dyoffset_single = {fReader, "pspmtlow1.dyoffset_single"};
  TTreeReaderArray<double> pspmtlow1_dyE1steepness_single = {fReader, "pspmtlow1.dyE1steepness_single"};
  TTreeReaderArray<double> pspmtlow1_dyE1decay_single = {fReader, "pspmtlow1.dyE1decay_single"};
  TTreeReaderArray<double> pspmtlow1_dychisq_double = {fReader, "pspmtlow1.dychisq_double"};
  TTreeReaderArray<double> pspmtlow1_dyE1_double = {fReader, "pspmtlow1.dyE1_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1real_double = {fReader, "pspmtlow1.dyE1real_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE1cal_double = {fReader, "pspmtlow1.dyE1cal_double"};
  TTreeReaderArray<double> pspmtlow1_dyT1_double = {fReader, "pspmtlow1.dyT1_double"};
  TTreeReaderArray<double> pspmtlow1_dyE1steepness_double = {fReader, "pspmtlow1.dyE1steepness_double"};
  TTreeReaderArray<double> pspmtlow1_dyE1decay_double = {fReader, "pspmtlow1.dyE1decay_double"};
  TTreeReaderArray<double> pspmtlow1_dyE2_double = {fReader, "pspmtlow1.dyE2_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE2real_double = {fReader, "pspmtlow1.dyE2real_double"};
  TTreeReaderValue<Double_t> pspmtlow1_dyE2cal_double = {fReader, "pspmtlow1.dyE2cal_double"};
  TTreeReaderArray<double> pspmtlow1_dyT2_double = {fReader, "pspmtlow1.dyT2_double"};
  TTreeReaderArray<double> pspmtlow1_dyE2steepness_double = {fReader, "pspmtlow1.dyE2steepness_double"};
  TTreeReaderArray<double> pspmtlow1_dyE2decay_double = {fReader, "pspmtlow1.dyE2decay_double"};
  TTreeReaderArray<double> pspmtlow1_dyoffset_double = {fReader, "pspmtlow1.dyoffset_double"};
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
  TTreeReaderArray<unsigned short> pspmtlow2_dytrace = {fReader, "pspmtlow2.dytrace"};
  TTreeReaderArray<double> pspmtlow2_dyenergy = {fReader, "pspmtlow2.dyenergy"};
  TTreeReaderArray<double> pspmtlow2_dyecal = {fReader, "pspmtlow2.dyecal"};
  TTreeReaderArray<double> pspmtlow2_dytime = {fReader, "pspmtlow2.dytime"};
  TTreeReaderValue<unsigned int> pspmtlow2_dytimecfd = {fReader, "pspmtlow2.dytimecfd"};
  TTreeReaderValue<Int_t> pspmtlow2_dycfdfailbit = {fReader, "pspmtlow2.dycfdfailbit"};
  TTreeReaderValue<Int_t> pspmtlow2_dyoverflow = {fReader, "pspmtlow2.dyoverflow"};
  TTreeReaderValue<Int_t> pspmtlow2_dymult = {fReader, "pspmtlow2.dymult"};
  TTreeReaderArray<Double_t> pspmtlow2_dyenergies = {fReader, "pspmtlow2.dyenergies[16]"};
  TTreeReaderArray<Double_t> pspmtlow2_dytimes = {fReader, "pspmtlow2.dytimes[16]"};
  TTreeReaderArray<double> pspmtlow2_dychisq_single = {fReader, "pspmtlow2.dychisq_single"};
  TTreeReaderArray<double> pspmtlow2_dyE1_single = {fReader, "pspmtlow2.dyE1_single"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1real_single = {fReader, "pspmtlow2.dyE1real_single"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1cal_single = {fReader, "pspmtlow2.dyE1cal_single"};
  TTreeReaderArray<double> pspmtlow2_dyT1_single = {fReader, "pspmtlow2.dyT1_single"};
  TTreeReaderArray<double> pspmtlow2_dyoffset_single = {fReader, "pspmtlow2.dyoffset_single"};
  TTreeReaderArray<double> pspmtlow2_dyE1steepness_single = {fReader, "pspmtlow2.dyE1steepness_single"};
  TTreeReaderArray<double> pspmtlow2_dyE1decay_single = {fReader, "pspmtlow2.dyE1decay_single"};
  TTreeReaderArray<double> pspmtlow2_dychisq_double = {fReader, "pspmtlow2.dychisq_double"};
  TTreeReaderArray<double> pspmtlow2_dyE1_double = {fReader, "pspmtlow2.dyE1_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1real_double = {fReader, "pspmtlow2.dyE1real_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE1cal_double = {fReader, "pspmtlow2.dyE1cal_double"};
  TTreeReaderArray<double> pspmtlow2_dyT1_double = {fReader, "pspmtlow2.dyT1_double"};
  TTreeReaderArray<double> pspmtlow2_dyE1steepness_double = {fReader, "pspmtlow2.dyE1steepness_double"};
  TTreeReaderArray<double> pspmtlow2_dyE1decay_double = {fReader, "pspmtlow2.dyE1decay_double"};
  TTreeReaderArray<double> pspmtlow2_dyE2_double = {fReader, "pspmtlow2.dyE2_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE2real_double = {fReader, "pspmtlow2.dyE2real_double"};
  TTreeReaderValue<Double_t> pspmtlow2_dyE2cal_double = {fReader, "pspmtlow2.dyE2cal_double"};
  TTreeReaderArray<double> pspmtlow2_dyT2_double = {fReader, "pspmtlow2.dyT2_double"};
  TTreeReaderArray<double> pspmtlow2_dyE2steepness_double = {fReader, "pspmtlow2.dyE2steepness_double"};
  TTreeReaderArray<double> pspmtlow2_dyE2decay_double = {fReader, "pspmtlow2.dyE2decay_double"};
  TTreeReaderArray<double> pspmtlow2_dyoffset_double = {fReader, "pspmtlow2.dyoffset_double"};
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
  TTreeReaderValue<unsigned int> DB3PPACUAnT_fUniqueID = {fReader, "DB3PPACUAnT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB3PPACUAnT_fBits = {fReader, "DB3PPACUAnT.fBits"};
  TTreeReaderValue<Double_t> DB3PPACUAnT_energy = {fReader, "DB3PPACUAnT.energy"};
  TTreeReaderValue<Double_t> DB3PPACUAnT_ecal = {fReader, "DB3PPACUAnT.ecal"};
  TTreeReaderValue<Double_t> DB3PPACUAnT_time = {fReader, "DB3PPACUAnT.time"};
  TTreeReaderValue<Int_t> DB3PPACUAnT_hit = {fReader, "DB3PPACUAnT.hit"};
  TTreeReaderValue<unsigned int> DB3PPACDAnT_fUniqueID = {fReader, "DB3PPACDAnT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB3PPACDAnT_fBits = {fReader, "DB3PPACDAnT.fBits"};
  TTreeReaderValue<Double_t> DB3PPACDAnT_energy = {fReader, "DB3PPACDAnT.energy"};
  TTreeReaderValue<Double_t> DB3PPACDAnT_ecal = {fReader, "DB3PPACDAnT.ecal"};
  TTreeReaderValue<Double_t> DB3PPACDAnT_time = {fReader, "DB3PPACDAnT.time"};
  TTreeReaderValue<Int_t> DB3PPACDAnT_hit = {fReader, "DB3PPACDAnT.hit"};
  TTreeReaderValue<unsigned int> DB3PPACULT_fUniqueID = {fReader, "DB3PPACULT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB3PPACULT_fBits = {fReader, "DB3PPACULT.fBits"};
  TTreeReaderValue<Double_t> DB3PPACULT_energy = {fReader, "DB3PPACULT.energy"};
  TTreeReaderValue<Double_t> DB3PPACULT_ecal = {fReader, "DB3PPACULT.ecal"};
  TTreeReaderValue<Double_t> DB3PPACULT_time = {fReader, "DB3PPACULT.time"};
  TTreeReaderValue<Int_t> DB3PPACULT_hit = {fReader, "DB3PPACULT.hit"};
  TTreeReaderValue<unsigned int> DB3PPACURT_fUniqueID = {fReader, "DB3PPACURT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB3PPACURT_fBits = {fReader, "DB3PPACURT.fBits"};
  TTreeReaderValue<Double_t> DB3PPACURT_energy = {fReader, "DB3PPACURT.energy"};
  TTreeReaderValue<Double_t> DB3PPACURT_ecal = {fReader, "DB3PPACURT.ecal"};
  TTreeReaderValue<Double_t> DB3PPACURT_time = {fReader, "DB3PPACURT.time"};
  TTreeReaderValue<Int_t> DB3PPACURT_hit = {fReader, "DB3PPACURT.hit"};
  TTreeReaderValue<unsigned int> DB3PPACDLT_fUniqueID = {fReader, "DB3PPACDLT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB3PPACDLT_fBits = {fReader, "DB3PPACDLT.fBits"};
  TTreeReaderValue<Double_t> DB3PPACDLT_energy = {fReader, "DB3PPACDLT.energy"};
  TTreeReaderValue<Double_t> DB3PPACDLT_ecal = {fReader, "DB3PPACDLT.ecal"};
  TTreeReaderValue<Double_t> DB3PPACDLT_time = {fReader, "DB3PPACDLT.time"};
  TTreeReaderValue<Int_t> DB3PPACDLT_hit = {fReader, "DB3PPACDLT.hit"};
  TTreeReaderValue<unsigned int> DB3PPACDRT_fUniqueID = {fReader, "DB3PPACDRT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB3PPACDRT_fBits = {fReader, "DB3PPACDRT.fBits"};
  TTreeReaderValue<Double_t> DB3PPACDRT_energy = {fReader, "DB3PPACDRT.energy"};
  TTreeReaderValue<Double_t> DB3PPACDRT_ecal = {fReader, "DB3PPACDRT.ecal"};
  TTreeReaderValue<Double_t> DB3PPACDRT_time = {fReader, "DB3PPACDRT.time"};
  TTreeReaderValue<Int_t> DB3PPACDRT_hit = {fReader, "DB3PPACDRT.hit"};
  TTreeReaderValue<unsigned int> DB4PPACUT_fUniqueID = {fReader, "DB4PPACUT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB4PPACUT_fBits = {fReader, "DB4PPACUT.fBits"};
  TTreeReaderValue<Double_t> DB4PPACUT_energy = {fReader, "DB4PPACUT.energy"};
  TTreeReaderValue<Double_t> DB4PPACUT_ecal = {fReader, "DB4PPACUT.ecal"};
  TTreeReaderValue<Double_t> DB4PPACUT_time = {fReader, "DB4PPACUT.time"};
  TTreeReaderValue<Int_t> DB4PPACUT_hit = {fReader, "DB4PPACUT.hit"};
  TTreeReaderValue<unsigned int> DB4PPACDT_fUniqueID = {fReader, "DB4PPACDT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB4PPACDT_fBits = {fReader, "DB4PPACDT.fBits"};
  TTreeReaderValue<Double_t> DB4PPACDT_energy = {fReader, "DB4PPACDT.energy"};
  TTreeReaderValue<Double_t> DB4PPACDT_ecal = {fReader, "DB4PPACDT.ecal"};
  TTreeReaderValue<Double_t> DB4PPACDT_time = {fReader, "DB4PPACDT.time"};
  TTreeReaderValue<Int_t> DB4PPACDT_hit = {fReader, "DB4PPACDT.hit"};
  TTreeReaderValue<unsigned int> DB4PPACLT_fUniqueID = {fReader, "DB4PPACLT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB4PPACLT_fBits = {fReader, "DB4PPACLT.fBits"};
  TTreeReaderValue<Double_t> DB4PPACLT_energy = {fReader, "DB4PPACLT.energy"};
  TTreeReaderValue<Double_t> DB4PPACLT_ecal = {fReader, "DB4PPACLT.ecal"};
  TTreeReaderValue<Double_t> DB4PPACLT_time = {fReader, "DB4PPACLT.time"};
  TTreeReaderValue<Int_t> DB4PPACLT_hit = {fReader, "DB4PPACLT.hit"};
  TTreeReaderValue<unsigned int> DB4PPACRT_fUniqueID = {fReader, "DB4PPACRT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB4PPACRT_fBits = {fReader, "DB4PPACRT.fBits"};
  TTreeReaderValue<Double_t> DB4PPACRT_energy = {fReader, "DB4PPACRT.energy"};
  TTreeReaderValue<Double_t> DB4PPACRT_ecal = {fReader, "DB4PPACRT.ecal"};
  TTreeReaderValue<Double_t> DB4PPACRT_time = {fReader, "DB4PPACRT.time"};
  TTreeReaderValue<Int_t> DB4PPACRT_hit = {fReader, "DB4PPACRT.hit"};
  TTreeReaderValue<unsigned int> DB5PPACULT_fUniqueID = {fReader, "DB5PPACULT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB5PPACULT_fBits = {fReader, "DB5PPACULT.fBits"};
  TTreeReaderValue<Double_t> DB5PPACULT_energy = {fReader, "DB5PPACULT.energy"};
  TTreeReaderValue<Double_t> DB5PPACULT_ecal = {fReader, "DB5PPACULT.ecal"};
  TTreeReaderValue<Double_t> DB5PPACULT_time = {fReader, "DB5PPACULT.time"};
  TTreeReaderValue<Int_t> DB5PPACULT_hit = {fReader, "DB5PPACULT.hit"};
  TTreeReaderValue<unsigned int> DB5PPACURT_fUniqueID = {fReader, "DB5PPACURT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB5PPACURT_fBits = {fReader, "DB5PPACURT.fBits"};
  TTreeReaderValue<Double_t> DB5PPACURT_energy = {fReader, "DB5PPACURT.energy"};
  TTreeReaderValue<Double_t> DB5PPACURT_ecal = {fReader, "DB5PPACURT.ecal"};
  TTreeReaderValue<Double_t> DB5PPACURT_time = {fReader, "DB5PPACURT.time"};
  TTreeReaderValue<Int_t> DB5PPACURT_hit = {fReader, "DB5PPACURT.hit"};
  TTreeReaderValue<unsigned int> DB5PPACDLT_fUniqueID = {fReader, "DB5PPACDLT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB5PPACDLT_fBits = {fReader, "DB5PPACDLT.fBits"};
  TTreeReaderValue<Double_t> DB5PPACDLT_energy = {fReader, "DB5PPACDLT.energy"};
  TTreeReaderValue<Double_t> DB5PPACDLT_ecal = {fReader, "DB5PPACDLT.ecal"};
  TTreeReaderValue<Double_t> DB5PPACDLT_time = {fReader, "DB5PPACDLT.time"};
  TTreeReaderValue<Int_t> DB5PPACDLT_hit = {fReader, "DB5PPACDLT.hit"};
  TTreeReaderValue<unsigned int> DB5PPACDRT_fUniqueID = {fReader, "DB5PPACDRT.fUniqueID"};
  TTreeReaderValue<unsigned int> DB5PPACDRT_fBits = {fReader, "DB5PPACDRT.fBits"};
  TTreeReaderValue<Double_t> DB5PPACDRT_energy = {fReader, "DB5PPACDRT.energy"};
  TTreeReaderValue<Double_t> DB5PPACDRT_ecal = {fReader, "DB5PPACDRT.ecal"};
  TTreeReaderValue<Double_t> DB5PPACDRT_time = {fReader, "DB5PPACDRT.time"};
  TTreeReaderValue<Int_t> DB5PPACDRT_hit = {fReader, "DB5PPACDRT.hit"};
  TTreeReaderValue<unsigned int> NDB4PPACLT_fUniqueID = {fReader, "NDB4PPACLT.fUniqueID"};
  TTreeReaderValue<unsigned int> NDB4PPACLT_fBits = {fReader, "NDB4PPACLT.fBits"};
  TTreeReaderValue<Double_t> NDB4PPACLT_energy = {fReader, "NDB4PPACLT.energy"};
  TTreeReaderValue<Double_t> NDB4PPACLT_ecal = {fReader, "NDB4PPACLT.ecal"};
  TTreeReaderValue<Double_t> NDB4PPACLT_time = {fReader, "NDB4PPACLT.time"};
  TTreeReaderValue<Int_t> NDB4PPACLT_hit = {fReader, "NDB4PPACLT.hit"};
  TTreeReaderValue<unsigned int> NDB4PPACRT_fUniqueID = {fReader, "NDB4PPACRT.fUniqueID"};
  TTreeReaderValue<unsigned int> NDB4PPACRT_fBits = {fReader, "NDB4PPACRT.fBits"};
  TTreeReaderValue<Double_t> NDB4PPACRT_energy = {fReader, "NDB4PPACRT.energy"};
  TTreeReaderValue<Double_t> NDB4PPACRT_ecal = {fReader, "NDB4PPACRT.ecal"};
  TTreeReaderValue<Double_t> NDB4PPACRT_time = {fReader, "NDB4PPACRT.time"};
  TTreeReaderValue<Int_t> NDB4PPACRT_hit = {fReader, "NDB4PPACRT.hit"};
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
  TTreeReaderValue<unsigned int> pid_fUniqueID = {fReader, "pid.fUniqueID"};
  TTreeReaderValue<unsigned int> pid_fBits = {fReader, "pid.fBits"};
  TTreeReaderValue<Double_t> pid_de1 = {fReader, "pid.de1"};
  TTreeReaderValue<Double_t> pid_de2 = {fReader, "pid.de2"};
  TTreeReaderValue<Double_t> pid_tof = {fReader, "pid.tof"};
  TTreeReaderValue<Double_t> pid_scintScintTOF = {fReader, "pid.scintScintTOF"};
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
  TTreeReaderValue<Double_t> corr_dde1 = {fReader, "corr.dde1"};
  TTreeReaderValue<Double_t> corr_dde2 = {fReader, "corr.dde2"};
  TTreeReaderValue<Double_t> corr_dtof = {fReader, "corr.dtof"};
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
  TTreeReaderValue<Double_t> corr_giscorr = {fReader, "corr.giscorr"};
  TTreeReaderValue<Double_t> corr_gtof = {fReader, "corr.gtof"};
  TTreeReaderValue<Double_t> corr_gde2 = {fReader, "corr.gde2"};
  TTreeReaderValue<Double_t> corr_gitime = {fReader, "corr.gitime"};
  TTreeReaderValue<Double_t> corr_gtime = {fReader, "corr.gtime"};
  TTreeReaderValue<Double_t> corr_gitdiff = {fReader, "corr.gitdiff"};
  TTreeReaderValue<Int_t> corr_ifrontch = {fReader, "corr.ifrontch"};
  TTreeReaderValue<Int_t> corr_ibackch = {fReader, "corr.ibackch"};
  TTreeReaderValue<Int_t> corr_ddfrontch = {fReader, "corr.ddfrontch"};
  TTreeReaderValue<Int_t> corr_ddbackch = {fReader, "corr.ddbackch"};
  TTreeReaderValue<Int_t> corr_flag = {fReader, "corr.flag"};
  TTreeReaderValue<Int_t> corr_isdecay = {fReader, "corr.isdecay"};
  TTreeReaderValue<Int_t> corr_isimplant = {fReader, "corr.isimplant"};
  TTreeReaderValue<Int_t> corr_islightion = {fReader, "corr.islightion"};
  TTreeReaderValue<Int_t> corr_isdynovflnopins = {fReader, "corr.isdynovflnopins"};
  TTreeReaderValue<Int_t> corr_hasclover = {fReader, "corr.hasclover"};
  TTreeReaderValue<Int_t> corr_iscloveronly = {fReader, "corr.iscloveronly"};
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
  TTreeReaderArray<Double_t> labr_energy = {fReader, "labr.energy[16]"};
  TTreeReaderArray<Double_t> labr_ecal = {fReader, "labr.ecal[16]"};
  TTreeReaderArray<Double_t> labr_time = {fReader, "labr.time[16]"};
  TTreeReaderArray<unsigned int> labr_timecfd = {fReader, "labr.timecfd[16]"};
  TTreeReaderArray<Int_t> labr_cfdfailbit = {fReader, "labr.cfdfailbit[16]"};
  TTreeReaderArray<Double_t> labr_timecal = {fReader, "labr.timecal[16]"};
  TTreeReaderValue<Int_t> labr_mult = {fReader, "labr.mult"};
  TTreeReaderValue<Int_t> labr_hit = {fReader, "labr.hit"};
  // TTreeReaderArray<unsigned int> implantlist_fUniqueID = {fReader, "implantlist.fUniqueID"};
  // TTreeReaderArray<unsigned int> implantlist_fBits = {fReader, "implantlist.fBits"};
  // TTreeReaderArray<Double_t> implantlist_de1 = {fReader, "implantlist.de1"};
  // TTreeReaderArray<Double_t> implantlist_de2 = {fReader, "implantlist.de2"};
  // TTreeReaderArray<Double_t> implantlist_tof = {fReader, "implantlist.tof"};
  // TTreeReaderArray<Double_t> implantlist_scintScintTOF = {fReader, "implantlist.scintScintTOF"};
  // TTreeReaderArray<Double_t> implantlist_time = {fReader, "implantlist.time"};
  // TTreeReaderArray<Int_t> implantlist_xpos = {fReader, "implantlist.xpos"};
  // TTreeReaderArray<Int_t> implantlist_ypos = {fReader, "implantlist.ypos"};
  TTreeReaderValue<std::vector<TPID>> implantlist = {fReader,"implantlist"}; 

  BetaDecaySelector(TTree * /*tree*/ =0) { }
  virtual ~BetaDecaySelector() { }
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
  ClassDef(BetaDecaySelector,0);

};

#endif

#ifdef BetaDecaySelector_cxx
void BetaDecaySelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t BetaDecaySelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef BetaDecaySelector_cxx
