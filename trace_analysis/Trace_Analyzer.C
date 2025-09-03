 // #include <"/usr/opt/ddastoys/include/DDASRootFitEvent.h>
 // #include </usr/opt/ddastoys/include/DDASRootFitHit.h>
// #include </usr/opt/ddastoys/include/DDASFitHit.h>
// #include </projects/e23055/EEConverter/DDASRootFit.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <typeinfo>
template <typename T>
constexpr std::string_view type_name();



   
    

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <numeric>


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

void _compute_slow_filter(const FilterParameters& fp,  std::vector<unsigned short> trace, std::vector<float> &slow_filter, TH1D* hE1, int bestX, int bestY,double Energy, TH2D* hE_2D, TH2D* hE_Diff) {
  slow_filter.resize(trace.size(), 0);

  // Guess a baseline value by averaging 5 samples at the start and end of the trace and taking the minimum value:
  float baseline = // std::min(
    std::accumulate(trace.begin(), trace.begin() +5, 0.0) / 5;
			    // std::accumulate(trace.end() - 1, trace.end(), 0.0) / 5.0);

/*   for ( int i=0; i<trace.size(); i++) {
    // std::cout<<"before subtraction:"<<trace.at(i);
    trace.at(i)-=baseline;
    // std::cout<<"after subtraction:"<<trace.at(i)<<'\n';
    } */
    TraceHandler handler(trace, baseline);
  // std::cout << "Estimated baseline: " << baseline << std::endl;
   
  // Using notation from Tan unless otherwise noted, with time in samples:
   long double b1 = std::exp(-1.0 / fp.tau);  // Ratio for geometric series sum Eq. 1.
  long double bL = std::pow(b1, fp.slow_risetime);
  long double bg = std::pow(b1, fp.slow_gap);
  // Coefficients of the inverse matrix Eq. 2 (example matrix elements given on the bottom of pg. 1542):
  long double a0 = bL / (bL - 1);
  long double ag = 1;
  long double a1 = 1 / (1 - bL);

/*   std::cout << "Ratio: " << b1 << ", coefficients: " << a0 << " " << ag << " " << a1 << std::endl; */
  // std::cout<<"bestX"<<bestX<<'\n';
  for (size_t i =0; i < trace.size(); ++i) {
    long double s0 = 0;  // Trailing sum.
    long double sg = 0;  // Gap sum.
    long double s1 = 0;  // Leading sum.
  
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
      slow_filter[i]= a0*s0 + ag * sg+ a1 *s1;
      // std::cout<<s0<<"    "<<sg<<"     "<< s1<<"      "<<slow_filter[i]<<" index: "<<i*4<<'\n';
       // if (i == trace.size() / 2) {
      // 	std::cout << "Sums_A7a: " << s0 << " " << sg << " " << s1 << " filter: " << slow_filter[i] << std::endl;
      // }
      // std::cout<<"entered this loop"<<'\n';
    }
    // std::cout<<slow_filter[i]<<'\n';
    ilow=0;
    ihigh=0;
    s0=0;
    sg=0;
    s1=0;
  }
  int size_trace=trace.size();
  double tracex[size_trace], tracey[size_trace], tracex_err[size_trace], tracey_err[size_trace];
  std::vector<double>filterx;
  std::vector<double>filtery;
  double maxTraceValue =trace[4900/4];
  double maxFilterValue = slow_filter[4900/4];
    // if (maxTraceValue != 0) {
    //     for (auto& value : slow_filter) {
    //         // value /= maxTraceValue/maxFilterValue;
    // 	  value /= (int)1240/65;
    //     }
    // }
  for (int bin=0; bin<trace.size(); bin++){
    //printf("%d\n",trace_max);
    // hTrace->Fill(bin,trace[bin]-offset);
    tracex[bin]=4*bin;
    tracex_err[bin]=0;
    tracey[bin]=trace[bin];
    tracey_err[bin]=0;
  }
  for (int bin=0; bin<trace.size(); bin++){
    filterx.push_back(bin*4);
    filtery.push_back(slow_filter[bin]);
	 
    //printf("%f\n",tracex[bin]);
  }


  int targetY = 0.25 * (bestY-baseline);
    int trigger =0;
	bool found = false;
	for (int i =0; i<=trace.size(); i++) {
	  int y = tracey[i]-baseline;
	  if (y >= targetY) {
            trigger = tracex[i];
            found = true;
            break;
	  }
	}
	// std::cout<<bestY<<'\n';
  double V_max = filtery[trigger/4+fp.slow_risetime+fp.slow_gap-1];
  /* double V_max_Corrected = -106.473+ filtery[trigger/4+208/4+48/4-1]*0.18466; */
 /*  double V_max_Corrected =-54.4976 + filtery[trigger/4+fp.slow_risetime+fp.slow_gap-1]*0.0958489; */
  hE1->Fill(V_max);
  hE_2D->Fill(V_max, Energy);
  hE_Diff->Fill((V_max - Energy) * 100 / V_max,Energy);
  std::cout<<"E_Filter=:"<<V_max<<'\n';
  TGraphErrors* gTrace = new TGraphErrors(size_trace,tracex,tracey,tracex_err,tracey_err);
  TGraph *gFilter = new TGraph(size_trace,filterx.data(),filtery.data());
  // gTrace->GetYaxis()->SetRangeUser(-10000,100000);
  gFilter->SetLineColor(kRed);
  gFilter->Draw();
  gTrace->Draw("same");



  
}






template <>
constexpr std::string_view type_name<void>() { return "void"; }
int Trace_Analyzer(int run=42, int nfiles=1) {

  TString ProgramsDir = "/user/cpvdaq/programs";
  TString DDASDir     = ProgramsDir + "/ddasdumper";

  TString DumpedDir  = DDASDir + "/dumped";
  TString ROOTDir    = ProgramsDir + "/rootdumper";
  TString DataDir    = ROOTDir + "/data";



  // TString CurrentDir  = gSystem->pwd();
  // if ( ROOTDir != CurrentDir ) {
  // 	std::cout << "ERROR Current directory does not match hardcoded rootdumper directory\nROOTDir : " << ROOTDir << "\nCurrentDir : " << CurrentDir << std::endl;
  // 	return -1;
  // }


  for (int filenumber = 0; filenumber < nfiles; filenumber++) {
    std::cout << "Processing file " << filenumber << " of " << nfiles << std::endl;
    stringstream ss;

	

    /* TFile *f0 = TFile::Open(".root"); */
   /*  TTree *tree = (TTree*)f0->Get("dchan"); */
     TChain* tree=new TChain("dchan");
     tree->Add("run-1406*");
        
    DDASEvent *pEvent = new DDASEvent;
    // // //	DDASRootFitHit *pEvent = new DDASRootFitHit; 
    tree->SetBranchAddress("ddasevent",&pEvent);
	
    TFile *outfile = new TFile("output_ddas_1281.root", "recreate" );	//TString::Format(DataDir + "/run%d.root",run),"recreate");
    TTree *AnalysisTree = new TTree("runTree","Data from Run");
    int Channel;
    double Time, TimeCoarse, Energy, Energy1;
    std::vector<unsigned short> trace;
    std::vector<float> slow_filter;
    /*
    // Plot the energies for the first two channels
    TH1D *Energy0 = new TH1D("Energy0","",10000,0,10000);
    TH1D *Energy1 = new TH1D("Energy1","",10000,0,10000);
    TH1D *Energy2 = new TH1D("Energy2","",10000,0,10000);
    */
   /*  tree->GetEvent(0);
    const int size_trace=pEvent->GetData().at(0)->GetTrace().size(); */
    // std::cout<<size_trace<<'\n';
    const int size_trace=130;
    TH2D *hTrace = new TH2D("hTrace","hTrace",size_trace,0,4*size_trace,6500,-5000,60000);
    TH2D *hMax = new TH2D("hMax","hMax",5000,0,250,6000,0,60000);
    TH1D *hE1 = new TH1D("hE1","hE1",60000,0,600000);
    TH1D *hE = new TH1D("hE","hE",6000,0,60000);
    TH1D* hist_Trace=new TH1D("hist_Trace","hist_Trace", size_trace,0,4*size_trace);
    TH2D* hE_2D = new TH2D("hE_2D", "hE_2D", 6000, 0, 600000, 600, 0, 60000);
    TH2D* hE_Diff = new TH2D("hE_Diff", "hE_Diff", 1000, 0, 100, 600, 0, 60000);
    int nEvents = tree->GetEntries();
    TGraphErrors *gTrace;
    TGraph *gFilter;
    TCanvas *cTrace;
   
    // std::cout<<nEvents<<'\n';
    for (int i =0; i <=1000; i+=1) {
      tree->GetEvent(i);

      /*  std::cout<<"working"<<'\n'; */
      int Channel = pEvent->GetData().at(0)->GetChannelID();
     
     /*  int trace_size =pEvent->GetData().at(0)->GetTrace().size(); */
      if(Channel==0 && pEvent->GetData().at(0)->GetOverflowCode()==0){
	/* if (i % 100 == 0) std::cout << i << "/" << nEvents << std::endl; */
	
	for (int j = 0; j <=0; j++) {
	

	  /*  Energy = pEvent->GetData().at(j)->GetEnergy();
     std::cout<<Energy<<'\n'; */
/* 	   std::cout<<"Energy="<<Energy<<'\n'; */
	  //std::cout<<"Sums="<<pEvent->GetData().at(j)->GetEnergySums(0)<<"   "<<pEvent->GetData().at(j)->GetEnergySums(1)<<"   "<<pEvent->GetData().at(j)->GetEnergySums(2)<<'\n';
	  /* hE->Fill(Energy); */
	  
	  // for(int i=0; i<trace_size; i++){
      
	    trace=pEvent->GetData().at(j)->GetTrace();
      if(trace.size()>0){
       Energy = pEvent->GetData().at(j)->GetEnergy();
     std::cout<<Energy<<'\n';
      std::cout<<trace.size()<<" Event: "<<i<<'\n';
	  // }
 	   int bestY=*max_element(trace.begin(),trace.end());
	  /* int bestX = std::distance(trace.begin(), bestY); */
	  auto maxElementIt = std::max_element(trace.begin(), trace.end()); 

 
    // hE1->Fill();
    // Calculate the index of the maximum element
    int bestX = std::distance(trace.begin(), maxElementIt);
    FilterParameters fp(0.0, 104, 0, 104, 3000, 32/4,48/4,(100/4));
 // float baseline = std::min(std::accumulate(trace.begin(), trace.begin() + 5, 0.0) / 5.0,
 // 			    std::accumulate(trace.end()-5, trace.end(), 0.0) / 5.0);
 //  for (int i=0; i<trace.size(); i++) {
 //    trace.at(i)-=baseline;
 //  }

  
    _compute_slow_filter(fp,  trace, slow_filter, hE1, bestX, bestY, Energy, hE_2D, hE_Diff );
	  // //htrace->Draw("");



	
      }

	 
	  // AnalysisTree->Write();

	}
	// std::cout<<"dynode"<<'\n';
      }
      // else{std::cout<<"anode"<<'\n';
				// }
  

      // /*
      // 	TCanvas *c1 = new TCanvas("c1","",980,600);
      // 	c1->SetLogy();
      // 	Energy0->Draw();
      // 	Energy1->SetLineColor(kRed);
      // 	Energy1->Draw("sames");
      // 	Energy2->SetLineColor(kBlack);
      // 	Energy2->Draw("sames");
      // */
      
    }
     /* TF1* fit_1D=new TF1("fit_1D","pol1",0,600000);
     hE_2D->Fit(fit_1D,"R") ;  */    
    /* hE_2D->Write();
    hE_Diff->Write();
    hE->Write();
    hE1->Write(); */
   
    // outfile->Close();
  }
  
  return 1;
}

