/*
 * TModule.h. Class definition for DDAS Pixie16 modules
 * 
 * Author: A. Chester
 *
 */

#ifndef TMODULE_H
#define TMODULE_H

/*
 * DDAS Pixie16 module class definition
 */
class TModule
{
 private:
  int fType;
  int fADCFreq;
  double fScale;
  double fClockCal;
  int fMaxVal;

 public:
  TModule();
  void SetupModule(int adcfreq, int adcdepth);
  int GetType() {return fType;}
  int GetADCFreq() {return fADCFreq;}
  double GetScale() {return fScale;}
  double GetClockCal() {return fClockCal;}
  int GetMaxVal() {return fMaxVal;}
};

#endif
