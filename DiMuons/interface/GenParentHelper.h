
#ifndef GENPARENT_HELPER
#define GENPARENT_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/GenParentInfo.h"

void FillGenParentInfos( GenParentInfos& _genParentInfos,
                         const edm::Handle < reco::GenParticleCollection >& genPartons,
                         const std::vector<int> IDs, const bool isMC );

#endif  // #ifndef GENPARENT_HELPER
