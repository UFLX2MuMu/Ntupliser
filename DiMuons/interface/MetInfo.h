
#ifndef MET_INFO
#define MET_INFO

#include <vector>
#include "TMath.h"


struct MetInfo {

  Float_t px;
  Float_t py;
  Float_t pt;
  Float_t phi;
  Float_t sumEt;

  void init();

};

#endif  // #ifndef MET_INFO
