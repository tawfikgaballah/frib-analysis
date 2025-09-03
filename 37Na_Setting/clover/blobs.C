#include <map>
#include <tuple>
#include <string>
#include <TFile.h>
#include <TCutG.h>
#include <TString.h>

// Define the map with tuples as keys
std::map<std::tuple<int, int, std::string>, std::string> nuclei = {
    {{2, 9, "Ne"}, "29Ne"},
    {{2, 9, "F"}, "29F"},
    {{2, 7, "F"}, "27F"},
    {{2, 6, "F"}, "26F"},
    {{4, 1, "Al"}, "41Al"},
    {{4, 0, "Al"}, "40Al"},
    {{3, 9, "Al"}, "39Al"}
};

void blobs() {
  TFile* output= new TFile("iongates_decay_CorrSorted37Na-Win3.root","update");
  TCutG* iongates;
  for (const auto& entry : nuclei) {
    int i = std::get<0>(entry.first);
    int j = std::get<1>(entry.first);
    std::string nucl = std::get<2>(entry.first);
    const char* nucl_name = entry.second.c_str();
    // File operations and object manipulations
    TFile* input = new TFile(Form("D%d%d%s.root", i, j, nucl.c_str()), "READ");
    if (input->IsOpen()) {
      iongates = (TCutG*)input->Get("CUTG");
      if (iongates) {
	iongates->SetName(Form("iongates_%d%d%s", i, j, nucl.c_str()));
	iongates->SetTitle(Form("iongates_%d%d%s", i, j, nucl.c_str()));
	output->cd();
	iongates->Write();
      }
      input->Close();
    }
    delete input; // Properly delete the TFile object
  }
}
