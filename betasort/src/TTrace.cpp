/*
 * TClock.cpp. Class methods for tracking event time.
 * Calibration methods and parameters for DDAS clock.
 * 
 * Author: A. Chester
 *
 */

#include "TTrace.h"

ClassImp(TTrace);

/*
 * Clears trace vector
 */
void TTrace::Reset()
{
  trace.clear();
}
