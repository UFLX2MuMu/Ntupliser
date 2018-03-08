
#include "Ntupliser/DiMuons/interface/MetHelper.h"

void FillMetInfo( MetInfo& _metInfo,
		  const edm::Handle < pat::METCollection >& mets,
		  const edm::Event& iEvent, const TLorentzVector _dMet ) {

  _metInfo.init();
  if ( !mets.isValid() ) {
    std::cout << "No valid MET collection" << std::endl;
    return;
  }

  for (pat::METCollection::const_iterator met = mets->begin(),
         metsEnd = mets->end(); met !=metsEnd; ++met) {

    TLorentzVector met_vec;
    met_vec.SetPtEtaPhiM( met->pt(), 0., met->phi(), met->sumEt() );
    met_vec = met_vec + _dMet;
    
    _metInfo.px    = met_vec.Px();
    _metInfo.py    = met_vec.Py();
    _metInfo.pt    = met_vec.Pt();
    _metInfo.phi   = met_vec.Phi();
    _metInfo.sumEt = met_vec.E();

    break;  // Only use the first "MET" in vector of "METs"
    
  }
  
}
