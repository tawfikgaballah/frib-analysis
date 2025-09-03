{
  TFile *files[2];
  // files[0]=new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1281-sorted-TG-48-newcorrection.root","READ");
  // files[1]=new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1281-sorted-TG-24.root","READ");
  // files[2]=new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1281-sorted-TG-48-nocorrection.root","READ");
  // files[3]=new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1281-sorted-TG-24-nocorrection.root","READ");


  files[0]=new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-sorted-TG-48-newcorrection.root","READ");
  files[1]=new TFile("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1422-sorted-TG-48-nocorrection1.root","READ");
  

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

    TCutG *I33Na = new TCutG("I33Na",8);
   I33Na->SetVarX("corr.itof");
   I33Na->SetVarY("corr.ide2");
   I33Na->SetTitle("Graph");
   I33Na->SetFillStyle(1000);
   I33Na->SetPoint(0,-971.707,624.089);
   I33Na->SetPoint(1,-970.35,598.785);
   I33Na->SetPoint(2,-970.282,568.06);
   I33Na->SetPoint(3,-972.183,539.141);
   I33Na->SetPoint(4,-973.88,575.289);
   I33Na->SetPoint(5,-973.473,596.978);
   I33Na->SetPoint(6,-971.64,625.896);
   I33Na->SetPoint(7,-971.707,624.089);




 TCutG *D33Na = new TCutG("D33Na",9);
   D33Na->SetVarX("implantlist.tof");
   D33Na->SetVarY("implantlist.de2");
   D33Na->SetTitle("Graph");
   D33Na->SetFillStyle(1000);
   D33Na->SetPoint(0,-971.707,625.896);
   D33Na->SetPoint(1,-970.418,591.556);
   D33Na->SetPoint(2,-970.418,564.445);
   D33Na->SetPoint(3,-971.843,546.371);
   D33Na->SetPoint(4,-972.726,546.371);
   D33Na->SetPoint(5,-973.812,582.519);
   D33Na->SetPoint(6,-972.522,622.282);
   D33Na->SetPoint(7,-971.436,620.474);
   D33Na->SetPoint(8,-971.707,625.896);



  
  std::string names[2] = {
			  "npspmtutk=48_newcorrection",
			  // "npspmtutk=24",
			  "npspmtutk=48_nocorrection"
			  // "npspmtutk=24_nocorrection"
  };
  TTree* data[4];

  for (int i=0; i< 2; i++){
    data[i]=(TTree*)files[i]->Get("data");
  }
     


  TCanvas* PID_Implant = new TCanvas("PID_Implant", "PID_Implant", 1000, 800);
  PID_Implant->Divide(2);
  for (int i = 0; i < 2; i++) {
    PID_Implant->cd(i + 1);
    TString histName = TString::Format("%s_PID_Implant", names[i].c_str());
    TH2D *hist = new TH2D(histName, histName + ";ITOF;IDE2", 500, -1000, -950, 1400, 0, 1400);
    TString drawCmd = TString::Format("corr.ide2:corr.itof>>%s", histName.Data());
    data[i]->Draw(drawCmd, " corr.isimplant", "colz");
    hist->GetXaxis()->SetTitle("ITOF");
    hist->GetYaxis()->SetTitle("IDE2");
    gPad->SetLogz(1);
    hist->GetXaxis()->SetTitleFont(43); // 43 is Times New Roman bold
    hist->GetYaxis()->SetTitleFont(43); // 43 is Times New Roman bold
    hist->GetXaxis()->SetTitleSize(20);
    hist->GetYaxis()->SetTitleSize(20);
    hist->GetXaxis()->CenterTitle();    // Center the X axis title
    hist->GetYaxis()->CenterTitle(); 
    hist->GetYaxis()->SetTitleOffset(1.5); // Adjust this value as needed
    hist->GetXaxis()->SetTitleOffset(1.5);
    I33Na->Draw("same");
    PID_Implant->Update();
    gPad->Update();
  }
    PID_Implant->SaveAs("PID_Implant.tiff");

  TCanvas* PID_Decay = new TCanvas("PID_Decay", "PID_Decay", 1000, 800);
  PID_Decay->Divide(2);
  for (int i = 0; i < 2; i++) {
    PID_Decay->cd(i + 1);
    TString histName = TString::Format("%s_PID_Decay", names[i].c_str());
    TH2D *hist = new TH2D(histName, histName + ";TOF;DE2", 500, -1000, -950, 1400, 0, 1400);
    TString drawCmd = TString::Format("implantlist.de2:implantlist.tof>>%s", histName.Data());
    data[i]->Draw(drawCmd, "corr.isdecay==1 &&corr.flag==32", "colz");
    hist->GetXaxis()->SetTitle("TOF");
    hist->GetYaxis()->SetTitle("DE2");
    gPad->SetLogz(1);
       hist->GetXaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetYaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetXaxis()->SetTitleSize(20);
    hist->GetYaxis()->SetTitleSize(20);
     hist->GetXaxis()->SetTitleOffset(1.5);
    hist->GetXaxis()->CenterTitle();    // Center the X axis title
    hist->GetYaxis()->CenterTitle(); 
    hist->GetYaxis()->SetTitleOffset(1.5); // Adjust this value as needed
    D33Na->Draw("same");
    PID_Decay->Update();
    gPad->Update();
  }
  PID_Decay->SaveAs("PID_Decay.tiff");
  TCanvas* Position_Correction_Low_Gain = new TCanvas("Position_Correction_Low_Gain", "Position_Correction_Low_Gain", 1000, 800);
  Position_Correction_Low_Gain->Divide(2);
  for (int i = 0; i < 2; i++) {
    Position_Correction_Low_Gain->cd(i + 1);
    TString histName = TString::Format("%s_DyEcal_Vs_XPos", names[i].c_str());
    TH2D *hist = new TH2D(histName, histName + ";Dynode_Ecal;YPos_LG", 600, -10, 50, 10000, 0, 100000);
    TString drawCmd = TString::Format("pspmtlow1.dyecal:pspmtlow1.xpos>>%s", histName.Data());
    data[i]->Draw(drawCmd, "", "colz");
    hist->GetXaxis()->SetTitle("XPos_LG");
    hist->GetYaxis()->SetTitle("Dynode_Ecal");
    gPad->SetLogz(1);
       hist->GetXaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetYaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetXaxis()->SetTitleSize(20);
    hist->GetYaxis()->SetTitleSize(20);
    hist->GetXaxis()->SetTitleOffset(1.5);
    hist->GetYaxis()->SetTitleOffset(1.5); // Adjust this value as needed
        hist->GetXaxis()->CenterTitle();    // Center the X axis title
    hist->GetYaxis()->CenterTitle(); 
    Position_Correction_Low_Gain->Update();
    gPad->Update();
  }
Position_Correction_Low_Gain->SaveAs("Position_Correction_Low_Gain.tiff");
  TCanvas* Y_Position_Correction_Low_Gain = new TCanvas("Y_Position_Correction_Low_Gain", "Y_Position_Correction_Low_Gain", 1000, 800);
  Y_Position_Correction_Low_Gain->Divide(2);
  for (int i = 0; i < 2; i++) {
    Y_Position_Correction_Low_Gain->cd(i + 1);
    TString histName = TString::Format("%s_DyEcal_Vs_YPos", names[i].c_str());
    TH2D *hist = new TH2D(histName, histName + ";Dynode_Ecal;YPos_LG", 600, -10, 50, 10000, 0, 100000);
    TString drawCmd = TString::Format("pspmtlow1.dyecal:pspmtlow1.ypos>>%s", histName.Data());
    data[i]->Draw(drawCmd, "", "colz");
    hist->GetXaxis()->SetTitle("YPos_LG");
    hist->GetYaxis()->SetTitle("Dynode_Ecal");
    gPad->SetLogz(1);
       hist->GetXaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetYaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetXaxis()->SetTitleSize(20);
    hist->GetYaxis()->SetTitleSize(20);
    hist->GetYaxis()->SetTitleOffset(1.5); // Adjust this value as needed
    Y_Position_Correction_Low_Gain->Update();
        hist->GetXaxis()->CenterTitle();    // Center the X axis title
	hist->GetYaxis()->CenterTitle(); 
    gPad->Update();
  }
 Y_Position_Correction_Low_Gain->SaveAs("Y_Position_Correction_Low_Gain.tiff");

  TCanvas* Position_Correction_High_Gain = new TCanvas("Position_Correction_High_Gain", "Position_Correction_High_Gain", 1000, 800);
  Position_Correction_High_Gain->Divide(2);
  for (int i = 0; i < 2; i++) {
    Position_Correction_High_Gain->cd(i + 1);
    TString histName = TString::Format("%s_DyEcal_Vs_XPos_HG", names[i].c_str());
    TH2D *hist = new TH2D(histName, histName + ";Dynode_Ecal;XPos_HG", 700, -10, 60, 10000, 0, 100000);
    TString drawCmd = TString::Format("pspmthigh1.dyecal:pspmthigh1.xpos_highgain>>%s", histName.Data());
    data[i]->Draw(drawCmd, "", "colz");
    hist->GetXaxis()->SetTitle("XPos_HG");
    hist->GetYaxis()->SetTitle("Dynode_Ecal");
    gPad->SetLogz(1);
       hist->GetXaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetYaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetXaxis()->SetTitleSize(20);
    hist->GetYaxis()->SetTitleSize(20);
    hist->GetXaxis()->SetTitleOffset(1.5);
    hist->GetYaxis()->SetTitleOffset(1.5); // Adjust this value as needed
    Position_Correction_High_Gain->Update();
        hist->GetXaxis()->CenterTitle();    // Center the X axis title
    hist->GetYaxis()->CenterTitle(); 
    gPad->Update();
  }
Position_Correction_High_Gain->SaveAs("Position_Correction_High_Gain.tiff");




  TCanvas* Y_Position_Correction_High_Gain = new TCanvas("Y_Position_Correction_High_Gain", "Y_Position_Correction_High_Gain", 1000, 800);
  Y_Position_Correction_High_Gain->Divide(2);
  for (int i = 0; i < 2; i++) {
    Y_Position_Correction_High_Gain->cd(i + 1);
    TString histName = TString::Format("%s_DyEcal_Vs_yPos_HG", names[i].c_str());
    TH2D *hist = new TH2D(histName, histName + ";Dynode_Ecal;XPos_HG", 700, -10, 60, 10000, 0, 100000);
    TString drawCmd = TString::Format("pspmthigh1.dyecal:pspmthigh1.ypos_highgain>>%s", histName.Data());
    data[i]->Draw(drawCmd, "", "colz");
    hist->GetXaxis()->SetTitle("YPos_HG");
    hist->GetYaxis()->SetTitle("Dynode_Ecal");
    gPad->SetLogz(1);
       hist->GetXaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetYaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetXaxis()->SetTitleSize(20);
    hist->GetYaxis()->SetTitleSize(20);
    hist->GetXaxis()->SetTitleOffset(1.5);
    hist->GetYaxis()->SetTitleOffset(1.5); // Adjust this value as needed
    hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->CenterTitle(); 
    Y_Position_Correction_High_Gain->Update();
    gPad->Update();
  }
  
Y_Position_Correction_High_Gain->SaveAs("Y_Position_Correction_High_Gain.tiff");
  TCanvas* Position_2D = new TCanvas("Position_2D", "Position_2D", 1000, 800);
  Position_2D->Divide(2);
  for (int i = 0; i < 2; i++) {
    Position_2D->cd(i + 1);
    TString histName = TString::Format("%s_Position_2D_LG", names[i].c_str());
    TH2D *hist = new TH2D(histName, histName + ";XPos;YPos", 600, -10, 50, 600, -10, 50);
    TString drawCmd = TString::Format("pspmtlow1.ypos:pspmtlow1.xpos>>%s", histName.Data());
    data[i]->Draw(drawCmd, "", "colz");
    hist->GetXaxis()->SetTitle("XPos_LG");
    hist->GetYaxis()->SetTitle("YPos_LG");
    gPad->SetLogz(1);
       hist->GetXaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetYaxis()->SetTitleFont(43); // 2 is Times New Roman bold
    hist->GetXaxis()->SetTitleSize(20);
    hist->GetYaxis()->SetTitleSize(20);
    hist->GetYaxis()->SetTitleOffset(1.5); // Adjust this value as needed
        hist->GetXaxis()->CenterTitle();    // Center the X axis title
	hist->GetXaxis()->SetTitleOffset(1.5);
	hist->GetYaxis()->CenterTitle(); 
    Position_2D->Update();
    gPad->Update();
  }
Position_2D->SaveAs("Position_2D.tiff");
  // TFile* output=new TFile("33Na_Decay_Curve_nocorrection.root","update");
  // TCanvas* Decay_Curve_33Na = new TCanvas("Decay_Curve_^{33}Na", "Decay_Curve_^{33}Na", 1000, 800);
  // Decay_Curve_33Na->Divide(2);
  // for (int i = 0; i < 2; i++) {
  //   Decay_Curve_33Na->cd(i + 1);
  //   TString histName = TString::Format("%s_Decay_Curve_^{33}Na", names[i].c_str());
  //   TH1D *hist = new TH1D(histName, histName + ";Decay_Time [Counts/ms]", 200,-100,100);
  //   TString drawCmd = TString::Format("corr.dtime-implantlist.time>>%s", histName.Data());
  //   data[i]->Draw(drawCmd, "corr.isdecay==1 && corr.flag==32 &&D33Na", "colz");
  //   hist->GetXaxis()->SetTitle("Decay_Time [counts/ms]");
  //   gPad->SetLogz(1);
  //      hist->GetXaxis()->SetTitleFont(43); // 2 is Times New Roman bold
  //   hist->GetYaxis()->SetTitleFont(43); // 2 is Times New Roman bold
  //   hist->GetXaxis()->SetTitleSize(20);
  //   hist->GetYaxis()->SetTitleSize(20);
  //   hist->GetXaxis()->SetTitleOffset(1.5);
  //   hist->GetYaxis()->SetTitleOffset(1.5); // Adjust this value as needed
  //       hist->GetXaxis()->CenterTitle();    // Center the X axis title
  //   hist->GetYaxis()->CenterTitle();
  //   hist->Write();
  //   Decay_Curve_33Na->Update();
  //   gPad->Update();
  // }






 
}



  
