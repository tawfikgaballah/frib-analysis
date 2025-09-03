/*
 * TCorrelation.cpp. Class methods for correlation algorithm.
 * Data storage for correlated variables and event classification.
 * 
 * Author: A. Chester
 *
 */

#include "TCorrelation.h"

#include <iostream>
#include <fstream>

ClassImp(TCorrelation);

/*
 * Default calibration parameters
 */
void TCorrelationCalibrator::Initialize()
{
  reset = 1; // reset correlator on first pass
  corrwindow = 100.0; // ms
  minimplant = 50.;  // ms
}

//
// ReadCalFile
//
// Function:
//   - reads detector calibration file
//
// Params:
//   - calibration file name as a std::string
//
// Return:
//   - none
//
void TCorrelationCalibrator::ReadCalFile(std::string name)
{
  std::cout << "Reading Correlator calibration from: " << name << std::endl;
  
  std::ifstream calfile(name.c_str());
  int linenum = 0;
  double value = 0;
 
  if(!calfile) {
    std::cout << "----> Unable to open file " << name << std::endl;
  } else {
    //read in cal file until end of file
    while(calfile) {
      if(calfile && (isdigit(calfile.peek()))) {
	linenum++;
	calfile >> value;	      
	if(linenum == 1) corrwindow = value;
	if(linenum == 2) minimplant = value;
      } else {
	calfile.ignore(1000,'\n');
      }
    } 
  }  
  calfile.close();
}

/*
 * Reset correlator 
 */
void TCorrelation::Reset()
{
  // Implants
  idyecal = 0.;
  itime = 0.;
  ide1 = 0.;
  ide2 = 0.;
  dtimplant = 0.;
  ixpos = -1.;
  iypos = -1.;
  isreverse=-1.;
  isforward=-1.;
  // Trace fit information for implants
  idychisq_single = 0.;
  idyE1real_single = 0.;
  idyE1cal_single = 0.;
  idyT1_single = 0.;
  idyE1steepness_single = 0.;
  idyE1decay_single = 0.;
  idychisq_double = 0.;
  idyE1real_double = 0.;
  idyE1cal_double = 0.;
  idyE1steepness_double = 0.;
  idyE1decay_double = 0.;
  idyT1_double = 0.;
  idyE2real_double = 0.;
  idyE2cal_double = 0.;
  idyE2steepness_double = 0.;
  idyE2decay_double = 0.;
  idyT2_double = 0.;
  idytdiffE1E2cal = 0.;

  // Decays
  ddyecal = 0.;
  dtime = 0.;
  dxpos = -1.;
  dypos = -1.;

// Alternatives to build the PID by RSL
  dde1 = 0.;
  dde2 = 0.;
  dtof = 0.;
// Alternatives to build the PID by RSL

radius.resize(0);
decaytime.resize(0);

 
  // Trace fit information
  ddychisq_single = 0.;
  ddyE1real_single = 0.;
  ddyE1cal_single = 0.;
  ddyT1_single = 0.;
  ddyE1steepness_single = 0.;
  ddyE1decay_single = 0.;
  ddychisq_double = 0.;
  ddyE1real_double = 0.;
  ddyE1cal_double = 0.;
  ddyE1steepness_double = 0.;
  ddyE1decay_double = 0.;
  ddyT1_double = 0.;
  ddyE2real_double = 0.;
  ddyE2cal_double = 0.;
  ddyE2steepness_double = 0.;
  ddyE2decay_double = 0.;
  ddyT2_double = 0.;
  ddytdiffE1E2cal = 0.;

  // Gamma-only
  giscorr = false;
  gtof = 0;
  gde2 = 0;
  gitime = 0;
  gtime = 0;
  gitdiff = 0;
  
  // DSSD/SSSD specific
  ifrontch = -1; // all implant positions
  ibackch = -1;
  ddfrontch = -1; // all decay positions
  ddbackch = -1;
   
  // event type identifiers
  flag = 0;
  isdecay = 0;
  isimplant = 0;
  islightion = 0;
  hasclover = 0;
  haslabr = 0;
  islabronly = 0;
  isdynovflnopins = 0;
}
