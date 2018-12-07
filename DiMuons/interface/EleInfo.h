
#ifndef ELE_INFO
#define ELE_INFO

#include <vector>
#include "TMath.h"

struct EleInfo {

  Bool_t isTightID          = -999;
  Bool_t isMediumID         = -999;
  Bool_t isLooseID          = -999;
  Bool_t isVetoID           = -999;
  Bool_t passConversionVeto = -999;

  Float_t mvaID  = -999;  // Central EGamma POG MVA ID
  Float_t lepMVA = -999;  // Prompt vs. non-prompt MVA ID from TOP-18-008

  Int_t   charge = -999;
  Float_t pt     = -999;
  Float_t eta    = -999;
  Float_t phi    = -999;

  Float_t d0_PV  = -999;
  Float_t dz_PV  = -999;
  Float_t IP_3D  = -999;
  Float_t SIP_3D = -999;

  Float_t missingInnerHits = -999;
 
  Bool_t isPF = -999; 

  Float_t relIso                = -999;
  Float_t sumChargedHadronPtR03 = -999;  // sum-pt of charged Hadron 
  Float_t sumNeutralHadronEtR03 = -999;  // sum pt of neutral hadrons
  Float_t sumPhotonEtR03        = -999;  // sum pt of PF photons
  Float_t sumPUPtR03            = -999;  // sum pt of charged Particles not from PV (for Pu corrections)
  Float_t relIsoEA              = -999;
  Float_t miniIso               = -999;
  Float_t miniIsoCharged        = -999;

  Int_t   jet_trkMult = -999;
  Float_t jet_ptRel   = -999;
  Float_t jet_ptRatio = -999;
  Float_t jet_deepCSV = -999;

};

typedef std::vector<EleInfo> EleInfos;

#endif  // #ifndef ELE_INFO                                                                                                                      
