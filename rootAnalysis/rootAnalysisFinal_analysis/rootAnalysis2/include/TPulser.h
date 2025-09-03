/*
 * TPulser.h. Class definition test analysis with a pulser. 
 * Incorporatres trace fitting as well to run "full" analysis.
 * 
 * Author: A. Chester
 *
 */

#ifndef TPULSER_H
#define TPULSER_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"

#include "Constants.h"

class RootHitExtension;   // need to add explicitly

/*
 * Pulser calibrator
 */
class TPulserCalibrator 
{
public:
  double offset;
  double slope;
  double fitoffset;
  double fitslope;
  double clockcal;
  double thresh;
  double uld;
  
  void Initialize();
};

/*
 * Pulser class defintion
 */
class TPulser: public TObject
{
public:
  // dynode
  double energy;
  double ecal;
  double time;
  unsigned int timecfd;
  int cfdfailbit;
  int overflow;
  int mult;
 
  // fit information
  // single pulse
  double chisq_single;
  double E1_single;
  double E1real_single;
  double E1cal_single; // E1real calibrated
  double T1_single;
  double offset_single;
  double E1steepness_single; 
  double E1decay_single;
  // double pulse
  double chisq_double;
  double E1_double;
  double E1real_double;
  double E1cal_double; // E1real calibrated
  double T1_double;
  double E1steepness_double;
  double E1decay_double;
  double E2_double;
  double E2real_double;
  double E2cal_double; // E2real calibrated
  double T2_double;
  double E2steepness_double;
  double E2decay_double;
  double offset_double;
  double tdiffE1E2; // in ADC samples
  double tdiffE1E2cal; // in ns

  // hit flags
  int hit;
  
  void Reset();
  void Unpack(DDASRootFitHit* ddashit, TRandom3 &rng, TPulserCalibrator &cal);
  void UnpackFit(TPulserCalibrator &cal, std::vector<RootHitExtension> &fits);

  ClassDef(TPulser,2);
};

#endif
