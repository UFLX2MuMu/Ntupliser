
#ifndef PHOT_HELPER
#define PHOT_HELPER

#include "Math/LorentzVector.h" // ROOT::Math::LorentzVector

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/PhotInfo.h"

void FillPhotInfos( PhotInfos& _photInfos, const reco::PFCandidateCollection photsSelected,
		    const edm::Handle<pat::PackedCandidateCollection> pfCands );

reco::PFCandidateCollection SelectPhots( const edm::Handle<pat::PackedCandidateCollection> pfCands );

double PhotCalcRelIso( const reco::PFCandidate phot, const edm::Handle<pat::PackedCandidateCollection> pfCands );

#endif  // #ifndef PHOT_HELPER
