  // BEGIN ANALYSIS
  //ROOT::EnableImplicitMT(10); // turn on multithreading
  //ROOT::EnableThreadSafety();
#include <iostream>
#include <vector>
#include <string>

// ROOT core and I/O
#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"

// Data frame
#include "ROOT/RDataFrame.hxx"

// Histograms
#include "TH1F.h"
#include "TH2F.h"

// Graphical cut
#include "TCutG.h"
#include <ROOT/RDF/RInterface.hxx>
#include "/projects/e21062/Offline-Analysis/rootAnalysis/include/TPID.h"
// // Enable multithreading in ROOT
#include "ROOT/EnableImplicitMT.h"

{
  cout << "Starting RDataFrame Analysis" << endl;

  // Create the data from with a root tree name "data" which is consistent 
  // across a vector of files called "files". Alternatively, if one had 
  // a tchain already added together, one could do ROOT::RDataFrame df(mychain).
  // "files" could also be a single root file.
  // ROOT::EnableImplicitMT(10);
  ROOT::RDataFrame df("data","/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/resorted37Na/run-1281-sorted.root");

  // Print columns' names
  auto colNames = df.GetColumnNames();
  auto report = df.Report();


  for (auto &&colName : colNames) std::cout << colName << " " << df.GetColumnType(colName) << std::endl;



  // Make histograms (df.Fill returns some histogram inside of a RDataFrame wrapper 
  // (it is not of type TH1 or TH2! but in some cases acts as though it is!)
  // You can see something like the TH1F constructor is taken as an input for 
  // the Fill() function.
  // When Fill is called the first time it starts a loop over all events. If
  // multiple fill functions are called, the first one still initiates the loop
  // but the same loop will do all the other filling in the background.
  auto hcorr_itof = df.Fill<double>(TH1F("hcorr_itof","hcorr_itof",1000,-1020,-920), {"corr.itof"});
  auto hcorr_ide1 = df.Fill<double>(TH1F("hcorr_ide1","hcorr_ide1",1000,0,2000), {"corr.ide1"});
  auto hcorr_ide2 = df.Fill<double>(TH1F("hcorr_ide2","hcorr_ide2",1000,0,2000), {"corr.ide2"});
  // // Make a 2D histogram with 1D cuts using Filter()
  // auto hcorr_itof_ide1 = df.Filter("rootout.corr.itof<-975 && rootout.corr.itof>-980").Fill<double,double>(TH2F("hcorr_itof_ide1","hcorr_itof_ide1",1000,-1020,-920,1000,0,2000), {"rootout.corr.itof","rootout.corr.ide1"});
  
  // // Here we will try to make a graphical cut and include it into Filter(). To
  // // do this, we first import the TCutG from our root file. Then we need to make
  // // a Lambda function which will be called in the Filter(). The Filter() 
  // // function is overloaded and one definition allows us to pass in a function
  // // to evaluate, followed by any arguments that function may have. 
  // TFile *gCut_21Ne_File = TFile::Open("cut_21Ne.root");
  // TCutG *gCut_21Ne = (TCutG*)gCut_21Ne_File->Get("CUTG");
  // // Our Lambda function to define the cut, it captures the gCut_21Ne TCutG
  // // and takes arguments x and y. It then evaluates the IsInside function 
  // // and returns the boolean to the Filter
  // auto is21ne = [&gCut_21Ne](double x, double y){return gCut_21Ne->IsInside(x,y);};
  // auto hcorr_itof_ide2 = df.Filter(is21ne,{"rootout.corr.itof","rootout.corr.ide2"}).Fill<double,double>(TH2F("hcorr_itof_ide2","hcorr_itof_ide2",1000,-1020,-920,1000,0,2000), {"rootout.corr.itof","rootout.corr.ide2"});
  // cout<<"end analysis"<<endl;
// After all processing and just before writing output or at the end of your analysis
report->Print();
  // // make the outfile

auto nrows = df.Count();
    std::cout << "Total number of rows to process: " << *nrows << std::endl;

    // Snapshot to trigger the event loop and start processing
    auto result = df.Snapshot("data", "outfile.root");

    // Display progress
    auto cindex = 0;
    auto total = nrows.GetValue();
    df.Foreach([&](const double &) {
        ++cindex;
        if (cindex % (total / 100) == 0) {  // Update progress for every 1% processed
            std::cout << "Progress: " << static_cast<int>(100.0 * cindex / total) << "%\r" << std::flush;
        }
    }, {"itof"});

    std::cout << std::endl << "Analysis complete." << std::endl;



 auto outputname = Form("outfile.root");
  // cout << "WRITING OUTPUTFILE " << BLUE << outputname << RESET << endl;  
   TFile *outfile = new TFile(outputname,"RECREATE");
  hcorr_itof->Write();
  hcorr_ide1->Write();
  hcorr_ide2->Write();
  // hcorr_itof_ide1->Write();
  // hcorr_itof_ide2->Write();
  outfile->Close();

  // if you need to loop over root files to make run by run outputs, you
  // need to reset your histo's every time
  //hcorr_itof->Reset();
  //hcorr_ide1->Reset();
  //hcorr_ide2->Reset();
  //hcorr_itof_ide1->Reset();
  ////hcorr_itof_ide2->Reset();
  cout<<"done with file"<<endl;
}
