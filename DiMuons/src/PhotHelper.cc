
#include "Ntupliser/DiMuons/interface/PhotHelper.h"

void FillPhotInfos( PhotInfos& _photInfos, const reco::PFCandidateCollection photsSelected,
		    const edm::Handle<pat::PackedCandidateCollection> pfCands ) {
  
  _photInfos.clear();
  int nPhots = photsSelected.size();
  
  for (int i = 0; i < nPhots; i++) {

    reco::PFCandidate phot = photsSelected.at(i);
    PhotInfo _photInfo;

    // Basic kinematics
    _photInfo.pt     = phot.pt();
    _photInfo.eta    = phot.eta();
    _photInfo.phi    = phot.phi();

    _photInfo.relIso = PhotCalcRelIso( phot, pfCands );

    _photInfos.push_back( _photInfo );
  } // End loop: for (int i = 0; i < nPhots; i++)

}


reco::PFCandidateCollection SelectPhots( const edm::Handle<pat::PackedCandidateCollection> pfCands ) {

  reco::PFCandidateCollection photsSelected;

  if ( !pfCands.isValid() ) {
    std::cout << "No valid photon collection" << std::endl;
    return photsSelected;
  }

  for (const pat::PackedCandidate & iPFCand : *pfCands) {  // Fill photons from PF candidates                                                                                                                                                            
    if ( iPFCand.charge() == 0 && iPFCand.pdgId() == 22 && iPFCand.pt() > 2.0 &&
	 PhotCalcRelIso( reco::PFCandidate(0, iPFCand.p4(), reco::PFCandidate::gamma), pfCands ) < 2.0 ) {
      photsSelected.push_back( reco::PFCandidate(0, iPFCand.p4(), reco::PFCandidate::gamma) );
    }
  }

  return photsSelected;
}


double PhotCalcRelIso( const reco::PFCandidate phot, const edm::Handle<pat::PackedCandidateCollection> pfCands ) {

  // From Oliver Reiger, double FSRRecoveryProducer::photonPfIso03
  // https://gitlab.cern.ch/uhh-cmssw/CAST/blob/final_CMSSW_9_4_9/FSRPhotons/plugins/FSRRecoveryProducer.cc#L69

  double sum_pt = 0.0;

  for (const pat::PackedCandidate &pfc : *pfCands) {
    double dR = deltaR(phot.p4(), pfc.p4());
    if (dR >= 0.3) continue;

    if (pfc.charge() != 0 && abs(pfc.pdgId()) == 211 && pfc.pt() > 0.2) {
      if (dR > 0.0001) sum_pt += pfc.pt();
    } else if (pfc.charge() == 0 && (abs(pfc.pdgId()) == 22 || abs(pfc.pdgId()) == 130) && pfc.pt() > 0.5) {
      if (dR > 0.01  ) sum_pt += pfc.pt();
    }
  }

  return (sum_pt / phot.pt());
} // End function: double PhotCalcRelIso( const reco::PFCandidate phot, const edm::Handle<pat::PackedCandidateCollection> pfCands ) {
