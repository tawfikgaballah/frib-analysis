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
#include "TPSPMT.h"
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

  TPINCalibrator SIPMT; // SIPM T2 
  TPINCalibrator PIN01T; // PIN01 time from FIFO
  TPINCalibrator SCLT; // Scintillator left time from FIFO
  TPINCalibrator SCRT; // Scintillator right time from FIFO

// db3 PPAC Anode
  TPINCalibrator DB3PPACUAnT; // DB3PPAC Up Anode time from FIFO
  TPINCalibrator DB3PPACDAnT; // DB3PPAC Down Anode time from FIFO

// db3 PPAC
  TPINCalibrator DB3PPACULT; // DB3PPAC Up-left time from FIFO
  TPINCalibrator DB3PPACURT; // DB3PPAC Up-right time from FIFO
  TPINCalibrator DB3PPACDLT; // DB3PPAC Down-Left time from FIFO
  TPINCalibrator DB3PPACDRT; // DB3PPAC Down-Right time from FIFO

// db4 PPAC
  TPINCalibrator DB4PPACUT; // DB4PPAC Up time from FIFO
  TPINCalibrator DB4PPACDT; // DB4PPAC Down time from FIFO
  TPINCalibrator DB4PPACLT; // DB4PPAC Left time from FIFO
  TPINCalibrator DB4PPACRT; // DB4PPAC Right time from FIFO

// db5 PPAC
  TPINCalibrator DB5PPACULT; // DB5PPAC Up-left time from FIFO
  TPINCalibrator DB5PPACURT; // DB5PPAC Up-right time from FIFO
  TPINCalibrator DB5PPACDLT; // DB5PPAC Down-Left time from FIFO
  TPINCalibrator DB5PPACDRT; // DB5PPAC Down-Right time from FIFO

  TPINCalibrator NDB4PPACLT; // DB4PPAC Left time from FIFO
  TPINCalibrator NDB4PPACRT; // DB4PPAC Right time from FIFO

  TPINCalibrator pin01;
  TPINCalibrator pin02;
  TPINCalibrator sipm;
  TPINCalibrator xscintB;
  TPINCalibrator xscintT;
  TPINCalibrator xpin1;
  TPINCalibrator xpin2;
  TPINCalibrator vetoR;
  TPINCalibrator vetoF;
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
  TPSPMTUTK pspmthigh1;
  TPSPMTUTK pspmthigh2;
  TPSPMTUTK pspmtlow1;
  TPSPMTUTK pspmtlow2;

  TPIN SIPMT; // SIPM T2 
  TPIN PIN01T; // PIN01 time from FIFO
  TPIN SCLT; // Scintillator left time from FIFO
  TPIN SCRT; // Scintillator right time from FIFO

// db3 PPAC Anode
  TPIN DB3PPACUAnT; // DB3PPAC Up Anode time from FIFO
  TPIN DB3PPACDAnT; // DB3PPAC Down Anode time from FIFO

// db3 PPAC
  TPIN DB3PPACULT; // DB3PPAC Up-left time from FIFO
  TPIN DB3PPACURT; // DB3PPAC up-right time from FIFO
  TPIN DB3PPACDLT; // DB3PPAC down-Left time from FIFO
  TPIN DB3PPACDRT; // DB3PPAC down-Right time from FIFO

// db4 PPAC
  TPIN DB4PPACUT; // DB4PPAC Up time from FIFO
  TPIN DB4PPACDT; // DB4PPAC Down time from FIFO
  TPIN DB4PPACLT; // DB4PPAC Left time from FIFO
  TPIN DB4PPACRT; // DB4PPAC Right time from FIFO

// db5 PPAC
  TPIN DB5PPACULT; // DB5PPAC Up-left time from FIFO
  TPIN DB5PPACURT; // DB5PPAC up-right time from FIFO
  TPIN DB5PPACDLT; // DB5PPAC down-Left time from FIFO
  TPIN DB5PPACDRT; // DB5PPAC down-Right time from FIFO

  TPIN NDB4PPACLT; // DB4PPAC Left time from FIFO
  TPIN NDB4PPACRT; // DB4PPAC Right time from FIFO

  TPIN pin01;
  TPIN pin02;
  TPIN sipm;
  TPIN xscintB;
  TPIN xscintT;
  TPIN xpin1;
  TPIN xpin2;
  TPIN vetoR;
  TPIN vetoF;
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
  TPSPMTUTK pspmthigh1;
  TPSPMTUTK pspmthigh2;
  TPSPMTUTK pspmtlow1;
  TPSPMTUTK pspmtlow2;

  TPIN SIPMT; // SIPM T2 
  TPIN PIN01T; // PIN01 time from FIFO
  TPIN SCLT; // Scintillator left time from FIFO
  TPIN SCRT; // Scintillator right time from FIFO

// db3 PPAC Anode
  TPIN DB3PPACUAnT; // DB4PPAC Up Anode time from FIFO
  TPIN DB3PPACDAnT; // DB4PPAC Down Anode time from FIFO

// db3 PPAC
  TPIN DB3PPACULT; // DB3PPAC Up-left time from FIFO
  TPIN DB3PPACURT; // DB3PPAC up-right time from FIFO
  TPIN DB3PPACDLT; // DB3PPAC down-Left time from FIFO
  TPIN DB3PPACDRT; // DB3PPAC down-Right time from FIFO

// db4 PPAC
  TPIN DB4PPACUT; // DB4PPAC Up time from FIFO
  TPIN DB4PPACDT; // DB4PPAC Down time from FIFO
  TPIN DB4PPACLT; // DB4PPAC Left time from FIFO
  TPIN DB4PPACRT; // DB4PPAC Right time from FIFO

// db5 PPAC
  TPIN DB5PPACULT; // DB5PPAC Up-left time from FIFO
  TPIN DB5PPACURT; // DB5PPAC up-right time from FIFO
  TPIN DB5PPACDLT; // DB5PPAC down-Left time from FIFO
  TPIN DB5PPACDRT; // DB5PPAC down-Right time from FIFO

  TPIN NDB4PPACLT; // DB4PPAC Left time from FIFO
  TPIN NDB4PPACRT; // DB4PPAC Right time from FIFO

  TPIN pin01;
  TPIN pin02;
  TPIN sipm;
  TPIN xscintB;
  TPIN xscintT;
  TPIN xpin1;
  TPIN xpin2;
  TPIN vetoR;
  TPIN vetoF;
  TPID pid;
  TCorrelation corr;
  TClover clover;
  TLaBr3 labr;
  
  void Reset();
  void SetOutputValues(TBetaDecayParams bdecay);

  ClassDef(TROOTDataOut,2);
};
#endif
