
#ifndef MUON_INFO
#define MUON_INFO

#include <vector>
#include "TMath.h"

struct MuonInfo {

  Bool_t isTracker    = -999;
  Bool_t isStandAlone = -999;
  Bool_t isGlobal     = -999;

  Bool_t isTightID      = -999;
  Bool_t isMediumID     = -999;
  Bool_t isMediumID2016 = -999;
  Bool_t isLooseID      = -999;
  Float_t lepMVA        = -999;

  Int_t    charge = -999;
  Double_t pt     = -999;
  Double_t ptErr  = -999;
  Double_t eta    = -999;
  Double_t phi    = -999;

  Double_t pt_trk    = -999;
  Double_t ptErr_trk = -999;
  Double_t eta_trk   = -999;
  Double_t phi_trk   = -999;

  Double_t pt_KaMu           = -999;
  Double_t ptErr_KaMu        = -999;
  Double_t pt_KaMu_sys_up    = -999;
  Double_t pt_KaMu_sys_down  = -999;
  Double_t pt_KaMu_clos_up   = -999;
  Double_t pt_KaMu_clos_down = -999;

  Double_t pt_Roch           = -999;
  Double_t ptErr_Roch        = -999;
  Double_t pt_Roch_sys_up    = -999;
  Double_t pt_Roch_sys_down  = -999;

  Float_t d0_BS        = -999;
  Float_t dz_BS        = -999;
  Float_t d0_PV        = -999;
  Float_t dz_PV        = -999;
  Float_t d0_PV_kinfit = -999;
  Float_t dz_PV_kinfit = -999;
  Float_t chi2_kinfit  = -999;
  Int_t   ndf_kinfit   = -999;
  Float_t IP_3D        = -999;
  Float_t SIP_3D       = -999;
  Float_t segCompat    = -999;

  Float_t relIso            = -999;
  Float_t relCombIso        = -999;
  Float_t trackIsoSumPt     = -999;
  Float_t trackIsoSumPtCorr = -999;
  Float_t hcalIso           = -999;
  Float_t ecalIso           = -999;
  Float_t relIsoEA03        = -999;
  Float_t relIsoEA04        = -999;
  Float_t miniIso           = -999;
  Float_t miniIsoCharged    = -999;

  Int_t   jet_trkMult = -999;
  Float_t jet_ptRel   = -999;
  Float_t jet_ptRatio = -999;
  Float_t jet_deepCSV = -999;

  // PF information
  Bool_t isPF = -999;

  Double_t pt_kinfit    = -999;
  Double_t ptErr_kinfit = -999;
  Double_t pt_PF        = -999;
  Double_t ptErr_PF     = -999;
  Double_t eta_PF       = -999;
  Double_t phi_PF       = -999;

  Float_t sumChargedHadronPtR03   = -999;  // sum-pt of charged Hadron
  Float_t sumChargedParticlePtR03 = -999;  // sum-pt of charged Particles(inludes e/mu)
  Float_t sumNeutralHadronEtR03   = -999;  // sum pt of neutral hadrons
  Float_t sumPhotonEtR03          = -999;  // sum pt of PF photons
  Float_t sumPUPtR03              = -999;  // sum pt of charged Particles not from PV  (for Pu corrections)

  Float_t sumChargedHadronPtR04   = -999;
  Float_t sumChargedParticlePtR04 = -999;
  Float_t sumNeutralHadronEtR04   = -999;
  Float_t sumPhotonEtR04          = -999;
  Float_t sumPUPtR04              = -999;

  const static Int_t nTrig = 9; // this number has to match the number of requested triggers in python/UFDiMuonsAnalyzer_*cff.py
  Bool_t  isHltMatched[nTrig] = {0};
  Float_t hltEff      [nTrig] = {0};
  Float_t hltPt       [nTrig] = {0};
  Float_t hltEta      [nTrig] = {0};
  Float_t hltPhi      [nTrig] = {0};

  Float_t GEN_pt  = -999;
  Float_t GEN_dR  = -999;
  Int_t   GEN_idx = -999; // Index of the matched genMuon in the genMuonInfo collections

};

typedef std::vector<MuonInfo> MuonInfos;

#endif  // #ifndef MUON_INFO
