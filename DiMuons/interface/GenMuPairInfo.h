
#ifndef GEN_MU_PAIR_INFO
#define GEN_MU_PAIR_INFO

#include <vector>
#include "TMath.h"

struct GenMuPairInfo {

  Int_t iMu1      = -999;
  Int_t iMu2      = -999;
  Int_t mother_ID = -999;
  Int_t postFSR   = -999;
  Int_t charge    = -999;

  Double_t mass  = -999;
  Double_t pt    = -999;
  Double_t eta   = -999;
  Double_t rapid = -999;
  Double_t phi   = -999;
  Double_t dR    = -999;
  Double_t dEta  = -999;
  Double_t dPhi  = -999;

};

typedef std::vector<GenMuPairInfo> GenMuPairInfos;

#endif  // #ifndef GEN_MU_PAIR_INFO
