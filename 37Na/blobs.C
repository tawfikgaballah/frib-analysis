#include <map>
#include <tuple>
#include <string>
#include <TFile.h>
#include <TCutG.h>
#include <TString.h>

// Define the map with tuples as keys
std::map<std::tuple<int, int, std::string>, std::string> nuclei = {
    {{3, 7, "Na"}, "37Na"},
    {{3, 3, "Na"}, "33Na"},
    {{3, 2, "Na"}, "32Na"},
    {{3, 4, "Na"}, "34Na"},
    {{3, 5, "Na"}, "35Na"},
    {{3, 8, "Na"}, "38Na"},
    {{3, 6, "Na"}, "36Na"},
    {{3, 1, "F"}, "31F"},
    {{3, 0, "F"}, "30F"},
    {{3, 2, "F"}, "32F"},
    {{4, 0, "Al"}, "40Al"},
    {{4, 1, "Al"}, "41Al"}
    
};

void blobs() {
  TFile* output= new TFile("iongates_6mm_radius.root","recreate");
  TCutG* iongates;
  for (const auto& entry : nuclei) {
    int i = std::get<0>(entry.first);
    int j = std::get<1>(entry.first);
    std::string nucl = std::get<2>(entry.first);
    const char* nucl_name = entry.second.c_str();
    // File operations and object manipulations
    for(std::string mode: {"Implant", "Decay"}){
      TFile* input = new TFile(Form("%d%d%s_%s.root", i, j, nucl.c_str(), mode.c_str()), "READ");
    if (input->IsOpen()) {
      iongates = (TCutG*)input->Get("CUTG");
      if (iongates) {
	iongates->SetName(Form("%d%d%s_%s", i, j, nucl.c_str(), mode.c_str()));
	iongates->SetTitle(Form("%d%d%s_%s", i, j, nucl.c_str(), mode.c_str()));
	output->cd();
	iongates->Write();
      }
      input->Close();
    }
    delete input; // Properly delete the TFile object
    }
  }
}
