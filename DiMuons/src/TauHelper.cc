
#include "Ntupliser/DiMuons/interface/TauHelper.h"

void FillTauInfos( TauInfos& _tauInfos, 
		   const pat::TauCollection tausSelected, 
		   const std::vector<std::string> _tauIDNames) {

  _tauInfos.clear();
  int nTaus = tausSelected.size();
  
  for (int i = 0; i < nTaus; i++) {

    pat::Tau tau = tausSelected.at(i);
    TauInfo _tauInfo;

    // Basic kinematics
    _tauInfo.charge  = tau.charge();
    _tauInfo.pt      = tau.pt();
    _tauInfo.eta     = tau.eta();
    _tauInfo.phi     = tau.phi();

    // Basic quality
    _tauInfo.isPF = tau.isPFTau();

    // Basic vertexing?

    // // -------------------------
    // // ONLY SAVE BASIC VARIABLES - AWB 12.11.16
    // // -------------------------
    // if ( _outputLevel == "Slim")
    //   continue;

    // // Standard quality
    // for (unsigned int id = 0; id < _tauIDNames.size(); id++) {
    //   if (id < idArraySize)
    // 	_tauInfo.tauID[id] = tau.tauID(_tauIDNames[id]);
    //   else
    // 	std::cout << "Found " << id+1 << "th tau ID name; only " << idArraySize << " allowed in array" << std::endl;
    // }

    // Standard vertexing
    if ( !(tau.leadChargedHadrCand().isNull()) ) {
      pat::PackedCandidate const* packedLeadTauCand = dynamic_cast<pat::PackedCandidate const*>(tau.leadChargedHadrCand().get());
      
      _tauInfo.dz_PV = packedLeadTauCand->dz();
      _tauInfo.d0_PV = packedLeadTauCand->dxy();
    }

    _tauInfos.push_back( _tauInfo );
  } // End loop: for (int i = 0; i < nTaus; i++)

} // End void FillTauInfos


pat::TauCollection SelectTaus( const edm::Handle<pat::TauCollection>& taus,
			       const double _tau_pT_min, const double _tau_eta_max ) {
  // Presumably should follow something from here:
  // https://twiki.cern.ch/twiki/bin/view/CMS/TauIDRecommendation13TeV
  
  pat::TauCollection tausSelected;
  tausSelected.clear();

  if ( !taus.isValid() ) {
    std::cout << "No valid tau collection" << std::endl;
    return tausSelected;
  }

  for ( pat::TauCollection::const_iterator tau = taus->begin(), tausEnd = taus->end(); tau != tausEnd; ++tau) {
    
    if ( tau->pt()          < _tau_pT_min  ) continue;
    if ( fabs( tau->eta() ) > _tau_eta_max ) continue;

    tausSelected.push_back(*tau);
  }
  
  return tausSelected;
}
