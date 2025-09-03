void get_histograms(TFile* input,const char* basehistname,int x, int y){
  TCanvas* canvas = new TCanvas("canvas", Form("%s%d%d",basehistname,x,y), 800, 600);
    canvas->Divide(4,4);
  for(int i=0; i<16; i++){
    canvas->cd(i+1);
     TString histname=Form("%s%d",basehistname,i);
    TH2D*  hist=(TH2D*)input->Get(histname);
    // hist->Draw("colz");
    // // delete hist;
    // canvas->Update();
    hist->GetYaxis()->SetRangeUser(x,y);
    TH1D* hist_1d=(TH1D*)hist->ProjectionX();
    hist_1d->GetXaxis()->SetRangeUser(-50,-10);
    hist_1d->Draw("colz");
     // TH1D* hist_1d=(TH1D*)input->Get(histname);
     //  hist_1d->GetXaxis()->SetRangeUser(-100,0);
     //  hist_1d->Draw("colz");
      canvas->Update();
  }
}
  void get_histograms_full(TFile* input){
     TCanvas* canvas = new TCanvas("canvas1", "Summed Histograms", 800, 600);
    canvas->Divide(2,2);
    canvas->cd(1);
    TH2D*  hist=(TH2D*)input->Get("Detector_Vs_Labr3_Ecal");
    hist->Draw("colz");
    // delete hist;
    canvas->cd(2);
    TH2D*  hist1=(TH2D*)input->Get("TDynode_Offset");
    hist1->Draw("colz");
    canvas->cd(3);
    TH2D*  hist2=(TH2D*)input->Get("LaBr3E_Vs_tdynode_offset");
    hist2->Draw("colz");
    canvas->cd(4);
     TH2D*  hist3=(TH2D*)input->Get("DyE_Vs_tdynode_offset");
    hist3->Draw("colz");
    canvas->Update();
  }



  void Dynode_Offset(){
    TFile* input= new TFile("Co_dytdiff_1240_dyecal_high2.root","read");

   
    // get_histograms_full( input);
    get_histograms(input, "/Labr3-Dynode/DyE_Vs_tdynode_offset_single_",30000, 40000);
    // get_histograms(input, "/Labr3-Dynode/DyE_Vs_tdynode_offset_single_",20000, 25000);
    // get_histograms(input, "/Labr3-Dynode/DyE_Vs_tdynode_offset_single_",25000, 30000);
    // get_histograms(input, "/Labr3-Dynode/DyE_Vs_tdynode_offset_single_",30000, 35000);
    // get_histograms(input, "/Labr3-Dynode/DyE_Vs_tdynode_offset_single_",35000, 40000);
  }
