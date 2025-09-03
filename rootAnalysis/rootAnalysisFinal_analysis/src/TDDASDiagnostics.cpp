/*
 * TDDASDiagnostics.cpp. Class methods for tracking basic event diagnostics.
 * 
 * Author: A. Chester
 *
 */

#include "TDDASDiagnostics.h"

ClassImp(TDDASDiagnostics);

/*
 * Reset diagnostic variables
 */
void TDDASDiagnostics::Reset()
{
  cmult = 0;
  eventlength = 0.;
  tdiffevent = 0.;
  chanhit.clear();
}
