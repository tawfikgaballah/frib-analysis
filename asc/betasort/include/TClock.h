/*
 * TClock.h. Class definition for tracking event time.
 * Calibration methods and parameters for DDAS clock.
 * 
 * Author: A. Chester
 *
 */

#ifndef TCLOCK_H
#define TCLOCK_H

#include "TObject.h"

/*
 * DDAS clock class definition
 */
class TClock: public TObject
{
public:
  double  current;
  double  initial;

  void Reset();

  ClassDef(TClock,2);
};

/*
 * DDAS clock calibrator
 */
class TClockCalibrator
{  
public:
  double calib; // convert raw clock to ns
  
  void Initialize();
};

#endif
