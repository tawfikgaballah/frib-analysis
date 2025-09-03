/*
 * TClover.cpp. Class methods Clover detectors.
 * Contains methods for Clover unpacker which applies 
 * calibration and performs threshold checks.
 * 
 * Author: A. Chester
 *
 */

#include "TClover.h"

#include <iostream>
#include <fstream>

using namespace ddastoys;

ClassImp(TClover);

//
//  Default calibration parameters
// 
void TCloverCalibrator::Initialize()
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
void TCloverCalibrator::ReadCalFile(std::string name)
{
  std::cout << "Reading Clover calibration from: " << name << std::endl;
  
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
      	if(linenum < totcrystals+1) square[location-1] = value;
	else if(linenum < 2*totcrystals+1) slope[location-1] = value; 
	else if(linenum < 3*totcrystals+1) intercept[location-1] = value;
	else if(linenum < 4*totcrystals+1) thresh[location-1] = value;
	else if(linenum < 5*totcrystals+1) uld[location-1] = value;
      } else {
	calfile.ignore(1000,'\n');
      }
    } 
  }  
  calfile.close();
}

void TCloverCalibrator::UpdateCalFile(std::string name) {
  std::cout << "Updating Clover calibration from: " << name << std::endl;
  
  std::ifstream calfile(name.c_str());
  int linenum = 0;
  int location = -1;
  double value = 0, value2 = 0;
 
  if(!calfile) {
    std::cout << "----> Unable to open file " << name << std::endl;
    for (int i=0; i<totcrystals; i++) {
      intercept[i] = 0.;
      slope[i] = 1.;
    }
  } else {
    while(calfile) {
      if(calfile && (isdigit(calfile.peek()))) {
	linenum++;
	calfile >> location >> value >> value2;
	if(linenum < totcrystals+1) {
	  intercept[location-1] = value;
	  slope[location-1] = value2;
	}
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
void TCloverCalibrator::ReadTimeCalFile(std::string name)
{
  std::cout << "Reading Clover-dynode time calibration from: " << name << std::endl;

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
	if(linenum < totcrystals+1) tdiffdynode[location-1] = value;
      } else  {
	calfile.ignore(1000,'\n');
      }
    }
  }
  calfile.close();
}

//
// Reset Clover variables
//
void TClover::Reset()
{
  std::fill(std::begin(time),std::end(time),0.);
  std::fill(std::begin(timecfd),std::end(timecfd),0);
  std::fill(std::begin(cfdfailbit),std::end(cfdfailbit),0);
  std::fill(std::begin(timecal),std::end(timecal),0.);
  std::fill(std::begin(energy),std::end(energy),-1.);
  std::fill(std::begin(ecal),std::end(ecal),-1.);
  mult = 0;

  // Add back
  std::fill(std::begin(ecalab),std::end(ecalab),0.);
  std::fill(std::begin(timeab),std::end(timeab),0.);
  std::fill(std::begin(cfdfailbitab),std::end(cfdfailbitab),0);
  std::fill(std::begin(timecalab),std::end(timecalab),0.);
  std::fill(std::begin(posmult),std::end(posmult),0);
  multab = 0;

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
void TClover::Unpack(DDASRootFitHit* ddashit, TRandom3 &rng, TCloverCalibrator &cal, int det)
{
  // position derived from crystal number
  int pos = det/4;
  
  // time
  time[det] = ddashit->getTime();
  timecfd[det] = ddashit->getTimeCFD(); // raw cfd time
  cfdfailbit[det] = ddashit->getCFDFailBit(); // 1 if fail
  // calibrated time
  timecal[det] = time[det] - cal.tdiffdynode[det];
  
  // raw energy
  energy[det] = ddashit->getEnergy() + rng.Rndm();
 /*  if (energy[det]>10)
  std::cout<<energy<<'\n'; */
  double ec = cal.square[det]*energy[det]*energy[det] + cal.slope[det]*energy[det] + cal.intercept[det];

  // calibrated energy
  if(ec > cal.thresh[det] && ec < cal.uld[det]) {
    if(!hit) hit = 1;
    ecal[det] = ec;
    mult++;

    // addback
    // energy
    ecalab[pos] += ec;
    // addback time is the average so we sum here and compute the
    // average after the full event has been processed
    timeab[pos] += time[det];
    cfdfailbitab[pos] |= cfdfailbit[det]; // 1 if OR is 1
    timecalab[pos] += timecal[det];
    // position multiplicity for computing average times later
    posmult[pos]++;
  }  
}


//
// AddBack
//
// Function:
//   - Calculates addback time and multiplicity
//
// Params:
//   - none
//
// Return:
//   - none
//
void TClover::AddBack()
{
  for(int i=0; i<nclovers; i++) {
    if(ecalab[i] > 0.) { // ecalab sum is in the Unpack() function
      timeab[i] /= posmult[i]; // average
      timecalab[i] /= posmult[i]; // average of corrected time
      multab++;
    }
  }
}
