/* This script utilizes AddFiles.h
 * so that several analysed root files 
 * can be loaded to TChain object at
 * the same time
 */

{
  /*******************************************
   * CAUTION! SWITCH BETWEEN CORR. WIN. = 3xT
   * RESULT AND CORR. WIN. = 1000 ms
   * RESULT BELOW
   *       ||
   *       \/
   ******************************************/
  
  // gROOT->ProcessLine(".L AddFiles.C");       // 9 pixel as correlation area
  //  gROOT->ProcessLine(".L AddFilesReverse.C"); 
  // 9 pixel as correlation area
  
  // gROOT->ProcessLine(".L AddFiles1000.C");
  // double s;
  //   double e;
  // Bool_t runtest = false;
  //   Bool_t runall = !runtest;
  
  //   gSystem->SetAclicMode(TSystem::kDebug);
  //   gSystem->SetAclicMode(TSystem::kOpt);

  //   // Get the shared object file which contains the beta decay classes
  //   // gSystem->Load("/mnt/home/chestera/software/rootanalysis/libTParameters.so");

  //   // Make the libraries
  //   Int_t error;
  //   gROOT->ProcessLine(".L /projects/e16032/e16032_Analysis_TG/0710analysis_TG/analysis/extract_analysis/sega/e21062_data/test1.C+", &error); if(error) exit(EXIT_FAILURE);
    
  //   gROOT->ProcessLine(".L /mnt/home/chestera/software/proof_selectors/selectors/Chain.C");

 gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/include/");
  gInterpreter->AddIncludePath("/user/e21062/HLC/ddasfitclasses/");
  gSystem->Load("/projects/e21062/Offline-Analysis/rootAnalysis/libTParameters.so");
 
  // make the libraries
  Int_t error;
     gROOT->ProcessLine(".L ./Selector_60Co.C+");

  TChain *data = new TChain("data");
  TChain *data_cal = new TChain("/cal/data_cal"); 
  // selections of RUNNUM:
  // 172, 181, 186,
  // 197, 198, 199,
  // 200, 1014
  // e16013a: 3006
  // int RUNNUM = 199;
  // int SUBSET = 4; 

  // run51, 137Cs
  //  AddRootFiles(data, 51, 0, 4); 
  // run61, 133Ba
  //  AddRootFiles(data, 61, 0, 33);    
  // run83, 60Co
  //  AddRootFiles(data, 83, 0, 100);
  // run85, 60Co, a half-day run
  //  AddRootFiles(data, 85, 0, 149); // labr3 only? 

  // 48Ca primary beams
  //  AddRootFiles(data, 102, 0, 3); 

  /* At the beginning of the beam time
   * the collection of anode traces were 
   * turned on
   */
  //  AddRootFiles(data, 127, 0, 40); 
  //  AddRootFiles(data, 134, 0, 85); 
  //  AddRootFiles(data, 135, 0, 85); 
  
  
  // move the beam around
  //    AddRootFiles(data, 127, 0, 41); // move beam down and right
  //        AddRootFiles(data, 130, 0, 27); // even further to the right
  //    AddRootFiles(data, 134, 0, 40); // back to run-127
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0246-sorted.root");

  // // data->SetName("segments_0000");
  // // data->SetBranchAddress("start",&s);
  // // data->SetBranchAddress("end",&e);
  
  data->Add("/mnt/analysis/e21062/sortedData2024/betasorted/localAnalyzed/TG/run-1240-sorted.root");
  // data_cal->Add("/projects/e21062/tg/37Na_Setting/calibration_test_run_1240_linear_two_points.root");
  // data->AddFriend(data_cal,"data_cal");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0238-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0241-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0244-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0245-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0246-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0247-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0248-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0249-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0250-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0251-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0252-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0253-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0254-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0255-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0256-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0257-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0258-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0259-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0261-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0262-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0263-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0264-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0266-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0267-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0268-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0269-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0270-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0271-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0272-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0280-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0282-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0283-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0284-sorted.root");
  // for (int l=0; l<77; l++){
  //     if(l<10){
  // 	data->Add(Form("/mnt/analysis/e21062/snl/sorted/run-0284-0%d-sorted.root",l));
  //     }
  //     else
  // 	data->Add(Form("/mnt/analysis/e21062/snl/sorted/run-0284-%d-sorted.root",l));
  //   }
      
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0285-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0286-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0287-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0288-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0290-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0292-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0294-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0295-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0296-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0298-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0299-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0300-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0301-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0302-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0303-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0304-sorted.root");
  // //data->Add("/mnt/analysis/e21062/snl/sorted/run-0305-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0306-sorted.root");
  // //  data->Add("/mnt/analysis/e21062/snl/sorted/run-0307-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0308-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0309-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0310-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0311-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0312-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0313-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0314-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0315-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0317-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0318-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0319-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0320-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0321-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0322-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0323-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0324-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0325-sorted.root");
  // data->Add("/mnt/analysis/e21062/snl/sorted/run-0326-sorted.root");

  //reverse_analyzed



  //    data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0237-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0238-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0241-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0244-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0245-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0246-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0247-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0248-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0249-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0250-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0251-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0252-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0253-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0254-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0255-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0256-sorted.root");
  // //  data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0257-sorted.root");
  // //  data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0258-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0259-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0261-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0262-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0263-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0264-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0266-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0267-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0268-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0269-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0270-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0271-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0272-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0280-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0282-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0283-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0284-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0285-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0286-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0287-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0288-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0290-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0292-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0294-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0295-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0296-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0298-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0299-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0300-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0301-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0302-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0303-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0304-sorted.root");
  // //data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0305-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0306-sorted.root");
  // //  data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0307-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0308-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0309-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0310-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0311-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0312-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0313-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0314-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0315-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0317-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0318-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0319-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0320-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0321-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0322-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0323-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0324-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0325-sorted.root");
  //   data->Add("/mnt/analysis/e21062/snl/sortedReverse/run-0326-sorted.root");
  
  cout << "Entries (from chain): " << data->GetEntries() << endl;
  // switch(RUNNUM)  {
  // case 172: {
  //   AddRootFiles(data, 172, 0, 257);
  //   break;
  // }  // 257 in total
  // case 181: {
  //   AddRootFiles(data, 181, 0, 95);
  //   AddRootFiles(data, 182, 0, 89);
  //   AddRootFiles(data, 183, 0, 22); // position test, 22 in total
  //   AddRootFiles(data, 184, 0, 41);
  //   AddRootFiles(data, 185, 0, 28);
  //   break;
  // }
  // case 186: {
  //   AddRootFiles(data, 186, 0, 1092);
  //   AddRootFiles(data, 187, 0, 87);
  //   AddRootFiles(data, 188, 0, 51);
  //   AddRootFiles(data, 189, 0, 8);     
  //   break; 
  // }
  // case 197: {
  //   AddRootFiles(data, 197, 0, 783); // 785 in total    
  //   break; 
  // }
  // case 198: {
  //   AddRootFiles(data, 198, 0, 299); // 299 in total
  //   break; 
  // }
  // case 199: {
  //   AddRootFiles(data, 199, 0, 1088); // 999 out of 1090 in total
  //   AddRootFiles(data, 200, 0, 105); // 105 in total
  //   AddRootFiles(data, 201, 0, 110); // 110 in total
  //   AddRootFiles(data, 203, 0, 39); // 39 in total
  //   AddRootFiles(data, 204, 0, 21); // 110 in total
  //   AddRootFiles(data, 205, 0, 104); // 121 in total
  //   AddRootFiles(data, 207, 0, 82); // 121 in total
  //   AddRootFiles(data, 1014, 0, 110);
  //   AddRootFiles(data, 1015, 0, 16);
  //   AddRootFiles(data, 1017, 0, 227);
  //   AddRootFiles(data, 1019, 0, 98);
  //   AddRootFiles(data, 1020, 0, 55);
  //   AddRootFiles(data, 1022, 0, 14);
  //   AddRootFiles(data, 1023, 0, 303);
  //   AddRootFiles(data, 198, 0, 299); // 299 in total
  //   AddRootFiles(data, 197, 0, 783); // 785 in total
  //   AddRootFiles(data, 186, 0, 1092);
  //   AddRootFiles(data, 187, 0, 87);
  //   AddRootFiles(data, 188, 0, 51);
  //   AddRootFiles(data, 189, 0, 8);
  //   AddRootFiles(data, 181, 0, 95);
  //   AddRootFiles(data, 182, 0, 89);
  //   AddRootFiles(data, 183, 0, 22); // position test, 22 in total
  //   AddRootFiles(data, 184, 0, 41);
  //   AddRootFiles(data, 185, 0, 28);
  //   AddRootFiles(data, 172, 0, 257);
  //   break;
  // }
  // case 200: {
  //   AddRootFiles(data, 200, 0, 105); // 105 in total
  //   AddRootFiles(data, 201, 0, 110); // 110 in total
  //   AddRootFiles(data, 203, 0, 39); // 39 in total
  //   AddRootFiles(data, 204, 0, 21); // 110 in total
  //   AddRootFiles(data, 205, 0, 104); // 121 in total
  //   AddRootFiles(data, 207, 0, 82); // 121 in total
  //   break; 
  // }
  //   case 1014: {
  //     AddRootFiles(data, 1014, 0, 110);
  //     AddRootFiles(data, 1015, 0, 16);
  //     AddRootFiles(data, 1017, 0, 227);
  //     AddRootFiles(data, 1019, 0, 98);
  //     AddRootFiles(data, 1020, 0, 55);
  //     AddRootFiles(data, 1022, 0, 14);
  //     AddRootFiles(data, 1023, 0, 303);
  //     break;  
  //   }




  // case 1023: {
  //   // AddRootFiles(data, 172, 0, 257);
   
  //   // AddRootFiles(data, 181, 0, 95);
  //   // AddRootFiles(data, 182, 0, 89);
  //   // AddRootFiles(data, 183, 0, 22); // position test, 22 in total
  //   // AddRootFiles(data, 184, 0, 41);
  //   // AddRootFiles(data, 185, 0, 28);
 
  //   // AddRootFiles(data, 186, 0, 1092);
  //   // AddRootFiles(data, 187, 0, 87);
  //   // AddRootFiles(data, 188, 0, 51);
  //   // AddRootFiles(data, 189, 0, 8);
    
    
  //   // AddRootFiles(data, 197, 0, 783); // 785 in total   
    
    
  //   // AddRootFiles(data, 198, 0, 299); // 299 in total
    
  //   AddRootFiles(data, 199, 0, 1088); // 999 out of 1090 in total
   
  //   // AddRootFiles(data, 200, 0, 105); // 105 in total
  //   // AddRootFiles(data, 201, 0, 110); // 110 in total
  //   // AddRootFiles(data, 203, 0, 39); // 39 in total
  //   // AddRootFiles(data, 204, 0, 21); // 110 in total
  //   // AddRootFiles(data, 205, 0, 104); // 121 in total
  //   // AddRootFiles(data, 207, 0, 82); // 121 in total
  
  //   // AddRootFiles(data, 1014, 0, 110);
  //   // AddRootFiles(data, 1015, 0, 16);
  //   // AddRootFiles(data, 1017, 0, 227);
  //   // AddRootFiles(data, 1019, 0, 98);
  //   // AddRootFiles(data, 1020, 0, 55);
  //   // AddRootFiles(data, 1022, 0, 14);
  //   // AddRootFiles(data, 1023, 0, 303);
  //   break;  
  // }
  // run-3006 data:
  // case 3006: {
  //   // AddRootFiles(data, 3006, 0, 197);
  //   // different settings

  //   // switch(SUBSET) {
  //   // case 1: AddRootFiles(data, 3006, 0, 35);break; 
  //   // case 2: AddRootFiles(data, 3006, 38, 65);break; 
  //   // case 3: AddRootFiles(data, 3006, 69, 93);break; 
  //   // case 4: AddRootFiles(data, 3006, 100, 155);break; 
  //   // case 5: AddRootFiles(data, 3006, 165, 197);break; 
  //   // }

  //   AddRootFiles(data, 3006, 0, 244);
  //   // AddRootFiles(data, 3006, 38, 68);
  //   // AddRootFiles(data, 3006, 69, 99);
  //   // AddRootFiles(data, 3006, 100, 164);
  //   // AddRootFiles(data, 3006, 165, 244);
    
  //   break; 
  // }
  // }
  
  // // 172
  // AddRootFiles(data, 172, 0, 257);  // 257 in total

  // // 18x
  // // 19x
  // //  AddRootFiles(data, 192, 0, 9); 
  // //  AddRootFiles(data, 193, 0, 14); 
  // //  AddRootFiles(data, 194, 0, 8); 
  // //  AddRootFiles(data, 195, 0, 13);
  // //  AddRootFiles(data, 196, 0, 10); 
  // // // 2xx
  // // AddRootFiles(data, 1004, 0, 15);
  // // AddRootFiles(data, 1005, 0, 88);
  // // AddRootFiles(data, 1006, 0, 19);
  // // AddRootFiles(data, 1007, 0, 4);
  // // AddRootFiles(data, 1008, 0, 58);
  // // AddRootFiles(data, 1009, 0, 56);
  // // AddRootFiles(data, 1010, 0, 35);
  // // AddRootFiles(data, 1011, 0, 47);
  // // AddRootFiles(data, 1012, 0, 17);
  // // PID back to normal as before
  
  // 208, background
  //  AddRootFiles(data, 208, 0, 9); 
  

  // e18401
  // 1000 - Co-60
  //  AddRootFiles(data, 1000, 0, 5);
  // end of beam time, Co-60
  //  AddRootFiles(data, 2001, 0, 59);
  //  AddRootFiles(data, 2004, 200, 300);
    

  // TProof *proof = TProof::Open("workers=8");
  // data->SetProof();


  // update after 06/24
  data->Process("Selector_60Co.C+");
  // data->Process("SingleSegaSelector.C+"); 
  // data->Process("SegaSelector3006.C+");
  
  // data->Process("CorrSelector.C+"); 
  
  // // detach from current PROOF session
  // data->SetProof(0);

  
  // // display process details
  // gProof->GetQueryResult()->Print(); 

  
}






