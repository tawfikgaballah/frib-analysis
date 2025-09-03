/*
 * TTAC.cpp. Class methods for TACs.
 * Calibration methods and parameters for DDAS clock.
 * 
 * Author: A. Chester
 *
 */

#include "TTAC.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace ddastoys;

ClassImp(TTAC);

/*
 * Default calibration parameters
 */
void TTACCalibrator::Initialize()
{
  // Correction factor (slope) and offset
  corr = 1.;
  offset = 0.;

  // Threshold and upper-level discriminator
  thresh = 5.;
  uld = 30000.;
}

void TTACCalibrator::ReadCalFile(std::string name)
{
  std::cout << "Reading TAC calibration from: " << name << std::endl;
  
  std::ifstream calfile(name.c_str());
  int linenum = 0;
  double value = 0;
  std::string line;
 
  if(!calfile) {
    std::cout << "----> Unable to open file " << name << std::endl;
  } else {
    //read in cal file until end of file
    while(calfile) {
      std::getline(calfile,line);
      if(line.length() == 0 || line[0] == '#') {
	continue;
      } else {
	linenum++;
	std::stringstream linestream(line);
	linestream >> value;
	if(linenum == 1) corr = value;
	if(linenum == 2) offset = value;
	if(linenum == 3) thresh = value;
	if(linenum == 4) uld = value;	      
      } 
    } 
  }  
  calfile.close();
}

/*
 * Reset TAC variables
 */
void TTAC::Reset()
{
  energy = 0;
  time = 0.;
  hit = 0;
}

void TTAC::Unpack(DDASRootFitHit* ddashit, TRandom3 &rng, TTACCalibrator &cal)
{
  // put hit information into detector class
  time = ddashit->getTime();
  double er = ddashit->getEnergy() + rng.Rndm();
  
  // threshold check
  if(er > cal.thresh && er < cal.uld) {
    energy = er;
    if(!hit) hit = 1;
  } else {
    energy = 99999.;
  }
}
