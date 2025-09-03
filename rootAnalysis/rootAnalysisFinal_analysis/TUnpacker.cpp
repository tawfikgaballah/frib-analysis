#include "TUnpacker.h"

#include <iostream>
#include <cmath>

// Channel map
// ID      -- Detector type
// ----- Crate 1 -----


// Lets make sure we make the unpacker
TUnpacker::TUnpacker()
{
  std::cout << "Creating channel mapper..." << std::endl;
}

// UnpackChannel
//
// Function:
//   - pass DDAS information to detector class unpackers
//   - handle fit information if necessary
//
// Params:
//   - global channel ID
//   - pointer to a DDAS hit
//   - trace fit information from RootHitExtension
//   - beta decay parameters (i.e. detector classes)
//   - beta decay variables (i.e. calibration parameters, thresholds, etc.)
//
// Return:
//   - 0 on success
//   - 1 on fail
//
int TUnpacker::UnpackChannel(int id, TRandom3 &rng, DDASRootFitHit* ddashit, std::vector<RootHitExtension> &fits, TBetaDecayParams &bdecay, int m)
{ 
  if(id < 0 || id >= totchan) {
    std::cout << "ERROR: Problems with id value " << id << " out of range." << std::endl;
    return 1;
  }
  
  bdecay.ddasdiagnostics.chanhit.push_back(id); // Increment channel hitpattern
  
  if(id == 0) {
    bdecay.pspmthigh1.UnpackDynode(ddashit, rng, bdecay.var.pspmthigh1);
    bdecay.pspmthigh1.UnpackDynodeFit(bdecay.var.pspmthigh1, fits, m);
  }
  
  if(id == 1) {
    bdecay.pspmtlow1.UnpackDynode(ddashit, rng, bdecay.var.pspmtlow1);
    bdecay.pspmtlow1.UnpackDynodeFit(bdecay.var.pspmtlow1, fits, m);
  }
  
  if(id == 2 && !bdecay.xscintB.hit) {
    bdecay.xscintB.Unpack(ddashit, rng, bdecay.var.xscintB, 1);
  }
  
  if(id == 4 && !bdecay.xscintT.hit) {
    bdecay.xscintT.Unpack(ddashit, rng, bdecay.var.xscintT, 1);
  }
  
  if (id == 6) {
    bdecay.xpin1.Unpack(ddashit, rng, bdecay.var.xpin1, 0);
  }
  
  if (id == 7) {
    bdecay.vetoF.Unpack(ddashit, rng, bdecay.var.vetoF, 0);
  }
  
  if (id == 8) {
    bdecay.vetoR.Unpack(ddashit, rng, bdecay.var.vetoR, 0);
  }
  
  if(id >= 16 && id < 20) {
    int pix = id - 16;
    bdecay.pspmthigh1.UnpackAnode(ddashit, rng, bdecay.var.pspmthigh1, pix);
  }
  
  if(id >= 20 && id < 24) {
    int pix = id - 20;
    bdecay.pspmtlow1.UnpackAnode(ddashit, rng, bdecay.var.pspmtlow1, pix);
  }
  

  if (id == 27) {
    bdecay.xpin2.Unpack(ddashit, rng, bdecay.var.xpin2, 0);
  }
  
  if (id == 28) {
    bdecay.NDB4PPACLT.Unpack(ddashit, rng, bdecay.var.NDB4PPACLT, 0);
  }

  if (id == 29) {
    bdecay.NDB4PPACRT.Unpack(ddashit, rng, bdecay.var.NDB4PPACRT, 0);
  }
    
  if(id == 208) {
    bdecay.pspmthigh2.UnpackDynode(ddashit, rng, bdecay.var.pspmthigh2);
    bdecay.pspmthigh2.UnpackDynodeFit(bdecay.var.pspmthigh2, fits, m);
  }
  
  if(id == 209) {
    bdecay.pspmtlow2.UnpackDynode(ddashit, rng, bdecay.var.pspmtlow2);
    bdecay.pspmtlow2.UnpackDynodeFit(bdecay.var.pspmtlow2, fits, m);
  }  

  if(id >= 212 && id < 216) {
    int pix = id - 212;
    bdecay.pspmthigh2.UnpackAnode(ddashit, rng, bdecay.var.pspmthigh2, pix);
  }

  if(id >= 216 && id < 220) {
    int pix = id - 216;
    bdecay.pspmtlow2.UnpackAnode(ddashit, rng, bdecay.var.pspmtlow2, pix);
  }  

  if (id == 231 && !bdecay.SIPMT.hit) {
    bdecay.SIPMT.Unpack(ddashit, rng, bdecay.var.SIPMT, 0);
  }

  if(id == 232) {
    bdecay.sipm.Unpack(ddashit, rng, bdecay.var.sipm, 0);
  }

  if(id == 233) {
    bdecay.PIN01T.Unpack(ddashit, rng, bdecay.var.PIN01T, 0);
  }
  
  if(id == 240 && !bdecay.SCLT.hit) {
    bdecay.SCLT.Unpack(ddashit, rng, bdecay.var.SCLT, 0);
  }
  
  if(id == 241) {
    bdecay.SCRT.Unpack(ddashit, rng, bdecay.var.SCRT, 0);
  }

// db3 PPAC Anode  
  if(id == 242) {
    bdecay.DB3PPACUAnT.Unpack(ddashit, rng, bdecay.var.DB3PPACUAnT, 0);
  }
  
  if(id == 245) {
    bdecay.DB3PPACDAnT.Unpack(ddashit, rng, bdecay.var.DB3PPACDAnT, 0);
  }

// db3 PPAC
  if(id == 31) {
    bdecay.DB3PPACULT.Unpack(ddashit, rng, bdecay.var.DB3PPACULT, 0); //using this for db3ppacUAnT neutron crate
  }
  
  if(id == 244) {
    bdecay.DB3PPACURT.Unpack(ddashit, rng, bdecay.var.DB3PPACURT, 0);
  }
  
  if(id == 246) {
    bdecay.DB3PPACDLT.Unpack(ddashit, rng, bdecay.var.DB3PPACDLT, 0);
  }
  
  if(id == 247) {
    bdecay.DB3PPACDRT.Unpack(ddashit, rng, bdecay.var.DB3PPACDRT, 0);
  }
  
// db4 PPAC
  if(id == 248) {
    bdecay.DB4PPACUT.Unpack(ddashit, rng, bdecay.var.DB4PPACUT, 0);
  }
  
  if(id == 249) {
    bdecay.DB4PPACDT.Unpack(ddashit, rng, bdecay.var.DB4PPACDT, 0);
  }
  
  if(id == 250) {
    bdecay.DB4PPACLT.Unpack(ddashit, rng, bdecay.var.DB4PPACLT, 0);
  }
  
  if(id == 251) {
    bdecay.DB4PPACRT.Unpack(ddashit, rng, bdecay.var.DB4PPACRT, 0);
  }

// db5 PPAC
  if(id == 252) {
    bdecay.DB5PPACULT.Unpack(ddashit, rng, bdecay.var.DB5PPACULT, 0);
  }
  
  if(id == 253) {
    bdecay.DB5PPACURT.Unpack(ddashit, rng, bdecay.var.DB5PPACURT, 0);
  }
  
  if(id == 255) {
    bdecay.DB5PPACDLT.Unpack(ddashit, rng, bdecay.var.DB5PPACDLT, 0);
  }
  
  if(id == 255) {
    bdecay.DB5PPACDRT.Unpack(ddashit, rng, bdecay.var.DB5PPACDRT, 0);
  }

// PINs  
  if(id == 352) {
    bdecay.pin01.Unpack(ddashit, rng, bdecay.var.pin01, 0);
  }

  if (id == 353) {
    bdecay.pin02.Unpack(ddashit, rng, bdecay.var.pin02, 0);
    //   printf("PIN02 %f\n", bdecay.pin02.ecal);
  }

// clovers  
  if((id >= 256 && id < 268) ||
     (id >= 272 && id < 284) ||
     (id >= 288 && id < 304) ||
     (id >= 304 && id < 315) ||
     (id >= 340 && id < 342)) {
    if (id==265 || id==266 || id==280 || id==281 || id==282 || id==300 || id==301) { 
    } else {
      int det = id-256;
      int idet = 0;
      int cry = 0;
      if (id == 308) { idet = 2; cry = 1; det = 4*idet + cry; }
      if (id == 309) { idet = 2; cry = 2; det = 4*idet + cry; }
      if (id == 310) { idet = 6; cry = 0; det= 4*idet + cry; }
      if (id == 311) { idet = 6; cry = 1; det = 4*idet + cry; }
      if (id == 312) { idet = 6; cry = 2; det = 4*idet + cry; }
      if (id == 340) { idet = 11; cry = 0; det = 4*idet + cry; }
      if (id == 341) { idet = 11; cry = 1; det= 4*idet + cry; }
      bdecay.clover.Unpack(ddashit, rng, bdecay.var.clover, det);
    }
  }

// labr
  if (id>=320 && id < 336){
    int det = id - 320;
    bdecay.labr.Unpack(ddashit, rng, bdecay.var.labr, det);
  }
  

  
  return 0;
}
