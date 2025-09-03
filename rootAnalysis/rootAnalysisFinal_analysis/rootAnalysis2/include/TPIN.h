/*
 * TPIN.h. Class definition for tracking event time.
 * Contains definitions for PIN unpacker and calibration.
 * 
 * Author: A. Chester
 *
 */

#ifndef TPIN_H
#define TPIN_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"

/*
 * PIN calibrator
 */
class TPINCalibrator 
{
public:
  double slope;
  double intercept;
  double thresh;
  double ithresh;
  double uld;

  void Initialize();
  void ReadCalFile(std::string);
};

/*
 * PIN class defintion
 */
class TPIN: public TObject
{
public:
  double energy;
  double ecal;
  double time;
  int hit;
  
  void Reset();
  void Unpack(DDASRootFitHit* chanhit, TRandom3 &rng, TPINCalibrator &cal, Bool_t goCFD);

  ClassDef(TPIN,2);
};

#endif
