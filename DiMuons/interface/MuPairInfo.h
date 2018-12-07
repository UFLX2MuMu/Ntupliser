
#ifndef MU_PAIR_INFO
#define MU_PAIR_INFO

#include <vector>
#include "TMath.h"

struct MuPairInfo {

  Int_t iMu1 = -999;
  Int_t iMu2 = -999;

  Double_t mass     = -999;
  Double_t massErr  = -999;
  Double_t pt       = -999;
  Double_t eta      = -999;
  Double_t rapid    = -999;
  Double_t phi      = -999;
  Int_t    charge   = -999;
  Double_t dR       = -999;
  Double_t dEta     = -999;
  Double_t dPhi     = -999;
  Double_t dPhiStar = -999;

  Double_t mass_PF    = -999;
  Double_t massErr_PF = -999;
  Double_t pt_PF      = -999;

  Double_t mass_kinfit    = -999;
  Double_t massErr_kinfit = -999;
  Double_t pt_kinfit      = -999;

  Double_t mass_trk    = -999;
  Double_t massErr_trk = -999;
  Double_t pt_trk      = -999;

  Double_t mass_KaMu           = -999;
  Double_t massErr_KaMu        = -999;
  Double_t pt_KaMu             = -999;
  Double_t mass_KaMu_clos_up   = -999;
  Double_t pt_KaMu_clos_up     = -999;
  Double_t mass_KaMu_clos_down = -999;
  Double_t pt_KaMu_clos_down   = -999;
  Double_t mass_KaMu_sys_up    = -999;
  Double_t pt_KaMu_sys_up      = -999;
  Double_t mass_KaMu_sys_down  = -999;
  Double_t pt_KaMu_sys_down    = -999;

  Double_t mass_Roch          = -999;
  Double_t massErr_Roch       = -999;
  Double_t pt_Roch            = -999;
  Double_t mass_Roch_sys_up   = -999;
  Double_t pt_Roch_sys_up     = -999;
  Double_t mass_Roch_sys_down = -999;
  Double_t pt_Roch_sys_down   = -999;

};

typedef std::vector<MuPairInfo> MuPairInfos;

#endif  // #ifndef MU_PAIR_INFO
