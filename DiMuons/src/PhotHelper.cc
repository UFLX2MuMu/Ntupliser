
#include "Ntupliser/DiMuons/interface/PhotHelper.h"

// Based on Oliver Rieger's FSR recovery tool: https://gitlab.cern.ch/uhh-cmssw/fsr-photon-recovery

void FillPhotInfos( PhotInfos& _photInfos, const reco::PFCandidateCollection photsSelected,
		    const edm::Handle<pat::PackedCandidateCollection> pfCands, const pat::MuonCollection muons, const double _phot_iso_dR ) {
  
  _photInfos.clear();
  int nPhots = photsSelected.size();
  
  for (int i = 0; i < nPhots; i++) {
    reco::PFCandidate phot = photsSelected.at(i);
    PhotInfo _photInfo;

    double dRPhoMu = 0.51; // dR between photon and muon
    int mu_idx = -999; // ID of the closest muon

    for (size_t j = 0; j < muons.size(); ++j){
      const auto muon = muons.at(j);
      // Find closest photon to the muon
      if (deltaR(muon.eta(), muon.phi(), phot.eta(), phot.phi()) <= dRPhoMu){
        dRPhoMu = deltaR(muon.eta(), muon.phi(), phot.eta(), phot.phi());
        mu_idx = j;
      } 
    }

    float dROverEt2 = dRPhoMu/pow(phot.pt(),2);

    // Fill photon variables
    _photInfo.pt        = phot.pt();
    _photInfo.eta       = phot.eta();
    _photInfo.phi       = phot.phi();
    _photInfo.dROverEt2 = dROverEt2;
    _photInfo.relIso    = photRelIso( phot, pfCands, _phot_iso_dR);
    _photInfo.dRPhoMu   = dRPhoMu;
    _photInfo.mu_idx    = mu_idx;

    _photInfos.push_back( _photInfo );
  } // End loop: for (int i = 0; i < nPhots; i++)

}


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
                                        const double _phot_iso_max) {

  reco::PFCandidateCollection photsSelected;

  if ( !pfCands.isValid() ) {
    std::cout << "No valid photon collection" << std::endl;
    return photsSelected;
  }


  for (pat::MuonCollection::const_iterator muon = muons.begin(), muonsEnd = muons.end(); muon !=muonsEnd; ++muon) {

    double dRPhoMu = 99; // dR between photon and muon
    reco::PFCandidate FSRPhot;
    for (std::vector<pat::PackedCandidate>::const_iterator pfCand = pfCands->begin(); pfCand != pfCands->end(); ++pfCand) {     

      if ( pfCand->charge() != 0 || pfCand->pdgId() != 22) continue; // Check if pfCand is photon
      if (abs(pfCand->eta()) > _phot_eta_max || (abs(pfCand->eta()) > _phot_etaGap_min && abs(pfCand->eta()) < _phot_etaGap_max) || pfCand->pt() < _phot_pT_min) continue; // photon kinematic selection

      // Find dR between photon and the muon
      if (deltaR(muon->eta(), muon->phi(), pfCand->eta(), pfCand->phi()) <= dRPhoMu){
        FSRPhot = reco::PFCandidate(0,pfCand->p4(),reco::PFCandidate::gamma);
        dRPhoMu = deltaR(muon->eta(), muon->phi(), FSRPhot.eta(), FSRPhot.phi());
      } else{
        continue;
      }

      // Check if the muon is closest muon
      bool closest = true;

      for (pat::MuonCollection::const_iterator muonOther = muons.begin(), muonsEnd = muons.end(); muonOther !=muonsEnd; ++muonOther) {
        if (muon == muonOther) continue;
        double dRPhoMuOther = deltaR(muonOther->eta(), muonOther->phi(), FSRPhot.eta(), FSRPhot.phi());
        if (dRPhoMuOther < dRPhoMu) {
          closest = false;
          break;
        }
      }

      if (dRPhoMu > _phot_dRPhoMu_max) continue;
      if (!closest) continue;

      // Check that is not in footprint of an electron      
      bool eleMatched = false;

      for (pat::ElectronCollection::const_iterator ele = eles.begin(), elesEnd = eles.end(); ele !=elesEnd; ++ele) {
        for (size_t nele = 0; nele < ele->associatedPackedPFCandidates().size(); nele++) {
          double ecandpt = ele->associatedPackedPFCandidates().at(nele)->pt();
          double ecandeta = ele->associatedPackedPFCandidates().at(nele)->eta();
          double ecandphi = ele->associatedPackedPFCandidates().at(nele)->phi();
          if (abs(ecandpt - FSRPhot.pt()) < 1e-10 && abs(ecandeta - FSRPhot.eta()) < 1e-10 && abs(ecandphi - FSRPhot.phi()) < 1e-10) {
            eleMatched = true;
            break;
          }
        }
      }

      if (eleMatched) continue;

      if (dRPhoMu/pow(FSRPhot.pt(),2) > _phot_dROverEt2_max) continue;
      if (photRelIso( FSRPhot, pfCands, _phot_iso_dR) > _phot_iso_max) continue;



      photsSelected.push_back(FSRPhot);
    }
  }
  return photsSelected;
}


double photRelIso(reco::PFCandidate phot, edm::Handle<pat::PackedCandidateCollection> pfCands, const double _phot_iso_dR) {
  double ptsum = 0.0;

  for (const pat::PackedCandidate &pfc : *pfCands) {
    double dr = deltaR(phot.p4(), pfc.p4());
    if (dr >= _phot_iso_dR) continue;
    if (dr < 0.0001) continue;

    if (pfc.charge() != 0 && abs(pfc.pdgId()) == 211 && pfc.pt() > 0.2) {
      if (dr > 0.0001) ptsum += pfc.pt();
    } else if (pfc.charge() == 0 && (abs(pfc.pdgId()) == 22 || abs(pfc.pdgId()) == 130) && pfc.pt() > 0.5) {
      if (dr > 0.01) ptsum += pfc.pt();
    }
  }
  return ptsum/phot.pt();
}

