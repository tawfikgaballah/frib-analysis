/*
 * TSeGA.h. Class definition for SeGA detectors.
 * Contains definitions for SeGA unpacker and calibration.
 * 
 * Author: A. Chester
 *
 */

#ifndef TSEGA_H
#define TSEGA_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"

#include "Constants.h"

/*
 * SeGA calibrator
 */
class TSeGACalibrator 
{
public:
  double square[nsega];
  double slope[nsega];
  double intercept[nsega];
  double thresh[nsega];
  double uld[nsega];
  double tdiffdynode[nsega];

  void Initialize();
  void ReadCalFile(std::string);
  void ReadTimeCalFile(std::string);
};

/*
 * SeGA class defintion
 */
class TSeGA: public TObject
{
private:
  
public:
  double energy[nsega];
  double ecal[nsega];
  double time[nsega];
  unsigned int timecfd[nsega];
  int cfdfailbit[nsega];
  double timecal[nsega];
  int mult;
  int hit;
   
  void Reset();
  void Unpack(ddastoys::DDASRootFitHit* chanhit, TRandom3 &rng, TSeGACalibrator &cal, int det);

  ClassDef(TSeGA,2);
};

#endif
