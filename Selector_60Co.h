//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb 26 14:54:05 2024 by ROOT version 6.04/02
// from TTree data/data
// found on file: /mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/newTau-cal/run-1240-sorted.root
//////////////////////////////////////////////////////////

#ifndef Selector_60Co_h
#define Selector_60Co_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include "TObject.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <TGraph2D.h>
#include "TObject.h"
#include "TVector.h"
#include <iomanip>
#include "TList.h"
#include "TH3D.h"
class Selector_60Co : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain






  TH2D* Detector_Vs_TDynode_Offset=nullptr;
  TH2D* LaBr3E_Vs_tdynode_offset=nullptr;
  TH1D* LaBr3_TDiff=nullptr;
  TH1D* TDynode_Offset=nullptr;
  TH2D* LaBr3E_Vs_TDiff=nullptr; 










   
// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaximplantlist = 1;

   // Declaration of leaf types
 //TROOTDataOut    *rootout;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          ddasdiagnostics_fUniqueID;
   UInt_t          ddasdiagnostics_fBits;
   Int_t           ddasdiagnostics_cmult;
   Double_t        ddasdiagnostics_eventlength;
   Double_t        ddasdiagnostics_tdiffevent;
   vector<int>     ddasdiagnostics_chanhit;
   UInt_t          clock_fUniqueID;
   UInt_t          clock_fBits;
   Double_t        clock_current;
   Double_t        clock_initial;
   UInt_t          pspmthigh1_fUniqueID;
   UInt_t          pspmthigh1_fBits;
   vector<unsigned short> pspmthigh1_dytrace;
   vector<double>  pspmthigh1_dyenergy;
   vector<double>  pspmthigh1_dyecal;
   vector<double>  pspmthigh1_dytime;
   UInt_t          pspmthigh1_dytimecfd;
   Int_t           pspmthigh1_dycfdfailbit;
   Int_t           pspmthigh1_dyoverflow;
   Int_t           pspmthigh1_dymult;
   Double_t        pspmthigh1_dyenergies[16];
   Double_t        pspmthigh1_dytimes[16];
   vector<double>  pspmthigh1_dychisq_single;
   vector<double>  pspmthigh1_dyE1_single;
   Double_t        pspmthigh1_dyE1real_single;
   Double_t        pspmthigh1_dyE1cal_single;
   vector<double>  pspmthigh1_dyT1_single;
   vector<double>  pspmthigh1_dyoffset_single;
   vector<double>  pspmthigh1_dyE1steepness_single;
   vector<double>  pspmthigh1_dyE1decay_single;
   vector<double>  pspmthigh1_dychisq_double;
   vector<double>  pspmthigh1_dyE1_double;
   Double_t        pspmthigh1_dyE1real_double;
   Double_t        pspmthigh1_dyE1cal_double;
   vector<double>  pspmthigh1_dyT1_double;
   vector<double>  pspmthigh1_dyE1steepness_double;
   vector<double>  pspmthigh1_dyE1decay_double;
   vector<double>  pspmthigh1_dyE2_double;
   Double_t        pspmthigh1_dyE2real_double;
   Double_t        pspmthigh1_dyE2cal_double;
   vector<double>  pspmthigh1_dyT2_double;
   vector<double>  pspmthigh1_dyE2steepness_double;
   vector<double>  pspmthigh1_dyE2decay_double;
   vector<double>  pspmthigh1_dyoffset_double;
   Double_t        pspmthigh1_dytdiffE1E2;
   Double_t        pspmthigh1_dytdiffE1E2cal;
   Double_t        pspmthigh1_aenergy[4];
   Double_t        pspmthigh1_aecal[4];
   Double_t        pspmthigh1_aenergy_qdc[4];
   Double_t        pspmthigh1_asum;
   Double_t        pspmthigh1_asum_qdc;
   Double_t        pspmthigh1_atime[4];
   Double_t        pspmthigh1_atimecal[4];
   Int_t           pspmthigh1_aoverflow[4];
   Int_t           pspmthigh1_aoverflowcount;
   Int_t           pspmthigh1_amultraw;
   Int_t           pspmthigh1_amult;
   Int_t           pspmthigh1_pixelmult[4];
   Double_t        pspmthigh1_xpos;
   Double_t        pspmthigh1_ypos;
   Int_t           pspmthigh1_dyhit;
   Int_t           pspmthigh1_ahit[4];
   Int_t           pspmthigh1_hit;
   UInt_t          pspmthigh2_fUniqueID;
   UInt_t          pspmthigh2_fBits;
   vector<unsigned short> pspmthigh2_dytrace;
   vector<double>  pspmthigh2_dyenergy;
   vector<double>  pspmthigh2_dyecal;
   vector<double>        pspmthigh2_dytime;
   UInt_t          pspmthigh2_dytimecfd;
   Int_t           pspmthigh2_dycfdfailbit;
   Int_t           pspmthigh2_dyoverflow;
   Int_t           pspmthigh2_dymult;
   Double_t        pspmthigh2_dyenergies[16];
   Double_t        pspmthigh2_dytimes[16];
   vector<double>  pspmthigh2_dychisq_single;
   vector<double>  pspmthigh2_dyE1_single;
   Double_t        pspmthigh2_dyE1real_single;
   Double_t        pspmthigh2_dyE1cal_single;
   vector<double>  pspmthigh2_dyT1_single;
   vector<double>  pspmthigh2_dyoffset_single;
   vector<double>  pspmthigh2_dyE1steepness_single;
   vector<double>  pspmthigh2_dyE1decay_single;
   vector<double>  pspmthigh2_dychisq_double;
   vector<double>  pspmthigh2_dyE1_double;
   Double_t        pspmthigh2_dyE1real_double;
   Double_t        pspmthigh2_dyE1cal_double;
   vector<double>  pspmthigh2_dyT1_double;
   vector<double>  pspmthigh2_dyE1steepness_double;
   vector<double>  pspmthigh2_dyE1decay_double;
   vector<double>  pspmthigh2_dyE2_double;
   Double_t        pspmthigh2_dyE2real_double;
   Double_t        pspmthigh2_dyE2cal_double;
   vector<double>  pspmthigh2_dyT2_double;
   vector<double>  pspmthigh2_dyE2steepness_double;
   vector<double>  pspmthigh2_dyE2decay_double;
   vector<double>  pspmthigh2_dyoffset_double;
   Double_t        pspmthigh2_dytdiffE1E2;
   Double_t        pspmthigh2_dytdiffE1E2cal;
   Double_t        pspmthigh2_aenergy[4];
   Double_t        pspmthigh2_aecal[4];
   Double_t        pspmthigh2_aenergy_qdc[4];
   Double_t        pspmthigh2_asum;
   Double_t        pspmthigh2_asum_qdc;
   Double_t        pspmthigh2_atime[4];
   Double_t        pspmthigh2_atimecal[4];
   Int_t           pspmthigh2_aoverflow[4];
   Int_t           pspmthigh2_aoverflowcount;
   Int_t           pspmthigh2_amultraw;
   Int_t           pspmthigh2_amult;
   Int_t           pspmthigh2_pixelmult[4];
   Double_t        pspmthigh2_xpos;
   Double_t        pspmthigh2_ypos;
   Int_t           pspmthigh2_dyhit;
   Int_t           pspmthigh2_ahit[4];
   Int_t           pspmthigh2_hit;
   UInt_t          pspmtlow1_fUniqueID;
   UInt_t          pspmtlow1_fBits;
   vector<unsigned short> pspmtlow1_dytrace;
   vector<double>  pspmtlow1_dyenergy;
   vector<double>  pspmtlow1_dyecal;
   vector<double>  pspmtlow1_dytime;
   UInt_t          pspmtlow1_dytimecfd;
   Int_t           pspmtlow1_dycfdfailbit;
   Int_t           pspmtlow1_dyoverflow;
   Int_t           pspmtlow1_dymult;
   Double_t        pspmtlow1_dyenergies[16];
   Double_t        pspmtlow1_dytimes[16];
   vector<double>  pspmtlow1_dychisq_single;
   vector<double>  pspmtlow1_dyE1_single;
   Double_t        pspmtlow1_dyE1real_single;
   Double_t        pspmtlow1_dyE1cal_single;
   vector<double>  pspmtlow1_dyT1_single;
   vector<double>  pspmtlow1_dyoffset_single;
   vector<double>  pspmtlow1_dyE1steepness_single;
   vector<double>  pspmtlow1_dyE1decay_single;
   vector<double>  pspmtlow1_dychisq_double;
   vector<double>  pspmtlow1_dyE1_double;
   Double_t        pspmtlow1_dyE1real_double;
   Double_t        pspmtlow1_dyE1cal_double;
   vector<double>  pspmtlow1_dyT1_double;
   vector<double>  pspmtlow1_dyE1steepness_double;
   vector<double>  pspmtlow1_dyE1decay_double;
   vector<double>  pspmtlow1_dyE2_double;
   Double_t        pspmtlow1_dyE2real_double;
   Double_t        pspmtlow1_dyE2cal_double;
   vector<double>  pspmtlow1_dyT2_double;
   vector<double>  pspmtlow1_dyE2steepness_double;
   vector<double>  pspmtlow1_dyE2decay_double;
   vector<double>  pspmtlow1_dyoffset_double;
   Double_t        pspmtlow1_dytdiffE1E2;
   Double_t        pspmtlow1_dytdiffE1E2cal;
   Double_t        pspmtlow1_aenergy[4];
   Double_t        pspmtlow1_aecal[4];
   Double_t        pspmtlow1_aenergy_qdc[4];
   Double_t        pspmtlow1_asum;
   Double_t        pspmtlow1_asum_qdc;
   Double_t        pspmtlow1_atime[4];
   Double_t        pspmtlow1_atimecal[4];
   Int_t           pspmtlow1_aoverflow[4];
   Int_t           pspmtlow1_aoverflowcount;
   Int_t           pspmtlow1_amultraw;
   Int_t           pspmtlow1_amult;
   Int_t           pspmtlow1_pixelmult[4];
   Double_t        pspmtlow1_xpos;
   Double_t        pspmtlow1_ypos;
   Int_t           pspmtlow1_dyhit;
   Int_t           pspmtlow1_ahit[4];
   Int_t           pspmtlow1_hit;
   UInt_t          pspmtlow2_fUniqueID;
   UInt_t          pspmtlow2_fBits;
   vector<unsigned short> pspmtlow2_dytrace;
   vector<double>  pspmtlow2_dyenergy;
   vector<double>  pspmtlow2_dyecal;
   vector<double>  pspmtlow2_dytime;
   UInt_t          pspmtlow2_dytimecfd;
   Int_t           pspmtlow2_dycfdfailbit;
   Int_t           pspmtlow2_dyoverflow;
   Int_t           pspmtlow2_dymult;
   Double_t        pspmtlow2_dyenergies[16];
   Double_t        pspmtlow2_dytimes[16];
   vector<double>  pspmtlow2_dychisq_single;
   vector<double>  pspmtlow2_dyE1_single;
   Double_t        pspmtlow2_dyE1real_single;
   Double_t        pspmtlow2_dyE1cal_single;
   vector<double>  pspmtlow2_dyT1_single;
   vector<double>  pspmtlow2_dyoffset_single;
   vector<double>  pspmtlow2_dyE1steepness_single;
   vector<double>  pspmtlow2_dyE1decay_single;
   vector<double>  pspmtlow2_dychisq_double;
   vector<double>  pspmtlow2_dyE1_double;
   Double_t        pspmtlow2_dyE1real_double;
   Double_t        pspmtlow2_dyE1cal_double;
   vector<double>  pspmtlow2_dyT1_double;
   vector<double>  pspmtlow2_dyE1steepness_double;
   vector<double>  pspmtlow2_dyE1decay_double;
   vector<double>  pspmtlow2_dyE2_double;
   Double_t        pspmtlow2_dyE2real_double;
   Double_t        pspmtlow2_dyE2cal_double;
   vector<double>  pspmtlow2_dyT2_double;
   vector<double>  pspmtlow2_dyE2steepness_double;
   vector<double>  pspmtlow2_dyE2decay_double;
   vector<double>  pspmtlow2_dyoffset_double;
   Double_t        pspmtlow2_dytdiffE1E2;
   Double_t        pspmtlow2_dytdiffE1E2cal;
   Double_t        pspmtlow2_aenergy[4];
   Double_t        pspmtlow2_aecal[4];
   Double_t        pspmtlow2_aenergy_qdc[4];
   Double_t        pspmtlow2_asum;
   Double_t        pspmtlow2_asum_qdc;
   Double_t        pspmtlow2_atime[4];
   Double_t        pspmtlow2_atimecal[4];
   Int_t           pspmtlow2_aoverflow[4];
   Int_t           pspmtlow2_aoverflowcount;
   Int_t           pspmtlow2_amultraw;
   Int_t           pspmtlow2_amult;
   Int_t           pspmtlow2_pixelmult[4];
   Double_t        pspmtlow2_xpos;
   Double_t        pspmtlow2_ypos;
   Int_t           pspmtlow2_dyhit;
   Int_t           pspmtlow2_ahit[4];
   Int_t           pspmtlow2_hit;
   UInt_t          SIPMT_fUniqueID;
   UInt_t          SIPMT_fBits;
   Double_t        SIPMT_energy;
   Double_t        SIPMT_ecal;
   Double_t        SIPMT_time;
   Int_t           SIPMT_hit;
   UInt_t          PIN01T_fUniqueID;
   UInt_t          PIN01T_fBits;
   Double_t        PIN01T_energy;
   Double_t        PIN01T_ecal;
   Double_t        PIN01T_time;
   Int_t           PIN01T_hit;
   UInt_t          SCLT_fUniqueID;
   UInt_t          SCLT_fBits;
   Double_t        SCLT_energy;
   Double_t        SCLT_ecal;
   Double_t        SCLT_time;
   Int_t           SCLT_hit;
   UInt_t          SCRT_fUniqueID;
   UInt_t          SCRT_fBits;
   Double_t        SCRT_energy;
   Double_t        SCRT_ecal;
   Double_t        SCRT_time;
   Int_t           SCRT_hit;
   UInt_t          DB3PPACUAnT_fUniqueID;
   UInt_t          DB3PPACUAnT_fBits;
   Double_t        DB3PPACUAnT_energy;
   Double_t        DB3PPACUAnT_ecal;
   Double_t        DB3PPACUAnT_time;
   Int_t           DB3PPACUAnT_hit;
   UInt_t          DB3PPACDAnT_fUniqueID;
   UInt_t          DB3PPACDAnT_fBits;
   Double_t        DB3PPACDAnT_energy;
   Double_t        DB3PPACDAnT_ecal;
   Double_t        DB3PPACDAnT_time;
   Int_t           DB3PPACDAnT_hit;
   UInt_t          DB3PPACULT_fUniqueID;
   UInt_t          DB3PPACULT_fBits;
   Double_t        DB3PPACULT_energy;
   Double_t        DB3PPACULT_ecal;
   Double_t        DB3PPACULT_time;
   Int_t           DB3PPACULT_hit;
   UInt_t          DB3PPACURT_fUniqueID;
   UInt_t          DB3PPACURT_fBits;
   Double_t        DB3PPACURT_energy;
   Double_t        DB3PPACURT_ecal;
   Double_t        DB3PPACURT_time;
   Int_t           DB3PPACURT_hit;
   UInt_t          DB3PPACDLT_fUniqueID;
   UInt_t          DB3PPACDLT_fBits;
   Double_t        DB3PPACDLT_energy;
   Double_t        DB3PPACDLT_ecal;
   Double_t        DB3PPACDLT_time;
   Int_t           DB3PPACDLT_hit;
   UInt_t          DB3PPACDRT_fUniqueID;
   UInt_t          DB3PPACDRT_fBits;
   Double_t        DB3PPACDRT_energy;
   Double_t        DB3PPACDRT_ecal;
   Double_t        DB3PPACDRT_time;
   Int_t           DB3PPACDRT_hit;
   UInt_t          DB4PPACUT_fUniqueID;
   UInt_t          DB4PPACUT_fBits;
   Double_t        DB4PPACUT_energy;
   Double_t        DB4PPACUT_ecal;
   Double_t        DB4PPACUT_time;
   Int_t           DB4PPACUT_hit;
   UInt_t          DB4PPACDT_fUniqueID;
   UInt_t          DB4PPACDT_fBits;
   Double_t        DB4PPACDT_energy;
   Double_t        DB4PPACDT_ecal;
   Double_t        DB4PPACDT_time;
   Int_t           DB4PPACDT_hit;
   UInt_t          DB4PPACLT_fUniqueID;
   UInt_t          DB4PPACLT_fBits;
   Double_t        DB4PPACLT_energy;
   Double_t        DB4PPACLT_ecal;
   Double_t        DB4PPACLT_time;
   Int_t           DB4PPACLT_hit;
   UInt_t          DB4PPACRT_fUniqueID;
   UInt_t          DB4PPACRT_fBits;
   Double_t        DB4PPACRT_energy;
   Double_t        DB4PPACRT_ecal;
   Double_t        DB4PPACRT_time;
   Int_t           DB4PPACRT_hit;
   UInt_t          DB5PPACULT_fUniqueID;
   UInt_t          DB5PPACULT_fBits;
   Double_t        DB5PPACULT_energy;
   Double_t        DB5PPACULT_ecal;
   Double_t        DB5PPACULT_time;
   Int_t           DB5PPACULT_hit;
   UInt_t          DB5PPACURT_fUniqueID;
   UInt_t          DB5PPACURT_fBits;
   Double_t        DB5PPACURT_energy;
   Double_t        DB5PPACURT_ecal;
   Double_t        DB5PPACURT_time;
   Int_t           DB5PPACURT_hit;
   UInt_t          DB5PPACDLT_fUniqueID;
   UInt_t          DB5PPACDLT_fBits;
   Double_t        DB5PPACDLT_energy;
   Double_t        DB5PPACDLT_ecal;
   Double_t        DB5PPACDLT_time;
   Int_t           DB5PPACDLT_hit;
   UInt_t          DB5PPACDRT_fUniqueID;
   UInt_t          DB5PPACDRT_fBits;
   Double_t        DB5PPACDRT_energy;
   Double_t        DB5PPACDRT_ecal;
   Double_t        DB5PPACDRT_time;
   Int_t           DB5PPACDRT_hit;
   UInt_t          NDB4PPACLT_fUniqueID;
   UInt_t          NDB4PPACLT_fBits;
   Double_t        NDB4PPACLT_energy;
   Double_t        NDB4PPACLT_ecal;
   Double_t        NDB4PPACLT_time;
   Int_t           NDB4PPACLT_hit;
   UInt_t          NDB4PPACRT_fUniqueID;
   UInt_t          NDB4PPACRT_fBits;
   Double_t        NDB4PPACRT_energy;
   Double_t        NDB4PPACRT_ecal;
   Double_t        NDB4PPACRT_time;
   Int_t           NDB4PPACRT_hit;
   UInt_t          pin01_fUniqueID;
   UInt_t          pin01_fBits;
   Double_t        pin01_energy;
   Double_t        pin01_ecal;
   Double_t        pin01_time;
   Int_t           pin01_hit;
   UInt_t          pin02_fUniqueID;
   UInt_t          pin02_fBits;
   Double_t        pin02_energy;
   Double_t        pin02_ecal;
   Double_t        pin02_time;
   Int_t           pin02_hit;
   UInt_t          sipm_fUniqueID;
   UInt_t          sipm_fBits;
   Double_t        sipm_energy;
   Double_t        sipm_ecal;
   Double_t        sipm_time;
   Int_t           sipm_hit;
   UInt_t          xscintB_fUniqueID;
   UInt_t          xscintB_fBits;
   Double_t        xscintB_energy;
   Double_t        xscintB_ecal;
   Double_t        xscintB_time;
   Int_t           xscintB_hit;
   UInt_t          xscintT_fUniqueID;
   UInt_t          xscintT_fBits;
   Double_t        xscintT_energy;
   Double_t        xscintT_ecal;
   Double_t        xscintT_time;
   Int_t           xscintT_hit;
   UInt_t          xpin1_fUniqueID;
   UInt_t          xpin1_fBits;
   Double_t        xpin1_energy;
   Double_t        xpin1_ecal;
   Double_t        xpin1_time;
   Int_t           xpin1_hit;
   UInt_t          xpin2_fUniqueID;
   UInt_t          xpin2_fBits;
   Double_t        xpin2_energy;
   Double_t        xpin2_ecal;
   Double_t        xpin2_time;
   Int_t           xpin2_hit;
   UInt_t          vetoR_fUniqueID;
   UInt_t          vetoR_fBits;
   Double_t        vetoR_energy;
   Double_t        vetoR_ecal;
   Double_t        vetoR_time;
   Int_t           vetoR_hit;
   UInt_t          vetoF_fUniqueID;
   UInt_t          vetoF_fBits;
   Double_t        vetoF_energy;
   Double_t        vetoF_ecal;
   Double_t        vetoF_time;
   Int_t           vetoF_hit;
   UInt_t          pid_fUniqueID;
   UInt_t          pid_fBits;
   Double_t        pid_de1;
   Double_t        pid_de2;
   Double_t        pid_tof;
   Double_t        pid_scintScintTOF;
   Double_t        pid_time;
   Int_t           pid_xpos;
   Int_t           pid_ypos;
   UInt_t          corr_fUniqueID;
   UInt_t          corr_fBits;
   Double_t        corr_idyecal;
   Double_t        corr_itime;
   Double_t        corr_ide1;
   Double_t        corr_ide2;
   Double_t        corr_itof;
   Double_t        corr_dtimplant;
   Double_t        corr_ixpos;
   Double_t        corr_iypos;
   Double_t        corr_idychisq_single;
   Double_t        corr_idyE1real_single;
   Double_t        corr_idyE1cal_single;
   Double_t        corr_idyT1_single;
   Double_t        corr_idyE1steepness_single;
   Double_t        corr_idyE1decay_single;
   Double_t        corr_idychisq_double;
   Double_t        corr_idyE1real_double;
   Double_t        corr_idyE1cal_double;
   Double_t        corr_idyE1steepness_double;
   Double_t        corr_idyE1decay_double;
   Double_t        corr_idyT1_double;
   Double_t        corr_idyE2real_double;
   Double_t        corr_idyE2cal_double;
   Double_t        corr_idyE2steepness_double;
   Double_t        corr_idyE2decay_double;
   Double_t        corr_idyT2_double;
   Double_t        corr_idytdiffE1E2cal;
   Double_t        corr_ddyecal;
   Double_t        corr_dtime;
   Double_t        corr_dxpos;
   Double_t        corr_dypos;
   Double_t        corr_dde1;
   Double_t        corr_dde2;
   Double_t        corr_dtof;
   Double_t        corr_ddychisq_single;
   Double_t        corr_ddyE1real_single;
   Double_t        corr_ddyE1cal_single;
   Double_t        corr_ddyT1_single;
   Double_t        corr_ddyE1steepness_single;
   Double_t        corr_ddyE1decay_single;
   Double_t        corr_ddychisq_double;
   Double_t        corr_ddyE1real_double;
   Double_t        corr_ddyE1cal_double;
   Double_t        corr_ddyE1steepness_double;
   Double_t        corr_ddyE1decay_double;
   Double_t        corr_ddyT1_double;
   Double_t        corr_ddyE2real_double;
   Double_t        corr_ddyE2cal_double;
   Double_t        corr_ddyE2steepness_double;
   Double_t        corr_ddyE2decay_double;
   Double_t        corr_ddyT2_double;
   Double_t        corr_ddytdiffE1E2cal;
   Int_t           corr_ifrontch;
   Int_t           corr_ibackch;
   Int_t           corr_ddfrontch;
   Int_t           corr_ddbackch;
   Int_t           corr_flag;
   Int_t           corr_isdecay;
   Int_t           corr_isimplant;
   Int_t           corr_islightion;
   Int_t           corr_isdynovflnopins;
   UInt_t          clover_fUniqueID;
   UInt_t          clover_fBits;
   Double_t        clover_time[52];
   UInt_t          clover_timecfd[52];
   Int_t           clover_cfdfailbit[52];
   Double_t        clover_timecal[52];
   Double_t        clover_energy[52];
   Double_t        clover_ecal[52];
   Int_t           clover_mult;
   Double_t        clover_timeab[13];
   Double_t        clover_timecalab[13];
   Int_t           clover_cfdfailbitab[13];
   Double_t        clover_ecalab[13];
   Int_t           clover_posmult[13];
   Int_t           clover_multab;
   Int_t           clover_hit;
   UInt_t          labr_fUniqueID;
   UInt_t          labr_fBits;
   Double_t        labr_energy[16];
   Double_t        labr_ecal[16];
   Double_t        labr_time[16];
   UInt_t          labr_timecfd[16];
   Int_t           labr_cfdfailbit[16];
   Double_t        labr_timecal[16];
   Int_t           labr_mult;
   Int_t           labr_hit;
   Int_t           implantlist_;
   /* UInt_t          implantlist_fUniqueID[kMaximplantlist];   //[implantlist_] */
   /* UInt_t          implantlist_fBits[kMaximplantlist];   //[implantlist_] */
   /* Double_t        implantlist_de1[kMaximplantlist];   //[implantlist_] */
   /* Double_t        implantlist_de2[kMaximplantlist];   //[implantlist_] */
   /* Double_t        implantlist_tof[kMaximplantlist];   //[implantlist_] */
   /* Double_t        implantlist_scintScintTOF[kMaximplantlist];   //[implantlist_] */
   /* Double_t        implantlist_time[kMaximplantlist];   //[implantlist_] */
   /* Int_t           implantlist_xpos[kMaximplantlist];   //[implantlist_] */
   /* Int_t           implantlist_ypos[kMaximplantlist];   //[implantlist_] */

   // List of branches
   TBranch        *b_rootout_fUniqueID;   //!
   TBranch        *b_rootout_fBits;   //!
   TBranch        *b_rootout_ddasdiagnostics_fUniqueID;   //!
   TBranch        *b_rootout_ddasdiagnostics_fBits;   //!
   TBranch        *b_rootout_ddasdiagnostics_cmult;   //!
   TBranch        *b_rootout_ddasdiagnostics_eventlength;   //!
   TBranch        *b_rootout_ddasdiagnostics_tdiffevent;   //!
   TBranch        *b_rootout_ddasdiagnostics_chanhit;   //!
   TBranch        *b_rootout_clock_fUniqueID;   //!
   TBranch        *b_rootout_clock_fBits;   //!
   TBranch        *b_rootout_clock_current;   //!
   TBranch        *b_rootout_clock_initial;   //!
   TBranch        *b_rootout_pspmthigh1_fUniqueID;   //!
   TBranch        *b_rootout_pspmthigh1_fBits;   //!
   TBranch        *b_rootout_pspmthigh1_dytrace;   //!
   TBranch        *b_rootout_pspmthigh1_dyenergy;   //!
   TBranch        *b_rootout_pspmthigh1_dyecal;   //!
   TBranch        *b_rootout_pspmthigh1_dytime;   //!
   TBranch        *b_rootout_pspmthigh1_dytimecfd;   //!
   TBranch        *b_rootout_pspmthigh1_dycfdfailbit;   //!
   TBranch        *b_rootout_pspmthigh1_dyoverflow;   //!
   TBranch        *b_rootout_pspmthigh1_dymult;   //!
   TBranch        *b_rootout_pspmthigh1_dyenergies;   //!
   TBranch        *b_rootout_pspmthigh1_dytimes;   //!
   TBranch        *b_rootout_pspmthigh1_dychisq_single;   //!
   TBranch        *b_rootout_pspmthigh1_dyE1_single;   //!
   TBranch        *b_rootout_pspmthigh1_dyE1real_single;   //!
   TBranch        *b_rootout_pspmthigh1_dyE1cal_single;   //!
   TBranch        *b_rootout_pspmthigh1_dyT1_single;   //!
   TBranch        *b_rootout_pspmthigh1_dyoffset_single;   //!
   TBranch        *b_rootout_pspmthigh1_dyE1steepness_single;   //!
   TBranch        *b_rootout_pspmthigh1_dyE1decay_single;   //!
   TBranch        *b_rootout_pspmthigh1_dychisq_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyE1_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyE1real_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyE1cal_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyT1_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyE1steepness_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyE1decay_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyE2_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyE2real_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyE2cal_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyT2_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyE2steepness_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyE2decay_double;   //!
   TBranch        *b_rootout_pspmthigh1_dyoffset_double;   //!
   TBranch        *b_rootout_pspmthigh1_dytdiffE1E2;   //!
   TBranch        *b_rootout_pspmthigh1_dytdiffE1E2cal;   //!
   TBranch        *b_rootout_pspmthigh1_aenergy;   //!
   TBranch        *b_rootout_pspmthigh1_aecal;   //!
   TBranch        *b_rootout_pspmthigh1_aenergy_qdc;   //!
   TBranch        *b_rootout_pspmthigh1_asum;   //!
   TBranch        *b_rootout_pspmthigh1_asum_qdc;   //!
   TBranch        *b_rootout_pspmthigh1_atime;   //!
   TBranch        *b_rootout_pspmthigh1_atimecal;   //!
   TBranch        *b_rootout_pspmthigh1_aoverflow;   //!
   TBranch        *b_rootout_pspmthigh1_aoverflowcount;   //!
   TBranch        *b_rootout_pspmthigh1_amultraw;   //!
   TBranch        *b_rootout_pspmthigh1_amult;   //!
   TBranch        *b_rootout_pspmthigh1_pixelmult;   //!
   TBranch        *b_rootout_pspmthigh1_xpos;   //!
   TBranch        *b_rootout_pspmthigh1_ypos;   //!
   TBranch        *b_rootout_pspmthigh1_dyhit;   //!
   TBranch        *b_rootout_pspmthigh1_ahit;   //!
   TBranch        *b_rootout_pspmthigh1_hit;   //!
   TBranch        *b_rootout_pspmthigh2_fUniqueID;   //!
   TBranch        *b_rootout_pspmthigh2_fBits;   //!
   TBranch        *b_rootout_pspmthigh2_dytrace;   //!
   TBranch        *b_rootout_pspmthigh2_dyenergy;   //!
   TBranch        *b_rootout_pspmthigh2_dyecal;   //!
   TBranch        *b_rootout_pspmthigh2_dytime;   //!
   TBranch        *b_rootout_pspmthigh2_dytimecfd;   //!
   TBranch        *b_rootout_pspmthigh2_dycfdfailbit;   //!
   TBranch        *b_rootout_pspmthigh2_dyoverflow;   //!
   TBranch        *b_rootout_pspmthigh2_dymult;   //!
   TBranch        *b_rootout_pspmthigh2_dyenergies;   //!
   TBranch        *b_rootout_pspmthigh2_dytimes;   //!
   TBranch        *b_rootout_pspmthigh2_dychisq_single;   //!
   TBranch        *b_rootout_pspmthigh2_dyE1_single;   //!
   TBranch        *b_rootout_pspmthigh2_dyE1real_single;   //!
   TBranch        *b_rootout_pspmthigh2_dyE1cal_single;   //!
   TBranch        *b_rootout_pspmthigh2_dyT1_single;   //!
   TBranch        *b_rootout_pspmthigh2_dyoffset_single;   //!
   TBranch        *b_rootout_pspmthigh2_dyE1steepness_single;   //!
   TBranch        *b_rootout_pspmthigh2_dyE1decay_single;   //!
   TBranch        *b_rootout_pspmthigh2_dychisq_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyE1_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyE1real_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyE1cal_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyT1_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyE1steepness_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyE1decay_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyE2_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyE2real_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyE2cal_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyT2_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyE2steepness_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyE2decay_double;   //!
   TBranch        *b_rootout_pspmthigh2_dyoffset_double;   //!
   TBranch        *b_rootout_pspmthigh2_dytdiffE1E2;   //!
   TBranch        *b_rootout_pspmthigh2_dytdiffE1E2cal;   //!
   TBranch        *b_rootout_pspmthigh2_aenergy;   //!
   TBranch        *b_rootout_pspmthigh2_aecal;   //!
   TBranch        *b_rootout_pspmthigh2_aenergy_qdc;   //!
   TBranch        *b_rootout_pspmthigh2_asum;   //!
   TBranch        *b_rootout_pspmthigh2_asum_qdc;   //!
   TBranch        *b_rootout_pspmthigh2_atime;   //!
   TBranch        *b_rootout_pspmthigh2_atimecal;   //!
   TBranch        *b_rootout_pspmthigh2_aoverflow;   //!
   TBranch        *b_rootout_pspmthigh2_aoverflowcount;   //!
   TBranch        *b_rootout_pspmthigh2_amultraw;   //!
   TBranch        *b_rootout_pspmthigh2_amult;   //!
   TBranch        *b_rootout_pspmthigh2_pixelmult;   //!
   TBranch        *b_rootout_pspmthigh2_xpos;   //!
   TBranch        *b_rootout_pspmthigh2_ypos;   //!
   TBranch        *b_rootout_pspmthigh2_dyhit;   //!
   TBranch        *b_rootout_pspmthigh2_ahit;   //!
   TBranch        *b_rootout_pspmthigh2_hit;   //!
   TBranch        *b_rootout_pspmtlow1_fUniqueID;   //!
   TBranch        *b_rootout_pspmtlow1_fBits;   //!
   TBranch        *b_rootout_pspmtlow1_dytrace;   //!
   TBranch        *b_rootout_pspmtlow1_dyenergy;   //!
   TBranch        *b_rootout_pspmtlow1_dyecal;   //!
   TBranch        *b_rootout_pspmtlow1_dytime;   //!
   TBranch        *b_rootout_pspmtlow1_dytimecfd;   //!
   TBranch        *b_rootout_pspmtlow1_dycfdfailbit;   //!
   TBranch        *b_rootout_pspmtlow1_dyoverflow;   //!
   TBranch        *b_rootout_pspmtlow1_dymult;   //!
   TBranch        *b_rootout_pspmtlow1_dyenergies;   //!
   TBranch        *b_rootout_pspmtlow1_dytimes;   //!
   TBranch        *b_rootout_pspmtlow1_dychisq_single;   //!
   TBranch        *b_rootout_pspmtlow1_dyE1_single;   //!
   TBranch        *b_rootout_pspmtlow1_dyE1real_single;   //!
   TBranch        *b_rootout_pspmtlow1_dyE1cal_single;   //!
   TBranch        *b_rootout_pspmtlow1_dyT1_single;   //!
   TBranch        *b_rootout_pspmtlow1_dyoffset_single;   //!
   TBranch        *b_rootout_pspmtlow1_dyE1steepness_single;   //!
   TBranch        *b_rootout_pspmtlow1_dyE1decay_single;   //!
   TBranch        *b_rootout_pspmtlow1_dychisq_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyE1_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyE1real_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyE1cal_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyT1_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyE1steepness_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyE1decay_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyE2_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyE2real_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyE2cal_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyT2_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyE2steepness_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyE2decay_double;   //!
   TBranch        *b_rootout_pspmtlow1_dyoffset_double;   //!
   TBranch        *b_rootout_pspmtlow1_dytdiffE1E2;   //!
   TBranch        *b_rootout_pspmtlow1_dytdiffE1E2cal;   //!
   TBranch        *b_rootout_pspmtlow1_aenergy;   //!
   TBranch        *b_rootout_pspmtlow1_aecal;   //!
   TBranch        *b_rootout_pspmtlow1_aenergy_qdc;   //!
   TBranch        *b_rootout_pspmtlow1_asum;   //!
   TBranch        *b_rootout_pspmtlow1_asum_qdc;   //!
   TBranch        *b_rootout_pspmtlow1_atime;   //!
   TBranch        *b_rootout_pspmtlow1_atimecal;   //!
   TBranch        *b_rootout_pspmtlow1_aoverflow;   //!
   TBranch        *b_rootout_pspmtlow1_aoverflowcount;   //!
   TBranch        *b_rootout_pspmtlow1_amultraw;   //!
   TBranch        *b_rootout_pspmtlow1_amult;   //!
   TBranch        *b_rootout_pspmtlow1_pixelmult;   //!
   TBranch        *b_rootout_pspmtlow1_xpos;   //!
   TBranch        *b_rootout_pspmtlow1_ypos;   //!
   TBranch        *b_rootout_pspmtlow1_dyhit;   //!
   TBranch        *b_rootout_pspmtlow1_ahit;   //!
   TBranch        *b_rootout_pspmtlow1_hit;   //!
   TBranch        *b_rootout_pspmtlow2_fUniqueID;   //!
   TBranch        *b_rootout_pspmtlow2_fBits;   //!
   TBranch        *b_rootout_pspmtlow2_dytrace;   //!
   TBranch        *b_rootout_pspmtlow2_dyenergy;   //!
   TBranch        *b_rootout_pspmtlow2_dyecal;   //!
   TBranch        *b_rootout_pspmtlow2_dytime;   //!
   TBranch        *b_rootout_pspmtlow2_dytimecfd;   //!
   TBranch        *b_rootout_pspmtlow2_dycfdfailbit;   //!
   TBranch        *b_rootout_pspmtlow2_dyoverflow;   //!
   TBranch        *b_rootout_pspmtlow2_dymult;   //!
   TBranch        *b_rootout_pspmtlow2_dyenergies;   //!
   TBranch        *b_rootout_pspmtlow2_dytimes;   //!
   TBranch        *b_rootout_pspmtlow2_dychisq_single;   //!
   TBranch        *b_rootout_pspmtlow2_dyE1_single;   //!
   TBranch        *b_rootout_pspmtlow2_dyE1real_single;   //!
   TBranch        *b_rootout_pspmtlow2_dyE1cal_single;   //!
   TBranch        *b_rootout_pspmtlow2_dyT1_single;   //!
   TBranch        *b_rootout_pspmtlow2_dyoffset_single;   //!
   TBranch        *b_rootout_pspmtlow2_dyE1steepness_single;   //!
   TBranch        *b_rootout_pspmtlow2_dyE1decay_single;   //!
   TBranch        *b_rootout_pspmtlow2_dychisq_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyE1_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyE1real_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyE1cal_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyT1_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyE1steepness_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyE1decay_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyE2_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyE2real_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyE2cal_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyT2_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyE2steepness_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyE2decay_double;   //!
   TBranch        *b_rootout_pspmtlow2_dyoffset_double;   //!
   TBranch        *b_rootout_pspmtlow2_dytdiffE1E2;   //!
   TBranch        *b_rootout_pspmtlow2_dytdiffE1E2cal;   //!
   TBranch        *b_rootout_pspmtlow2_aenergy;   //!
   TBranch        *b_rootout_pspmtlow2_aecal;   //!
   TBranch        *b_rootout_pspmtlow2_aenergy_qdc;   //!
   TBranch        *b_rootout_pspmtlow2_asum;   //!
   TBranch        *b_rootout_pspmtlow2_asum_qdc;   //!
   TBranch        *b_rootout_pspmtlow2_atime;   //!
   TBranch        *b_rootout_pspmtlow2_atimecal;   //!
   TBranch        *b_rootout_pspmtlow2_aoverflow;   //!
   TBranch        *b_rootout_pspmtlow2_aoverflowcount;   //!
   TBranch        *b_rootout_pspmtlow2_amultraw;   //!
   TBranch        *b_rootout_pspmtlow2_amult;   //!
   TBranch        *b_rootout_pspmtlow2_pixelmult;   //!
   TBranch        *b_rootout_pspmtlow2_xpos;   //!
   TBranch        *b_rootout_pspmtlow2_ypos;   //!
   TBranch        *b_rootout_pspmtlow2_dyhit;   //!
   TBranch        *b_rootout_pspmtlow2_ahit;   //!
   TBranch        *b_rootout_pspmtlow2_hit;   //!
   TBranch        *b_rootout_SIPMT_fUniqueID;   //!
   TBranch        *b_rootout_SIPMT_fBits;   //!
   TBranch        *b_rootout_SIPMT_energy;   //!
   TBranch        *b_rootout_SIPMT_ecal;   //!
   TBranch        *b_rootout_SIPMT_time;   //!
   TBranch        *b_rootout_SIPMT_hit;   //!
   TBranch        *b_rootout_PIN01T_fUniqueID;   //!
   TBranch        *b_rootout_PIN01T_fBits;   //!
   TBranch        *b_rootout_PIN01T_energy;   //!
   TBranch        *b_rootout_PIN01T_ecal;   //!
   TBranch        *b_rootout_PIN01T_time;   //!
   TBranch        *b_rootout_PIN01T_hit;   //!
   TBranch        *b_rootout_SCLT_fUniqueID;   //!
   TBranch        *b_rootout_SCLT_fBits;   //!
   TBranch        *b_rootout_SCLT_energy;   //!
   TBranch        *b_rootout_SCLT_ecal;   //!
   TBranch        *b_rootout_SCLT_time;   //!
   TBranch        *b_rootout_SCLT_hit;   //!
   TBranch        *b_rootout_SCRT_fUniqueID;   //!
   TBranch        *b_rootout_SCRT_fBits;   //!
   TBranch        *b_rootout_SCRT_energy;   //!
   TBranch        *b_rootout_SCRT_ecal;   //!
   TBranch        *b_rootout_SCRT_time;   //!
   TBranch        *b_rootout_SCRT_hit;   //!
   TBranch        *b_rootout_DB3PPACUAnT_fUniqueID;   //!
   TBranch        *b_rootout_DB3PPACUAnT_fBits;   //!
   TBranch        *b_rootout_DB3PPACUAnT_energy;   //!
   TBranch        *b_rootout_DB3PPACUAnT_ecal;   //!
   TBranch        *b_rootout_DB3PPACUAnT_time;   //!
   TBranch        *b_rootout_DB3PPACUAnT_hit;   //!
   TBranch        *b_rootout_DB3PPACDAnT_fUniqueID;   //!
   TBranch        *b_rootout_DB3PPACDAnT_fBits;   //!
   TBranch        *b_rootout_DB3PPACDAnT_energy;   //!
   TBranch        *b_rootout_DB3PPACDAnT_ecal;   //!
   TBranch        *b_rootout_DB3PPACDAnT_time;   //!
   TBranch        *b_rootout_DB3PPACDAnT_hit;   //!
   TBranch        *b_rootout_DB3PPACULT_fUniqueID;   //!
   TBranch        *b_rootout_DB3PPACULT_fBits;   //!
   TBranch        *b_rootout_DB3PPACULT_energy;   //!
   TBranch        *b_rootout_DB3PPACULT_ecal;   //!
   TBranch        *b_rootout_DB3PPACULT_time;   //!
   TBranch        *b_rootout_DB3PPACULT_hit;   //!
   TBranch        *b_rootout_DB3PPACURT_fUniqueID;   //!
   TBranch        *b_rootout_DB3PPACURT_fBits;   //!
   TBranch        *b_rootout_DB3PPACURT_energy;   //!
   TBranch        *b_rootout_DB3PPACURT_ecal;   //!
   TBranch        *b_rootout_DB3PPACURT_time;   //!
   TBranch        *b_rootout_DB3PPACURT_hit;   //!
   TBranch        *b_rootout_DB3PPACDLT_fUniqueID;   //!
   TBranch        *b_rootout_DB3PPACDLT_fBits;   //!
   TBranch        *b_rootout_DB3PPACDLT_energy;   //!
   TBranch        *b_rootout_DB3PPACDLT_ecal;   //!
   TBranch        *b_rootout_DB3PPACDLT_time;   //!
   TBranch        *b_rootout_DB3PPACDLT_hit;   //!
   TBranch        *b_rootout_DB3PPACDRT_fUniqueID;   //!
   TBranch        *b_rootout_DB3PPACDRT_fBits;   //!
   TBranch        *b_rootout_DB3PPACDRT_energy;   //!
   TBranch        *b_rootout_DB3PPACDRT_ecal;   //!
   TBranch        *b_rootout_DB3PPACDRT_time;   //!
   TBranch        *b_rootout_DB3PPACDRT_hit;   //!
   TBranch        *b_rootout_DB4PPACUT_fUniqueID;   //!
   TBranch        *b_rootout_DB4PPACUT_fBits;   //!
   TBranch        *b_rootout_DB4PPACUT_energy;   //!
   TBranch        *b_rootout_DB4PPACUT_ecal;   //!
   TBranch        *b_rootout_DB4PPACUT_time;   //!
   TBranch        *b_rootout_DB4PPACUT_hit;   //!
   TBranch        *b_rootout_DB4PPACDT_fUniqueID;   //!
   TBranch        *b_rootout_DB4PPACDT_fBits;   //!
   TBranch        *b_rootout_DB4PPACDT_energy;   //!
   TBranch        *b_rootout_DB4PPACDT_ecal;   //!
   TBranch        *b_rootout_DB4PPACDT_time;   //!
   TBranch        *b_rootout_DB4PPACDT_hit;   //!
   TBranch        *b_rootout_DB4PPACLT_fUniqueID;   //!
   TBranch        *b_rootout_DB4PPACLT_fBits;   //!
   TBranch        *b_rootout_DB4PPACLT_energy;   //!
   TBranch        *b_rootout_DB4PPACLT_ecal;   //!
   TBranch        *b_rootout_DB4PPACLT_time;   //!
   TBranch        *b_rootout_DB4PPACLT_hit;   //!
   TBranch        *b_rootout_DB4PPACRT_fUniqueID;   //!
   TBranch        *b_rootout_DB4PPACRT_fBits;   //!
   TBranch        *b_rootout_DB4PPACRT_energy;   //!
   TBranch        *b_rootout_DB4PPACRT_ecal;   //!
   TBranch        *b_rootout_DB4PPACRT_time;   //!
   TBranch        *b_rootout_DB4PPACRT_hit;   //!
   TBranch        *b_rootout_DB5PPACULT_fUniqueID;   //!
   TBranch        *b_rootout_DB5PPACULT_fBits;   //!
   TBranch        *b_rootout_DB5PPACULT_energy;   //!
   TBranch        *b_rootout_DB5PPACULT_ecal;   //!
   TBranch        *b_rootout_DB5PPACULT_time;   //!
   TBranch        *b_rootout_DB5PPACULT_hit;   //!
   TBranch        *b_rootout_DB5PPACURT_fUniqueID;   //!
   TBranch        *b_rootout_DB5PPACURT_fBits;   //!
   TBranch        *b_rootout_DB5PPACURT_energy;   //!
   TBranch        *b_rootout_DB5PPACURT_ecal;   //!
   TBranch        *b_rootout_DB5PPACURT_time;   //!
   TBranch        *b_rootout_DB5PPACURT_hit;   //!
   TBranch        *b_rootout_DB5PPACDLT_fUniqueID;   //!
   TBranch        *b_rootout_DB5PPACDLT_fBits;   //!
   TBranch        *b_rootout_DB5PPACDLT_energy;   //!
   TBranch        *b_rootout_DB5PPACDLT_ecal;   //!
   TBranch        *b_rootout_DB5PPACDLT_time;   //!
   TBranch        *b_rootout_DB5PPACDLT_hit;   //!
   TBranch        *b_rootout_DB5PPACDRT_fUniqueID;   //!
   TBranch        *b_rootout_DB5PPACDRT_fBits;   //!
   TBranch        *b_rootout_DB5PPACDRT_energy;   //!
   TBranch        *b_rootout_DB5PPACDRT_ecal;   //!
   TBranch        *b_rootout_DB5PPACDRT_time;   //!
   TBranch        *b_rootout_DB5PPACDRT_hit;   //!
   TBranch        *b_rootout_NDB4PPACLT_fUniqueID;   //!
   TBranch        *b_rootout_NDB4PPACLT_fBits;   //!
   TBranch        *b_rootout_NDB4PPACLT_energy;   //!
   TBranch        *b_rootout_NDB4PPACLT_ecal;   //!
   TBranch        *b_rootout_NDB4PPACLT_time;   //!
   TBranch        *b_rootout_NDB4PPACLT_hit;   //!
   TBranch        *b_rootout_NDB4PPACRT_fUniqueID;   //!
   TBranch        *b_rootout_NDB4PPACRT_fBits;   //!
   TBranch        *b_rootout_NDB4PPACRT_energy;   //!
   TBranch        *b_rootout_NDB4PPACRT_ecal;   //!
   TBranch        *b_rootout_NDB4PPACRT_time;   //!
   TBranch        *b_rootout_NDB4PPACRT_hit;   //!
   TBranch        *b_rootout_pin01_fUniqueID;   //!
   TBranch        *b_rootout_pin01_fBits;   //!
   TBranch        *b_rootout_pin01_energy;   //!
   TBranch        *b_rootout_pin01_ecal;   //!
   TBranch        *b_rootout_pin01_time;   //!
   TBranch        *b_rootout_pin01_hit;   //!
   TBranch        *b_rootout_pin02_fUniqueID;   //!
   TBranch        *b_rootout_pin02_fBits;   //!
   TBranch        *b_rootout_pin02_energy;   //!
   TBranch        *b_rootout_pin02_ecal;   //!
   TBranch        *b_rootout_pin02_time;   //!
   TBranch        *b_rootout_pin02_hit;   //!
   TBranch        *b_rootout_sipm_fUniqueID;   //!
   TBranch        *b_rootout_sipm_fBits;   //!
   TBranch        *b_rootout_sipm_energy;   //!
   TBranch        *b_rootout_sipm_ecal;   //!
   TBranch        *b_rootout_sipm_time;   //!
   TBranch        *b_rootout_sipm_hit;   //!
   TBranch        *b_rootout_xscintB_fUniqueID;   //!
   TBranch        *b_rootout_xscintB_fBits;   //!
   TBranch        *b_rootout_xscintB_energy;   //!
   TBranch        *b_rootout_xscintB_ecal;   //!
   TBranch        *b_rootout_xscintB_time;   //!
   TBranch        *b_rootout_xscintB_hit;   //!
   TBranch        *b_rootout_xscintT_fUniqueID;   //!
   TBranch        *b_rootout_xscintT_fBits;   //!
   TBranch        *b_rootout_xscintT_energy;   //!
   TBranch        *b_rootout_xscintT_ecal;   //!
   TBranch        *b_rootout_xscintT_time;   //!
   TBranch        *b_rootout_xscintT_hit;   //!
   TBranch        *b_rootout_xpin1_fUniqueID;   //!
   TBranch        *b_rootout_xpin1_fBits;   //!
   TBranch        *b_rootout_xpin1_energy;   //!
   TBranch        *b_rootout_xpin1_ecal;   //!
   TBranch        *b_rootout_xpin1_time;   //!
   TBranch        *b_rootout_xpin1_hit;   //!
   TBranch        *b_rootout_xpin2_fUniqueID;   //!
   TBranch        *b_rootout_xpin2_fBits;   //!
   TBranch        *b_rootout_xpin2_energy;   //!
   TBranch        *b_rootout_xpin2_ecal;   //!
   TBranch        *b_rootout_xpin2_time;   //!
   TBranch        *b_rootout_xpin2_hit;   //!
   TBranch        *b_rootout_vetoR_fUniqueID;   //!
   TBranch        *b_rootout_vetoR_fBits;   //!
   TBranch        *b_rootout_vetoR_energy;   //!
   TBranch        *b_rootout_vetoR_ecal;   //!
   TBranch        *b_rootout_vetoR_time;   //!
   TBranch        *b_rootout_vetoR_hit;   //!
   TBranch        *b_rootout_vetoF_fUniqueID;   //!
   TBranch        *b_rootout_vetoF_fBits;   //!
   TBranch        *b_rootout_vetoF_energy;   //!
   TBranch        *b_rootout_vetoF_ecal;   //!
   TBranch        *b_rootout_vetoF_time;   //!
   TBranch        *b_rootout_vetoF_hit;   //!
   TBranch        *b_rootout_pid_fUniqueID;   //!
   TBranch        *b_rootout_pid_fBits;   //!
   TBranch        *b_rootout_pid_de1;   //!
   TBranch        *b_rootout_pid_de2;   //!
   TBranch        *b_rootout_pid_tof;   //!
   TBranch        *b_rootout_pid_scintScintTOF;   //!
   TBranch        *b_rootout_pid_time;   //!
   TBranch        *b_rootout_pid_xpos;   //!
   TBranch        *b_rootout_pid_ypos;   //!
   TBranch        *b_rootout_corr_fUniqueID;   //!
   TBranch        *b_rootout_corr_fBits;   //!
   TBranch        *b_rootout_corr_idyecal;   //!
   TBranch        *b_rootout_corr_itime;   //!
   TBranch        *b_rootout_corr_ide1;   //!
   TBranch        *b_rootout_corr_ide2;   //!
   TBranch        *b_rootout_corr_itof;   //!
   TBranch        *b_rootout_corr_dtimplant;   //!
   TBranch        *b_rootout_corr_ixpos;   //!
   TBranch        *b_rootout_corr_iypos;   //!
   TBranch        *b_rootout_corr_idychisq_single;   //!
   TBranch        *b_rootout_corr_idyE1real_single;   //!
   TBranch        *b_rootout_corr_idyE1cal_single;   //!
   TBranch        *b_rootout_corr_idyT1_single;   //!
   TBranch        *b_rootout_corr_idyE1steepness_single;   //!
   TBranch        *b_rootout_corr_idyE1decay_single;   //!
   TBranch        *b_rootout_corr_idychisq_double;   //!
   TBranch        *b_rootout_corr_idyE1real_double;   //!
   TBranch        *b_rootout_corr_idyE1cal_double;   //!
   TBranch        *b_rootout_corr_idyE1steepness_double;   //!
   TBranch        *b_rootout_corr_idyE1decay_double;   //!
   TBranch        *b_rootout_corr_idyT1_double;   //!
   TBranch        *b_rootout_corr_idyE2real_double;   //!
   TBranch        *b_rootout_corr_idyE2cal_double;   //!
   TBranch        *b_rootout_corr_idyE2steepness_double;   //!
   TBranch        *b_rootout_corr_idyE2decay_double;   //!
   TBranch        *b_rootout_corr_idyT2_double;   //!
   TBranch        *b_rootout_corr_idytdiffE1E2cal;   //!
   TBranch        *b_rootout_corr_ddyecal;   //!
   TBranch        *b_rootout_corr_dtime;   //!
   TBranch        *b_rootout_corr_dxpos;   //!
   TBranch        *b_rootout_corr_dypos;   //!
   TBranch        *b_rootout_corr_dde1;   //!
   TBranch        *b_rootout_corr_dde2;   //!
   TBranch        *b_rootout_corr_dtof;   //!
   TBranch        *b_rootout_corr_ddychisq_single;   //!
   TBranch        *b_rootout_corr_ddyE1real_single;   //!
   TBranch        *b_rootout_corr_ddyE1cal_single;   //!
   TBranch        *b_rootout_corr_ddyT1_single;   //!
   TBranch        *b_rootout_corr_ddyE1steepness_single;   //!
   TBranch        *b_rootout_corr_ddyE1decay_single;   //!
   TBranch        *b_rootout_corr_ddychisq_double;   //!
   TBranch        *b_rootout_corr_ddyE1real_double;   //!
   TBranch        *b_rootout_corr_ddyE1cal_double;   //!
   TBranch        *b_rootout_corr_ddyE1steepness_double;   //!
   TBranch        *b_rootout_corr_ddyE1decay_double;   //!
   TBranch        *b_rootout_corr_ddyT1_double;   //!
   TBranch        *b_rootout_corr_ddyE2real_double;   //!
   TBranch        *b_rootout_corr_ddyE2cal_double;   //!
   TBranch        *b_rootout_corr_ddyE2steepness_double;   //!
   TBranch        *b_rootout_corr_ddyE2decay_double;   //!
   TBranch        *b_rootout_corr_ddyT2_double;   //!
   TBranch        *b_rootout_corr_ddytdiffE1E2cal;   //!
   TBranch        *b_rootout_corr_ifrontch;   //!
   TBranch        *b_rootout_corr_ibackch;   //!
   TBranch        *b_rootout_corr_ddfrontch;   //!
   TBranch        *b_rootout_corr_ddbackch;   //!
   TBranch        *b_rootout_corr_flag;   //!
   TBranch        *b_rootout_corr_isdecay;   //!
   TBranch        *b_rootout_corr_isimplant;   //!
   TBranch        *b_rootout_corr_islightion;   //!
   TBranch        *b_rootout_corr_isdynovflnopins;   //!
   TBranch        *b_rootout_clover_fUniqueID;   //!
   TBranch        *b_rootout_clover_fBits;   //!
   TBranch        *b_rootout_clover_time;   //!
   TBranch        *b_rootout_clover_timecfd;   //!
   TBranch        *b_rootout_clover_cfdfailbit;   //!
   TBranch        *b_rootout_clover_timecal;   //!
   TBranch        *b_rootout_clover_energy;   //!
   TBranch        *b_rootout_clover_ecal;   //!
   TBranch        *b_rootout_clover_mult;   //!
   TBranch        *b_rootout_clover_timeab;   //!
   TBranch        *b_rootout_clover_timecalab;   //!
   TBranch        *b_rootout_clover_cfdfailbitab;   //!
   TBranch        *b_rootout_clover_ecalab;   //!
   TBranch        *b_rootout_clover_posmult;   //!
   TBranch        *b_rootout_clover_multab;   //!
   TBranch        *b_rootout_clover_hit;   //!
   TBranch        *b_rootout_labr_fUniqueID;   //!
   TBranch        *b_rootout_labr_fBits;   //!
   TBranch        *b_rootout_labr_energy;   //!
   TBranch        *b_rootout_labr_ecal;   //!
   TBranch        *b_rootout_labr_time;   //!
   TBranch        *b_rootout_labr_timecfd;   //!
   TBranch        *b_rootout_labr_cfdfailbit;   //!
   TBranch        *b_rootout_labr_timecal;   //!
   TBranch        *b_rootout_labr_mult;   //!
   TBranch        *b_rootout_labr_hit;   //!
   /* TBranch        *b_implantlist_;   //! */
   /* TBranch        *b_implantlist_fUniqueID;   //! */
   /* TBranch        *b_implantlist_fBits;   //! */
   /* TBranch        *b_implantlist_de1;   //! */
   /* TBranch        *b_implantlist_de2;   //! */
   /* TBranch        *b_implantlist_tof;   //! */
   /* TBranch        *b_implantlist_scintScintTOF;   //! */
   /* TBranch        *b_implantlist_time;   //! */
   /* TBranch        *b_implantlist_xpos;   //! */
   /* TBranch        *b_implantlist_ypos;   //! */

   Selector_60Co(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selector_60Co() { }
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


//Checking that histograms are actually written to file
  void OutputObject(const char *objname) { //
    if(fOutput->FindObject(objname)) {
      fOutput->FindObject(objname)->Write();
    } else {
      printf("CANNOT FIND THIS FILE! \n");
    }
  }


   
   ClassDef(Selector_60Co,0);
};

#endif

#ifdef Selector_60Co_cxx
void Selector_60Co::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_rootout_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_rootout_fBits);
   fChain->SetBranchAddress("ddasdiagnostics.fUniqueID", &ddasdiagnostics_fUniqueID, &b_rootout_ddasdiagnostics_fUniqueID);
   fChain->SetBranchAddress("ddasdiagnostics.fBits", &ddasdiagnostics_fBits, &b_rootout_ddasdiagnostics_fBits);
   fChain->SetBranchAddress("ddasdiagnostics.cmult", &ddasdiagnostics_cmult, &b_rootout_ddasdiagnostics_cmult);
   fChain->SetBranchAddress("ddasdiagnostics.eventlength", &ddasdiagnostics_eventlength, &b_rootout_ddasdiagnostics_eventlength);
   fChain->SetBranchAddress("ddasdiagnostics.tdiffevent", &ddasdiagnostics_tdiffevent, &b_rootout_ddasdiagnostics_tdiffevent);
   fChain->SetBranchAddress("ddasdiagnostics.chanhit", &ddasdiagnostics_chanhit, &b_rootout_ddasdiagnostics_chanhit);
   fChain->SetBranchAddress("clock.fUniqueID", &clock_fUniqueID, &b_rootout_clock_fUniqueID);
   fChain->SetBranchAddress("clock.fBits", &clock_fBits, &b_rootout_clock_fBits);
   fChain->SetBranchAddress("clock.current", &clock_current, &b_rootout_clock_current);
   fChain->SetBranchAddress("clock.initial", &clock_initial, &b_rootout_clock_initial);
   fChain->SetBranchAddress("pspmthigh1.fUniqueID", &pspmthigh1_fUniqueID, &b_rootout_pspmthigh1_fUniqueID);
   fChain->SetBranchAddress("pspmthigh1.fBits", &pspmthigh1_fBits, &b_rootout_pspmthigh1_fBits);
   fChain->SetBranchAddress("pspmthigh1.dytrace", &pspmthigh1_dytrace, &b_rootout_pspmthigh1_dytrace);
   fChain->SetBranchAddress("pspmthigh1.dyenergy", &pspmthigh1_dyenergy, &b_rootout_pspmthigh1_dyenergy);
   fChain->SetBranchAddress("pspmthigh1.dyecal", &pspmthigh1_dyecal, &b_rootout_pspmthigh1_dyecal);
   fChain->SetBranchAddress("pspmthigh1.dytime", &pspmthigh1_dytime, &b_rootout_pspmthigh1_dytime);
   fChain->SetBranchAddress("pspmthigh1.dytimecfd", &pspmthigh1_dytimecfd, &b_rootout_pspmthigh1_dytimecfd);
   fChain->SetBranchAddress("pspmthigh1.dycfdfailbit", &pspmthigh1_dycfdfailbit, &b_rootout_pspmthigh1_dycfdfailbit);
   fChain->SetBranchAddress("pspmthigh1.dyoverflow", &pspmthigh1_dyoverflow, &b_rootout_pspmthigh1_dyoverflow);
   fChain->SetBranchAddress("pspmthigh1.dymult", &pspmthigh1_dymult, &b_rootout_pspmthigh1_dymult);
   fChain->SetBranchAddress("pspmthigh1.dyenergies[16]", pspmthigh1_dyenergies, &b_rootout_pspmthigh1_dyenergies);
   fChain->SetBranchAddress("pspmthigh1.dytimes[16]", pspmthigh1_dytimes, &b_rootout_pspmthigh1_dytimes);
   fChain->SetBranchAddress("pspmthigh1.dychisq_single", &pspmthigh1_dychisq_single, &b_rootout_pspmthigh1_dychisq_single);
   fChain->SetBranchAddress("pspmthigh1.dyE1_single", &pspmthigh1_dyE1_single, &b_rootout_pspmthigh1_dyE1_single);
   fChain->SetBranchAddress("pspmthigh1.dyE1real_single", &pspmthigh1_dyE1real_single, &b_rootout_pspmthigh1_dyE1real_single);
   fChain->SetBranchAddress("pspmthigh1.dyE1cal_single", &pspmthigh1_dyE1cal_single, &b_rootout_pspmthigh1_dyE1cal_single);
   fChain->SetBranchAddress("pspmthigh1.dyT1_single", &pspmthigh1_dyT1_single, &b_rootout_pspmthigh1_dyT1_single);
   fChain->SetBranchAddress("pspmthigh1.dyoffset_single", &pspmthigh1_dyoffset_single, &b_rootout_pspmthigh1_dyoffset_single);
   fChain->SetBranchAddress("pspmthigh1.dyE1steepness_single", &pspmthigh1_dyE1steepness_single, &b_rootout_pspmthigh1_dyE1steepness_single);
   fChain->SetBranchAddress("pspmthigh1.dyE1decay_single", &pspmthigh1_dyE1decay_single, &b_rootout_pspmthigh1_dyE1decay_single);
   fChain->SetBranchAddress("pspmthigh1.dychisq_double", &pspmthigh1_dychisq_double, &b_rootout_pspmthigh1_dychisq_double);
   fChain->SetBranchAddress("pspmthigh1.dyE1_double", &pspmthigh1_dyE1_double, &b_rootout_pspmthigh1_dyE1_double);
   fChain->SetBranchAddress("pspmthigh1.dyE1real_double", &pspmthigh1_dyE1real_double, &b_rootout_pspmthigh1_dyE1real_double);
   fChain->SetBranchAddress("pspmthigh1.dyE1cal_double", &pspmthigh1_dyE1cal_double, &b_rootout_pspmthigh1_dyE1cal_double);
   fChain->SetBranchAddress("pspmthigh1.dyT1_double", &pspmthigh1_dyT1_double, &b_rootout_pspmthigh1_dyT1_double);
   fChain->SetBranchAddress("pspmthigh1.dyE1steepness_double", &pspmthigh1_dyE1steepness_double, &b_rootout_pspmthigh1_dyE1steepness_double);
   fChain->SetBranchAddress("pspmthigh1.dyE1decay_double", &pspmthigh1_dyE1decay_double, &b_rootout_pspmthigh1_dyE1decay_double);
   fChain->SetBranchAddress("pspmthigh1.dyE2_double", &pspmthigh1_dyE2_double, &b_rootout_pspmthigh1_dyE2_double);
   fChain->SetBranchAddress("pspmthigh1.dyE2real_double", &pspmthigh1_dyE2real_double, &b_rootout_pspmthigh1_dyE2real_double);
   fChain->SetBranchAddress("pspmthigh1.dyE2cal_double", &pspmthigh1_dyE2cal_double, &b_rootout_pspmthigh1_dyE2cal_double);
   fChain->SetBranchAddress("pspmthigh1.dyT2_double", &pspmthigh1_dyT2_double, &b_rootout_pspmthigh1_dyT2_double);
   fChain->SetBranchAddress("pspmthigh1.dyE2steepness_double", &pspmthigh1_dyE2steepness_double, &b_rootout_pspmthigh1_dyE2steepness_double);
   fChain->SetBranchAddress("pspmthigh1.dyE2decay_double", &pspmthigh1_dyE2decay_double, &b_rootout_pspmthigh1_dyE2decay_double);
   fChain->SetBranchAddress("pspmthigh1.dyoffset_double", &pspmthigh1_dyoffset_double, &b_rootout_pspmthigh1_dyoffset_double);
   fChain->SetBranchAddress("pspmthigh1.dytdiffE1E2", &pspmthigh1_dytdiffE1E2, &b_rootout_pspmthigh1_dytdiffE1E2);
   fChain->SetBranchAddress("pspmthigh1.dytdiffE1E2cal", &pspmthigh1_dytdiffE1E2cal, &b_rootout_pspmthigh1_dytdiffE1E2cal);
   fChain->SetBranchAddress("pspmthigh1.aenergy[4]", pspmthigh1_aenergy, &b_rootout_pspmthigh1_aenergy);
   fChain->SetBranchAddress("pspmthigh1.aecal[4]", pspmthigh1_aecal, &b_rootout_pspmthigh1_aecal);
   fChain->SetBranchAddress("pspmthigh1.aenergy_qdc[4]", pspmthigh1_aenergy_qdc, &b_rootout_pspmthigh1_aenergy_qdc);
   fChain->SetBranchAddress("pspmthigh1.asum", &pspmthigh1_asum, &b_rootout_pspmthigh1_asum);
   fChain->SetBranchAddress("pspmthigh1.asum_qdc", &pspmthigh1_asum_qdc, &b_rootout_pspmthigh1_asum_qdc);
   fChain->SetBranchAddress("pspmthigh1.atime[4]", pspmthigh1_atime, &b_rootout_pspmthigh1_atime);
   fChain->SetBranchAddress("pspmthigh1.atimecal[4]", pspmthigh1_atimecal, &b_rootout_pspmthigh1_atimecal);
   fChain->SetBranchAddress("pspmthigh1.aoverflow[4]", pspmthigh1_aoverflow, &b_rootout_pspmthigh1_aoverflow);
   fChain->SetBranchAddress("pspmthigh1.aoverflowcount", &pspmthigh1_aoverflowcount, &b_rootout_pspmthigh1_aoverflowcount);
   fChain->SetBranchAddress("pspmthigh1.amultraw", &pspmthigh1_amultraw, &b_rootout_pspmthigh1_amultraw);
   fChain->SetBranchAddress("pspmthigh1.amult", &pspmthigh1_amult, &b_rootout_pspmthigh1_amult);
   fChain->SetBranchAddress("pspmthigh1.pixelmult[4]", pspmthigh1_pixelmult, &b_rootout_pspmthigh1_pixelmult);
   fChain->SetBranchAddress("pspmthigh1.xpos", &pspmthigh1_xpos, &b_rootout_pspmthigh1_xpos);
   fChain->SetBranchAddress("pspmthigh1.ypos", &pspmthigh1_ypos, &b_rootout_pspmthigh1_ypos);
   fChain->SetBranchAddress("pspmthigh1.dyhit", &pspmthigh1_dyhit, &b_rootout_pspmthigh1_dyhit);
   fChain->SetBranchAddress("pspmthigh1.ahit[4]", pspmthigh1_ahit, &b_rootout_pspmthigh1_ahit);
   fChain->SetBranchAddress("pspmthigh1.hit", &pspmthigh1_hit, &b_rootout_pspmthigh1_hit);
   fChain->SetBranchAddress("pspmthigh2.fUniqueID", &pspmthigh2_fUniqueID, &b_rootout_pspmthigh2_fUniqueID);
   fChain->SetBranchAddress("pspmthigh2.fBits", &pspmthigh2_fBits, &b_rootout_pspmthigh2_fBits);
   fChain->SetBranchAddress("pspmthigh2.dytrace", &pspmthigh2_dytrace, &b_rootout_pspmthigh2_dytrace);
   fChain->SetBranchAddress("pspmthigh2.dyenergy", &pspmthigh2_dyenergy, &b_rootout_pspmthigh2_dyenergy);
   fChain->SetBranchAddress("pspmthigh2.dyecal", &pspmthigh2_dyecal, &b_rootout_pspmthigh2_dyecal);
   fChain->SetBranchAddress("pspmthigh2.dytime", &pspmthigh2_dytime, &b_rootout_pspmthigh2_dytime);
   fChain->SetBranchAddress("pspmthigh2.dytimecfd", &pspmthigh2_dytimecfd, &b_rootout_pspmthigh2_dytimecfd);
   fChain->SetBranchAddress("pspmthigh2.dycfdfailbit", &pspmthigh2_dycfdfailbit, &b_rootout_pspmthigh2_dycfdfailbit);
   fChain->SetBranchAddress("pspmthigh2.dyoverflow", &pspmthigh2_dyoverflow, &b_rootout_pspmthigh2_dyoverflow);
   fChain->SetBranchAddress("pspmthigh2.dymult", &pspmthigh2_dymult, &b_rootout_pspmthigh2_dymult);
   fChain->SetBranchAddress("pspmthigh2.dyenergies[16]", pspmthigh2_dyenergies, &b_rootout_pspmthigh2_dyenergies);
   fChain->SetBranchAddress("pspmthigh2.dytimes[16]", pspmthigh2_dytimes, &b_rootout_pspmthigh2_dytimes);
   fChain->SetBranchAddress("pspmthigh2.dychisq_single", &pspmthigh2_dychisq_single, &b_rootout_pspmthigh2_dychisq_single);
   fChain->SetBranchAddress("pspmthigh2.dyE1_single", &pspmthigh2_dyE1_single, &b_rootout_pspmthigh2_dyE1_single);
   fChain->SetBranchAddress("pspmthigh2.dyE1real_single", &pspmthigh2_dyE1real_single, &b_rootout_pspmthigh2_dyE1real_single);
   fChain->SetBranchAddress("pspmthigh2.dyE1cal_single", &pspmthigh2_dyE1cal_single, &b_rootout_pspmthigh2_dyE1cal_single);
   fChain->SetBranchAddress("pspmthigh2.dyT1_single", &pspmthigh2_dyT1_single, &b_rootout_pspmthigh2_dyT1_single);
   fChain->SetBranchAddress("pspmthigh2.dyoffset_single", &pspmthigh2_dyoffset_single, &b_rootout_pspmthigh2_dyoffset_single);
   fChain->SetBranchAddress("pspmthigh2.dyE1steepness_single", &pspmthigh2_dyE1steepness_single, &b_rootout_pspmthigh2_dyE1steepness_single);
   fChain->SetBranchAddress("pspmthigh2.dyE1decay_single", &pspmthigh2_dyE1decay_single, &b_rootout_pspmthigh2_dyE1decay_single);
   fChain->SetBranchAddress("pspmthigh2.dychisq_double", &pspmthigh2_dychisq_double, &b_rootout_pspmthigh2_dychisq_double);
   fChain->SetBranchAddress("pspmthigh2.dyE1_double", &pspmthigh2_dyE1_double, &b_rootout_pspmthigh2_dyE1_double);
   fChain->SetBranchAddress("pspmthigh2.dyE1real_double", &pspmthigh2_dyE1real_double, &b_rootout_pspmthigh2_dyE1real_double);
   fChain->SetBranchAddress("pspmthigh2.dyE1cal_double", &pspmthigh2_dyE1cal_double, &b_rootout_pspmthigh2_dyE1cal_double);
   fChain->SetBranchAddress("pspmthigh2.dyT1_double", &pspmthigh2_dyT1_double, &b_rootout_pspmthigh2_dyT1_double);
   fChain->SetBranchAddress("pspmthigh2.dyE1steepness_double", &pspmthigh2_dyE1steepness_double, &b_rootout_pspmthigh2_dyE1steepness_double);
   fChain->SetBranchAddress("pspmthigh2.dyE1decay_double", &pspmthigh2_dyE1decay_double, &b_rootout_pspmthigh2_dyE1decay_double);
   fChain->SetBranchAddress("pspmthigh2.dyE2_double", &pspmthigh2_dyE2_double, &b_rootout_pspmthigh2_dyE2_double);
   fChain->SetBranchAddress("pspmthigh2.dyE2real_double", &pspmthigh2_dyE2real_double, &b_rootout_pspmthigh2_dyE2real_double);
   fChain->SetBranchAddress("pspmthigh2.dyE2cal_double", &pspmthigh2_dyE2cal_double, &b_rootout_pspmthigh2_dyE2cal_double);
   fChain->SetBranchAddress("pspmthigh2.dyT2_double", &pspmthigh2_dyT2_double, &b_rootout_pspmthigh2_dyT2_double);
   fChain->SetBranchAddress("pspmthigh2.dyE2steepness_double", &pspmthigh2_dyE2steepness_double, &b_rootout_pspmthigh2_dyE2steepness_double);
   fChain->SetBranchAddress("pspmthigh2.dyE2decay_double", &pspmthigh2_dyE2decay_double, &b_rootout_pspmthigh2_dyE2decay_double);
   fChain->SetBranchAddress("pspmthigh2.dyoffset_double", &pspmthigh2_dyoffset_double, &b_rootout_pspmthigh2_dyoffset_double);
   fChain->SetBranchAddress("pspmthigh2.dytdiffE1E2", &pspmthigh2_dytdiffE1E2, &b_rootout_pspmthigh2_dytdiffE1E2);
   fChain->SetBranchAddress("pspmthigh2.dytdiffE1E2cal", &pspmthigh2_dytdiffE1E2cal, &b_rootout_pspmthigh2_dytdiffE1E2cal);
   fChain->SetBranchAddress("pspmthigh2.aenergy[4]", pspmthigh2_aenergy, &b_rootout_pspmthigh2_aenergy);
   fChain->SetBranchAddress("pspmthigh2.aecal[4]", pspmthigh2_aecal, &b_rootout_pspmthigh2_aecal);
   fChain->SetBranchAddress("pspmthigh2.aenergy_qdc[4]", pspmthigh2_aenergy_qdc, &b_rootout_pspmthigh2_aenergy_qdc);
   fChain->SetBranchAddress("pspmthigh2.asum", &pspmthigh2_asum, &b_rootout_pspmthigh2_asum);
   fChain->SetBranchAddress("pspmthigh2.asum_qdc", &pspmthigh2_asum_qdc, &b_rootout_pspmthigh2_asum_qdc);
   fChain->SetBranchAddress("pspmthigh2.atime[4]", pspmthigh2_atime, &b_rootout_pspmthigh2_atime);
   fChain->SetBranchAddress("pspmthigh2.atimecal[4]", pspmthigh2_atimecal, &b_rootout_pspmthigh2_atimecal);
   fChain->SetBranchAddress("pspmthigh2.aoverflow[4]", pspmthigh2_aoverflow, &b_rootout_pspmthigh2_aoverflow);
   fChain->SetBranchAddress("pspmthigh2.aoverflowcount", &pspmthigh2_aoverflowcount, &b_rootout_pspmthigh2_aoverflowcount);
   fChain->SetBranchAddress("pspmthigh2.amultraw", &pspmthigh2_amultraw, &b_rootout_pspmthigh2_amultraw);
   fChain->SetBranchAddress("pspmthigh2.amult", &pspmthigh2_amult, &b_rootout_pspmthigh2_amult);
   fChain->SetBranchAddress("pspmthigh2.pixelmult[4]", pspmthigh2_pixelmult, &b_rootout_pspmthigh2_pixelmult);
   fChain->SetBranchAddress("pspmthigh2.xpos", &pspmthigh2_xpos, &b_rootout_pspmthigh2_xpos);
   fChain->SetBranchAddress("pspmthigh2.ypos", &pspmthigh2_ypos, &b_rootout_pspmthigh2_ypos);
   fChain->SetBranchAddress("pspmthigh2.dyhit", &pspmthigh2_dyhit, &b_rootout_pspmthigh2_dyhit);
   fChain->SetBranchAddress("pspmthigh2.ahit[4]", pspmthigh2_ahit, &b_rootout_pspmthigh2_ahit);
   fChain->SetBranchAddress("pspmthigh2.hit", &pspmthigh2_hit, &b_rootout_pspmthigh2_hit);
   fChain->SetBranchAddress("pspmtlow1.fUniqueID", &pspmtlow1_fUniqueID, &b_rootout_pspmtlow1_fUniqueID);
   fChain->SetBranchAddress("pspmtlow1.fBits", &pspmtlow1_fBits, &b_rootout_pspmtlow1_fBits);
   fChain->SetBranchAddress("pspmtlow1.dytrace", &pspmtlow1_dytrace, &b_rootout_pspmtlow1_dytrace);
   fChain->SetBranchAddress("pspmtlow1.dyenergy", &pspmtlow1_dyenergy, &b_rootout_pspmtlow1_dyenergy);
   fChain->SetBranchAddress("pspmtlow1.dyecal", &pspmtlow1_dyecal, &b_rootout_pspmtlow1_dyecal);
   fChain->SetBranchAddress("pspmtlow1.dytime", &pspmtlow1_dytime, &b_rootout_pspmtlow1_dytime);
   fChain->SetBranchAddress("pspmtlow1.dytimecfd", &pspmtlow1_dytimecfd, &b_rootout_pspmtlow1_dytimecfd);
   fChain->SetBranchAddress("pspmtlow1.dycfdfailbit", &pspmtlow1_dycfdfailbit, &b_rootout_pspmtlow1_dycfdfailbit);
   fChain->SetBranchAddress("pspmtlow1.dyoverflow", &pspmtlow1_dyoverflow, &b_rootout_pspmtlow1_dyoverflow);
   fChain->SetBranchAddress("pspmtlow1.dymult", &pspmtlow1_dymult, &b_rootout_pspmtlow1_dymult);
   fChain->SetBranchAddress("pspmtlow1.dyenergies[16]", pspmtlow1_dyenergies, &b_rootout_pspmtlow1_dyenergies);
   fChain->SetBranchAddress("pspmtlow1.dytimes[16]", pspmtlow1_dytimes, &b_rootout_pspmtlow1_dytimes);
   fChain->SetBranchAddress("pspmtlow1.dychisq_single", &pspmtlow1_dychisq_single, &b_rootout_pspmtlow1_dychisq_single);
   fChain->SetBranchAddress("pspmtlow1.dyE1_single", &pspmtlow1_dyE1_single, &b_rootout_pspmtlow1_dyE1_single);
   fChain->SetBranchAddress("pspmtlow1.dyE1real_single", &pspmtlow1_dyE1real_single, &b_rootout_pspmtlow1_dyE1real_single);
   fChain->SetBranchAddress("pspmtlow1.dyE1cal_single", &pspmtlow1_dyE1cal_single, &b_rootout_pspmtlow1_dyE1cal_single);
   fChain->SetBranchAddress("pspmtlow1.dyT1_single", &pspmtlow1_dyT1_single, &b_rootout_pspmtlow1_dyT1_single);
   fChain->SetBranchAddress("pspmtlow1.dyoffset_single", &pspmtlow1_dyoffset_single, &b_rootout_pspmtlow1_dyoffset_single);
   fChain->SetBranchAddress("pspmtlow1.dyE1steepness_single", &pspmtlow1_dyE1steepness_single, &b_rootout_pspmtlow1_dyE1steepness_single);
   fChain->SetBranchAddress("pspmtlow1.dyE1decay_single", &pspmtlow1_dyE1decay_single, &b_rootout_pspmtlow1_dyE1decay_single);
   fChain->SetBranchAddress("pspmtlow1.dychisq_double", &pspmtlow1_dychisq_double, &b_rootout_pspmtlow1_dychisq_double);
   fChain->SetBranchAddress("pspmtlow1.dyE1_double", &pspmtlow1_dyE1_double, &b_rootout_pspmtlow1_dyE1_double);
   fChain->SetBranchAddress("pspmtlow1.dyE1real_double", &pspmtlow1_dyE1real_double, &b_rootout_pspmtlow1_dyE1real_double);
   fChain->SetBranchAddress("pspmtlow1.dyE1cal_double", &pspmtlow1_dyE1cal_double, &b_rootout_pspmtlow1_dyE1cal_double);
   fChain->SetBranchAddress("pspmtlow1.dyT1_double", &pspmtlow1_dyT1_double, &b_rootout_pspmtlow1_dyT1_double);
   fChain->SetBranchAddress("pspmtlow1.dyE1steepness_double", &pspmtlow1_dyE1steepness_double, &b_rootout_pspmtlow1_dyE1steepness_double);
   fChain->SetBranchAddress("pspmtlow1.dyE1decay_double", &pspmtlow1_dyE1decay_double, &b_rootout_pspmtlow1_dyE1decay_double);
   fChain->SetBranchAddress("pspmtlow1.dyE2_double", &pspmtlow1_dyE2_double, &b_rootout_pspmtlow1_dyE2_double);
   fChain->SetBranchAddress("pspmtlow1.dyE2real_double", &pspmtlow1_dyE2real_double, &b_rootout_pspmtlow1_dyE2real_double);
   fChain->SetBranchAddress("pspmtlow1.dyE2cal_double", &pspmtlow1_dyE2cal_double, &b_rootout_pspmtlow1_dyE2cal_double);
   fChain->SetBranchAddress("pspmtlow1.dyT2_double", &pspmtlow1_dyT2_double, &b_rootout_pspmtlow1_dyT2_double);
   fChain->SetBranchAddress("pspmtlow1.dyE2steepness_double", &pspmtlow1_dyE2steepness_double, &b_rootout_pspmtlow1_dyE2steepness_double);
   fChain->SetBranchAddress("pspmtlow1.dyE2decay_double", &pspmtlow1_dyE2decay_double, &b_rootout_pspmtlow1_dyE2decay_double);
   fChain->SetBranchAddress("pspmtlow1.dyoffset_double", &pspmtlow1_dyoffset_double, &b_rootout_pspmtlow1_dyoffset_double);
   fChain->SetBranchAddress("pspmtlow1.dytdiffE1E2", &pspmtlow1_dytdiffE1E2, &b_rootout_pspmtlow1_dytdiffE1E2);
   fChain->SetBranchAddress("pspmtlow1.dytdiffE1E2cal", &pspmtlow1_dytdiffE1E2cal, &b_rootout_pspmtlow1_dytdiffE1E2cal);
   fChain->SetBranchAddress("pspmtlow1.aenergy[4]", pspmtlow1_aenergy, &b_rootout_pspmtlow1_aenergy);
   fChain->SetBranchAddress("pspmtlow1.aecal[4]", pspmtlow1_aecal, &b_rootout_pspmtlow1_aecal);
   fChain->SetBranchAddress("pspmtlow1.aenergy_qdc[4]", pspmtlow1_aenergy_qdc, &b_rootout_pspmtlow1_aenergy_qdc);
   fChain->SetBranchAddress("pspmtlow1.asum", &pspmtlow1_asum, &b_rootout_pspmtlow1_asum);
   fChain->SetBranchAddress("pspmtlow1.asum_qdc", &pspmtlow1_asum_qdc, &b_rootout_pspmtlow1_asum_qdc);
   fChain->SetBranchAddress("pspmtlow1.atime[4]", pspmtlow1_atime, &b_rootout_pspmtlow1_atime);
   fChain->SetBranchAddress("pspmtlow1.atimecal[4]", pspmtlow1_atimecal, &b_rootout_pspmtlow1_atimecal);
   fChain->SetBranchAddress("pspmtlow1.aoverflow[4]", pspmtlow1_aoverflow, &b_rootout_pspmtlow1_aoverflow);
   fChain->SetBranchAddress("pspmtlow1.aoverflowcount", &pspmtlow1_aoverflowcount, &b_rootout_pspmtlow1_aoverflowcount);
   fChain->SetBranchAddress("pspmtlow1.amultraw", &pspmtlow1_amultraw, &b_rootout_pspmtlow1_amultraw);
   fChain->SetBranchAddress("pspmtlow1.amult", &pspmtlow1_amult, &b_rootout_pspmtlow1_amult);
   fChain->SetBranchAddress("pspmtlow1.pixelmult[4]", pspmtlow1_pixelmult, &b_rootout_pspmtlow1_pixelmult);
   fChain->SetBranchAddress("pspmtlow1.xpos", &pspmtlow1_xpos, &b_rootout_pspmtlow1_xpos);
   fChain->SetBranchAddress("pspmtlow1.ypos", &pspmtlow1_ypos, &b_rootout_pspmtlow1_ypos);
   fChain->SetBranchAddress("pspmtlow1.dyhit", &pspmtlow1_dyhit, &b_rootout_pspmtlow1_dyhit);
   fChain->SetBranchAddress("pspmtlow1.ahit[4]", pspmtlow1_ahit, &b_rootout_pspmtlow1_ahit);
   fChain->SetBranchAddress("pspmtlow1.hit", &pspmtlow1_hit, &b_rootout_pspmtlow1_hit);
   fChain->SetBranchAddress("pspmtlow2.fUniqueID", &pspmtlow2_fUniqueID, &b_rootout_pspmtlow2_fUniqueID);
   fChain->SetBranchAddress("pspmtlow2.fBits", &pspmtlow2_fBits, &b_rootout_pspmtlow2_fBits);
   fChain->SetBranchAddress("pspmtlow2.dytrace", &pspmtlow2_dytrace, &b_rootout_pspmtlow2_dytrace);
   fChain->SetBranchAddress("pspmtlow2.dyenergy", &pspmtlow2_dyenergy, &b_rootout_pspmtlow2_dyenergy);
   fChain->SetBranchAddress("pspmtlow2.dyecal", &pspmtlow2_dyecal, &b_rootout_pspmtlow2_dyecal);
   fChain->SetBranchAddress("pspmtlow2.dytime", &pspmtlow2_dytime, &b_rootout_pspmtlow2_dytime);
   fChain->SetBranchAddress("pspmtlow2.dytimecfd", &pspmtlow2_dytimecfd, &b_rootout_pspmtlow2_dytimecfd);
   fChain->SetBranchAddress("pspmtlow2.dycfdfailbit", &pspmtlow2_dycfdfailbit, &b_rootout_pspmtlow2_dycfdfailbit);
   fChain->SetBranchAddress("pspmtlow2.dyoverflow", &pspmtlow2_dyoverflow, &b_rootout_pspmtlow2_dyoverflow);
   fChain->SetBranchAddress("pspmtlow2.dymult", &pspmtlow2_dymult, &b_rootout_pspmtlow2_dymult);
   fChain->SetBranchAddress("pspmtlow2.dyenergies[16]", pspmtlow2_dyenergies, &b_rootout_pspmtlow2_dyenergies);
   fChain->SetBranchAddress("pspmtlow2.dytimes[16]", pspmtlow2_dytimes, &b_rootout_pspmtlow2_dytimes);
   fChain->SetBranchAddress("pspmtlow2.dychisq_single", &pspmtlow2_dychisq_single, &b_rootout_pspmtlow2_dychisq_single);
   fChain->SetBranchAddress("pspmtlow2.dyE1_single", &pspmtlow2_dyE1_single, &b_rootout_pspmtlow2_dyE1_single);
   fChain->SetBranchAddress("pspmtlow2.dyE1real_single", &pspmtlow2_dyE1real_single, &b_rootout_pspmtlow2_dyE1real_single);
   fChain->SetBranchAddress("pspmtlow2.dyE1cal_single", &pspmtlow2_dyE1cal_single, &b_rootout_pspmtlow2_dyE1cal_single);
   fChain->SetBranchAddress("pspmtlow2.dyT1_single", &pspmtlow2_dyT1_single, &b_rootout_pspmtlow2_dyT1_single);
   fChain->SetBranchAddress("pspmtlow2.dyoffset_single", &pspmtlow2_dyoffset_single, &b_rootout_pspmtlow2_dyoffset_single);
   fChain->SetBranchAddress("pspmtlow2.dyE1steepness_single", &pspmtlow2_dyE1steepness_single, &b_rootout_pspmtlow2_dyE1steepness_single);
   fChain->SetBranchAddress("pspmtlow2.dyE1decay_single", &pspmtlow2_dyE1decay_single, &b_rootout_pspmtlow2_dyE1decay_single);
   fChain->SetBranchAddress("pspmtlow2.dychisq_double", &pspmtlow2_dychisq_double, &b_rootout_pspmtlow2_dychisq_double);
   fChain->SetBranchAddress("pspmtlow2.dyE1_double", &pspmtlow2_dyE1_double, &b_rootout_pspmtlow2_dyE1_double);
   fChain->SetBranchAddress("pspmtlow2.dyE1real_double", &pspmtlow2_dyE1real_double, &b_rootout_pspmtlow2_dyE1real_double);
   fChain->SetBranchAddress("pspmtlow2.dyE1cal_double", &pspmtlow2_dyE1cal_double, &b_rootout_pspmtlow2_dyE1cal_double);
   fChain->SetBranchAddress("pspmtlow2.dyT1_double", &pspmtlow2_dyT1_double, &b_rootout_pspmtlow2_dyT1_double);
   fChain->SetBranchAddress("pspmtlow2.dyE1steepness_double", &pspmtlow2_dyE1steepness_double, &b_rootout_pspmtlow2_dyE1steepness_double);
   fChain->SetBranchAddress("pspmtlow2.dyE1decay_double", &pspmtlow2_dyE1decay_double, &b_rootout_pspmtlow2_dyE1decay_double);
   fChain->SetBranchAddress("pspmtlow2.dyE2_double", &pspmtlow2_dyE2_double, &b_rootout_pspmtlow2_dyE2_double);
   fChain->SetBranchAddress("pspmtlow2.dyE2real_double", &pspmtlow2_dyE2real_double, &b_rootout_pspmtlow2_dyE2real_double);
   fChain->SetBranchAddress("pspmtlow2.dyE2cal_double", &pspmtlow2_dyE2cal_double, &b_rootout_pspmtlow2_dyE2cal_double);
   fChain->SetBranchAddress("pspmtlow2.dyT2_double", &pspmtlow2_dyT2_double, &b_rootout_pspmtlow2_dyT2_double);
   fChain->SetBranchAddress("pspmtlow2.dyE2steepness_double", &pspmtlow2_dyE2steepness_double, &b_rootout_pspmtlow2_dyE2steepness_double);
   fChain->SetBranchAddress("pspmtlow2.dyE2decay_double", &pspmtlow2_dyE2decay_double, &b_rootout_pspmtlow2_dyE2decay_double);
   fChain->SetBranchAddress("pspmtlow2.dyoffset_double", &pspmtlow2_dyoffset_double, &b_rootout_pspmtlow2_dyoffset_double);
   fChain->SetBranchAddress("pspmtlow2.dytdiffE1E2", &pspmtlow2_dytdiffE1E2, &b_rootout_pspmtlow2_dytdiffE1E2);
   fChain->SetBranchAddress("pspmtlow2.dytdiffE1E2cal", &pspmtlow2_dytdiffE1E2cal, &b_rootout_pspmtlow2_dytdiffE1E2cal);
   fChain->SetBranchAddress("pspmtlow2.aenergy[4]", pspmtlow2_aenergy, &b_rootout_pspmtlow2_aenergy);
   fChain->SetBranchAddress("pspmtlow2.aecal[4]", pspmtlow2_aecal, &b_rootout_pspmtlow2_aecal);
   fChain->SetBranchAddress("pspmtlow2.aenergy_qdc[4]", pspmtlow2_aenergy_qdc, &b_rootout_pspmtlow2_aenergy_qdc);
   fChain->SetBranchAddress("pspmtlow2.asum", &pspmtlow2_asum, &b_rootout_pspmtlow2_asum);
   fChain->SetBranchAddress("pspmtlow2.asum_qdc", &pspmtlow2_asum_qdc, &b_rootout_pspmtlow2_asum_qdc);
   fChain->SetBranchAddress("pspmtlow2.atime[4]", pspmtlow2_atime, &b_rootout_pspmtlow2_atime);
   fChain->SetBranchAddress("pspmtlow2.atimecal[4]", pspmtlow2_atimecal, &b_rootout_pspmtlow2_atimecal);
   fChain->SetBranchAddress("pspmtlow2.aoverflow[4]", pspmtlow2_aoverflow, &b_rootout_pspmtlow2_aoverflow);
   fChain->SetBranchAddress("pspmtlow2.aoverflowcount", &pspmtlow2_aoverflowcount, &b_rootout_pspmtlow2_aoverflowcount);
   fChain->SetBranchAddress("pspmtlow2.amultraw", &pspmtlow2_amultraw, &b_rootout_pspmtlow2_amultraw);
   fChain->SetBranchAddress("pspmtlow2.amult", &pspmtlow2_amult, &b_rootout_pspmtlow2_amult);
   fChain->SetBranchAddress("pspmtlow2.pixelmult[4]", pspmtlow2_pixelmult, &b_rootout_pspmtlow2_pixelmult);
   fChain->SetBranchAddress("pspmtlow2.xpos", &pspmtlow2_xpos, &b_rootout_pspmtlow2_xpos);
   fChain->SetBranchAddress("pspmtlow2.ypos", &pspmtlow2_ypos, &b_rootout_pspmtlow2_ypos);
   fChain->SetBranchAddress("pspmtlow2.dyhit", &pspmtlow2_dyhit, &b_rootout_pspmtlow2_dyhit);
   fChain->SetBranchAddress("pspmtlow2.ahit[4]", pspmtlow2_ahit, &b_rootout_pspmtlow2_ahit);
   fChain->SetBranchAddress("pspmtlow2.hit", &pspmtlow2_hit, &b_rootout_pspmtlow2_hit);
   fChain->SetBranchAddress("SIPMT.fUniqueID", &SIPMT_fUniqueID, &b_rootout_SIPMT_fUniqueID);
   fChain->SetBranchAddress("SIPMT.fBits", &SIPMT_fBits, &b_rootout_SIPMT_fBits);
   fChain->SetBranchAddress("SIPMT.energy", &SIPMT_energy, &b_rootout_SIPMT_energy);
   fChain->SetBranchAddress("SIPMT.ecal", &SIPMT_ecal, &b_rootout_SIPMT_ecal);
   fChain->SetBranchAddress("SIPMT.time", &SIPMT_time, &b_rootout_SIPMT_time);
   fChain->SetBranchAddress("SIPMT.hit", &SIPMT_hit, &b_rootout_SIPMT_hit);
   fChain->SetBranchAddress("PIN01T.fUniqueID", &PIN01T_fUniqueID, &b_rootout_PIN01T_fUniqueID);
   fChain->SetBranchAddress("PIN01T.fBits", &PIN01T_fBits, &b_rootout_PIN01T_fBits);
   fChain->SetBranchAddress("PIN01T.energy", &PIN01T_energy, &b_rootout_PIN01T_energy);
   fChain->SetBranchAddress("PIN01T.ecal", &PIN01T_ecal, &b_rootout_PIN01T_ecal);
   fChain->SetBranchAddress("PIN01T.time", &PIN01T_time, &b_rootout_PIN01T_time);
   fChain->SetBranchAddress("PIN01T.hit", &PIN01T_hit, &b_rootout_PIN01T_hit);
   fChain->SetBranchAddress("SCLT.fUniqueID", &SCLT_fUniqueID, &b_rootout_SCLT_fUniqueID);
   fChain->SetBranchAddress("SCLT.fBits", &SCLT_fBits, &b_rootout_SCLT_fBits);
   fChain->SetBranchAddress("SCLT.energy", &SCLT_energy, &b_rootout_SCLT_energy);
   fChain->SetBranchAddress("SCLT.ecal", &SCLT_ecal, &b_rootout_SCLT_ecal);
   fChain->SetBranchAddress("SCLT.time", &SCLT_time, &b_rootout_SCLT_time);
   fChain->SetBranchAddress("SCLT.hit", &SCLT_hit, &b_rootout_SCLT_hit);
   fChain->SetBranchAddress("SCRT.fUniqueID", &SCRT_fUniqueID, &b_rootout_SCRT_fUniqueID);
   fChain->SetBranchAddress("SCRT.fBits", &SCRT_fBits, &b_rootout_SCRT_fBits);
   fChain->SetBranchAddress("SCRT.energy", &SCRT_energy, &b_rootout_SCRT_energy);
   fChain->SetBranchAddress("SCRT.ecal", &SCRT_ecal, &b_rootout_SCRT_ecal);
   fChain->SetBranchAddress("SCRT.time", &SCRT_time, &b_rootout_SCRT_time);
   fChain->SetBranchAddress("SCRT.hit", &SCRT_hit, &b_rootout_SCRT_hit);
   fChain->SetBranchAddress("DB3PPACUAnT.fUniqueID", &DB3PPACUAnT_fUniqueID, &b_rootout_DB3PPACUAnT_fUniqueID);
   fChain->SetBranchAddress("DB3PPACUAnT.fBits", &DB3PPACUAnT_fBits, &b_rootout_DB3PPACUAnT_fBits);
   fChain->SetBranchAddress("DB3PPACUAnT.energy", &DB3PPACUAnT_energy, &b_rootout_DB3PPACUAnT_energy);
   fChain->SetBranchAddress("DB3PPACUAnT.ecal", &DB3PPACUAnT_ecal, &b_rootout_DB3PPACUAnT_ecal);
   fChain->SetBranchAddress("DB3PPACUAnT.time", &DB3PPACUAnT_time, &b_rootout_DB3PPACUAnT_time);
   fChain->SetBranchAddress("DB3PPACUAnT.hit", &DB3PPACUAnT_hit, &b_rootout_DB3PPACUAnT_hit);
   fChain->SetBranchAddress("DB3PPACDAnT.fUniqueID", &DB3PPACDAnT_fUniqueID, &b_rootout_DB3PPACDAnT_fUniqueID);
   fChain->SetBranchAddress("DB3PPACDAnT.fBits", &DB3PPACDAnT_fBits, &b_rootout_DB3PPACDAnT_fBits);
   fChain->SetBranchAddress("DB3PPACDAnT.energy", &DB3PPACDAnT_energy, &b_rootout_DB3PPACDAnT_energy);
   fChain->SetBranchAddress("DB3PPACDAnT.ecal", &DB3PPACDAnT_ecal, &b_rootout_DB3PPACDAnT_ecal);
   fChain->SetBranchAddress("DB3PPACDAnT.time", &DB3PPACDAnT_time, &b_rootout_DB3PPACDAnT_time);
   fChain->SetBranchAddress("DB3PPACDAnT.hit", &DB3PPACDAnT_hit, &b_rootout_DB3PPACDAnT_hit);
   fChain->SetBranchAddress("DB3PPACULT.fUniqueID", &DB3PPACULT_fUniqueID, &b_rootout_DB3PPACULT_fUniqueID);
   fChain->SetBranchAddress("DB3PPACULT.fBits", &DB3PPACULT_fBits, &b_rootout_DB3PPACULT_fBits);
   fChain->SetBranchAddress("DB3PPACULT.energy", &DB3PPACULT_energy, &b_rootout_DB3PPACULT_energy);
   fChain->SetBranchAddress("DB3PPACULT.ecal", &DB3PPACULT_ecal, &b_rootout_DB3PPACULT_ecal);
   fChain->SetBranchAddress("DB3PPACULT.time", &DB3PPACULT_time, &b_rootout_DB3PPACULT_time);
   fChain->SetBranchAddress("DB3PPACULT.hit", &DB3PPACULT_hit, &b_rootout_DB3PPACULT_hit);
   fChain->SetBranchAddress("DB3PPACURT.fUniqueID", &DB3PPACURT_fUniqueID, &b_rootout_DB3PPACURT_fUniqueID);
   fChain->SetBranchAddress("DB3PPACURT.fBits", &DB3PPACURT_fBits, &b_rootout_DB3PPACURT_fBits);
   fChain->SetBranchAddress("DB3PPACURT.energy", &DB3PPACURT_energy, &b_rootout_DB3PPACURT_energy);
   fChain->SetBranchAddress("DB3PPACURT.ecal", &DB3PPACURT_ecal, &b_rootout_DB3PPACURT_ecal);
   fChain->SetBranchAddress("DB3PPACURT.time", &DB3PPACURT_time, &b_rootout_DB3PPACURT_time);
   fChain->SetBranchAddress("DB3PPACURT.hit", &DB3PPACURT_hit, &b_rootout_DB3PPACURT_hit);
   fChain->SetBranchAddress("DB3PPACDLT.fUniqueID", &DB3PPACDLT_fUniqueID, &b_rootout_DB3PPACDLT_fUniqueID);
   fChain->SetBranchAddress("DB3PPACDLT.fBits", &DB3PPACDLT_fBits, &b_rootout_DB3PPACDLT_fBits);
   fChain->SetBranchAddress("DB3PPACDLT.energy", &DB3PPACDLT_energy, &b_rootout_DB3PPACDLT_energy);
   fChain->SetBranchAddress("DB3PPACDLT.ecal", &DB3PPACDLT_ecal, &b_rootout_DB3PPACDLT_ecal);
   fChain->SetBranchAddress("DB3PPACDLT.time", &DB3PPACDLT_time, &b_rootout_DB3PPACDLT_time);
   fChain->SetBranchAddress("DB3PPACDLT.hit", &DB3PPACDLT_hit, &b_rootout_DB3PPACDLT_hit);
   fChain->SetBranchAddress("DB3PPACDRT.fUniqueID", &DB3PPACDRT_fUniqueID, &b_rootout_DB3PPACDRT_fUniqueID);
   fChain->SetBranchAddress("DB3PPACDRT.fBits", &DB3PPACDRT_fBits, &b_rootout_DB3PPACDRT_fBits);
   fChain->SetBranchAddress("DB3PPACDRT.energy", &DB3PPACDRT_energy, &b_rootout_DB3PPACDRT_energy);
   fChain->SetBranchAddress("DB3PPACDRT.ecal", &DB3PPACDRT_ecal, &b_rootout_DB3PPACDRT_ecal);
   fChain->SetBranchAddress("DB3PPACDRT.time", &DB3PPACDRT_time, &b_rootout_DB3PPACDRT_time);
   fChain->SetBranchAddress("DB3PPACDRT.hit", &DB3PPACDRT_hit, &b_rootout_DB3PPACDRT_hit);
   fChain->SetBranchAddress("DB4PPACUT.fUniqueID", &DB4PPACUT_fUniqueID, &b_rootout_DB4PPACUT_fUniqueID);
   fChain->SetBranchAddress("DB4PPACUT.fBits", &DB4PPACUT_fBits, &b_rootout_DB4PPACUT_fBits);
   fChain->SetBranchAddress("DB4PPACUT.energy", &DB4PPACUT_energy, &b_rootout_DB4PPACUT_energy);
   fChain->SetBranchAddress("DB4PPACUT.ecal", &DB4PPACUT_ecal, &b_rootout_DB4PPACUT_ecal);
   fChain->SetBranchAddress("DB4PPACUT.time", &DB4PPACUT_time, &b_rootout_DB4PPACUT_time);
   fChain->SetBranchAddress("DB4PPACUT.hit", &DB4PPACUT_hit, &b_rootout_DB4PPACUT_hit);
   fChain->SetBranchAddress("DB4PPACDT.fUniqueID", &DB4PPACDT_fUniqueID, &b_rootout_DB4PPACDT_fUniqueID);
   fChain->SetBranchAddress("DB4PPACDT.fBits", &DB4PPACDT_fBits, &b_rootout_DB4PPACDT_fBits);
   fChain->SetBranchAddress("DB4PPACDT.energy", &DB4PPACDT_energy, &b_rootout_DB4PPACDT_energy);
   fChain->SetBranchAddress("DB4PPACDT.ecal", &DB4PPACDT_ecal, &b_rootout_DB4PPACDT_ecal);
   fChain->SetBranchAddress("DB4PPACDT.time", &DB4PPACDT_time, &b_rootout_DB4PPACDT_time);
   fChain->SetBranchAddress("DB4PPACDT.hit", &DB4PPACDT_hit, &b_rootout_DB4PPACDT_hit);
   fChain->SetBranchAddress("DB4PPACLT.fUniqueID", &DB4PPACLT_fUniqueID, &b_rootout_DB4PPACLT_fUniqueID);
   fChain->SetBranchAddress("DB4PPACLT.fBits", &DB4PPACLT_fBits, &b_rootout_DB4PPACLT_fBits);
   fChain->SetBranchAddress("DB4PPACLT.energy", &DB4PPACLT_energy, &b_rootout_DB4PPACLT_energy);
   fChain->SetBranchAddress("DB4PPACLT.ecal", &DB4PPACLT_ecal, &b_rootout_DB4PPACLT_ecal);
   fChain->SetBranchAddress("DB4PPACLT.time", &DB4PPACLT_time, &b_rootout_DB4PPACLT_time);
   fChain->SetBranchAddress("DB4PPACLT.hit", &DB4PPACLT_hit, &b_rootout_DB4PPACLT_hit);
   fChain->SetBranchAddress("DB4PPACRT.fUniqueID", &DB4PPACRT_fUniqueID, &b_rootout_DB4PPACRT_fUniqueID);
   fChain->SetBranchAddress("DB4PPACRT.fBits", &DB4PPACRT_fBits, &b_rootout_DB4PPACRT_fBits);
   fChain->SetBranchAddress("DB4PPACRT.energy", &DB4PPACRT_energy, &b_rootout_DB4PPACRT_energy);
   fChain->SetBranchAddress("DB4PPACRT.ecal", &DB4PPACRT_ecal, &b_rootout_DB4PPACRT_ecal);
   fChain->SetBranchAddress("DB4PPACRT.time", &DB4PPACRT_time, &b_rootout_DB4PPACRT_time);
   fChain->SetBranchAddress("DB4PPACRT.hit", &DB4PPACRT_hit, &b_rootout_DB4PPACRT_hit);
   fChain->SetBranchAddress("DB5PPACULT.fUniqueID", &DB5PPACULT_fUniqueID, &b_rootout_DB5PPACULT_fUniqueID);
   fChain->SetBranchAddress("DB5PPACULT.fBits", &DB5PPACULT_fBits, &b_rootout_DB5PPACULT_fBits);
   fChain->SetBranchAddress("DB5PPACULT.energy", &DB5PPACULT_energy, &b_rootout_DB5PPACULT_energy);
   fChain->SetBranchAddress("DB5PPACULT.ecal", &DB5PPACULT_ecal, &b_rootout_DB5PPACULT_ecal);
   fChain->SetBranchAddress("DB5PPACULT.time", &DB5PPACULT_time, &b_rootout_DB5PPACULT_time);
   fChain->SetBranchAddress("DB5PPACULT.hit", &DB5PPACULT_hit, &b_rootout_DB5PPACULT_hit);
   fChain->SetBranchAddress("DB5PPACURT.fUniqueID", &DB5PPACURT_fUniqueID, &b_rootout_DB5PPACURT_fUniqueID);
   fChain->SetBranchAddress("DB5PPACURT.fBits", &DB5PPACURT_fBits, &b_rootout_DB5PPACURT_fBits);
   fChain->SetBranchAddress("DB5PPACURT.energy", &DB5PPACURT_energy, &b_rootout_DB5PPACURT_energy);
   fChain->SetBranchAddress("DB5PPACURT.ecal", &DB5PPACURT_ecal, &b_rootout_DB5PPACURT_ecal);
   fChain->SetBranchAddress("DB5PPACURT.time", &DB5PPACURT_time, &b_rootout_DB5PPACURT_time);
   fChain->SetBranchAddress("DB5PPACURT.hit", &DB5PPACURT_hit, &b_rootout_DB5PPACURT_hit);
   fChain->SetBranchAddress("DB5PPACDLT.fUniqueID", &DB5PPACDLT_fUniqueID, &b_rootout_DB5PPACDLT_fUniqueID);
   fChain->SetBranchAddress("DB5PPACDLT.fBits", &DB5PPACDLT_fBits, &b_rootout_DB5PPACDLT_fBits);
   fChain->SetBranchAddress("DB5PPACDLT.energy", &DB5PPACDLT_energy, &b_rootout_DB5PPACDLT_energy);
   fChain->SetBranchAddress("DB5PPACDLT.ecal", &DB5PPACDLT_ecal, &b_rootout_DB5PPACDLT_ecal);
   fChain->SetBranchAddress("DB5PPACDLT.time", &DB5PPACDLT_time, &b_rootout_DB5PPACDLT_time);
   fChain->SetBranchAddress("DB5PPACDLT.hit", &DB5PPACDLT_hit, &b_rootout_DB5PPACDLT_hit);
   fChain->SetBranchAddress("DB5PPACDRT.fUniqueID", &DB5PPACDRT_fUniqueID, &b_rootout_DB5PPACDRT_fUniqueID);
   fChain->SetBranchAddress("DB5PPACDRT.fBits", &DB5PPACDRT_fBits, &b_rootout_DB5PPACDRT_fBits);
   fChain->SetBranchAddress("DB5PPACDRT.energy", &DB5PPACDRT_energy, &b_rootout_DB5PPACDRT_energy);
   fChain->SetBranchAddress("DB5PPACDRT.ecal", &DB5PPACDRT_ecal, &b_rootout_DB5PPACDRT_ecal);
   fChain->SetBranchAddress("DB5PPACDRT.time", &DB5PPACDRT_time, &b_rootout_DB5PPACDRT_time);
   fChain->SetBranchAddress("DB5PPACDRT.hit", &DB5PPACDRT_hit, &b_rootout_DB5PPACDRT_hit);
   fChain->SetBranchAddress("NDB4PPACLT.fUniqueID", &NDB4PPACLT_fUniqueID, &b_rootout_NDB4PPACLT_fUniqueID);
   fChain->SetBranchAddress("NDB4PPACLT.fBits", &NDB4PPACLT_fBits, &b_rootout_NDB4PPACLT_fBits);
   fChain->SetBranchAddress("NDB4PPACLT.energy", &NDB4PPACLT_energy, &b_rootout_NDB4PPACLT_energy);
   fChain->SetBranchAddress("NDB4PPACLT.ecal", &NDB4PPACLT_ecal, &b_rootout_NDB4PPACLT_ecal);
   fChain->SetBranchAddress("NDB4PPACLT.time", &NDB4PPACLT_time, &b_rootout_NDB4PPACLT_time);
   fChain->SetBranchAddress("NDB4PPACLT.hit", &NDB4PPACLT_hit, &b_rootout_NDB4PPACLT_hit);
   fChain->SetBranchAddress("NDB4PPACRT.fUniqueID", &NDB4PPACRT_fUniqueID, &b_rootout_NDB4PPACRT_fUniqueID);
   fChain->SetBranchAddress("NDB4PPACRT.fBits", &NDB4PPACRT_fBits, &b_rootout_NDB4PPACRT_fBits);
   fChain->SetBranchAddress("NDB4PPACRT.energy", &NDB4PPACRT_energy, &b_rootout_NDB4PPACRT_energy);
   fChain->SetBranchAddress("NDB4PPACRT.ecal", &NDB4PPACRT_ecal, &b_rootout_NDB4PPACRT_ecal);
   fChain->SetBranchAddress("NDB4PPACRT.time", &NDB4PPACRT_time, &b_rootout_NDB4PPACRT_time);
   fChain->SetBranchAddress("NDB4PPACRT.hit", &NDB4PPACRT_hit, &b_rootout_NDB4PPACRT_hit);
   fChain->SetBranchAddress("pin01.fUniqueID", &pin01_fUniqueID, &b_rootout_pin01_fUniqueID);
   fChain->SetBranchAddress("pin01.fBits", &pin01_fBits, &b_rootout_pin01_fBits);
   fChain->SetBranchAddress("pin01.energy", &pin01_energy, &b_rootout_pin01_energy);
   fChain->SetBranchAddress("pin01.ecal", &pin01_ecal, &b_rootout_pin01_ecal);
   fChain->SetBranchAddress("pin01.time", &pin01_time, &b_rootout_pin01_time);
   fChain->SetBranchAddress("pin01.hit", &pin01_hit, &b_rootout_pin01_hit);
   fChain->SetBranchAddress("pin02.fUniqueID", &pin02_fUniqueID, &b_rootout_pin02_fUniqueID);
   fChain->SetBranchAddress("pin02.fBits", &pin02_fBits, &b_rootout_pin02_fBits);
   fChain->SetBranchAddress("pin02.energy", &pin02_energy, &b_rootout_pin02_energy);
   fChain->SetBranchAddress("pin02.ecal", &pin02_ecal, &b_rootout_pin02_ecal);
   fChain->SetBranchAddress("pin02.time", &pin02_time, &b_rootout_pin02_time);
   fChain->SetBranchAddress("pin02.hit", &pin02_hit, &b_rootout_pin02_hit);
   fChain->SetBranchAddress("sipm.fUniqueID", &sipm_fUniqueID, &b_rootout_sipm_fUniqueID);
   fChain->SetBranchAddress("sipm.fBits", &sipm_fBits, &b_rootout_sipm_fBits);
   fChain->SetBranchAddress("sipm.energy", &sipm_energy, &b_rootout_sipm_energy);
   fChain->SetBranchAddress("sipm.ecal", &sipm_ecal, &b_rootout_sipm_ecal);
   fChain->SetBranchAddress("sipm.time", &sipm_time, &b_rootout_sipm_time);
   fChain->SetBranchAddress("sipm.hit", &sipm_hit, &b_rootout_sipm_hit);
   fChain->SetBranchAddress("xscintB.fUniqueID", &xscintB_fUniqueID, &b_rootout_xscintB_fUniqueID);
   fChain->SetBranchAddress("xscintB.fBits", &xscintB_fBits, &b_rootout_xscintB_fBits);
   fChain->SetBranchAddress("xscintB.energy", &xscintB_energy, &b_rootout_xscintB_energy);
   fChain->SetBranchAddress("xscintB.ecal", &xscintB_ecal, &b_rootout_xscintB_ecal);
   fChain->SetBranchAddress("xscintB.time", &xscintB_time, &b_rootout_xscintB_time);
   fChain->SetBranchAddress("xscintB.hit", &xscintB_hit, &b_rootout_xscintB_hit);
   fChain->SetBranchAddress("xscintT.fUniqueID", &xscintT_fUniqueID, &b_rootout_xscintT_fUniqueID);
   fChain->SetBranchAddress("xscintT.fBits", &xscintT_fBits, &b_rootout_xscintT_fBits);
   fChain->SetBranchAddress("xscintT.energy", &xscintT_energy, &b_rootout_xscintT_energy);
   fChain->SetBranchAddress("xscintT.ecal", &xscintT_ecal, &b_rootout_xscintT_ecal);
   fChain->SetBranchAddress("xscintT.time", &xscintT_time, &b_rootout_xscintT_time);
   fChain->SetBranchAddress("xscintT.hit", &xscintT_hit, &b_rootout_xscintT_hit);
   fChain->SetBranchAddress("xpin1.fUniqueID", &xpin1_fUniqueID, &b_rootout_xpin1_fUniqueID);
   fChain->SetBranchAddress("xpin1.fBits", &xpin1_fBits, &b_rootout_xpin1_fBits);
   fChain->SetBranchAddress("xpin1.energy", &xpin1_energy, &b_rootout_xpin1_energy);
   fChain->SetBranchAddress("xpin1.ecal", &xpin1_ecal, &b_rootout_xpin1_ecal);
   fChain->SetBranchAddress("xpin1.time", &xpin1_time, &b_rootout_xpin1_time);
   fChain->SetBranchAddress("xpin1.hit", &xpin1_hit, &b_rootout_xpin1_hit);
   fChain->SetBranchAddress("xpin2.fUniqueID", &xpin2_fUniqueID, &b_rootout_xpin2_fUniqueID);
   fChain->SetBranchAddress("xpin2.fBits", &xpin2_fBits, &b_rootout_xpin2_fBits);
   fChain->SetBranchAddress("xpin2.energy", &xpin2_energy, &b_rootout_xpin2_energy);
   fChain->SetBranchAddress("xpin2.ecal", &xpin2_ecal, &b_rootout_xpin2_ecal);
   fChain->SetBranchAddress("xpin2.time", &xpin2_time, &b_rootout_xpin2_time);
   fChain->SetBranchAddress("xpin2.hit", &xpin2_hit, &b_rootout_xpin2_hit);
   fChain->SetBranchAddress("vetoR.fUniqueID", &vetoR_fUniqueID, &b_rootout_vetoR_fUniqueID);
   fChain->SetBranchAddress("vetoR.fBits", &vetoR_fBits, &b_rootout_vetoR_fBits);
   fChain->SetBranchAddress("vetoR.energy", &vetoR_energy, &b_rootout_vetoR_energy);
   fChain->SetBranchAddress("vetoR.ecal", &vetoR_ecal, &b_rootout_vetoR_ecal);
   fChain->SetBranchAddress("vetoR.time", &vetoR_time, &b_rootout_vetoR_time);
   fChain->SetBranchAddress("vetoR.hit", &vetoR_hit, &b_rootout_vetoR_hit);
   fChain->SetBranchAddress("vetoF.fUniqueID", &vetoF_fUniqueID, &b_rootout_vetoF_fUniqueID);
   fChain->SetBranchAddress("vetoF.fBits", &vetoF_fBits, &b_rootout_vetoF_fBits);
   fChain->SetBranchAddress("vetoF.energy", &vetoF_energy, &b_rootout_vetoF_energy);
   fChain->SetBranchAddress("vetoF.ecal", &vetoF_ecal, &b_rootout_vetoF_ecal);
   fChain->SetBranchAddress("vetoF.time", &vetoF_time, &b_rootout_vetoF_time);
   fChain->SetBranchAddress("vetoF.hit", &vetoF_hit, &b_rootout_vetoF_hit);
   fChain->SetBranchAddress("pid.fUniqueID", &pid_fUniqueID, &b_rootout_pid_fUniqueID);
   fChain->SetBranchAddress("pid.fBits", &pid_fBits, &b_rootout_pid_fBits);
   fChain->SetBranchAddress("pid.de1", &pid_de1, &b_rootout_pid_de1);
   fChain->SetBranchAddress("pid.de2", &pid_de2, &b_rootout_pid_de2);
   fChain->SetBranchAddress("pid.tof", &pid_tof, &b_rootout_pid_tof);
   fChain->SetBranchAddress("pid.scintScintTOF", &pid_scintScintTOF, &b_rootout_pid_scintScintTOF);
   fChain->SetBranchAddress("pid.time", &pid_time, &b_rootout_pid_time);
   fChain->SetBranchAddress("pid.xpos", &pid_xpos, &b_rootout_pid_xpos);
   fChain->SetBranchAddress("pid.ypos", &pid_ypos, &b_rootout_pid_ypos);
   fChain->SetBranchAddress("corr.fUniqueID", &corr_fUniqueID, &b_rootout_corr_fUniqueID);
   fChain->SetBranchAddress("corr.fBits", &corr_fBits, &b_rootout_corr_fBits);
   fChain->SetBranchAddress("corr.idyecal", &corr_idyecal, &b_rootout_corr_idyecal);
   fChain->SetBranchAddress("corr.itime", &corr_itime, &b_rootout_corr_itime);
   fChain->SetBranchAddress("corr.ide1", &corr_ide1, &b_rootout_corr_ide1);
   fChain->SetBranchAddress("corr.ide2", &corr_ide2, &b_rootout_corr_ide2);
   fChain->SetBranchAddress("corr.itof", &corr_itof, &b_rootout_corr_itof);
   fChain->SetBranchAddress("corr.dtimplant", &corr_dtimplant, &b_rootout_corr_dtimplant);
   fChain->SetBranchAddress("corr.ixpos", &corr_ixpos, &b_rootout_corr_ixpos);
   fChain->SetBranchAddress("corr.iypos", &corr_iypos, &b_rootout_corr_iypos);
   fChain->SetBranchAddress("corr.idychisq_single", &corr_idychisq_single, &b_rootout_corr_idychisq_single);
   fChain->SetBranchAddress("corr.idyE1real_single", &corr_idyE1real_single, &b_rootout_corr_idyE1real_single);
   fChain->SetBranchAddress("corr.idyE1cal_single", &corr_idyE1cal_single, &b_rootout_corr_idyE1cal_single);
   fChain->SetBranchAddress("corr.idyT1_single", &corr_idyT1_single, &b_rootout_corr_idyT1_single);
   fChain->SetBranchAddress("corr.idyE1steepness_single", &corr_idyE1steepness_single, &b_rootout_corr_idyE1steepness_single);
   fChain->SetBranchAddress("corr.idyE1decay_single", &corr_idyE1decay_single, &b_rootout_corr_idyE1decay_single);
   fChain->SetBranchAddress("corr.idychisq_double", &corr_idychisq_double, &b_rootout_corr_idychisq_double);
   fChain->SetBranchAddress("corr.idyE1real_double", &corr_idyE1real_double, &b_rootout_corr_idyE1real_double);
   fChain->SetBranchAddress("corr.idyE1cal_double", &corr_idyE1cal_double, &b_rootout_corr_idyE1cal_double);
   fChain->SetBranchAddress("corr.idyE1steepness_double", &corr_idyE1steepness_double, &b_rootout_corr_idyE1steepness_double);
   fChain->SetBranchAddress("corr.idyE1decay_double", &corr_idyE1decay_double, &b_rootout_corr_idyE1decay_double);
   fChain->SetBranchAddress("corr.idyT1_double", &corr_idyT1_double, &b_rootout_corr_idyT1_double);
   fChain->SetBranchAddress("corr.idyE2real_double", &corr_idyE2real_double, &b_rootout_corr_idyE2real_double);
   fChain->SetBranchAddress("corr.idyE2cal_double", &corr_idyE2cal_double, &b_rootout_corr_idyE2cal_double);
   fChain->SetBranchAddress("corr.idyE2steepness_double", &corr_idyE2steepness_double, &b_rootout_corr_idyE2steepness_double);
   fChain->SetBranchAddress("corr.idyE2decay_double", &corr_idyE2decay_double, &b_rootout_corr_idyE2decay_double);
   fChain->SetBranchAddress("corr.idyT2_double", &corr_idyT2_double, &b_rootout_corr_idyT2_double);
   fChain->SetBranchAddress("corr.idytdiffE1E2cal", &corr_idytdiffE1E2cal, &b_rootout_corr_idytdiffE1E2cal);
   fChain->SetBranchAddress("corr.ddyecal", &corr_ddyecal, &b_rootout_corr_ddyecal);
   fChain->SetBranchAddress("corr.dtime", &corr_dtime, &b_rootout_corr_dtime);
   fChain->SetBranchAddress("corr.dxpos", &corr_dxpos, &b_rootout_corr_dxpos);
   fChain->SetBranchAddress("corr.dypos", &corr_dypos, &b_rootout_corr_dypos);
   fChain->SetBranchAddress("corr.dde1", &corr_dde1, &b_rootout_corr_dde1);
   fChain->SetBranchAddress("corr.dde2", &corr_dde2, &b_rootout_corr_dde2);
   fChain->SetBranchAddress("corr.dtof", &corr_dtof, &b_rootout_corr_dtof);
   fChain->SetBranchAddress("corr.ddychisq_single", &corr_ddychisq_single, &b_rootout_corr_ddychisq_single);
   fChain->SetBranchAddress("corr.ddyE1real_single", &corr_ddyE1real_single, &b_rootout_corr_ddyE1real_single);
   fChain->SetBranchAddress("corr.ddyE1cal_single", &corr_ddyE1cal_single, &b_rootout_corr_ddyE1cal_single);
   fChain->SetBranchAddress("corr.ddyT1_single", &corr_ddyT1_single, &b_rootout_corr_ddyT1_single);
   fChain->SetBranchAddress("corr.ddyE1steepness_single", &corr_ddyE1steepness_single, &b_rootout_corr_ddyE1steepness_single);
   fChain->SetBranchAddress("corr.ddyE1decay_single", &corr_ddyE1decay_single, &b_rootout_corr_ddyE1decay_single);
   fChain->SetBranchAddress("corr.ddychisq_double", &corr_ddychisq_double, &b_rootout_corr_ddychisq_double);
   fChain->SetBranchAddress("corr.ddyE1real_double", &corr_ddyE1real_double, &b_rootout_corr_ddyE1real_double);
   fChain->SetBranchAddress("corr.ddyE1cal_double", &corr_ddyE1cal_double, &b_rootout_corr_ddyE1cal_double);
   fChain->SetBranchAddress("corr.ddyE1steepness_double", &corr_ddyE1steepness_double, &b_rootout_corr_ddyE1steepness_double);
   fChain->SetBranchAddress("corr.ddyE1decay_double", &corr_ddyE1decay_double, &b_rootout_corr_ddyE1decay_double);
   fChain->SetBranchAddress("corr.ddyT1_double", &corr_ddyT1_double, &b_rootout_corr_ddyT1_double);
   fChain->SetBranchAddress("corr.ddyE2real_double", &corr_ddyE2real_double, &b_rootout_corr_ddyE2real_double);
   fChain->SetBranchAddress("corr.ddyE2cal_double", &corr_ddyE2cal_double, &b_rootout_corr_ddyE2cal_double);
   fChain->SetBranchAddress("corr.ddyE2steepness_double", &corr_ddyE2steepness_double, &b_rootout_corr_ddyE2steepness_double);
   fChain->SetBranchAddress("corr.ddyE2decay_double", &corr_ddyE2decay_double, &b_rootout_corr_ddyE2decay_double);
   fChain->SetBranchAddress("corr.ddyT2_double", &corr_ddyT2_double, &b_rootout_corr_ddyT2_double);
   fChain->SetBranchAddress("corr.ddytdiffE1E2cal", &corr_ddytdiffE1E2cal, &b_rootout_corr_ddytdiffE1E2cal);
   fChain->SetBranchAddress("corr.ifrontch", &corr_ifrontch, &b_rootout_corr_ifrontch);
   fChain->SetBranchAddress("corr.ibackch", &corr_ibackch, &b_rootout_corr_ibackch);
   fChain->SetBranchAddress("corr.ddfrontch", &corr_ddfrontch, &b_rootout_corr_ddfrontch);
   fChain->SetBranchAddress("corr.ddbackch", &corr_ddbackch, &b_rootout_corr_ddbackch);
   fChain->SetBranchAddress("corr.flag", &corr_flag, &b_rootout_corr_flag);
   fChain->SetBranchAddress("corr.isdecay", &corr_isdecay, &b_rootout_corr_isdecay);
   fChain->SetBranchAddress("corr.isimplant", &corr_isimplant, &b_rootout_corr_isimplant);
   fChain->SetBranchAddress("corr.islightion", &corr_islightion, &b_rootout_corr_islightion);
   fChain->SetBranchAddress("corr.isdynovflnopins", &corr_isdynovflnopins, &b_rootout_corr_isdynovflnopins);
   fChain->SetBranchAddress("clover.fUniqueID", &clover_fUniqueID, &b_rootout_clover_fUniqueID);
   fChain->SetBranchAddress("clover.fBits", &clover_fBits, &b_rootout_clover_fBits);
   fChain->SetBranchAddress("clover.time[52]", clover_time, &b_rootout_clover_time);
   fChain->SetBranchAddress("clover.timecfd[52]", clover_timecfd, &b_rootout_clover_timecfd);
   fChain->SetBranchAddress("clover.cfdfailbit[52]", clover_cfdfailbit, &b_rootout_clover_cfdfailbit);
   fChain->SetBranchAddress("clover.timecal[52]", clover_timecal, &b_rootout_clover_timecal);
   fChain->SetBranchAddress("clover.energy[52]", clover_energy, &b_rootout_clover_energy);
   fChain->SetBranchAddress("clover.ecal[52]", clover_ecal, &b_rootout_clover_ecal);
   fChain->SetBranchAddress("clover.mult", &clover_mult, &b_rootout_clover_mult);
   fChain->SetBranchAddress("clover.timeab[13]", clover_timeab, &b_rootout_clover_timeab);
   fChain->SetBranchAddress("clover.timecalab[13]", clover_timecalab, &b_rootout_clover_timecalab);
   fChain->SetBranchAddress("clover.cfdfailbitab[13]", clover_cfdfailbitab, &b_rootout_clover_cfdfailbitab);
   fChain->SetBranchAddress("clover.ecalab[13]", clover_ecalab, &b_rootout_clover_ecalab);
   fChain->SetBranchAddress("clover.posmult[13]", clover_posmult, &b_rootout_clover_posmult);
   fChain->SetBranchAddress("clover.multab", &clover_multab, &b_rootout_clover_multab);
   fChain->SetBranchAddress("clover.hit", &clover_hit, &b_rootout_clover_hit);
   fChain->SetBranchAddress("labr.fUniqueID", &labr_fUniqueID, &b_rootout_labr_fUniqueID);
   fChain->SetBranchAddress("labr.fBits", &labr_fBits, &b_rootout_labr_fBits);
   fChain->SetBranchAddress("labr.energy[16]", labr_energy, &b_rootout_labr_energy);
   fChain->SetBranchAddress("labr.ecal[16]", labr_ecal, &b_rootout_labr_ecal);
   fChain->SetBranchAddress("labr.time[16]", labr_time, &b_rootout_labr_time);
   fChain->SetBranchAddress("labr.timecfd[16]", labr_timecfd, &b_rootout_labr_timecfd);
   fChain->SetBranchAddress("labr.cfdfailbit[16]", labr_cfdfailbit, &b_rootout_labr_cfdfailbit);
   fChain->SetBranchAddress("labr.timecal[16]", labr_timecal, &b_rootout_labr_timecal);
   fChain->SetBranchAddress("labr.mult", &labr_mult, &b_rootout_labr_mult);
   fChain->SetBranchAddress("labr.hit", &labr_hit, &b_rootout_labr_hit);
   /* fChain->SetBranchAddress("implantlist", &implantlist_, &b_implantlist_); */
   /* fChain->SetBranchAddress("implantlist.fUniqueID", &implantlist_fUniqueID, &b_implantlist_fUniqueID); */
   /* fChain->SetBranchAddress("implantlist.fBits", &implantlist_fBits, &b_implantlist_fBits); */
   /* fChain->SetBranchAddress("implantlist.de1", &implantlist_de1, &b_implantlist_de1); */
   /* fChain->SetBranchAddress("implantlist.de2", &implantlist_de2, &b_implantlist_de2); */
   /* fChain->SetBranchAddress("implantlist.tof", &implantlist_tof, &b_implantlist_tof); */
   /* fChain->SetBranchAddress("implantlist.scintScintTOF", &implantlist_scintScintTOF, &b_implantlist_scintScintTOF); */
   /* fChain->SetBranchAddress("implantlist.time", &implantlist_time, &b_implantlist_time); */
   /* fChain->SetBranchAddress("implantlist.xpos", &implantlist_xpos, &b_implantlist_xpos); */
   /* fChain->SetBranchAddress("implantlist.ypos", &implantlist_ypos, &b_implantlist_ypos); */
}

Bool_t Selector_60Co::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Selector_60Co_cxx
