#define labr_selector_cxx
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


#include "labr_selector.h"
#include <TH2.h>
#include <TStyle.h>

void labr_selector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void labr_selector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

				// h2Labr32NaAll = new TH2D("h2Labr32NaAll",
  // 			   "gamma_gamma Spectrum, gated on #beta-decays of ^{32}Na",
  // 			   4500, 0, 4500,4500,0,4500);
  // GetOutputList()->Add(h2Labr32NaAll);

  // h2Labr32NaAll_AB = new TH2D("h2Labr32NaAll_AB",
  // 			   "gamma_gamma Spectrum, gated on #beta-decays of ^{32}Na",
  // 			   4500, 0, 4500,4500,0,4500);
  // GetOutputList()->Add(h2Labr32NaAll_AB);


  
  h1Labr21NAll = new TH1D("h1Labr21NAll",
			   "Total Labr Spectrum, gated on #beta-decays of ^{21}N",
			     3000, 0, 30000);
  GetOutputList()->Add(h1Labr21NAll);

   h1Labr24OAll = new TH1D("h1Labr24OAll",
			   "Total Labr Spectrum, gated on #beta-decays of ^{24}O",
			     3000, 0, 30000);
  GetOutputList()->Add(h1Labr24OAll);

 Detector_Vs_E_24O=new TH2D("Detector_Vs_E_24O","Detector_Vs_E_24O",3000,0,30000,16,0,16);
 GetOutputList()->Add(Detector_Vs_E_24O);

   Detector_Vs_E_21N=new TH2D("Detector_Vs_E_21N","Detector_Vs_E_21N",3000,0,30000,16,0,16);
 GetOutputList()->Add(Detector_Vs_E_21N);

 iongates_24O = new TCutG("IONGATES_24O",10);
   iongates_24O->SetVarX("PID");
   iongates_24O->SetVarY("");
   iongates_24O->SetTitle("Graph");
   iongates_24O->SetFillStyle(1000);
   iongates_24O->SetPoint(0,-971.608,312.5);
   iongates_24O->SetPoint(1,-970.888,290.625);
   iongates_24O->SetPoint(2,-971.711,268.75);
   iongates_24O->SetPoint(3,-972.893,262.5);
   iongates_24O->SetPoint(4,-973.818,271.875);
   iongates_24O->SetPoint(5,-974.023,293.75);
   iongates_24O->SetPoint(6,-973.252,309.375);
   iongates_24O->SetPoint(7,-972.07,312.5);
   iongates_24O->SetPoint(8,-971.351,312.5);
   iongates_24O->SetPoint(9,-971.608,312.5);


   iongates_21N = new TCutG("IONGATES_21N",13);
   iongates_21N->SetVarX("PID");
   iongates_21N->SetVarY("");
   iongates_21N->SetTitle("Graph");
   iongates_21N->SetFillStyle(1000);
   iongates_21N->SetPoint(0,-970.403,232.202);
   iongates_21N->SetPoint(1,-969.897,220.083);
   iongates_21N->SetPoint(2,-970.572,198.269);
   iongates_21N->SetPoint(3,-972.512,186.15);
   iongates_21N->SetPoint(4,-974.072,188.573);
   iongates_21N->SetPoint(5,-975.295,212.812);
   iongates_21N->SetPoint(6,-974.831,234.626);
   iongates_21N->SetPoint(7,-973.482,244.321);
   iongates_21N->SetPoint(8,-972.554,246.745);
   iongates_21N->SetPoint(9,-971.542,241.898);
   iongates_21N->SetPoint(10,-970.614,237.05);
   iongates_21N->SetPoint(11,-970.192,229.778);
   iongates_21N->SetPoint(12,-970.403,232.202);







  
   TString option = GetOption();

}

Bool_t labr_selector::Process(Long64_t entry)
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
   // 	     if(labr_ecal[s]>10 && labr_timecal[s]>10 &&labr_cfdfailbit[s]!=1)
   // 	       labr_Vs_time->Fill(labr_timecal[s]-dtimecal*1.0e3,labr_ecal[s]);
   // 	   }
   // 	   for(int s=0; s<13;s++){
   // 	     if(labr_ecalab[s]>10 && labr_timecalab[s]>10&&labr_cfdfailbit[s]!=1)
   // 	       labr_Vs_time_ab->Fill(labr_timecalab[s]-dtimecal*1.0e3,labr_ecalab[s]);
   // 	   }
   // 	   for(int s = 0; s < 52; s++) {
   // 	     if(labr_ecal[s]>50 && labr_cfdfailbit[s]!=1 && labr_timecal[s]>10 &&(s!=26 && s!=24 &&s!=25 && s!=27 &&s!=45 && s!=46 &&s!19 &&s!=20) /*&& coincCut->IsInside(labr_ecal[s],
   // 														  (labr_timecal[s]-*corr_dtime*1.0e6))*/){
   // 	       h1Labr32NaAll->Fill(labr_ecal[s]);
   // 	       h2E_Vs_id->Fill(labr_ecal[s],s);
   // 	       for(int p=s+1; p<52;p++){
   // 		 if(labr_ecal[p]>10 && labr_cfdfailbit[p]!=1 && labr_timecal[p]>10 &&(p!=26 && p!=24 &&p!=25  && p!=27 &&p!=45 && p!=46 &&p!=19 &&p!=20) /*&& coincCut->IsInside(labr_ecal[p],(labr_timecal[p]-*corr_dtime*1.0e6))*/){  
   // 		   h2Labr32NaAll->Fill(labr_ecal[s],labr_ecal[p]);
   // 		   h2Labr32NaAll->Fill(labr_ecal[p],labr_ecal[s]);
	       
   // 		 }
   // 	       }  
   // 	     }
   // 	   }//end_labrecal

   // 	   //  for(int s = 0; s < 13; s++) {
   // 	   //   if(labr_ecalab[s]>10 && labr_cfdfailbitab[s]!=1 && labr_timecalab[s]>10/*&&(s!=3 && s!=7)&& coincCut_ab->IsInside(labr_ecalab[s],
   // 	   // 												    (labr_timecalab[s]-*corr_dtime*1.0e6)+100)*/){
   // 	   //     h1Labr32NaAll_AB->Fill(labr_ecalab[s]);
   // 	   //     h2E_Vs_id_AB->Fill(labr_ecalab[s],s);
   // 	   //     for(int p=s+1; p<13;p++){
   // 	   // 	 if(labr_ecalab[p]>10 && labr_cfdfailbitab[p]!=1 && labr_timecalab[p]>10 /*&&(p!=3 && p!=7) && coincCut_ab->IsInside(labr_ecalab[p],
   // 	   // 													 (labr_timecalab[p]-*corr_dtime*1.0e6)+100)*/){
		
   // 	   // 	   h2Labr32NaAll_AB->Fill(labr_ecalab[s],labr_ecalab[p]);
   // 	   // 	   h2Labr32NaAll_AB->Fill(labr_ecalab[p],labr_ecalab[s]);
	      
   // 	   // 	 }
   // 	   //     }  
   // 	   //   }
   // 	   // }
   // 	   //end_labrecalab
   // 	   //	}//end_Single_Pulse
   // 	 }//end_PID_Gate
   //     }//end_half_life_gate
   //   }//end_loop_over_Implants
   // } //end_flag_Check




    bool isGoodDecay = (*corr_flag == 12);
   bool isGoodCorr = (*corr_flag == 32 // && *corr_isdecay == 1
		      );

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
	 // double Radius = sqrt(dx * dx + dy * dy);
	 // double dtimecal = *corr_dtime - implant.time;
	 for(int s=0; s<16;s++){
	   if(labr_energy[s]>100 && labr_time[s]>10 &&labr_cfdfailbit[s]!=1){

	     if (iongates_21N->IsInside(tof1, DE2)) {
	       Detector_Vs_E_21N->Fill(labr_energy[s],s);
	       h1Labr21NAll->Fill(labr_energy[s]);
	     }
	     if (iongates_24O->IsInside(tof1, DE2)) {
	       h1Labr24OAll->Fill(labr_energy[s]);
	       Detector_Vs_E_24O->Fill(labr_energy[s],s);
	     }
	     
	   }
	     
	 }

       }
     }
   }
   return kTRUE;
}

void labr_selector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void labr_selector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
TFile *outroot = new TFile("./21N_24O_labr_3_mm.root","RECREATE");
  // fOutput->FindObject("h2Sega32NaAll")->Write();
   MakeOutput("h1Labr21NAll");
   MakeOutput("h1Labr24OAll");
   MakeOutput("IONGATES_21N");
   MakeOutput("IONGATES_24O");
   MakeOutput("Detector_Vs_E_24O");
   MakeOutput("Detector_Vs_E_21N");
   // MakeOutput("h1Labr32NaAll_AB");
  // MakeOutput("h2Labr32NaAll");
  // MakeOutput("h2E_Vs_id");
  // MakeOutput("h2E_Vs_id_AB");
  // MakeOutput("h1Labr32NaAll");
  // MakeOutput("PIDhist");
  // MakeOutput("iongates");
  // MakeOutput("labr_Vs_time");
  // MakeOutput("labr_Vs_time_ab");








 
  outroot->Close();
}
