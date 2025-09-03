#define test1_cxx
// The class definition in test1.h has been generated automatically
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
// root> T->Process("test1.C")
// root> T->Process("test1.C","some options")
// root> T->Process("test1.C+")
//


#include "test1.h"
#include <TH2.h>
#include <TStyle.h>

void test1::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();
}

void test1::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).


 // coincCut = (TCutG*)inroot3->Get("blob1"); 

 clover_Vs_time = new TH2D("clover_Vs_time",
			   "corrdtime-clover_time_Vs_clover_energy",
			   4500, 0, 4500,2000,0,2000);
  GetOutputList()->Add(clover_Vs_time);
  clover_Vs_time_ab = new TH2D("clover_Vs_time_ab",
			   "corrdtime-clover_timeab_Vs_clover_energyab",
			   4500, 0, 4500,2000,0,2000);
  GetOutputList()->Add(clover_Vs_time_ab);

  h2Clover32NaAll = new TH2D("h2Clover32NaAll",
			   "gamma_gamma Spectrum, gated on #beta-decays of ^{32}Na",
			   4500, 0, 4500,4500,0,4500);
  GetOutputList()->Add(h2Clover32NaAll);
  h2E_Vs_id = new TH2D("h2E_Vs_id",
			   "Clover_Energy_Vs_Detector_ID",
			   4500, 0, 4500,52,0,52);
  GetOutputList()->Add(h2E_Vs_id);
  h2E_Vs_id_AB = new TH2D("h2E_Vs_id_AB",
			   "Clover_Energy_Vs_Detector_ID_AB",
			   4500, 0, 4500,13,0,13);
  GetOutputList()->Add(h2E_Vs_id_AB);

  h1Clover32NaAll = new TH1D("h1Clover32NaAll",
			   "Total Clover Spectrum, gated on #beta-decays of ^{32}Na",
			   4500, 0, 4500);
  GetOutputList()->Add(h1Clover32NaAll);



  h2Clover32NaAll_AB = new TH2D("h2Clover32NaAll_AB",
			   "gamma_gamma Spectrum, gated on #beta-decays of ^{32}Na",
			   4500, 0, 4500,4500,0,4500);
  GetOutputList()->Add(h2Clover32NaAll_AB);


  PIDhist = new TH2D("PIDhist",
		     "gamma_gamma Spectrum, gated on #beta-decays of ^{32}Na",
		     8000,-300,-200,8000,0,8000 );
  GetOutputList()->Add(PIDhist);

  h1Clover32NaAll_AB = new TH1D("h1Clover32NaAll_AB",
				"Total Clover Spectrum, gated on #beta-decays of ^{32}Na",
				4500, 0, 4500);
  GetOutputList()->Add(h1Clover32NaAll_AB);

  
  iongates = new TCutG("iongates",9);
  GetOutputList()->Add(iongates);
  coincCut = new TCutG("coincCut",12);
  coincCut_ab = new TCutG("coincCut_ab",14);
  TString option = GetOption();

}

Bool_t test1::Process(Long64_t entry)
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

  fReader.SetEntry(entry);

 
  if(*corr_flag==32){
    for(unsigned int j=0; j<implantlist->size(); j++) {
      double tof1 = implantlist->at(j).tof;
      double DE2 = implantlist->at(j).de2;
      double implantTime = implantlist->at(j).time;
      double dtimecal = abs(implantTime-*corr_dtime);
      if( abs(dtimecal)>0 && abs(dtimecal)<39){
	cout<<*corr_itime<<'\n';
	iongates->SetVarX("tof1");
	iongates->SetVarY("DE2");
	iongates->SetTitle("Graph");
	iongates->SetFillStyle(1000);
	iongates->SetPoint(0,-250.847,2836.03);
	iongates->SetPoint(1,-251.955,2643.72);
	iongates->SetPoint(2,-251.782,2585);
	iongates->SetPoint(3,-248.566,2542.51);
	iongates->SetPoint(4,-247.98,2810.94);
	iongates->SetPoint(5,-249.674,2875.79);
	iongates->SetPoint(6,-250.912,2805.67);
	iongates->SetPoint(7,-250.912,2805.67);
	iongates->SetPoint(8,-250.847,2836.03);



	coincCut->SetVarX("clover_ecal[s]");
	coincCut->SetVarY("clover_timecal[s]-*corr_dtime*1.0e6");
	coincCut->SetTitle("coincCut");
	coincCut->SetFillStyle(1000);
	coincCut->SetPoint(0,4493.04,190.333);
	coincCut->SetPoint(1,15.6491,187);
	coincCut->SetPoint(2,2.60816,750.333);
	coincCut->SetPoint(3,680.738,407);
	coincCut->SetPoint(4,841.576,595.333);
	coincCut->SetPoint(5,1341.48,355.333);
	coincCut->SetPoint(6,1432.77,640.333);
	coincCut->SetPoint(7,1741.4,337);
	coincCut->SetPoint(8,2932.48,262);
	coincCut->SetPoint(9,4501.74,190.333);
	coincCut->SetPoint(10,4601.72,195.333);
	coincCut->SetPoint(11,4493.04,190.333);




	coincCut_ab->SetVarX("clover_ecalab[s]");
	coincCut_ab->SetVarY("clover_timecalab[s]-*corr_dtime*1.0e6");
	coincCut_ab->SetTitle("coincCut_ab");
	coincCut_ab->SetFillStyle(1000);
	coincCut_ab->SetPoint(0,4484.35,189.663);
	coincCut_ab->SetPoint(1,6.95511,191.942);
	coincCut_ab->SetPoint(2,15.6491,634.051);
	coincCut_ab->SetPoint(3,589.451,426.67);
	coincCut_ab->SetPoint(4,732.902,530.361);
	coincCut_ab->SetPoint(5,1267.58,369.697);
	coincCut_ab->SetPoint(6,1428.42,537.197);
	coincCut_ab->SetPoint(7,2089.16,289.935);
	coincCut_ab->SetPoint(8,2549.94,293.354);
	coincCut_ab->SetPoint(9,3306.32,258.031);
	coincCut_ab ->SetPoint(10,4484.35,189.663);
	coincCut_ab->SetPoint(11,4540.86,185.105);
	coincCut_ab->SetPoint(12,4527.82,188.524);
	coincCut_ab->SetPoint(13,4484.35,189.663);
	//Na33
	// iongates->SetPoint(0,-247.132,2825.91);
	// iongates->SetPoint(1,-245.959,2937.25);
	// iongates->SetPoint(2,-244.135,2937.25);
	// iongates->SetPoint(3,-243.418,2785.43);
	// iongates->SetPoint(4,-244.982,2583);
	// iongates->SetPoint(5,-246.676,2583);
	// iongates->SetPoint(6,-247.328,2704.45);
	// iongates->SetPoint(7,-247.002,2856.28);
	// iongates->SetPoint(8,-247.132,2825.91);

	//Mg32


	// iongates->SetPoint(0,-262.82,2741.61);
	// iongates->SetPoint(1,-262.614,2896.55);
	// iongates->SetPoint(2,-261.478,2989.51);
	// iongates->SetPoint(3,-260.136,2997.26);
	// iongates->SetPoint(4,-259.62,2881.05);
	// iongates->SetPoint(5,-259.93,2764.85);
	// iongates->SetPoint(6,-261.169,2710.62);
	// iongates->SetPoint(7,-262.201,2733.86);
	// iongates->SetPoint(8,-262.82,2741.61);


      
	PIDhist->Fill(tof1,DE2);
	bool isPspmtMultGood = false;
	if(*pspmtlow1_amult > PSPMTMULT) isPspmtMultGood = true; 

	// bool isIonMultGood = false;
	// if(*corr_islightion > PSPMTMULT) isIonMultGood = true; 
	bool isSinglePulse = true;
	if((*pspmthigh1_dychisq_double)/(*pspmthigh1_dychisq_single) < (1.0/10.0)) isSinglePulse=false;
	// dynode fit energy < cut-off
	bool isEnergyLess = false;
	if(isSinglePulse && *pspmtlow1_dyE1real_single < DYEHIGH) isEnergyLess = true;
	// dynode fit energy > 2000
	bool isEnergyMore = false;
	if(isSinglePulse && *pspmtlow1_dyE1real_single > DYELOW) isEnergyMore = true; 

	// if(*corr_flag == 32) { // Don't bother looping unless the flag is good
	//   if(isSinglePulse /*&& (isEnergyLess && isEnergyMore)  && isPspmtMultGood
	//  && isIonMultGood*/){

     

      
	if(iongates&& iongates->IsInside(tof1,DE2) ){

	  for(int s=0; s<52;s++){
	    if(clover_ecal[s]>10 && clover_timecal[s]>10 &&clover_cfdfailbit[s]!=1)
	      clover_Vs_time->Fill(clover_ecal[s],clover_timecal[s]*1.0e-6-dtimecal);
	  }
	  for(int s=0; s<13;s++){
	    if(clover_ecalab[s]>10 && clover_timecalab[s]>10&&clover_cfdfailbit[s]!=1)
	      clover_Vs_time_ab->Fill(clover_ecalab[s],clover_timecalab[s]*1.0e-6-dtimecal);
	  }
	  for(int s = 0; s < 52; s++) {
	    if(clover_ecal[s]>50 && clover_cfdfailbit[s]!=1 && clover_timecal[s]>10 &&(s!=19 && s!=12 && s!=13 && s!=14 && s!=15 && s!=28 && s!=29 && s!=30 && s!=31 &&s!=18)/* && coincCut->IsInside(clover_ecal[s],
																						(clover_timecal[s]-*corr_dtime*1.0e6))*/){
	      h1Clover32NaAll->Fill(clover_ecal[s]);
	       h2E_Vs_id->Fill(clover_ecal[s],s);
	      for(int p=s+1; p<52;p++){
		if(clover_ecal[p]>10 && clover_cfdfailbit[p]!=1 && clover_timecal[p]>10 &&(p!=19 && p!=12 && p!=13 && p!=14 && p!=15 && p!=28 && p!=29 && p!=30 && p!=31 &&p!=18) /*&& coincCut->IsInside(clover_ecal[p],(clover_timecal[p]-*corr_dtime*1.0e6))*/){  
		  h2Clover32NaAll->Fill(clover_ecal[s],clover_ecal[p]);
		  h2Clover32NaAll->Fill(clover_ecal[p],clover_ecal[s]);
	       
		}
	      }  
	    }
	  }//end_cloverecal

	  for(int s = 0; s < 13; s++) {
	    if(clover_ecalab[s]>10 && clover_cfdfailbitab[s]!=1 && clover_timecalab[s]>10&&(s!=3 && s!=7)/*&& coincCut_ab->IsInside(clover_ecalab[s],
													   (clover_timecalab[s]-*corr_dtime*1.0e6)+100)*/){
	      h1Clover32NaAll_AB->Fill(clover_ecalab[s]);
	       h2E_Vs_id_AB->Fill(clover_ecalab[s],s);
	      for(int p=s+1; p<13;p++){
		if(clover_ecalab[p]>10 && clover_cfdfailbitab[p]!=1 && clover_timecalab[p]>10 &&(p!=3 && p!=7)/*&& coincCut_ab->IsInside(clover_ecalab[p],
														(clover_timecalab[p]-*corr_dtime*1.0e6)+100)*/){
		
		  h2Clover32NaAll_AB->Fill(clover_ecalab[s],clover_ecalab[p]);
		  h2Clover32NaAll_AB->Fill(clover_ecalab[p],clover_ecalab[s]);
	      
		}
	      }  
	    }
	  }//end_cloverecalab
	  //	}//end_Single_Pulse
	}//end_PID_Gate
       }//end_half_life_gate
    }//end_loop_over_Implants
  } //end_flag_Check
  
  return kTRUE;
}

void test1::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void test1::Terminate()
{
  TFile *outroot = new TFile("./summed_Gated_39ms_Excluded_test.root","RECREATE");
  // fOutput->FindObject("h2Sega32NaAll")->Write();
  MakeOutput("h2Clover32NaAll_AB");
  MakeOutput("h1Clover32NaAll_AB");
  MakeOutput("h2Clover32NaAll");
  // MakeOutput("h2E_Vs_id");
  // MakeOutput("h2E_Vs_id_AB");
  MakeOutput("h1Clover32NaAll");
  MakeOutput("PIDhist");
  MakeOutput("iongates");
  // MakeOutput("clover_Vs_time");
  // MakeOutput("clover_Vs_time_ab");

  outroot->Close();
  
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

}
