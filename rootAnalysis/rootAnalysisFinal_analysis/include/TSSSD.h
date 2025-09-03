/*
 * TSSSD.h. Class definition for tracking event time.
 * Contains definitions for SSSD unpacker and calibration.
 * 
 * Author: A. Chester
 *
 */

#ifndef TSSSD_H
#define TSSSD_H

#include "DDASRootFitHit.h"

#include "TObject.h"
#include "TRandom3.h"

#include "Constants.h"

/*
 * SSSD calibrator
 */
class TSSSDCalibrator 
{
public:
  // high gain
  double hioffset[nsssd];
  double hislope[nsssd];
  double hithresh[nsssd];
  double hiuld[nsssd];
 
  // low gain
  double looffset[nsssd];
  double loslope[nsssd];
  double lothresh[nsssd];
  double lould[nsssd];

  void Initialize();
  void ReadCalFile(std::string);
};

/*
 * SSSD class defintion
 */
class TSSSD: public TObject
{
public:
  // high gain
  double hienergy[nsssd];
  double hiecal[nsssd];
  double hitime[nsssd];
  double himax;
  double himaxtime;
  int himaxch;
  int himult;  
  
  // low gain
  double loenergy[nsssd];
  double loecal[nsssd];
  double lotime[nsssd];
  double lomax;
  double lomaxtime;
  int lomaxch;
  int lomult;
  
  void Reset();
  void Unpack(DDASRootFitHit* chanhit, TRandom3 &rng, TSSSDCalibrator &cal);

  ClassDef(TSSSD,2);
};

#endif
