
#include "Ntupliser/DiMuons/interface/GenJetHelper.h"

void FillGenJetInfos( GenJetInfos& _genJetInfos,
		      const edm::Handle < reco::GenJetCollection >& genJets, 
		      bool isMC ) { 

  _genJetInfos.clear();
  if ( !genJets.isValid() ) {
    if (isMC) std::cout << "No valid collection of GEN jets" << std::endl;
    return;
  }

  reco::GenJetCollection sortedGenJets = (*genJets);
  sort(sortedGenJets.begin(), sortedGenJets.end(), genJet_sortByPt);
  for(unsigned int i = 0; i < sortedGenJets.size(); i++) {
    
    GenJetInfo _genJetInfo;
    
    _genJetInfo.px     = sortedGenJets[i].px();
    _genJetInfo.py     = sortedGenJets[i].py();
    _genJetInfo.pz     = sortedGenJets[i].pz();
    _genJetInfo.pt     = sortedGenJets[i].pt();
    _genJetInfo.eta    = sortedGenJets[i].eta();
    _genJetInfo.phi    = sortedGenJets[i].phi();
    _genJetInfo.mass   = sortedGenJets[i].mass();
    _genJetInfo.charge = sortedGenJets[i].charge();
    
    _genJetInfos.push_back( _genJetInfo );
  }

}

bool genJet_sortByPt (reco::GenJet i, reco::GenJet j) { 
  return ( i.pt() > j.pt() ); 
}
