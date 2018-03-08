
#include "Ntupliser/DiMuons/interface/GenParentHelper.h"

void FillGenParentInfos( GenParentInfos& _genParentInfos,
			 const edm::Handle < reco::GenParticleCollection >& genPartons,
			 const std::vector<int> IDs, const bool isMC ) {

  _genParentInfos.clear();
  
  for (unsigned int i = 0; i < genPartons->size(); i++) {

    const reco::Candidate& parent = genPartons->at(i);
    if ( parent.status() != 62 &&  // "Final" GEN particle or photon with daughters
	 (parent.pdgId() != 22 || parent.numberOfDaughters() != 2) ) continue;

    bool good_ID = false;
    for (unsigned int j = 0; j < IDs.size(); j++) {
      if ( abs(parent.pdgId()) == IDs.at(j) ) {
	good_ID = true;
      }
    }
    if (not good_ID) continue;
    
    GenParentInfo _genParentInfo;
    _genParentInfo.init();
    
    _genParentInfo.ID         = parent.pdgId();
    _genParentInfo.status     = parent.status();
    _genParentInfo.nDaughters = parent.numberOfDaughters();
    
    _genParentInfo.pt     = parent.pt();
    _genParentInfo.eta    = parent.eta();
    _genParentInfo.phi    = parent.phi();
    _genParentInfo.mass   = parent.mass();
    _genParentInfo.charge = parent.charge();
    
    if (parent.numberOfDaughters() > 0) {
      _genParentInfo.daughter_1_ID     = parent.daughter(0)->pdgId();
      _genParentInfo.daughter_1_status = parent.daughter(0)->status();
    }    
    if (parent.numberOfDaughters() > 1) {
      _genParentInfo.daughter_2_ID     = parent.daughter(1)->pdgId();
      _genParentInfo.daughter_2_status = parent.daughter(1)->status();
    }
    
    _genParentInfos.push_back( _genParentInfo );
  } // End loop: for (unsigned int i = 0; i < genPartons->size(); i++) 

}
