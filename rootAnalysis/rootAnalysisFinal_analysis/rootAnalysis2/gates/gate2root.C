{
	string name = "gates.root";
	TFile *out = new TFile(name.c_str(), "RECREATE");
	int ngates = 34;	

	cout << "Writing " << ngates << " gates to " << name << endl;

	for(int ig = 0; ig <= 26; ig++){
		fstream in;
		in.open(Form("gate%d.C", ig));
		if(!in.is_open()){
			cout << "Error: gate" << ig << ".C not opened" << endl;	
		}
		else{
			cout << "Processing gate" << ig << ".C..." << endl;
			gROOT->ProcessLine(Form(".x gate%d.C", ig));
			cutg->SetLineColor(2);
			cutg->SetLineWidth(2);
			cutg->SetVarX("bdecay->corr.itof");
			cutg->SetVarY("bdecay->corr.ide2");
			string gate = Form("gate%d", ig);
			cutg->Write(gate.c_str());
			in.close();
		}
	}
	
	cout << "ls " << name << ":" << endl;	

	out->ls();
	out->Close();
}

