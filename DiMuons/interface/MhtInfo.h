
#ifndef MHT_INFO
#define MHT_INFO

#include <vector>
#include "TMath.h"


struct MhtInfo {

  Float_t pt;
  Float_t phi;
  Float_t MT;
  Float_t mass;

  Float_t pt_had;
  Float_t phi_had;
  Float_t MT_had;
  Float_t mass_had;

  void init();

};

#endif  // #ifndef MHT_INFO
