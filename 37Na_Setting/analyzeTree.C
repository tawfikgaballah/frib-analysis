#include <TFile.h>
#include <TTree.h>
#include <map>
#include <vector>
#include <TFile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <map>
#include <map>
#include <vector>
#include"TH1D.h"
#include"TH2D.h"
struct EntryData {
  Long64_t index;
  Double_t Ei;
  Int_t index_i;

  Double_t ADC;
  Double_t tcal;
  // Float_t tpred;
};
const int tbins=2000; 
const int t_min=-100;
const int t_max=100;

const int ebins=1400; 
const int e_min=0;
const int e_max=1400; 

const int dbins=1000; 
const int d_min=0;
const int d_max=10000;
double shifts[16]={-14.8188, -26.0571, -29.7526, -20.6941, -23.6376, -28.6894, -19.314, -21.183, -24.0159, -18.8482, -18.7869, -23.6501, -8.54579, 0, -22.7087, -22.3649};
//double shifts[16]={-14.7912, -26.0571, -29.7526, -20.6673, -23.6376, -28.6894, -19.2796, -21.1468, -24.0159, -18.8269, -18.7659, -23.6501, -8.54579, 0, -22.7087, -22.3649};
double shifts_1240[16]={-18.9601, -18.0815, -25.5616, -16.2638, -21.6255, -26.8352, -22.8314, -16.6077, -21.6251, -16.9239, -18.0982, -19.9179, -9.70704, 0, -16.0336, -28.0785};
const double shifts_1[16]={-19.5671,-18.3432,-25.9482,-16.666,-22.2344,-26.9911,-23.1673,-17.521,-22.3561,-17.0482,-18.8937,-20.6728,-10.1422,0,-16.3027,-28.6543};
void analyzeTree() {
  //  TFile *file = TFile::Open("/mnt/analysis/e21062/sortedData2024/betasorted/NERSC-analyzed/run-1281-sorted.root","READ");
      TFile *file = TFile::Open("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1240-sorted.root","READ");
       TFile *file1 = TFile::Open("/projects/e21062/tg/37Na_Setting/calibration_test_run_1240_linear_two_points.root","READ");
// Ba_2004_training_data_with_time_stamp_1st_step_modified_no_reference_to_dynode.root
  //TFile *file = TFile::Open("/data/e16032/tg1250/ML_From_HPCC/Co_2004_training_data_with_time_stamp_1st_step_modified_test.root","READ");
  TTreeReader reader("data", file);

  TTree* data=(TTree*)file->Get("data");
  std::cout<<data->GetEntries()<<'\n';
  TTree* data_cal=(TTree*)file1->Get("/cal/data_cal");
  std::cout<<data_cal->GetEntries()<<'\n';
  data->AddFriend(data_cal,"data_cal");
  TFile* output=new TFile("output_Co_calibration_run1423.root","recreate");
  
  TH2D* Detector_Vs_TDynode_Offset=new TH2D("Detector_Vs_TDynode_Offset","Detector_Vs_TDynode_offset",tbins,t_min,t_max,15,0,15);
  TH2D* LaBr3E_Vs_tdynode_offset=new TH2D("LaBr3E_Vs_tdynode_offset","LaBr3E_Vs_tdynode_offset",tbins,t_min,t_max,ebins, e_min, e_max);
  TH1D* LaBr3_TDiff=new TH1D("LaBr3_TDiff","LaBr3_TDiff",tbins,t_min,t_max);
   TH1D* LaBr3_Energy=new TH1D("LaBr3_Energy","LaBr3_Energy",ebins,e_min,e_max);
  TH1D* TDynode_Offset=new TH1D("TDynode_Offset","TDynode_Offset",tbins,t_min,t_max);
  TH2D* LaBr3E_Vs_TDiff=new TH2D("LaBr3E_Vs_TDiff","LaBr3E_Vs_TDiff",tbins,t_min,t_max,ebins, e_min, e_max);

  TH2D* Detector_Vs_TDynode_Offset_Aligned=new TH2D("Detector_Vs_TDynode_Offset_Aligned","Detector_Vs_TDynode_offset_Aligned",tbins,t_min,t_max,15,0,15);
  TH2D* LaBr3E_Vs_tdynode_offset_Aligned=new TH2D("LaBr3E_Vs_tdynode_offset_Aligned","LaBr3E_Vs_tdynode_offset_Aligned",tbins,t_min,t_max,ebins, e_min, e_max);
  TH1D* LaBr3_TDiff_Aligned=new TH1D("LaBr3_TDiff_Aligned","LaBr3_TDiff_Aligned",tbins,t_min,t_max);
   TH1D* LaBr3_Energy_Aligned=new TH1D("LaBr3_Energy_Aligned","LaBr3_Energy_Aligned",ebins,e_min,e_max);
  TH1D* TDynode_Offset_Aligned=new TH1D("TDynode_Offset_Aligned","TDynode_Offset_Aligned",tbins,t_min,t_max);
  TH2D* LaBr3E_Vs_TDiff_Aligned=new TH2D("LaBr3E_Vs_TDiff_Aligned","LaBr3E_Vs_TDiff_Aligned",tbins,t_min,t_max,ebins, e_min, e_max);




  
  TH1D* tdynode[16];
  for (int i=0; i<16; i++){
    tdynode[i]=new TH1D(Form("tdynode_%d",i),Form("tdynode_%d",i),tbins,t_min,t_max);
  }

    TH1D* tdynode_aligned[16];
  for (int i=0; i<16; i++){
   tdynode_aligned[i]=new TH1D(Form("tdynode_aligned_%d",i),Form("tdynode_aligned_%d",i),tbins,t_min,t_max);
  }
  
  TTreeReaderArray<Double_t> labr_ecal(reader, "data_cal.labr3_ecal");
  TTreeReaderValue<Int_t> pspmthigh2_dycfdfailbit(reader, "pspmthigh2.dycfdfailbit");
  TTreeReaderArray<Int_t> labr_cfdfailbit(reader, "labr.cfdfailbit[16]");

  TTreeReaderArray<Double_t> pspmthigh2_dytime(reader, "pspmthigh2.dytime");
  TTreeReaderArray<Double_t> pspmthigh2_dyenergy(reader, "pspmthigh2.dyenergy");
  TTreeReaderArray<Double_t> labr_timecal(reader, "labr.timecal[16]");
  
   
  while (reader.Next()) {
    int dy_cfd=*pspmthigh2_dycfdfailbit;
    double dy_energy;
    double dy_time;
    if( pspmthigh2_dyenergy.GetSize()>=1 && pspmthigh2_dytime.GetSize()>=1){
      for(int i=0; i<3; i++){
	if(pspmthigh2_dytime[i]>dy_time){
	  dy_time=pspmthigh2_dytime[i];
	}

	if(pspmthigh2_dyenergy[i]>dy_energy){
	  dy_energy=pspmthigh2_dyenergy[i];
	}
      }
     
      // std::cout<<"A7A"<<" e_size: "<<pspmthigh2_dyenergy.GetSize()<<" t_size: "<<pspmthigh2_dytime.GetSize()<< '\n';
      // std::cout<<pspmthigh2_dyenergy[0]<<"       "<<pspmthigh2_dyenergy[1]<<"     "<<pspmthigh2_dyenergy[2]<<"     "<<pspmthigh2_dyenergy[3]<<'\n';
      // dy_energy=pspmthigh2_dyenergy[0];
      // dy_time=pspmthigh2_dytime[0];
    }
    if(dy_cfd!=1 && dy_energy>10 && dy_time>10){
      for (int i=0; i<16; i++){
	double E_i=labr_ecal[i];
	double T_i=labr_timecal[i];
	int cfd_labr3_i=labr_cfdfailbit[i];
    
     
	//else{
       	//std::cout<<pspmthigh2_dyenergy[0]<<'\n';
       	// dy_energy=(double)pspmthigh2_dyenergy;
       	// dy_time=(double)pspmthigh2_dytime;
	//}

	if(E_i>0 && cfd_labr3_i!=1 &&T_i>10 && i!=13){
	  
	  Detector_Vs_TDynode_Offset->Fill(T_i-dy_time,i);
	  LaBr3E_Vs_tdynode_offset->Fill(T_i-dy_time, E_i);
	  TDynode_Offset->Fill(T_i-dy_time);
	  LaBr3_Energy->Fill(E_i);
	  Detector_Vs_TDynode_Offset_Aligned->Fill(T_i-dy_time-shifts[i],i);
	  LaBr3E_Vs_tdynode_offset_Aligned->Fill(T_i-dy_time-shifts[i], E_i);
	  TDynode_Offset_Aligned->Fill(T_i-dy_time-shifts[i]);
	  tdynode[i]->Fill(T_i-dy_time);
	  tdynode_aligned[i]->Fill(T_i-shifts[i]-dy_time);
	  for (int j=i+1; j<16; j++){
	    double E_j=labr_ecal[j];
	    double T_j=labr_timecal[j];
	    int cfd_labr3_j=labr_cfdfailbit[j];
	    if(E_j>0 && cfd_labr3_j!=1 &&T_j>10 && j!=13){
	     
	      LaBr3_TDiff->Fill(T_i-T_j);
	      LaBr3E_Vs_TDiff->Fill(T_i-T_j,E_j);
	    
	      LaBr3_TDiff_Aligned->Fill(T_i-T_j-shifts[i]+shifts[j]);
	      LaBr3E_Vs_TDiff_Aligned->Fill(T_i-T_j-shifts[i]+shifts[j],E_j);
	    }
	  }
   
	}

      }
      // }
    }
  }
output->mkdir("raw_time");
output->mkdir("aligned");

output->mkdir("raw_individual");
output->mkdir("aligned_individual");

 output->cd("raw_individual");
 
 for (int i=0; i<16; i++){
   tdynode[i]->Write();
 }

output->cd("aligned_individual");
 
 for (int i=0; i<16; i++){
   tdynode_aligned[i]->Write();
 } 
 
output->cd("raw_time");

  LaBr3_TDiff->Write();
  LaBr3E_Vs_TDiff->Write();
  Detector_Vs_TDynode_Offset->Write();
  LaBr3E_Vs_tdynode_offset->Write();
  TDynode_Offset->Write();
  LaBr3_Energy->Write();

output->cd("aligned");

 LaBr3_TDiff_Aligned->Write();
 LaBr3E_Vs_TDiff_Aligned->Write();
 Detector_Vs_TDynode_Offset_Aligned->Write();
 LaBr3E_Vs_tdynode_offset_Aligned->Write();
 TDynode_Offset_Aligned->Write();


  output->cd();
  output->Close();



 for (int i=0; i<16; i++){
   tdynode[i]->Write();
 }
  

}
