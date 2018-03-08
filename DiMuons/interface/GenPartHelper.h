
#ifndef GENPART_HELPER
#define GENPART_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/GenPartInfo.h"

void FillGenPartInfo( GenPartInfo& _genPartInfo,
		      const reco::Candidate& genPart );

void FillBosonAndMuDaughters( const reco::Candidate& boson,
			      GenPartInfo& _genGpreFSR,  GenPartInfo& _genM1GpreFSR,  GenPartInfo& _genM2GpreFSR,
			      GenPartInfo& _genGpostFSR, GenPartInfo& _genM1GpostFSR, GenPartInfo& _genM2GpostFSR,
			      GenPartInfo& _genZpreFSR,  GenPartInfo& _genM1ZpreFSR,  GenPartInfo& _genM2ZpreFSR,
			      GenPartInfo& _genZpostFSR, GenPartInfo& _genM1ZpostFSR, GenPartInfo& _genM2ZpostFSR,
			      GenPartInfo& _genHpreFSR,  GenPartInfo& _genM1HpreFSR,  GenPartInfo& _genM2HpreFSR,
			      GenPartInfo& _genHpostFSR, GenPartInfo& _genM1HpostFSR, GenPartInfo& _genM2HpostFSR,
			      GenPartInfo& _genWpreFSR,  GenPartInfo& _genMWpreFSR,
			      GenPartInfo& _genWpostFSR, GenPartInfo& _genMWpostFSR );

#endif  // #ifndef GENPART_HELPER

