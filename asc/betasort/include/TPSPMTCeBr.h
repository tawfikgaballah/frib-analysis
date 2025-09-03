/*
 * TPSPMTCeBr.h. Class definition for tracking event time.
 * Contains definitions for PSPMT unpacker and calibration
 * as well as PSPMT interaction position routines and 
 * trace fit handling.
 * 
 * Author: A. Chester
 *
 */

#ifndef TPSPMTCEBR_H
#define TPSPMTCEBR_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"

#include "Constants.h"

//class RootHitExtension;   // need to add explicitly

/*
 * PSPMT calibrator
 */
class TPSPMTCeBrCalibrator 
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
  double aoffset[nanodes_CeBr];
  double aslope[nanodes_CeBr];
  double athresh[nanodes_CeBr];
  double auld[nanodes_CeBr];
  double tdiffdynode[nanodes_CeBr];
  
public:
  void Initialize();
  void ReadCalFile(std::string);
  void ReadTimeCalFile(std::string);
};

/*
 * PSPMT class defintion
 */
class TPSPMTCeBr: public TObject
{
public:
  // dynode
  std::vector<UShort_t> dytrace; // by RSL

  // dynode
  std::vector<double> dyenergy;
  std::vector<double> dyecal;
  std::vector<double> dytime;
  unsigned int dytimecfd;
  int dycfdfailbit;
  int dyoverflow;
  int dymult;
  double dyenergies[16];
  double dytimes[16];

  double denergy_qdc;
 
  // fit information
  // single pulse
  std::vector<double> dychisq_single;
  std::vector<double> dyE1_single;
  double dyE1real_single;
  double dyE1cal_single; // dyE1real calibrated
  std::vector<double> dyT1_single;
  std::vector<double> dyoffset_single;
  std::vector<double> dyE1steepness_single; 
  std::vector<double> dyE1decay_single;
  // double pulse
  std::vector<double> dychisq_double;
  std::vector<double> dyE1_double;
  double dyE1real_double;
  double dyE1cal_double; // dyE1real calibrated
  std::vector<double> dyT1_double;
  std::vector<double> dyE1steepness_double;
  std::vector<double> dyE1decay_double;
  std::vector<double> dyE2_double;
  double dyE2real_double;
  double dyE2cal_double; // dyE2real calibrated
  std::vector<double> dyT2_double;
  std::vector<double> dyE2steepness_double;
  std::vector<double> dyE2decay_double;
  std::vector<double> dyoffset_double;

  double dytdiffE1E2; // in ADC samples
  double dytdiffE1E2cal; // in ns

  // Anode
  double aenergy[nanodes_CeBr];
  double aecal[nanodes_CeBr];
  double asum;
  double atime[nanodes_CeBr];
  double atimecal[nanodes_CeBr];
  int aoverflow[nanodes_CeBr];
  int aoverflowcount;  
  int amultraw;
  int amult;
  int pixelmult[nanodes_CeBr];
  // Anode linearlized position fit parameters
  double lxamp;   // amplitude of 1D fit
  double lxpos;   // x-position from 2D fit
  double lxgamma; // lorentzian gamma in x
  double lyamp;   // amplitude of 1D fit
  double lypos;   // y-position from 2D fit
  double lygamma; // lorentzian gamma in y

  // hit flags
  int dyhit;
  int ahit[nanodes_CeBr];
  int hit; // dynode and at least one anode
  
  void Reset();
  void UnpackDynode(ddastoys::DDASRootFitHit* ddashit, TRandom3 &rng, TPSPMTCeBrCalibrator &cal);
  void UnpackDynodeFit(ddastoys::DDASRootFitHit* ddashit, TPSPMTCeBrCalibrator &cal, int i);
  void UnpackAnode(ddastoys::DDASRootFitHit* ddashit, TRandom3 &rng, TPSPMTCeBrCalibrator &cal, int pix);
  void FitAnodePosition();

  ClassDef(TPSPMTCeBr,2);
};

#endif
