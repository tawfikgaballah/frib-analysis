#include "TUnpacker.h"

#include <iostream>
#include <cmath>

using namespace ddastoys;

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
int TUnpacker::UnpackChannel(int id, TRandom3 &rng, DDASRootFitHit* ddashit, TBetaDecayParams &bdecay, int m)
{ 
  if(id < 0 || id >= totchan) {
    std::cout << "ERROR: Problems with id value " << id << " out of range." << std::endl;
    return 1;
  }
  
  bdecay.ddasdiagnostics.chanhit.push_back(id); // Increment channel hitpattern
  
  if(id == 0) {
    bdecay.NpspmtCeBr.UnpackDynode(ddashit, rng, bdecay.var.NpspmtCeBr);
    bdecay.NpspmtCeBr.UnpackDynodeFit(ddashit, bdecay.var.NpspmtCeBr, m);
  }
  
  if(id == 2 && !bdecay.xscintB.hit) {
    bdecay.xscintB.Unpack(ddashit, rng, bdecay.var.xscintB, 1);
  }
  
  if(id == 4 && !bdecay.xscintT.hit) {
    bdecay.xscintT.Unpack(ddashit, rng, bdecay.var.xscintT, 1);
  }
  
  if (id == 26) {
    bdecay.xpin1.Unpack(ddashit, rng, bdecay.var.xpin1, 0);
  }
  
  if (id == 27) {
    bdecay.xpin2.Unpack(ddashit, rng, bdecay.var.xpin2, 0);
  }
  
  /*if (id == 28) {
    bdecay.NDB4P0LT.Unpack(ddashit, rng, bdecay.var.NDB4P0LT, 0);
  }*/

/*   if (id == 29) {
    bdecay.NDB4P1L.Unpack(ddashit, rng, bdecay.var.NDB4P1L, 0);
  } */

 /*  if (id == 30) {
    bdecay.NDB3P1A.Unpack(ddashit, rng, bdecay.var.NDB3P1A, 0);
  } */
/* 
  if (id == 31) {
    bdecay.NDB3P0A.Unpack(ddashit, rng, bdecay.var.NDB3P0A, 0);
  }
 */
  /*if(id == 208) {
    bdecay.GpspmtCeBr.UnpackDynode(ddashit, rng, bdecay.var.GpspmtCeBr);
    bdecay.GpspmtCeBr.UnpackDynodeFit(ddashit, bdecay.var.GpspmtCeBr, m);
  }*/
  
  /*if(id == 221 && !bdecay.sipm.hit) {
    bdecay.sipm.Unpack(ddashit, rng, bdecay.var.sipm, 1);
  }*/
  
  if(id == 222 && !bdecay.SIPMT.hit) {
    bdecay.SIPMT.Unpack(ddashit, rng, bdecay.var.SIPMT, 1);
  }
  
  // if(id == 223 && !bdecay.SIPMB.hit) {
  //   bdecay.SIPMB.Unpack(ddashit, rng, bdecay.var.SIPMB, 1);
  // }

  if (id == 224) {
    bdecay.DB3SLT.Unpack(ddashit, rng, bdecay.var.DB3SLT, 0);
  }
  if (id == 225) {
    bdecay.DB3SRT.Unpack(ddashit, rng, bdecay.var.DB3SRT, 0);
  }
  if (id == 226) {
    bdecay.DB3P0AT.Unpack(ddashit, rng, bdecay.var.DB3P0AT, 0);
  }
  if (id == 227) {
    bdecay.DB3P1AT.Unpack(ddashit, rng, bdecay.var.DB3P1AT, 0);
  } 
  /*if (id == 236) {
    bdecay.DB4P0LT.Unpack(ddashit, rng, bdecay.var.DB4P0LT, 0);
  }
  if (id == 237) {
    bdecay.DB4P0RT.Unpack(ddashit, rng, bdecay.var.DB4P0RT, 0);
  }
  if (id == 238) {
    bdecay.DB4P0UT.Unpack(ddashit, rng, bdecay.var.DB4P0UT, 0);
  }
  if (id == 239) {
  bdecay.DB4P0DT.Unpack(ddashit, rng, bdecay.var.DB4P0DT, 0);
}*/
/*if (id == 240) {
  bdecay.DB3P0L.Unpack(ddashit, rng, bdecay.var.DB3P0L, 0);
}
if (id == 241) {
  bdecay.DB3P0R.Unpack(ddashit, rng, bdecay.var.DB3P0R, 0);
}
if (id == 242) {
  bdecay.DB3P0U.Unpack(ddashit, rng, bdecay.var.DB3P0U, 0);
}
if (id == 243) {
  bdecay.DB3P0D.Unpack(ddashit, rng, bdecay.var.DB3P0D, 0);
}
if (id == 244) {
  bdecay.DB3P1L.Unpack(ddashit, rng, bdecay.var.DB3P1L, 0);
}
if (id == 245) {
  bdecay.DB3P1R.Unpack(ddashit, rng, bdecay.var.DB3P1R, 0);
}
if (id == 246) {
  bdecay.DB3P1U.Unpack(ddashit, rng, bdecay.var.DB3P1U, 0);
}
if (id == 247) {
  bdecay.DB3P1D.Unpack(ddashit, rng, bdecay.var.DB3P1D, 0);
} */
/* if (id == 248) {
  bdecay.DB5P0L.Unpack(ddashit, rng, bdecay.var.DB5P0L, 0);
}
if (id == 249) {
  bdecay.DB5P0R.Unpack(ddashit, rng, bdecay.var.DB5P0R, 0);
}
if (id == 250) {
  bdecay.DB5P0U.Unpack(ddashit, rng, bdecay.var.DB5P0U, 0);
}
if (id == 251) {
  bdecay.DB5P0D.Unpack(ddashit, rng, bdecay.var.DB5P0D, 0);
}
if (id == 252) {
  bdecay.DB5P1L.Unpack(ddashit, rng, bdecay.var.DB5P1L, 0);
}
if (id == 253) {
  bdecay.DB5P1R.Unpack(ddashit, rng, bdecay.var.DB5P1R, 0);
}
if (id == 254) {
  bdecay.DB5P1U.Unpack(ddashit, rng, bdecay.var.DB5P1U, 0);
}
if (id == 255) {
  bdecay.DB5P1D.Unpack(ddashit, rng, bdecay.var.DB5P1D, 0);
} */
  

  
  if(id >= 416 && id < 672) {
    int pix = id - 416;
    bdecay.NpspmtCeBr.UnpackAnode(ddashit, rng, bdecay.var.NpspmtCeBr, pix);
  }

// clovers  
  if((id >= 256 && id < 319)){
    int empty = 0;

     int det =12; // detector number 0-15
      int idet = 0;// 
      int cry=0;
       //det 1
       if (id == 256) { idet = 0; cry = 0; det = 4*idet + cry; }
       if (id == 257) { idet = 0; cry = 1; det = 4*idet + cry; }
       if (id == 258) { idet = 0; cry = 2; det = 4*idet + cry; }
       if (id == 259) { idet = 0; cry = 3; det = 4*idet + cry; }
       // det 2
       if (id == 260) { idet = 1; cry = 0; det = 4*idet + cry; }
       if (id == 261) { idet = 1; cry = 1; det = 4*idet + cry; }
       if (id == 262) { idet = 1; cry = 2; det = 4*idet + cry; }
       if (id == 263) { idet = 1; cry = 3; det = 4*idet + cry; }

       //det 3
       if (id == 264) { idet = 2; cry = 0; det = 4*idet + cry; }
       if (id == 267) { idet = 2; cry = 1; det = 4*idet + cry; }
       if (id == 308) { idet = 2; cry = 2; det = 4*idet + cry; }
       if (id == 309) { idet = 2; cry = 3; det = 4*idet + cry; }
       
       //det 5
       if (id == 272) { idet = 4; cry = 0; det = 4*idet + cry; }
       if (id == 273) { idet = 4; cry = 1; det = 4*idet + cry; }
       if (id == 274) { idet = 4; cry = 2; det = 4*idet + cry; }
       if (id == 275) { idet = 4; cry = 3; det = 4*idet + cry; }

       //det 6
       if (id == 276) { idet = 5; cry = 0; det = 4*idet + cry; }
       if (id == 277) { idet = 5; cry = 1; det = 4*idet + cry; }
       if (id == 278) { idet = 5; cry = 2; det = 4*idet + cry; }
       if (id == 279) { idet = 5; cry = 3; det = 4*idet + cry; }

       //det 7
       if (id == 283) { idet = 6; cry = 0; det = 4*idet + cry; }
       if (id == 310) { idet = 6; cry = 1; det = 4*idet + cry; }
       if (id == 311) { idet = 6; cry = 2; det = 4*idet + cry; }
       if (id == 312) { idet = 6; cry = 3; det = 4*idet + cry; }

       //det 9
       if (id == 288) { idet = 8; cry = 0; det = 4*idet + cry; }
       if (id == 289) { idet = 8; cry = 1; det = 4*idet + cry; }
       if (id == 290) { idet = 8; cry = 2; det = 4*idet + cry; }
       if (id == 291) { idet = 8; cry = 3; det = 4*idet + cry; }

        //det 10
       if (id == 292) { idet = 9; cry = 0; det = 4*idet + cry; }
       if (id == 293) { idet = 9; cry = 1; det = 4*idet + cry; }
       if (id == 294) { idet = 9; cry = 2; det = 4*idet + cry; }
       if (id == 295) { idet = 9; cry = 3; det = 4*idet + cry; }

       //det 11
       if (id == 296) { idet = 10; cry = 0; det = 4*idet + cry; }
       if (id == 297) { idet = 10; cry = 1; det = 4*idet + cry; }
       if (id == 298) { idet = 10; cry = 2; det = 4*idet + cry; }
       if (id == 299) { idet = 10; cry = 3; det = 4*idet + cry; }

       //det 13
       if (id == 304) { idet = 12; cry = 0; det = 4*idet + cry; }
       if (id == 305) { idet = 12; cry = 1; det = 4*idet + cry; }
       if (id == 306) { idet = 12; cry = 2; det = 4*idet + cry; }
       if (id == 307) { idet = 12; cry = 3; det = 4*idet + cry; }
       
       
       bdecay.clover.Unpack(ddashit, rng, bdecay.var.clover, det);

  }

// labr
  if ((id>=320 && id < 336) || (id>=340 && id<342)){
    int det = id - 324;
    if(id>=340 && id<342){
        det=id-324;
      }
    bdecay.labr.Unpack(ddashit, rng, bdecay.var.labr, det);
  }
  
  if (id == 352) {
    bdecay.pin01.Unpack(ddashit, rng, bdecay.var.pin01, 0);
  }
  
  if (id == 353) {
    bdecay.pin02.Unpack(ddashit, rng, bdecay.var.pin02, 0);
  }
  
  return 0;
}
