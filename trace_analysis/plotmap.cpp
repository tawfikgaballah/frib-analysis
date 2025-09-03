#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <omp.h>  // Include OpenMP for parallel processing
#include <set>

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
#include "TFile.h"
#include "TF2.h"
#include "/usr/opt/ddastoys/4.0-001/include/functions_analytic.h"
#include "/usr/opt/ddastoys/4.0-001/include/lmfit_analytic.h"
TApplication* theApp; // ugh
const int clockns = 4; // ns/sample
//const int overflow = 65535; // trace overflow value
const int overflow = 15999;








Double_t f2DLorentz(Double_t *x, Double_t *par) {

  // Fit parameters
  Double_t scale   = par[0]; // Amplitude
  Double_t gammax  = par[1]; // Width x
  Double_t gammay  = par[2]; // Width y
  Double_t posx    = par[3]; // Position x
  Double_t posy    = par[4]; // Position y

  // Some quantities
  Double_t xx = x[0]-posx;
  Double_t yy = x[1]-posy;
  Double_t gammax2 = gammax*gammax;
  Double_t gammay2 = gammay*gammay;

  // The denominators of the x and y portions of the 2D fit
  Double_t denomx = 1.0 / (xx*xx + gammax2);
  Double_t denomy = 1.0 / (yy*yy + gammay2);

  // Final fit function
  Double_t val = scale*gammax2*gammay2*denomx*denomy;
  
  return val;
}

/***********************************************************/
// Three-parameter generalized 1D Lorentzian lineshape. FWHM
// along each axis is given by 2*gamma.
Double_t f1DLorentz(Double_t *x, Double_t *par) {

  // Fit parameters
  Double_t scale   = par[0]; // Amplitude
  Double_t gammax  = par[1]; // Width x
  Double_t posx    = par[2]; // Position x

  // Some quantities
  Double_t xx = x[0]-posx;
  Double_t gammax2 = gammax*gammax;

  // Final fit function
  Double_t val = (scale*gammax2)/(xx*xx + gammax2);
  
  return val;
}






TF2* Lorentzian_1D( TH2D* hist) {
  TH1D* projX = hist->ProjectionX();
  TH1D* projY = hist->ProjectionY();
    
  double amplitude = hist->GetMaximum();
  double position_x = projX->GetBinCenter(projX->GetMaximumBin());
  double width_x = projX->GetStdDev();
  double amplitude_y = projY->GetMaximum()-projY->GetMinimum();
  double position_y = projY->GetBinCenter(projY->GetMaximumBin());
  double width_y = projY->GetStdDev();
  
  TF2 *fit_function = new TF2("fit_function",f2DLorentz,0,16,0,16,5);

  fit_function->SetParameter(0, amplitude);
  fit_function->SetParameter(1,16);
  fit_function->SetParameter(2, 16);
  fit_function->SetParameter(3, position_x);
  fit_function->SetParameter(4, position_y);
  fit_function->SetParLimits(3,fmax(position_x-3,0.001),fmin(position_x+3,15.999));
  fit_function->SetParLimits(4,fmax(position_y-3,0.001),fmin(position_y+3,15.999));
  return fit_function;
}



TF1* Lorentzian( TH1D* hist) {
  double amplitude_x = hist->GetMaximum()-hist->GetMinimum();
  double position_x = hist->GetBinCenter(hist->GetMaximumBin());
  double width_x = hist->GetStdDev();
 
  TF1* fit_x= new TF1("fit_x","([0]/(TMath::Pi()*[2]*(1+pow((x-[1])/[2],2))))",0,16);
  fit_x->SetParameter(0, amplitude_x);
  fit_x->SetParameter(1, position_x);
  fit_x->SetParameter(2, width_x);
  fit_x->SetParLimits(1,fmax(position_x-2,0),fmin(position_x+2,16));
 
  return fit_x;
}















int plot(TH2D* Map, TH1D* chn)
{
  if(theApp==NULL) theApp = new TApplication("theApp",0,0);
  TCanvas* c = new TCanvas("c","c",800,500);
  TCanvas* c1 = new TCanvas("c1","c1",800,500); 
  c->cd();


  Map->Draw("colz");
  c1->cd();
  chn->Draw("hist");
  theApp->Run(kTRUE);  


  // delete Map;
  delete c;
  delete c1;
  return 0;
}

int generate_unique_id(int crateid, int slotid, int channum) {
  return ((crateid - 1) << 8) | ((slotid - 2) << 4) | channum;
}

void extract_values(int unique_id, int &crateid, int &slotid, int &channum) {
  crateid = unique_id / 208;                             // Extract crateid
  int slotid_component = unique_id - (208 * crateid);     // Calculate remaining component after crateid
  slotid = (slotid_component / 16) + 2;                  // Extract slotid
  channum = slotid_component % 16;                       // Extract channum
}


void displayProgressBar(float progress) {
  int barWidth = 70;
  std::cout << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) {
    if (i < pos) std::cout << "=";
    else if (i == pos) std::cout << ">";
    else std::cout << " ";
  }
  std::cout << "] " << int(progress * 100.0) << " %\r";
  std::cout.flush();
}

int main() {
  for(int i=61; i<=61; i++){
  TChain* data = new TChain("DDASFit");
  data->Add(Form("/mnt/analysis/e16032/rootfiles/run-00%d-00*",i));
  TH2D* chn_Vs_E=new TH2D("chn_Vs_E","chn_Vs_E", 6500,0,65000,300,50,350);
  TH2D* chn_vs_dynode=new TH2D("Anodes_Vs_DynodeE","Anodes_Vs_DynodeE",6500,0,65000,300,0,300);
   TH2D* Map_Full=new TH2D("map_full", "map_full", 20,0,20,20,0,20);
    TH2D* Map_Full_dynode=new TH2D("map_full_dynode", "map_full_dynode", 20,0,20,20,0,20);
  TH1D* dynode=new TH1D("DynodeE","DynodeE",6500,0,65000);
  TH2D* Map_Ave=new TH2D("map_ave", "map_ave", 200,0,20,200,0,20);
  TH1D* dynode_middle=new TH1D("DynodeE_Middle","DynodeE_Middle",6500,0,65000);
  TH1D* dynode_c1=new TH1D("DynodeE_c1","DynodeE_c1",6500,0,65000);
  TH1D* dynode_c2=new TH1D("DynodeE_c2","DynodeE_c2",6500,0,65000);
  TH1D* dynode_c3=new TH1D("DynodeE_c3","DynodeE_c3",6500,0,65000);
  TH2D* Map_Lorentzian=new TH2D("map_lorentzian", "map_lorentzian", 200,0,20,200,0,20);
  TH2D* Dynode_Vs_Xpos=new TH2D("Dynode_Vs_Xpos", "Dynode_Vs_Xpos", 200,0,20, 5000,0,5000);
  TH2D* Dynode_Vs_Ypos=new TH2D("Dynode_Vs_Ypos", "Dynode_Vs_Ypos", 200,0,20,5000,0,5000);
  // int slow_rise_parameters[] = {48,108,208,308,408,508,608};
  // int slow_gap_parameters[] = {48,52,56,60,64,68,72};
  // int tau_parameters[] = {4, 8, 12, 16, 20, 32, 40};


 

  TFile* output = new TFile(Form("output_run%d_Map_10_test.root",i), "RECREATE");
  std::cout << "Input data chain has " << data->GetEntries() << " events" << std::endl;

  std::vector<DDASRootFitHit*> channellist;
  std::vector<DDASRootFitHit*>::iterator channellist_it;
  std::vector<RootHitExtension>* fitdata(0);
  data->SetBranchAddress("HitFits", &fitdata);
  std::vector<Double_t> fitresult;
  std::vector<Double_t> fitresult2;

  int totalEntries = data->GetEntries()*1;
  // #pragma omp parallel for schedule(dynamic)
  
  for (int evt = 0; evt <totalEntries*1; ++evt) {
    TH2D* Map=new TH2D("map", "map", 40,-20,20,40,-20,20);
    TH1D* chn=new TH1D("chn", "chn", 416,0,416);
    if (omp_get_thread_num() == 0) {
      displayProgressBar(static_cast<float>(evt) / totalEntries);
    }
  

    DDASRootFitEvent* rawhits = new DDASRootFitEvent();
    TBranch *aRawHitsevent = data->GetBranch("RawHits");
    aRawHitsevent->SetAddress(&rawhits);
    data->GetEntry(evt);

    channellist = rawhits->GetData();
    std::set<int> found_ids;
    int dymult = 0;
    int crate2=0;
    for (channellist_it = channellist.begin(); channellist_it < channellist.end(); channellist_it++) {
      int crateid = (*channellist_it)->crateid;
      int slotid = (*channellist_it)->slotid;
      int channum = (*channellist_it)->chanid;
      int id = 208 * crateid + 16 * (slotid - 2) + channum;
      // int id = (crateid-1)*208+(slotid-2)*16+channum;
      if (id == 0) {
	dymult++;
      }
      if(crateid>0){
      	crate2++;
      }
      // if (id >= 224 && id <= 480) {
      // 	found_ids.insert(id);
      // }
    }

    // bool all_found = true;
    //  for (int i = 224; i <= 480; ++i) {
    //      if (found_ids.find(i) == found_ids.end()) {
    //          all_found = false;
    //          break;
    //      }
    //  }
    double dyenergy, chancount;
    bool foundmiddle;
    bool foundc1;
    bool foundc2;
    bool foundc3;

    double xpos_ave=-1;
    double ypos_ave=-1;
    double tot_energy=-1;
    for (size_t i = 0; i < channellist.size(); i++) {
      int crateid = channellist[i]->crateid;
      int slotid = channellist[i]->slotid;
      int channum = channellist[i]->chanid;
      double energy = channellist[i]->energy;
      // double time = channellist[i]->time;
      // std::vector<uint16_t> trace = channellist[i]->trace;
      // std::vector<double> slow_filter;
      // std::vector<uint32_t> qdcSums = channellist[i]->qdcSums;


      int id = 208 * crateid + 16 * (slotid - 2) + channum;

      if(id==0){
	dyenergy=energy;
      }
      else if(id!=0 &&id>=64 &&id<=319){
	// std::cout<<"found"<<'\n';
	int xPos = -1;  
	int yPos = -1; 
	int p1d=id-64;
	xPos =(int)(p1d)%16;
	yPos =(int)(p1d)/16;
	// xPos=abs(xPos-16);
	// yPos=abs(yPos-16);
	// xPos=yPos;
	// yPos=-xPos;
      
	Map->Fill(xPos, yPos, energy);
	Map_Full->Fill(xPos, yPos, energy);
	Map_Full_dynode->Fill(xPos, yPos, dyenergy);
	chn->Fill(id);
	chn_Vs_E->Fill(energy, id);

	xpos_ave+=xPos*energy;
	ypos_ave+=yPos*energy;
	tot_energy+=energy;
	// chn_vs_dynode->Fill(dyenergy,id);
	// chancount++; 
 
      }
    }




    if(xpos_ave>=6 &&xpos_ave<=9 &&ypos_ave>=6 &&ypos_ave<=9){
      dynode_middle->Fill(dyenergy);
      // foundmiddle==true;
    }

    if(xpos_ave>=0 &&xpos_ave<=3 &&ypos_ave>=12 &&ypos_ave<=15 ){
      dynode_c1->Fill(dyenergy);
      // foundc1==true;
    }
    if(xpos_ave>=12 &&xpos_ave<=15 &&ypos_ave>=12 &&ypos_ave<=15) {
      dynode_c2->Fill(dyenergy);
      // foundc2==true;
    }
    if(xpos_ave>=12 &&xpos_ave<=15 &&ypos_ave>=0 &&ypos_ave<=3 ){
      dynode_c3->Fill(dyenergy);
      // foundc3==true;
    }
    chancount=chn->Integral();
    chn_vs_dynode->Fill(dyenergy,chancount);
    dynode->Fill(dyenergy);
    Map_Ave->Fill(xpos_ave/tot_energy,ypos_ave/tot_energy); 
    // if(chancount>=256){
    //   plot(Map, chn);
    // }

    Map->SetBinContent(5, 16, 0);
        
    // Create linearized fit function and perform fit
    TF2* linear_fx = Lorentzian_1D(Map);
    Map->Fit(linear_fx, "QNEMRL");
 
    Map_Lorentzian->Fill(linear_fx->GetParameter(3), linear_fx->GetParameter(4));
    Dynode_Vs_Xpos->Fill(linear_fx->GetParameter(3), dyenergy);
    Dynode_Vs_Ypos->Fill(linear_fx->GetParameter(4), dyenergy);
	
    delete linear_fx; // Make sure to delete fit functions to prevent memory leaks
    delete Map;
    delete chn;
    crate2=0;
  }
  output->cd();
  // chn_Vs_E->Draw();
  chn_Vs_E->Write();
  chn_vs_dynode->Write();
  Map_Full->Write();
  Map_Full_dynode->Write();
  dynode->Write();
  dynode_middle->Write();
  dynode_c1->Write();
  dynode_c2->Write();
  dynode_c3->Write();
  Map_Ave->Write();
  Map_Lorentzian->Write();
  Dynode_Vs_Xpos->Write();
  Dynode_Vs_Ypos->Write();
  // Map->Write();
   output->Close();
   delete output;
   delete data;
   delete chn_Vs_E;
   delete chn_vs_dynode;
   delete  Map_Full;
   delete  dynode;
     
  }
   return 0;
}
