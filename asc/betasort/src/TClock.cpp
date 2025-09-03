/*
 * TClock.cpp. Class methods for tracking event time.
 * Calibration methods and parameters for DDAS clock.
 * 
 * Author: A. Chester
 *
 */

#include "TClock.h"

ClassImp(TClock);

/*
 * Reset clock variables
 */
void TClock::Reset()
{
  current = 0.;
  initial = 0.;
}

/*
 * Default calibration parameters
 */
void TClockCalibrator::Initialize()
{
  calib = 1.; // assumes clock is ns
}
