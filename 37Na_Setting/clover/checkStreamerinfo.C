#include <TFile.h>
#include <TClass.h>
#include <iostream>

void checkStreamerInfo(const char* filename) {
    TFile* file = TFile::Open(filename);
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    TClass* cl = TClass::GetClass("TPID");
    if (!cl) {
        std::cerr << "Class TPID not found." << std::endl;
        return;
    }

    TStreamerInfo* info = (TStreamerInfo*)cl->GetStreamerInfo();
    std::cout << "Checksum for TPID in " << filename << ": " << info->GetCheckSum() << std::endl;

    file->Close();
    delete file;
}

void checkStreamerinfo() {
    checkStreamerInfo("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resorted37Na/run-1421-sorted.root");
    return 0;
}
