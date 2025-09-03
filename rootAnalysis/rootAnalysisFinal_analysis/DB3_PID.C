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

// Define the configurations
std::vector<AnalysisConfig> configs = {
    {"PID_Implant_UP_Gamma", "PID_Implant_UP_Gamma", "pin02.energy:(sipm.time-DB3PPACUAnT.time)>>", "corr.isforward==1 && xscintT.energy>10 && pspmtlow1.dyenergy>10", 1000, -1010, -910, 1400, 0, 1400, "tof", "de2", false},
    {"PID_Implant_Down_Gamma", "PID_Implant_Down_Gamma", "pin02.energy:(sipm.time-DB3PPACDAnT.time)>>", "corr.isforward==1 && xscintT.energy>10 && pspmtlow1.dyenergy>10", 1000, -1000, -900, 1400, 0, 1400, "tof", "de2", false},
    {"PID_Implant_neutron", "PID_Implant_neutron", "pin02.energy:(sipm.time-DB3PPACULT.time)>>", "corr.isforward==1 && xscintT.energy>10 && pspmtlow1.dyenergy>10", 1000, -1500, -1400, 1400, 0, 1400, "tof", "de2", false},

    {"PID_UP_Gamma", "PID_UP_Gamma", "pin02.energy:(sipm.time-DB3PPACUAnT.time)>>", "corr.isforward==1 ", 1000, -1010, -910, 1400, 0, 1400, "tof", "de2", false},
    {"PID_Down_Gamma", "PID_Down_Gamma", "pin02.energy:(sipm.time-DB3PPACDAnT.time)>>", "corr.isforward==1 ", 1000, -1000, -900, 1400, 0, 1400, "tof", "de2", false},
    {"PID_neutron", "PID_neutron", "pin02.energy:(sipm.time-DB3PPACULT.time)>>", "corr.isforward==1", 1000, -1500, -1400, 1400, 0, 1400, "tof", "de2", false}
};

// Define the gating ranges based on the type of drawCommand
std::map<std::string, std::vector<std::pair<double, double>>> gatingRanges = {
    {"sipm.time-DB3PPACDAnT.time", {{-1, 0}, {0, 10}, {1050, 1500}, {2900, 3250}, {4500, 5000}, {6000, 7000}, {7600, 8800}}},
    {"sipm.time-DB3PPACUAnT.time", {{-1, 0}, {0, 10}, {1050, 1500}, {2950, 3250}, {4550, 5000}, {6300, 6600}}},
    {"sipm.time-DB3PPACULT.time", {{-1, 0}, {0, 10}, {550, 950}, {1650, 1850}, {2600, 2900}, {3700, 3850}}}
};

void DB3_PID() {
    // Create output file
    TFile* output = new TFile("DB3_Gated_PID.root", "recreate");

    int countcanvas = 0;
    for (const auto& config : configs) {
        std::string baseCanvasName = config.canvasName;
        TCanvas* canvas = new TCanvas(baseCanvasName.c_str(), baseCanvasName.c_str(), 2000, 1200);

        // Determine which drawCommand is being used and select the appropriate ranges
        std::vector<std::pair<double, double>> energyRanges;
        if (config.drawCommand.find("sipm.time-DB3PPACDAnT.time") != std::string::npos) {
            energyRanges = gatingRanges["sipm.time-DB3PPACDAnT.time"];
        } else if (config.drawCommand.find("sipm.time-DB3PPACUAnT.time") != std::string::npos) {
            energyRanges = gatingRanges["sipm.time-DB3PPACUAnT.time"];
        } else if (config.drawCommand.find("sipm.time-DB3PPACULT.time") != std::string::npos) {
            energyRanges = gatingRanges["sipm.time-DB3PPACULT.time"];
        }

        // Divide the canvas for energy range histograms + 1 for "no gate" histogram
        canvas->Divide(energyRanges.size() + 1);

        // Create TChain and add data
        TChain* data = new TChain("data");
        data->Add("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-xscintT-sipm-sorted-TG-48-hasGoodPosition-check-6mm-dyoverflow-unconditioned-corrections-from-amelia-neutron.root");

        // Loop over each energy range to create histograms
        for (std::size_t i = 0; i < energyRanges.size(); ++i) {
            double low = energyRanges[i].first;
            double high = energyRanges[i].second;
            
            // Determine which energy variable to use based on drawCommand
            std::string energyVariable;
            if (config.drawCommand.find("DB3PPACDAnT.time") != std::string::npos) {
                energyVariable = "DB3PPACDAnT.energy";
            } else if (config.drawCommand.find("DB3PPACUAnT.time") != std::string::npos) {
                energyVariable = "DB3PPACUAnT.energy";
            } else if (config.drawCommand.find("DB3PPACULT.time") != std::string::npos) {
                energyVariable = "DB3PPACULT.energy";
            }
            
            // Define the energy gate condition
            std::string energyCondition = energyVariable + " > " + std::to_string(low) + " && " + energyVariable + " < " + std::to_string(high);
            // Combine the base condition with the energy gate condition
            std::string fullCondition = "(" + config.condition + ") && (" + energyCondition + ")";
            
            // Define unique histogram title and canvas name
            std::string histogramTitle = baseCanvasName + "_range" + std::to_string(i + 1) + "_" + std::to_string(low) + "to" + std::to_string(high);
            std::string fullTitle = histogramTitle + ";" + config.xTitle + ";" + config.yTitle;
            
            // Select the appropriate type of histogram
            if (config.is1D) {
                TH1D* hist = new TH1D(histogramTitle.c_str(), fullTitle.c_str(), config.nBinsX, config.xLow, config.xHigh);
                data->Draw((config.drawCommand + histogramTitle).c_str(), fullCondition.c_str());
                output->cd();
                hist->Write();
            } else {
                TH2D* hist = new TH2D(histogramTitle.c_str(), fullTitle.c_str(), config.nBinsX, config.xLow, config.xHigh, config.nBinsY, config.yLow, config.yHigh);
                data->Draw((config.drawCommand + histogramTitle).c_str(), fullCondition.c_str(), "colz");
                output->cd();
                hist->Write();
            }
            
            // Update canvas
            canvas->cd(i + 1);
            canvas->Update();
        }

        // Create and draw histogram with no gate
        std::string noGateTitle = baseCanvasName + "_noGate";
        std::string noGateFullTitle = noGateTitle + ";" + config.xTitle + ";" + config.yTitle;

        if (config.is1D) {
            TH1D* histNoGate = new TH1D(noGateTitle.c_str(), noGateFullTitle.c_str(), config.nBinsX, config.xLow, config.xHigh);
            data->Draw((config.drawCommand + noGateTitle).c_str(), config.condition.c_str());
            output->cd();
            histNoGate->Write();
        } else {
            TH2D* histNoGate = new TH2D(noGateTitle.c_str(), noGateFullTitle.c_str(), config.nBinsX, config.xLow, config.xHigh, config.nBinsY, config.yLow, config.yHigh);
            data->Draw((config.drawCommand + noGateTitle).c_str(), config.condition.c_str(), "colz");
            output->cd();
            histNoGate->Write();
        }

        // Update canvas for no-gate histogram
        canvas->cd(energyRanges.size() + 1);
        canvas->Update();
    }

    output->Close();
}
