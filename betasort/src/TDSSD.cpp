/*
 * TDSSD.cpp. Class methods DSSD detectors.
 * Contains DSSD unpacker which applies calibration
 * and performs threshold checks.
 * 
 * Author: A. Chester
 *
 */

#include "TDSSD.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace ddastoys;

ClassImp(TDSSD);

//
//  Default calibration parameters
// 
void TDSSDCalibrator::Initialize()
{
  // high gain
 std::fill(std::begin(hioffset),std::end(hioffset),0.);
 std::fill(std::begin(hislope),std::end(hislope),1.);
 std::fill(std::begin(hithresh),std::end(hithresh),0.);
 std::fill(std::begin(hiuld),std::end(hiuld),30000.);
  
  // low gain
 std::fill(std::begin(looffset),std::end(looffset),0.);
 std::fill(std::begin(loslope),std::end(loslope),1.);
 std::fill(std::begin(lothresh),std::end(lothresh),0.);
 std::fill(std::begin(lould),std::end(lould),30000.);
}

//
// ReadCalFile
//
// Function:
//   - reads detector calibration file
//
// Params:
//   - calibration file name as a std::string
//
// Return:
//   - none
//
void TDSSDCalibrator::ReadCalFile(std::string name)
{
  std::cout << "Reading DSSD calibration from: " << name << std::endl;

  std::ifstream calfile(name.c_str());
  
  int linenum = 0;

  int location = -1;
  double value = 0;
  
  if(!calfile) {
    std::cout << "----> Unable to open file " << name << std::endl;
  } else {
    //read in cal file until end of file
    while(calfile) {
      if(calfile && (isdigit(calfile.peek()))) {
	linenum++;
	calfile >> location >> value;
	// std::cout << linenum << " " << location << " " << value << std::endl;	      
	if(linenum < ndssd+1) hioffset[location-1] = value;
	else if(linenum < 2*ndssd+1) hislope[location-1] = value;
	else if(linenum < 3*ndssd+1) hithresh[location-1] = value;
	else if(linenum < 4*ndssd+1) hiuld[location-1] = value;
	else if(linenum < 5*ndssd+1) looffset[location-1] = value;
	else if(linenum < 6*ndssd+1) loslope[location-1] = value;
	else if(linenum < 7*ndssd+1) lothresh[location-1] = value;
	else if(linenum < 8*ndssd+1) lould[location-1] = value;
      }  else {
	//ignore line
	calfile.ignore(1000,'\n');
      }
    } // end while read
  }  
  calfile.close();
}

//
// Reset DSSD variables
//
void TDSSD::Reset()
{
  // high gain
  std::fill(std::begin(hitime),std::end(hitime),0.);
  std::fill(std::begin(hienergy),std::end(hienergy),0.);
  std::fill(std::begin(hiecal),std::end(hiecal),0.);

  // low gain
  std::fill(std::begin(lotime),std::end(lotime),0.);
  std::fill(std::begin(loenergy),std::end(loenergy),0.);
  std::fill(std::begin(loecal),std::end(loecal),0.);

  // implanted ion
  imax = 0.;
  imaxtime = 0.;
  imaxch = 100;
  imult = 0;

  // decay
  dmax = 0.;
  dmaxtime = 0.;
  dmaxch = 100;
  dmult = 0; 
}

//
// Unpack
//
// Function:
//   - unpacks ADC information into detector class
//
// Params:
//   - pointer to a DDAS hit data structure
//   - calibration parameters
//
// Return:
//   - none
//
void TDSSD::Unpack(DDASRootFitHit* ddashit, TRandom3 &rng, TDSSDCalibrator &cal)
{
  // extract hit information

  /*
  * placeholder until DSSD detector is used for an experiment analyzed
  * with this version of the sorting code. possibly e18018 analysis
  * can be used as a template but need the source code.
  */
}
