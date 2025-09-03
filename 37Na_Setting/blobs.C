{
  TFile* output= new TFile("iongates.root","recreate");
  TCutG* iongates[4][8];
  for ( int i:{7,5,4,3,2}){
    TFile* input=new TFile(Form("3%dNa.root",i),"READ");
    iongates[3][i]=(TCutG*)input->Get("CUTG");
    iongates[3][i]->SetName(Form("iongates_3%dNa",i));
    iongates[3][i]->SetTitle(Form("iongates_3%dNa",i));
    output->cd();
    iongates[3][i]->Write();
  }
}
