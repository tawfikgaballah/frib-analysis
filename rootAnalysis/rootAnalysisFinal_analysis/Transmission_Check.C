#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TString.h>
#include <vector>
#include <string>
#include <TCutG.h>

  

// Define each analysis type with specific histogram parameters
struct AnalysisConfig {
    std::string type;
    std::string canvasName;
    std::string drawCommand;
    std::string condition;
    int nBinsX;
    double xLow;
    double xHigh;
    int nBinsY;
    double yLow;
    double yHigh;
  std::string xTitle;
  std::string yTitle;
  bool is1D;
};

std::vector<AnalysisConfig> configs = {
				               // {"PID_Implant_UP", "PID_Implant_UP", "pin02.energy:(sipm.time-DB3PPACDAnT.time)>>", "corr.isforward==1 &&sipm.energy>10  && pspmtlow1.dyenergy>10", 1000, -1000, -900, 1400, 0, 1400,"tof","de2", false},
					       // {"PID_Implant_Down", "PID_Implant_Down", "pin02.energy:(sipm.time-DB3PPACDAnT.time)>>", "corr.isforward==1 &&sipm.energy>10  && pspmtlow1.dyenergy>10", 1000, -1000, -900, 1400, 0, 1400,"tof","de2", false},
				       //    {"PID_Implant_neutron", "PID_Implant_neutron", "xpin2.energy:(sipm.time-DB3PPACULT.time)>>", "corr.isforward==1 &&sipm.energy>10  && pspmtlow1.dyenergy>10", 1000, -1500,-1400, 1400, 0, 1400,"pid_tof","pid_de2", false}
                // {"PID_Implant_Correlated", "PID_Implant_Correlated", "pin02.energy:(sipm.time-DB3PPACDAnT.time)>>", "sipm.energy>10  && pspmtlow1.dyenergy>10 ", 1000, -1000, -900, 1400, 0, 1400,"tof","de2", false},
				       // {"pin2_neutron_crate_Vs_tof_DB3UA_neutron_crate_", "pin2_neutron_crate__Vs_tof_DB3UA_neutron_crate_", "xpin2.ecal:(sipm.time-DB3PPACULT.time)>>", "xscintT.hit==1 && pspmtlow1.dyhit==1 &&xpin2.ecal>240 && DB3PPACULT.hit==1 &&corr.isforward==1 &&sipm.hit==1", 1000, -1500,-1400, 1400, 0, 1400,"sipm_time-DB3PPACUAnT_time_neutron_crate","pin2_energy_neutron_crate", false},
					  
				       // {"pin2_gamma_crate__Vs_tof_DB3UA_gamma_crate_", "pin2_gamma_crate__Vs_tof_DB3UA_gamma_crate_", "pin02.ecal:(sipm.time-DB3PPACUAnT.time)>>", "xscintT.hit==1 && pspmtlow1.dyhit==1 &&pin02.ecal>240 && DB3PPACUAnT.hit==1 &&corr.isforward==1 &&sipm.hit==1", 1000, -1010,-910, 1400, 0, 1400,"sipm_time-DB3PPACUAnT_time_gamma_crate","pin2_energy_gamma_crate", false},
					  
					  // {"pin2_gamma_crate__Vs_tof_DB3UA_neutron_crate_", "pin2_gamma_crate__Vs_tof_DB3UA_neutron_crate_", "pin02.energy:(sipm.time-DB3PPACULT.time)>>", "xscintT.hit==1 && pspmtlow1.dyhit==1 &&pin02.ecal>240 && DB3PPACULT.hit==1 &&corr.isforward==1 &&sipm.hit==1", 1000, -1500,-1400, 1400, 0, 1400,"sipm_time-DB3PPACUAnT_time_neutron_crate","pin2_energy_gamma_crate", false},
					  
					  // {"pin2_gamma_crate__Vs_tof_DB3DA_gamma_crate_", "pin2_gamma_crate__Vs_tof_DB3DA_gamma_crate_", "pin02.ecal:(sipm.time-DB3PPACDAnT.time)>>", "xscintT.hit==1 && pspmtlow1.dyhit==1 &&pin02.ecal>240 && DB3PPACUAnT.hit==1 &&corr.isforward==1 &&sipm.hit==1", 1000, -1010,-910, 1400, 0, 1400,"sipm_time-DB3PPACDAnT_time_gamma_crate","pin2_energy_gamma_crate", false}
					  
					  // {"PID_Implant_neutron_crate", "PID_Implant_neutron_crate", "corr.ide2:corr.itof>>", "corr.isforward==1", 1000, -1500, -1400, 1400, 0, 1400,"corr_itof","corr_ide2", false}
				       // {"DyEcal_Low_Implant", "DyEcal_Low_Implant", "pspmtlow1.dyecal:(pspmtlow1.dytime-clover.time)>>", "corr.isdecay==1",8000,-2000,2000,7000,0,70000,"dytime-clover_time","pspmtlow1_dyecal", false}
				        //   {"DB3_U_Gamma", "DB3_U_Gamma", "DB3PPACUAnT.energy>>", "corr.isforward==1",10000,0,10000,0,0,0,"DB3PPACUAnT","", true},
				       
				       // {"DB3DA_Gamma_tof_Vs_DB3UA_Gamma_tof", "DB3DA_Gamma_tof_Vs_DB3UA_Gamma_tof", "(sipm.time-DB3PPACDAnT.time):(sipm.time-DB3PPACUAnT.time)>>", "corr.isforward==1&&pin02.ecal>240 &&pin02.ecal<1400",1000,-1010,-910,1000,-1010,-910,"sipm_time-DB3PPACUAnT_Gamma","sipm_time-DB3PPACDAnT_Gamma",false},
				       // {"DB3UA_neutron_tof_Vs_DB3UA_Gamma_tof", "DB3UA_neutron_tof_Vs_DB3UA_Gamma_tof", "(sipm.time-DB3PPACULT.time):(sipm.time-DB3PPACUAnT.time)>>", "corr.isforward==1 &&pin02.ecal>240 &&pin02.ecal<1400",1000,-1010,-910,1000,-1500,-1400,"sipm_time-DB3PPACUAnT_Gamma","sipm_time-DB3PPACUAnT_neutron",false},
				       // {"DB3UA_neutron_tof_Vs_DB3DA_Gamma_tof", "DB3UA_neutron_tof_Vs_DB3DA_Gamma_tof", "(sipm.time-DB3PPACULT.time):(sipm.time-DB3PPACDAnT.time)>>", "corr.isforward==1&&pin02.ecal>240 &&pin02.ecal<1400",1000,-1010,-910,1000,-1500,-1400,"sipm_time-DB3PPACDAnT_Gamma","sipm_time-DB3PPACUAnT_neutron",false},
				       // {"DB3DA_Gamma_Energy_Vs_DB3UA_neutron_Energy", "DB3DA_Gamma_Energy_Vs_DB3UA_neutron_Energy", "DB3PPACDAnT.energy:DB3PPACULT.energy>>", "corr.isforward==1&&pin02.ecal>240 &&pin02.ecal<1400",10000,0,10000,10000,0,10000,"DB3PPACUAnT_neutron","DB3PPACDAnT_Gamma",false},
				       //	 {"DB3UA_Gamma_Energy_Vs_DB3UA_neutron_Energy", "DB3UA_Gamma_Energy_Vs_DB3UA_neutron_Energy", "DB3PPACUAnT.energy:DB3PPACULT.energy>>", "corr.isforward==1",10000,0,10000,10000,0,10000,"DB3PPACUAnT_neutron","DB3PPACUAnT_Gamma",false},
				        

				       //    {"DB3_U_Neutron", "DB3_U_Neutron", "DB3PPACULT.energy:(sipm.time-DB3PPACULT.time)>>", "corr.isforward==1&&pin02.ecal>240 &&pin02.ecal<1400 &&sipm.hit==1 &&DB3PPACULT.hit==1",1000,-1500,-1400,10000,0,10000,"DB3PPACUAnT_time","DB3PPACUAnT_energy", false},
				        // {"DB3_U_Gamma", "DB3_U_Gamma", "DB3PPACUAnT.energy:(sipm.time-DB3PPACUAnT.time)>>", "corr.isforward==1&&pin02.ecal>240 &&pin02.ecal<1400 &&sipm.hit==1 &&DB3PPACUAnT.hit==1",1000,-1010,-910,10000,0,10000,"DB3PPACUAnT_time","DB3PPACUAnT_energy", false},
				        // {"DB3_D_Gamma", "DB3_D_Gamma", "DB3PPACDAnT.energy:(sipm.time-DB3PPACDAnT.time)>>", "corr.isforward==1&&pin02.ecal>240 &&pin02.ecal<1400 &&sipm.hit==1&& DB3PPACDAnT.hit==1",1000,-1010,-910,10000,0,10000,"DB3PPACDAnT_time","DB3PPACDAnT_energy", false}
				       // {"DyEcal_Low_Decay", "DyEcal_Low_Decay", "pspmtlow1.dyecal:(pspmtlow1.dytime-clover.time)>>", "",8000,-2000,2000,7000,0,70000,"dytime-clover_time","pspmtlow1_dyecal", false}
					// {"DyEcal_Low_Correlated", "DyEcal_Low_Correlated", "pspmtlow1.dyecal>>", "",7000,0,70000,0,0,0,"pspmtlow1_dyecal","", true},
					// {"pid_de2", "pid_de2", "pid.de2>>", "",1400,0,1400,0,0,0,"pid_pin2","", true},
					// {"pin02_energy", "pin02_energy", "pin02.energy>>", "",1400,0,1400,0,0,0,"pin2","", true}
				       //    {"clover_ecal", "clover_ecal", "clover.ecal>>", "clover.ecal>20 &&D30Ne ",4500,0,4500,0,0,0,"clover_ecal","", true},
				       // {"DyEcal_Low_Not_Correlated", "DyEcal_Low_Not_Correlated", "pspmtlow1.dyecal>>", "PID_33Na&&pspmtlow1.dyecal>10",7000,0,70000,0,0,0,"pspmtlow1_dyecal","", true},
				       //  {"xscintTE_Correlated", "xscintE_Correlated", "xscintT.ecal>>", "I33Na&&xscintT.ecal>10",7000,0,70000,0,0,0,"xscint_Ecal","", true},
				       // {"xscintTE_Not_Correlated", "xscintE_Not_Correlated", "xscintT.ecal>>", "PID_33Na&&xscintT.ecal>10",7000,0,70000,0,0,0,"xscint_Ecal","", true}
				       // {"sipmE_Correlated", "sipmE_Correlated", "sipm.ecal>>", "I33Na&&sipm.ecal>10",7000,0,70000,0,0,0,"sipm_Ecal","", true},
				       // 	 {"sipmE_Not_Correlated", "sipmE_Not_Correlated", "sipm.ecal>>", "PID_33Na&&sipm.ecal>10",7000,0,70000,0,0,0,"sipm_Ecal","", true}
				       // {"PID_Implant_no_dynode_has_sipm", "PID_Implant_no_dynode_has_sipm", "pid.de2:pid.tof>>", "sipm.hit==1 && pspmthigh1.hit==1 &&pspmtlow1.hit!=1", 500, -1000, -950, 1400, 0, 1400,"tof","de2", false}
				       // {"pspmtlow1E_Vs_sipmE", "pspmtlow1_Vs_sipmE", "pspmtlow1.dyecal:sipm.ecal>>", "pid.de2>240 &&pid.tof<-950&&pid.tof>-1000",7000,0,70000,7000,0,70000,"sipmE","pspmtlow1E", false}
				       // {"sipmE_Not_Correlated_has_pspmtlow", "sipmE_Not_Correlated_haspspmtlow", "sipm.ecal>>", "PID_33Na&&sipm.ecal>10 &&pspmtlow1.hit==1",7000,0,70000,0,0,0,"sipm_Ecal","", true}
				       // {"pspntlow1_dyoverflow_not_correlated", "pspmtlow1_dyoverflow_not_correlated", "pspmthigh1.hit:pspmtlow1.hit>>", "PID_33Na", 4,-2,2, 4,-2,2,"pspmtlow1_hit","pspmthigh1_hit",false},
				        //{"PID_Implant_no_dynode_has_sipm", "PID_Implant_no_dynode_has_sipm", "pid.de2:pid.tof>>", "sipm.hit==1 && pspmthigh1.hit!=1&&pspmtlow1.hit!=1", 500, -1000, -950, 1400, 0, 1400,"itof","ide2", false}
				       // {"sipmE_Not_Correlated_has_pspmtlow", "sipmE_Not_Correlated_haspspmtlow", "sipm.ecal>>", "PID_33Na&&sipm.ecal>10 &&pspmtlow1.hit==1",7000,0,70000,0,0,0,"sipm_Ecal","", true},
				       // 	  {"sipmE_Not_Correlated_!has_pspmtlow", "sipmE_Not_Correlated_!haspspmtlow", "sipm.ecal>>", "PID_33Na&&sipm.ecal>10 &&pspmtlow1.hit!=1",7000,0,70000,0,0,0,"sipm_Ecal","", true}
				       // {"PID_Implant_hasxscintT", "PID_Implant_hasxsscintT", "corr.ide2:corr.itof>>", "corr.isforward==1 && xscintT.hit==1 &&implant ", 500, -1000, -950, 1400, 0, 1400,"itof","ide2", false},
				       // {"PID_Implant_!hasxscintT", "PID_Implant_!hasxsscintT", "corr.ide2:corr.itof>>", "corr.isforward==1 && xscintT.hit!=1 &&implant ", 500, -1000, -950, 1400, 0, 1400,"itof","ide2", false},
				       //   {"PID_Decay", "PID_Decay", "implantlist.de2:implantlist.tof>>", "", 1000, -1010,-910, 1400, 0, 1400,"implantlist.tof","implantlist.de2", false}
				       // {"Position_2D_HG", "Position_2D_HG", "pspmthigh1.ypos_highgain:pspmthigh1.xpos_highgain>>", "corr.isforward==1&&corr.radius<=10", 600, -10, 50, 600, -10, 50,"xpos_HG","ypos_HG", false },
				       // {"Position_2D_LG", "Position_2D_LG", "pspmtlow1.ypos:pspmtlow1.xpos>>", "corr.isforward==1 &&corr.radius<=10", 600, -10, 50, 600, -10, 50,"xpos_LG","ypos_LG", false},
				       // {"Beta_Energy_Vs_DTime", "Beta_Energy_Vs_DTimr", "pspmthigh1.dyecal:(corr.decaytime)>>", "corr.isdecay==1 &&corr.radius<=10", 200, -100, 100, 10000, 0, 100000,"decay_time", "pspmthigh1.dyecal",false},
				       // {"BetaEnergy_Vs_Radius", "BetaEnergy_Vs_Radius", "pspmthigh1.dyecal:sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))>>", "pspmthigh1.dyecal>0 && corr.isforward==1 &&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=10", 100, 0, 10, 7000, 0, 70000,"decay_radius", "pspmthigh1.dyecal",false},
				       // {"Beta_Energy_Vs_Scint_Energy", "Beta_Energy_Vs_Scint_Energy", "pspmthigh1.dyecal:sipm.energy>>", "corr.isforward==1 && pspmthigh1.dyecal>0 && sipm.energy>0 &&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=10", 1600, 0, 16000, 7000, 0, 70000,"sipm.energy","pspmthigh1.dyecal", false},
				       // {"pspmtlow_Vs_Scint_Energy", "pspmtlow_Vs_Scint_Energy", "pspmtlow1.dyecal:sipm.energy>>", "corr.isforward==1 && pspmtlow1.dyecal>0 && sipm.energy>0&&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=10", 1600, 0, 16000, 7000, 0, 70000,"sipm.energy","pspmtlow1.dyecal", false},
				      // {"radius_Vs_decaytime", "radius_Vs_decaytime", "sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2)):(corr.decaytime)>>", "corr.flag==32 && corr.isdecay==1 &&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=10", 200,-100,100, 100,0,10,"decaytime [ms]","radius [mm]", false},
				       // {"radius_Vs_#beta_energy", "radius_Vs_#beta_energy", "(sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))):(pspmthigh1.dyecal)>>", "corr.isforward==1 && pspmthigh1.dyecal>0 &&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=10 ",7000,0,70000,100,0,10,"#beta_energy_highgain [ms]","radius [mm]", false}
				       //  {"Decaytime", "Decaytime", "(corr.dtime-implantlist.time)>>", "D30Ne_neutron &&corr.isforward==1",1100,-100,1000,0,0,0,"decaytime [ms]","", true}
				       {"DB3_U_Neutron", "DB3_U_Neutron", "DB3PPACULT.energy>>", "corr.isforward==1",10000,0,10000,0,0,0,"DB3PPACUAnT","", true},
				       {"DB3_U_Gamma", "DB3_U_Gamma", "DB3PPACUAnT.energy>>", "corr.isforward==1",10000,0,10000,0,0,0,"DB3PPACUAnT","", true},
				       {"DB3_D_Gamma", "DB3_D_Gamma", "DB3PPACDAnT.energy>>", "corr.isforward==1",10000,0,10000,0,0,0,"DB3PPACDAnT","", true},

				        // {"DB3_U_Neutron_Vs_tof", "DB3_U_Neutron_Vs_tof", "DB3PPACULT.energy:(sipm.time-DB3PPACULT.time)>>", "corr.isforward==1 &&sipm.hit==1 &&DB3PPACULT.hit==1",1000,-1500,-1400,10000,0,10000,"DB3PPACUAnT_time","DB3PPACUAnT_energy", false},
				        // {"DB3_U_Gamma_Vs_tof", "DB3_U_Gamma_Vs_tof", "DB3PPACUAnT.energy:(sipm.time-DB3PPACUAnT.time)>>", "corr.isforward==1&& sipm.hit==1 &&DB3PPACUAnT.hit==1",1000,-1010,-910,10000,0,10000,"DB3PPACUAnT_time","DB3PPACUAnT_energy", false},
				        // {"DB3_D_Gamma_Vs_tof", "DB3_D_Gamma_Vs_tof", "DB3PPACDAnT.energy:(sipm.time-DB3PPACDAnT.time)>>", "corr.isforward==1&& sipm.hit==1&& DB3PPACDAnT.hit==1",1000,-1010,-910,10000,0,10000,"DB3PPACDAnT_time","DB3PPACDAnT_energy", false}

					 {"PID_Implant_UP_Gamma", "PID_Implant_UP_Gamma", "pin02.energy:(sipm.time-DB3PPACDAnT.time)>>", "corr.isforward==1 &&xscintT.energy>10  && pspmtlow1.dyenergy>10", 1000, -1000, -900, 1400, 0, 1400,"tof","de2", false},
				       
					 {"PID_Implant_Down_Gamma", "PID_Implant_Down_Gamma", "pin02.energy:(sipm.time-DB3PPACDAnT.time)>>", "corr.isforward==1 &&xscintT.energy>10  && pspmtlow1.dyenergy>10", 1000, -1000, -900, 1400, 0, 1400,"tof","de2", false},
				       
				         {"PID_Implant_neutron", "PID_Implant_neutron", "xpin2.energy:(sipm.time-DB3PPACULT.time)>>", "corr.isforward==1 &&xscintT.energy>10  && pspmtlow1.dyenergy>10", 1000, -1500,-1400, 1400, 0, 1400,"tof","de2", false}
				       
};
void Transmission_Check() {
  gStyle->SetOptStat(111111111); 
  TCutG *I33Na = new TCutG("I33Na",12);
   I33Na->SetVarX("corr.itof");
   I33Na->SetVarY("corr.ide2");
   I33Na->SetTitle("Corr_PID");
   I33Na->SetFillStyle(1000);
   I33Na->SetPoint(0,-971.416,626.249);
   I33Na->SetPoint(1,-970.145,597.112);
   I33Na->SetPoint(2,-969.982,564.334);
   I33Na->SetPoint(3,-971.578,542.482);
   I33Na->SetPoint(4,-973.012,547.945);
   I33Na->SetPoint(5,-974.088,571.618);
   I33Na->SetPoint(6,-973.99,591.649);
   I33Na->SetPoint(7,-972.556,620.786);
   I33Na->SetPoint(8,-971.253,622.607);
   I33Na->SetPoint(9,-971.025,622.607);
   I33Na->SetPoint(10,-971.187,618.965);
   I33Na->SetPoint(11,-971.416,626.249);

TCutG *PID_33Na = new TCutG("PID_33Na",9);
   PID_33Na->SetVarX("pid.tof");
   PID_33Na->SetVarY("pid.de2");
   PID_33Na->SetTitle("PID");
   PID_33Na->SetFillStyle(1000);
   PID_33Na->SetPoint(0,-971.289,635.354);
   PID_33Na->SetPoint(1,-969.819,600.754);
   PID_33Na->SetPoint(2,-969.603,564.334);
   PID_33Na->SetPoint(3,-971.289,537.019);
   PID_33Na->SetPoint(4,-973.225,546.124);
   PID_33Na->SetPoint(5,-973.727,577.081);
   PID_33Na->SetPoint(6,-973.189,620.786);
   PID_33Na->SetPoint(7,-970.966,631.712);
   PID_33Na->SetPoint(8,-971.289,635.354);




   TCutG *D33Na = new TCutG("D33Na",9);
   D33Na->SetVarX("implantlist.tof");
   D33Na->SetVarY("implantlist.de2");
   D33Na->SetTitle("PID_Decay");
   D33Na->SetFillStyle(1000);
   D33Na->SetPoint(0,-971.807,629.15);
   D33Na->SetPoint(1,-970.699,614.98);
   D33Na->SetPoint(2,-970.373,568.927);
   D33Na->SetPoint(3,-971.709,538.816);
   D33Na->SetPoint(4,-972.817,545.901);
   D33Na->SetPoint(5,-973.794,576.012);
   D33Na->SetPoint(6,-973.631,611.437);
   D33Na->SetPoint(7,-971.709,629.15);
   D33Na->SetPoint(8,-971.807,629.15);


    TCutG *D33Na_neutron = new TCutG("D33Na_neutron",9);
   D33Na_neutron->SetVarX("implantlist.tof");
   D33Na_neutron->SetVarY("implantlist.de2");
   D33Na_neutron->SetTitle("");
   D33Na_neutron->SetFillStyle(1000);
   D33Na_neutron->SetPoint(0,-1472.22,629.15);
   D33Na_neutron->SetPoint(1,-1470.4,604.352);
   D33Na_neutron->SetPoint(2,-1470.07,581.326);
   D33Na_neutron->SetPoint(3,-1471.77,551.215);
   D33Na_neutron->SetPoint(4,-1473.33,551.215);
   D33Na_neutron->SetPoint(5,-1474.24,579.555);
   D33Na_neutron->SetPoint(6,-1473.92,618.522);
   D33Na_neutron->SetPoint(7,-1471.9,630.921);
   D33Na_neutron->SetPoint(8,-1472.22,629.15);


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
   TFile *file =new TFile("D30Ne.root","read");

   TCutG* D30Ne=(TCutG*)file->Get("D30Ne");

 TCutG *D30Ne_neutron = new TCutG("D30Ne_neutron",11);
   D30Ne_neutron->SetVarX("implantlist[0].tof");
   D30Ne_neutron->SetVarY("implantlist[0].de2");
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
   
  // Define the conditions for the various analyses
   std::vector<std::string> beta_gate_conditions = {"PIN", "xscintT"};
  std::vector<std::string> tofv_conditions = {"sipm"};

  // Calculate total number of combinations
  int totalCombinations = beta_gate_conditions.size() * tofv_conditions.size();
  std::vector<TFile*> files(totalCombinations);
  // std::vector<TTree*> data(totalCombinations);
  std::vector<std::string> names(totalCombinations);

  int index = 0;

  ///////////////////// USE IF YOU WANT TO SAVE HISTOGRAMS TO FILES //////////////////////////////////////////////
  
  // TFile* output=new TFile("flag_check_hasGoodPosition-check-dyoverflow.root","recreate");
  // for (int index = 0; index < totalCombinations; index++) {
  //   std::string beta_gate = beta_gate_conditions[index % beta_gate_conditions.size()];
  //   std::string tofv = tofv_conditions[index / beta_gate_conditions.size()];
  //   std::string baseName = "gate_on_" + beta_gate + "_and_" + tofv + "_tof";
  //   std::string filePath = "/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-" + beta_gate + "-" + tofv + "-sorted-TG-48-hasGoodPosition-check-dyoverflow-100mm.root";
        
  //   files[index] = new TFile(filePath.c_str(), "READ");
  //   data[index] = static_cast<TTree*>(files[index]->Get("data"));












    // // Assuming 'data' and 'output' are properly initialized and available

    // std::vector<int> flags = {-1, 4, 8, 12, 16, 20, 28, 32, 44, 96, 99};
    // TDirectory* baseDir = output->mkdir(baseName.c_str());
    // baseDir->cd(); // Change to the base directory

 

    // for (const auto& config : configs) {
    //   std::string subdirname= config.type;
    //   TDirectory* subDir = baseDir->mkdir(subdirname.c_str());
    //   subDir->cd();

    //   for (int flag : flags) {
    //     std::string titleBase = baseName + "_" + config.type;
    //     if (flag == -1) {
    // 	  titleBase += "_AllData";
    //     } else {
    // 	  titleBase += "_Flag_" + std::to_string(flag);
    //     }

    //     std::string histogramTitle = titleBase;
    // 	std::string fullTitle = histogramTitle + ";" + config.xTitle + ";" + config.yTitle;

    // 	TH2D* hist = new TH2D(histogramTitle.c_str(), fullTitle.c_str(), config.nBinsX, config.xLow, config.xHigh, config.nBinsY, config.yLow, config.yHigh);

    //     std::string condition = (flag == -1) ? "" : "corr.flag==" + std::to_string(flag);
    //     if (!config.condition.empty()) {
    // 	  condition = (flag == -1) ? config.condition : config.condition + " && corr.flag==" + std::to_string(flag);
    //     }

    //     data[index]->Draw((config.drawCommand + histogramTitle).c_str(), condition.c_str(), "colz");

    //     hist->Write();
    //   }
    //   output->cd();
    // }

  ////////////////////////////////////////////////////


  TFile* output=new TFile("DB3_Energy.root","recreate");
  //////////////USE IF YOU WANT TO DRAW STUFF ON CANVAS//////////////////////////
  int countcanvas=0; 
  for (const auto& config : configs) {
    std::string canvasname= config.canvasName;
    TCanvas* canvas =new TCanvas(canvasname.c_str(), canvasname.c_str(), 2000, 1200);
    canvas->Divide(beta_gate_conditions.size());
      
    // std::string filePath = "/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-xscintT-sipm-sorted-TG-48-hasGoodPosition-check-6mm-dyoverflow-unconditioned-corrections-from-amelia-neutron-pid-1s.root"; 
       // std::string filePath = "/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/decay_and_gamma_run-1428-sorted.root"; 
      // files[0] = new TFile(filePath.c_str(), "READ");
      TChain *data=new TChain("data");
      data->Add("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-xscintT-sipm-sorted-TG-48-hasGoodPosition-check-6mm-dyoverflow-unconditioned-corrections-from-amelia-neutron.root");
      // data[0] = static_cast<TTree*>(files[0]->Get("data"));

 


      std::string histogramTitle = canvasname;
      std::string fullTitle = histogramTitle + ";" + config.xTitle + ";" + config.yTitle;
if (config.is1D) {
                TH1D* hist = new TH1D(histogramTitle.c_str(), fullTitle.c_str(), config.nBinsX, config.xLow, config.xHigh);
                data->Draw((config.drawCommand + histogramTitle).c_str(), config.condition.c_str());
		output->cd();
		hist->Write();
              
            } else {
                TH2D* hist = new TH2D(histogramTitle.c_str(), fullTitle.c_str(), config.nBinsX, config.xLow, config.xHigh, config.nBinsY, config.yLow, config.yHigh);
                data->Draw((config.drawCommand + histogramTitle).c_str(), config.condition.c_str(), "colz");
		output->cd();
                hist->Write();
            }

        
     
      canvas->Update();
  }
  output->Close();
}
