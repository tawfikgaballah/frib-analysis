#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include "./include/TPID.h"
void Reader(){
  TChain *data = new TChain("data");
  data->Add("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-xscintT-sipm-sorted-TG-48-hasGoodPosition-check-20mm-dyoverflow-unconditioned-corrections-from-amelia-neutron-pid-1s*");
    
   TFile *file =new TFile("D30Ne_10mm_Forward_Reverse_neutron.root","recreate");
  // TCutG* D30Ne=(TCutG*)file->Get("CUTG");
   // TCutG *D30Ne = new TCutG("D30Ne",9);
   // D30Ne->SetVarX("implantlist.tof");
   // D30Ne->SetVarY("implantlist.de2");
   // D30Ne->SetTitle("D30Ne");
   // D30Ne->SetFillStyle(1000);
   // D30Ne->SetPoint(0,-972.057,517.561);
   // D30Ne->SetPoint(1,-970.753,501.619);
   // D30Ne->SetPoint(2,-970.167,478.593);
   // D30Ne->SetPoint(3,-971.992,443.168);
   // D30Ne->SetPoint(4,-973.556,453.796);
   // D30Ne->SetPoint(5,-974.012,482.136);
   // D30Ne->SetPoint(6,-972.774,514.018);
   // D30Ne->SetPoint(7,-971.601,514.018);
   // D30Ne->SetPoint(8,-972.057,517.561);


  TCutG *D30Ne_neutron = new TCutG("D30Ne_neutron",11);
   D30Ne_neutron->SetVarX("implantlist.tof");
   D30Ne_neutron->SetVarY("implantlist.de2");
   D30Ne_neutron->SetTitle("D30Ne_n");
   D30Ne_neutron->SetFillStyle(1000);
   D30Ne_neutron->SetPoint(0,-1472.42,510.476);
   D30Ne_neutron->SetPoint(1,-1470.79,498.077);
   D30Ne_neutron->SetPoint(2,-1470.27,471.508);
   D30Ne_neutron->SetPoint(3,-1471.18,444.939);
   D30Ne_neutron->SetPoint(4,-1472.48,436.083);
   D30Ne_neutron->SetPoint(5,-1473.66,441.397);
   D30Ne_neutron->SetPoint(6,-1474.31,452.024);
   D30Ne_neutron->SetPoint(7,-1474.31,476.822);
   D30Ne_neutron->SetPoint(8,-1473.46,499.848);
   D30Ne_neutron->SetPoint(9,-1472.29,512.247);
   D30Ne_neutron->SetPoint(10,-1472.42,510.476);
  // Initialize TTreeReader using the TChain
  TTreeReader fReader(data);

  // Reading values from the TTree
  TTreeReaderValue<std::vector<TPID>> implantlist(fReader, "implantlist");
  TTreeReaderValue<double> corr_dxpos(fReader, "corr.dxpos");
  TTreeReaderValue<double> corr_dypos(fReader, "corr.dypos");
   TTreeReaderValue<int> pspmtlow1_dyhit(fReader, "pspmtlow1.dyhit");
  TTreeReaderArray<Double_t> clover_ecal(fReader, "clover.ecal[52]");
  TH1D* clover_E=new TH1D("Total Clover Spectrum, gated on #beta-decays of ^{30}Ne","Total Clover Spectrum, gated on #beta-decays of ^{30}Ne",4500,0,4500);
  // Iterating through the implant list
  while (fReader.Next()) {
    for (auto& implant : *implantlist) {
      double tof1 = implant.tof;
      double DE2 = implant.de2;
      double ixpos=implant.xpos;
      double iypos= implant.ypos;
      if(D30Ne_neutron->IsInside(tof1, DE2) && (sqrt(pow((ixpos-*corr_dxpos),2)+pow((iypos-*corr_dypos),2)))<=10){
	for(int i=0; i<52; i++){
	  if(clover_ecal[i]>20){
	    clover_E->Fill(clover_ecal[i]);
	  }
	}
      }
    }
  }
  file->cd();
  clover_E->Write();
  clover_E->Draw("");
}
