
#ifndef ELE_INFO
#define ELE_INFO

#include <vector>
#include "TMath.h"

struct EleInfo {

  Bool_t isTightID         ;
  Bool_t isMediumID        ;
  Bool_t isLooseID         ;
  Bool_t isVetoID          ;
  Bool_t passConversionVeto;

  Float_t mvaID;   // Central EGamma POG MVA ID
  Float_t lepMVA;  // Prompt vs. non-prompt MVA ID from TOP-18-008

  Int_t   charge;
  Float_t pt    ;
  Float_t eta   ;
  Float_t phi   ;

  Float_t d0_PV;
  Float_t dz_PV;
  Float_t IP_3D;
  Float_t SIP_3D;

  Float_t missingInnerHits;
 
  Bool_t isPF; 

  Float_t relIso               ;
  Float_t sumChargedHadronPtR03;  // sum-pt of charged Hadron 
  Float_t sumNeutralHadronEtR03;  // sum pt of neutral hadrons
  Float_t sumPhotonEtR03       ;  // sum pt of PF photons
  Float_t sumPUPtR03           ;  // sum pt of charged Particles not from PV (for Pu corrections)
  Float_t relIsoEA             ;
  Float_t miniIso              ;
  Float_t miniIsoCharged       ;

  Int_t   jet_trkMult;
  Float_t jet_ptRel  ;
  Float_t jet_ptRatio;
  Float_t jet_deepCSV;


  void init();

};

typedef std::vector<EleInfo> EleInfos;

#endif  // #ifndef ELE_INFO                                                                                                                      
