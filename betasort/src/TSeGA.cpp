/*
 * TSeGA.cpp. Class methods SeGA detectors.
 * Contains methods for SeGA unpacker which applies 
 * calibration and performs threshold checks.
 * 
 * Author: A. Chester
 *
 */

#include "TSeGA.h"

#include <iostream>
#include <fstream>

using namespace ddastoys;

ClassImp(TSeGA);

//
//  Default calibration parameters
// 
void TSeGACalibrator::Initialize()
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
void TSeGACalibrator::ReadCalFile(std::string name)
{
  std::cout << "Reading SeGA calibration from: " << name << std::endl;
  
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
      	if(linenum < nsega+1) square[location-1] = value;
	else if(linenum < 2*nsega+1) slope[location-1] = value;
	else if(linenum < 3*nsega+1) intercept[location-1] = value;
	else if(linenum < 4*nsega+1) thresh[location-1] = value;
	else if(linenum < 5*nsega+1) uld[location-1] = value;
      } else {
	calfile.ignore(1000,'\n');
      }
    } 
  }  
  calfile.close();
}

void TSeGACalibrator::ReadTimeCalFile(std::string name)
{
  std::cout << "Reading SeGA-dynode time calibration from: " << name << std::endl;

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
	if(linenum < nsega+1) tdiffdynode[location-1] = value;
      } else  {
	calfile.ignore(1000,'\n');
      }
    }
  }
  calfile.close();
}

//
// Reset SeGA variables
//
void TSeGA::Reset()
{
  std::fill(std::begin(time),std::end(time),0.);
  std::fill(std::begin(timecfd),std::end(timecfd),0);
  std::fill(std::begin(cfdfailbit),std::end(cfdfailbit),0);
  std::fill(std::begin(timecal),std::end(timecal),0);
  std::fill(std::begin(energy),std::end(energy),0.);
  std::fill(std::begin(ecal),std::end(ecal),0.);
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
void TSeGA::Unpack(DDASRootFitHit* ddashit, TRandom3 &rng, TSeGACalibrator &cal, int det)
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
    ecal[det] = ec;
    mult++;
    if(!hit) hit = 1;
  }
}
