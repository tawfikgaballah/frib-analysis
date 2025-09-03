/*
 * TPID.cpp. Class methods PID variables which are 
 * derived from dE measurements in an upstream PIN
 * detector and some measure of TOF throught the 
 * fragment separator. 
 * 
 * Author: A. Chester
 *
 */

#include "TPID.h"

ClassImp(TPID);

//
// Reset PID variables
//
void TPID::Reset()
{
  // PIN dE
  de1 = 0.;
  de2 = 0.;
  // TOF
  tof = 0.;
  scintScintTOF = 0.;
 
  // Correlation variables
  time = 0.;
  xpos = -1;
  ypos = -1;

}

  
