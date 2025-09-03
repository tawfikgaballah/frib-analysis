/*
 * TTAC.h. Class definition for TACs.
 * Calibration methods and parameters for DDAS clock.
 * 
 * Author: A. Chester
 *
 */

#ifndef TTAC_H
#define TTAC_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"

/*
 * TAC calibrator
 */
class TTACCalibrator
{
public:
  double corr; // slope for TOF momentum spread correction
  double offset; // offset for TOF momentum spread correction
  double thresh;
  double uld;

  void Initialize();
  void ReadCalFile(std::string name);
};

/*
 * TAC class definition
 */
class TTAC: public TObject
{
public:
  double energy; // time of flight is proportional to "energy" from TAC
  double time; // time of the signal, not the time of flight
  double hit;
  
  void Reset();
  void Unpack(ddastoys::DDASRootFitHit* ddashit, TRandom3 &rng, TTACCalibrator &cal);

  ClassDef(TTAC,2);
};

#endif
