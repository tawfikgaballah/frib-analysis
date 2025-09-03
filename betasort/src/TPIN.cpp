/*
 * TPIN.cpp. Class methods PIN detectors.
 * Contains methods for PIN unpacker which applies 
 * calibration and performs threshold checks.
 * 
 * Author: A. Chester
 *
 */

#include "TPIN.h"

#include <iostream>
#include <fstream>

using namespace ddastoys;

ClassImp(TPIN);

//
//  Default calibration parameters
// 
void TPINCalibrator::Initialize()
{
  slope     = 1.;
  intercept = 0.;
  thresh    = 0.;
  ithresh   = 0.;
  uld       = 30000.;
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
void TPINCalibrator::ReadCalFile(std::string name)
{
  std::cout << "Reading PIN calibration from: " << name << std::endl;
  
  std::ifstream calfile(name.c_str());
  int linenum = 0;
  double value = 0;
 
  if(!calfile) {
    std::cout << "----> Unable to open file " << name << std::endl;
  } else {
    //read in cal file until end of file
    while(calfile) {
      if(calfile && (isdigit(calfile.peek()))) {
	linenum++;
	calfile >> value;	      
	if(linenum == 1) slope = value;
	if(linenum == 2) intercept = value;
	if(linenum == 3) thresh = value;
	if(linenum == 4) ithresh = value;
	if(linenum == 5) uld = value;	      
      } else {
	calfile.ignore(1000,'\n');
      }
    } 
  }  
  calfile.close();
}

//
// Reset PIN variables
//
void TPIN::Reset()
{
  energy = 0.;
  time = 0.;
  ecal = 0.;
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
void TPIN::Unpack(DDASRootFitHit* ddashit, TRandom3 &rng, TPINCalibrator &cal, Bool_t goCFD)
{
  // extract hit information
  // put hit information into detector class
  time = ddashit->getTime();
  energy = ddashit->getEnergy() + rng.Rndm();
  double ec = cal.slope*energy + cal.intercept;

  // threshold check
  if(ec > cal.thresh && ec < cal.uld) {
    ecal = ec;
    if(!hit) hit = 1;
  }

  if (goCFD) {
    Float_t tauDiff = 6., delay = 5., fraction = 0.5; 
    
    std::vector<UShort_t> trace = ddashit->getTrace();

    std::vector<Float_t> sint;
    std::vector<Float_t> sdiff;
    std::vector<Float_t> s;
    std::vector<Float_t> pulse;
    std::vector<Float_t> cfd;

    if (!trace.empty()) {
      Float_t baseline = 0;
      for (Int_t i=0; i<20; i++) { baseline += trace[i]; }
      baseline /= 20;
      // std::cout << "BL " << baseline << std::endl;
      for (Int_t i; i<trace.size(); i++) { pulse.push_back(((Float_t)trace[i]-baseline)); }
      sint.push_back((pulse[0]+pulse[1])/2.);
      sint.push_back((pulse[0]+pulse[1]+pulse[2])/3.);
      sint.push_back((pulse[0]+pulse[1]+pulse[2]+pulse[3]+pulse[4])/5.);
      sint.push_back((pulse[0]+pulse[1]+pulse[2]+pulse[3]+pulse[4]+pulse[5]+pulse[6])/7.);
      for (Int_t i=4; i<pulse.size()-5; i++) {
	sint.push_back((pulse[i-4] + pulse[i-3] + pulse[i-2] + pulse[i-1]+pulse[i]+pulse[i+1]+pulse[i+2]+pulse[i+3]+pulse[i+4])/9.);
      }
      //    s.push_back((sint[0]+sint[1])/2.);
      //s.push_back((sint[0]+sint[1]+sint[2])/3.);
      //s.push_back((sint[0]+sint[1]+sint[2]+sint[3]+sint[4])/5.);
      //s.push_back((sint[0]+sint[1]+sint[2]+sint[3]+sint[4]+sint[5]+sint[6])/7.);
      for (Int_t i=0; i<sint.size(); i++) {
	//s.push_back((sint[i-4] + sint[i-3] + sint[i-2] + sint[i-1]+sint[i]+sint[i+1]+sint[i+2]+sint[i+3]+sint[i+4])/9.);
	s.push_back(sint[i]);
      }
      sdiff.push_back(s[0]);
      for (Int_t i=1; i<sint.size()-1; i++) {
	sdiff.push_back((s[i] - s[i-1]) + (sdiff[i-1] - (sdiff[i-1]/tauDiff)));
      }

    
      for (Int_t i=(Int_t)delay; i<trace.size()-10; i++) {
	if (i+delay < trace.size()-1) {
	  cfd.push_back((sdiff[i-(Int_t)delay] - fraction*sdiff[i]));
	} else {
	  cfd.push_back((sdiff[i] - fraction*sdiff[i]));
	}
      }

      Int_t maxJ = 0; 
      Float_t maxCFD = 0;
      for (Int_t i=20; i<80; i++) {
	if (cfd[i] > maxCFD) {
	  maxCFD = cfd[i];
	  maxJ = i;
	}
      }
    
      Int_t tcross = -100;
    
      /* Crossing point */
      if (cfd.size() > (UInt_t)maxJ) {
	if (cfd[maxJ] < 0) {
	  for (UInt_t uj=0; uj<cfd.size(); uj++) {
	    cfd[uj] = -cfd[uj];
	  }
	}
	for (Int_t i=maxJ; i>0; i--) {
	  if (cfd[i] < 0) { tcross = i; break; }
	}
      }
    
      UInt_t ui = (UInt_t)tcross;
      UInt_t x1, x2;
      Float_t y1, y2, start1, startCFD;
      start1 = 0;
      if (cfd.size() > ui) {
	x1 = ui; y1 = cfd[ui]; x2 = ui+1; y2 = cfd[ui+1];
	start1 = x2 - (y2/((y2-y1)/(x2-x1)));
      } else {
	start1 = -10;
      }
      startCFD = start1;

      if (start1 < 10 || start1 > 70) {
	startCFD = -1000;
	// std::cout << "j, cfd " << maxJ << " " << maxCFD << std::endl;
	//for (Int_t i=0; i<cfd.size(); i++) {
	//	std::cout << i << " " << trace[i] << " " << pulse[i] << " " << sint[i] << " " << s[i] << " " << sdiff[i] << " " << cfd[i] << std::endl;
	//}
	//std::cout << "***************************************************************************************" << std::endl;
      }
      cfd.clear();    
      //    std::cout << startCFD << std::endl;
      time += startCFD;
    }
  }
    

}

