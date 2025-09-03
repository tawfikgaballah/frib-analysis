/*
 * TADC.cpp. Class methods for DDAS ADCs.
 * 
 * Author: A. Chester
 *
 */

#include "TADC.h"

ClassImp(TADC);

/*
 * Reset ADC variables
 */
void TADC::Reset()
{
  std::fill(std::begin(energy),std::end(energy),0);
  std::fill(std::begin(timefull),std::end(timefull),0.);
  std::fill(std::begin(timecfd),std::end(timecfd),0);
  std::fill(std::begin(cfdfailbit),std::end(cfdfailbit),0);
  std::fill(std::begin(channel),std::end(channel),0);
  
  for(int i=0; i<nchannels; i++)
    chantrace[i].Reset();
}
