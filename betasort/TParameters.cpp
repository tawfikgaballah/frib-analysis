#include "TParameters.h"

ClassImp(TBetaDecayParams);
ClassImp(TROOTDataOut);

// Full set of beta decay variables
void TBetaDecayVariables::Initialize()
{
  clock.Initialize();
  //pspmthigh1.Initialize();
  //pspmthigh2.Initialize();
  //pspmtlow1.Initialize();
  //pspmtlow2.Initialize();

  NpspmtCeBr.Initialize();
  //GpspmtCeBr.Initialize();

  SIPMT.Initialize();
  //PIN01T.Initialize();
  DB3SLT.Initialize();
  DB3SRT.Initialize();

// DB3 PPAC Anode 
  DB3P0AT.Initialize();
  DB3P1AT.Initialize();

// DB3 PPAC 
  //DB3PPACULT.Initialize();
  //DB3PPACURT.Initialize();
  //DB3PPACDLT.Initialize();
  //DB3PPACDRT.Initialize();

// db4 PPAC 
  //DB4P0UT.Initialize();
  //DB4P0DT.Initialize();
  //DB4P0LT.Initialize();
  //DB4P0RT.Initialize();

// DB5 PPAC 
  //DB5PPACULT.Initialize();
  //DB5PPACURT.Initialize();
  //DB5PPACDLT.Initialize();
  //DB5PPACDRT.Initialize();

  //NDB4P0LT.Initialize();
  //NDB4PPACRT.Initialize();

  pin01.Initialize();
  pin02.Initialize();
  //sipm.Initialize();
  xscintB.Initialize();
  xscintT.Initialize();
  xpin1.Initialize();
  xpin2.Initialize();
  corr.Initialize();
  clover.Initialize();
  labr.Initialize();
}


// The beta decay parameters
void TBetaDecayParams::Reset()
{
  ddasdiagnostics.Reset();
  clock.Reset();
  //pspmthigh1.Reset();
  //pspmthigh2.Reset();
  //pspmtlow1.Reset();
  //pspmtlow2.Reset();

  NpspmtCeBr.Reset();
  //GpspmtCeBr.Reset();

  SIPMT.Reset();
  //PIN01T.Reset();
  DB3SLT.Reset();
  DB3SRT.Reset();

// DB3 PPAC Anode
  DB3P1AT.Reset();
  DB3P0AT.Reset();

// DB3 PPAC
  //DB3PPACULT.Reset();
  //DB3PPACURT.Reset();
  //DB3PPACDLT.Reset();
  //DB3PPACDRT.Reset();

// db4 PPAC
  //DB4P0UT.Reset();
  //DB4P0DT.Reset();
  //DB4P0LT.Reset();
  //DB4P0RT.Reset();

// DB5 PPAC
  //DB5PPACULT.Reset();
  //DB5PPACURT.Reset();
  //DB5PPACDLT.Reset();
  //DB5PPACDRT.Reset();

  //NDB4P0LT.Reset();
  //NDB4PPACRT.Reset();

  pin01.Reset();
  pin02.Reset();
  //sipm.Reset();
  xscintB.Reset();
  xscintT.Reset();
  xpin1.Reset();
  xpin2.Reset();
  pid.Reset();
  corr.Reset();
  clover.Reset();
  labr.Reset();
}

// ROOT output
void TROOTDataOut::Reset()
{
  ddasdiagnostics.Reset();
  clock.Reset();
  // pspmthigh1.Reset();
  // pspmthigh2.Reset();
  // pspmtlow1.Reset();
  // pspmtlow2.Reset();

  NpspmtCeBr.Reset();
  // GpspmtCeBr.Reset();

  SIPMT.Reset();
  //PIN01T.Reset();
  DB3SLT.Reset();
  DB3SRT.Reset();

// DB3 PPAC Anode
  DB3P0AT.Reset();
  DB3P1AT.Reset();

// DB3 PPAC
  //DB3PPACULT.Reset();
  //DB3PPACURT.Reset();
  //DB3PPACDLT.Reset();
  //DB3PPACDRT.Reset();

// db4 PPAC
  //DB4P0UT.Reset();
  //DB4P0DT.Reset();
  //DB4P0LT.Reset();
  //DB4P0RT.Reset();

// DB5 PPAC
  //DB5PPACULT.Reset();
  //DB5PPACURT.Reset();
  //DB5PPACDLT.Reset();
  //DB5PPACDRT.Reset();

  //NDB4P0LT.Reset();
  //NDB4PPACRT.Reset();

  pin01.Reset();
  pin02.Reset();
  //sipm.Reset();
  xscintB.Reset();
  xscintT.Reset();
  xpin1.Reset();
  xpin2.Reset();
  pid.Reset();
  corr.Reset();
  clover.Reset();
  labr.Reset();
}

void TROOTDataOut::SetOutputValues(TBetaDecayParams bdecay) {
  ddasdiagnostics = bdecay.ddasdiagnostics;  
  clock = bdecay.clock;
  // pspmthigh1 = bdecay.pspmthigh1;
  // pspmthigh2 = bdecay.pspmthigh2;
  // pspmtlow1 = bdecay.pspmtlow1;
  // pspmtlow2 = bdecay.pspmtlow2;
  // GpspmtCeBr = bdecay.GpspmtCeBr;
  NpspmtCeBr = bdecay.NpspmtCeBr;
  SIPMT   = bdecay.SIPMT;
  //PIN01T  = bdecay.PIN01T;
  DB3SLT    = bdecay.DB3SLT;
  DB3SRT    = bdecay.DB3SRT;

// DB3 PPAC Anode
  DB3P0AT  = bdecay.DB3P0AT;
  DB3P1AT  = bdecay.DB3P1AT;

// DB3 PPAC
  //DB3PPACULT  = bdecay.DB3PPACULT;
  //DB3PPACURT  = bdecay.DB3PPACURT;
  //DB3PPACDLT  = bdecay.DB3PPACDLT;
  //DB3PPACDRT  = bdecay.DB3PPACDRT;

// db4 PPAC
  //DB4P0UT  = bdecay.DB4P0UT;
  //DB4P0DT  = bdecay.DB4P0DT;
  //DB4P0LT  = bdecay.DB4P0LT;
  //DB4P0RT  = bdecay.DB4P0RT;

// DB5 PPAC
  //DB5PPACULT  = bdecay.DB5PPACULT;
  //DB5PPACURT  = bdecay.DB5PPACURT;
  //DB5PPACDLT  = bdecay.DB5PPACDLT;
  //DB5PPACDRT  = bdecay.DB5PPACDRT;

  //NDB4P0LT  = bdecay.NDB4P0LT;
  //NDB4PPACRT = bdecay.NDB4PPACRT;

  pin01 = bdecay.pin01;
  pin02 = bdecay.pin02;
  //sipm = bdecay.sipm;
  xscintB = bdecay.xscintB;
  xscintT = bdecay.xscintT;
  xpin1 = bdecay.xpin1;
  xpin2 = bdecay.xpin2;
  pid = bdecay.pid;
  corr = bdecay.corr;
  clover = bdecay.clover;
  labr = bdecay.labr;
}
