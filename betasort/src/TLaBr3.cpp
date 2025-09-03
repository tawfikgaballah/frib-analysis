/*
 * TLaBr3.cpp. Class methods LaBr3 detectors.
 * Contains methods for LaBr3 unpacker which applies 
 * calibration and performs threshold checks.
 * 
 * Author: A. Chester
 *
 */

#include "TLaBr3.h"

#include <iostream>
#include <fstream>

using namespace ddastoys;

ClassImp(TLaBr3);

//
//  Default calibration parameters
// 
void TLaBr3Calibrator::Initialize()
{
  std::fill(std::begin(square),std::end(square),0.);
  std::fill(std::begin(slope),std::end(slope),1.);
  std::fill(std::begin(intercept),std::end(intercept),0.);
  std::fill(std::begin(thresh),std::end(thresh),0.);
  std::fill(std::begin(uld),std::end(uld),30000.);
  std::fill(std::begin(tdiffdynode),std::end(tdiffdynode),0.);
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
void TLaBr3Calibrator::ReadCalFile(std::string name)
{
  std::cout << "Reading LaBr3 calibration from: " << name << std::endl;
  
  std::ifstream calfile(name.c_str());
  int linenum = 0;
  int location = -1;
  double value = 0;
 
  if(!calfile) {
    std::cout << "----> Unable to open file " << name << std::endl;
  } else {
    while(calfile) {
      if(calfile && (isdigit(calfile.peek()))) {
	linenum++;
	calfile >> location >> value;	      
      	if(linenum < nlabr3+1) square[location-1] = value;
	else if(linenum < 2*nlabr3+1) slope[location-1] = value;
	else if(linenum < 3*nlabr3+1) intercept[location-1] = value;
	else if(linenum < 4*nlabr3+1) thresh[location-1] = value;
	else if(linenum < 5*nlabr3+1) uld[location-1] = value;
      } else {
	calfile.ignore(1000,'\n');
      }
    } 
  }  
  calfile.close();
}

//
// ReadTimeCalFile
//
// Function:
//   - reads detector calibration file for timing with respect to dynode signals
//
// Params:
//   - calibration file name as a std::string
//
// Return:
//   - none
//
void TLaBr3Calibrator::ReadTimeCalFile(std::string name)
{
  std::cout << "Reading LaBr3-dynode time calibration from: " << name << std::endl;

  std::ifstream calfile(name.c_str());

  int linenum = 0;
  int location = -1;
  double value = 0;

  if(!calfile) {
    std::cout << "Unable to open file " << name << std::endl;
  } else {
    while(calfile) {
      if(calfile && (isdigit(calfile.peek())))  {
	linenum++;
	calfile >> location >> value;
	if(linenum < nlabr3+1) tdiffdynode[location-1] = value;
      } else  {
	calfile.ignore(1000,'\n');
      }
    }
  }
  calfile.close();
}

//
// Reset LaBr3 variables
//
void TLaBr3::Reset()
{
  std::fill(std::begin(time),std::end(time),0.);
  std::fill(std::begin(timecfd),std::end(timecfd),0);
  std::fill(std::begin(cfdfailbit),std::end(cfdfailbit),0);
  std::fill(std::begin(timecal),std::end(timecal),0);
  std::fill(std::begin(energy),std::end(energy),-1.);
  std::fill(std::begin(ecal),std::end(ecal),-1.);
  mult = 0;
  hit = 0;
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
void TLaBr3::Unpack(DDASRootFitHit* ddashit, TRandom3 &rng, TLaBr3Calibrator &cal, int det)
{
  // extract hit information
  // put hit information into detector class
  // time
  time[det] = ddashit->getTime();
  timecfd[det] = ddashit->getTimeCFD();
  cfdfailbit[det] = ddashit->getCFDFailBit(); // no get()
  timecal[det] = time[det] - cal.tdiffdynode[det];
     
    // energies
  energy[det] = ddashit->getEnergy() + rng.Rndm();
  double ec = cal.square[det]*energy[det]*energy[det] + cal.slope[det]*energy[det] + cal.intercept[det];

  // threshold check
  if(ec > cal.thresh[det] && ec < cal.uld[det]) {
    if(!hit) hit = 1;
    ecal[det] = ec;
    mult++;
  }
}
