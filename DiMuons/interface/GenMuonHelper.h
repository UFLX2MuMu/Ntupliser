
#ifndef GENMUON_HELPER
#define GENMUON_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/GenMuonInfo.h"
#include "Ntupliser/DiMuons/interface/GenParentInfo.h"

void FillGenMuonInfos( GenMuonInfos& _genMuonInfos, GenParentInfos& _genParentInfos,
		       const edm::Handle < reco::GenParticleCollection >& genPartons,
		       const bool isMC );

#endif  // #ifndef GENMUON_HELPER
