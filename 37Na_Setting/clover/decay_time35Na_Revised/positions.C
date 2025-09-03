#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TObject.h>
// Headers needed by this particular selector
#include <vector>

#include <TH1D.h>
#include <TH2D.h>
#include <TCutG.h>
#include <TH3D.h>
#include <TAxis.h>
#include <vector>
#include "/projects/e21062/Offline-Analysis/rootAnalysis/include/TPID.h"

 
 
{

 gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/include/");
  gInterpreter->AddIncludePath("/user/e21062/HLC/ddasfitclasses/");
   gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/libTParameters.so");
  TCutG* iongates_37 = new TCutG("iongates_37",11);
  iongates_37->SetVarX("PID");
  iongates_37->SetVarY("");
  iongates_37->SetTitle("Graph");
  iongates_37->SetFillStyle(1000);
  iongates_37->SetPoint(0,-957.224,762.111);
  iongates_37->SetPoint(1,-956.469,729.421);
  iongates_37->SetPoint(2,-956.884,701.09);
  iongates_37->SetPoint(3,-957.903,690.193);
  iongates_37->SetPoint(4,-958.62,703.269);
  iongates_37->SetPoint(5,-958.96,733.78);
  iongates_37->SetPoint(6,-958.658,753.394);
  iongates_37->SetPoint(7,-957.903,766.469);
  iongates_37->SetPoint(8,-957.45,773.007);
  iongates_37->SetPoint(9,-956.96,753.394);
  iongates_37->SetPoint(10,-957.224,762.111);


  
TFile* file= new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resortedNewCal37Na/run-1307-sorted.root","READ");
// TTree* data=(TTree*)file->Get("data");

 TChain *data = new TChain("data");
 data->Add("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resortedNewCal37Na/run-1307-sorted.root");
  TTreeReader freader(data);
   TTreeReaderValue<std::vector<TPID>> implantlist = {freader,"rootout.implantlist"};
  while(freader.Next()){
    if(sizeof(implantlist)>0){
      std::vector<TPID> zobry=*implantlist;
    double tof=zobry.at(0).tof;
    double de2=zobry.at(0).de2;
    }
  }
    
 // data->Draw("rootout.pspmtlow1.ypos:rootout.pspmtlow1.xpos>>h1(500,0,50,500,0,50)","","colz");
 // if( iongates_37->IsInside(implantlist[0].tof, implantlist[0].de2)) {
  // data->Draw("corr.dypos-implantlist[0].ypos:corr.dxpos-implantlist[0].xpos>>h1(500,-50,50,500,-50,50)","iongates_37->IsInside(implantlist[0].tof, implantlist[0].de2)","colz");
// TH2D* hist=(TH2D*)gDirectory("h1");
// hist->Draw("colz");
 // }
}
