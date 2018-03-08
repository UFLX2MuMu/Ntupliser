
#import "Ntupliser/DiMuons/interface/EleInfo.h"

void EleInfo::init() {

  isPF               = -999;
  isTightID          = -999;
  isMediumID         = -999;
  isLooseID          = -999;
  isVetoID           = -999;
  passConversionVeto = -999;
  
  charge = -999;
  pt     = -999;
  eta    = -999;
  phi    = -999;
  
  d0_PV = -999;
  dz_PV = -999;
  
  missingInnerHits = -999;
  
  sumChargedHadronPtR03 = -999;
  sumNeutralHadronEtR03 = -999;
  sumPhotonEtR03        = -999;
  sumPUPtR03            = -999;

} // End void EleInfo::init()

