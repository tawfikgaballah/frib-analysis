{
  TFile *files[4];
  files[0]=new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-sorted-TG-48.root","READ");
  files[1]=new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-sorted-TG-24.root","READ");
  files[2]=new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-sorted-TG-48-uncorrected.root","READ");
  files[3]=new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-sorted-TG-24-uncorrected.root","READ");
 TCutG *cutg = new TCutG("CUTG",9);
   cutg->SetVarX("implantlist[0].tof");
   cutg->SetVarY("implantlist[0].de2");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,-963.846,992.808);
   cutg->SetPoint(1,-954.558,133.905);
   cutg->SetPoint(2,-968.945,91.8606);
   cutg->SetPoint(3,-983.969,61.829);
   cutg->SetPoint(4,-988.431,169.943);
   cutg->SetPoint(5,-973.315,914.726);
   cutg->SetPoint(6,-966.122,1112.93);
   cutg->SetPoint(7,-963.299,962.776);
   cutg->SetPoint(8,-963.846,992.808);
  std::string names[4] = {
    "npspmtutk=48",
    "npspmtutk=24",
    "npspmtutk=48_nocorrection",
    "npspmtutk=24_nocorrection"
};
  TTree* data[4];
     for (int i=0; i<4; i++){
     data[i]=(TTree*)files[i]->Get("data");
 }
  TCanvas* PID_Implant=new TCanvas("PID_Implant","PID_Implant", 800, 500);
  PID_Implant->Divide(2,2);
 for (int i=0; i<4; i++){
   PID_Implant->cd(i+1);
      TString drawCmd = TString::Format("corr.ide2:corr.itof>>\"%s\"(500,-1000,-950,1400,0,1400)",names[i].c_str());
    data[i]->Draw(drawCmd, "", "colz");
    PID_Implant->SetLogz(1);
    PID_Implant->Update();
 }

TCanvas* PID_Decay=new TCanvas("PID_Decay","PID_Decay", 800, 500);
  PID_Decay->Divide(2,2);
 for (int i=0; i<4; i++){
   PID_Decay->cd(i+1);
      TString drawCmd = TString::Format("implantlist[0].de2:implantlist[0].tof>>\" %s\"(500,-1000,-950,1400,0,1400)",names[i].c_str());
    data[i]->Draw(drawCmd, "CUTG", "colz");
    PID_Decay->SetLogz(1);
    PID_Decay->Update();
 }

 
TCanvas* Position_Correction_Low_Gain=new TCanvas("Position_Correction_Low_Gain","Position_Correction_Low_Gain", 800, 500);
  Position_Correction_Low_Gain->Divide(2,2);
 for (int i=0; i<4; i++){
   Position_Correction_Low_Gain->cd(i+1);
      TString drawCmd = TString::Format("pspmtlow1.dyecal:pspmtlow1.xpos>>\"%s \"(480,0,48,10000,0,100000)",names[i].c_str());
    data[i]->Draw(drawCmd, "", "colz");
    Position_Correction_Low_Gain->SetLogz(1);
    Position_Correction_Low_Gain->Update();
 }

 
TCanvas* Position_Correction_High_Gain=new TCanvas("Position_Correction_High_Gain","Position_Correction_High_Gain", 800, 500);
  Position_Correction_High_Gain->Divide(2,2);
 for (int i=0; i<4; i++){
   Position_Correction_High_Gain->cd(i+1);
      TString drawCmd = TString::Format("pspmthigh1.dyecal:pspmthigh1.xpos_highgain>>\"%s   \"(480,0,48,10000,0,100000)",names[i].c_str());
    data[i]->Draw(drawCmd, "", "colz");
    Position_Correction_High_Gain->SetLogz(1);
    Position_Correction_High_Gain->Update();
 }


 TCanvas* Radius=new TCanvas("Radius","Radius", 800, 500);
  Radius->Divide(2,2);
 for (int i=0; i<4; i++){
   Radius->cd(i+1);
      TString drawCmd = TString::Format("(corr.dxpos-implantlist.xpos):(corr.dypos-implantlist.ypos)>>\"%s  \"(400,-20,20,400,-20,20)",names[i].c_str());
    data[i]->Draw(drawCmd, "", "colz");
    Radius->SetLogz(1);
    Radius->Update();
 }

 TCanvas* Position_2D=new TCanvas("Position_2D","Position_2D", 800, 500);
  Position_2D->Divide(2,2);
 for (int i=0; i<4; i++){
   Position_2D->cd(i+1);
      TString drawCmd = TString::Format("pspmtlow1.ypos:pspmtlow1.xpos>>\"%s    \"(480,0,48,480,0,48)",names[i].c_str());
    data[i]->Draw(drawCmd, "", "colz");
    Position_2D->SetLogz(1);
    Position_2D->Update();
 }
 
}



  
