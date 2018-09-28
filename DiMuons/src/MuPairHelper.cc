
#include "Ntupliser/DiMuons/interface/MuPairHelper.h"

void FillMuPairInfos( MuPairInfos& _pairInfos, const MuonInfos _muonInfos ) {

  _pairInfos.clear();
  if (_muonInfos.size() < 2)
    return;

  double const MASS_MUON  = 0.105658367; // GeV/c^2
  double const PI         = 3.14159265359;

  // 4-vectors: nominal, mu1_up, mu1_down, mu2_up, mu2_down
  muVecSys mu1_vec;
  muVecSys mu2_vec;
  pairVecSys pair_vec;
  double massErr;

  std::vector< std::pair< bool, std::pair<int, int> > > isOS;
  isOS.clear();

  // Sort pairs by OS/SS, then highest mu1 pT, then highest mu2 pT
  // Muons come sorted by pT, so only need to stable sort by OS/SS 
  for (int i = 0; i < int(_muonInfos.size()); i++) {
    for (int j = i+1; j < int(_muonInfos.size()); j++) {
      bool osPair = (_muonInfos.at(i).charge + _muonInfos.at(j).charge == 0);
      isOS.push_back(std::make_pair(osPair, std::make_pair(i, j)));
    }
  }

  int nPairs = isOS.size();
  std::stable_sort( isOS.begin(), isOS.end(), pair_is_OS );
  
  for (int i = 0; i < int(isOS.size()); i++) {
    
    MuPairInfo _pairInfo;
    _pairInfo.init();
    
    int iMu1 = isOS.at(i).second.first;
    int iMu2 = isOS.at(i).second.second;
    
    _pairInfo.iMu1 = iMu1;
    _pairInfo.iMu2 = iMu2;
    _pairInfo.charge = _muonInfos.at(iMu1).charge + _muonInfos.at(iMu2).charge; 

    FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		    _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		    _muonInfos.at(iMu1).pt, _muonInfos.at(iMu2).pt,
		    _muonInfos.at(iMu1).ptErr, _muonInfos.at(iMu2).ptErr );

    _pairInfo.mass    = pair_vec.nom.M();
    _pairInfo.massErr = massErr;
    _pairInfo.pt      = pair_vec.nom.Pt();
    _pairInfo.eta     = pair_vec.nom.PseudoRapidity();
    _pairInfo.rapid   = pair_vec.nom.Rapidity();
    _pairInfo.phi     = pair_vec.nom.Phi();

    double _dR   = mu1_vec.nom.DeltaR(mu2_vec.nom);
    double _dEta = mu1_vec.nom.PseudoRapidity() - mu2_vec.nom.PseudoRapidity();
    double _dPhi = mu1_vec.nom.DeltaPhi(mu2_vec.nom);

    double _dThetaStarEta = acos( tanh(_dEta/2) );
    double _dPhiStar      = tan( (PI - fabs(_dPhi)) / 2) * sin(_dThetaStarEta);

    _pairInfo.dR   = _dR;
    _pairInfo.dEta = _dEta;
    _pairInfo.dPhi = _dPhi;
    _pairInfo.dPhiStar = _dPhiStar;

    if ( _muonInfos.at(iMu1).pt_PF > 0 && _muonInfos.at(iMu2).pt_PF > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_PF, _muonInfos.at(iMu2).pt_PF,
		      _muonInfos.at(iMu1).ptErr, _muonInfos.at(iMu2).ptErr );
      
      _pairInfo.mass_PF    = pair_vec.nom.M();
      _pairInfo.massErr_PF = massErr;
      _pairInfo.pt_PF      = pair_vec.nom.Pt();
    }

    if ( _muonInfos.at(iMu1).pt_trk > 0 && _muonInfos.at(iMu2).pt_trk > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_trk, _muonInfos.at(iMu2).pt_trk,
		      _muonInfos.at(iMu1).ptErr_trk, _muonInfos.at(iMu2).ptErr_trk );
      
      _pairInfo.mass_trk    = pair_vec.nom.M();
      _pairInfo.massErr_trk = massErr;
      _pairInfo.pt_trk      = pair_vec.nom.Pt();
    }
    
    if ( _muonInfos.at(iMu1).pt_KaMu > 0 && _muonInfos.at(iMu2).pt_KaMu > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_KaMu, _muonInfos.at(iMu2).pt_KaMu,
		      _muonInfos.at(iMu1).ptErr_KaMu, _muonInfos.at(iMu2).ptErr_KaMu );
      
      _pairInfo.mass_KaMu    = pair_vec.nom.M();
      _pairInfo.massErr_KaMu = massErr;
      _pairInfo.pt_KaMu      = pair_vec.nom.Pt();
    }
    
    if ( _muonInfos.at(iMu1).pt_KaMu_clos_up > 0 && _muonInfos.at(iMu2).pt_KaMu_clos_up > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_KaMu_clos_up, _muonInfos.at(iMu2).pt_KaMu_clos_up,
		      _muonInfos.at(iMu1).ptErr_KaMu, _muonInfos.at(iMu2).ptErr_KaMu );
      
      _pairInfo.mass_KaMu_clos_up = pair_vec.nom.M();
      _pairInfo.pt_KaMu_clos_up   = pair_vec.nom.Pt();
    }

    if ( _muonInfos.at(iMu1).pt_KaMu_clos_down > 0 && _muonInfos.at(iMu2).pt_KaMu_clos_down > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_KaMu_clos_down, _muonInfos.at(iMu2).pt_KaMu_clos_down,
		      _muonInfos.at(iMu1).ptErr_KaMu, _muonInfos.at(iMu2).ptErr_KaMu );
      
      _pairInfo.mass_KaMu_clos_down = pair_vec.nom.M();
      _pairInfo.pt_KaMu_clos_down   = pair_vec.nom.Pt();
    }

    if ( _muonInfos.at(iMu1).pt_KaMu_sys_up > 0 && _muonInfos.at(iMu2).pt_KaMu_sys_up > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_KaMu_sys_up, _muonInfos.at(iMu2).pt_KaMu_sys_up,
		      _muonInfos.at(iMu1).ptErr_KaMu, _muonInfos.at(iMu2).ptErr_KaMu );
      
      _pairInfo.mass_KaMu_sys_up = pair_vec.nom.M();
      _pairInfo.pt_KaMu_sys_up   = pair_vec.nom.Pt();
    }

    if ( _muonInfos.at(iMu1).pt_KaMu_sys_down > 0 && _muonInfos.at(iMu2).pt_KaMu_sys_down > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_KaMu_sys_down, _muonInfos.at(iMu2).pt_KaMu_sys_down,
		      _muonInfos.at(iMu1).ptErr_KaMu, _muonInfos.at(iMu2).ptErr_KaMu );
      
      _pairInfo.mass_KaMu_sys_down = pair_vec.nom.M();
      _pairInfo.pt_KaMu_sys_down   = pair_vec.nom.Pt();
    }


    // Kinemtic Fit
    if ( _muonInfos.at(iMu1).pt_kinfit > 0 && _muonInfos.at(iMu2).pt_kinfit > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_kinfit, _muonInfos.at(iMu2).pt_kinfit,
		      _muonInfos.at(iMu1).ptErr_Roch, _muonInfos.at(iMu2).ptErr_Roch );
      
      _pairInfo.mass_kinfit    = pair_vec.nom.M();
      _pairInfo.massErr_kinfit = massErr;
      _pairInfo.pt_kinfit      = pair_vec.nom.Pt();
    }
 

    if ( _muonInfos.at(iMu1).pt_Roch > 0 && _muonInfos.at(iMu2).pt_Roch > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_Roch, _muonInfos.at(iMu2).pt_Roch,
		      _muonInfos.at(iMu1).ptErr_Roch, _muonInfos.at(iMu2).ptErr_Roch );
      
      _pairInfo.mass_Roch    = pair_vec.nom.M();
      _pairInfo.massErr_Roch = massErr;
      _pairInfo.pt_Roch      = pair_vec.nom.Pt();
    }
    
    if ( _muonInfos.at(iMu1).pt_Roch_sys_up > 0 && _muonInfos.at(iMu2).pt_Roch_sys_up > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_Roch_sys_up, _muonInfos.at(iMu2).pt_Roch_sys_up,
		      _muonInfos.at(iMu1).ptErr_Roch, _muonInfos.at(iMu2).ptErr_Roch );
      
      _pairInfo.mass_Roch_sys_up = pair_vec.nom.M();
      _pairInfo.pt_Roch_sys_up   = pair_vec.nom.Pt();
    }
    
    if ( _muonInfos.at(iMu1).pt_Roch_sys_down > 0 && _muonInfos.at(iMu2).pt_Roch_sys_down > 0 ) {
      FillMuPairMasses( mu1_vec, mu2_vec, pair_vec, massErr, MASS_MUON, 
		      _muonInfos.at(iMu1), _muonInfos.at(iMu2),
		      _muonInfos.at(iMu1).pt_Roch_sys_down, _muonInfos.at(iMu2).pt_Roch_sys_down,
		      _muonInfos.at(iMu1).ptErr_Roch, _muonInfos.at(iMu2).ptErr_Roch );
      
      _pairInfo.mass_Roch_sys_down = pair_vec.nom.M();
      _pairInfo.pt_Roch_sys_down   = pair_vec.nom.Pt();
    }

    _pairInfos.push_back( _pairInfo );
  } // End loop: for (int i = 0; i < isOS.size(); i++)
  
  if ( int(_pairInfos.size()) != nPairs )
    std::cout << "Bizzare error: muon _pairInfos.size() = " << _pairInfos.size()
	      << ", nPairs = " << nPairs << std::endl;
  
} // End void FillMuPairInfos( MuPairInfos& _pairInfos, const MuonInfos _muonInfos )

bool pair_is_OS( std::pair< bool, std::pair<int, int> > i, 
		 std::pair< bool, std::pair<int, int> > j) {
  return (i.first || !j.first);
}

void FillMuPairMasses( muVecSys& mu1_vec, muVecSys& mu2_vec, pairVecSys& pair_vec, 
		     double& massErr, const double MASS_MUON,
		     const MuonInfo _mu1, const MuonInfo _mu2, 
		     const double _mu1_pt, const double _mu2_pt,
		     const double _mu1_ptErr, const double _mu2_ptErr ) {

  mu1_vec.nom.SetPtEtaPhiM(_mu1_pt, _mu1.eta, _mu1.phi, MASS_MUON);
  mu2_vec.nom.SetPtEtaPhiM(_mu2_pt, _mu2.eta, _mu2.phi, MASS_MUON);
  
  mu1_vec.up.SetPtEtaPhiM(_mu1_pt + _mu1_ptErr, _mu1.eta, _mu1.phi, MASS_MUON);
  mu2_vec.up.SetPtEtaPhiM(_mu2_pt + _mu2_ptErr, _mu2.eta, _mu2.phi, MASS_MUON);
  
  mu1_vec.down.SetPtEtaPhiM(_mu1_pt - _mu1_ptErr, _mu1.eta, _mu1.phi, MASS_MUON);
  mu2_vec.down.SetPtEtaPhiM(_mu2_pt - _mu2_ptErr, _mu2.eta, _mu2.phi, MASS_MUON);
  
  pair_vec.nom   = mu1_vec.nom  + mu2_vec.nom;
  pair_vec.up1   = mu1_vec.up   + mu2_vec.nom;
  pair_vec.down1 = mu1_vec.down + mu2_vec.nom;
  pair_vec.up2   = mu1_vec.nom  + mu2_vec.up;
  pair_vec.down2 = mu1_vec.nom  + mu2_vec.down;
  
  massErr = sqrt( pow(pair_vec.nom.M() - pair_vec.up1.M(),   2) +
		  pow(pair_vec.nom.M() - pair_vec.down1.M(), 2) + 
		  pow(pair_vec.nom.M() - pair_vec.up2.M(),   2) + 
		  pow(pair_vec.nom.M() - pair_vec.down2.M(), 2) ) / 2.;
  
} // End void FillMuPairMasses()
