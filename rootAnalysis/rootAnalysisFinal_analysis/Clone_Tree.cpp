#include <ROOT/RDataFrame.hxx> // Include RDataFrame
#include <array>

#include "TChain.h"
#include <TSystem.h>  // This makes 'gSystem' available
#include <vector>
// #include "LinkDef.h"
#include "/projects/e21062/aad/e21062B/rootAnalysisFinal/include/TPID.h"
#include "/projects/e21062/aad/e21062B/rootAnalysisFinal/include/TClover.h"
// #ifdef __CLING__
// #pragma link C++ class std::vector<TPID>+;
// #pragma link C++ class TPID+;
// #endif



std::vector<std::string> GenerateBranchNames(const std::string& base_name, int num_elements) {
    std::vector<std::string> branch_names;
    branch_names.reserve(num_elements);
    for (int i = 0; i < num_elements; ++i) {
        branch_names.push_back(base_name + "[" + std::to_string(i) + "]");  // Concatenate to form "clover.ecal[0]", etc.
    }
    return branch_names;
}




int main(){
   // gSystem->Load("/projects/e21062/aad/e21062B/rootAnalysisFinal/libTParameters.so");
 //  // gSystem->Load("libDict.so");
 // gInterpreter->AddIncludePath("/projects/e21062/aad/e21062B/rootAnalysisFinal/include/");
 // gInterpreter->AddIncludePath("/projects/e21062/aad/e21062B/rootAnalysisFinal/");
 //    gInterpreter->AddIncludePath("/projects/e21062/hlc/ddasfitclasses/");

  // TChain* data= new TChain("data");
  // data->Add("/mnt/analysis/e21062/aad/e21062B/sortedNew/run-*.root");
 

    // Directory to search for files
    const char *dir = "/mnt/analysis/e21062/aad/e21062B/sortedNew/";

    // Open the directory and iterate over the files
    void *dirp = gSystem->OpenDirectory(dir);
    if (!dirp) {
        std::cerr << "Error: Cannot open directory: " << dir << std::endl;
        return 0;
    }

    const char *entry;
    int nfiles = 0;
    while ((entry = gSystem->GetDirEntry(dirp)) != nullptr) {
        std::string filename(entry);
        // Check if the file has the .root extension
        if (filename.find("1281-sorted.root") != std::string::npos) {
            std::string filepath = std::string(dir) + filename;
            std::cout << "Adding file: " << filepath << std::endl;
	    TChain *data = new TChain("data");
            data->Add(filepath.c_str());


// Create an RDataFrame to read from the tree
 

    // // Define a lambda function to cast the first element to double and filter it
    // auto filterByFirstElement = [](const std::vector<double>& dytime) {
    //     if (dytime.size()==1) {
    //         double firstElement = static_cast<double>(dytime[0]);  // Cast the first element
    //         return firstElement > 10.0;  // Example condition: Keep only if first element > 10.0
    //     }
    //     return false;  // Discard empty arrays
    // };

    // // Apply the filter function to cast and filter by the first element
    // auto df_filtered = df.Filter({"corr.isimplant==1 || corr.isdecay==1"});
	    //  data->GetBranch("implantlist.to")->SetNameTitle("implantlist_tof", "implantlist_tof");
	    // data->GetBranch("clover.cfdfailbit[52]")->SetNameTitle("clover_cfdfailbit", "clover_cfdfailbit");
	    // data->GetBranch("clover.timecal[52]")->SetNameTitle("clover_timecal", "clover_timecal");
	    
 // 		 double clover_ecal[52],clover_timecal[52];
 // 		 int  clover_cfdfailbit[52];
 // data->SetBranchAddress("clover_ecal", &clover_ecal);
 // data->SetBranchAddress("clover_timecal", &clover_timecal);
 // data->SetBranchAddress("clover_cfdfailbit", &clover_cfdfailbit);
 ROOT::RDataFrame df(*data);
 

// auto df_mod = df.Define("clover_cfdfailbit_arr", [](const int cfdfailbit[52]) {
//     int cfdfailbit_arr[52];  // Define a C-style array of 52 integers
//     for (int i = 0; i < 52; ++i) {
//         cfdfailbit_arr[i] = cfdfailbit[i];  // Copy values into the array
//     }
//     return std::vector<int>(cfdfailbit_arr, cfdfailbit_arr + 52);  // Return a vector for ROOT
// }, {"clover_cfdfailbit"});

//  // Define the "clover_ecal_arr" column using std::array of 52 doubles
// auto df_mod = df.Define("clover_ecal_arr", [](const std::array<double, 52>& ecal) {
//     std::array<double, 52> ecal_arr;  // Define a std::array of 52 doubles
//     for (int i = 0; i < 52; ++i) {
//         ecal_arr[i] = ecal[i];  // Copy values into the array
//     }
//     return ecal_arr;  // Return the array
// }, {"clover_ecal"});

// // Define the "clover_cfdfailbit_arr" column using std::array of 52 doubles
// df_mod = df_mod.Define("clover_cfdfailbit_arr", [](const std::array<Int_t, 52>& cfdfailbit) {
//     std::array<Int_t, 52> cfdfailbit_arr;  // Define a std::array of 52 doubles
//     for (int i = 0; i < 52; ++i) {
//         cfdfailbit_arr[i] = cfdfailbit[i];  // Copy values into the array
//     }
//     return cfdfailbit_arr;  // Return the array
// }, {"clover_cfdfailbit"});

// // Define the "clover_timecal_arr" column using std::array of 52 doubles
// auto df_mod = df.Define("implantlist_tof1", [](const std::vector<double>& tof) {
// 					     std::vector<double>null{0};
//      if (tof.size()>1) {
            
//        return tof;
//         }
//      else
//         return null;  // Discard empty arrays
// }, {"implantlist_tof"});




 
    df.Snapshot("trimmed_data", Form("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/filtered_files/%s", filename.c_str()), 
		{"implantlist", "corr.dxpos", "corr.dypos", "corr.dtime", 
	       "corr.isdecay", "corr.itof", "corr.ide2", "corr.isimplant", "corr.hasclover", "corr.gtof", "corr.gde2", "corr.gitime",
			"pspmtlow1.dytime", "pspmthigh1.dytime", "pspmtlow1.dyenergy", 
			"pspmthigh1.dyenergy", "pspmtlow1.dyhit", "pspmthigh1.dyhit", 
	       "pspmtlow1.dycfdfailbit", "pspmthigh1.dycfdfailbit","clover.cfdfailbit[52]", "clover.ecal[52]", "clover.timecal[52]"});

    delete data; 


	    
            nfiles++;
        }
    }

    // Close the directory
    gSystem->FreeDirectory(dirp);

  

  
     
    





    return 0;
}

