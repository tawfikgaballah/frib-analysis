/*
 * TPID.h. Class definitions for PID variables which are 
 * derived from dE measurements in an upstream PIN
 * detector and some measure of TOF throught the 
 * fragment separator.
 * 
 * Author: A. Chester
 *
 */

#ifndef TPID_H
#define TPID_H

#include "TObject.h"

/*
 * PID class defintion
 */
class TPID: public TObject
{
public:
  // PIN dE
  // unsigned int fUniqueID;
  //  unsigned int fBits;
  double de1;
  double de2;
  double tof;
  double scintScintTOF;
  double time;
  int xpos;
  int ypos;

  // int size;
  // For use in vectors we need a copy constructor
  TPID& operator=(const TPID& rhs)
    {
      // fUniqueID=rhs.fUniqueID;
      // fBits=rhs.fBits;
      de1 = rhs.de1;
      de2 = rhs.de2;
      tof = rhs.tof;
      scintScintTOF = rhs.scintScintTOF;
      time = rhs.time;
      xpos = rhs.xpos;
      ypos = rhs.ypos;
      return *this;
    }
    

void Reset();


  
  ClassDef(TPID,2);
};

#endif
