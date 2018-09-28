
#ifndef MU_PAIR_INFO
#define MU_PAIR_INFO

#include <vector>
#include "TMath.h"

struct MuPairInfo {

  Int_t iMu1;
  Int_t iMu2;

  Double_t mass;
  Double_t massErr;
  Double_t pt;
  Double_t eta;
  Double_t rapid;
  Double_t phi;
  Int_t    charge;
  Double_t dR;
  Double_t dEta;
  Double_t dPhi;
  Double_t dPhiStar;

  Double_t mass_PF;
  Double_t massErr_PF;
  Double_t pt_PF;

  Double_t mass_trk;
  Double_t massErr_trk;
  Double_t pt_trk;

  Double_t mass_KaMu;
  Double_t massErr_KaMu;
  Double_t pt_KaMu;
  Double_t mass_KaMu_clos_up;
  Double_t pt_KaMu_clos_up;
  Double_t mass_KaMu_clos_down;
  Double_t pt_KaMu_clos_down;
  Double_t mass_KaMu_sys_up;
  Double_t pt_KaMu_sys_up;
  Double_t mass_KaMu_sys_down;
  Double_t pt_KaMu_sys_down;

  Double_t mass_Roch;
  Double_t massErr_Roch;
  Double_t pt_Roch;
  Double_t mass_Roch_sys_up;
  Double_t pt_Roch_sys_up;
  Double_t mass_Roch_sys_down;
  Double_t pt_Roch_sys_down;

  Double_t mass_kinfit;
  Double_t massErr_kinfit;
  Double_t pt_kinfit;

  void init();

};

typedef std::vector<MuPairInfo> MuPairInfos;

#endif  // #ifndef MU_PAIR_INFO
