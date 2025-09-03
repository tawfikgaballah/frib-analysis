/*
 * TLaBr3.h. Class definition for LaBr3 detectors.
 * Contains definitions for LaBr3 unpacker and calibration.
 * 
 * Author: A. Chester
 *
 */

#ifndef TLABR3_H
#define TLABR3_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"

#include "Constants.h"

/*
 * LaBr3 calibrator
 */
class TLaBr3Calibrator 
{
public:
  double square[nlabr3];
  double slope[nlabr3];
  double intercept[nlabr3];
  double thresh[nlabr3];
  double uld[nlabr3];
  double tdiffdynode[nlabr3];

  void Initialize();
  void ReadCalFile(std::string);
  void ReadTimeCalFile(std::string);
};

/*
 * LaBr3 class defintion
 */
class TLaBr3: public TObject
{
public:
  double energy[nlabr3];
  double ecal[nlabr3];
  double time[nlabr3];
  unsigned int timecfd[nlabr3];
  int cfdfailbit[nlabr3];
  double timecal[nlabr3];
  int mult;
  int hit;
   
  void Reset();
  void Unpack(DDASRootFitHit* chanhit, TRandom3 &rng, TLaBr3Calibrator &cal, int det);

  ClassDef(TLaBr3,2);
};

#endif
