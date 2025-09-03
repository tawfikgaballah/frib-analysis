/*
 * TSSSD.cpp. Class methods SSSD detectors.
 * Contains SSSD unpacker which applies calibration
 * and performs threshold checks.
 * 
 * Author: A. Chester
 *
 */

#include "TSSSD.h"

#include <iostream>
#include <fstream>
#include <algorithm>

ClassImp(TSSSD);

//
//  Default calibration parameters
// 
void TSSSDCalibrator::Initialize()
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
void TSSSDCalibrator::ReadCalFile(std::string name)
{
  std::cout << "Reading SSSD calibration from: " << name << std::endl;

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
// Reset SSSD variables
//
void TSSSD::Reset()
{
  // high gain
  std::fill(std::begin(hitime),std::end(hitime),0.);
  std::fill(std::begin(hienergy),std::end(hienergy),0.);
  std::fill(std::begin(hiecal),std::end(hiecal),0.);
  himax = 0.;
  himaxtime = 0.;
  himaxch = 100;
  himult = 0; 
  
  // low gain
  std::fill(std::begin(lotime),std::end(lotime),0.);
  std::fill(std::begin(loenergy),std::end(loenergy),0.);
  std::fill(std::begin(loecal),std::end(loecal),0.);
  lomax = 0.;
  lomaxtime = 0.;
  lomaxch = 100;
  lomult = 0; 
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
void TSSSD::Unpack(DDASRootFitHit* ddashit, TRandom3 &rng, TSSSDCalibrator &cal)
{
  // extract hit information

  /*
  * placeholder until SSSD detector is used for an experiment analyzed
  * with this version of the sorting code. possibly e18018 analysis
  * can be used as a template but need the source code.
  */
}
