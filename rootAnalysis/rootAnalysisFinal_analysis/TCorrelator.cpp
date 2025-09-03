/***************************************
// Comments by RSL
// For the e21062, the positions were determined by using qdc_sums
// qdc_sums were not enabled for the gamma crate (pspmthigh2/low2)
// therefore positions were determined by using the neutron crate
// which are pspmthigh1, pspmtlow1
// The rest of the analysis were done by using the gamma crate channels
// which are pspmthigh2, pspmtlow1
****************************************/

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
 * 96 - unknown event                   *
 * ==================================== *
 * 99 - Reset correlation aray          *
 ****************************************/

// Implant reset function
void TImplant::Reset()
{
  implanted = false;
  dyecal = 0;         // Dynode energy
  time = 0;           // Time of event
  de1 = 0;            // dE from Pin01
  de2 = 0;            // dE from Pin02
  tof = 0;            // TOF from some PIN/separator
  scintScintTOF = 0.; // TOF
  dtLastIon = 0;      // Time since last implant

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
  for (int i = 0; i < npspmt_utk; i++)
  {
    for (int j = 0; j < npspmt_utk; j++)
    {
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
int TCorrelator::Correlate(TBetaDecayParams &bdecay, std::string beta_gate, std::string tofv, std::string corrflow)
{

  // Reset correlator
  int condition = 96; // inital condition is unknown event
  if (bdecay.var.corr.reset == 1)
  {
    TCorrelator::Reset();
    bdecay.corr.flag = 99; // Set the reset flag
    bdecay.var.corr.reset = 0;
  }

  // Get time
  double current_time = 0;
  if (bdecay.clock.initial > 0)
  {
    current_time = bdecay.clock.initial / 1.e6; // Time in ms
  }
  else
  {
    //    std::cout << "Invalid time: " << bdecay.clock.initial << " something is very wrong!" << std::endl;;
    return 1; // bad
  }

  // signal flags
  bool hasPSPMTLow = false;  // PSPMT low gain (ions)
  bool hasPSPMTHigh = false; // PSPMT high gain (decays)
  bool hasPin = false;       // any PIN hit
  bool hasPin01 = false;
  bool hasPin02 = false;
  bool hasPinImplant = false; // implant-like events above implant threshold
  bool hasPin01Implant = false;
  bool hasPin02Implant = false;
  bool hasPinLightIon = false; // light ion events below implant threshold
  bool hasPin01LightIon = false;
  bool hasPin02LightIon = false;
  bool hasClover = false;
  bool hasxscintT = false;
  //... and others (clover, LaBr3, etc.)

  // event identification
  bool isImplant = false;
  bool isDecay = false;
  bool isLightIon = false;
  bool isUnidentified = false;
   bool isCloverOnly = false;
  //... and others (clover only, LaBr3 only etc.)

  // PSPMT positions
  int xPos = -1;
  int yPos = -1;

  /*********************************
   *** Event Type Identification ***
   *********************************/

  // Hit flags are set in TUnpacker.cpp
  //
  // PSPMT low gain for ions
  if (corrflow == "reverse")
  {
    bdecay.corr.isreverse = 1;
  }
  else if (corrflow == "forward")
  {

    bdecay.corr.isforward = 1;
  }
  if (bdecay.pspmtlow1.hit == 1)
  {
    hasPSPMTLow = true;

    //	std::cout<< "hasPSPMTLow = true" <<std::endl;
  }

  // PSPMT high gain for decays
  if (bdecay.pspmthigh1.hit == 1)
  {
    hasPSPMTHigh = true;

    //	std::cout<< "hasPSPMThigh = true" <<std::endl;
  }

  //  if(hasPSPMTHigh){  // test by RSL
  //	std::cout << bdecay.pspmthigh1.dyenergy.at(0) << std::endl; } // all pspnthigh2.at(0) with no conditions

  // Pin01 implant vs light ions
  if (bdecay.pin01.hit == 1)
  {
    hasPin01 = true;
    if (bdecay.pin01.ecal > 240)
    {
      hasPin01Implant = true;

      //	std::cout<< "hasPin01Implant = true;" <<std::endl;
    }
    else
    {
      hasPin01LightIon = true;

      //	std::cout<< "hasPin01LightIon = true;" <<std::endl;
    }
  }

  // Pin02 implant vs light ions
  if (bdecay.pin02.hit == 1)
  {
    hasPin02 = true;
    if (bdecay.pin02.ecal > 240)
    {
      hasPin02Implant = true;

      //	std::cout<< "hasPin02Implant = true;" <<std::endl;     // This condition does not satisfy
    }
    else
    {
      hasPin02LightIon = true;

      //	std::cout<< "hasPin02LightIon = true;" <<std::endl;     // This condition does not satisfy
    }
  }

  if (hasPin01 || hasPin02)
  {
    hasPin = true;
  } // any PIN is hit
  if (hasPin01Implant && hasPin02Implant)
  {
    hasPinImplant = true;
  } // implants only
  if (hasPin01LightIon && hasPin02LightIon)
  {
    hasPinLightIon = true;
  } // light ions only

  // advanced event type identificaton
  // implant event identification


  if (bdecay.xscintT.hit==1)
    {
      hasxscintT = true;

      //	std::cout<< "hasPin01Implant = true;" <<std::endl;
    }
  if (hasPSPMTLow && hasPinImplant &&  !bdecay.vetoR.hit )
  { // PSPMT low gain AND PIN AND NOT rear veto plastic implant
    isImplant = true;
    bdecay.corr.isimplant = 1;
  }

  // light ion event identification
  if ((hasPSPMTLow || hasPSPMTHigh) && (hasPinLightIon || bdecay.vetoF.hit == 1 || bdecay.vetoR.hit == 1 || bdecay.sipm.hit == 1))
  { // any PSPMT AND PIN light ion? --ASC 3/7/22
    isLightIon = true;
    bdecay.corr.islightion = 1;
  }

  if (beta_gate == "PIN")
  {
    // Original condition but now using dynamic attributes from cond2
    if ((hasPSPMTHigh || hasPSPMTLow) && !hasPin && !isLightIon)
    { // Assuming li.detected checks for light ions
      bdecay.corr.isdecay = 1;
      isDecay = true;
    }
  }
  else if (beta_gate == "SIPMT")
  {
    if ((hasPSPMTHigh || hasPSPMTLow) && !bdecay.SIPMT.hit)
    { // new condinition for beta decay
      isDecay = true;
      bdecay.corr.isdecay = 1;
    }
  }

  else if (beta_gate == "xscintT")
  {
    if ((hasPSPMTHigh || hasPSPMTLow) && !hasxscintT)
    { // new condinition for beta decay
      isDecay = true;
      bdecay.corr.isdecay = 1;
    }
  }

  else if (beta_gate == "xscintB")
  {
    if ((hasPSPMTHigh || hasPSPMTLow)&& !bdecay.xscintB.hit)
    { // new condinition for beta decay
      isDecay = true;
      bdecay.corr.isdecay = 1;
    }
  }
  else if (beta_gate == "sipm")
  {
    if ((hasPSPMTHigh || hasPSPMTLow) && !bdecay.sipm.hit)
    { // new condinition for beta decay
      isDecay = true;
      bdecay.corr.isdecay = 1;
    }
  }

  // clover only event
  if(bdecay.clover.hit == 1){
    hasClover = true;
    bdecay.corr.hasclover = true;
    
  }
  if(!hasPin && !hasPSPMTHigh && !hasPSPMTLow && hasClover){
    isCloverOnly = true;
    bdecay.corr.iscloveronly = 1;
  }
  // everything else
  if (!isImplant && !isDecay && !isLightIon)
  { // something besides stuff in the PSPMT (for now)
    isUnidentified = true;
    //	std::cout<< "Unidentified pspmthigh1 energy: " << bdecay.pspmthigh1.dyenergy.at(0) << std::endl;
  }

  // if there is a saturated HG hit and there is a good LG signal, use the low energy w/ conversion factor.
    if(bdecay.pspmthigh1.hit==true && bdecay.pspmthigh1.dyoverflow==true && bdecay.pspmtlow1.hit==true && bdecay.pspmtlow1.dyoverflow==false)
    {
      double m = 44.0625;
      double b = 942.184;

      bdecay.pspmthigh1.dyecal.at(0) = m*bdecay.pspmtlow1.dyecal.at(0)+b;
      bdecay.pspmthigh1.dyenergy.at(0) = m*bdecay.pspmtlow1.dyenergy.at(0)+b;
      bdecay.pspmthigh1.dytime.at(0) = bdecay.pspmtlow1.dytime.at(0);
    }
  /*********************************
   ***    Build correlations     ***
   *********************************/
  bool hasGoodPosition_implant = false;

  bool hasGoodPosition_decay = false;
  //____________________________________________________________
  // Implant
  if (isImplant)
  {

    // Get position info from the anode energy distribution fit
    xPos = int(bdecay.pspmtlow1.xpos);
    yPos = int(bdecay.pspmtlow1.ypos);

    //   std::cout << "Implant xpos: " << xPos << " Implant yPos: " << yPos << std::endl;

    //	std::cout<< " bdecay.pspmtlow1.xpos " << bdecay.pspmtlow1.xpos << std::endl;

    // check if the position is good
    if ((xPos >= 0 && xPos < npspmt_utk) && (yPos >= 0 && yPos < npspmt_utk))
    {
      condition = 4; // implant flag
      hasGoodPosition_implant = true;

      //	std::cout<< "has good implant position conditions"  << std::endl; //fails
    }
    else
    {
      condition = 8; // bad implant position
    }

    // If there is a good implant position, continue processing the event
    if (hasGoodPosition_implant)
    {

      //	std::cout<< "has good implant position checks"  << std::endl; 	// fails

      double timeDiffIon = -1.;
      if (fImplant[xPos][yPos].time >= 0)
      {
        // Note: need abs(timeDiffIon) for reverse correlation!
        if (corrflow == "forward")
          timeDiffIon = current_time - fImplant[xPos][yPos].time;
        if (corrflow == "reverse")
          timeDiffIon = abs(current_time - fImplant[xPos][yPos].time);
        if (timeDiffIon > 0)
        {
          // Check for existing implant in this pixel
          if (fImplant[xPos][yPos].implanted)
          {
            fImplant[xPos][yPos].dtLastIon = timeDiffIon;
          }
          else
          {
            // If the time and position are good, count this spot as implanted
            // if it hasn't already been
            fImplant[xPos][yPos].implanted = true;
          }

          // Assign values -- this overwrites the previous implant in this position
          fImplant[xPos][yPos].dyecal = bdecay.pspmtlow1.dyecal.at(0);
          fImplant[xPos][yPos].time = current_time;
          fImplant[xPos][yPos].de1 = bdecay.pid.de1;
          fImplant[xPos][yPos].de2 = bdecay.pid.de2;
          fImplant[xPos][yPos].tof = bdecay.pid.tof;
          // Store the fit information
          fImplant[xPos][yPos].dychisq_single = bdecay.pspmtlow1.dychisq_single.at(0);
          fImplant[xPos][yPos].dyE1real_single = bdecay.pspmtlow1.dyE1_single.at(0);

          fImplant[xPos][yPos].dyT1_single = bdecay.pspmtlow1.dyT1_single.at(0);
          fImplant[xPos][yPos].dychisq_double = bdecay.pspmtlow1.dychisq_double.at(0);
          fImplant[xPos][yPos].dyE1real_double = bdecay.pspmtlow1.dyE1_double.at(0);

          fImplant[xPos][yPos].dyT1_double = bdecay.pspmtlow1.dyT1_double.at(0);
          fImplant[xPos][yPos].dyE2real_double = bdecay.pspmtlow1.dyE2_double.at(0);

          fImplant[xPos][yPos].dyT2_double = bdecay.pspmtlow1.dyT2_double.at(0);
          fImplant[xPos][yPos].dytdiffE1E2cal = bdecay.pspmtlow1.dytdiffE1E2cal;
          fImplant[xPos][yPos].xpos = bdecay.pspmtlow1.xpos;
          fImplant[xPos][yPos].ypos = bdecay.pspmtlow1.ypos;

          // Add implant to list of implants in that pixel
          fImplantVector[xPos][yPos].push_back(fImplant[xPos][yPos]);

          // Set the implant output
          bdecay.corr.idyecal = fImplant[xPos][yPos].dyecal;
          bdecay.corr.itime = fImplant[xPos][yPos].time;
          bdecay.corr.ide1 = fImplant[xPos][yPos].de1;
          bdecay.corr.ide2 = fImplant[xPos][yPos].de2;
          bdecay.corr.itof = fImplant[xPos][yPos].tof;
          /* if ((fImplant[xPos][yPos].de2<=fImplant[xPos][yPos-1].de2+.1||fImplant[xPos][yPos].de2>=fImplant[xPos][yPos-1].de2+.1)&&xPos==20){
          std::cout<<" de2: "<<fImplant[xPos][yPos-1].de2<<" tof: "<<fImplant[xPos][yPos-1].tof<<" xpos: "<<xPos<<" ypos: "<<yPos-1<<'\n';
          std::cout<<" de2: "<<fImplant[xPos][yPos].de2<<" tof: "<<fImplant[xPos][yPos].tof<<" xpos: "<<xPos<<" ypos: "<<yPos<<'\n';
        } */
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
  else if (isDecay)
  {

    //	std::cout<< "THIS IS WHERE WE FILL IMPLANTLIST FOR THE DECAYS" << std::endl;
    double x, y;  
    // Get position info from the anode energy distribution fit
    if(bdecay.pspmthigh1.hit==true && bdecay.pspmthigh1.dyoverflow==false)
    // if there is a high gain hit and it's NOT saturated, use the high gain x,y
    {
      xPos = int(bdecay.pspmthigh1.xpos_highgain);
      yPos = int(bdecay.pspmthigh1.ypos_highgain);

      x = bdecay.pspmthigh1.xpos_highgain;
      y = bdecay.pspmthigh1.ypos_highgain;
      
    }

    // if there is a saturated HG hit, use the low gain position as long as LG is present and not saturated too
    else if(bdecay.pspmthigh1.hit==true && bdecay.pspmthigh1.dyoverflow==true && bdecay.pspmtlow1.hit==true && bdecay.pspmtlow1.dyoverflow==false)
    {
      xPos = int(bdecay.pspmtlow1.xpos);
      yPos = int(bdecay.pspmtlow1.ypos);

      x = bdecay.pspmtlow1.xpos;
      y = bdecay.pspmtlow1.ypos;
    }

    else{

      xPos=-9999;
      yPos=-9999;

    }
    // Get position info from the anode energy distribution fit
    // xPos = int(bdecay.pspmthigh1.xpos_highgain);
    // yPos = int(bdecay.pspmthigh1.ypos_highgain);

    //   std::cout << "Decay xpos: " << xPos << " Decay yPos: " << yPos << std::endl;

    //	std::cout<< " bdecay.pspmthigh1.xpos " << bdecay.pspmthigh1.xpos << std::endl;

    // Decay position check
    // Note that the 16x16 anode is 0 indexed on both axes!
    if ((xPos >= 0 && xPos < npspmt_utk) && (yPos >= 0 && yPos < npspmt_utk))
    {
      condition = 12;
      hasGoodPosition_decay = true;

      //	std::cout<< "has good implant position conditions"  << std::endl; //fails
    }
    else
    {
      condition = 16;
    }

    if (hasGoodPosition_decay)
    {

      //	std::cout<< "has good decay position checks"  << std::endl;

      // Perform the correlation. Search the correlation grid for implants
      // which satisfy the time difference requirement. Note: time differences
      // must be abs(tdiff) for reverse correlation!
      int corrGridLimit = ((fCorrWin - 1) / 2) * (npspmt_utk / 24); // for fCorrWin = 3, corrGridLimit = 1

      for (int i = (-corrGridLimit); i < (corrGridLimit + 1); i++)
      {
        for (int j = (-corrGridLimit); j < (corrGridLimit + 1); j++)
        {
          if ((xPos + i) >= 0 && (xPos + i) < npspmt_utk &&
              (yPos + j) >= 0 && (yPos + j) < npspmt_utk)
          { // Good correlation grid position
            // Loop over implanted ion vector for position checking. Also need a
            // software limit correlation window so that our lists dont get too big.
            // Use correlation window defined in the variables. All time limits for
            // e.g. implant half-lives are done at histogramming step.
            double it = 0;
            int counter = 0;
            for (auto &ion : fImplantVector[xPos + i][yPos + j])
            {
              if (std::abs(current_time - ion.time) > bdecay.var.corr.corrwindow)
              {
                fImplantVector[xPos + i][yPos + j].erase(fImplantVector[xPos + i][yPos + j].begin() + it);
              }
              else
              {
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
                double x1 = x;
                double x2 = ion.xpos;
                double y1 = y;
                double y2 = ion.ypos;

                double distance = std::sqrt(std::pow((x2 - x1), 2.0) + std::pow((y2 - y1), 2.0));

                //	std::cout << "x1: " << x1 << " x2: " << x2 << " y1: " << y1 << " y2: " << y2 << " distance: " << distance << std::endl;

                if (distance <= corrGridLimit)
                {
                  // if(distance>1)
                  //                 std::cout << "x1: " << x1 << " x2: " << x2 << " y1: " << y1 << " y2: " << y2 << " distance: " << distance << std::endl;

                  fCorrelatedImplants.push_back(implantStore);

                  bdecay.corr.dde1 = ion.de1;
                  bdecay.corr.dde2 = ion.de2;
                  bdecay.corr.dtof = ion.tof;
                  bdecay.corr.radius.push_back(distance);

                  bdecay.corr.ddyecal = bdecay.pspmthigh1.dyecal.at(0);
                  bdecay.corr.dtime = current_time;
                  double decaytime = current_time - ion.time;
                  bdecay.corr.decaytime.push_back(decaytime);
                  bdecay.corr.dxpos = x;
                  bdecay.corr.dypos = y;
                  // Store the fit information
                  bdecay.corr.ddychisq_single = bdecay.pspmthigh1.dychisq_single.at(0);
                  bdecay.corr.ddyE1real_single = bdecay.pspmthigh1.dyE1_single.at(0);

                  bdecay.corr.ddyT1_single = bdecay.pspmthigh1.dyT1_single.at(0);
                  bdecay.corr.ddychisq_double = bdecay.pspmthigh1.dychisq_double.at(0);
                  bdecay.corr.ddyE1real_double = bdecay.pspmthigh1.dyE1_double.at(0);

                  bdecay.corr.ddyT1_double = bdecay.pspmthigh1.dyT1_double.at(0);
                  bdecay.corr.ddyE2real_double = bdecay.pspmthigh1.dyE2_double.at(0);

                  bdecay.corr.ddyT2_double = bdecay.pspmthigh1.dyT2_double.at(0);
                  bdecay.corr.ddytdiffE1E2cal = bdecay.pspmthigh1.dytdiffE1E2;
                  /*  if(counter==0 &&bdecay.corr.decaytime.at(counter)!=bdecay.corr.dtime-ion.time&&bdecay.corr.decaytime.size()>0&&sizeof(ion)>0){

                   std::cout<<"decaytime[0]= "<<bdecay.corr.decaytime.at(counter)<<" corr_dtime-implantlist[0]="<< bdecay.corr.dtime-ion.time<<'\n';
                   counter++;
                 } */
                }

              } // End store of correlated ions

            } // End loop over ion list
          } // End good position check
        }
      } // End correlation grid search

      if (fCorrelatedImplants.size() > 0)
      {
        condition = 32; // at least one ion correlated to this decay
      }
      else
      {
        condition = 44; // no implant in correlation field
      }

      // Set decay output

    } // End good decay position check
  } // End decay analysis
  //____________________________________________________________
  // Light ion
  else if (isLightIon)
  {
    condition = 20;
  }
  //____________________________________________________________
  // Everything else
  else
  {
    condition = 96; // Unknown event type, probably redundant
  }
//   if(bdecay.corr.iscloveronly!=1)
//  std::cout<<" cond: "<<bdecay.corr.iscloveronly<<'\n';

  bool printevent = false;
  if (condition == 96 && printevent)
  {
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "condition  " << condition << std::endl;

    std::cout << "----- PIN detectors -----" << std::endl;
    std::cout << "hit.pin01  " << bdecay.pin01.hit << " energy " << bdecay.pin01.energy << " ecal " << bdecay.pin01.ecal << " time " << bdecay.pin01.time << std::endl;
    std::cout << "hit.pin02  " << bdecay.pin02.hit << " energy " << bdecay.pin02.energy << " ecal " << bdecay.pin02.ecal << " time " << bdecay.pin02.time << std::endl;

    std::cout << "----- PSPMT dynode high gain -----" << std::endl;
    //    std::cout << "hit.dynode " << bdecay.pspmthigh1.dyhit << " energy " << bdecay.pspmthigh1.dyenergy << " ecal " << bdecay.pspmthigh1.dyecal << " time " << std::setprecision(12) << bdecay.pspmthigh1.dytime << std::endl;
    std::cout << "xpos " << std::setprecision(5) << bdecay.pspmthigh1.xpos_highgain << " ypos " << bdecay.pspmthigh1.ypos_highgain << std::endl;
    //    std::cout << "dynode fit: E1single " << bdecay.pspmthigh1.dyE1real_single << " E1dobule " << bdecay.pspmthigh1.dyE1real_double << " E2double " << bdecay.pspmthigh1.dyE2real_double << std::endl;
    std::cout << "dynode mult " << bdecay.pspmthigh1.dymult << std::endl;
    for (int i = 0; i < bdecay.pspmthigh1.dymult; i++)
    {
      std::cout << "dynode[" << i << "] " << std::setprecision(12) << bdecay.pspmthigh1.dytimes[i] << std::endl;
    }
    std::cout << "hit.pspmthigh1 " << bdecay.pspmthigh1.hit << std::endl;
    std::cout << "anode mult high " << bdecay.pspmthigh1.amult << std::endl;

    std::cout << "----- PSPMT dynode low gain -----" << std::endl;
    //    std::cout << "hit.dynode " << bdecay.pspmtlow1.dyhit << " energy " << bdecay.pspmtlow1.dyenergy << " ecal " << bdecay.pspmtlow1.dyecal << " time " << std::setprecision(12) << bdecay.pspmtlow1.dytime << std::endl;
    std::cout << "xpos " << std::setprecision(5) << bdecay.pspmtlow1.xpos << " ypos " << bdecay.pspmtlow1.ypos << std::endl;
    //    std::cout << "dynode fit: E1single " << bdecay.pspmtlow1.dyE1real_single << " E1dobule " << bdecay.pspmtlow1.dyE1real_double << " E2double " << bdecay.pspmtlow1.dyE2real_double << std::endl;
    std::cout << "dynode mult " << bdecay.pspmtlow1.dymult << std::endl;
    for (int i = 0; i < bdecay.pspmtlow1.dymult; i++)
    {
      std::cout << "dynode[" << i << "] " << std::setprecision(12) << bdecay.pspmtlow1.dytimes[i] << std::endl;
    }
    std::cout << "hit.pspmtlow " << bdecay.pspmtlow1.hit << std::endl;
    std::cout << "anode mult low " << bdecay.pspmtlow1.amult << std::endl;

    std::cout << "----- Detector hit flags -----" << std::endl;
    std::cout << "hasPin " << hasPin << std::endl;
    std::cout << "hasPin01Implant " << hasPin01Implant << std::endl;
    std::cout << "hasPin02Implant " << hasPin02Implant << std::endl;
    std::cout << "hasPin01LightIon " << hasPin01LightIon << std::endl;
    std::cout << "hasPin02LightIon " << hasPin02LightIon << std::endl;
    std::cout << "hasPinLightIon " << hasPinLightIon << std::endl;
    std::cout << "hasPSPMTLow " << hasPSPMTLow << std::endl;
    std::cout << "hasPSPMTHigh " << hasPSPMTHigh << std::endl;

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
