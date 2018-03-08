
#ifndef GENPARENT_INFO
#define GENPARENT_INFO

#include <vector>
#include "TMath.h"

struct GenParentInfo {

  Int_t ID;
  Int_t status;
  Int_t nDaughters;

  Float_t pt;
  Float_t eta;
  Float_t phi;
  Float_t mass;
  Int_t charge;

  Int_t daughter_1_ID;
  Int_t daughter_2_ID;
  Int_t daughter_1_status;
  Int_t daughter_2_status;
  Int_t daughter_1_idx;
  Int_t daughter_2_idx;

  void init();

};

typedef std::vector<GenParentInfo> GenParentInfos;

#endif  // #ifndef GENPARENT_INFO
