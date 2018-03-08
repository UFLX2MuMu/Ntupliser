
#include "Ntupliser/DiMuons/interface/GenMuonHelper.h"

void FillGenMuonInfos( GenMuonInfos& _genMuonInfos, GenParentInfos& _genParentInfos,
		       const edm::Handle < reco::GenParticleCollection >& genPartons,
		       const bool isMC ) {
  
  _genMuonInfos.clear();
  
  for (unsigned int i = 0; i < genPartons->size(); i++) {
    
    const reco::Candidate& muon = genPartons->at(i);
    if ( abs(muon.pdgId()) != 13 ) continue;
    
    bool preFSR = false;
    bool postFSR = false;

    int mID  = -99;
    int mSt  = -99;
    int gmID = -99;
    if (muon.numberOfMothers() > 0) {
      mID = muon.mother(0)->pdgId();
      mSt = muon.mother(0)->status(); 
      if (muon.mother(0)->numberOfMothers() > 0) {
	gmID = muon.mother(0)->mother(0)->pdgId();
      }
    }

    if ( (abs(mID) > 21 && abs(mID) < 26) ||                      // gamma/Z/W/H --> muon
	 (abs(mID) == 15 && abs(gmID) > 21 && abs(gmID) < 26) ||  // gamma/Z/W/H --> tau --> muon
	 (abs(mID) > 0 && abs(mID) < 3 && mSt == 21) ) {          // ud --> gamma --> mu-mu
      preFSR = true;
    } else if ( abs(mID) == 13 && muon.status() == 1 ) {  // muon --> muon
      postFSR = true;
    }

    if (not preFSR && not postFSR) continue;
    
    GenMuonInfo _genMuonInfo;
    _genMuonInfo.init();
    
    _genMuonInfo.status     = muon.status();
    _genMuonInfo.nMothers   = muon.numberOfMothers();
    _genMuonInfo.postFSR    = postFSR;
    
    _genMuonInfo.pt     = muon.pt();
    _genMuonInfo.eta    = muon.eta();
    _genMuonInfo.phi    = muon.phi();
    _genMuonInfo.mass   = muon.mass();
    _genMuonInfo.charge = muon.charge();

    if (muon.numberOfMothers() > 0) {
      _genMuonInfo.mother_ID     = muon.mother(0)->pdgId();
      _genMuonInfo.mother_status = muon.mother(0)->status();
    }

    _genMuonInfos.push_back( _genMuonInfo );
  } // End loop: for (unsigned int i = 0; i < genPartons->size(); i++) 


  //////////////////////////////
  ///  Infer the FSR photon  ///
  //////////////////////////////
  TLorentzVector preFSR_vec;
  TLorentzVector postFSR_vec;
  TLorentzVector FSR_vec;
  for (int i = 0; i < int(_genMuonInfos.size()); i++) {
    for (int j = 0; j < int(_genMuonInfos.size()); j++) {

      if (_genMuonInfos.at(i).postFSR != 0) continue;
      if (_genMuonInfos.at(j).postFSR != 1) continue;
      if (_genMuonInfos.at(i).charge != _genMuonInfos.at(j).charge) continue;

      if ( fabs(_genMuonInfos.at(i).pt  - _genMuonInfos.at(j).pt ) > 0.001 ||
	   fabs(_genMuonInfos.at(i).phi - _genMuonInfos.at(j).phi) > 0.001 ||
	   fabs(_genMuonInfos.at(i).eta - _genMuonInfos.at(j).eta) > 0.001 ) {
	preFSR_vec .SetPtEtaPhiM(_genMuonInfos.at(i).pt, _genMuonInfos.at(i).eta, _genMuonInfos.at(i).phi, _genMuonInfos.at(i).mass);
	postFSR_vec.SetPtEtaPhiM(_genMuonInfos.at(j).pt, _genMuonInfos.at(j).eta, _genMuonInfos.at(j).phi, _genMuonInfos.at(j).mass);
	FSR_vec = preFSR_vec - postFSR_vec;
	
	_genMuonInfos.at(j).FSR_pt   = FSR_vec.Pt();
	_genMuonInfos.at(j).FSR_eta  = FSR_vec.Eta();
	_genMuonInfos.at(j).FSR_phi  = FSR_vec.Phi();
	_genMuonInfos.at(j).FSR_mass = FSR_vec.M();
      } else { 
	_genMuonInfos.at(j).FSR_pt   = 0;
	_genMuonInfos.at(j).FSR_eta  = preFSR_vec.Eta();
	_genMuonInfos.at(j).FSR_phi  = preFSR_vec.Phi();
	_genMuonInfos.at(j).FSR_mass = 0;
      }

    }
  }
  
  /////////////////////////////////////////////////////////////////////////////////
  ///  Create a parent gamma for muons from the ud --> gamma --> mu-mu process  ///
  /////////////////////////////////////////////////////////////////////////////////
  TLorentzVector mu1_vec;
  TLorentzVector mu2_vec;
  TLorentzVector gamma_vec;
  for (int i = 0; i < int(_genMuonInfos.size()); i++) {
    for (int j = i+1; j < int(_genMuonInfos.size()); j++) {

      if ( abs(_genMuonInfos.at(i).mother_ID) > 2 ) continue;
      if ( abs(_genMuonInfos.at(j).mother_ID) > 2 ) continue;
      if ( _genMuonInfos.at(i).charge + _genMuonInfos.at(j).charge != 0 ) continue;

      mu1_vec.SetPtEtaPhiM(_genMuonInfos.at(i).pt, _genMuonInfos.at(i).eta, _genMuonInfos.at(i).phi, _genMuonInfos.at(i).mass);
      mu2_vec.SetPtEtaPhiM(_genMuonInfos.at(j).pt, _genMuonInfos.at(j).eta, _genMuonInfos.at(j).phi, _genMuonInfos.at(j).mass);
      if ( fabs(mu1_vec.Pt() - mu2_vec.Pt()) > 0.001  ) {
	gamma_vec = mu1_vec + mu2_vec;
      } else {
	gamma_vec.SetPtEtaPhiM( 0.0, 0.0, 0.0, sqrt( pow(mu1_vec.Pt() + mu2_vec.Pt(), 2) + 
						     pow(mu1_vec.Pz() - mu2_vec.Pz(), 2) +
						     pow(mu1_vec.M()  + mu2_vec.M(),  2) ) );
      }

      GenParentInfo _genParentInfo;
      _genParentInfo.init();
      
      _genParentInfo.ID         = 22;
      _genParentInfo.status     = 21;
      _genParentInfo.nDaughters = 2;
      
      _genParentInfo.pt     = gamma_vec.Pt();
      _genParentInfo.eta    = gamma_vec.Eta();
      _genParentInfo.phi    = gamma_vec.Phi();
      _genParentInfo.mass   = gamma_vec.M();
      _genParentInfo.charge = 0;

      _genParentInfo.daughter_1_ID     = -13*_genMuonInfos.at(i).charge;
      _genParentInfo.daughter_1_status = _genMuonInfos.at(i).status;
      _genParentInfo.daughter_1_idx    = i;

      _genParentInfo.daughter_2_ID     = -13*_genMuonInfos.at(j).charge;
      _genParentInfo.daughter_2_status = _genMuonInfos.at(j).status;
      _genParentInfo.daughter_2_idx    = j;


      _genParentInfos.push_back(_genParentInfo);
    } // End loop: for (int j = 0; j < int(_genMuonInfos.size()); j++)
  } // End loop: for (int i = 0; i < int(_genMuonInfos.size()); i++)


  ////////////////////////////////
  ///  Match muons to parents  /// 
  ////////////////////////////////
  for (int i = 0; i < int(_genMuonInfos.size()); i++) {
    for (int j = 0; j < int(_genParentInfos.size()); j++) {
      
      if ( _genMuonInfos.at(i).mother_ID     == _genParentInfos.at(j).ID &&
	   _genMuonInfos.at(i).mother_status == _genParentInfos.at(j).status ) {
	
	_genMuonInfos.at(i).mother_idx = j;
	
	if ( -13*_genMuonInfos.at(i).charge == _genParentInfos.at(j).daughter_1_ID &&
	     _genMuonInfos.at(i).status     == _genParentInfos.at(j).daughter_1_status ) {
	  _genParentInfos.at(j).daughter_1_idx = i;
	} else if ( -13*_genMuonInfos.at(i).charge == _genParentInfos.at(j).daughter_2_ID &&
		    _genMuonInfos.at(i).status     == _genParentInfos.at(j).daughter_2_status ) {
	  _genParentInfos.at(j).daughter_2_idx = i;
	}
      }

    } // End loop: for (int j = 0; j < int(_genParentInfos.size()); j++)
  } // End loop: for (int i = 0; i < int(_genMuonInfos.size()); i++)


}

