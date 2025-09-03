/* This script utilizes AddFiles.h
 * so that several analysed root files 
 * can be loaded to TChain object at
 * the same time
 */

{
    gROOT->ProcessLine(".L AddFiles1.C+"); // load the files that you want to look at
    gROOT->ProcessLine(".L Timing_Branches.C+");
   // TFile *input=new TFile("/mnt/analysis/e16032/tg1250/rootfiles/2004/run-2004-tg1250.root", "READ");
   TChain *data = new TChain("data");
   
   // TTree *data1=new TTree("data1","data1");
  // test
  //  AddRootFiles(data, 172, 1, 1);  

  // run51, 137Cs
  //  AddRootFiles(data, 51, 0, 4); 
  // run61, 133Ba
  //  AddRootFiles(data, 61, 0, 33);    
  // run83, 60Co
  //  AddRootFiles(data, 83, 0, 100);
  // run84, 133Ba
  // AddRootFiles(data, 85, 0, 148);
  //AddRootFiles(data, 84, 0, 10);//test
  
  // run 133 background
  //  AddRootFiles(data, 133, 0, 0 );
  // run 140 background
  //  AddRootFiles(data, 140, 0, 3 );
  // run 191 background
  // AddRootFiles(data,191, 0, 0 );
  // run 202 background
  //  AddRootFiles(data,202, 0, 0 );
  // run 206 background
  //  AddRootFiles(data,206, 0, 0 );
  // run 208 background
  //  AddRootFiles(data,208, 0, 9 );
  // run 1003 backgrlound
  //  AddRootFiles(data,1003, 0, 0 );
  // run 1021 background
  //  AddRootFiles(data,1021, 0, 0 );
  // run 2000 background
  //AddRootFiles(data,2000, 0, 1 );
  
  // run85, 60Co, a half-day run
  //AddRootFiles(data, 85, 0, 149); // labr3 only? 

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
  //    AddRootFiles(data, 130, 0, 27); // even further to the right
  //    AddRootFiles(data, 134, 0, 40); // back to run-127
  

  
  // Run 172
  //AddRootFiles(data, 172, 0, 257);  // 258 segments in total
  //AddRootFiles(data, 172, 0, 0);  // 
  //AddRootFiles(data, 172, 0, 9); 

  // // // 18x
  // AddRootFiles(data, 181, 1, 95);
  // AddRootFiles(data, 182, 1, 89);
  // //  AddRootFiles(data, 183, 11, 22); // position test, 22 in total
  // AddRootFiles(data, 184, 0, 41);
  // AddRootFiles(data, 185, 0, 28);
  // // // //  AddRootFiles(data, 186, 0, 199);
  // AddRootFiles(data, 187, 0, 87);
  // AddRootFiles(data, 188, 0, 51);
  // AddRootFiles(data, 189, 0, 8); 

	       
  // // // 186
  //AddRootFiles(data, 186, 0, 1094); // 1095 in total
  //AddRootFiles(data, 186, 0, 9);//test


  // // // 19x
  // AddRootFiles(data, 192, 0, 9); 
  // AddRootFiles(data, 193, 0, 14); 
  // AddRootFiles(data, 194, 0, 8); 
  // AddRootFiles(data, 195, 0, 13);
  // AddRootFiles(data, 196, 0, 10); 
  //AddRootFiles(data, 197, 0, 785); // 785 in total
  // AddRootFiles(data, 198, 0, 299); // 299 in total
  // AddRootFiles(data, 199, 0, 1088); // 1089 in total
  // AddRootFiles(data, 199, 1088, 1088); // test
  //AddRootFiles(data, 199, 0, 555); // figuring out size problems
	  
  
  // 2xx
  // AddRootFiles(data, 200, 0, 105); // 105 in total
  // AddRootFiles(data, 201, 0, 110); // 110 in total
  // AddRootFiles(data, 203, 0, 39); // 39 in total
  // AddRootFiles(data, 204, 0, 21); // 110 in total
  // AddRootFiles(data, 205, 0, 121); // 121 in total
  // AddRootFiles(data, 207, 0, 82); // 121 in total
    
  // // // 208, background
  // // //  AddRootFiles(data, 208, 0, 9); 

  // // //
  // // // PID was shifted during run-1001/1002  
  // AddRootFiles(data, 1004, 0, 15);
  // AddRootFiles(data, 1005, 0, 88);
  // AddRootFiles(data, 1006, 0, 19);
  // AddRootFiles(data, 1007, 0, 4);
  // AddRootFiles(data, 1008, 0, 58);
  // AddRootFiles(data, 1009, 0, 56);
  // AddRootFiles(data, 1010, 0, 35);
  // AddRootFiles(data, 1011, 0, 47);
  // AddRootFiles(data, 1012, 0, 17);
  // // // D3 was not matched in A1900
  // // // different PID from this point?? YES!!!
  // AddRootFiles(data, 1014, 0, 110);
  // AddRootFiles(data, 1015, 0, 16);
  // AddRootFiles(data, 1017, 0, 227);
  // AddRootFiles(data, 1019, 0, 98);
  // AddRootFiles(data, 1020, 0, 55);
  // AddRootFiles(data, 1022, 0, 14);
  // AddRootFiles(data, 1023, 0, 303);


  // e18401
  // 1000 - Co-60
  //  AddRootFiles(data, 1000, 0, 5);
  // end of beam time, Co-60
  //  AddRootFiles(data, 2001, 0, 59);
  //AddRootFiles(data, 2004, 200, 300);//Previously set, why?
  //AddRootFiles(data, 2004, 120, 130); //test
  //AddRootFiles(data, 2003, 0, 47); 
    AddRootFiles(data, 2004, 101,354);
  // ConvertChainToTree(data, data1);
  //AddRootFiles(data, 2004, 200, 210);//test
  
  // // run-3006
  // AddRootFiles(data, 3006, 0, 99); 

  
  

    TProof *proof = TProof::Open("workers=30");
   data->SetProof();

  //12/29/21
   data->Process("Timing_Branches.C+");
    // data->Process("cfdtiming1.C+");
  // data->Process("cfdselector.C+");
   // data->Process("cfdtiming1_dynode.C+");
  // update after 07/31/20
  //data->Process("segaselector.C++");
  //data->Process("gammaSelector.C"); //root 6.16
  //data->Process("gamma_spec.C+");
  
  // detach from current PROOF session
  data->SetProof(0);

  
  //display process details
    gProof->GetQueryResult()->Print();

  

  
}
