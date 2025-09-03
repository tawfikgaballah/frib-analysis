#define BetaDecaySelector_cxx
// The class definition in BetaDecaySelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("BetaDecaySelector.C")
// root> T->Process("BetaDecaySelector.C","some options")
// root> T->Process("BetaDecaySelector.C+")
//


#include "BetaDecaySelector.h"
#include <TH2.h>
#include <TStyle.h>

void BetaDecaySelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void BetaDecaySelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

  
       // hIonDecayTime_37Na = new TH1D("hIonDecayTime_37Na",
       // 			      "T_{1/2} for 37Na",
       // 				      2000, 0, 200);
       // GetOutputList()->Add(hIonDecayTime_37Na);

       Position_Vs_hIonDecayTime_37Na= new TH2D("Position_Vs_hIonDecayTime_37Na","Position_Vs_hIonDecayTime_37Na",2000,-200,200,200,0,100);
       GetOutputList()->Add(Position_Vs_hIonDecayTime_37Na);
       Position_Vs_hIonDecayTime_33Na= new TH2D("Position_Vs_hIonDecayTime_33Na","Position_Vs_hIonDecayTime_33Na",2000,-200,200,200,0,100);
       GetOutputList()->Add(Position_Vs_hIonDecayTime_33Na);
       position_37=new TH2D("position_37","position_37",500,0,50,500,0,50);
       GetOutputList()->Add(position_37);
       position_33=new TH2D("position_33","position_33",500,0,50,500,0,50);
       GetOutputList()->Add(position_33);


       radius_37=new TH2D("radius_37","radius_37",500,-50,50,500,-50,50);
       GetOutputList()->Add(radius_37);
       radius_33=new TH2D("radius_33","radius_33",500,-50,50,500,-50,50);
       GetOutputList()->Add(radius_33);



       hIonDecayTime_35Na= new TH1D("hIonDecayTime_35Na","hIonDecayTime_35Na",4000,-200,200);
       GetOutputList()->Add(hIonDecayTime_35Na);

        hIonDecayTime_34Na= new TH1D("hIonDecayTime_34Na","hIonDecayTime_34Na",4000,-200,200);
       GetOutputList()->Add(hIonDecayTime_34Na);
       
       
       iongates_37 = new TCutG("iongates_37",11);
       iongates_37->SetVarX("PID");
       iongates_37->SetVarY("");
       iongates_37->SetTitle("Graph");
       iongates_37->SetFillStyle(1000);
       // iongates_37->SetPoint(0,-957.224,762.111);
       // iongates_37->SetPoint(1,-956.469,729.421);
       // iongates_37->SetPoint(2,-956.884,701.09);
       // iongates_37->SetPoint(3,-957.903,690.193);
       // iongates_37->SetPoint(4,-958.62,703.269);
       // iongates_37->SetPoint(5,-958.96,733.78);
       // iongates_37->SetPoint(6,-958.658,753.394);
       // iongates_37->SetPoint(7,-957.903,766.469);
       // iongates_37->SetPoint(8,-957.45,773.007);
       // iongates_37->SetPoint(9,-956.96,753.394);
       // iongates_37->SetPoint(10,-957.224,762.111);

       iongates_37->SetPoint(0,-957.315,762.764);
       iongates_37->SetPoint(1,-956.774,735.689);
       iongates_37->SetPoint(2,-957.107,701.231);
       iongates_37->SetPoint(3,-957.69,693.847);
       iongates_37->SetPoint(4,-958.439,698.769);
       iongates_37->SetPoint(5,-959.021,715.999);
       iongates_37->SetPoint(6,-959.105,738.15);
       iongates_37->SetPoint(7,-958.564,757.841);
       iongates_37->SetPoint(8,-957.523,770.148);
       iongates_37->SetPoint(9,-957.107,762.764);
       iongates_37->SetPoint(10,-957.315,762.764);
       GetOutputList()->Add(iongates_37);


       iongates_decay_37 = new TCutG("IONGATES_DECAY_37",19);
   iongates_decay_37->SetVarX("radius_37");
   iongates_decay_37->SetVarY("");
   iongates_decay_37->SetTitle("Graph");
   iongates_decay_37->SetFillStyle(1000);
   iongates_decay_37->SetPoint(0,2.92065,2.08882);
   iongates_decay_37->SetPoint(1,3.13775,1.40607);
   iongates_decay_37->SetPoint(2,2.58725,0.415411);
   iongates_decay_37->SetPoint(3,1.87394,0.0405666);
   iongates_decay_37->SetPoint(4,1.20715,-0.628798);
   iongates_decay_37->SetPoint(5,1.06759,-1.09735);
   iongates_decay_37->SetPoint(6,0.610136,-1.13752);
   iongates_decay_37->SetPoint(7,0.214713,-0.883157);
   iongates_decay_37->SetPoint(8,-0.157451,-0.695735);
   iongates_decay_37->SetPoint(9,-0.444327,-0.655573);
   iongates_decay_37->SetPoint(10,-0.932791,0.12089);
   iongates_decay_37->SetPoint(11,-1.12663,0.562671);
   iongates_decay_37->SetPoint(12,-1.11112,1.75414);
   iongates_decay_37->SetPoint(13,-0.738956,2.7448);
   iongates_decay_37->SetPoint(14,0.726437,2.959);
   iongates_decay_37->SetPoint(15,2.13756,2.79835);
   iongates_decay_37->SetPoint(16,2.82761,2.47705);
   iongates_decay_37->SetPoint(17,2.93616,2.03527);
   iongates_decay_37->SetPoint(18,2.92065,2.08882);
   GetOutputList()->Add(iongates_decay_37);



       
       iongates_33 = new TCutG("iongates_33",11);
       iongates_33->SetVarX("PIDhist");
       iongates_33->SetVarY("");
       iongates_33->SetTitle("Graph");
       iongates_33->SetFillStyle(1000);
       // iongates_33->SetPoint(0,-971.096,613.917);
       // iongates_33->SetPoint(1,-970.573,587.765);
       // iongates_33->SetPoint(2,-970.878,559.433);
       // iongates_33->SetPoint(3,-972.012,546.357);
       // iongates_33->SetPoint(4,-973.059,555.075);
       // iongates_33->SetPoint(5,-973.495,581.227);
       // iongates_33->SetPoint(6,-973.19,609.558);
       // iongates_33->SetPoint(7,-972.405,618.275);
       // iongates_33->SetPoint(8,-971.707,618.275);
       // iongates_33->SetPoint(9,-970.966,616.096);
       // iongates_33->SetPoint(10,-971.096,613.917);


       iongates_33->SetPoint(0,-971.566,633.531);
       iongates_33->SetPoint(1,-970.584,609.558);
       iongates_33->SetPoint(2,-970.358,570.33);
       iongates_33->SetPoint(3,-971.792,539.819);
       iongates_33->SetPoint(4,-973.037,546.357);
       iongates_33->SetPoint(5,-973.641,579.047);
       iongates_33->SetPoint(6,-973.453,603.02);
       iongates_33->SetPoint(7,-972.509,618.275);
       iongates_33->SetPoint(8,-972.358,629.172);
       iongates_33->SetPoint(9,-971.301,631.351);
       iongates_33->SetPoint(10,-971.566,633.531);
       GetOutputList()->Add(iongates_33);


       iongates_decay_33 = new TCutG("IONGATES_DECAY_33",25);
   iongates_decay_33->SetVarX("radius_33");
   iongates_decay_33->SetVarY("");
   iongates_decay_33->SetTitle("Graph");
   iongates_decay_33->SetFillStyle(1000);
   iongates_decay_33->SetPoint(0,2.03124,3.14013);
   iongates_decay_33->SetPoint(1,2.41929,2.69337);
   iongates_decay_33->SetPoint(2,2.71392,2.37425);
   iongates_decay_33->SetPoint(3,3.13071,1.99131);
   iongates_decay_33->SetPoint(4,3.48283,1.40414);
   iongates_decay_33->SetPoint(5,3.5475,0.0127958);
   iongates_decay_33->SetPoint(6,2.94387,-1.0722);
   iongates_decay_33->SetPoint(7,2.4121,-1.86361);
   iongates_decay_33->SetPoint(8,1.60008,-2.16996);
   iongates_decay_33->SetPoint(9,0.637141,-2.24654);
   iongates_decay_33->SetPoint(10,-0.376097,-2.22102);
   iongates_decay_33->SetPoint(11,-1.03003,-1.92743);
   iongates_decay_33->SetPoint(12,-1.45401,-1.83808);
   iongates_decay_33->SetPoint(13,-1.72708,-0.970081);
   iongates_decay_33->SetPoint(14,-2.15825,-0.650965);
   iongates_decay_33->SetPoint(15,-2.28041,0.165971);
   iongates_decay_33->SetPoint(16,-2.25885,0.957379);
   iongates_decay_33->SetPoint(17,-1.65522,1.90196);
   iongates_decay_33->SetPoint(18,-1.20968,2.55296);
   iongates_decay_33->SetPoint(19,-0.706657,3.07631);
   iongates_decay_33->SetPoint(20,-0.153328,3.29331);
   iongates_decay_33->SetPoint(21,0.989259,3.29331);
   iongates_decay_33->SetPoint(22,1.91626,3.19119);
   iongates_decay_33->SetPoint(23,2.08154,3.12737);
   iongates_decay_33->SetPoint(24,2.03124,3.14013);
   GetOutputList()->Add(iongates_decay_33);







   iongates_34 = new TCutG("IONGATES_34",16);
   iongates_34->SetVarX("PID");
   iongates_34->SetVarY("");
   iongates_34->SetTitle("Graph");
   iongates_34->SetFillStyle(1000);
   iongates_34->SetPoint(0,-966.797,643.693);
   iongates_34->SetPoint(1,-966.375,613.304);
   iongates_34->SetPoint(2,-967.043,582.916);
   iongates_34->SetPoint(3,-968.132,568.616);
   iongates_34->SetPoint(4,-969.08,565.041);
   iongates_34->SetPoint(5,-969.572,573.979);
   iongates_34->SetPoint(6,-969.853,591.854);
   iongates_34->SetPoint(7,-970.169,618.667);
   iongates_34->SetPoint(8,-969.959,641.905);
   iongates_34->SetPoint(9,-969.467,656.205);
   iongates_34->SetPoint(10,-968.799,663.355);
   iongates_34->SetPoint(11,-968.237,672.293);
   iongates_34->SetPoint(12,-967.429,659.78);
   iongates_34->SetPoint(13,-966.867,650.843);
   iongates_34->SetPoint(14,-966.586,645.48);
   iongates_34->SetPoint(15,-966.797,643.693);
   GetOutputList()->Add(iongates_34);





   



   iongates_35 = new TCutG("IONGATES_35",13);
   iongates_35->SetVarX("PID");
   iongates_35->SetVarY("");
   iongates_35->SetTitle("Graph");
   iongates_35->SetFillStyle(1000);
   iongates_35->SetPoint(0,-963.972,694.776);
   iongates_35->SetPoint(1,-962.846,658.209);
   iongates_35->SetPoint(2,-963.346,619.03);
   iongates_35->SetPoint(3,-964.139,605.97);
   iongates_35->SetPoint(4,-965.056,592.91);
   iongates_35->SetPoint(5,-965.765,600.746);
   iongates_35->SetPoint(6,-966.473,632.09);
   iongates_35->SetPoint(7,-966.682,666.045);
   iongates_35->SetPoint(8,-965.89,689.552);
   iongates_35->SetPoint(9,-965.139,702.612);
   iongates_35->SetPoint(10,-964.556,705.224);
   iongates_35->SetPoint(11,-963.763,692.164);
   iongates_35->SetPoint(12,-963.972,694.776);
   GetOutputList()->Add(iongates_35);
   
}

Bool_t BetaDecaySelector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

   bool isGoodDecay = (*corr_flag == 12);
   bool isGoodCorr = (*corr_flag == 32 && *corr_isdecay == 1);

   if (isGoodCorr) {
       // Precompute values that do not depend on the loop
       double corr_dxpos_x = *corr_dxpos;
       double corr_dypos_y = *corr_dypos;
       
       for (auto& implant : *implantlist) {
           double xpos = implant.xpos;
           double ypos = implant.ypos;
           double dx = corr_dxpos_x - xpos;
           double dy = corr_dypos_y - ypos;
           
           if (dx >= -1 && dx <= 2 && dy >= -1 && dy <= 2) {
               double tof1 = implant.tof;
               double DE2 = implant.de2;
               double Radius = sqrt(dx * dx + dy * dy);
               double dtimecal = *corr_dtime - implant.time;

               if (iongates_35->IsInside(tof1, DE2)) {
                   hIonDecayTime_35Na->Fill(dtimecal);
               }

               if (iongates_34->IsInside(tof1, DE2)) {
                   hIonDecayTime_34Na->Fill(dtimecal);
               }
           }
       }
   }

   return kTRUE;
}

// Bool_t BetaDecaySelector::Process(Long64_t entry)
// {
//    // The Process() function is called for each entry in the tree (or possibly
//    // keyed object in the case of PROOF) to be processed. The entry argument
//    // specifies which entry in the currently loaded tree is to be processed.
//    // When processing keyed objects with PROOF, the object is already loaded
//    // and is available via the fObject pointer.
//    //
//    // This function should contain the \"body\" of the analysis. It can contain
//    // simple or elaborate selection criteria, run algorithms on the data
//    // of the event and typically fill histograms.
//    //
//    // The processing can be stopped by calling Abort().
//    //
//    // Use fStatus to set the return value of TTree::Process().
//    //
//    // The return value is currently not used.

//    fReader.SetEntry(entry);



 


   
//    //@UPDATE: 01/02/2020
//    //new flags for correlations used
//    // some flags

//    bool isGoodDecay = false;
//    if(*corr_flag == 12) isGoodDecay = true; 
//    bool isGoodCorr = false;
//    if(*corr_flag == 32) isGoodCorr = true;
//    if(isGoodCorr && *corr_isdecay==1){
//      //   {// && isLocal) {
//      for(unsigned int j=0; j<implantlist->size(); j++) {
//        double tof1 = implantlist->at(j).tof;
//        double DE2 = implantlist->at(j).de2;
//        double implantTime = implantlist->at(j).time;
//        double xpos=implantlist->at(j).xpos;
//        double ypos=implantlist->at(j).ypos;
//        double Radius=sqrt(pow((xpos-*corr_dxpos), 2) + pow((ypos-*corr_dypos), 2));
   
//        double dtimecal = *corr_dtime-implantTime;  
//        if((*corr_dxpos-xpos)>=-1 &&(*corr_dxpos-xpos)<=2 && (*corr_dypos-ypos)>=-1 && (*corr_dypos-ypos)<=2){
// 	 if( iongates_37->IsInside(tof1, DE2) // && iongates_decay_37->IsInside(*corr_dxpos-xpos,*corr_dypos-ypos)
// 	     ) {
// 	   Position_Vs_hIonDecayTime_37Na->Fill(dtimecal, Radius);
// 	   //radius_37->Fill(*corr_dxpos-xpos,*corr_dypos-ypos);
// 	   //position_37->Fill(*pspmtlow1_xpos,*pspmtlow1_ypos);

// 	 }
// 	 if( iongates_33->IsInside(tof1, DE2)// && iongates_decay_33->IsInside(*corr_dxpos-xpos,*corr_dypos-ypos)
// 	     ) {
// 	   Position_Vs_hIonDecayTime_33Na->Fill(dtimecal, Radius);
// 	   // radius_33->Fill(*corr_dxpos-xpos,*corr_dypos-ypos);
// 	   //position_33->Fill(*pspmtlow1_xpos,*pspmtlow1_ypos);

// 	 } 
     
//        }
//      }
//    }


   
   
//    return kTRUE;
// }

void BetaDecaySelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void BetaDecaySelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

  TFile *outroot = new TFile("test_root.root",
			     "RECREATE");

  // fOutput->FindObject("iongates_35")->Write();
  // fOutput->FindObject("iongates_34")->Write();
  fOutput->FindObject("IONGATES_34")->Write();
  fOutput->FindObject("IONGATES_35")->Write();
    
  fOutput->FindObject("hIonDecayTime_34Na")->Write();
  fOutput->FindObject("hIonDecayTime_35Na")->Write();
  // fOutput->FindObject("position_33")->Write();
  // fOutput->FindObject("position_37")->Write();

  // fOutput->FindObject("radius_33")->Write();
  // fOutput->FindObject("radius_37")->Write();

  outroot->Close(); 
}
