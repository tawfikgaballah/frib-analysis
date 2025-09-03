/*
 * TPSPMT.cpp. Class methods PSPMT detectors.
 * Contains methods for PSPMT unpacker which applies 
 * calibration and performs threshold checks.
 * 
 * Author: A. Chester
 *
 */

#include "TPSPMT.h"

#include <iostream>
#include <fstream>
#include <sstream>


#include "RootExtensions.h"    // need to add explicitly

#include "TLinearSolver.h"

#include "/projects/e21062/DDASToys/functions_analytic.h"   // need to add explicitly because of
				  // DDAS AnalyticFit namespace
#include "/projects/e21062/DDASToys/lmfit_analytic.h"	 // need to add explicitly because of
				  // DDAS AnalyticFit namespace

ClassImp(TPSPMT);

//
//  Default calibration parameters
// 
void TPSPMTCalibrator::Initialize()
{
  // dynode
  dyoffset = 0.;
  dyslope = 1.;
  dyfitoffset = 0.;
  dyfitslope = 1.;
  dyclockcal = 2.; // default assume dynode is 500 MSPS card 2 ns/sample
  dythresh = 0.;
  dyuld = 30000;
  dycoincwindow = 100.; // default 100 ns for coincidence with anodes

  std::fill(std::begin(aoffset),std::end(aoffset),0.);
  std::fill(std::begin(aslope),std::end(aslope),1.);
  std::fill(std::begin(athresh),std::end(athresh),0.);
  std::fill(std::begin(auld),std::end(auld),30000.);
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
void TPSPMTCalibrator::ReadCalFile(std::string name)
{
  std::cout << "Reading PSPMT calibration from: " << name << std::endl;

  std::ifstream calfile(name.c_str());
  
  int linenum = 0;
  int location = -1;
  double value = 0;
  std::string line;

  if(!calfile) {
    std::cout << "Unable to open file " << name << std::endl;
  } else {
    // std::cout << "File opened" << std::endl;
    while(!calfile.eof()) {
      std::getline(calfile,line);
      if(line.length() == 0 || line[0] == '#') {
	continue;
      } else {
	linenum++;

	if(linenum < 4*nanodes+1) {
	  std::stringstream linestream(line);
	  linestream >> location >> value;
  	  if(linenum < nanodes+1) aslope[location-1] = value;
  	  else if(linenum < 2*nanodes+1) aoffset[location-1] = value;
  	  else if(linenum < 3*nanodes+1) athresh[location-1] = value;
  	  else if(linenum < 4*nanodes+1) auld[location-1] = value;
  	} else {
	  std::stringstream linestream(line);
	  linestream >> value;
	  if(linenum == 4*nanodes+1) dyslope = value;
  	  if(linenum == 4*nanodes+2) dyoffset = value;
	  if(linenum == 4*nanodes+3) dyfitslope = value;
  	  if(linenum == 4*nanodes+4) dyfitoffset = value;
	  if(linenum == 4*nanodes+5) dyclockcal = value;
  	  if(linenum == 4*nanodes+6) dythresh = value;
  	  if(linenum == 4*nanodes+7) dyuld = value;
	  if(linenum == 4*nanodes+8) dycoincwindow = value;
	}
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
void TPSPMTCalibrator::ReadTimeCalFile(std::string name)
{
  std::cout << "Reading PSPMT anode-dynode time calibration from: " << name << std::endl;

  std::ifstream calfile(name.c_str());

  int linenum = 0;
  int location = -1;
  double value = 0;

  if(!calfile) {
    std::cout << "Unable to open file " << name << std::endl;
  } else {
    // Read in cal file until end of file
    while(calfile) {
      if(calfile && (isdigit(calfile.peek()))) {
	linenum++;
	calfile >> location >> value;
	if(linenum < nanodes+1) tdiffdynode[location-1] = value;
      } else {
	//ignore line
	calfile.ignore(1000,'\n');
      }
    }
  }
  calfile.close();
}
  
//
// Reset PSPMT variables
//
void TPSPMT::Reset()
{
  // dynode
  dyenergy = 0.;
  dyecal = 0.;
  dytime = 0.;
  dytimecfd = 0;
  dycfdfailbit = 0;
  dyoverflow = 0;
  dymult = 0;
  
  // fit information
  // single pulse
  dychisq_single = 0.;
  dyE1_single = 0.;
  dyE1real_single = 0.;
  dyE1cal_single = 0.;
  dyT1_single = 0.;
  dyoffset_single = 0.;
  dyE1steepness_single = 0.; 
  dyE1decay_single = 0.;
  // double pulse
  dychisq_double = 0.;
  dyE1_double = 0.;
  dyE1real_double = 0.;
  dyE1cal_double = 0.;
  dyT1_double = 0.;
  dyE1steepness_double = 0.;
  dyE1decay_double = 0.;
  dyE2_double = 0.;
  dyE2real_double = 0.;
  dyE2cal_double = 0.;
  dyT2_double = 0.;
  dyE2steepness_double = 0.;
  dyE2decay_double = 0.;
  dyoffset_double = 0.;
  dytdiffE1E2 = 0.;
  dytdiffE1E2cal = 0.;

  // anode
  std::fill(std::begin(aenergy),std::end(aenergy),0.);
  std::fill(std::begin(aecal),std::end(aecal),0.);
  asum = 0.;
  std::fill(std::begin(atime),std::end(atime),0);
  std::fill(std::begin(atimecal),std::end(atimecal),0);
  std::fill(std::begin(aoverflow),std::end(aoverflow),0);
  aoverflowcount = 0;  
  amultraw = 0;
  amult = 0;
  std::fill(std::begin(pixelmult),std::end(pixelmult),0);
  // anode linearlized position fit parameters
  lxamp = 0.;   // amplitude of 1D fit
  lxpos = -1.;  // x-position from 2D fit
  lxgamma = 0.; // Lorentzian sigma in x
  lyamp = 0.;   // amplitude of 1D fit
  lypos = -1.;  // y-position from 2D fit
  lygamma = 0.; // Lorentzian sigma in y

  // hit flags
  dyhit = 0;
  std::fill(std::begin(ahit),std::end(ahit),0);
  hit = 0;
}

//
// UnpackDynode
//
// Function:
//   - unpacks ADC information into detector class
//   - specific to PSPMT dynode to handle trace analysis
//
// Params:
//   - pointer to a DDAS hit data structure
//   - calibration parameters
//
// Return:
//   - none
//
void TPSPMT::UnpackDynode(DDASRootFitHit* ddashit, TRandom3 &rng, TPSPMTCalibrator &cal)
{
  // extract hit information
  // put hit information into detector class
  // trace analysis
  auto trace = ddashit->GetTrace();
  if(trace.size() > 0) { // if threre is a trace, check for overflow
    dyoverflow = ddashit->GetADCOverflowUnderflow(); // 1 if the trace overflows the ADC
  }

  // time
  dytime = ddashit->GetTime();
  dytimecfd = ddashit->GetCFDTime();
  dycfdfailbit = ddashit->cfdfailbit; // no Get();
  
  // energy (from Pixie)
  dyenergy = ddashit->GetEnergy() + rng.Rndm();
  double ec = cal.dyslope*dyenergy + cal.dyoffset;

  if(ec > cal.dythresh && ec < cal.dyuld) {
    if(!dyhit) dyhit = 1;
    dyecal = ec;
  }

  // reset overflows to have a high energy
  if(dyoverflow == 1) {
    if(!dyhit) dyhit = 1; // overflows still a good hit
    dyenergy = 99999.;
    dyecal = 99999.;
  }
}

//
// UnpackDynodeFit
//
// Function:
//   - assigns dynode fit parameters to the proper dynode variables
//
// Params:
//   - pointer to a DDAS hit data structure
//   - calibration parameters
//
// Return:
//   - none
//
void TPSPMT::UnpackDynodeFit(TPSPMTCalibrator &cal, std::vector<RootHitExtension> &fits)
{
  for(unsigned i=0; i<fits.size(); i++) {
      if (fits[i].haveExtension) {
      RootFit1Info fit1 = fits[i].onePulseFit;
      RootFit2Info fit2 = fits[i].twoPulseFit;      
      
      // assign single pulse fit results
      dyE1_single = fit1.pulse.amplitude;
      dyT1_single = fit1.pulse.position;

      // comment out for template fitting
      dyE1steepness_single = fit1.pulse.steepness;
      dyE1decay_single = fit1.pulse.decayTime;
      
      dyoffset_single = fit1.offset;
      dychisq_single = fit1.chiSquare;

      // check organization for defining E2 to be the second pulse
      if(fit2.pulses[0].position < fit2.pulses[1].position) {
	dyE1_double = fit2.pulses[0].amplitude;
	dyT1_double = fit2.pulses[0].position;
	
	// comment out for template fitting
	dyE1steepness_double = fit2.pulses[0].steepness;
	dyE1decay_double = fit2.pulses[0].decayTime;
	
	dyE2_double = fit2.pulses[1].amplitude;
	dyT2_double = fit2.pulses[1].position;

	// comment out for template fitting
	dyE2steepness_double = fit2.pulses[1].steepness;
	dyE2decay_double = fit2.pulses[1].decayTime;
	
      } else {	
	dyE1_double = fit2.pulses[1].amplitude;
	dyT1_double = fit2.pulses[1].position;

	// comment out for template fitting
	dyE1steepness_double = fit2.pulses[1].steepness;
	dyE1decay_double = fit2.pulses[1].decayTime;
	
	dyE2_double = fit2.pulses[0].amplitude;
	dyT2_double = fit2.pulses[0].position;

	// comment out for template fitting
	dyE2steepness_double = fit2.pulses[0].steepness;
	dyE2decay_double = fit2.pulses[0].decayTime;
      }
      
      dychisq_double = fit2.chiSquare;
      dyoffset_double = fit2.offset;
      dytdiffE1E2 = dyT2_double - dyT1_double;
      dytdiffE1E2cal = cal.dyclockcal*dytdiffE1E2;
      
      // calculate real amplitudes
      dyE1real_single = DDAS::AnalyticFit::pulseAmplitude(dyE1_single,dyE1steepness_single,dyE1decay_single,dyT1_single);
      dyE1real_double = DDAS::AnalyticFit::pulseAmplitude(dyE1_double,dyE1steepness_double,dyE1decay_double,dyT1_double);
      dyE2real_double = DDAS::AnalyticFit::pulseAmplitude(dyE2_double,dyE2steepness_double,dyE2decay_double,dyT2_double);

      // calibrated energies
      dyE1cal_single = cal.dyfitslope*dyE1real_single + cal.dyfitoffset;
      dyE1cal_double = cal.dyfitslope*dyE1real_double + cal.dyfitoffset;
      dyE2cal_double = cal.dyfitslope*dyE2real_double + cal.dyfitoffset;
    }
  }
}

//
// UnpackAnode
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
void TPSPMT::UnpackAnode(DDASRootFitHit* ddashit, TRandom3 &rng, TPSPMTCalibrator &cal, int pix)
{
  // extract hit information
  amultraw++; // raw multiplicty
  
  // put hit information into detector class
  // trace analysis
  auto trace = ddashit->GetTrace();
  if(trace.size() > 0) { // if threre is a trace, check for overflow
    aoverflow[pix] = ddashit->GetADCOverflowUnderflow(); // 1 if the trace overflows the ADC
    aoverflowcount++;
  }

  // time
  double time = ddashit->GetTime();
  // calibrated anode time
  double timecal = time - cal.tdiffdynode[pix];
  
  // Due to some odd events where the anodes have times but no energies, lets make sure that the
  // anode energy is reasonable as well before keeping any anode data.
  double energy = ddashit->GetEnergy() + rng.Rndm();
  aenergy[pix] = energy;
  double ec = cal.aslope[pix]*energy + cal.aoffset[pix];

  // the conditon for a good anode event is:
  // |t_anode-t_dynode| < dycoincwindow AND athresh < e_anode < auld.
  if(std::abs(timecal - dytime) < cal.dycoincwindow) {
    if(ec > cal.athresh[pix] && ec < cal.auld[pix]) {
      // in the case of multiple anode hits
      // save only the first anode hit info
      if(!ahit[pix]) { 
	ahit[pix] = 1;
	aecal[pix] = ec;
	asum += ec;
	atime[pix] = time;
	atimecal[pix] = timecal;
	amult++;
      }
      pixelmult[pix]++; // but do increment pixel mult
    } // end threshold and uld check
    
      // reset overflows to have a high energy
    if(aoverflow[pix] == 1) {
      // in the case of multiple anode hits
      // save only the first anode hit info
      if(!ahit[pix]) { 
	ahit[pix] = 1;
	aecal[pix] = 99999.;
	asum += 99999.;
	atime[pix] = time;
	atimecal[pix] = timecal;
	amult++;
      }	      
      pixelmult[pix]++; // but do increment pixel mult
    } // end overflow check      
  } // end coincidence check

}

//
// UnpackAnodePosition
//
// Function:
//   - anode position determination for building correlations
//   - performs linearized fit of x- and y-projections of anode energy to
//     reconstruct a 2D Lorentzian lineshape for the energy deposition
//
// Params:
//   - none
//
// Return:
//   - none
//
void TPSPMT::FitAnodePosition()
{
  TLinearSolver solver;
  solver.Reset();
  double anodexproj[npspmt] = {0.}; // x projection of 2D energy plot
  double anodeyproj[npspmt] = {0.}; // y projection of 2D energy plot

  // fill the projection histograms
  for(int i=0; i<nanodes; i++) {
    if(aecal[i] > 0) {
      int xpix = i % npspmt;
      int ypix = i / npspmt;
      // drop first and last row in y
      // *** specific to e17011! use with caution! *** 
      if(ypix > 0 && ypix < npspmt-1) {
	anodexproj[xpix] += aecal[i];
	anodeyproj[ypix] += aecal[i];
      }
    } // end anode energy check
  } // end loop over anodes

  // find maximum of x projection
  double max = -1;
  int xmax = -1;
  for(int i=0; i<npspmt; i++) {
    if(anodexproj[i] > max) {
      max = anodexproj[i];
      xmax = i;
    }
  }
  // same for y
  max = -1;
  int ymax = -1;
  for(int i=0; i<npspmt; i++) {
    if(anodeyproj[i] > max) {
      max = anodeyproj[i];
      ymax = i;
    }
  }

  /************************************************************************************
   * Anode position determination using the linear fitter. Positions
   * in x and y are found by fitting a Lorentzian lineshape to projections
   * along the x and y axes. Note that the reciprocal of the Lorentzian,
   *    1/L(x) = ((x-x0)^2 + sigma)/(A*sigma)
   * (where for convienience sigma = gamma^2) has the form
   *    1/L(x) = ax^2 + bx + c,
   * where
   *    a = 1/(A*sigma)
   *    b = -2*x0/(A*sigma)
   *    c = (x0^2 + sigma)/(A*sigma)
   * This function is linear in the parameters a, b, and c! For a fit function
   * f(x), the chisq is given by
   *    chisq = sum[ wi(yi - f(xi))^2 ]
   * where w is the weight, y is the observed data. The partial derivatives reduce 
   * to a matrix equation Mu = v where u are the fit parameters and v depends on the
   * observed data. The parameters can be determined by solving the matrix eqn.
   * In this case, the data is the reciprocal of the projection along the axis 
   * of interest, the weight is chosen to be yi^3 to account for both the 
   * data and the transformation and the fit function f(x) is the quadratic
   * given above.
   *
   * Fitting procedure:
   *   1. Take projection along the x- or y-axis
   *   2. Define matrix and vectors M, u, v
   *   3. Solve matrix equation
   *   4. Transform fit parameters back into Lorentzian parameters:
   *       x0 = -b/(2*a)
   *       sigma = (c - a*x0^2)/a
   *       A = 1/(a*sigma)
   *
   * Note: amplitudes are for the projections not the overall 2D distribution
   * though the x0 and sigma parameters are consistent with the 2D fit. One
   * can similarly linearize the 2D fit if the amplitude is important, but 
   * this is a much more tedious algebraic system to solve if all you're 
   * interested in is the position.
   ************************************************************************************/
  // fits
  const int dim = 3;
  // Lorentz solutions from the solver
  double Ampx = 0;
  double x0 = -1;
  double sigmax = 0;
  double Ampy = 0;
  double y0 = -1;
  double sigmay = 0;

  if(displaylinfitinfo) {
    std::cout << "Max projection: " << xmax << ", " << ymax << std::endl;
  }
  
  // x part  
  // calculate matrix elements and result vector from the data
  solver.dim = dim; // number of fit parameters
  for(int i=0; i<npspmt; i++) { // data bins only
    if(anodexproj[i] > 0) {
      double x = i + 0.5;
      double d = anodexproj[i];
      double y = 1.0/d;
      double w = d*d*d; // weight choice to account for data and transformation
      solver.chisq += w*y*y;
      solver.matrix[0][0] += w;
      solver.matrix[1][0] += w*x;
      solver.matrix[2][0] += w*x*x;
      solver.matrix[2][1] += w*x*x*x;
      solver.matrix[2][2] += w*x*x*x*x;
      solver.vector[0] += w*y;
      solver.vector[1] += w*y*x;
      solver.vector[2] += w*y*x*x;
    }
  }
  solver.matrix[0][1] = solver.matrix[1][0];
  solver.matrix[1][1] = solver.matrix[2][0];
  solver.matrix[0][2] = solver.matrix[2][0];
  solver.matrix[1][2] = solver.matrix[2][1];  
  
  if(solver.SolveLinEq() != 0) {
    // std::cout << "x: Matrix is not invertable! The system has no solution." << std::endl;
    lxamp = ERR_MINV;
    lxpos = ERR_MINV;
    lxgamma = ERR_MINV;
  } else {
    // transform back to Lorentzian parameters
    x0 = -solver.solution[1]/(2.0*solver.solution[2]);
    sigmax = (solver.solution[0]-solver.solution[2]*x0*x0)/solver.solution[2];
    Ampx = 1.0/(solver.solution[2]*sigmax);
    sigmax = sqrt(sigmax);
      
    // result is outside anode pixel range or the quadratic fit has no minimum
    if(x0 < 0) {
      lxamp = ERR_BADPOS;
      // lxpos = ERR_BADPOS;
      lxpos = xmax; // Use max from projection
      lxgamma = ERR_BADPOS;
    } else if(x0 > npspmt) {
      lxamp = ERR_BADPOS;
      // lxpos = ERR_BADPOS;
      lxpos = xmax; // Use max from projection
      lxgamma = ERR_BADPOS;
    } else if(solver.solution[2] < 0) {
      lxamp = ERR_CONCDOWN;
      lxpos = ERR_CONCDOWN;
      lxgamma = ERR_CONCDOWN;
    } else {
      lxamp = Ampx;
      lxpos = x0;
      lxgamma = sigmax;
    }
       
    if(displaylinfitinfo) {
      std::cout << "lineqsolver chisq: " << solver.chisq << std::endl;
      std::cout << "lineqsolver fit par: a: " << solver.solution[2] << " b: " << solver.solution[1] << " c: " << solver.solution[0] << std::endl;
      std::cout << "lineqsolver lor par: " << lxamp << " " << lxpos << " " << lxgamma << std::endl;
      std::cout << "lxpos        : " << lxpos << std::endl;
    }
    
  } // end processing x solver results

  solver.Reset();
    
  // y part
  // calculate matrix elements and result vector from the data
  solver.dim = dim;
  for(int i=0; i<npspmt; i++) {
    if(anodeyproj[i] > 0) {
      double x = i + 0.5;
      double d = anodeyproj[i];
      double y = 1.0/d;
      double w = d*d*d;
      solver.chisq += w*y*y;
      solver.matrix[0][0] += w;
      solver.matrix[1][0] += w*x;
      solver.matrix[2][0] += w*x*x;
      solver.matrix[2][1] += w*x*x*x;
      solver.matrix[2][2] += w*x*x*x*x;
      solver.vector[0] += w*y;
      solver.vector[1] += w*y*x;
      solver.vector[2] += w*y*x*x;
    }
  }
  solver.matrix[0][1] = solver.matrix[1][0];
  solver.matrix[1][1] = solver.matrix[2][0];
  solver.matrix[0][2] = solver.matrix[2][0];
  solver.matrix[1][2] = solver.matrix[2][1];  
  
  if(solver.SolveLinEq() != 0) {
    // std::cout << "y: Matrix is not invertable! The system has no solution." << std::endl;
    lyamp = ERR_MINV;
    lypos = ERR_MINV;
    lygamma = ERR_MINV;
  } else {      
    for(int i = 0; i < solver.dim; i++) {
      solver.chisq -= solver.solution[i]*solver.vector[i];
    }
      
    // transform back to Lorentzian parameters
    y0 = -solver.solution[1]/(2.0*solver.solution[2]);
    sigmay = (solver.solution[0]-solver.solution[2]*y0*y0)/solver.solution[2];
    Ampy = 1.0/(solver.solution[2]*sigmay);
    sigmay = sqrt(sigmay);

    // result is outside anode pixel range or the quadratic fit has no minimum
    if(y0 < 0) {
      lyamp = ERR_BADPOS;
      //lypos = ERR_BADPOS;
      lypos = ymax;
      lygamma = ERR_BADPOS;
    } else if(y0 > npspmt) {
      lyamp = ERR_BADPOS;
      //lypos = ERR_BADPOS;
      lypos = ymax;
      lygamma = ERR_BADPOS;
    } else if(solver.solution[2] < 0) {
      lyamp = ERR_CONCDOWN;
      lypos = ERR_CONCDOWN;
      lygamma = ERR_CONCDOWN;
    } else {
      lyamp = Ampy;
      lypos = y0;
      lygamma = sigmay;
    }
       
    if(displaylinfitinfo) {
      std::cout << "lineqsolver chisq: " << solver.chisq << std::endl;
      std::cout << "lineqsolver fit par: a: " << solver.solution[2] << " b: " << solver.solution[1] << " c: " << solver.solution[0] << std::endl;
      std::cout << "lineqsolver lor par: " << lyamp << " " << lypos << " " << lygamma << std::endl;
      std::cout << "lypos        : " << lypos << std::endl;
    }
    
  } // end processing x solver results
  
}
