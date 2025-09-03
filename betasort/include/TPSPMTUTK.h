/*
 * TPSPMTUTK.h. Class definition for tracking event time.
 * Contains definitions for PSPMTUTK unpacker and calibration
 * as well as PSPMTUTK interaction position routines and 
 * trace fit handling.
 * 
 * Author: A. Chester
 *
 */

#ifndef TPSPMTUTK_H
#define TPSPMTUTK_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"
#include "TGraph2D.h"

#include "Constants.h"

/*
 * PSPMTUTK calibrator
 */
class TPSPMTUTKCalibrator 
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
  TGraph2D *corr_surface[2];

  // anodes
  double aoffset[nanodes_utk];
  double aslope[nanodes_utk];
  double athresh[nanodes_utk];
  double auld[nanodes_utk];
  double tdiffdynode[nanodes_utk];
  
  void Initialize();
  void ReadCalFile(std::string);
  void ReadTimeCalFile(std::string);
  void ReadCorrFile(bool gain);
};

/*
 * PSPMTUTK class defintion
 */
class TPSPMTUTK: public TObject
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
  double aenergy[nanodes_utk];
  double aecal[nanodes_utk];
  double aenergy_qdc[nanodes_utk];
  double asum;
  double asum_qdc;
  double atime[nanodes_utk];
  double atimecal[nanodes_utk];
  int aoverflow[nanodes_utk];
  int aoverflowcount;  
  int amultraw;
  int amult;
  int pixelmult[nanodes_utk];
  // Anode position
  double xpos;
  double ypos;
  double xcal;
  double ycal;


  // hit flags
  int dyhit;
  int ahit[nanodes_utk];
  int hit; // dynode and at least one anode
  int gain;  

  void Reset();
  void UnpackDynode(ddastoys::DDASRootFitHit* ddashit, TRandom3 &rng, TPSPMTUTKCalibrator &cal);
  void UnpackDynodeFit(ddastoys::DDASRootFitHit* ddashit, TPSPMTUTKCalibrator &cal, int i);
  void UnpackAnode(ddastoys::DDASRootFitHit* ddashit, TRandom3 &rng, TPSPMTUTKCalibrator &cal, int pix);
  double Position_Correction(TPSPMTUTKCalibrator &cal, double input_pos, double input_energy, int axis);
  void FitAnodePosition(TPSPMTUTKCalibrator &cal);

  ClassDef(TPSPMTUTK,2);
};

#endif
