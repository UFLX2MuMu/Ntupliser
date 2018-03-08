
#ifndef JET_PAIR_INFO
#define JET_PAIR_INFO

#include <vector>
#include "TMath.h"

struct JetPairInfo {

  Int_t iJet1;
  Int_t iJet2;

  Float_t mass;
  Float_t pt;
  Float_t eta;
  Float_t phi;
  Float_t dR;
  Float_t dEta;
  Float_t dPhi;

  void init();

};

typedef std::vector<JetPairInfo> JetPairInfos;

#endif  // #ifndef JET_PAIR_INFO
