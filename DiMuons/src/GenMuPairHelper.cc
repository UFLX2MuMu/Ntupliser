
#include "Ntupliser/DiMuons/interface/GenMuPairHelper.h"

void FillGenMuPairInfos( GenMuPairInfos& _genPairInfos, const GenMuonInfos _muonInfos ) {
  
  _genPairInfos.clear();
  if (_muonInfos.size() < 2)
    return;
  
  int charge_FSR[2][2] = {{0,0},{0,0}};
  for (int i = 0; i < int(_muonInfos.size()); i++)
    charge_FSR[(_muonInfos.at(i).charge == 1)][(_muonInfos.at(i).postFSR == 1)] += 1;
  
  bool postFSR = false;
  bool good_pair = false;
  TLorentzVector mu1_vec;
  TLorentzVector mu2_vec;
  TLorentzVector pair_vec;
  
  std::vector< std::pair< double, std::pair<int, int> > > isOS;
  std::vector< std::pair< double, std::pair<int, int> > > isOS_pre;
  std::vector< std::pair< double, std::pair<int, int> > > isOS_post;
  isOS.clear();
  isOS_pre.clear();
  isOS_post.clear();

  // Sort pairs by OS/SS, then highest mu1 pT, then highest mu2 pT
  // Muons come sorted by pT, so only need to stable sort by OS/SS
  for (int i = 0; i < int(_muonInfos.size()); i++) {
    for (int j = i+1; j < int(_muonInfos.size()); j++) {

      if (_muonInfos.at(i).postFSR || _muonInfos.at(j).postFSR) {
	postFSR = true;
	if ( (_muonInfos.at(i).postFSR && _muonInfos.at(j).postFSR) ||
	     (charge_FSR[0][1] == 0 || charge_FSR[1][1] == 0) ) good_pair = true;
	else good_pair = false;
      } else {
	postFSR = false;
	if (_muonInfos.at(i).mother_ID == _muonInfos.at(j).mother_ID)
	  good_pair = true;
      }

      if (not good_pair) continue;

      mu1_vec.SetPtEtaPhiM(_muonInfos.at(i).pt, _muonInfos.at(i).eta, _muonInfos.at(i).phi, _muonInfos.at(i).mass);
      mu2_vec.SetPtEtaPhiM(_muonInfos.at(j).pt, _muonInfos.at(j).eta, _muonInfos.at(j).phi, _muonInfos.at(j).mass);

      if ( fabs(mu1_vec.Pt() - mu2_vec.Pt()) > 0.001  ) {
        pair_vec = mu1_vec + mu2_vec;
      } else {
        pair_vec.SetPtEtaPhiM( 0.0, 0.0, 0.0, sqrt( pow(mu1_vec.Pt() + mu2_vec.Pt(), 2) +
						    pow(mu1_vec.Pz() - mu2_vec.Pz(), 2) +
						    pow(mu1_vec.M()  + mu2_vec.M(),  2) ) );
      }


      bool isOS = (_muonInfos.at(i).charge + _muonInfos.at(j).charge == 0);
      if (postFSR)
	isOS_post.push_back(std::make_pair(isOS, std::make_pair(i, j)));
      else
	isOS_pre.push_back(std::make_pair(isOS, std::make_pair(i, j)));
    }
  }
  
  int nPairs_pre = isOS_pre.size();
  int nPairs_post = isOS_post.size();

  std::stable_sort( isOS_pre.begin(), isOS_pre.end(), gen_pair_is_OS );
  std::stable_sort( isOS_post.begin(), isOS_post.end(), gen_pair_is_OS );

  isOS.insert( isOS.end(), isOS_pre.begin(), isOS_pre.end() );
  isOS.insert( isOS.end(), isOS_post.begin(), isOS_post.end() );

  for (int i = 0; i < int(isOS.size()); i++) {

    GenMuPairInfo _genPairInfo;
    
    int iMu1 = isOS.at(i).second.first;
    int iMu2 = isOS.at(i).second.second;

    _genPairInfo.iMu1      = iMu1;
    _genPairInfo.iMu2      = iMu2;
    _genPairInfo.charge    = _muonInfos.at(iMu1).charge + _muonInfos.at(iMu2).charge;
    _genPairInfo.mother_ID = _muonInfos.at(iMu1).mother_ID;
    if (_muonInfos.at(iMu1).postFSR || _muonInfos.at(iMu2).postFSR)
      _genPairInfo.postFSR = 1;
    else
      _genPairInfo.postFSR = 0;

    mu1_vec.SetPtEtaPhiM(_muonInfos.at(iMu1).pt, _muonInfos.at(iMu1).eta, _muonInfos.at(iMu1).phi, _muonInfos.at(iMu1).mass);
    mu2_vec.SetPtEtaPhiM(_muonInfos.at(iMu2).pt, _muonInfos.at(iMu2).eta, _muonInfos.at(iMu2).phi, _muonInfos.at(iMu2).mass);

    if ( fabs(mu1_vec.Pt() - mu2_vec.Pt()) > 0.001  ) {
      pair_vec = mu1_vec + mu2_vec;
    } else {
      pair_vec.SetPtEtaPhiM( 0.0, 0.0, 0.0, sqrt( pow(mu1_vec.Pt() + mu2_vec.Pt(), 2) +
						  pow(mu1_vec.Pz() - mu2_vec.Pz(), 2) +
						  pow(mu1_vec.M()  + mu2_vec.M(),  2) ) );
    }

    _genPairInfo.mass  = pair_vec.M();
    _genPairInfo.pt    = pair_vec.Pt();
    _genPairInfo.eta   = pair_vec.PseudoRapidity();
    _genPairInfo.rapid = pair_vec.Rapidity();
    _genPairInfo.phi   = pair_vec.Phi();

    _genPairInfo.dR   = mu1_vec.DeltaR(mu2_vec);
    _genPairInfo.dEta = mu1_vec.PseudoRapidity() - mu2_vec.PseudoRapidity();
    _genPairInfo.dPhi = mu1_vec.DeltaPhi(mu2_vec);

    _genPairInfos.push_back( _genPairInfo );
  } // End loop: for (int i = 0; i < isOS.size(); i++)
  
  if ( int(_genPairInfos.size()) != nPairs_pre + nPairs_post )
    std::cout << "Bizzare error: muon _genPairInfos.size() = " << _genPairInfos.size()
	      << ", nPairs_pre = " << nPairs_pre << ", nPairs_post = " << nPairs_post << std::endl;
  
} // End void FillGenMuPairInfos( GenMuPairInfos& _genPairInfos, const GenMuonInfos _muonInfos )

bool gen_pair_is_OS( std::pair< bool, std::pair<int, int> > i,
		     std::pair< bool, std::pair<int, int> > j) {
  return (i.first || !j.first);
}
