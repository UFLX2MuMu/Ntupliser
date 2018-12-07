
#ifndef JET_PAIR_INFO
#define JET_PAIR_INFO

#include <vector>
#include "TMath.h"

struct JetPairInfo {

  Int_t iJet1 = -999;
  Int_t iJet2 = -999;

  Float_t mass = -999;
  Float_t pt   = -999;
  Float_t eta  = -999;
  Float_t phi  = -999;
  Float_t dR   = -999;
  Float_t dEta = -999;
  Float_t dPhi = -999;

};

typedef std::vector<JetPairInfo> JetPairInfos;

#endif  // #ifndef JET_PAIR_INFO
