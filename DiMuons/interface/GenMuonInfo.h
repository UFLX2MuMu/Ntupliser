
#ifndef GENMUON_INFO
#define GENMUON_INFO

#include <vector>
#include "TMath.h"

struct GenMuonInfo {

  Int_t status;
  Int_t nMothers;
  Int_t postFSR;

  Float_t pt;
  Float_t eta;
  Float_t phi;
  Float_t mass;
  Int_t charge;

  Float_t FSR_pt;
  Float_t FSR_eta;
  Float_t FSR_phi;
  Float_t FSR_mass;

  Int_t mother_ID;
  Int_t mother_status;
  Int_t mother_idx;

  void init();

};

typedef std::vector<GenMuonInfo> GenMuonInfos;

#endif  // #ifndef GENMUON_INFO
