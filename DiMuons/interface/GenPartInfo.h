
#ifndef GENPART_INFO
#define GENPART_INFO

#include <vector>
#include "TMath.h"

struct GenPartInfo {

  Float_t charge = -999;
  Float_t mass   = -999;
  Float_t pt     = -999;
  Float_t ptErr  = -999;
  Float_t eta    = -999;  // pseudo rapidity
  Float_t y      = -999;  // rapidity
  Float_t phi    = -999;  // phi

};

typedef std::vector<GenPartInfo> GenPartInfos;

#endif  // #ifndef GENPART_INFO
