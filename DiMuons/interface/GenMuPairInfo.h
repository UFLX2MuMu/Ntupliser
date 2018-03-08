
#ifndef GEN_MU_PAIR_INFO
#define GEN_MU_PAIR_INFO

#include <vector>
#include "TMath.h"

struct GenMuPairInfo {

  Int_t iMu1;
  Int_t iMu2;
  Int_t mother_ID;
  Int_t postFSR;
  Int_t charge;

  Double_t mass ;
  Double_t pt   ;
  Double_t eta  ;
  Double_t rapid;
  Double_t phi  ;
  Double_t dR   ;
  Double_t dEta ;
  Double_t dPhi ;

  void init();

};

typedef std::vector<GenMuPairInfo> GenMuPairInfos;

#endif  // #ifndef GEN_MU_PAIR_INFO
