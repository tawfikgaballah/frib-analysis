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
				       //  {"PID_Implant", "PID_Implant", "corr.ide2:corr.itof>>", "corr.isforward==1 &&implant", 500, -1000, -950, 1400, 0, 1400,"itof","ide2", false},
				       // {"PID_Implant_hasxscintT", "PID_Implant_hasxsscintT", "corr.ide2:corr.itof>>", "corr.isforward==1 && xscintT.hit==1 &&implant ", 500, -1000, -950, 1400, 0, 1400,"itof","ide2", false},
				       // {"PID_Implant_!hasxscintT", "PID_Implant_!hasxsscintT", "corr.ide2:corr.itof>>", "corr.isforward==1 && xscintT.hit!=1 &&implant ", 500, -1000, -950, 1400, 0, 1400,"itof","ide2", false},
					//   {"PID_Decay", "PID_Decay", "implantlist.de2:implantlist.tof>>", "corr.isforward==1 &&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=6 && decay", 500, -1000, -950, 1400, 0, 1400,"implantlist.tof","implantlist.de2", false}
				       // {"Position_2D_HG", "Position_2D_HG", "pspmthigh1.ypos_highgain:pspmthigh1.xpos_highgain>>", "corr.isforward==1&&corr.radius<=10", 600, -10, 50, 600, -10, 50,"xpos_HG","ypos_HG", false },
				       // {"Position_2D_LG", "Position_2D_LG", "pspmtlow1.ypos:pspmtlow1.xpos>>", "corr.isforward==1 &&corr.radius<=10", 600, -10, 50, 600, -10, 50,"xpos_LG","ypos_LG", false},
				       // {"Beta_Energy_Vs_DTime", "Beta_Energy_Vs_DTimr", "pspmthigh1.dyecal:(corr.decaytime)>>", "corr.isdecay==1 &&corr.radius<=10", 200, -100, 100, 10000, 0, 100000,"decay_time", "pspmthigh1.dyecal",false},
				       // {"BetaEnergy_Vs_Radius", "BetaEnergy_Vs_Radius", "pspmthigh1.dyecal:sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))>>", "pspmthigh1.dyecal>0 && corr.isforward==1 &&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=10", 100, 0, 10, 7000, 0, 70000,"decay_radius", "pspmthigh1.dyecal",false},
				       // {"Beta_Energy_Vs_Scint_Energy", "Beta_Energy_Vs_Scint_Energy", "pspmthigh1.dyecal:sipm.energy>>", "corr.isforward==1 && pspmthigh1.dyecal>0 && sipm.energy>0 &&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=10", 1600, 0, 16000, 7000, 0, 70000,"sipm.energy","pspmthigh1.dyecal", false},
				       // {"pspmtlow_Vs_Scint_Energy", "pspmtlow_Vs_Scint_Energy", "pspmtlow1.dyecal:sipm.energy>>", "corr.isforward==1 && pspmtlow1.dyecal>0 && sipm.energy>0&&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=10", 1600, 0, 16000, 7000, 0, 70000,"sipm.energy","pspmtlow1.dyecal", false},
				      // {"radius_Vs_decaytime", "radius_Vs_decaytime", "sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2)):(corr.decaytime)>>", "corr.flag==32 && corr.isdecay==1 &&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=10", 200,-100,100, 100,0,10,"decaytime [ms]","radius [mm]", false},
				       // {"radius_Vs_#beta_energy", "radius_Vs_#beta_energy", "(sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))):(pspmthigh1.dyecal)>>", "corr.isforward==1 && pspmthigh1.dyecal>0 &&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=10 ",7000,0,70000,100,0,10,"#beta_energy_highgain [ms]","radius [mm]", false}
				       {"Decaytime", "Decaytime", "(corr.dtime-implantlist.time)>>", "D33Na &&sqrt(pow((implantlist.xpos-corr.dxpos),2)+pow((implantlist.ypos-corr.dypos),2))<=6",200,-100,100,0,0,0,"decaytime [ms]","", true}
				       
};
void beta_correlation() {


 TCutG *implant = new TCutG("implant",7);
   implant->SetVarX("corr.itof");
   implant->SetVarY("corr.ide2");
   implant->SetTitle("Graph");
   implant->SetFillStyle(1000);
   implant->SetPoint(0,-964.184,1066.9);
   implant->SetPoint(1,-978.328,927.733);
   implant->SetPoint(2,-993.928,134.283);
   implant->SetPoint(3,-972.296,49.3349);
   implant->SetPoint(4,-951.496,181.275);
   implant->SetPoint(5,-964.08,1068.71);
   implant->SetPoint(6,-964.184,1066.9);

 TCutG *decay = new TCutG("decay",9);
   decay->SetVarX("implantlist.tof");
   decay->SetVarY("implantlist.de2");
   decay->SetTitle("Graph");
   decay->SetFillStyle(1000);
   decay->SetPoint(0,-964.08,1065.1);
   decay->SetPoint(1,-975,951.229);
   decay->SetPoint(2,-995.384,125.246);
   decay->SetPoint(3,-973.96,67.4089);
   decay->SetPoint(4,-960.128,96.3273);
   decay->SetPoint(5,-951.808,188.505);
   decay->SetPoint(6,-963.976,1066.9);
   decay->SetPoint(7,-964.08,1065.1);
   decay->SetPoint(8,-964.08,1065.1);
   TCutG *D33Na = new TCutG("D33Na",10);
   D33Na->SetVarX("implantlist.tof");
   D33Na->SetVarY("implantlist.de2");
   D33Na->SetTitle("Graph");
   D33Na->SetFillStyle(1000);
 D33Na->SetPoint(0,-971.677,621.983);
   D33Na->SetPoint(1,-970.463,599.445);
   D33Na->SetPoint(2,-970.271,564.771);
   D33Na->SetPoint(3,-972.252,547.434);
   D33Na->SetPoint(4,-973.275,556.103);
   D33Na->SetPoint(5,-973.978,578.641);
   D33Na->SetPoint(6,-973.786,601.179);
   D33Na->SetPoint(7,-971.741,621.983);
   D33Na->SetPoint(8,-971.677,620.25);
   D33Na->SetPoint(9,-971.677,621.983);
TCutG *I33Na = new TCutG("I33Na",9);
   I33Na->SetVarX("corr.itof");
   I33Na->SetVarY("corr.ide2");
   I33Na->SetTitle("Graph1");
   I33Na->SetFillStyle(1000);
I33Na->SetPoint(0,-971.869,627.326);
   I33Na->SetPoint(1,-970.718,606.561);
   I33Na->SetPoint(2,-970.143,568.494);
   I33Na->SetPoint(3,-971.997,549.46);
   I33Na->SetPoint(4,-972.763,545.999);
   I33Na->SetPoint(5,-973.978,573.685);
   I33Na->SetPoint(6,-973.978,590.988);
   I33Na->SetPoint(7,-972.06,629.056);
   I33Na->SetPoint(8,-971.869,627.326);



   TCutG *pid33Na = new TCutG("pid33Na",10);
   pid33Na->SetVarX("pid.tof");
   pid33Na->SetVarY("pid.de2");
   pid33Na->SetTitle("Graph");
   pid33Na->SetFillColor(1);
   pid33Na->SetPoint(0,-971.356,625.714);
   pid33Na->SetPoint(1,-970.252,597.219);
   pid33Na->SetPoint(2,-970.289,570.4);
   pid33Na->SetPoint(3,-971.577,540.229);
   pid33Na->SetPoint(4,-972.571,538.553);
   pid33Na->SetPoint(5,-973.785,572.076);
   pid33Na->SetPoint(6,-973.749,598.895);
   pid33Na->SetPoint(7,-972.092,627.39);
   pid33Na->SetPoint(8,-971.062,625.714);
   pid33Na->SetPoint(9,-971.356,625.714);
  // Define the conditions for the various analyses
   std::vector<std::string> beta_gate_conditions = {"PIN", "xscintT"};
  std::vector<std::string> tofv_conditions = {"sipm"};

  // Calculate total number of combinations
  int totalCombinations = beta_gate_conditions.size() * tofv_conditions.size();
  std::vector<TFile*> files(totalCombinations);
  std::vector<TTree*> data(totalCombinations);
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



  //////////////USE IF YOU WANT TO DRAW STUFF ON CANVAS//////////////////////////
  int countcanvas=0; 
  for (const auto& config : configs) {
    std::string canvasname= config.canvasName;
    TCanvas* canvas =new TCanvas(canvasname.c_str(), canvasname.c_str(), 2000, 1200);
    canvas->Divide(beta_gate_conditions.size());
      
      
    for (int index = 0; index < totalCombinations; index++) {
      canvas->cd(countcanvas+1);
      std::string beta_gate = beta_gate_conditions[index % beta_gate_conditions.size()];
      std::string tofv = tofv_conditions[index / beta_gate_conditions.size()];
      std::string baseName = "anti_gate_on" + beta_gate;
      std::string filePath = "/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-" + beta_gate + "-" + tofv + "-sorted-TG-48-hasGoodPosition-check-10mm-dyoverflow.root";
        
      files[index] = new TFile(filePath.c_str(), "READ");
      data[index] = static_cast<TTree*>(files[index]->Get("data"));

 


      std::string histogramTitle = canvasname+"_"+baseName;
      std::string fullTitle = histogramTitle + ";" + config.xTitle + ";" + config.yTitle;
if (config.is1D) {
                TH1D* hist = new TH1D(histogramTitle.c_str(), fullTitle.c_str(), config.nBinsX, config.xLow, config.xHigh);
                data[index]->Draw((config.drawCommand + histogramTitle).c_str(), config.condition.c_str());
              
            } else {
                TH2D* hist = new TH2D(histogramTitle.c_str(), fullTitle.c_str(), config.nBinsX, config.xLow, config.xHigh, config.nBinsY, config.yLow, config.yHigh);
                data[index]->Draw((config.drawCommand + histogramTitle).c_str(), config.condition.c_str(), "colz");
                
            }

        
     
      canvas->Update();
      // gPad->SetLogz();
      std::string save= canvasname+".tiff";
      canvas->SaveAs(save.c_str());
      countcanvas+=1;
    }
    countcanvas=0;
  }
  ////////////////////////////////////////////////////////

}
