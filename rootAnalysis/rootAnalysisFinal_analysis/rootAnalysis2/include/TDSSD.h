/*
 * TDSSD.h. Class definition for tracking event time.
 * Contains definitions for DSSD unpacker and calibration.
 * 
 * Author: A. Chester
 *
 */

#ifndef TDSSD_H
#define TDSSD_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"

#include "Constants.h"

/*
 * DSSD calibrator
 */
class TDSSDCalibrator 
{
public:
  // high gain
  double hioffset[ndssd];
  double hislope[ndssd];
  double hithresh[ndssd];
  double hiuld[ndssd];

  // low gain
  double looffset[ndssd];
  double loslope[ndssd];
  double lothresh[ndssd];
  double lould[ndssd];

  void Initialize();
  void ReadCalFile(std::string);
};

/*
 * DSSD class defintion
 */
class TDSSD: public TObject
{
public:
  // high gain
  double hienergy[ndssd];
  double hiecal[ndssd];
  double hitime[ndssd];
  
  // low gain
  double loenergy[ndssd];
  double loecal[ndssd];
  double lotime[ndssd];

  // implanted ion information
  double imax;
  double imaxtime;
  int imaxch;
  int imult;

  // decay information
  double dmax;
  double dmaxtime;
  int dmaxch;
  int dmult;
  
  void Reset();
  void Unpack(DDASRootFitHit* chanhit, TRandom3 &rng, TDSSDCalibrator &cal);

  ClassDef(TDSSD,2);
};

#endif
