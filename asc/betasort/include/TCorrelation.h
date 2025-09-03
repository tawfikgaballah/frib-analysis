/*
 * TCorrelation.h. Class definition for tracking event time.
 * Calibration methods and parameters for DDAS clock.
 * 
 * Author: A. Chester
 *
 */

#ifndef TCORRELATION_H
#define TCORRELATION_H

#include "TObject.h"

/*
 * Correlation calibrator
 */
class TCorrelationCalibrator
{  
public:  
  int reset;
  double corrwindow;
  double minimplant;
  
  void Initialize();
  void ReadCalFile(std::string name);
};

/*
 * Correlation class definition
 */
class TCorrelation: public TObject
{
public:
  // Implants
  double idyecal;
  double itime;
  double ide1;
  double ide2;
  double itof;
  double dtimplant;
  double ixpos;
  double iypos;
  // Trace fit information for implants
  double idychisq_single;
  double idyE1real_single;
  double idyE1cal_single;
  double idyT1_single;
  double idyE1steepness_single;
  double idyE1decay_single;
  double idychisq_double;
  double idyE1real_double;
  double idyE1cal_double;
  double idyE1steepness_double;
  double idyE1decay_double;
  double idyT1_double;
  double idyE2real_double;
  double idyE2cal_double;
  double idyE2steepness_double;
  double idyE2decay_double;
  double idyT2_double;
  double idytdiffE1E2cal;

  // Decays
  double ddyecal;
  double dtime;
  double dxpos;
  double dypos;

// Alternatives to build the PID by RSL
  double dde1;
  double dde2;
  double dtof;
	double dixpos;
	double diypos;
	double ditime;
// Alternatives to build the PID by RSL  

  // Trace fit information
  double ddychisq_single;
  double ddyE1real_single;
  double ddyE1cal_single;
  double ddyT1_single;
  double ddyE1steepness_single;
  double ddyE1decay_single;
  double ddychisq_double;
  double ddyE1real_double;
  double ddyE1cal_double;
  double ddyE1steepness_double;
  double ddyE1decay_double;
  double ddyT1_double;
  double ddyE2real_double;
  double ddyE2cal_double;
  double ddyE2steepness_double;
  double ddyE2decay_double;
  double ddyT2_double;
  double ddytdiffE1E2cal;
 
  // Gamma-only 
  double giscorr;  // I think this should almost always be true
  double gtof;  //tof of ion correlated with the gammas from that event
  double gde2;  //de2 of ion correlated with the gammas from that event
  double gitime;  //time of pin hit for correlated ion
  double gtime;  //time of clover hit
  double gitdiff; //time difference between gamma and correlated ion


  // DSSD/SSSD specific
  int ifrontch; // all implant positions
  int ibackch;
  int ddfrontch; // all decay positions
  int ddbackch;
  
  // event type identifiers
  int flag;
  int isdecay;
  int hasclover;
  int iscloveronly;
  int isimplant;
  int islightion;
  int isdynovflnopins;
  
  void Reset();

  ClassDef(TCorrelation,2);
};

#endif
