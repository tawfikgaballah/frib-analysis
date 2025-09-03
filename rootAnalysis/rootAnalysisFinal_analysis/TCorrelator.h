#ifndef TCORRELATOR_H
#define TCORREALTOR_H
#include "TCutG.h"
#include <vector>

#include "TParameters.h"
#include "Constants.h"
#include "TFile.h"
#include "TCutG.h"
class TImplant
{
 public:
  bool implanted;
  double dyecal;    // Dynode energy
  double time;      // Time of event
  double de1;       // dE from Pin01
  double de2;       // dE from Pin02
  double tof;       // Time of flight
  double scintScintTOF; // TOF
  double dtLastIon; // Time since last implant

  // Trace fit information
  double dychisq_single;
  double dyE1real_single;
  double dyE1cal_single;
  double dyE1steepness_single;
  double dyE1decay_single;
  double dyT1_single;
  double dychisq_double;
  double dyE1real_double;
  double dyE1cal_double;
  double dyE1steepness_double;
  double dyE1decay_double;
  double dyT1_double;
  double dyE2real_double;
  double dyE2cal_double;
  double dyE2steepness_double;
  double dyE2decay_double;
  double dyT2_double;
  double dytdiffE1E2cal;

  // interaction position
  double xpos;
  double ypos;
  
  
   
  TImplant& operator=(const TImplant& rhs)
    {
      implanted = rhs.implanted;
      time = rhs.time;
      de1 = rhs.de1;
      de2 = rhs.de2;
      tof = rhs.tof;
      scintScintTOF = rhs.scintScintTOF;
      dyecal = rhs.dyecal;
      dtLastIon = rhs.dtLastIon;
      // Trace fit information
      dychisq_single = rhs.dychisq_single;
      dyE1real_single = rhs.dyE1real_single;
      dyE1cal_single = rhs.dyE1cal_single;
      dyE1steepness_single = rhs.dyE1steepness_single;
      dyE1decay_single = rhs.dyE1decay_single;
      dyT1_single = rhs.dyT1_single;
      dychisq_double = rhs.dychisq_double;
      dyE1real_double = rhs.dyE1real_double;
      dyE1cal_double = rhs.dyE1cal_double;
      dyE1steepness_double = rhs.dyE1steepness_double;
      dyE1decay_double = rhs.dyE1decay_double;
      dyT1_double = rhs.dyT1_double;
      dyE2real_double = rhs.dyE2real_double;
      dyE2cal_double = rhs.dyE2cal_double;
      dyE2steepness_double = rhs.dyE2steepness_double;
      dyE2decay_double = rhs.dyE2decay_double;
      dyT2_double = rhs.dyT2_double;
      dytdiffE1E2cal = rhs.dytdiffE1E2cal;
      xpos = rhs.xpos;
      ypos = rhs.ypos;
      return *this;
    }
  
  void Reset();
};

// Correlator setup
class TCorrelator
{
 public:
  TCorrelator();
  void Reset();
  int Correlate(TBetaDecayParams &bdecay, std::string beta_gate, std::string tofv, std::string corrflow);
  void clearImplants() { fCorrelatedImplants.clear(); }
  std::vector<TPID> getImplants() { return fCorrelatedImplants; }



 private:
  TImplant fImplant[npspmt_utk][npspmt_utk];
  std::vector<TImplant> fImplantVector[npspmt_utk][npspmt_utk];
  const int fCorrWin = 11; // Correlation window size in mm
  std::vector<TPID> fCorrelatedImplants;

     
};

#endif
