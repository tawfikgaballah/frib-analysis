// This script makes a database for
// nuclei that might be involved in the
// fitting of decay time distribution

#include<fstream>
#include<string>
#include<iomanip>
#include<cstdlib>


// needed headers
#include"./Nuclei.hpp"

// global variables

using namespace std;

void MakeNucleiDataBase() {
	// root file to store nuclei info.
	TFile *outroot = new TFile("nuclei_info_database.root",
							   "RECREATE");

	// prepare the root tree
	TTree *outtree = new TTree("nucleiInfo",
							   "Info. of Nuclei");
	std::string nucleusName;
	// set the branch

	outtree->Branch("nucl", "Nucleus", &nucleus, 32000, 99);


	// reader for the text files
	fstream infile;
	for(int z = 9; z <= 18; z++) {
	  for(int n = 10; n <= 30; n++) {
	    // if((z==11 && n==26)||(z==12 &&n==25)){
	      // assign names for this nucleus
	      string X;
	      switch(z) {
	      case 9: X = "F"; break;
	      case 10: X = "Ne"; break;
	      case 11: X = "Na"; break;
	      case 12: X = "Mg"; break;
	      case 13: X = "Al"; break;
	      case 14: X = "Si"; break;
	      case 15: X = "P";  break;
	      case 16: X = "S";  break; 
	      case 17: X = "Cl";  break; 
	      case 18: X = "Ar";  break; 
	      }
	      char nucl[10];
	      sprintf(nucl, "%d%s", z+n, X.c_str());
	      std::stringstream nuclStream;
	      nuclStream << nucl;
	      nuclStream >> nucleusName;

	      // read nuclei info
	      // in this first round, halflife are read in
	      std::vector<double> vecBranches = {};
	      std::vector<double> vecBranchErrors = {}; 


	      //_____1st ROUND_____			
	      // In the first round, read halflife and
	      // branching ratio (abs. value); errors are
	      // stored separately
	      infile.open(Form("z%dn%d.dat", z, n), std::iostream::in);
	      if(!infile.is_open()) {
		printf("CANNOT FIND FILE z%dn%d.dat! (for %d%s)\n",
		       z, n,
		       (z+n),
		       X.c_str());
		continue; 
	      } else {
		double halflife       = 0;
		double branchingRatio = 0;
				
		printf("Now reading %s... \n", nucleusName.c_str()); 
		string line; 
		unsigned int lineCnt = 0;
		while(std::getline(infile, line)) {
		  lineCnt++;
		  std::istringstream iss (line);
		  if(lineCnt > 1) {
		    iss >> branchingRatio;
		    vecBranches.push_back(branchingRatio);
		  } else {
		    iss >> halflife;
		  }					
		}// complete reading text file
				
		// assign read in info.
		nucleus->Reset();
		nucleus->name = nucleusName;
		nucleus->Z = z;
		nucleus->N = n;
		nucleus->halflife = halflife;
				
		nucleus->B0 = vecBranches.at(0);
		nucleus->B1 = vecBranches.at(1);
		nucleus->B2 = vecBranches.at(2);		
	      }
	      infile.close();


	      //_____2nd ROUND_____
	      // in this second round, 
	      // errors of halflife of this nucleus
	      // and errors of branches are read
	      infile.open(Form("z%dn%d.err", z, n), std::iostream::in);
	      if(!infile.is_open()) {
		printf("CANNOT FIND FILE z%dn%d.err! (for %d%s)\n",
		       z, n,
		       (z+n),
		       X.c_str());
		continue; 
	      } else {
		double halflifeError  = 0; 
		double branchingError = 0;
				
		string lineerr; 
		unsigned int lineCnterr = 0;
		while(std::getline(infile, lineerr)) {
		  lineCnterr++;
		  std::istringstream iss (lineerr);
		  if(lineCnterr > 1) {
		    iss >> branchingError;
		    vecBranchErrors.push_back(branchingError); 
		  } else {
		    iss >> halflifeError;
		  }					
		} // complete reading text file
		infile.close(); 
				
		nucleus->halflifeError = halflifeError;
		nucleus->b0            = vecBranchErrors.at(0);
		nucleus->b1            = vecBranchErrors.at(1);
		nucleus->b2            = vecBranchErrors.at(2);
	      }
			
	      outtree->Fill();
	      // }
	  }
	}
	
	// list saved info.
	outtree->Scan("name:Z:N:halflife:halflifeError:B0:B1:B2:b0:b1:b2"); 
	
	
	// finalize output
	outroot->Write();
	outroot->Close(); 
	
	
}
