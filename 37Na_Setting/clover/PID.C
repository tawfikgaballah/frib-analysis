{
  TChain *chain=new TChain("data");
 //   TCanvas* canvas=new TCanvas("");
 // canvas->Divide(2,2);
 // canvas->cd(1);
   chain->Add("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/CorrSorted37Na-Reverse-Win3/run*");
   chain->Draw("implantlist[0].de2:implantlist[0].tof>>decay_implantlist(500,-1000,-950,1400,0,1400)","corr.isdecay==1");
   TH1D* hist=(TH1D*)gDirectory->Get("decay_implantlist");
   hist->Draw("colz");
   TFile* output=new TFile("PID_Decays_Corr3_Final","RECREATE");
   hist->Write();
 // canvas->cd(2);
 // chain->Draw("implantlist[0].de2:implantlist[0].tof>>implant_implantlist(500,-1000,-950,1400,0,1400)","colz");
 // canvas->cd(3);
 // chain->Draw("corr.ide2:corr.itof>>implant_corr(500,-1000,-950,1400,0,1400)");
 // canvas->cd(4);
 // chain->Draw("corr.dde2:corr.dtof>>decay_corr(500,-1000,-950,1400,0,1400)");
}
