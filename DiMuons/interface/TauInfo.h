
#ifndef TAU_INFO
#define TAU_INFO

#include <vector>
#include "TMath.h"

struct TauInfo {

  // Double_t tauID[idArraySize] = -999;
  
  Float_t charge = -999;
  Float_t pt     = -999;
  Float_t eta    = -999;
  Float_t phi    = -999;

  Float_t d0_PV = -999;
  Float_t dz_PV = -999;
 
  Bool_t isPF = -999;

};

typedef std::vector<TauInfo> TauInfos;

#endif  // #ifndef TAU_INFO
