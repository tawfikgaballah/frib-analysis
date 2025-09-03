#ifndef CONSTANTS_H
#define CONSTANTS_H

// daq
const int ncrates = 2;
const int nslots = 13;
const int nchannels = 16;
const int chanpercrate = nslots*nchannels; // channels per crate
const int totchan = ncrates*chanpercrate; // total channels in the system
const int nadcs = 24; // total number of adcs in the system

// implantation detectors
const int nanodes = 256;
const int npspmt = 16;
const int nanodes_utk = 4;
const int npspmt_utk = 48; 
const int range_pspmt = 3;  // in cm, pspmt positions range from -3 -> 3
const int ndssd = 40;
const int nsssd = 16;

// gamma detectors
const int nclovers = 13;
const int ncrystals = 4;
const int totcrystals = nclovers*ncrystals; // total single crystals
const int nlabr3 = 16;
const int nsega = 16;

// anode position fitting results
const int ERR_MINV = -100;   // Matrix for linear equation solver is not invertable
const int ERR_BADPOS = -99; // Position fit outside of anode pixel range [0,nanodes)
const int ERR_CONCDOWN = -98; // Quadratic fit is concave down (no minimum)
const int ERR_QDCMULT = -97; // Not all QDC sums present for the event
const bool displaylinfitinfo = false; // Set to true to display linear fit information

#endif
