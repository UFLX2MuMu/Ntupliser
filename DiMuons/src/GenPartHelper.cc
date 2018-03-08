
#include "Ntupliser/DiMuons/interface/GenPartHelper.h"

void FillGenPartInfo( GenPartInfo& _genPartInfo,
                      const reco::Candidate& genPart ) {

  _genPartInfo.init();

  _genPartInfo.charge = genPart.charge();
  _genPartInfo.mass   = genPart.mass();
  _genPartInfo.pt     = genPart.pt();
  // _genPartInfo.ptErr would need to be filled with pat::Track
  _genPartInfo.eta    = genPart.eta();
  _genPartInfo.y      = genPart.rapidity();
  _genPartInfo.phi    = genPart.phi();

}



void FillBosonAndMuDaughters( const reco::Candidate& boson,
			      GenPartInfo& _genGpreFSR,  GenPartInfo& _genM1GpreFSR,  GenPartInfo& _genM2GpreFSR,
			      GenPartInfo& _genGpostFSR, GenPartInfo& _genM1GpostFSR, GenPartInfo& _genM2GpostFSR,
			      GenPartInfo& _genZpreFSR,  GenPartInfo& _genM1ZpreFSR,  GenPartInfo& _genM2ZpreFSR,
			      GenPartInfo& _genZpostFSR, GenPartInfo& _genM1ZpostFSR, GenPartInfo& _genM2ZpostFSR,
			      GenPartInfo& _genHpreFSR,  GenPartInfo& _genM1HpreFSR,  GenPartInfo& _genM2HpreFSR,
			      GenPartInfo& _genHpostFSR, GenPartInfo& _genM1HpostFSR, GenPartInfo& _genM2HpostFSR,
			      GenPartInfo& _genWpreFSR,  GenPartInfo& _genMWpreFSR,
			      GenPartInfo& _genWpostFSR, GenPartInfo& _genMWpostFSR ) {
  
  // photon, Z, W, H
  if (boson.status() == 62) {
    if (abs(boson.pdgId()) < 22 || abs(boson.pdgId()) > 25)
      return;
  }
  // Technically 21 is an incoming particle from the feynman diagram q, anti-q -> lept, lept 
  // with no intermediate gen particle. I think this is q, anti-q -> gamma* -> lept, lept.
  // Whenever there is no Z in the dyJetsToLL sample there is this q, anti-q -> lept, lept 
  // where the quark and the antiquark have the same two leptons as daughters.
  // We will have to reconstruct the values for the off shell gamma
  else if (boson.status() != 21)
    return;

  GenPartInfo bosonInfo;
  GenPartInfo mu1preFSR;
  GenPartInfo mu1postFSR;
  GenPartInfo mu2preFSR;
  GenPartInfo mu2postFSR;
  
  bosonInfo.init();
  mu1preFSR.init();
  mu1postFSR.init();
  mu2preFSR.init();
  mu2postFSR.init();

  FillGenPartInfo( bosonInfo, boson );

  TLorentzVector l1, l2, mother;
  bool moreThanOneLeptPair = false;

  // Get the daughter muons for the boson
  for (unsigned int i = 0; i < boson.numberOfDaughters(); i++) {
    const reco::Candidate* daughter = boson.daughter(i);
    
    // Get information about the lepton daughters to reconstruct the virtual photon later
    if (daughter->pdgId() == 11 || daughter->pdgId() == 13 || daughter->pdgId() == 15) {
      for (unsigned int j = 0; j < boson.numberOfDaughters(); j++) { // Loop from i? - AWB 08.11.16
	// We already know you can't make a lepton pair with yourself, so skip this one if it's the case
	if(i == j) continue;
	const reco::Candidate* daughter2 = boson.daughter(j);
	// Found a pair of opposite signed lepton daughters
	if(daughter->pdgId() == -1*daughter2->pdgId()) {
	  // We already found a pair, l1 AND l2 were initialized already
	  if (l1.M() != 0 && l2.M() != 0) moreThanOneLeptPair = true;
	  l1.SetPtEtaPhiM(daughter->pt(),  daughter->eta(),  daughter->phi(),  daughter->mass());
	  l2.SetPtEtaPhiM(daughter2->pt(), daughter2->eta(), daughter2->phi(), daughter2->mass());
	}
      }
    }

    // Status 23 muon, intermediate particle from a decay
    if (daughter->pdgId() == 13 && daughter->status() == 23) {
      // We have an intermediate status 23 muon, save the intermediate values as preFSR
      FillGenPartInfo( mu1preFSR, *daughter );
      
      // If it did not radiate then the post and pre are the same
      mu1postFSR = mu1preFSR;

      // If it did radiate, get the postFSR final state, status 1 version 
      // of this muon and overwrite the postFSR quantities
      for (unsigned int i = 0; i < daughter->numberOfDaughters(); i++) {
	const reco::Candidate* postFSRcand = daughter->daughter(i);
	if (postFSRcand->pdgId() == 13 && daughter->status() == 1)
	  FillGenPartInfo( mu1postFSR, *postFSRcand );
      }
    }

    // Status 23 antimuon, intermediate particle from a decay
    else if (daughter->pdgId() == -13 && daughter->status() == 23) {
      // We have an intermediate status 23 muon, save the intermediate values as preFSR                                                        
      FillGenPartInfo( mu2preFSR, *daughter );
      
      mu2postFSR = mu2preFSR;
      
      // If it did radiate, get the postFSR final state, status 1 version 
      // of this muon and overwrite the postFSR quantities
      for (unsigned int i = 0; i<daughter->numberOfDaughters(); i++) {
	const reco::Candidate* postFSRcand = daughter->daughter(i);
	if (postFSRcand->pdgId() == -13 && daughter->status() == 1)
	  FillGenPartInfo( mu2postFSR, *postFSRcand );
      }
    }

    // Final state muon
    else if (daughter->pdgId() == 13 && daughter->status() == 1) {
      // No intermediate status 23 muon that radiated only final state status 1, so pre and post are the same
      FillGenPartInfo( mu1preFSR, *daughter );

      // No radiation, post and pre are the same                                                                                               
      mu1postFSR = mu1preFSR;
    }
    // Final state antimuon
    else if (daughter->pdgId() == -13 && daughter->status() == 1) {
      // No intermediate status 23 muon that radiated only final state status 1, so pre and post are the same                                  
      FillGenPartInfo( mu2preFSR, *daughter );

      // No radiation, post and pre are the same
      mu2postFSR = mu2preFSR;
    }

  } // End loop: for (unsigned int i = 0; i < boson.numberOfDaughters(); i++)

  // No muons found, Z/gamma* decayed to other leptons
  if ( mu1preFSR.pt < 0 && mu1postFSR.pt < 0 && 
       mu2preFSR.pt < 0 && mu2postFSR.pt < 0 && 
       l1.M() !=0 && l2.M() != 0 ) {
    // Use the mass to let us know what the Z/gamma* decayed to
    mu1preFSR.pt     = -l1.M();
    mu1preFSR.eta    = -l1.M();
    mu1preFSR.phi    = -l1.M();;
    mu1preFSR.charge = -l1.M();
    
    mu2preFSR.pt     = -l2.M();
    mu2preFSR.eta    = -l2.M();
    mu2preFSR.phi    = -l2.M();;
    mu2preFSR.charge = -l2.M();
    
    mu1postFSR = mu1preFSR;
    mu2postFSR = mu2preFSR;
  }

  // Fill the appropriate boson and daughters
  if (boson.status() == 21) {
    // In DY this is an incoming quark, anti-quark annihilation
    // 21 could be any incoming particle in other samples though
    
    // If the virtual photon went to two leptons then reconstruct it
    if (l1.M() != 0 && l2.M() != 0) {
      mother = l1 + l2;

      bosonInfo.mass   = mother.M();
      bosonInfo.pt     = mother.Pt();
      bosonInfo.eta    = -111;
      bosonInfo.y      = mother.Rapidity();
      bosonInfo.phi    = mother.Phi();
      bosonInfo.charge = 0;

      // Not sure what to do if the virtual photon decayed to a bunch of leptons
      if (moreThanOneLeptPair) {
	bosonInfo.mass   = -333;
	bosonInfo.pt     = -333;
	bosonInfo.eta    = -333;
	bosonInfo.y      = -333;
	bosonInfo.phi    = -333;
	bosonInfo.charge = -333;
      }
    }
    else {
      bosonInfo.init();
    }

    _genGpreFSR = bosonInfo;
    _genM1GpreFSR = mu1preFSR;
    _genM2GpreFSR = mu2preFSR;
    
    _genGpostFSR = bosonInfo;
    _genM1GpostFSR = mu1postFSR;
    _genM2GpostFSR = mu2postFSR;

  } // End conditional: if (boson.status() == 21)

  // Z
  if(abs(boson.pdgId()) == 23) {
    _genZpreFSR = bosonInfo;
    _genM1ZpreFSR = mu1preFSR;
    _genM2ZpreFSR = mu2preFSR;

    _genZpostFSR = bosonInfo;
    _genM1ZpostFSR = mu1postFSR;
    _genM2ZpostFSR = mu2postFSR;
  }
  // W
  if(abs(boson.pdgId()) == 24) {
    _genWpreFSR = bosonInfo;
    if (bosonInfo.charge == mu1preFSR.charge) _genMWpreFSR = mu1preFSR;
    if (bosonInfo.charge == mu2preFSR.charge) _genMWpreFSR = mu2preFSR;
    
    _genWpostFSR = bosonInfo;
    if (bosonInfo.charge == mu1postFSR.charge) _genMWpreFSR = mu1postFSR;
    if (bosonInfo.charge == mu2postFSR.charge) _genMWpreFSR = mu2postFSR;
  }

  // H
  if(abs(boson.pdgId()) == 25) {
    _genHpreFSR = bosonInfo;
    _genM1HpreFSR = mu1preFSR;
    _genM2HpreFSR = mu2preFSR;
    
    _genHpostFSR = bosonInfo;
    _genM1HpostFSR = mu1postFSR;
    _genM2HpostFSR = mu2postFSR;
  }

} // End void FillBosonAndMuDaughters
