
#ifndef MET_HELPER
#define MET_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/MetInfo.h"


void FillMetInfo( MetInfo& _metInfo,
		  const edm::Handle < pat::METCollection >& mets, 
		  const edm::Event& iEvent, const TLorentzVector _dMet );

#endif  // #ifndef MET_HELPER
