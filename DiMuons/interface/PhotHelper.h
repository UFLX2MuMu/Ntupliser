
#ifndef PHOT_HELPER
#define PHOT_HELPER

#include "Math/LorentzVector.h" // ROOT::Math::LorentzVector

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/PhotInfo.h"

void FillPhotInfos( PhotInfos& _photInfos, const reco::PFCandidateCollection photsSelected,
		    const edm::Handle<pat::PackedCandidateCollection> pfCands, const pat::MuonCollection muons, const double _phot_iso_dR );

reco::PFCandidateCollection SelectPhots( const edm::Handle<pat::PackedCandidateCollection> pfCands, 
                                        const pat::MuonCollection muons, 
                                        const pat::ElectronCollection eles,
                                        const double _phot_pT_min,
                                        const double _phot_eta_max,
                                        const double _phot_etaGap_min,
                                        const double _phot_etaGap_max,
                                        const double _phot_dRPhoMu_max,
                                        const double _phot_dROverEt2_max,
                                        const double _phot_iso_dR,
                                        const double _phot_iso_max);

double photRelIso(reco::PFCandidate phot, edm::Handle<pat::PackedCandidateCollection> pfCands, const double _phot_iso_dR);

#endif  // #ifndef PHOT_HELPER
