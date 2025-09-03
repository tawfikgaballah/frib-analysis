#include "TCorrelator.h"
#include "TCutG.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include <cmath>

#include "TParameters.h"

/****************************************
 * Correlation flags:                   *
 * ==================================== *
 * 4  - implant good position           *
 * 8  - implant bad position            *
 * 12 - decay good position             *
 * 16 - decay bad position              *
 * 20 - light ion                       *
 * 28 - decay before ion (BAD!)         *
 * 32 - good correlation                *
 * 44 - no implants to correlate        *
 * 56 - Clover only
 * 96 - unknown event                   *
 * ==================================== *
 * 99 - Reset correlation aray          * 
 ****************************************/


// Implant reset function
void TImplant::Reset()
{
  implanted = false;
  dyecal = 0;      // Dynode energy
  time = 0;        // Time of event
  de1 = 0;         // dE from Pin01
  de2 = 0;         // dE from Pin02
  tof = 0;         // TOF from some PIN/separator
  scintScintTOF = 0.; // TOF
  dtLastIon = 0;   // Time since last implant 

  // Trace fit information
  dychisq_single = 0;
  dyE1real_single = 0;
  dyT1_single = 0;
  dychisq_double = 0;
  dyE1real_double = 0;
  dyT1_double = 0;
  dyE2real_double = 0;
  dyT2_double = 0;
  dytdiffE1E2cal = 0;
  
  // interaction position
  xpos = -1.;
  ypos = -1.;

}


// Lets make sure we are making the correlator only once
TCorrelator::TCorrelator()
{
  std::cout << "Starting correlator..." << std::endl;
}

// Reset
//
// Function:
//   - reset correlation arrays
//
// Params:
//   - none
//
// Return:
//   - none
//
void TCorrelator::Reset()
{
  std::cout << "Resetting correlator array..." << std::endl;
  for(int i=0; i<npspmt_CeBr; i++) {
    for(int j=0; j<npspmt_CeBr; j++) {
      fImplant[i][j].Reset();
      fImplantVector[i][j].clear();
    }
  }
  fCorrelatedImplants.clear();
}

// Correlate
//
// Function:
//   - correlate decays with implanted ions by examining the relative position
//     and time of the implant and decay events.
//
// Params:
//   - beta decay parameters (i.e. detector classes)
//   - beta decay variables (i.e. calibration parameters, thresholds, etc.)
//
// Return:
//   - 0 if successful (valid correlation flag)
//   - 1 otherwise
//
int TCorrelator::Correlate(TBetaDecayParams &bdecay)
{
	// Reset correlator
	int condition = 96; // inital condition is unknown event
	if(bdecay.var.corr.reset == 1) {
		TCorrelator::Reset(); 
		bdecay.corr.flag = 99; // Set the reset flag
		bdecay.var.corr.reset = 0; 
	}

	// Get time
	double current_time = 0;
	if(bdecay.clock.initial > 0) {
		current_time = bdecay.clock.initial / 1.e6; // Time in ms
	} else {
		//    std::cout << "Invalid time: " << bdecay.clock.initial << " something is very wrong!" << std::endl;;
		return 1; // bad
	}

	// signal flags
	bool hasPSPMT = false;      // PSPMT 
	bool hasPin = false;           // any PIN hit
	bool hasPin01 = false;
	bool hasPin02 = false;
	bool hasPinImplant = false;    // implant-like events above implant threshold
	bool hasPin01Implant = false;
	bool hasPin02Implant = false;
	bool hasPinLightIon = false;   // light ion events below implant threshold
	bool hasPin01LightIon = false;
	bool hasPin02LightIon = false;
	bool hasClover = false;  // put hit information into detector class
	bool hasScint = false;
	//... and others (clover, LaBr3, etc.)

	// event identification
	bool isImplant = false;
	bool isDecay = false;
	bool isCloverOnly = false;
	bool isLightIon = false;
	bool isUnidentified = false;
	//... and others (clover only, LaBr3 only etc.)

	// PSPMT positions
	int xPos = -1;
	int yPos = -1;

	/*********************************
	 *** Event Type Identification ***
	 *********************************/
  
	// Hit flags are set in TUnpacker.cpp
	//
	// PSPMT 2 for gamma crate
	if(bdecay.NpspmtCeBr.hit == 1) {
		hasPSPMT = true;
	}
	if(bdecay.NpspmtCeBr.dyecal.size()>0){
	  if(bdecay.NpspmtCeBr.dyecal.at(0)>1){
	    hasPSPMT = true;
	  }
	}

  
	// Pin01 implant vs light ions
	if(bdecay.pin01.hit == 1) {
		hasPin01 = true;
		if(bdecay.pin01.ecal > bdecay.var.pin01.ithresh) {
			hasPin01Implant = true;
		} else {
			hasPin01LightIon = true;
		}
	}
  
	// Pin02 implant vs light ions
	if(bdecay.pin02.hit == 1) {
		hasPin02 = true;
		if(bdecay.pin02.ecal > bdecay.var.pin02.ithresh) {
			hasPin02Implant = true;
		} else {
			hasPin02LightIon = true;
		}
	}

	if(bdecay.clover.hit == 1){
		hasClover = true;
		bdecay.corr.hasclover = true;
	}

	if(bdecay.xscintT.hit == 1){
		hasScint = true;
	}

	if(hasPin01 || hasPin02) {hasPin = true;}// any PIN is hit    
	if(hasPin01Implant && hasPin02Implant) { hasPinImplant = true;}// implants only
	if(hasPin01LightIon && hasPin02LightIon) {hasPinLightIon = true;} // light ions only

	// advanced event type identificaton
	// implant event identification
	if(hasPSPMT && hasPinImplant) {
		isImplant = true;
		bdecay.corr.isimplant = 1;
	}

	// light ion event identification
	if(hasPSPMT && (!hasPin01Implant && !hasPin02Implant) && hasScint) { 
		isLightIon = true;
		bdecay.corr.islightion = 1;
	}

 
	// decay event identification
	if(hasPSPMT && !hasScint && bdecay.DB3P1AT.energy==0){
		isDecay = true;
		bdecay.corr.isdecay = 1;
	}

	// clover only event  
	if(!hasPin && !hasPSPMT && hasClover){
		isCloverOnly = true;
		bdecay.corr.iscloveronly = 1;
	}

	// everything else
	if(!isImplant && !isDecay && !isLightIon && !isCloverOnly) { // something besides stuff in the PSPMT (for now)
		isUnidentified = true;
	}

	
  /*********************************
   ***    Build correlations     ***
   *********************************/


  bool hasGoodPosition = false;
  //____________________________________________________________
  // Implant
	if(isImplant) {
//std::cout<<"is implant" << std::endl;
		// Get position info from the anode energy distribution fit
		xPos = int(bdecay.NpspmtCeBr.lxpos);
		yPos = int(bdecay.NpspmtCeBr.lypos);
		//std::cout << "implant " << xPos << " " << yPos <<std::endl;

		// check if the position is good
		if((xPos >=0 && xPos < npspmt_CeBr) && (yPos >=0 && yPos < npspmt_CeBr)) {
			condition = 4; // implant flag
			hasGoodPosition = true;
//std::cout<<"good pos"<<std::endl;

		} else {
			condition = 8; // bad implant position	
//std::cout<<"bad pos"<<std::endl;
		}
//std::cout<<xPos << " " <<yPos<<std::endl;
		// If there is a good implant position, continue processing the event
		if(hasGoodPosition) {
//std::cout<<"good pos"<<std::endl;
			double timeDiffIon = -1.;
			if(fImplant[xPos][yPos].time >= 0) {
//std::cout<<"good time"<<std::endl;			
				// Note: need abs(timeDiffIon) for reverse correlation!
				timeDiffIon = std::abs(current_time - fImplant[xPos][yPos].time);
				if(timeDiffIon > 0) {	    
					// Check for existing implant in this pixel
					if(fImplant[xPos][yPos].implanted) {
						fImplant[xPos][yPos].dtLastIon = timeDiffIon;
					} else {
						// If the time and position are good, count this spot as implanted
  	    		// if it hasn't already been
  	    		fImplant[xPos][yPos].implanted = true;
  	  		}

  	  		// Assign values -- this overwrites the previous implant in this position
			if (!bdecay.NpspmtCeBr.dyecal.empty())
			fImplant[xPos][yPos].dyecal = bdecay.NpspmtCeBr.dyecal.at(0);
  	  		fImplant[xPos][yPos].time = current_time;
  	  		fImplant[xPos][yPos].de1 = bdecay.pid.de1;
			fImplant[xPos][yPos].de2 = bdecay.pid.de2;
			fImplant[xPos][yPos].tof = bdecay.pid.tof;

  	  		// Store the fit information
			if (!bdecay.NpspmtCeBr.dychisq_single.empty()){
  	  		fImplant[xPos][yPos].dychisq_single = bdecay.NpspmtCeBr.dychisq_single.at(0);
  	  		fImplant[xPos][yPos].dyE1real_single = bdecay.NpspmtCeBr.dyE1_single.at(0);
 
  	  		fImplant[xPos][yPos].dyT1_single = bdecay.NpspmtCeBr.dyT1_single.at(0);
  	  		fImplant[xPos][yPos].dychisq_double = bdecay.NpspmtCeBr.dychisq_double.at(0);
  	  		fImplant[xPos][yPos].dyE1real_double = bdecay.NpspmtCeBr.dyE1_double.at(0);

  	  		fImplant[xPos][yPos].dyT1_double = bdecay.NpspmtCeBr.dyT1_double.at(0);
  	  		fImplant[xPos][yPos].dyE2real_double = bdecay.NpspmtCeBr.dyE2_double.at(0);

  	  		fImplant[xPos][yPos].dyT2_double = bdecay.NpspmtCeBr.dyT2_double.at(0);
			}
  	  		fImplant[xPos][yPos].dytdiffE1E2cal = bdecay.NpspmtCeBr.dytdiffE1E2cal;
			fImplant[xPos][yPos].xpos = bdecay.NpspmtCeBr.lxpos;
			fImplant[xPos][yPos].ypos = bdecay.NpspmtCeBr.lypos;
	  
			// Add implant to list of implants in that pixel
  	  		fImplantVector[xPos][yPos].push_back(fImplant[xPos][yPos]);	

	  
   	  		// Set the implant output
			bdecay.corr.idyecal = fImplant[xPos][yPos].dyecal;
  	  		bdecay.corr.itime = fImplant[xPos][yPos].time;
  	  		bdecay.corr.ide1 = fImplant[xPos][yPos].de1;
			bdecay.corr.ide2 = fImplant[xPos][yPos].de2;
			bdecay.corr.itof = fImplant[xPos][yPos].tof;
			bdecay.corr.dtimplant = fImplant[xPos][yPos].dtLastIon;
  	  		bdecay.corr.ixpos = fImplant[xPos][yPos].xpos;
  	  		bdecay.corr.iypos = fImplant[xPos][yPos].ypos;	  
			// Trace fit information
			bdecay.corr.idychisq_single = fImplant[xPos][yPos].dychisq_single;
			bdecay.corr.idyE1real_single = fImplant[xPos][yPos].dyE1real_single;
	
			bdecay.corr.idyT1_single = fImplant[xPos][yPos].dyT1_single;
			bdecay.corr.idychisq_double = fImplant[xPos][yPos].dychisq_double;
			bdecay.corr.idyE1real_double = fImplant[xPos][yPos].dyE1real_double;

			bdecay.corr.idyT1_double = fImplant[xPos][yPos].dyT1_double;
			bdecay.corr.idyE2real_double = fImplant[xPos][yPos].dyE2real_double;

			bdecay.corr.idyT2_double = fImplant[xPos][yPos].dyT2_double;
			bdecay.corr.idytdiffE1E2cal = fImplant[xPos][yPos].dytdiffE1E2cal;	  
		} // End implant time difference check
      } // End good implant time check 
    } // End good implant position check
  } // End implant analysis
  //____________________________________________________________
  // Decay
	else if(isDecay) {

			xPos = int(bdecay.NpspmtCeBr.lxpos);
			yPos = int(bdecay.NpspmtCeBr.lypos);
			//std::cout << "decay " << xPos << " " << yPos <<std::endl;

    
		// Decay position check
		// Note that the 16x16 anode is 0 indexed on both axes!
		if(xPos >=0 && xPos < npspmt_CeBr &&
			yPos >= 0 && yPos < npspmt_CeBr) {
			condition = 12;
			hasGoodPosition = true;
		} else {
			condition = 16;
		}

		if(hasGoodPosition) {

			// Perform the correlation. Search the correlation grid for implants
			// which satisfy the time difference requirement. Note: time differences
			// must be abs(tdiff) for reverse correlation!
			int corrGridLimit = (fCorrWin - 1)/2; // for fCorrWin = 3, corrGridLimit = 1

			for(int i=(-corrGridLimit); i<(corrGridLimit+1); i++) {
				for(int j=(-corrGridLimit); j<(corrGridLimit+1); j++) {
					if((xPos+i) >= 0 && (xPos+i) < npspmt_CeBr &&
					(yPos+j) >= 0 && (yPos+j) < npspmt_CeBr) { // Good correlation grid position
						// Loop over implanted ion vector for position checking. Also need a
						// software limit correlation window so that our lists dont get too big.
						// Use correlation window defined in the variables. All time limits for
						// e.g. implant half-lives are done at histogramming step.									

						double it = 0;
						for(auto & ion : fImplantVector[xPos+i][yPos+j]) {		
							if(std::abs(current_time - ion.time) > bdecay.var.corr.corrwindow) {	
								fImplantVector[xPos+i][yPos+j].erase(fImplantVector[xPos+i][yPos+j].begin()+it);
							} else {
								it++;
								// If ion is within corrwindow add it to list of implants correlated with decay event
								TPID implantStore;
								implantStore.Reset();
								implantStore.time = ion.time;
								implantStore.de1 = ion.de1;
								implantStore.de2 = ion.de2;
								implantStore.tof = ion.tof;

								implantStore.xpos = ion.xpos;
								implantStore.ypos = ion.ypos;

								
								// Euclidian distance check between locations
					double x1 = bdecay.NpspmtCeBr.lxpos;
					double x2 = ion.xpos;
					double y1 = bdecay.NpspmtCeBr.lypos;
					double y2 = ion.ypos;

								double distance = std::sqrt(std::pow((x2-x1),2.0) + std::pow((y2-y1),2.0)); 

								if(distance < corrGridLimit) {	

									fCorrelatedImplants.push_back(implantStore);

				      bdecay.corr.dde1 = ion.de1;
	      			      bdecay.corr.dde2 = ion.de2;
	    			      bdecay.corr.dtof = ion.tof;
		  
								}
							}  // End store of correlated ions
						} // End loop over ion list
					} // End good position check
				}
			} // End correlation grid search
      
      if(fCorrelatedImplants.size() > 0) {
				condition = 32; // at least one ion correlated to this decay
      } else {
				condition = 44; // no implant in correlation field
      }

      // Set decay output
	  if (!bdecay.NpspmtCeBr.dyecal.empty())
      bdecay.corr.ddyecal = bdecay.NpspmtCeBr.dyecal.at(0);
      bdecay.corr.dtime = current_time;
      bdecay.corr.dxpos = bdecay.NpspmtCeBr.lxpos;
      bdecay.corr.dypos = bdecay.NpspmtCeBr.lypos;

      // Store the fit information
	  if (!bdecay.NpspmtCeBr.dychisq_single.empty()){
      bdecay.corr.ddychisq_single = bdecay.NpspmtCeBr.dychisq_single.at(0);
      bdecay.corr.ddyE1real_single = bdecay.NpspmtCeBr.dyE1_single.at(0);

      bdecay.corr.ddyT1_single = bdecay.NpspmtCeBr.dyT1_single.at(0);
      bdecay.corr.ddychisq_double = bdecay.NpspmtCeBr.dychisq_double.at(0);
      bdecay.corr.ddyE1real_double = bdecay.NpspmtCeBr.dyE1_double.at(0);
 
      bdecay.corr.ddyT1_double = bdecay.NpspmtCeBr.dyT1_double.at(0);
      bdecay.corr.ddyE2real_double = bdecay.NpspmtCeBr.dyE2_double.at(0);

      bdecay.corr.ddyT2_double = bdecay.NpspmtCeBr.dyT2_double.at(0);
      bdecay.corr.ddytdiffE1E2cal = bdecay.NpspmtCeBr.dytdiffE1E2;
	}
    } // End good decay position check    
  } // End decay analysis


	
  //____________________________________________________________
  // Light ion
  else if(isLightIon) {
    condition = 20;
  }
  //____________________________________________________________
  // Everything else
  else {
    condition = 96; // Unknown event type, probably redundant
  }

// Clover events
	//else if(isCloverOnly){
	if(hasClover){
		if(isCloverOnly)
			condition = 56;
		// may want to move this corrwin variable elsewhere
		double corrwin = 1;  // 1ms
		for(int det = 0; det < totcrystals; det++){
			// is 10 keV a reasonable threshold here?
			if(bdecay.clover.ecal[det] > 10){
				// Initialize temp vars. For storing temp info on current implant with smallest tdiff
				double mintdiff = corrwin+1; //  Initialize to > corrwin
				double temp_gtof = 0.;
				double temp_gde2 = 0.;
				double temp_gitime = 0.;
				double temp_clovertime = 0.;
				double temp_tdiff = 0.;
				// Can't get position info from clovers but implants are still indexed by PSPMT row x column so we'll search whole grid
				for(int i=0; i < npspmt_CeBr; i++){
					for(int j=0; j < npspmt_CeBr; j++){
						// Loop over implants
						double it=0;
							
							for(auto & ion : fImplantVector[i][j]) {
								
								double tdiff = bdecay.clover.time[det] / 1.e6 - ion.time;  // assuming ns here?
								// We only really care if the implant is in the correlation window AND it has the smallest tdiff yet
								if((tdiff < mintdiff) && (std::abs(tdiff) < corrwin)){
									mintdiff = tdiff;
									temp_clovertime = bdecay.clover.time[det];
									bdecay.corr.giscorr = true; 
									temp_gtof = ion.tof;
									temp_gde2 = ion.de2;
									temp_gitime = ion.time;
									it++;
				
						  		}  // end correlation window check 
							}  // end loop over implant vector
						//}					
					}  
				}  // end loop over PSPMT
				// no need to change anything in events w/ numcorr = 0
				if(bdecay.corr.giscorr == true){
					bdecay.corr.gtof = temp_gtof;
					bdecay.corr.gde2 = temp_gde2;
					bdecay.corr.gitime = temp_gitime;
					bdecay.corr.gtime = temp_clovertime;
					bdecay.corr.gitdiff = mintdiff;			
				}
				// making an assumption; that tdiff will be roughly the same for each gamma bc they
				// are emitted close in time. So, findding one correlated ion for one non-trivial gamma
				// is enough for the entire event. Thus when we're done saving info for the first 
				// non-trivial gamma hit, we can stop searching the other gamma crystals
				break;
			}	 // end energy threshold check
		}  // end loop over crystals
	}  // end clover only

    
  bool printevent = false;
  if(condition == 32 && printevent) {
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "condition  " << condition << std::endl;

    std::cout << "----- PIN detectors -----" << std::endl;
    std::cout << "hit.pin01  " << bdecay.pin01.hit << " energy " << bdecay.pin01.energy << " ecal " << bdecay.pin01.ecal << " time " << bdecay.pin01.time << std::endl;
    std::cout << "hit.pin02  " << bdecay.pin02.hit << " energy " << bdecay.pin02.energy << " ecal " << bdecay.pin02.ecal << " time " << bdecay.pin02.time << std::endl;

    std::cout << "----- PSPMT dynode high gain -----" << std::endl;
//    std::cout << "hit.dynode " << bdecay.NpspmtCeBr.dyhit << " energy " << bdecay.NpspmtCeBr.dyenergy << " ecal " << bdecay.NpspmtCeBr.dyecal << " time " << std::setprecision(12) << bdecay.NpspmtCeBr.dytime << std::endl;
    std::cout << "lxpos " << std::setprecision(5) << bdecay.NpspmtCeBr.lxpos << " lypos " << bdecay.NpspmtCeBr.lypos << std::endl;
//    std::cout << "dynode fit: E1single " << bdecay.NpspmtCeBr.dyE1real_single << " E1dobule " << bdecay.NpspmtCeBr.dyE1real_double << " E2double " << bdecay.NpspmtCeBr.dyE2real_double << std::endl;
    std::cout << "dynode mult " << bdecay.NpspmtCeBr.dymult << std::endl;
    for(int i=0; i<bdecay.NpspmtCeBr.dymult; i++) {
      std::cout << "dynode[" << i << "] " << std::setprecision(12) << bdecay.NpspmtCeBr.dytimes[i] << std::endl;
    }
    std::cout << "hit.NpspmtCeBr " << bdecay.NpspmtCeBr.hit << std::endl;
    std::cout << "anode mult high " << bdecay.NpspmtCeBr.amult << std::endl;

    std::cout << "----- PSPMT dynode low gain -----" << std::endl;
//    std::cout << "hit.dynode " << bdecay.pspmtlow1.dyhit << " energy " << bdecay.NpspmtCeBr.dyenergy << " ecal " << bdecay.NpspmtCeBr.dyecal << " time " << std::setprecision(12) << bdecay.NpspmtCeBr.dytime << std::endl;
        std::cout << "lxpos " << std::setprecision(5) << bdecay.NpspmtCeBr.lxpos << " lypos " << bdecay.NpspmtCeBr.lypos << std::endl;
//    std::cout << "dynode fit: E1single " << bdecay.NpspmtCeBr.dyE1real_single << " E1dobule " << bdecay.NpspmtCeBr.dyE1real_double << " E2double " << bdecay.NpspmtCeBr.dyE2real_double << std::endl;
    std::cout << "dynode mult " << bdecay.NpspmtCeBr.dymult << std::endl;
    for(int i=0; i<bdecay.NpspmtCeBr.dymult; i++) {
      std::cout << "dynode[" << i << "] " << std::setprecision(12) << bdecay.NpspmtCeBr.dytimes[i] << std::endl;
    }
    std::cout << "hit.NpspmtCeBr " << bdecay.NpspmtCeBr.hit << std::endl;
    std::cout << "anode mult low " << bdecay.NpspmtCeBr.amult << std::endl;

    std::cout << "----- Detector hit flags -----" << std::endl;
    std::cout << "hasPin " << hasPin << std::endl;
    std::cout << "hasPin01Implant " << hasPin01Implant << std::endl;
    std::cout << "hasPin02Implant "<< hasPin02Implant << std::endl;
    std::cout << "hasPin01LightIon " << hasPin01LightIon << std::endl;
    std::cout << "hasPin02LightIon " << hasPin02LightIon << std::endl;
    std::cout << "hasPinLightIon " << hasPinLightIon << std::endl;
    std::cout << "hasPSPMT " << hasPSPMT << std::endl;
    std::cout << "hasPSPMT " << hasPSPMT << std::endl;

    std::cout << "----- Event type flags -----" << std::endl;
    std::cout << "isImplant " << isImplant << std::endl;
    std::cout << "isDecay " << isDecay << std::endl; 
    std::cout << "isLightIon " << isLightIon << std::endl;
    std::cout << "isUnidentified " << isUnidentified << std::endl;

    getc(stdin);
  }

  // End correlation
  bdecay.corr.flag = condition; // Set the correlation flag
  
  return 0;
}
