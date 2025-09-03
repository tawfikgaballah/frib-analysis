#include "TAnalyzer.h"

#include <iostream>
#include <vector>
#include <sys/time.h>

#include "DDASRootFitEvent.h"

#include "TFile.h"
#include "TRandom3.h"

#include "TUnpacker.h"
#include "TCorrelator.h"
#include "TModule.h"
#include "Constants.h"

using namespace ddastoys;

// Lets make sure we make an analyzer
TAnalyzer::TAnalyzer()
{
  std::cout << "Creating analyzer..." << std::endl;
}

//
// ResetChannelList
//
// Function:
//  - resets event channel vector
//
// Params:
//  - the channel list, a vector of DDAS channels
//  - the channel list iterator
//
// Return:
//  - none
//
void TAnalyzer::ResetChannelList(std::vector<DDASRootFitHit*>  channellist, std::vector<DDASRootFitHit*>::iterator channellist_it) 
{
  channellist_it = channellist.begin();
  
  for (channellist_it = channellist.begin(); channellist_it < channellist.end(); channellist_it++) 
    delete *channellist_it;
    
  channellist.clear();
}

//
// PrintChannelList
//
// Function:
//   - prints contents of the event channel vector
//
// Params:
//   - the channel list, a vector of DDAS channels
//   - the channel list iterator
//
// Return:
//   - none
//
void TAnalyzer::PrintChannelList(std::vector<DDASRootFitHit*>  channellist, std::vector<DDASRootFitHit*>::iterator channellist_it) 
{

  channellist_it = channellist.begin();

  std::cout << "Event size is " << channellist.size() << std::endl;
  
  for (channellist_it = channellist.begin(); channellist_it < channellist.end(); channellist_it++) {
    int crateid = (*channellist_it)->getCrateID();
    int slotid = (*channellist_it)->getSlotID();
    int channum = (*channellist_it)->getChannelID();
    double energy = (*channellist_it)->getEnergy();
    double time = (*channellist_it)->getTime();

    int id = chanpercrate*crateid + nchannels*(slotid-2) + channum;
 
    std::cout << (*channellist_it) << " " << crateid << " " << slotid << " " << channum << " id: " << id << " energy: " << energy << " time: " << time << std::endl;
  }
  std::cout << "----------------------------------------------" << std::endl;
	
}

//
// AnalyzeData
//
// Function:
//   - initialize parameters and variables
//   - setup random number generator
//   - map DDAS events to detectors
//   - read calibration parameters and perform calibraton
//   - correlate events
//   - fill output data structures
//
// Params:
//   - input tree of DDAS events
//   - output tree of detector events
//
// Return:
//   - none
//

template <class T> void TAnalyzer::AnalyzeData(T* tree_in, TTree* tree_out, std::string runnumber)
{
  // event info and iterator
  std::vector<DDASRootFitHit*> channellist;
  std::vector<DDASRootFitHit*>::iterator channellist_it;

  // setup variables, data sorting classes
  TBetaDecayParams bdecay;
  bdecay.Reset();
  bdecay.var.Initialize();
  TUnpacker unpacker;
  TCorrelator corr;

  // random number generator passed to Unpacker
  // ROOT for now, try and incorporate C++ std library
  // from <random> later...
  // -- ASC 2/24/22
  TRandom3 random3(0);
  
  // output for of all the results
  TROOTDataOut *rootout = new TROOTDataOut();
  rootout->Reset();

  // read calibration files
  //
  // ----- examples -----
  bdecay.var.pspmthigh1.ReadCalFile("/user/e23055/asc/betasort/cal/PSPMTHighInit.txt");
  bdecay.var.pspmthigh2.ReadCalFile("/user/e23055/asc/betasort/cal/PSPMTHighInit.txt");     
  bdecay.var.pspmtlow1.ReadCalFile("/user/e23055/asc/betasort/cal/PSPMTLowInit.txt");
  bdecay.var.pspmtlow2.ReadCalFile("/user/e23055/asc/betasort/cal/PSPMTLowInit.txt");

  bdecay.var.NpspmtCeBr.ReadCalFile("/user/e23055/asc/betasort/cal/NpspmtCeBrInit.txt");

  bdecay.var.pin01.ReadCalFile("/user/e23055/asc/betasort/cal/PIN01Init.txt");
  bdecay.var.pin02.ReadCalFile("/user/e23055/asc/betasort/cal/PIN02Init.txt");
  //bdecay.var.clover.ReadCalFile("/projects/e23055/OfflineAnalysis/rootAnalysisFinal/cal/CloverInit.txt");
  bdecay.var.clover.ReadCalFile("/user/e23055/asc/betasort/cal/CloverInit.txt");
  bdecay.var.labr.ReadCalFile("/user/e23055/asc/betasort/cal/LaBr3Init.txt");

  std::cout << "---> Anode-dynode 1 CeBr coincidence window: " << bdecay.var.NpspmtCeBr.dycoincwindow << " ns" << std::endl;
  
  double starttime = 0.;
  double endtime = 0.;

  // make the relevant output stuff in the tree
  tree_out->Branch("rootout", "TROOTDataOut", &rootout, 32000, 99);
  // adding Implant branch
  tree_out->Branch("implantlist",&implantlist,32000,99);


	//____________________________________________________________________
	//
	// Get TOF Offset & dE Scaling 

	// First, need to get the values
	Double_t TOFoffset = 0.;
	Double_t deScale = 1.;

	std::ifstream pidcorr;
	pidcorr.open("/user/e23055/asc/betasort/pid_corr.txt");
	if(pidcorr.is_open()){
		bool flag = false;
		while(!pidcorr.eof()){
			char temp[10];
			pidcorr >> temp;		
			// Encounters # "comment" delimiter
			if(temp[0] == '#'){
				pidcorr.ignore(1000, '\n');
				continue;
			}
			else if(std::stof(temp) == std::stof(runnumber)){
				flag = true;
				pidcorr >> temp;
				TOFoffset = std::stof(temp); // temp, convert to double
				pidcorr >> temp;
				deScale = std::stof(temp); // temp, convert to double
				break;
			}
		}
		
		if(flag == false){
			//std::cout << "Error: No PID Correction found for run " << runnumber << ". Exiting." << std::endl;
			//std::exit(EXIT_FAILURE);
			std::cout << "Warning: No PID Correction found for run " << runnumber << ". Setting TOF offset = 0 and deScale = 1." << std::endl;
		}
		
		else{
			std::cout << "Found PID corrections. TOF offset = " << TOFoffset << " and deScale = " << deScale << std::endl;
		}
		
	}
	else{
	  //std::cout << "Error: PID Corrections file not open. Exiting." << std::endl;
		std::cout << "Warning: No PID Correction found for run " << runnumber << ". Setting TOF offset = 0 and deScale = 1." << std::endl;	
		//std::exit(EXIT_FAILURE);
	}

	//
	// END Get TOF Offset & dE Scaling
	// ___________________________________________________________________  

  // find the number of events in a file
  auto nevents = tree_in->GetEntries();
  std::cout << "Number events in run segment: " << tree_in->GetEntries() << std::endl;

  // where to find the fit information
  //std::vector<RootHitExtension>* fitdata(0);
  //tree_in->SetBranchAddress("HitFits", &fitdata);

  // built event raw data
  DDASRootFitEvent *rawhits;

  // progress tracking
  timeval tvelapsed_c, tvelapsed_o;
  gettimeofday (&tvelapsed_o, NULL);
  Long64_t eventcounter = 0;
  
  // loop over the events
  /********* Forward correlation ********/

  for(auto evt = 0; evt < nevents; evt++) {
      // reset data structures and hit variables for the new event
    ResetChannelList(channellist,channellist_it);
    rootout->Reset();
    bdecay.Reset();
      
    // progress bar -- forward direction
    if(evt > 0 && (evt % (int)(nevents * 0.01)) == 0) {
	gettimeofday (&tvelapsed_c, NULL);
	
	double rate = eventcounter/(((tvelapsed_c.tv_sec+tvelapsed_c.tv_usec/1.e6)-(tvelapsed_o.tv_sec+tvelapsed_o.tv_usec/1.e6)));

	double remaining = (nevents - evt) / rate / 60;


std::cout << "Processed " << evt << " events. " << (int)(evt/(int)(nevents*0.01)) << "% done. Current rate: " << rate << " events per second. Estimated time remaining: " << remaining << " minutes.\r" << std::flush;
    
      	gettimeofday (&tvelapsed_o, NULL);
      	eventcounter=0;
    }

    //  check with only 1% of the file
    // if(evt > 0 && (evt % (int)(nevents * 0.01)) == 0) {
    //   break;
    // }

    // // check with only 5% of the file
    // if(evt > 0 && (evt % (int)(nevents * 0.05)) == 0) {
    // 	break;
    // }

    /**************************************/

 // Forward correlation ends   

      /******** Reverse correlation ********/
/* 
       for (auto evt=nevents-1; evt>=0; evt--){
         

           // Reset data structures and hit variables for the new event
           ResetChannelList(channellist,channellist_it);
           rootout->Reset();
           bdecay.Reset();
  
           // Progress bar -- reverse correlation
           if(evt > 0 && ((nevents-evt) % (int)(nevents * 0.01)) == 0) {
  
       		gettimeofday (&tvelapsed_c, NULL);

		double rate = eventcounter/(((tvelapsed_c.tv_sec+tvelapsed_c.tv_usec/1.e6)-(tvelapsed_o.tv_sec+tvelapsed_o.tv_usec/1.e6)));
		double remaining = evt / rate / 60;

		std::cout << "Processed " << nevents - evt << " events. " << 100-(int)(evt/(int)(nevents*0.01)) << "% done. Current rate: " << rate << " events per second. Estimated time remaining: " << remaining << " minutes.\r" << std::flush;
      
       		gettimeofday (&tvelapsed_o, NULL);
       		eventcounter=0;
           }  */
	
 // reverse correlation ends

    // make the event
    rawhits = new DDASRootFitEvent();
    //std::cout << "made event\n";

    // Built raw event location in input tree
    TBranch *addasevent = tree_in->GetBranch("RawHits");
    addasevent->SetAddress(&rawhits);
        
    // Get the event
    tree_in->GetEntry(evt);
    //std::cout << "GET ENTRY " << evt << std::endl;

    // Hits with fit information have an extension which indicates
    // that there is associated fit info present
    //std::vector<RootHitExtension>& fits(*fitdata);      

    // set the vector of channels hit in this event
    channellist = rawhits->GetData();
    //PrintChannelList(channellist,channellist_it);
    
    // Now that we have the vector of channels, we need to unpack it into
    // bdecay classes. Iterate over the channellist, extract some basic information,
    // and send it to the channel mapper.
    int eventsize = channellist.size();

    // don't bother doing anything if the event is empty
    // introduced when making TChain out of entire run
    if(eventsize > 0) {
      bdecay.ddasdiagnostics.cmult = eventsize;

      channellist_it = channellist.begin();

      double previous_time = 0;

      // first pass through for only the dynodes
      // inefficient but we want the dynode time set first to reference other detectors to it
      for (long unsigned int i = 0; i < channellist.size(); i++) {
	int crateid = channellist[i]->getCrateID();
	int slotid = channellist[i]->getSlotID();
	int channum = channellist[i]->getChannelID();
	double current_time = channellist[i]->getTime(); // in ns

	int id = chanpercrate*crateid + nchannels*(slotid-2) + channum;

	// update the current time for each entry
	bdecay.clock.current = current_time;

	if(id == 0) { // NpspmtCeBr 1 

	  // fill arrays with dynode hits
	  if(bdecay.NpspmtCeBr.dymult < 16) {	
	    bdecay.NpspmtCeBr.dyenergies[bdecay.NpspmtCeBr.dymult] = channellist[i]->getEnergy();
	    bdecay.NpspmtCeBr.dytimes[bdecay.NpspmtCeBr.dymult] = channellist[i]->getTime();		
	    bdecay.NpspmtCeBr.dymult++; // increment dymult *after* using it above	  
	  } else {
	    std::cout << "More than 16 PSPMT 1 high gain dynode triggers in in event " << evt << std::endl;
	  }  

	    unpacker.UnpackChannel(id, random3, channellist[i], bdecay, i);

	 
	    // std::vector<UShort_t> tmp = channellist[i]->getTrace();
	    // bdecay.NpspmtCeBr.dytrace.insert(bdecay.NpspmtCeBr.dytrace.end(), tmp.begin(), tmp.end());

	} // end dynode address check
      } // end first pass over channel list
      
      // loop over entires a second time for non-reference-dynode events
      for (channellist_it = channellist.begin(); channellist_it < channellist.end(); channellist_it++) {
	int crateid = (*channellist_it)->getCrateID();
	int slotid = (*channellist_it)->getSlotID();
	int channum = (*channellist_it)->getChannelID();
	double current_time = (*channellist_it)->getTime(); // in ns

	int id = chanpercrate*crateid + nchannels*(slotid-2) + channum;
	
	// the time of an event will be taken as the time of the first channel in the event.     
	if(channellist_it == channellist.begin()) {
	  starttime = current_time;
	  previous_time = current_time;
	  bdecay.clock.initial = current_time;
	}
	if(channellist_it == channellist.end()-1)
	  endtime = current_time;
	  
	// time difference between events starting after the first one
	// can be 0 but cannot exceed event builder window
	bdecay.ddasdiagnostics.tdiffevent = current_time-previous_time; // in ns
	previous_time = current_time;
		
	// update the current time for each entry
	bdecay.clock.current = current_time;

	// unpack NpspmtCeBr anode channel data
	if(id >=416 && id < 672 // && (bdecay.NpspmtCeBr.dyenergy.size()>0)
	   ) { 
	  unpacker.UnpackChannel(id, random3, (*channellist_it), bdecay, 0);
	}


	// unpack the rest channel data
	else if((id != 0) && !(id >=416 && id < 672)) { // neither the dynodes nor any anodes hit.
	 unpacker.UnpackChannel(id, random3, (*channellist_it), bdecay, 0);
	}
      } // end loop over event channel list (unpacking stage)

      bdecay.ddasdiagnostics.eventlength = endtime - starttime; // in ns
    
      /********************************************************************************
       *                                                                              *
       * Event level processing goes here                                             *
       * PID, TOF timing, analysis before writing, application of correction factors, * 
       * addback multiplicity and time, etc.                                          *
       *                                                                              *
       ********************************************************************************/      
      // if dynode hit and all anodes have a signal set PSPMT hit flag and determine interaction position
      // NpspmtCeBr 2 high gain
      // if(bdecay.NpspmtCeBr.dyhit == 1 && bdecay.NpspmtCeBr.amult > 0) {
      // 	bdecay.NpspmtCeBr.hit = 1;
      	// fit the 2D anode energy distribution
      	bdecay.NpspmtCeBr.FitAnodePosition();
      // }

      if(bdecay.xpin1.hit == 1) { bdecay.pid.de1 = bdecay.xpin1.ecal; }
      // Scaling de2 energy only right now to match run by run
      if(bdecay.xpin2.hit == 1) { bdecay.pid.de2 = bdecay.xpin2.ecal*deScale; }
      // Add TOFoffset here ... instead of in new branch
      //if(bdecay.SIPMT.hit == 1 && bdecay.SCLT.hit == 1) { bdecay.pid.tof = (bdecay.SIPMT.time - bdecay.SCLT.time + TOFoffset); }
      if(bdecay.SIPMT.hit == 1 && bdecay.DB3SLT.hit == 1) { bdecay.pid.tof = (bdecay.SIPMT.time - bdecay.DB3SLT.time + TOFoffset); }
	//if(bdecay.xscintT.hit == 1 && bdecay.DB3PPACDAnT.hit == 1) { bdecay.pid.tof = (bdecay.xscintT.time - bdecay.DB3PPACDAnT.time + TOFoffset); }



      /******************************
       * End event level processing *
       ******************************/

      // clear out list of implants in correlator before correlating
      corr.clearImplants();
           
      // correlate this event.
      if(corr.Correlate(bdecay))
      	std::cout << "Bad correlation event " << evt << std::endl;

      // Clear out vector used for storing implant values before writing
      implantlist.clear();      
      // Fill the implant vector
      implantlist = corr.getImplants();

      // Sort Implants so that latest times are first
      std::sort(implantlist.begin(), implantlist.end(), sortTime);
      
      // put selected data into root structure for write.
      rootout->SetOutputValues(bdecay);

//      if( (bdecay.pspmthigh2.dyenergy.size()>0) || (bdecay.pspmtlow2.dyenergy.size()>0) )     // This condition I do not like, only (bdecay.pspmthigh2.dyenergy.size()>0)  gives me expected evts
      //if( (bdecay.corr.isimplant==1) || (bdecay.corr.isdecay==1) ) 
	//if( bdecay.pspmthigh1.dyenergy.size()>0){tree_out->Fill();}
      	
	// conditions go here e.g. only events with PSPMT
    // 	if( /* (bdecay.corr.isimplant==1) || (bdecay.corr.isdecay==1) ||*/ (bdecay.corr.iscloveronly==1) ||  bdecay.NpspmtCeBr.dyenergy.size()>0) {

		//std::cout << "Filling tree..." << std::endl;

		tree_out->Fill(); 

	//}
	//tree_out->Fill();      

      eventcounter++;
    } // End eventsize > 0 check
  } // End loop over the events

}

//Since only member functions are template need to specify inputs
template void TAnalyzer::AnalyzeData<TTree>(TTree* tree_in, TTree* tree_out, std::string runnumber);
template void TAnalyzer::AnalyzeData<TChain>(TChain* tree_in,TTree* tree_out,std::string runnumber);
