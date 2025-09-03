#ifndef TPARAMETERS_H
#define TPARAMETERS_H

#include "TObject.h"

/*
 * A (hopefully temporary) workaround for running PROOF analysis.
 * This file gets included somehow and the paths to the detector files
 * need to be given despite PROOF in principle compiling the script
 * with the right include paths. As of now this is a workaround but 
 * certainly not intended to be a long-term solution.
 * --ASC 2/25/22
 *
 */
#include "TDDASDiagnostics.h"
#include "TClock.h"
#include "TTrace.h"
#include "TADC.h"
#include "TTAC.h"
#include "TPIN.h"
#include "TDSSD.h"
#include "TSSSD.h"
#include "TLaBr3.h"
#include "TPID.h"
#include "TSeGA.h"
#include "TClover.h"
#include "TCorrelation.h"
#include "TPSPMTCeBr.h"
#include "TPSPMTUTK.h"
#include "TPulser.h"
#include "Constants.h"

// variables definitions
class TBetaDecayVariables
{
 public:
  TClockCalibrator clock;
  TPSPMTUTKCalibrator pspmthigh1;
  TPSPMTUTKCalibrator pspmthigh2;
  TPSPMTUTKCalibrator pspmtlow1;
  TPSPMTUTKCalibrator pspmtlow2;

  TPSPMTCeBrCalibrator NpspmtCeBr;
  TPSPMTCeBrCalibrator GpspmtCeBr;

  TPINCalibrator SIPMT; // SIPM T2 
  TPINCalibrator PIN01T; // PIN01 time from FIFO
  TPINCalibrator DB3SLT; // Scintillator left time from FIFO
  TPINCalibrator DB3SRT; // Scintillator right time from FIFO

// db3 PPAC Anode
  TPINCalibrator DB3P0AT; // DB3PPAC 0 (upstream) Anode time from FIFO
  TPINCalibrator DB3P1AT; // DB3PPAC 1 (downstream) Anode time from FIFO

// db3 PPAC
  TPINCalibrator DB3PPACULT; // DB3PPAC Up-left time from FIFO
  TPINCalibrator DB3PPACURT; // DB3PPAC up-right time from FIFO
  TPINCalibrator DB3PPACDLT; // DB3PPAC down-Left time from FIFO
  TPINCalibrator DB3PPACDRT; // DB3PPAC down-Right time from FIFO

// db4 PPAC
  TPINCalibrator DB4P0UT; // DB4PPAC Up time from FIFO
  TPINCalibrator DB4P0DT; // DB4PPAC Down time from FIFO
  TPINCalibrator DB4P0LT; // DB4PPAC Left time from FIFO
  TPINCalibrator DB4P0RT; // DB4PPAC Right time from FIFO

// db5 PPAC
  TPINCalibrator DB5PPACULT; // DB5PPAC Up-left time from FIFO
  TPINCalibrator DB5PPACURT; // DB5PPAC Up-right time from FIFO
  TPINCalibrator DB5PPACDLT; // DB5PPAC Down-Left time from FIFO
  TPINCalibrator DB5PPACDRT; // DB5PPAC Down-Right time from FIFO

  TPINCalibrator NDB4P0LT; // DB4PPAC Left time from FIFO
  TPINCalibrator NDB4PPACRT; // DB4PPAC Right time from FIFO

  TPINCalibrator pin01;
  TPINCalibrator pin02;
  TPINCalibrator sipm;
  TPINCalibrator xscintB;
  TPINCalibrator xscintT;
  TPINCalibrator xpin1;
  TPINCalibrator xpin2;
  TCorrelationCalibrator corr;
  TCloverCalibrator clover;
  TLaBr3Calibrator labr;
  
 public:
  void Initialize();
};

// The entire beta-decay set-up 
class TBetaDecayParams: public TObject
{
 public:
  TDDASDiagnostics ddasdiagnostics;
  TClock clock;
  //TPSPMTUTK pspmthigh1;
  //TPSPMTUTK pspmthigh2;
  //TPSPMTUTK pspmtlow1;
  //TPSPMTUTK pspmtlow2;

  //TPSPMTCeBr GpspmtCeBr;
  TPSPMTCeBr NpspmtCeBr;

  TPIN SIPMT; // SIPM T2 
  //TPIN PIN01T; // PIN01 time from FIFO
  TPIN DB3SLT; // Scintillator left time from FIFO
  TPIN DB3SRT; // Scintillator right time from FIFO

// db3 PPAC Anode
  TPIN DB3P0AT; // DB3PPAC 0 (Upstream) Anode time from FIFO
  TPIN DB3P1AT; // DB3PPAC 1 (Downstream) Anode time from FIFO

// db3 PPAC
  //TPIN DB3PPACULT; // DB3PPAC Up-left time from FIFO
  //TPIN DB3PPACURT; // DB3PPAC up-right time from FIFO
  //TPIN DB3PPACDLT; // DB3PPAC down-Left time from FIFO
  //TPIN DB3PPACDRT; // DB3PPAC down-Right time from FIFO

// db4 PPAC
  //TPIN DB4P0UT; // DB4PPAC Up time from FIFO
  //TPIN DB4P0DT; // DB4PPAC Down time from FIFO
  //TPIN DB4P0LT; // DB4PPAC Left time from FIFO
  //TPIN DB4P0RT; // DB4PPAC Right time from FIFO

// db5 PPAC
  //TPIN DB5PPACULT; // DB5PPAC Up-left time from FIFO
  //TPIN DB5PPACURT; // DB5PPAC up-right time from FIFO
  //TPIN DB5PPACDLT; // DB5PPAC down-Left time from FIFO
  //TPIN DB5PPACDRT; // DB5PPAC down-Right time from FIFO

  //TPIN NDB4P0LT; // DB4PPAC Left time from FIFO
  //TPIN NDB4PPACRT; // DB4PPAC Right time from FIFO

  TPIN pin01;
  TPIN pin02;
  //TPIN sipm;
  TPIN xscintB;
  TPIN xscintT;
  TPIN xpin1;
  TPIN xpin2;
  TPID pid;
  TCorrelation corr;
  TClover clover;
  TLaBr3 labr;
  
  TBetaDecayVariables var;
  
  void Reset();

  ClassDef(TBetaDecayParams,2);
};

// Class data written to the output file
class TROOTDataOut : public TObject
{
public:
  TDDASDiagnostics ddasdiagnostics;
  TClock clock;
  // TPSPMTUTK pspmthigh1;
  // TPSPMTUTK pspmthigh2;
  // TPSPMTUTK pspmtlow1;
  // TPSPMTUTK pspmtlow2;

  // TPSPMTCeBr GpspmtCeBr;
  TPSPMTCeBr NpspmtCeBr;

  TPIN SIPMT; // SIPM T2 
  //TPIN PIN01T; // PIN01 time from FIFO
  TPIN DB3SLT; // Scintillator left time from FIFO
  TPIN DB3SRT; // Scintillator right time from FIFO

// db3 PPAC Anode
  TPIN DB3P0AT; // DB3PPAC 0 (Upstream) Anode time from FIFO
  TPIN DB3P1AT; // DB3PPAC 1 (Downstream) Anode time from FIFO

// db3 PPAC
  //TPIN DB3PPACULT; // DB3PPAC Up-left time from FIFO
  //TPIN DB3PPACURT; // DB3PPAC up-right time from FIFO
  //TPIN DB3PPACDLT; // DB3PPAC down-Left time from FIFO
  //TPIN DB3PPACDRT; // DB3PPAC down-Right time from FIFO

// db4 PPAC
  //TPIN DB4P0UT; // DB4PPAC Up time from FIFO
  //TPIN DB4P0DT; // DB4PPAC Down time from FIFO
  //TPIN DB4P0LT; // DB4PPAC Left time from FIFO
  //TPIN DB4P0RT; // DB4PPAC Right time from FIFO

// db5 PPAC
  //TPIN DB5PPACULT; // DB5PPAC Up-left time from FIFO
  //TPIN DB5PPACURT; // DB5PPAC up-right time from FIFO
  //TPIN DB5PPACDLT; // DB5PPAC down-Left time from FIFO
  //TPIN DB5PPACDRT; // DB5PPAC down-Right time from FIFO

  //TPIN NDB4P0LT; // DB4PPAC Left time from FIFO
  //TPIN NDB4PPACRT; // DB4PPAC Right time from FIFO

  TPIN pin01;
  TPIN pin02;
  //TPIN sipm;
  TPIN xscintB;
  TPIN xscintT;
  TPIN xpin1;
  TPIN xpin2;
  TPID pid;
  TCorrelation corr;
  TClover clover;
  TLaBr3 labr;
  
  void Reset();
  void SetOutputValues(TBetaDecayParams bdecay);

  ClassDef(TROOTDataOut,2);
};
#endif
