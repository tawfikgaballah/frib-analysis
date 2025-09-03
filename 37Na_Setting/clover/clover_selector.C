#define clover_selector_cxx
// The class definition in clover_selector.h has been generated automatically
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
// root> T->Process("clover_selector.C")
// root> T->Process("clover_selector.C","some options")
// root> T->Process("clover_selector.C+")
//


#include "clover_selector.h"
#include <TH2.h>
#include <TStyle.h>

void clover_selector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void clover_selector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

				// h2Clover32NaAll = new TH2D("h2Clover32NaAll",
  // 			   "gamma_gamma Spectrum, gated on #beta-decays of ^{32}Na",
  // 			   4500, 0, 4500,4500,0,4500);
  // GetOutputList()->Add(h2Clover32NaAll);

  // h2Clover32NaAll_AB = new TH2D("h2Clover32NaAll_AB",
  // 			   "gamma_gamma Spectrum, gated on #beta-decays of ^{32}Na",
  // 			   4500, 0, 4500,4500,0,4500);
  // GetOutputList()->Add(h2Clover32NaAll_AB);


  
 //  h1Clover33NaAll = new TH2D("Time_Vs_Clover_33Na",
 // 			   "Total Clover Spectrum, gated on #beta-decays of ^{33}Na",
 // 			     4500, 0, 4500,100,0,100);
 //  GetOutputList()->Add(h1Clover33NaAll);
 //  h1Clover33NaAll_AB = new TH2D("Time_Vs_Clover_33Na_AB",
 // 				"Total Clover Spectrum, gated on #beta-decays of ^{33}Na",
 // 				4500, 0, 4500,100,0,100);
 //  GetOutputList()->Add(h1Clover33NaAll_AB);

 //  h1Clover34NaAll = new TH2D("Time_Vs_Clover_34Na",
 // 			   "Total Clover Spectrum, gated on #beta-decays of ^{34}Na",
 // 			     4500, 0, 4500,100,0,100);
 //  GetOutputList()->Add(h1Clover34NaAll);
 //  h1Clover34NaAll_AB = new TH2D("Time_Vs_Clover_34Na_AB",
 // 				"Total Clover Spectrum, gated on #beta-decays of ^{34}Na",
 // 				4500, 0, 4500,100,0,100);
 //  GetOutputList()->Add(h1Clover34NaAll_AB);

 //    h1Clover35NaAll = new TH2D("Time_Vs_Clover_35Na",
 // 			   "Total Clover Spectrum, gated on #beta-decays of ^{35}Na",
 // 			     4500, 0, 4500,100,0,100);
 //  GetOutputList()->Add(h1Clover35NaAll);
 //  h1Clover35NaAll_AB = new TH2D("Time_Vs_Clover_35Na_AB",
 // 				"Total Clover Spectrum, gated on #beta-decays of ^{35}Na",
 // 				4500, 0, 4500,100,0,100);
 //  GetOutputList()->Add(h1Clover35NaAll_AB);

  for ( int i:{7,5,4,3,2,1}){
    iongates[3][i]=(TCutG*)blobs->Get(Form("iongates_3%dNa",i));
    GetOutputList()->Add(iongates[3][i]);

    h2CloverNaAll[3][i]=new TH2D(Form("DecayTime_Vs_Clover_3%dNa",i),
 				 Form("Total Clover Spectrum, gated on #beta-decays of ^{3%d}Na",i),
 			     4500, 0, 4500,300,0,100);
  GetOutputList()->Add(h2CloverNaAll[3][i]);

   h2CloverNaAll_implant[3][i]=new TH2D(Form("Clover_3%dNa_Vs_Time",i),
 				 Form("Total Clover Spectrum_Vs_Time_Since_Last_Implant_gated_on_#beta-decays of ^{3%d}Na",i),
 					2000,-50,150,4500,0,4500);
  GetOutputList()->Add(h2CloverNaAll_implant[3][i]);
 }

 
  
  PID_Implant = new TH2D("PID_Implant",
  		     "PID_Implant",
  		     500,-1000,-950,1400,0,1400);
  GetOutputList()->Add(PID_Implant);

   PID_Decay = new TH2D("PID_Decay",
  		     "PID_Decay",
  		     500,-1000,-950,1400,0,1400);
  GetOutputList()->Add(PID_Decay);


 




// iongates_33 = new TCutG("iongates_33",11);
//        iongates_33->SetVarX("PIDhist");
//        iongates_33->SetVarY("");
//        iongates_33->SetTitle("Graph");
//        iongates_33->SetFillStyle(1000);
//        iongates_33->SetPoint(0,-971.566,633.531);
//        iongates_33->SetPoint(1,-970.584,609.558);
//        iongates_33->SetPoint(2,-970.358,570.33);
//        iongates_33->SetPoint(3,-971.792,539.819);
//        iongates_33->SetPoint(4,-973.037,546.357);
//        iongates_33->SetPoint(5,-973.641,579.047);
//        iongates_33->SetPoint(6,-973.453,603.02);
//        iongates_33->SetPoint(7,-972.509,618.275);
//        iongates_33->SetPoint(8,-972.358,629.172);
//        iongates_33->SetPoint(9,-971.301,631.351);
//        iongates_33->SetPoint(10,-971.566,633.531);
//        GetOutputList()->Add(iongates_33);


//  iongates_34 = new TCutG("IONGATES_34",16);
//    iongates_34->SetVarX("PID");
//    iongates_34->SetVarY("");
//    iongates_34->SetTitle("Graph");
//    iongates_34->SetFillStyle(1000);
//    iongates_34->SetPoint(0,-966.797,643.693);
//    iongates_34->SetPoint(1,-966.375,613.304);
//    iongates_34->SetPoint(2,-967.043,582.916);
//    iongates_34->SetPoint(3,-968.132,568.616);
//    iongates_34->SetPoint(4,-969.08,565.041);
//    iongates_34->SetPoint(5,-969.572,573.979);
//    iongates_34->SetPoint(6,-969.853,591.854);
//    iongates_34->SetPoint(7,-970.169,618.667);
//    iongates_34->SetPoint(8,-969.959,641.905);
//    iongates_34->SetPoint(9,-969.467,656.205);
//    iongates_34->SetPoint(10,-968.799,663.355);
//    iongates_34->SetPoint(11,-968.237,672.293);
//    iongates_34->SetPoint(12,-967.429,659.78);
//    iongates_34->SetPoint(13,-966.867,650.843);
//    iongates_34->SetPoint(14,-966.586,645.48);
//    iongates_34->SetPoint(15,-966.797,643.693);
//    GetOutputList()->Add(iongates_34);



   

//    iongates_35 = new TCutG("IONGATES_35",13);
//    iongates_35->SetVarX("PID");
//    iongates_35->SetVarY("");
//    iongates_35->SetTitle("Graph");
//    iongates_35->SetFillStyle(1000);
//    iongates_35->SetPoint(0,-963.972,694.776);
//    iongates_35->SetPoint(1,-962.846,658.209);
//    iongates_35->SetPoint(2,-963.346,619.03);
//    iongates_35->SetPoint(3,-964.139,605.97);
//    iongates_35->SetPoint(4,-965.056,592.91);
//    iongates_35->SetPoint(5,-965.765,600.746);
//    iongates_35->SetPoint(6,-966.473,632.09);
//    iongates_35->SetPoint(7,-966.682,666.045);
//    iongates_35->SetPoint(8,-965.89,689.552);
//    iongates_35->SetPoint(9,-965.139,702.612);
//    iongates_35->SetPoint(10,-964.556,705.224);
//    iongates_35->SetPoint(11,-963.763,692.164);
//    iongates_35->SetPoint(12,-963.972,694.776);
//    GetOutputList()->Add(iongates_35);








  
   TString option = GetOption();

}

Bool_t clover_selector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetLocalEntry(entry);


   
   // if(*corr_flag==32){
   //   for(unsigned int j=0; j<implantlist->size(); j++) {
   //     double tof1 = implantlist->at(j).tof;
   //     double DE2 = implantlist->at(j).de2;
   //     double implantTime = implantlist->at(j).time;
   //     // double Radius=sqrt(pow((implantlist->at(j).xpos-*corr_dxpos), 2) + pow((implantlist->at(j).ypos-*corr_dypos), 2));
   //     double xpos=implantlist->at(j).xpos-*corr_dxpos;
   //     double ypos=implantlist->at(j).ypos-*corr_dypos;
   //     double dtimecal = abs(implantTime-*corr_dtime);
   //     PIDhist->Fill(tof1,DE2);
   //     if( abs(dtimecal)>0 && abs(dtimecal)<77 &&xpos>=0 && xpos<=14 && ypos>=0 && ypos<=14
   // 	   ){
   // 	 // cout<<*corr_itime<<'\n';
	 
      
	 
     

      
   // 	 if(iongates&& iongates->IsInside(tof1,DE2) ){

   // 	   for(int s=0; s<52;s++){
   // 	     if(clover_ecal[s]>10 && clover_timecal[s]>10 &&clover_cfdfailbit[s]!=1)
   // 	       clover_Vs_time->Fill(clover_timecal[s]-dtimecal*1.0e3,clover_ecal[s]);
   // 	   }
   // 	   for(int s=0; s<13;s++){
   // 	     if(clover_ecalab[s]>10 && clover_timecalab[s]>10&&clover_cfdfailbit[s]!=1)
   // 	       clover_Vs_time_ab->Fill(clover_timecalab[s]-dtimecal*1.0e3,clover_ecalab[s]);
   // 	   }
   // 	   for(int s = 0; s < 52; s++) {
   // 	     if(clover_ecal[s]>50 && clover_cfdfailbit[s]!=1 && clover_timecal[s]>10 &&(s!=26 && s!=24 &&s!=25 && s!=27 &&s!=45 && s!=46 &&s!19 &&s!=20) /*&& coincCut->IsInside(clover_ecal[s],
   // 														  (clover_timecal[s]-*corr_dtime*1.0e6))*/){
   // 	       h1Clover32NaAll->Fill(clover_ecal[s]);
   // 	       h2E_Vs_id->Fill(clover_ecal[s],s);
   // 	       for(int p=s+1; p<52;p++){
   // 		 if(clover_ecal[p]>10 && clover_cfdfailbit[p]!=1 && clover_timecal[p]>10 &&(p!=26 && p!=24 &&p!=25  && p!=27 &&p!=45 && p!=46 &&p!=19 &&p!=20) /*&& coincCut->IsInside(clover_ecal[p],(clover_timecal[p]-*corr_dtime*1.0e6))*/){  
   // 		   h2Clover32NaAll->Fill(clover_ecal[s],clover_ecal[p]);
   // 		   h2Clover32NaAll->Fill(clover_ecal[p],clover_ecal[s]);
	       
   // 		 }
   // 	       }  
   // 	     }
   // 	   }//end_cloverecal

   // 	   //  for(int s = 0; s < 13; s++) {
   // 	   //   if(clover_ecalab[s]>10 && clover_cfdfailbitab[s]!=1 && clover_timecalab[s]>10/*&&(s!=3 && s!=7)&& coincCut_ab->IsInside(clover_ecalab[s],
   // 	   // 												    (clover_timecalab[s]-*corr_dtime*1.0e6)+100)*/){
   // 	   //     h1Clover32NaAll_AB->Fill(clover_ecalab[s]);
   // 	   //     h2E_Vs_id_AB->Fill(clover_ecalab[s],s);
   // 	   //     for(int p=s+1; p<13;p++){
   // 	   // 	 if(clover_ecalab[p]>10 && clover_cfdfailbitab[p]!=1 && clover_timecalab[p]>10 /*&&(p!=3 && p!=7) && coincCut_ab->IsInside(clover_ecalab[p],
   // 	   // 													 (clover_timecalab[p]-*corr_dtime*1.0e6)+100)*/){
		
   // 	   // 	   h2Clover32NaAll_AB->Fill(clover_ecalab[s],clover_ecalab[p]);
   // 	   // 	   h2Clover32NaAll_AB->Fill(clover_ecalab[p],clover_ecalab[s]);
	      
   // 	   // 	 }
   // 	   //     }  
   // 	   //   }
   // 	   // }
   // 	   //end_cloverecalab
   // 	   //	}//end_Single_Pulse
   // 	 }//end_PID_Gate
   //     }//end_half_life_gate
   //   }//end_loop_over_Implants
   // } //end_flag_Check




    bool isGoodImplant = (*corr_isimplant == 1);
   bool isGoodCorr = (*corr_flag == 32 && *corr_isdecay==1);
  
   if(implantlist->size()>0){
     for (int i=0; i<(int)implantlist->size();i++) {      
       double tof1 = implantlist->at(i).tof;
       std::cout<<tof1<<'\n';
       double DE2 = implantlist->at(i).de2;
       // PID_Implant->Fill(tof1,DE2);
       // if(isGoodCorr){
       // 	 PID_Decay->Fill(tof1,DE2);
       // }
     }
   }
   
   
   // if (isGoodCorr) {
   //   // Precompute values that do not depend on the loop
   //   double corr_dxpos_x = *corr_dxpos;
   //   double corr_dypos_y = *corr_dypos;
       
     // for (auto& implant : implantlist) {
     //   double xpos = implant.xpos;
     //   double ypos = implant.ypos;
     //   double dx = corr_dxpos_x - xpos;
     //   double dy = corr_dypos_y - ypos;
           
       
     //   double tof1 = implant.tof;
     //   double DE2 = implant.de2;
   //     double Radius = sqrt(dx * dx + dy * dy);
   //     double dtimecal = *corr_dtime - implant.time;
   //     for(int s=0; s<52;s++){
   // 	 if(clover_ecal[s]>10 && clover_timecal[s]>10 &&clover_cfdfailbit[s]!=1 &&(s!=26 && s!=24 &&s!=25 && s!=27 &&s!=45 && s!=46 &&s!=19 &&s!=20)){
   // 	   // for(int s=0; s<13;s++){
   // 	   //   if(clover_ecalab[s]>10 && clover_timecalab[s]>10&&clover_cfdfailbitab[s]!=1){
   // 	   for ( int i:{7,5,4,3,2,1}){
   // 	     if (iongates[3][i]->IsInside(tof1, DE2)) {
   // 	       std::cout<<"True:"<<i<<'\n';
   // 	        if (dx >= -1 && dx <= 2 && dy >= -1 && dy <= 2) {
   // 	       if (isGoodCorr){
   // 		   h2CloverNaAll[3][i]->Fill(clover_ecal[s],dtimecal);
   // 		 }
   		 
   // 	       }
   // 		if (*corr_flag==32){
   // 		h2CloverNaAll_implant[3][i]->Fill(clover_timecal[s]/1e03-implant.time*1e03,clover_ecal[s]);
   // 		}
   // 	     }
   	     
   // 	   }
	     
   // 	 }

   //     }
   //   }
   // }
   return kTRUE;
}

void clover_selector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void clover_selector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
TFile *outroot = new TFile("./PID_CorrSorted37Na-Win7.root","RECREATE");
  // fOutput->FindObject("h2Sega32NaAll")->Write();
   // MakeOutput("Time_Vs_Clover_35Na");
   // MakeOutput("Time_Vs_Clover_34Na");
   // MakeOutput("Time_Vs_Clover_33Na");
   // MakeOutput("iongates_33");
   // MakeOutput("IONGATES_34");
   // MakeOutput("IONGATES_35");
   // MakeOutput("h1Clover32NaAll_AB");
  // MakeOutput("h2Clover32NaAll");
  // MakeOutput("h2E_Vs_id");
  // MakeOutput("h2E_Vs_id_AB");
  // MakeOutput("h1Clover32NaAll");
  //  fOutput->FindObject("PID_Implant")->Write();
  // fOutput->FindObject("PID_Decay")->Write();
  // MakeOutput("iongates");
  // MakeOutput("clover_Vs_time");
  // MakeOutput("clover_Vs_time_ab");



 // for ( int i:{7,5,4,3,2,1}){
 //   outroot->mkdir(Form("3%dNa",i));
 //   outroot->cd(Form("3%dNa",i));
 //   MakeOutput(Form("iongates_3%dNa",i));
 //   MakeOutput(Form("DecayTime_Vs_Clover_3%dNa",i));
 //   MakeOutput(Form("Clover_3%dNa_Vs_Time",i));
 // }




 
  outroot->Close();
}
