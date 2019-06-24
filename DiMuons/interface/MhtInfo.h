
#ifndef MHT_INFO
#define MHT_INFO

#include <vector>
#include "TMath.h"


struct MhtInfo {

  Float_t pt   = -999;
  Float_t phi  = -999;
  Float_t MT   = -999;
  Float_t mass = -999;

  Float_t pt_had   = -999;
  Float_t phi_had  = -999;
  Float_t MT_had   = -999;
  Float_t mass_had = -999;

  void init();

};

#endif  // #ifndef MHT_INFO
