
#ifndef PHOT_HELPER
#define PHOT_HELPER

#include "Math/LorentzVector.h" // ROOT::Math::LorentzVector

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/PhotInfo.h"

void FillPhotInfos( PhotInfos& _photInfos, const reco::PFCandidateCollection photsSelected,
		    const edm::Handle<pat::PackedCandidateCollection> pfCands, const pat::MuonCollection muons );

reco::PFCandidateCollection SelectPhots( const edm::Handle<pat::PackedCandidateCollection> pfCands, 
                                        const pat::MuonCollection muons, 
                                        const pat::ElectronCollection eles);

double photonPfIso03(reco::PFCandidate phot, edm::Handle<pat::PackedCandidateCollection> pfCands);

#endif  // #ifndef PHOT_HELPER
