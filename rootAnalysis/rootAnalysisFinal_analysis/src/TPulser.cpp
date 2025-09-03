/*
 * TPulser.cpp. Class methods Pulser detectors.
 * Contains methods for Pulser unpacker which applies 
 * calibration and performs threshold checks.
 * 
 * Author: A. Chester
 *
 */

#include "TPulser.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "RootExtensions.h"    // need to add explicitly

#include "/projects/e21062/DDASToys/functions_analytic.h"   // need to add explicitly because of
				  // DDAS AnalyticFit namespace
#include "/projects/e21062/DDASToys/lmfit_analytic.h"	 // need to add explicitly because of
				  // DDAS AnalyticFit namespace

ClassImp(TPulser);

//
//  Default calibration parameters
// 
void TPulserCalibrator::Initialize()
{
  // dynode
  offset = 0.;
  slope = 1.;
  fitoffset = 0.;
  fitslope = 1.;
  clockcal = 4.; // default assume dynode is 250 MSPS card 4 ns/sample
  thresh = 0.;
  uld = 30000;
}
  
//
// Reset Pulser variables
//
void TPulser::Reset()
{
  // dynode
  energy = 0.;
  ecal = 0.;
  time = 0.;
  timecfd = 0;
  cfdfailbit = 0;
  overflow = 0;
  mult = 0;
  
  // fit information
  // single pulse
  chisq_single = 0.;
  E1_single = 0.;
  E1real_single = 0.;
  E1cal_single = 0.;
  T1_single = 0.;
  offset_single = 0.;
  E1steepness_single = 0.; 
  E1decay_single = 0.;
  // double pulse
  chisq_double = 0.;
  E1_double = 0.;
  E1real_double = 0.;
  E1cal_double = 0.;
  T1_double = 0.;
  E1steepness_double = 0.;
  E1decay_double = 0.;
  E2_double = 0.;
  E2real_double = 0.;
  E2cal_double = 0.;
  T2_double = 0.;
  E2steepness_double = 0.;
  E2decay_double = 0.;
  offset_double = 0.;
  tdiffE1E2 = 0.;
  tdiffE1E2cal = 0.;

  // hit flags
  hit = 0;
}

//
// Unpack
//
// Function:
//   - unpacks ADC information into detector class
//   - specific to Pulser dynode to handle trace analysis
//
// Params:
//   - pointer to a DDAS hit data structure
//   - calibration parameters
//
// Return:
//   - none
//
void TPulser::Unpack(DDASRootFitHit* ddashit, TRandom3 &rng, TPulserCalibrator &cal)
{
  // extract hit information
  // put hit information into detector class
  // trace analysis
  auto trace = ddashit->GetTrace();
  if(trace.size() > 0) { // if threre is a trace, check for overflow
    overflow = ddashit->GetADCOverflowUnderflow(); // 1 if the trace overflows the ADC
  }

  // time
  time = ddashit->GetTime();
  timecfd = ddashit->GetCFDTime();
  cfdfailbit = ddashit->cfdfailbit; // no Get();
  
  // energy (from Pixie)
  energy = ddashit->GetEnergy() + rng.Rndm();
  double ec = cal.slope*energy + cal.offset;

  if(ec > cal.thresh && ec < cal.uld) {
    if(!hit) hit = 1;
    ecal = ec;
  }

  // reset overflows to have a high energy
  if(overflow == 1) {
    if(!hit) hit = 1; // overflows still a good hit
    energy = 99999.;
    ecal = 99999.;
  }
}

//
// UnpacknodeFit
//
// Function:
//   - assigns node fit parameters to the proper node variables
//
// Params:
//   - pointer to a DDAS hit data structure
//   - calibration parameters
//
// Return:
//   - none
//
void TPulser::UnpackFit(TPulserCalibrator &cal, std::vector<RootHitExtension> &fits)
{
  for(unsigned i=0; i<fits.size(); i++) {
      if (fits[i].haveExtension) {
      RootFit1Info fit1 = fits[i].onePulseFit;
      RootFit2Info fit2 = fits[i].twoPulseFit;      
      
      // assign single pulse fit results
      E1_single = fit1.pulse.amplitude;
      T1_single = fit1.pulse.position;

      // comment out for template fitting
      E1steepness_single = fit1.pulse.steepness;
      E1decay_single = fit1.pulse.decayTime;
      
      offset_single = fit1.offset;
      chisq_single = fit1.chiSquare;

      // check organization for defining E2 to be the second pulse
      if(fit2.pulses[0].position < fit2.pulses[1].position) {
	E1_double = fit2.pulses[0].amplitude;
	T1_double = fit2.pulses[0].position;
	
	// comment out for template fitting
	E1steepness_double = fit2.pulses[0].steepness;
	E1decay_double = fit2.pulses[0].decayTime;
	
	E2_double = fit2.pulses[1].amplitude;
	T2_double = fit2.pulses[1].position;

	// comment out for template fitting
	E2steepness_double = fit2.pulses[1].steepness;
	E2decay_double = fit2.pulses[1].decayTime;
	
      } else {	
	E1_double = fit2.pulses[1].amplitude;
	T1_double = fit2.pulses[1].position;

	// comment out for template fitting
	E1steepness_double = fit2.pulses[1].steepness;
	E1decay_double = fit2.pulses[1].decayTime;
	
	E2_double = fit2.pulses[0].amplitude;
	T2_double = fit2.pulses[0].position;

	// comment out for template fitting
	E2steepness_double = fit2.pulses[0].steepness;
	E2decay_double = fit2.pulses[0].decayTime;
      }
      
      chisq_double = fit2.chiSquare;
      offset_double = fit2.offset;
      tdiffE1E2 = T2_double - T1_double;
      tdiffE1E2cal = cal.clockcal*tdiffE1E2;
      
      // calculate real amplitudes
      E1real_single = DDAS::AnalyticFit::pulseAmplitude(E1_single,E1steepness_single,E1decay_single,T1_single);
      E1real_double = DDAS::AnalyticFit::pulseAmplitude(E1_double,E1steepness_double,E1decay_double,T1_double);
      E2real_double = DDAS::AnalyticFit::pulseAmplitude(E2_double,E2steepness_double,E2decay_double,T2_double);

      // calibrated energies
      E1cal_single = cal.fitslope*E1real_single + cal.fitoffset;
      E1cal_double = cal.fitslope*E1real_double + cal.fitoffset;
      E2cal_double = cal.fitslope*E2real_double + cal.fitoffset;
    }
  }
}


