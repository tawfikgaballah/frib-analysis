#include <string>
#include <fstream>

void test(){
	time_t start, stop;
	start = time(0);

	TFile *out = new TFile("/projects/e21062/aad/rootanalysis/root_files/all2Ds.root", "RECREATE");

	string name[26] = {"i21O", "i22O", "i23O", "i24Fl", "i24O", "i25Fl", "i26Fl", "i27Fl", "i27Ne", "i28Ne", "i29Ne", "i30Na", "i30Ne", "i31Na", "i33Mg", "i33Na", "i34Mg", "i35Mg", "i36Al", "i36Mg", "i37Al", "i38Al", "i39Al", "i40Si", "i41Si", "i42Si"};

	TH2F *h2[26];
	TFile *f[26];

	for(int i = 0; i < 3; i++){

		stringstream inname;
		inname << "/projects/e21062/aad/rootanalysis/hist_interactive/" << name[i] << "_2D.root";
		cout << "Adding file " << inname.str() << endl;
		f[i] = new TFile((inname.str()).c_str(), "READ");

		if((f[i])->IsOpen()){
			h2[i] = (TH2F*)(f[i])->Get("h");
			if(h2[i]){
				h2[i]->SetTitle(Form("Clover energy versus time since implant, %s gate", (name[i]).c_str()));
				h2[i]->Clone((name[i]).c_str());
			}
			else{
				cout << "Error: Histogram missing" << endl;
			}
			//f->Close();		
		}	
		else{
			cout << "Error: File not open" << endl;
		}

	}
	
	out->Write();
	out->Close();
	
	stop = time(0);
	cout << "Done processing after " << difftime(stop, start)/60 << " minutes." << endl;
}
