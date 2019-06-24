
#ifndef GENPARENT_INFO
#define GENPARENT_INFO

#include <vector>
#include "TMath.h"

struct GenParentInfo {

  Int_t ID         = -999;
  Int_t status     = -999;
  Int_t nDaughters = -999;

  Float_t pt   = -999;
  Float_t eta  = -999;
  Float_t phi  = -999;
  Float_t mass = -999;
  Int_t charge = -999;

  Int_t daughter_1_ID     = -999;
  Int_t daughter_2_ID     = -999;
  Int_t daughter_1_status = -999;
  Int_t daughter_2_status = -999;
  Int_t daughter_1_idx    = -999;
  Int_t daughter_2_idx    = -999;

};

typedef std::vector<GenParentInfo> GenParentInfos;

#endif  // #ifndef GENPARENT_INFO
