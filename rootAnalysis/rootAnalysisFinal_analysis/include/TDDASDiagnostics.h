/*
 * TDDASDiagnostics.h. Class definition for tracking basic event information.
 * 
 * Author: A. Chester
 *
 */

#ifndef TDDASDIAGNOSTICS_H
#define TDDASDIAGNOSTICS_H

#include <vector>

#include "TObject.h"

//#include "Constants.h"

/*
 * DDAS clock class definition
 */
class TDDASDiagnostics: public TObject
{
public:
  int cmult;
  double eventlength;
  double tdiffevent;
  std::vector<int> chanhit;
  
  void Reset();

  ClassDef(TDDASDiagnostics,2);
};

#endif
