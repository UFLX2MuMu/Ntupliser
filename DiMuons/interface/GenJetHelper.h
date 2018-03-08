
#ifndef GENJET_HELPER
#define GENJET_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/GenJetInfo.h"

void FillGenJetInfos( GenJetInfos& _genJetInfos, 
		      const edm::Handle < reco::GenJetCollection >& genJets, 
		      bool isMC);

// static
bool genJet_sortByPt(reco::GenJet i, reco::GenJet j);

#endif  // #ifndef GENJET_HELPER
