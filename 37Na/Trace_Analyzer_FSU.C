#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>





// ROOT includes
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TFile.h"

TApplication* theApp=nullptr; // ugh
const int clockns = 4; // ns/sample
//const int overflow = 65535; // trace overflow value
const int overflow = 15999;
int plot(std::vector<uint16_t> trace, std::vector<double> fit, std::vector<double> fit2, double baseline, double trigger, double trigger_filter)
{
 
  TH1D* htrace = new TH1D("Trace","Trace",trace.size(),0,trace.size()*4);
  htrace->GetXaxis()->SetTitleSize(0.05);
  htrace->GetXaxis()->SetTitle("Sample");
  htrace->GetXaxis()->CenterTitle();
  htrace->GetYaxis()->SetTitleSize(0.05);
  htrace->GetYaxis()->SetTitle("Voltage [ADC units]");
  htrace->GetYaxis()->SetTitleOffset(1.2);
  htrace->GetYaxis()->CenterTitle();
  htrace->SetLineColor(kBlack);
  htrace->SetLineWidth(2);

  // // define the fit histogram 
  // TH1D* hfit = new TH1D("Fit","Fit",trace.size(),0,trace.size());
  // hfit->SetLineColor(kRed);
  // hfit->SetLineWidth(2);

  TH1D* hfit2 = new TH1D("Filter","Filter",trace.size(),0,trace.size()*4);
  hfit2->SetLineColor(kBlue);
  hfit2->SetLineWidth(2);
  
  // fill the histograms
  for(unsigned i=0; i<trace.size(); i++) {
    htrace->Fill(i*4-trigger*4+100,trace[i]-baseline);
    // hfit->Fill(i,fit[i]);
    hfit2->Fill(i*4-trigger_filter*4+100,fit2[i]/10);

  }

  // draw on this canvas

  //  std::unique_ptr<TCanvas> c(new TCanvas("c", "c", 800, 600)); // by RSL

  TCanvas* c = new TCanvas("c","c",800,500); 
  c->cd();
  c->SetLeftMargin(0.125);
  c->SetRightMargin(0.025);
  c->SetTopMargin(0.025);
  c->SetBottomMargin(0.125);
  // display options
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

   hfit2->Draw("hist");    
  htrace->Draw("hist c same");

  gSystem->ProcessEvents();

  c->WaitPrimitive();
// Pause to display the canvas until user closes it
     if (theApp) theApp->Run();
    
  delete htrace;
  // delete hfit;
  delete hfit2;
  delete c;  
  
  return 0;
}





void rebin(std::vector<uint16_t>& data, std::size_t binSize) {
  if (binSize == 0) {
    throw std::invalid_argument("Bin size must be greater than 0");
  }

  std::size_t newSize = (data.size() + binSize - 1) / binSize;
  std::vector<double> rebinned(newSize, 0);

  // Rebin the data
  for (std::size_t i = 0; i < data.size(); ++i) {
    rebinned[i / binSize] += data[i];
  }

  // Resize the original vector and copy the rebinned data back into it
  data.resize(newSize);
  for (std::size_t i = 0; i < newSize; ++i) {
    data[i] = rebinned[i];
  }
}



class FilterParameters {
public:
  float xdt;
  int fast_risetime;
  int fast_gap;
  int cfd_delay;
  int cfd_scale;
  double slow_risetime;
  double slow_gap;
  int tau;

  FilterParameters(float xdt_val, int fast_risetime_val, int fast_gap_val, int cfd_delay_val,
		   int cfd_scale_val, double slow_risetime_val, double slow_gap_val, int tau_val)
    : xdt(xdt_val), fast_risetime(fast_risetime_val), fast_gap(fast_gap_val),
      cfd_delay(cfd_delay_val), cfd_scale(cfd_scale_val), slow_risetime(slow_risetime_val),
      slow_gap(slow_gap_val), tau(tau_val) {}
};

class TraceHandler {
public:
  std::vector<uint16_t> trace;
  float baseline;

  TraceHandler(std::vector<uint16_t>& trace, float baseline)
    : trace(trace), baseline(baseline) {}

  double computeSum(int ilow, int ihigh) {
    double sum = 0.0;
    for (int i = ilow; i < ihigh; ++i) {
      sum += trace[i] - baseline;
    }
    return sum;
  }
};

double _compute_slow_filter(const FilterParameters& fp, std::vector<uint16_t>& trace, double baseline, int i, TraceHandler& handler) {
  double s0 = 0, s1 = 0, sg = 0;

  double b1 = std::exp(-1.0 / fp.tau);
  double bL = std::pow(b1, fp.slow_risetime);
  double bg = std::pow(b1, fp.slow_gap);
  double a0 = bL / (bL - 1);
  double ag = 1;
  double a1 = 1 / (1 - bL);

  int ilow = i - 2 * fp.slow_risetime - fp.slow_gap + 1;
  int ihigh = ilow + fp.slow_risetime;

  if (ilow >= 0) {
    s0 = handler.computeSum(ilow, ihigh);
    ilow = ihigh;
    ihigh = ilow + fp.slow_gap;

    if (ihigh < trace.size()) {
      sg = handler.computeSum(ilow, ihigh);
    }

    ilow = ihigh;
    ihigh = ilow + fp.slow_risetime;

    if (ihigh < trace.size()) {
      s1 = handler.computeSum(ilow, ihigh);
    }
  }
  return (a0 * s0 + ag * sg + a1 * s1);
}

// void displayProgressBar(float progress) {
//   int barWidth = 70;
//   std::cout << "[";
//   int pos = barWidth * progress;
//   for (int i = 0; i < barWidth; ++i) {
//     if (i < pos) std::cout << "=";
//     else if (i == pos) std::cout << ">";
//     else std::cout << " ";
//   }
//   std::cout << "] " << int(progress * 100.0) << " %\r";
//   std::cout.flush();
// }

void Trace_Analyzer_FSU() {
  if (!gApplication) {
    int argc = 0;
    char** argv = nullptr;
    theApp = new TApplication("theApp", &argc, argv);
  }
  
  TChain* data = new TChain("sorted_data");
  data->Add("run-0268-sorted-*.root");

  // int slow_rise_parameters[] = {48,108,208,308,408,508,608};
  // int slow_gap_parameters[] = {48,52,56,60,64,68,72};
  // int tau_parameters[] = {4, 8, 12, 16, 20, 32, 40};

  int slow_rise_parameters[] = {108};
  int slow_gap_parameters[] = {64};
  int tau_parameters[] = {20};

  int size_slow_rise = sizeof(slow_rise_parameters) / sizeof(slow_rise_parameters[0]);
  int size_slow_gap = sizeof(slow_gap_parameters) / sizeof(slow_gap_parameters[0]);
  int size_tau = sizeof(tau_parameters) / sizeof(tau_parameters[0]);

  TH1F* hE = new TH1F("hE", "hE", 10000, 0, 100000);
  TH2F* hE_2D = new TH2F("hE_2D", "hE_2D", 7000, 0, 70000,7000,0,70000);
  TH2D* Map=new TH2D("map", "map", 20,0,20,20,0,20);
  TH1F* hE_offline[size_slow_rise][size_slow_gap][size_tau];

  for (int l = 0; l < size_slow_rise; ++l) {
    for (int m = 0; m < size_slow_gap; ++m) {
      for (int n = 0; n < size_tau; ++n) {
	hE_offline[l][m][n] = new TH1F(Form("hE_offline_L=%i_G=%i_Tau=%i", slow_rise_parameters[l], slow_gap_parameters[m], tau_parameters[n]),
				       Form("hE_offline_L=%i_G=%i_Tau=%i", slow_rise_parameters[l], slow_gap_parameters[m], tau_parameters[n]),
				       10000, 0, 100000);
      }
    }
  }

  TFile* output = new TFile("output_run268_test.root", "RECREATE");
  std::cout << "Input data chain has " << data->GetEntries() << " events" << std::endl;


  std::vector<unsigned short> *trace=nullptr;
  data->SetBranchAddress("trace", &trace);
 

  int totalEntries = data->GetEntries()*1;

  // Improved main loop and trace handling
  data->SetBranchAddress("trace", &trace);

  for (int evt = 0; evt <= totalEntries; ++evt) {
    data->GetEntry(evt);
    if (!trace || trace->empty()) continue;

    std::vector<unsigned short> trace_data = *trace;
    std::vector<double> slow_filter, fitresult, fitresult2;

    // Compute baseline
    double baseline = 0.;
    int baserange = 10;
    rebin(trace_data, 1);
    for (size_t i = 0; i < baserange; i++) {
      baseline += trace_data[i];
    }
    baseline /= baserange;

    // Perform trace handling and filtering
    TraceHandler handler(trace_data, baseline);
    int bestX = std::distance(trace_data.begin(), std::max_element(trace_data.begin(), trace_data.end()));
    double bestY = trace_data[bestX];
    int targetY = 0.25 * (bestY - baseline);

    int trigger = 0;
    bool found = false;
    for (size_t j = 0; j < trace_data.size(); j++) {
      int y = trace_data[j] - baseline;
      if (y >= targetY) {
    	trigger = j;
    	found = true;
    	break;
      }
    }

    
    if (found) {
      for (int l = 0; l < size_slow_rise; l++) {
    	for (int m = 0; m < size_slow_gap; m++) {
    	  for (int n = 0; n < size_tau; n++) {
    	    FilterParameters fp(0.0, 104, 0, 104, 3000, slow_rise_parameters[l] / 4,
    				slow_gap_parameters[m] / 4, tau_parameters[n] / 4);
    	    for (size_t i = 0; i < trace_data.size()-10; i++) {
    	      double filter_val = _compute_slow_filter(fp, trace_data, baseline, i, handler);
    	      slow_filter.push_back(filter_val);
    	    }

	   int bestX_filter = std::distance(slow_filter.begin(), std::max_element(slow_filter.begin(), slow_filter.end()));
    double bestY_filter = slow_filter[bestX];
    int targetY_filter = 0.25 * (bestY_filter);

    int trigger_filter = 0;
    bool found_filter = false;
    for (size_t j = 0; j < slow_filter.size(); j++) {
      int y = slow_filter[j];
      if (y >= 10) {
    	trigger_filter = j;
    	found_filter = true;
    	break;
      }
    }
    if (found_filter){
      double V_max = slow_filter[trigger_filter + fp.slow_risetime + fp.slow_gap - 1] ;
      std::cout<<V_max<<'\n';
    plot(trace_data, fitresult, slow_filter, baseline, trigger, trigger_filter);

    
    
    	    hE_offline[l][m][n]->Fill(V_max);
    	    slow_filter.clear();
    }
    	  }
    	}
      }
    }
   }
  // if(theApp){
  //   theApp->Run();
  //   //theApp->Terminate();
  // }
  if (theApp) theApp->Terminate(); // End TApplication at the end of the loop
}
