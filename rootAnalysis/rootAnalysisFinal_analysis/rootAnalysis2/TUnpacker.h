#ifndef TUNPACKER_H
#define TUNPACKER_H

#include <vector>

#include "DDASRootFitHit.h"

#include "TRandom3.h"

#include "TParameters.h"

class TUnpacker
{
public:
  TUnpacker();
  int UnpackChannel(int id, TRandom3 &rng, DDASRootFitHit* ddashit, std::vector<RootHitExtension>& fits, TBetaDecayParams &bdecay, int m);
};

#endif
