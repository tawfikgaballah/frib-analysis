/*
 * TClover.h. Class definition for Clover detectors.
 * Contains definitions for Clover unpacker and calibration.
 * 
 * Author: A. Chester
 *
 */

#ifndef TCLOVER_H
#define TCLOVER_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"

#include "Constants.h"

/*
 * Clover calibrator
 */
class TCloverCalibrator 
{
public:
  double square[totcrystals];
  double slope[totcrystals];
  double intercept[totcrystals];
  double thresh[totcrystals];
  double uld[totcrystals];
  double tdiffdynode[totcrystals];

  void Initialize();
  void ReadCalFile(std::string);
  void UpdateCalFile(std::string);
  void ReadTimeCalFile(std::string);
};

/*
 * Clover class defintion
 */
class TClover: public TObject
{
public:
  double time[totcrystals];
  unsigned int timecfd[totcrystals];
  int cfdfailbit[totcrystals];
  double timecal[totcrystals];
  double energy[totcrystals];
  double ecal[totcrystals];
  int mult;

  // Simple add-back (no crosstalk corrections)
  double timeab[nclovers];
  double timecalab[nclovers];
  int cfdfailbitab[nclovers]; // OR of all cfdfailbits
  double ecalab[nclovers];
  int posmult[nclovers];
  int multab;

  int hit;
   
  void Reset();
  void Unpack(ddastoys::DDASRootFitHit* chanhit, TRandom3 &rng, TCloverCalibrator &cal, int det);
  void AddBack();

  ClassDef(TClover,2);
};

#endif
