
#ifndef PHOT_INFO
#define PHOT_INFO

#include <vector>
#include "TMath.h"


struct PhotInfo {

  Float_t pt     = -999;
  Float_t eta    = -999;
  Float_t phi    = -999;
  Float_t dREtg = -999;
  Float_t relIso   = -999;
  Float_t dRPhoMu = -999;
  Int_t mu_idx = -999;
};

typedef std::vector<PhotInfo> PhotInfos;

#endif  // #ifndef PHOT_INFO                                                                                                                      
