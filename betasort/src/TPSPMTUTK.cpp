/*
 * TPSPMTUTK.cpp. Class methods PSPMTUTK detectors.
 * Contains methods for PSPMTUTK unpacker which applies 
 * calibration and performs threshold checks.
 * 
 * Author: A. Chester
 *
 */

#include "TPSPMTUTK.h"
#include "TGraph2D.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <fit_extensions.h>
#include <functions_analytic.h>


using namespace ddastoys;

ClassImp(TPSPMTUTK);

//
//  Default calibration parameters
// 
void TPSPMTUTKCalibrator::Initialize()
{
  // dynode
  dyoffset = 0.;
  dyslope = 1.;
  dyfitoffset = 0.;
  dyfitslope = 1.;
  dyclockcal = 4.; // 500 MSPS: 2 ns/sample, 250 MSPS 4 ns/sample, 100 MSPS 10 ns/sample
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
void TPSPMTUTKCalibrator::ReadCalFile(std::string name)
{
  std::cout << "Reading PSPMTUTK calibration from: " << name << std::endl;

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

	if(linenum < 4*nanodes_utk+1) {
	  std::stringstream linestream(line);
	  linestream >> location >> value;
  	  if(linenum < nanodes_utk+1) aslope[location-1] = value;
  	  else if(linenum < 2*nanodes_utk+1) aoffset[location-1] = value;
  	  else if(linenum < 3*nanodes_utk+1) athresh[location-1] = value;
  	  else if(linenum < 4*nanodes_utk+1) auld[location-1] = value;
  	} else {
	  std::stringstream linestream(line);
	  linestream >> value;
	  if(linenum == 4*nanodes_utk+1) dyslope = value;
  	  if(linenum == 4*nanodes_utk+2) dyoffset = value;
	  if(linenum == 4*nanodes_utk+3) dyfitslope = value;
  	  if(linenum == 4*nanodes_utk+4) dyfitoffset = value;
	  if(linenum == 4*nanodes_utk+5) dyclockcal = value;
  	  if(linenum == 4*nanodes_utk+6) dythresh = value;
  	  if(linenum == 4*nanodes_utk+7) dyuld = value;
	  if(linenum == 4*nanodes_utk+8) dycoincwindow = value;
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
void TPSPMTUTKCalibrator::ReadTimeCalFile(std::string name)
{
  std::cout << "Reading PSPMTUTK anode-dynode time calibration from: " << name << std::endl;

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
	if(linenum < nanodes_utk+1) tdiffdynode[location-1] = value;
      } else {
	//ignore line
	calfile.ignore(1000,'\n');
      }
    }
  }
  calfile.close();
}

// Read data file for position correction
void TPSPMTUTKCalibrator::ReadCorrFile(bool gain) 
{
  if(gain==0 || gain==1) {
    // read the two position files (x and y)
    std::string fname[2];
    std::string path = "/projects/e21062/DPS/betasort/cal/";

    // access the data
    if(gain==0) fname[0] = "lowxpos_data";
    if(gain==0) fname[1] = "lowypos_data";
    if(gain==1) fname[0] = "highxpos_data";
    if(gain==1) fname[1] = "highypos_data";

    std::string file;
    for(int axis=0; axis<2; axis++) {
      file=path+fname[axis];
      std::ifstream infile(Form("%s.txt",file.c_str()));
      if (!infile) {
        std::cerr << "Unable to open file "<<Form("%s\n",file.c_str());
        //return 1;
      }
      std::cerr << "Reading PSPMTUTK position correction from "<<Form("/projects/e21062/DPS/betasort/%s.txt\n",fname[axis].c_str());

      std::vector<double> firstRow;
      std::vector<std::vector<double>> data;
      std::string line;

      // Read the first row separately
      if (std::getline(infile, line)) {
        std::stringstream ss(line);
        double value;
        while (ss >> value) {
          firstRow.push_back(value);
        }
        data.push_back(firstRow);  // Optionally, add the first row to the data vector
      }
      double* firstrow = &firstRow[0]; // cast to array

      // Read the rest of the file
      while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::vector<double> row;
        double value;
        while (ss >> value) {
          row.push_back(value);
        }
        data.push_back(row);
      }
      infile.close();

      // Determine the dimensions of the array
      size_t numRows = data.size()-1;
      size_t numCols = numRows > 0 ? data[0].size() : 0;

      // Dynamically allocate the array
      double** calc_position = new double*[numRows];
      for (size_t i = 0; i < numRows; ++i) {
        calc_position[i] = new double[numCols];
      }

      // Copy data from vector to calc_position
      for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
          calc_position[i][j] = data[i+1][j];
        }
      }

      // make array of crystal centers' positions
      int ncenters = npspmt_utk;
      /* Here we make additional calibration points at pixels beyond
      the real size of the detector. This is needed to interpolate to the edge
      of the detector physical area. extra_points = 6 gives 3 calibration
      points beyond each edge.*/
      int extra_points = 6; 
      ncenters = npspmt_utk + extra_points;
      double centers[ncenters];
      for(int px=0; px<ncenters; px++) {
        centers[px] = (px - extra_points/2) + 0.5; 
      }
      

      int counter=0;
      for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
          corr_surface[axis]->SetPoint(counter,firstrow[j],calc_position[i][j],centers[i]);
          counter++;
        }
      }
      // this is to draw the calibration surface - for testing
      //corr_surface[axis]->Draw("surf1 p0");
      //corr_surface[axis]->SaveAs(Form("test_surface_%s.root",fname[axis].c_str()));
    }
  }
  else{
    std::cout<<"WRONG GAIN AT PSPMTUTK CALIBRATOR"<<std::endl;
  }
}

  
//
// Reset PSPMTUTK variables
//
void TPSPMTUTK::Reset()
{
  // dynode
  dytrace.clear();

  dyenergy.clear();
  dyecal.clear();
  dytime.clear();
  dytimecfd = 0;
  dycfdfailbit = 0;
  dyoverflow = 0;
  dymult = 0;
  std::fill(std::begin(dyenergies),std::end(dyenergies),0.);
  std::fill(std::begin(dytimes),std::end(dytimes),0.);

  denergy_qdc = 0;
  
  // fit information
  // single pulse
  dychisq_single.clear();
  dyE1_single.clear();
  dyE1real_single = 0;
  dyE1cal_single = 0;
  dyT1_single.clear();
  dyoffset_single.clear();
  dyE1steepness_single.clear();
  dyE1decay_single.clear();
  // double pulse
  dychisq_double.clear();
  dyE1_double.clear();
  dyE1real_double = 0;
  dyE1cal_double = 0;
  dyT1_double.clear();
  dyE1steepness_double.clear();
  dyE1decay_double.clear();
  dyE2_double.clear();
  dyE2real_double = 0;
  dyE2cal_double = 0;
  dyT2_double.clear();
  dyE2steepness_double.clear();
  dyE2decay_double.clear();
  dyoffset_double.clear();

  dytdiffE1E2 = 0.;
  dytdiffE1E2cal = 0.;

  // anode
  std::fill(std::begin(aenergy),std::end(aenergy),0.);
  std::fill(std::begin(aecal),std::end(aecal),0.);
  std::fill(std::begin(aenergy_qdc),std::end(aenergy_qdc),0.);
  asum = 0.;
  asum_qdc = 0.;
  std::fill(std::begin(atime),std::end(atime),0.);
  std::fill(std::begin(atimecal),std::end(atimecal),0.);
  std::fill(std::begin(aoverflow),std::end(aoverflow),0);
  aoverflowcount = 0;  
  amultraw = 0;
  amult = 0;
  std::fill(std::begin(pixelmult),std::end(pixelmult),0);
  // anode position
  xpos = -1.;
  ypos = -1.;
  xcal = -1.;
  ycal = -1.;

  // hit flags
  dyhit = 0;
  std::fill(std::begin(ahit),std::end(ahit),0);
  hit = 0;
  gain=-1;
}

//
// UnpackDynode
//
// Function:
//   - unpacks ADC information into detector class
//   - specific to PSPMTUTK dynode to handle trace analysis
//
// Params:
//   - pointer to a DDAS hit data structure
//   - calibration parameters
//
// Return:
//   - none
//
void TPSPMTUTK::UnpackDynode(DDASRootFitHit* ddashit, TRandom3 &rng, TPSPMTUTKCalibrator &cal)
{
	// extract hit information
	// put hit information into detector class
	// trace analysis
	auto trace = ddashit->getTrace();
	if(trace.size() > 0) { // if threre is a trace, check for overflow
		dyoverflow = ddashit->getADCOverflowUnderflow(); // 1 if the trace overflows the ADC
	}

	dytrace = ddashit->getTrace();

	// time
	dytime.push_back(ddashit->getTime());
	dytimecfd = ddashit->getTimeCFD();
	dycfdfailbit = ddashit->getCFDFailBit(); // no Get();
  
	// energy (from Pixie)
	dyenergy.push_back(ddashit->getEnergy() + rng.Rndm());


	for(int k=0; k<dyenergy.size(); k++)
		dyecal.push_back(cal.dyslope*dyenergy[k] + cal.dyoffset);

	if(dyecal.at(0) > cal.dythresh && dyecal.at(0) < cal.dyuld) {
		if(!dyhit) dyhit = 1;
	}

	std::vector<uint32_t> qdcSums = ddashit->getQDCSums();

	if(qdcSums.size() > 0) { // if the QDC sum vector isn't empty, set the energy
		denergy_qdc = qdcSums[0] - qdcSums[2];
	}

	// reset overflows to have a high energy
	if(dyoverflow == 1) {
		if(!dyhit) dyhit = 1; // overflows still a good hit
		dyenergy.at(0) = 99999.;
		dyecal.at(0) = 99999.;
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
void TPSPMTUTK::UnpackDynodeFit(DDASRootFitHit* ddashit, TPSPMTUTKCalibrator &cal, int i)
{
  if (ddashit->hasExtension()) {
    HitExtension ext = ddashit->getExtension();
      fit1Info fit1 = ext.onePulseFit;
      fit2Info fit2 = ext.twoPulseFit;      
      
      // assign single pulse fit results
      dyE1_single.push_back(fit1.pulse.amplitude);
      dyT1_single.push_back(fit1.pulse.position);
      
      // comment out for template fitting
      dyE1steepness_single.push_back(fit1.pulse.steepness);
      dyE1decay_single.push_back(fit1.pulse.decayTime);
      
      dyoffset_single.push_back(fit1.offset);
      dychisq_single.push_back(fit1.chiSquare);

      // check organization for defining E2 to be the second pulse
      if(fit2.pulses[0].position < fit2.pulses[1].position) {
	dyE1_double.push_back(fit2.pulses[0].amplitude);
	dyT1_double.push_back(fit2.pulses[0].position);
	
	// comment out for template fitting
	dyE1steepness_double.push_back(fit2.pulses[0].steepness);
	dyE1decay_double.push_back(fit2.pulses[0].decayTime);
	
	dyE2_double.push_back(fit2.pulses[1].amplitude);
	dyT2_double.push_back(fit2.pulses[1].position);

	// comment out for template fitting
	dyE2steepness_double.push_back(fit2.pulses[1].steepness);
	dyE2decay_double.push_back(fit2.pulses[1].decayTime);	
      } 
	
	else {	
	dyE1_double.push_back(fit2.pulses[1].amplitude);
	dyT1_double.push_back(fit2.pulses[1].position);

	// comment out for template fitting
	dyE1steepness_double.push_back(fit2.pulses[1].steepness);
	dyE1decay_double.push_back(fit2.pulses[1].decayTime);
	
	dyE2_double.push_back(fit2.pulses[0].amplitude);
	dyT2_double.push_back(fit2.pulses[0].position);

	// comment out for template fitting
	dyE2steepness_double.push_back(fit2.pulses[0].steepness);
	dyE2decay_double.push_back(fit2.pulses[0].decayTime);
      }
      
      dychisq_double.push_back(fit2.chiSquare);
      dyoffset_double.push_back(fit2.offset);

      dytdiffE1E2 = dyT2_double.at(0) - dyT1_double.at(0);
      dytdiffE1E2cal = cal.dyclockcal*dytdiffE1E2;
      
      // calculate real amplitudes
      dyE1real_single = analyticfit::pulseAmplitude(dyE1_single.at(0),dyE1steepness_single.at(0),dyE1decay_single.at(0),dyT1_single.at(0));
      dyE1real_double = analyticfit::pulseAmplitude(dyE1_double.at(0),dyE1steepness_double.at(0),dyE1decay_double.at(0),dyT1_double.at(0));
      dyE2real_double = analyticfit::pulseAmplitude(dyE2_double.at(0),dyE2steepness_double.at(0),dyE2decay_double.at(0),dyT2_double.at(0));

      // calibrated energies
      dyE1cal_single = cal.dyfitslope*dyE1real_single + cal.dyfitoffset;
      dyE1cal_double = cal.dyfitslope*dyE1real_double + cal.dyfitoffset;
      dyE2cal_double = cal.dyfitslope*dyE2real_double + cal.dyfitoffset;
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
void TPSPMTUTK::UnpackAnode(DDASRootFitHit* ddashit, TRandom3 &rng, TPSPMTUTKCalibrator &cal, int pix)
{
  // extract hit information
  amultraw++; // raw multiplicty
  
  // put hit information into detector class
  // trace analysis
  auto trace = ddashit->getTrace();
  //if(trace.size() > 0) { // if threre is a trace, check for overflow
    aoverflow[pix] = ddashit->getADCOverflowUnderflow(); // 1 if the trace overflows the ADC
    if(aoverflow[pix] == 1) {
      aoverflowcount++;
    }
  //}

  // time
  double time = ddashit->getTime();
  // calibrated anode time
  double timecal = time - cal.tdiffdynode[pix];
  
  // Due to some odd events where the anodes have times but no energies, lets make sure that the
  // anode energy is reasonable as well before keeping any anode data.
  double energy = ddashit->getEnergy() + rng.Rndm();
  aenergy[pix] = energy;
  double ec = cal.aslope[pix]*energy + cal.aoffset[pix];
  
  // the conditon for a good anode event is:
  // |t_anode-t_dynode| < dycoincwindow AND athresh < e_anode < auld.
  if(std::abs(timecal - dytime.front()) < cal.dycoincwindow) {
    if(ec > cal.athresh[pix] && ec < cal.auld[pix]) {
      // in the case of multiple anode hits
      // save only the first anode hit info
      if(!ahit[pix]) {	
	      ahit[pix] = 1;
	      // get QDC sums
	      std::vector<uint32_t> qdcSums = ddashit->getQDCSums();
	      if(qdcSums.size() > 0) { // if the QDC sum vector isn't empty, set the energy
	        aenergy_qdc[pix] = qdcSums[0] - qdcSums[2];
	        asum_qdc += aenergy_qdc[pix];
	      }
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
	      // get QDC sums
	      std::vector<uint32_t> qdcSums = ddashit->getQDCSums();
	      if(qdcSums.size() > 0) { // if the QDC sum vector isn't empty, set the energy
	        aenergy_qdc[pix] = qdcSums[0] - qdcSums[2];
	        asum_qdc += aenergy_qdc[pix];
	      }
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
// Position_Correction
//
// Function:
//   - uses a data driven interpolation to correct and calibrate the positions
//     of the PSPMT_UTK by applying a calibration which is energy-dependent.
//
// Params:
//   - cal - the calibration object which knows about the calibration surface
//   - input_pos - the uncalibrated x or y position
//   - input_energy - the energy measured from the dynode
//   - axis - indicates the x or y axis so that the correct
//     correction/calibration file gets loaded and the is applied correctly
//     false/0 for x-axis, true/1 for y-axis
//
// Return:
//   - the corrected and calibrated position or -10 initialization value
//

double TPSPMTUTK::Position_Correction(TPSPMTUTKCalibrator &cal, double input_pos=-1., double input_energy=-1., int axis=-1) {

  double corrected_pos = -10;
  
  if(input_energy>=0. && input_energy<= 65000 && (axis==0 || axis==1)) 
  {
    corrected_pos = cal.corr_surface[axis]->Interpolate(input_energy,input_pos);
    //std::cout<<Form("gain: %d       axis: %d        dyenergy: %f       pos: %f      corrected_pos: %f",gain,axis,input_energy,input_pos,cal.corr_surface[axis]->Interpolate(input_energy,input_pos))<<std::endl;
  }

  return corrected_pos;
}

//
// UnpackAnodePosition
//
// Function:
//   - anode position determination for building correlations
//   - uses 4 corner anodes energies/qdcs to extract position
//
// Params:
//   - highgain: false for low gain and true for high gain. low gain channel needs a correction that 
//     high gain channel doesn't
//
// Return:
//   - none
//


void TPSPMTUTK::FitAnodePosition(TPSPMTUTKCalibrator &cal)
{
  // check to see if all the QDC sums are set
  bool check = true;
  
  for(int i=0; i<nanodes_utk; i++) { // really hacky check to see if all the energies are good
    if(aenergy_qdc[i] > 0) {
      check &= true;
    } else {
      check &= false;
    }
  }
  
  // if all the QDC sums are present calculate the position
  // position set to error values if out of range or not all
  // QDC sums are present for the current event
  if(check == true && dytrace.size()>0) {

    auto max = *std::max_element(dytrace.begin(),dytrace.end());

	double baseline = 0.;
	for(long unsigned int i=0; i<10; i++) {
	  baseline += dytrace.at(i);
	}

	baseline /= 10;
	double amplitude = max - baseline;

	double area = 0.;
	for(long unsigned int i=0; i<dytrace.size(); i++) {
	  area += dytrace.at(i);
	}

	area -= dytrace.size()*baseline;


	double xa = aenergy_qdc[0];
	double xb = aenergy_qdc[1];
    	double ya = aenergy_qdc[2];
    	double yb = aenergy_qdc[3];

	if(gain == 0){  // LG

		// DPS position correction
		//xpos = (((ya + xb)/asum_qdc)-0.5)/(1-0.45*pow(area/1e6, 0.6));
		//ypos = (((xa + xb)/asum_qdc)-0.5)/(1-0.2*pow(area/1e6, 0.6));

	      //xcal = Position_Correction(cal, xpos, dyenergy.at(0), 0);
	      //ycal = Position_Correction(cal, ypos, dyenergy.at(0), 1);

	      //xpos=xcal;
	     //ypos=ycal;

		// Old position correction
		xpos = ((6*(ya + xb)/asum_qdc)-3)/(1-0.45*pow(area/1e6, 0.6));
	    	ypos = ((6*(xa + xb)/asum_qdc)-3)/(1-0.2*pow(area/1e6, 0.6));


		xpos = xpos * 6.4 + 11.9;
		ypos = ypos * 6.1 + 12.0;




	
	}

	else if(gain == 1){  // HG

		// DPS position correction
	      //xpos = ((ya + xb)/asum_qdc)-0.5;
      		//ypos = ((xa + xb)/asum_qdc)-0.5;	

		  //xcal = Position_Correction(cal, xpos, dyenergy.at(0), 0);
	      //ycal = Position_Correction(cal, ypos, dyenergy.at(0), 1);

	      //xpos=xcal;
	      //ypos=ycal;

		// Old position correction
		xpos = npspmt_utk*(ya + xb)/asum_qdc;
	    	ypos = npspmt_utk*(xa + xb)/asum_qdc;	


		xpos = xpos * 1.6 - 7.8;
		ypos = ypos * 1.5 - 6.0;





	}

	if(xpos < 0 || xpos > npspmt_utk){
	      	xpos = ERR_BADPOS;
		xcal = ERR_BADPOS;
	}
    	if(ypos < 0 || ypos > npspmt_utk){
	      	ypos = ERR_BADPOS;
		ycal = ERR_BADPOS;
	}

    	
  } else {
    xpos = ERR_QDCMULT;
    ypos = ERR_QDCMULT;
	xcal = ERR_QDCMULT;
	ycal = ERR_QDCMULT;
  }
  
}
