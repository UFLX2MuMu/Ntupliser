
#ifndef MUON_INFO
#define MUON_INFO

#include <vector>
#include "TMath.h"

struct MuonInfo {

  Bool_t isTracker   ;
  Bool_t isStandAlone;
  Bool_t isGlobal    ;

  Bool_t isTightID ;
  Bool_t isMediumID;
  Bool_t isMediumID2016;
  Bool_t isLooseID ;

  Int_t    charge;
  Double_t pt    ;
  Double_t ptErr ;
  Double_t eta   ;
  Double_t phi   ;

  Double_t pt_trk   ;
  Double_t ptErr_trk;
  Double_t eta_trk  ;
  Double_t phi_trk  ;

  Double_t pt_KaMu          ;
  Double_t ptErr_KaMu       ;
  Double_t pt_KaMu_sys_up   ;
  Double_t pt_KaMu_sys_down ;
  Double_t pt_KaMu_clos_up  ;
  Double_t pt_KaMu_clos_down;

  Double_t pt_Roch          ;
  Double_t ptErr_Roch       ;
  Double_t pt_Roch_sys_up   ;
  Double_t pt_Roch_sys_down ;

  Double_t pt_kinfit        ;
  Double_t ptErr_kinfit     ;

  Float_t d0_BS;
  Float_t dz_BS;

  Float_t d0_PV;
  Float_t dz_PV;

  Float_t d0_PV_kinfit;
  Float_t dz_PV_kinfit;
  Float_t chi2_kinfit;
  UInt_t ndf_kinfit;

  Float_t relIso           ;
  Float_t relCombIso       ;
  Float_t trackIsoSumPt    ;
  Float_t trackIsoSumPtCorr;
  Float_t hcalIso          ;
  Float_t ecalIso          ;

  // PF information
  Bool_t isPF;

  Double_t pt_PF   ;
  Double_t ptErr_PF;
  Double_t eta_PF  ;
  Double_t phi_PF  ;
  
  Float_t sumChargedHadronPtR03  ;  // sum-pt of charged Hadron
  Float_t sumChargedParticlePtR03;  // sum-pt of charged Particles(inludes e/mu)
  Float_t sumNeutralHadronEtR03  ;  // sum pt of neutral hadrons
  Float_t sumPhotonEtR03         ;  // sum pt of PF photons
  Float_t sumPUPtR03             ;  // sum pt of charged Particles not from PV  (for Pu corrections)

  Float_t sumChargedHadronPtR04  ;
  Float_t sumChargedParticlePtR04;
  Float_t sumNeutralHadronEtR04  ;
  Float_t sumPhotonEtR04         ;
  Float_t sumPUPtR04             ;

  const static Int_t nTrig = 8; // this number has to match the number of requested triggers in python/UFDiMuonsAnalyzer_*cff.py
  Bool_t  isHltMatched[nTrig];
  Float_t hltEff      [nTrig];
  Float_t hltPt       [nTrig];
  Float_t hltEta      [nTrig];
  Float_t hltPhi      [nTrig];

  Float_t GEN_pt;
  Float_t GEN_dR;

  void init();

};

typedef std::vector<MuonInfo> MuonInfos;

#endif  // #ifndef MUON_INFO
