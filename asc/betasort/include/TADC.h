/*
 * TADC.h. Class definition for sotrage of ADC data.
 * 
 * Author: A. Chester
 *
 */

#ifndef TADC_H
#define TADC_H

#include "TObject.h"

#include "Constants.h"
#include "TTrace.h"

/*
 * DDAS ADC class definition
 */ 
class TADC: public TObject
{
 public:
  unsigned int energy[nchannels];
  double timefull[nchannels];
  unsigned int timecfd[nchannels];
  int cfdfailbit[nchannels]; // 0 for good cfd, 1 for fail
int channel[nchannels];  // by RSL
  TTrace chantrace[nchannels];  
  
  void Reset();
  
  ClassDef(TADC,2);
};

#endif
