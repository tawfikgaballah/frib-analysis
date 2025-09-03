// e21062B neutron crate
// This was used to test whether dymult > 1 exists in the e21062_2 dataset. They do. 
// the main codes are in the BKP directory.

/*
 * A basic trace viewer which can be expanded to do more 
 * complicated stuff. For analysis of e21062 dumped files.
 * -- ASC 3/17/22
 *
 * This script loads files from the filepath into a chain
 * and will plot one-by-one the traces of a given run for a 
 * particluar crate, slot, and channel as a ROOT TH1.
 *
 */

// standard stuff
#include <iostream>
#include <vector>

// DDAS/NSCLDAQ
#include "ddaschannel.h"
#include "DDASEvent.h"

// ROOT fit format
#include "/projects/e21062/RSL/TemplatePrograms/eeconverter/DDASRootFitEvent.h"
#include "/projects/e21062/RSL/TemplatePrograms/eeconverter/DDASRootFitHit.h"
#include "/projects/e21062/RSL/TemplatePrograms/eeconverter/RootExtensions.h"

// ROOT includes
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TStyle.h"

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <numeric>

#include "/usr/opt/ddastoys/include/functions_analytic.h"
#include "/usr/opt/ddastoys/include/lmfit_analytic.h"






class FilterParameters {
public:
    float xdt = 0.0;
    int fast_risetime = 104;
    int fast_gap =0;
    int cfd_delay = 104;
    int cfd_scale = 3000;
    double slow_risetime = 800/4;
    double slow_gap = 608/4;
    int tau = 40/4;

  FilterParameters(float xdt_val, int fast_risetime_val, int fast_gap_val, int cfd_delay_val,
                     int cfd_scale_val, double slow_risetime_val, double slow_gap_val, int tau_val)
        : xdt(xdt_val), fast_risetime(fast_risetime_val), fast_gap(fast_gap_val),
          cfd_delay(cfd_delay_val), cfd_scale(cfd_scale_val), slow_risetime(slow_risetime_val),
          slow_gap(slow_gap_val), tau(tau_val) {}
};

class TraceHandler {
public:
    std::vector<unsigned short> trace;
    float baseline;
    
    // Constructor
    TraceHandler( std::vector<unsigned short>& trace, float baseline)
        : trace(trace), baseline(baseline) {}

    // Function to compute the sum
    double computeSum(int ilow, int ihigh) {
        double sum = 0.0;
        for (int i = ilow; i < ihigh; ++i) {
            sum += trace[i]-baseline;
        }
        return sum;
    }
};
// class Filter {
// public:
//   std::vector<float> trace;
//   std::vector<float> slow_filter;

double _compute_slow_filter(const FilterParameters& fp,  std::vector<unsigned short> trace, double baseline, int i,TraceHandler handler) {
  


  // std::cout<<"bestX"<<bestX<<'\n';
int s0=0;
int s1=0; 
int sg=0;
   
  // std::cout << "Estimated baseline: " << baseline << std::endl;
   
  // Using notation from Tan unless otherwise noted, with time in samples:
   long double b1 = std::exp(-1.0 / fp.tau);  // Ratio for geometric series sum Eq. 1.
  long double bL = std::pow(b1, fp.slow_risetime);
  long double bg = std::pow(b1, fp.slow_gap);
  // Coefficients of the inverse matrix Eq. 2 (example matrix elements given on the bottom of pg. 1542):
  long double a0 = bL / (bL - 1);
  long double ag = 1;
  long double a1 = 1 / (1 - bL);
 //  std::cout << "Ratio: " << b1 << ", coefficients: " << a0 << " " << ag << " " << a1 << std::endl; 
    int ilow = i -  2*fp.slow_risetime - fp.slow_gap + 1;
    int ihigh = ilow + fp.slow_risetime;

    if (ilow >= 0) {
      // s0 = std::accumulate(trace.begin() + ilow, trace.begin() + ihigh, 0.0)   - baseline * fp.slow_risetime;
	 s0 = handler.computeSum(ilow, ihigh);

      // s0 = std::accumulate(trace.begin() + ilow+fp.slow_risetime+.5*fp.slow_gap, trace.begin() + ihigh+fp.slow_risetime, 0.0) - baseline * fp.slow_risetime;
      // If the trailing sum is computed, compute the gap and leading sums if they do not run off the end of the trace:
      ilow = ihigh;
      ihigh = ilow + fp.slow_gap;

      // ilow = i - 0.5*fp.slow_gap + 1;
      // ihigh = i+0.5*fp.slow_gap;
    
      if (ihigh < trace.size()) {
	// sg = std::accumulate(trace.begin() + ilow, trace.begin() + ihigh, 0.0)   - baseline * fp.slow_gap;
	  
	  	 sg= handler.computeSum(ilow, ihigh);
		// std::cout<<"    "<<sg<<'\n';
      }

      ilow = ihigh;
      ihigh = ilow + fp.slow_risetime;

      // ilow = ihigh;
      // ihigh = ilow + fp.slow_risetime;

      if (ihigh < trace.size()) {
	// s1 = std::accumulate(trace.begin() + ilow, trace.begin() + ihigh, 0.0)   - baseline * fp.slow_risetime;
	  
	  	 s1 = handler.computeSum(ilow, ihigh);
		 
	// Compute the filter value if we have not run off the end of the trace for the leading sum:
		 // -((a0+a1)*bL+ag*bg)*baseline
	
	// std::cout<<slow_filter[i]<<'\n';
      }
      
      // std::cout<<s0<<"    "<<sg<<"     "<< s1<<"      "<<slow_filter[i]<<" index: "<<i*4<<'\n';
       // if (i == trace.size() / 2) {
      // 	std::cout << "Sums_A7a: " << s0 << " " << sg << " " << s1 << " filter: " << slow_filter[i] << std::endl;
      // }
      // std::cout<<"entered this loop"<<'\n';
    
    // std::cout<<slow_filter[i]<<'\n';

  


  
}
 std::cout<<"s0: "<<s0<<" sg: "<<sg<<" s1: "<<s1<<" sum: "<<a0*s0 + ag * sg+ a1 *s1<<" point: "<<i<<'\n';
   return (a0*s0 + ag * sg+ a1 *s1)/(fp.slow_gap*2);
}










TApplication* theApp; // ugh
const int clockns = 4; // ns/sample
const int overflow = 65535; // trace overflow value

int plot(std::vector<uint16_t> trace, std::vector<double> fit, std::vector<double> fit2)
{
  if(theApp==NULL) theApp = new TApplication("theApp",0,0);

  TH1D* htrace = new TH1D("Trace","Trace",trace.size(),0,trace.size());
  htrace->GetXaxis()->SetTitleSize(0.05);
  htrace->GetXaxis()->SetTitle("Sample");
  htrace->GetXaxis()->CenterTitle();
  htrace->GetYaxis()->SetTitleSize(0.05);
  htrace->GetYaxis()->SetTitle("Voltage [ADC units]");
  htrace->GetYaxis()->SetTitleOffset(1.2);
  htrace->GetYaxis()->CenterTitle();
  htrace->SetLineColor(kBlack);
  htrace->SetLineWidth(2);

  // define the fit histogram 
  TH1D* hfit = new TH1D("Fit","Fit",trace.size(),0,trace.size());
  hfit->SetLineColor(kRed);
  hfit->SetLineWidth(2);

  TH1D* hfit2 = new TH1D("Fit2","Fit2",trace.size(),0,trace.size());
  hfit2->SetLineColor(kBlue);
  hfit2->SetLineWidth(2);
  
  // fill the histograms
  for(unsigned i=0; i<trace.size(); i++) {
    htrace->Fill(i,trace[i]);
    hfit->Fill(i,fit[i]);
    hfit2->Fill(i,fit2[i]);

  }

  // draw on this canvas

//  std::unique_ptr<TCanvas> c(new TCanvas("c", "c", 800, 600)); // by RSL

  TCanvas* c = new TCanvas("c","c",800,500); 
  c->cd();
  /* c->SetLeftMargin(0.125);
  c->SetRightMargin(0.025);
  c->SetTopMargin(0.025);
  c->SetBottomMargin(0.125); */
  // display options
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
hfit2->Draw("hist");	
  htrace->Draw("hist c same");
  hfit->Draw("hist c same");
  

  theApp->Run(kTRUE);  

  delete htrace;
  delete hfit;
  delete hfit2;
  delete c;  
  
  return 0;
}

int main()
{
  // name of chain from fitted-converted data file(s)
  TChain* data = new TChain("DDASFit");

  // add the data to the chain, ymmv on how you want to do this, can wildcard
// data->Add("/mnt/analysis/e21062/sortedDataAug2023/eeconverted/run-0314-00-fitted-converted.root");
//  data->Add("/mnt/analysis/e21062/sortedData2024/eeconverted/run-1240-00-fitted-converted.root");
  data->Add("/mnt/analysis/e21062/sortedData2024/eeconverted/converted/run1382/run-1382-00-fitted.root");

  std::cout << "Input data chain has " << data->GetEntries() << " events" << std::endl;

  // data structures for iterating over the channel list and grabbing the event data
  std::vector<DDASRootFitHit*> channellist;
  std::vector<DDASRootFitHit*>::iterator channellist_it;
  std::vector<RootHitExtension>* fitdata(0);
  data->SetBranchAddress("HitFits", &fitdata);
  std::vector<Double_t> fitresult; // Vector for holding fit output
  std::vector<Double_t> fitresult2; // Vector for holding fit output

  // loop over events
  for(auto evt=0; evt<data->GetEntries(); evt++) {
    // make the event
    DDASRootFitEvent* rawhits = new DDASRootFitEvent();
    TBranch *aRawHitsevent = data->GetBranch("RawHits");
    aRawHitsevent->SetAddress(&rawhits);
    data->GetEntry(evt);
    
// make the channel list

	channellist = rawhits->GetData(); 

    // one pass to see if dynode multiplicity 1
    int dymult = 0;
    for(channellist_it = channellist.begin(); channellist_it < channellist.end(); channellist_it++) {
      int crateid = (*channellist_it)->crateid;
      int slotid = (*channellist_it)->slotid;
      int channum = (*channellist_it)->chanid;
      int id = 208*crateid + 16*(slotid-2) + channum;
      if(id == 0) {
	dymult++;
      }
    }
    
    // loop over channels in each hit, could also do with
    // actual channel vector but this is the easy way
    for(long unsigned int i = 0; i < channellist.size(); i++) {
         
      // event info
      int crateid = channellist[i]->crateid;
      int slotid = channellist[i]->slotid;
      int channum = channellist[i]->chanid;
      double energy = channellist[i]->energy;
      double time = channellist[i]->time;
      std::vector<uint16_t> trace = channellist[i]->trace;
      std::vector<double> slow_filter;		
      std::vector<uint32_t> qdcSums = channellist[i]->qdcSums;

      std::vector<RootHitExtension>& fits(*fitdata);  //???

      double dychisq_single =  0.;
      double dyE1_single = 0.;
      double dyE1real_single = 0.;
      double dyE1steepness_single = 0.;
      double dyE1decay_single = 0.;
      double dyT1_single = 0.;
      double dyoffset_single  = 0.;
  
      UInt_t iterations_single=0;      
      UInt_t fitStatus_single=0;
      
      double dychisq_double =  0.;
      double dyoffset_double  = 0.;
      double dyE1_double = 0.;
      double dyE1real_double = 0.;
      double dyE1steepness_double = 0.;
      double dyE1decay_double = 0.;
      double dyT1_double = 0.;
      double dyE2_double = 0.;
      double dyE2real_double = 0.;
      double dyE2steepness_double = 0.;
      double dyE2decay_double = 0.;
      double dyT2_double = 0.;
      UInt_t iterations_double=0;      
      UInt_t fitStatus_double=0;
      

      int id = 208*crateid + 16*(slotid-2) + channum;


//      std::cout << "trace.size(): " << trace.size() <<std::endl;
// If I do not plot anything and only print the following, I get empty, id's are only anodes
//if(qdcSums.size() > 0 && (id == 0 || id == 1))
//      std::cout << "id: " << id <<std::endl;
      
      // traces for a single channel
      if(id == 0 && trace.size() > 0) {

	// clear for each trace which might contain a fit
	fitresult.clear();
	fitresult2.clear();
	
	// some calculations based on the trace properties
	auto max = *std::max_element(trace.begin(),trace.end());

	double baseline = 0.;
	for(long unsigned int i=0; i<10; i++) {
	  baseline += trace[i];
	}

	std::cout << "baseline: "<< baseline << std::endl;

	baseline /= 10;
	double amplitude = max - baseline;

	std::cout << "amplitude: "<< amplitude << std::endl;

	double area = 0.;
	for(long unsigned int i=0; i<trace.size(); i++) {
	  area += trace[i];
	}

	std::cout << "area: "<< area << std::endl;

	area -= trace.size()*baseline;

	std::cout << "trace.size(): "<< trace.size() << std::endl;
	std::cout << "baseline: "<< baseline << std::endl;
	std::cout << "area: "<< area << std::endl;

	// retrieve dynode fit information
//	for(long unsigned int i = 0; i < fits.size(); i++) {
	  if (fits[i].haveExtension) {
	    RootFit1Info fit1 = fits[i].onePulseFit;
	    // assign single pulse fit results
	    dyE1_single = fit1.pulse.amplitude;
	    dyT1_single = fit1.pulse.position;
	    dyE1steepness_single = fit1.pulse.steepness;
	    dyE1decay_single = fit1.pulse.decayTime;      
	    dyoffset_single = fit1.offset;
	    dychisq_single = fit1.chiSquare;
	    iterations_single=fit1.iterations;      
	    fitStatus_single=fit1.fitStatus;
	    
	    RootFit2Info fit2 = fits[i].twoPulseFit;
	    // assign double pulse fit results
	    dyE1_double = fit2.pulses[0].amplitude;
	    dyT1_double = fit2.pulses[0].position;
	    dyE1steepness_double = fit2.pulses[0].steepness;
	    dyE1decay_double = fit2.pulses[0].decayTime;
	    
	    dyE2_double = fit2.pulses[1].amplitude;
	    dyT2_double = fit2.pulses[1].position;
	    dyE2steepness_double = fit2.pulses[1].steepness;
	    dyE2decay_double = fit2.pulses[1].decayTime;
	    
	    dyoffset_double = fit2.offset;	    
	    dychisq_double = fit2.chiSquare;
	    iterations_double=fit2.iterations;      
	    fitStatus_double=fit2.fitStatus;
	   
	  // real amplitdue
	  dyE1real_single = DDAS::AnalyticFit::pulseAmplitude(dyE1_single,dyE1steepness_single,
						 dyE1decay_single,dyT1_single);
	  // real amplitdue
	  dyE1real_double = DDAS::AnalyticFit::pulseAmplitude(dyE1_double,dyE1steepness_double,
						 dyE1decay_double,dyT1_double);
	  // real amplitdue
	  dyE2real_double = DDAS::AnalyticFit::pulseAmplitude(dyE2_double,dyE2steepness_double,
						 dyE2decay_double,dyT2_double);
	}

	// fit vector for easy plotting as a histogram w/o re-writing fitting functions as a TF1
	double testchisq = 0.;

     	
	for(long unsigned int i=0; i<trace.size(); i++) {
	  double f = DDAS::AnalyticFit::singlePulse(dyE1_single,dyE1steepness_single,
				       dyE1decay_single,dyT1_single,dyoffset_single,i);
	  fitresult.push_back(f);
	}
	
	for(long unsigned int i=0; i<trace.size(); i++) {
	  double f2 = DDAS::AnalyticFit::doublePulse(dyE1_double,dyE1steepness_double,
					dyE1decay_double,dyT1_double,
					dyE2_double,dyE2steepness_double,
					dyE2decay_double,dyT2_double,
					dyoffset_double,i);
	  fitresult2.push_back(f2);
	}
 

 FilterParameters fp(0.0, 104, 0, 104, 3000, 32/4,48/4,(100/4));
 

TraceHandler handler(trace, baseline);
  if(channum==0 &&crateid==0 &&max <overflow){
for(long unsigned int i=0; i<trace.size(); i++) {

   slow_filter.push_back(_compute_slow_filter(fp, trace ,baseline, i, handler));
	}





       testchisq = dychisq_double/dychisq_single;
	  
	// ignore overflows for testing purposes (this value is module dependent!)
	//	if(max < overflow && dymult == 1 &&  dyE1decay_single>0.25 && dychisq_single>100.0 ) {

	  // print the Pixie information and plot the trace and fit

	
//	std::cout << "max: " << max << std::endl;


	if(    dymult >=1 	
){ 
 

	  std::cout << "max: " << max << std::endl;
	  std::cout << "overflow: " << overflow << std::endl;

	  std::cout << "----- event information -----\n";

	  std::cout << "event : " << evt << std::endl;
	  std::cout << "dymult : " << dymult << std::endl;
/*
	  std::cout << "trace.begin() = " << *trace.begin() << std::endl;
	  std::cout << "trace.end() = " << *trace.end() << std::endl;	 

	  std::cout << "id    : " << id << std::endl;
	  std::cout << "crate : " << crateid << std::endl;
	  std::cout << "slot  : " << slotid << std::endl;
	  std::cout << "chan  : " << channum << std::endl;
	  std::cout << "channellist.size: " << channellist.size() << std::endl;*/

	  std::cout << "dynode energy: " << energy << std::endl;
	 /* std::cout << "dynode time  : " << time << std::endl;
	  std::cout << "bline : " << baseline << std::endl;
	  std::cout << "amp   : " << amplitude << std::endl;
	  std::cout << "area  : " << area << std::endl;
	  std::cout << "dychisq_double/dychisq_single : " << testchisq << std::endl;

   std::cout << "\n ======== Single Fit Information ======== " << std::endl;
	  std::cout << "dyE1_single: " << dyE1_single << std::endl;
	  std::cout << "dyT1_single: " << dyT1_single << std::endl;
	  std::cout << "dyoffset_single: " << dyoffset_single << std::endl;
	  std::cout << "dychisq_single: " << dychisq_single << std::endl;
	  std::cout << "dyE1steepness_single: " << dyE1steepness_single << std::endl;
	  std::cout << "dyE1decay_single: " << dyE1decay_single << std::endl;
	  std::cout << "dyE1real_single: " << dyE1real_single << std::endl;

   std::cout << "\n ======== Double Fit Information ======== " << std::endl;
	  std::cout << "dyE1_double: " << dyE1_double << std::endl;
	  std::cout << "dyT1_double: " << dyT1_double << std::endl;
	  std::cout << "dyE2_double: " << dyE2_double << std::endl;
	  std::cout << "dyT2_double: " << dyT2_double << std::endl;
	  std::cout << "dyoffset_double: " << dyoffset_double << std::endl;
	  std::cout << "dychisq_double: " << dychisq_double << std::endl;
	  std::cout << "dyE1steepness_double: " << dyE1steepness_double << std::endl;
	  std::cout << "dyE1decay_double: " << dyE1decay_double << std::endl;
	  std::cout << "dyE1real_double: " << dyE1real_double << std::endl;
	  std::cout << "dyE2steepness_double: " << dyE2steepness_double << std::endl;
	  std::cout << "dyE2decay_double: " << dyE2decay_double << std::endl;
	  std::cout << "dyE2real_double: " << dyE2real_double << std::endl;
   std::cout << "======================================================================" << std::endl;

*/

	  // draw it
	
	plot(trace, fitresult,slow_filter); 	
}       
	} // end overflow check and conditions for double pulse


      } // end channel check      
    } // end loop over channel list    
  } // end loop over events
  
  return 0;
}
