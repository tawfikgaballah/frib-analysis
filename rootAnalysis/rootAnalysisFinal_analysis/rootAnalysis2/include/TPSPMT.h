/*
 * TPSPMT.h. Class definition for tracking event time.
 * Contains definitions for PSPMT unpacker and calibration
 * as well as PSPMT interaction position routines and 
 * trace fit handling.
 * 
 * Author: A. Chester
 *
 */

#ifndef TPSPMT_H
#define TPSPMT_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"

#include "Constants.h"

class RootHitExtension;   // need to add explicitly

/*
 * PSPMT calibrator
 */
class TPSPMTCalibrator 
{
public:
  // dynode
  double dyoffset;
  double dyslope;
  double dyfitoffset;
  double dyfitslope;
  double dyclockcal;
  double dythresh;
  double dyuld;
  double dycoincwindow;

  // anodes
  double aoffset[nanodes];
  double aslope[nanodes];
  double athresh[nanodes];
  double auld[nanodes];
  double tdiffdynode[nanodes];
  
public:
  void Initialize();
  void ReadCalFile(std::string);
  void ReadTimeCalFile(std::string);
};

/*
 * PSPMT class defintion
 */
class TPSPMT: public TObject
{
public:
  // dynode
  double dyenergy;
  double dyecal;
  double dytime;
  unsigned int dytimecfd;
  int dycfdfailbit;
  int dyoverflow;
  int dymult;
  
  // fit information
  // single pulse
  double dychisq_single;
  double dyE1_single;
  double dyE1real_single;
  double dyE1cal_single; // dyE1real calibrated
  double dyT1_single;
  double dyoffset_single;
  double dyE1steepness_single; 
  double dyE1decay_single;
  // double pulse
  double dychisq_double;
  double dyE1_double;
  double dyE1real_double;
  double dyE1cal_double; // dyE1real calibrated
  double dyT1_double;
  double dyE1steepness_double;
  double dyE1decay_double;
  double dyE2_double;
  double dyE2real_double;
  double dyE2cal_double; // dyE2real calibrated
  double dyT2_double;
  double dyE2steepness_double;
  double dyE2decay_double;
  double dyoffset_double;
  double dytdiffE1E2; // in ADC samples
  double dytdiffE1E2cal; // in ns

  // Anode
  double aenergy[nanodes];
  double aecal[nanodes];
  double asum;
  double atime[nanodes];
  double atimecal[nanodes];
  int aoverflow[nanodes];
  int aoverflowcount;  
  int amultraw;
  int amult;
  int pixelmult[nanodes];
  // Anode linearlized position fit parameters
  double lxamp;   // amplitude of 1D fit
  double lxpos;   // x-position from 2D fit
  double lxgamma; // lorentzian gamma in x
  double lyamp;   // amplitude of 1D fit
  double lypos;   // y-position from 2D fit
  double lygamma; // lorentzian gamma in y

  // hit flags
  int dyhit;
  int ahit[nanodes];
  int hit; // dynode and at least one anode
  
  void Reset();
  void UnpackDynode(DDASRootFitHit* ddashit, TRandom3 &rng, TPSPMTCalibrator &cal);
  void UnpackDynodeFit(TPSPMTCalibrator &cal, std::vector<RootHitExtension> &fits);
  void UnpackAnode(DDASRootFitHit* ddashit, TRandom3 &rng, TPSPMTCalibrator &cal, int pix);
  void FitAnodePosition();

  ClassDef(TPSPMT,2);
};

#endif
