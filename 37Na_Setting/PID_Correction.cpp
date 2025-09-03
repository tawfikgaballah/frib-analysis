#include "PID_Correction.h"

void fill_histograms_calibrated(TTree* data_cal_local, TTree* data, int run,std::map<int, std::vector<std::pair<double, double>>> dataMap){



  // for (int i = 0; i < 16; ++i) {
  //      amplitude_cal[i] = 0; // Assuming 0 is a suitable "reset" value.
  //  }
   
  TTreeReader reader1(data);
  TTreeReaderValue<std::vector<TPID>> implantlist = {reader1,"implantlist"}; 
  
  // reader1.SetEntry(0);
  int count=0;
  long int nEntries= data->GetEntries();
  double correction[2];
  if (dataMap.find(run) != dataMap.end() && !dataMap[run].empty()) {
    // Initialize the array with the first pair from the vector
    correction[0] = dataMap[run][0].first;
    correction[1] = dataMap[run][0].second;
    std::cout << "Correction: [" << correction[0] << ", " << correction[1] << "]" << std::endl;
  } else {
    std::cerr << "Run not found or no data for run." << std::endl;
  }
  while(reader1.Next()){
    // data->GetEntry(i);
    if(implantlist->size()>0){
      TOF= implantlist->at(0).scintScintTOF+correction[0];
     
      DE2=(implantlist->at(0).tof)*correction[1];
      // if(TOF<0){
      // std::cout<<TOF<<",  "<<implantlist->at(0).tof<<", "<<DE2<<", "<<implantlist->at(0).de2<<'\n';
      // }

      
    }
 data_cal_local->Fill();

    TOF=0;
    DE2=0;

    
 
    count++;
    // int oneper = (int)(nEntries * 0.0);
    int twenty = (int)(nEntries * 0.2);
    if( (count % twenty) == 0) {
      cout << "Processing run number: "<<run<< " - percent done " << (int)(count/twenty)*20 << "%"<<endl;
    }
  }

}





void auto_fitter_summed(const char* inputFile, const char* outputFile, int i, std::map<int, std::vector<std::pair<double, double>>> dataMap) {
  // Open the ROOT file
  // TFile *file = new TFile("test_run008_tawfik.root", "READ");

  // if (!file || file->IsZombie()) {
  //   std::cerr << "Error opening file" << std::endl;
  //   return;
  // }
 


  TFile* output=new TFile(outputFile,"RECREATE");
 TTree* data_cal=new TTree("data_cal","calibrated_PID");

     data_cal->SetNotify(0);
    // data_cal->SetDirectory(0);
  data_cal->Branch("DE2", &DE2, "DE2/D");
  data_cal->Branch("TOF", &TOF, "TOF/D");

  
  TFile* file1;
  file1=new TFile(inputFile,"READ");
  if (!file1) {
    std::cerr << "file not found!" << std::endl;
    // break;
  }
  TTree *data = dynamic_cast<TTree*>(file1->Get("data"));
  // Check if the tree exists
  if (!data) {
    std::cerr << "Tree 'clover' not found in the file!" << std::endl;
    file1->Close();
  }


 
    




  fill_histograms_calibrated(data_cal, data, i, dataMap);



  

  
  
  file1->Close();
  output->cd();
  data_cal->Write();
   
  
 
  output->Close();




  
}



int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <inputFile_start> <inputFile_end>" << std::endl;
    return 1;
  }

  int start, end;
  std::istringstream(argv[1]) >> start; // Convert string to int
  std::istringstream(argv[2]) >> end;   // Convert string to int
std::string filePath = "./Book1.csv";

     // Open the file
     std::ifstream file(filePath);

     // Check if file is open
     if (!file.is_open()) {
       std::cerr << "Error opening file!" << std::endl;
       return -1;
     }

     // Prepare the map
     // The key is the first number as double, the value is a vector of pairs of index (int) and the second number (double)
    

     // Read lines from the file
     std::string line;
     while (std::getline(file, line)) {
       std::istringstream s(line);
       std::string field;
       std::vector<std::string> fields;

       // Extract each field from the line
       while (getline(s, field, ',')) {
     	 fields.push_back(field);
       }

       // Convert string fields to appropriate types and add to the map
       if (fields.size() == 3) {
     	 int index = std::stoi(fields[0]);
     	 double firstNumber = std::stod(fields[1]);
     	 double secondNumber = std::stod(fields[2]);
     	 dataMap[index].push_back(std::make_pair(firstNumber, secondNumber));
       }
     }

     // Close the file
     file.close();

     std::vector<int> excludedValues = {1289,1332,1335,1398,1423,1409};
  
 for(int i = start; i <= end; i++){
   if ((std::find(excludedValues.begin(), excludedValues.end(), i) == excludedValues.end())&&(i<1338 ||i>1391)) {
     std::string inputFile;
     std::string outputFile;
     // Use string formatting to create file names
  
     inputFile =Form("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/run-%d-sorted.root", i);
     outputFile = Form("./run%d_PID_Calibration.root", i);



     // //Uncomment this part if you want to send the jobs in parallel
     // // Now prepare a job script for each file 
     //        std::string jobScriptName = "job_" + std::to_string(i) + ".sh";
     //        std::ofstream jobScript(jobScriptName);

     //        jobScript << "#!/bin/bash\n";
     //        jobScript << "#SBATCH --job-name=processing_" << i << "\n";
     //        jobScript << "#SBATCH --output=processing_" << i << "_%j.out\n";
     //        jobScript << "#SBATCH --error=processing_" << i << "_%j.err\n";
     //        jobScript << "#SBATCH --time=01:00:00\n";
     //        // jobScript << "#SBATCH --partition=msstate\n";
     //        jobScript << "#SBATCH --nodes=1\n";
     //        jobScript << "#SBATCH --ntasks-per-node=1\n";
     //        // Add other SBATCH directives as needed

     //        jobScript << "module load your_module\n"; // If you need to load specific modules
     //        jobScript << "./auto_fitter_summed " << inputFile << " " << outputFile << "\n";

     //        jobScript.close();

     //        // Submit the job script
     //        std::string command = "sbatch " + jobScriptName;
     //        system(command.c_str());


     









    

     //Comment out this part if you want to send the jobs in parallel	
     try {
       auto_fitter_summed(inputFile.c_str(), outputFile.c_str(),i, dataMap);
       std::cout << "Processed " << inputFile << " successfully." << std::endl;
     } catch (const std::exception& e) {
       std::cerr << "An error occurred processing " << inputFile << ": " << e.what() << std::endl;
       // Decide how to handle the error; you could continue or return an error code.
       continue;
     }
     
   }
 }
  return 0;
}
