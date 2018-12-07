
#include "Ntupliser/DiMuons/interface/JetPairHelper.h"

void FillJetPairInfos( JetPairInfos& _pairInfos, const JetInfos _jetInfos ) {

  _pairInfos.clear();
  if (_jetInfos.size() < 2)
    return;
  
  TLorentzVector jet1_vec;
  TLorentzVector jet2_vec;
  TLorentzVector pair_vec;
  
  std::vector< std::pair< float, std::pair<int, int> > > pairs_by_mass;
  pairs_by_mass.clear();
  
  // Sort pairs by invariant mass
  for (int i = 0; i < int(_jetInfos.size()); i++) {
    for (int j = i+1; j < int(_jetInfos.size()); j++) {

      // Only consider the first 8 jets
      if (i > 7 || j > 7) continue;
      
      jet1_vec.SetPtEtaPhiM(_jetInfos.at(i).pt, _jetInfos.at(i).eta, _jetInfos.at(i).phi, _jetInfos.at(i).mass);
      jet2_vec.SetPtEtaPhiM(_jetInfos.at(j).pt, _jetInfos.at(j).eta, _jetInfos.at(j).phi, _jetInfos.at(j).mass);
      pair_vec = jet1_vec + jet2_vec;
      pairs_by_mass.push_back(std::make_pair(pair_vec.M(), std::make_pair(i, j)));
    }
  }
  
  int nPairs = pairs_by_mass.size();
  std::stable_sort( pairs_by_mass.begin(), pairs_by_mass.end(), sort_jet_pairs_by_mass );
  
  for (int i = 0; i < int(pairs_by_mass.size()); i++) {

    // Only fill the first 15 pairs (5+4+3+2+1)
    if (i > 14) continue;

    JetPairInfo _pairInfo;
    
    int iJet1 = pairs_by_mass.at(i).second.first;
    int iJet2 = pairs_by_mass.at(i).second.second;
    
    _pairInfo.iJet1 = iJet1;
    _pairInfo.iJet2 = iJet2;

    jet1_vec.SetPtEtaPhiM(_jetInfos.at(iJet1).pt, _jetInfos.at(iJet1).eta, _jetInfos.at(iJet1).phi, _jetInfos.at(iJet1).mass);
    jet2_vec.SetPtEtaPhiM(_jetInfos.at(iJet2).pt, _jetInfos.at(iJet2).eta, _jetInfos.at(iJet2).phi, _jetInfos.at(iJet2).mass);
    pair_vec = jet1_vec + jet2_vec;

    _pairInfo.mass    = pair_vec.M();
    _pairInfo.pt      = pair_vec.Pt();
    _pairInfo.eta     = pair_vec.PseudoRapidity();
    _pairInfo.phi     = pair_vec.Phi();

    _pairInfo.dR   = jet1_vec.DeltaR(jet2_vec); 
    _pairInfo.dEta = jet1_vec.PseudoRapidity() - jet2_vec.PseudoRapidity(); 
    _pairInfo.dPhi = jet1_vec.DeltaPhi(jet2_vec); 

    _pairInfos.push_back( _pairInfo );
  } // End loop: for (int i = 0; i < pairs_by_mass.size(); i++)
  
  if ( int(_pairInfos.size()) != nPairs && nPairs < 15 )
    std::cout << "Bizzare error: jet _pairInfos.size() = " << _pairInfos.size()
	      << ", nPairs = " << nPairs << std::endl;
  
} // End void FillJetPairInfos( JetPairInfos& _pairInfos, const JetInfos _jetInfos )

bool sort_jet_pairs_by_mass( std::pair< float, std::pair<int, int> > i, 
			     std::pair< float, std::pair<int, int> > j ) {
  return (i.first > j.first);
}

