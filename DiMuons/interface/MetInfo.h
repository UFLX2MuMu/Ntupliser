
#ifndef MET_INFO
#define MET_INFO

#include <vector>
#include "TMath.h"


struct MetInfo {

  Float_t px    = -999;
  Float_t py    = -999;
  Float_t pt    = -999;
  Float_t phi   = -999;
  Float_t sumEt = -999;

  void init();

};

#endif  // #ifndef MET_INFO
