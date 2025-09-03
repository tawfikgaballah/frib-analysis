#include "TParameters.h"

ClassImp(TBetaDecayParams);
ClassImp(TROOTDataOut);

// Full set of beta decay variables
void TBetaDecayVariables::Initialize()
{
  clock.Initialize();
  pspmthigh1.Initialize();
  pspmthigh2.Initialize();
  pspmtlow1.Initialize();
  pspmtlow2.Initialize();

  SIPMT.Initialize();
  PIN01T.Initialize();
  SCLT.Initialize();
  SCRT.Initialize();

// DB3 PPAC Anode 
  DB3PPACUAnT.Initialize();
  DB3PPACDAnT.Initialize();

// DB3 PPAC 
  DB3PPACULT.Initialize();
  DB3PPACURT.Initialize();
  DB3PPACDLT.Initialize();
  DB3PPACDRT.Initialize();

// db4 PPAC 
  DB4PPACUT.Initialize();
  DB4PPACDT.Initialize();
  DB4PPACLT.Initialize();
  DB4PPACRT.Initialize();

// DB5 PPAC 
  DB5PPACULT.Initialize();
  DB5PPACURT.Initialize();
  DB5PPACDLT.Initialize();
  DB5PPACDRT.Initialize();

  NDB4PPACLT.Initialize();
  NDB4PPACRT.Initialize();

  pin01.Initialize();
  pin02.Initialize();
  sipm.Initialize();
  xscintB.Initialize();
  xscintT.Initialize();
  xpin1.Initialize();
  xpin2.Initialize();
  vetoR.Initialize();
  vetoF.Initialize();
  corr.Initialize();
  clover.Initialize();
  labr.Initialize();
}


// The beta decay parameters
void TBetaDecayParams::Reset()
{
  ddasdiagnostics.Reset();
  clock.Reset();
  pspmthigh1.Reset();
  pspmthigh2.Reset();
  pspmtlow1.Reset();
  pspmtlow2.Reset();

  SIPMT.Reset();
  PIN01T.Reset();
  SCLT.Reset();
  SCRT.Reset();

// DB3 PPAC Anode
  DB3PPACUAnT.Reset();
  DB3PPACDAnT.Reset();

// DB3 PPAC
  DB3PPACULT.Reset();
  DB3PPACURT.Reset();
  DB3PPACDLT.Reset();
  DB3PPACDRT.Reset();

// db4 PPAC
  DB4PPACUT.Reset();
  DB4PPACDT.Reset();
  DB4PPACLT.Reset();
  DB4PPACRT.Reset();

// DB5 PPAC
  DB5PPACULT.Reset();
  DB5PPACURT.Reset();
  DB5PPACDLT.Reset();
  DB5PPACDRT.Reset();

  NDB4PPACLT.Reset();
  NDB4PPACRT.Reset();

  pin01.Reset();
  pin02.Reset();
  sipm.Reset();
  xscintB.Reset();
  xscintT.Reset();
  xpin1.Reset();
  xpin2.Reset();
  vetoR.Reset();
  vetoF.Reset();
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
  pspmthigh1.Reset();
  pspmthigh2.Reset();
  pspmtlow1.Reset();
  pspmtlow2.Reset();

  SIPMT.Reset();
  PIN01T.Reset();
  SCLT.Reset();
  SCRT.Reset();

// DB3 PPAC Anode
  DB3PPACUAnT.Reset();
  DB3PPACDAnT.Reset();

// DB3 PPAC
  DB3PPACULT.Reset();
  DB3PPACURT.Reset();
  DB3PPACDLT.Reset();
  DB3PPACDRT.Reset();

// db4 PPAC
  DB4PPACUT.Reset();
  DB4PPACDT.Reset();
  DB4PPACLT.Reset();
  DB4PPACRT.Reset();

// DB5 PPAC
  DB5PPACULT.Reset();
  DB5PPACURT.Reset();
  DB5PPACDLT.Reset();
  DB5PPACDRT.Reset();

  NDB4PPACLT.Reset();
  NDB4PPACRT.Reset();

  pin01.Reset();
  pin02.Reset();
  sipm.Reset();
  xscintB.Reset();
  xscintT.Reset();
  xpin1.Reset();
  xpin2.Reset();
  vetoR.Reset();
  vetoF.Reset();
  pid.Reset();
  corr.Reset();
  clover.Reset();
  labr.Reset();
}

void TROOTDataOut::SetOutputValues(TBetaDecayParams bdecay) {
  ddasdiagnostics = bdecay.ddasdiagnostics;  
  clock = bdecay.clock;
  pspmthigh1 = bdecay.pspmthigh1;
  pspmthigh2 = bdecay.pspmthigh2;
  pspmtlow1 = bdecay.pspmtlow1;
  pspmtlow2 = bdecay.pspmtlow2;
  SIPMT   = bdecay.SIPMT;
  PIN01T  = bdecay.PIN01T;
  SCLT    = bdecay.SCLT;
  SCRT    = bdecay.SCRT;

// DB3 PPAC Anode
  DB3PPACUAnT  = bdecay.DB3PPACUAnT;
  DB3PPACDAnT  = bdecay.DB3PPACDAnT;

// DB3 PPAC
  DB3PPACULT  = bdecay.DB3PPACULT;
  DB3PPACURT  = bdecay.DB3PPACURT;
  DB3PPACDLT  = bdecay.DB3PPACDLT;
  DB3PPACDRT  = bdecay.DB3PPACDRT;

// db4 PPAC
  DB4PPACUT  = bdecay.DB4PPACUT;
  DB4PPACDT  = bdecay.DB4PPACDT;
  DB4PPACLT  = bdecay.DB4PPACLT;
  DB4PPACRT  = bdecay.DB4PPACRT;

// DB5 PPAC
  DB5PPACULT  = bdecay.DB5PPACULT;
  DB5PPACURT  = bdecay.DB5PPACURT;
  DB5PPACDLT  = bdecay.DB5PPACDLT;
  DB5PPACDRT  = bdecay.DB5PPACDRT;

  NDB4PPACLT  = bdecay.NDB4PPACLT;
  NDB4PPACRT  = bdecay.NDB4PPACRT;

  pin01 = bdecay.pin01;
  pin02 = bdecay.pin02;
  sipm = bdecay.sipm;
  xscintB = bdecay.xscintB;
  xscintT = bdecay.xscintT;
  xpin1 = bdecay.xpin1;
  xpin2 = bdecay.xpin2;
  vetoR = bdecay.vetoR;
  vetoF = bdecay.vetoF;
  pid = bdecay.pid;
  corr = bdecay.corr;
  clover = bdecay.clover;
  labr = bdecay.labr;
}
