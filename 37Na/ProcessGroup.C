{

  gSystem->Load("/projects/e21062/tg/rootAnalysis/rootAnalysisFinal/libTParameters.so");
    gSystem->Load("/projects/e21062/tg/rootAnalysis/rootAnalysisFinal/include/");
  TChain* data=new TChain("data");
  for(int i=1281; i<1282; i++){
    if (i!=1289 && i!=1332 &&i!=1335){
      data->Add(Form("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-%d-xscintT-sipm-sorted-TG-48-10mm.root",i));
    }
  }

  //   for(int i=1431; i<=1433; i++){
  //     if(i!=1423&& i!=1398){
  //     data->Add(Form("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-%d-xscintT-sipm-sorted-TG-48-10mm.root",i));
  //     }
  // }

 // // Open the directory
 //    void* dir = gSystem->OpenDirectory("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/RSL/rootanalysis-Amelia-Sept2024/forwardCorr/");
 //    const char* file;

 //    // Create a vector to hold the valid run numbers
 //    std::vector<int> runNumbers;

 //    // Iterate over all files in the directory
 //    while ((file = gSystem->GetDirEntry(dir))) {
 //        TString fileName = TString(file);
        
 //        // Check if the file name matches the "run-*-sorted.root" format and extract the run number
 //        if (fileName.BeginsWith("run-") && fileName.EndsWith("-sorted.root")) {
 //            TString runNumberStr = fileName(4, fileName.Length() - 16); // Extract the run number between "run-" and "-sorted.root"
 //            int runNumber = runNumberStr.Atoi();
            
 //            // Exclude run 1398
 //            if (runNumber != 1398) {
 //                runNumbers.push_back(runNumber); // Add valid run number to the vector
 //            }
 //        }
 //    }

 //    // Sort the run numbers in ascending order
 //    std::sort(runNumbers.begin(), runNumbers.end());

 //    // Add the files to the TChain in the sorted order
 //    for (int runNumber : runNumbers) {
 //        TString filePath = TString::Format("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/RSL/rootanalysis-Amelia-Sept2024/forwardCorr/run-%d-sorted.root", runNumber);
        
 //        // Add the file to the TChain
 //        data->Add(filePath);

 //        // Print the added file path
 //        std::cout << "Added file: " << filePath.Data() << std::endl;
 //    }

 //    // Close the directory
 //    gSystem->FreeDirectory(dir);


  // TProof *proof = TProof::Open("workers=1");
  //  data->SetProof();
   data->Process("e21062_selector_basic.C+");
    //data->Process("e21062_selector_basic_am.C");
  // data->SetProof(0);
  // gProof->GetQueryResult()->Print(); 
}
