/*
 * TTrace.h. Class definition for handling DDAS traces.
 * This is a placeholder for now, as traces are typcally
 * dropped at this step and only their fit parameters
 * are kept for further analysis.
 * 
 * Author: A. Chester
 *
 */

#ifndef TTRACE_H
#define TTRACE_H

#include "TObject.h"

/*
 * DDAS trace class definition
 */ 
class TTrace : public TObject
{
public:
  std::vector<unsigned short> trace;

  void Reset();
  
  ClassDef(TTrace,2);
};

#endif
