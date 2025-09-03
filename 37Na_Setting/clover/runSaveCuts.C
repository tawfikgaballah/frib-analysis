#include <iostream>
#include <string>
#include <vector>

// Function to extract file name without extension
std::string getBaseName(const std::string& filePath) {
    size_t startPos = filePath.find_last_of("/\\") + 1; // Handle file path separators
    size_t endPos = filePath.find_last_of(".C");
    return filePath.substr(startPos, endPos - startPos);
}

void saveCuts(const std::vector<std::string>& files, const std::string& outputFile) {
    TFile *fout = new TFile(outputFile.c_str(), "RECREATE");

    for (const auto& file : files) {
        std::string baseName = getBaseName(file);

        gROOT->Macro(file.c_str());

        TList* list = (TList*)gROOT->GetListOfSpecials();
        TIter next(list);
        TObject* obj = nullptr;

        while ((obj = next())) {
            if (TCutG* cut = dynamic_cast<TCutG*>(obj)) {
                std::string cutName = baseName; // Combine macro base name with original cut name
                cut->SetName(cutName.c_str());
                cut->Write(); // Write the TCutG object into the output file
		delete cut;
            }
        }
    }

    fout->Close();
    std::cout << "TCutG objects have been saved to " << outputFile << std::endl;
}

void runSaveCuts() {
    // List of the .C files containing TCutG objects
  std::vector<std::string> files = {"./I37Na.C", "./I35Na.C", "./I34Na.C","./I33Na.C","./I32Na.C"}; // Add your files here
    saveCuts(files, "iongates_implant_CorrSorted37Na-Win3.root");
}
