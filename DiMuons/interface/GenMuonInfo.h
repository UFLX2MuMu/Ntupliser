
#ifndef GENMUON_INFO
#define GENMUON_INFO

#include <vector>
#include "TMath.h"

struct GenMuonInfo {

  Int_t status   = -999;
  Int_t nMothers = -999;
  Int_t postFSR  = -999;

  Float_t pt   = -999;
  Float_t eta  = -999;
  Float_t phi  = -999;
  Float_t mass = -999;
  Int_t charge = -999;

  Float_t FSR_pt   = -999;
  Float_t FSR_eta  = -999;
  Float_t FSR_phi  = -999;
  Float_t FSR_mass = -999;

  Int_t mother_ID     = -999;
  Int_t mother_status = -999;
  Int_t mother_idx    = -999;

};

typedef std::vector<GenMuonInfo> GenMuonInfos;

#endif  // #ifndef GENMUON_INFO
