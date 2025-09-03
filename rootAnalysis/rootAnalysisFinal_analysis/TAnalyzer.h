#ifndef TANALYZER_H
#define TANALYZER_H

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include "DDASRootFitHit.h"

#include "TTree.h"
#include "TChain.h"

#include "TParameters.h"

class TAnalyzer
{
 public:
  TAnalyzer();
  void ResetChannelList(std::vector<DDASRootFitHit*>  channellist, std::vector<DDASRootFitHit*>::iterator channellist_it);
  void PrintChannelList(std::vector<DDASRootFitHit*>  channellist, std::vector<DDASRootFitHit*>::iterator channellist_it);

  // creating template to pass in either TTree or TChain
  template <class T> void AnalyzeData(T* tree_in, TTree* tree_out, std::string runnumber, std::string beta_gate, std::string tofv);

  // for storing implants in list
  std::vector<TPID> implantlist;  
  // want to have latest times first to replicate original analysis
  static bool sortTime(TPID one, TPID two){return one.time > two.time;}

  static bool sortTime_Reverse(TPID one, TPID two){return one.time < two.time;}
};

#endif
