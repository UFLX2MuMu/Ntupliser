
#ifndef GENJET_INFO
#define GENJET_INFO

#include <vector>
#include "TMath.h"

struct GenJetInfo {

  Float_t px     = -999;
  Float_t py     = -999;
  Float_t pz     = -999;
  Float_t pt     = -999;
  Float_t eta    = -999;
  Float_t phi    = -999;
  Float_t mass   = -999;
  Float_t charge = -999;

};

typedef std::vector<GenJetInfo> GenJetInfos;

#endif  // #ifndef GENJET_INFO
