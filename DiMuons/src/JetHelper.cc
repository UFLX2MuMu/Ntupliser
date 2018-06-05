
#include "Ntupliser/DiMuons/interface/JetHelper.h"

void FillSlimJetInfos( SlimJetInfos& _slimJetInfos, const JetInfos _jetInfos ) {
  
  _slimJetInfos.clear();
  
  for (int i = 0; i < int(_jetInfos.size()); i++) {
    SlimJetInfo s;
    JetInfo j = _jetInfos.at(i);
    s.pt        = j.pt;
    s.eta       = j.eta;
    s.phi       = j.phi;
    s.mass      = j.mass;
    s.partonID  = j.partonID;
    s.jecFactor = j.jecFactor;
    s.jecUnc    = j.jecUnc;
    s.CSV       = j.CSV;
    s.puID      = j.puID;
    _slimJetInfos.push_back(s);
  }
  
}

void FillJetInfos( JetInfos& _jetInfos, int& _nJetsFwd,
		   int& _nBLoose, int& _nBMed, int& _nBTight,
		   const pat::JetCollection jetsSelected,
		   const std::string _btagName) {

  _jetInfos.clear();
  _nJetsFwd  = 0;
  _nBLoose   = 0;
  _nBMed     = 0;
  _nBTight   = 0;
  int nJets     = jetsSelected.size();
  int nJetsCent = 0;

  for (int i = 0; i < nJets; i++) {
    
    pat::Jet jet = jetsSelected.at(i);
    JetInfo _jetInfo;
    _jetInfo.init();

    _jetInfo.px       = jet.px();
    _jetInfo.py       = jet.py();
    _jetInfo.pz       = jet.pz();
    _jetInfo.pt       = jet.pt();
    _jetInfo.eta      = jet.eta();
    _jetInfo.phi      = jet.phi();
    _jetInfo.mass     = jet.mass();
    _jetInfo.charge   = jet.charge();
    _jetInfo.partonID = jet.partonFlavour();
    
    _jetInfo.chf  = jet.chargedHadronEnergyFraction();
    _jetInfo.nhf  = jet.neutralHadronEnergyFraction();
    _jetInfo.cef  = jet.chargedEmEnergyFraction();
    _jetInfo.nef  = jet.neutralEmEnergyFraction();
    _jetInfo.muf  = jet.muonEnergyFraction();
    _jetInfo.hfhf = jet.HFHadronEnergyFraction();
    _jetInfo.hfef = jet.HFEMEnergyFraction();
    
    _jetInfo.cm   = jet.chargedMultiplicity();
    _jetInfo.chm  = jet.chargedHadronMultiplicity();
    _jetInfo.nhm  = jet.neutralHadronMultiplicity();
    _jetInfo.cem  = jet.electronMultiplicity();
    _jetInfo.nem  = jet.photonMultiplicity();
    _jetInfo.mum  = jet.muonMultiplicity();
    _jetInfo.hfhm = jet.HFHadronMultiplicity();
    _jetInfo.hfem = jet.HFEMMultiplicity();
    
    _jetInfo.jecUnc    = -1.0;
    _jetInfo.jecFactor = jet.jecFactor("Uncorrected");
   
    //with deepCSV need to sum two disriminators: probb and probbb
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X 
    _jetInfo.CSV  = jet.bDiscriminator(_btagName+":probb") + jet.bDiscriminator(_btagName+":probbb");
    if (_jetInfo.CSV < 0.) _jetInfo.CSV = -0.4;
    if (_jetInfo.CSV > 1.) _jetInfo.CSV = 1.0;
    _jetInfo.puID = jet.userFloat("pileupJetId:fullDiscriminant");
    
    const reco::GenJet* genJet = jet.genJet();
    if (genJet != NULL) {
      _jetInfo.genMatched = true;
      _jetInfo.genPx      = genJet->px();
      _jetInfo.genPy      = genJet->py();
      _jetInfo.genPz      = genJet->pz();
      _jetInfo.genPt      = genJet->pt();
      _jetInfo.genEta     = genJet->eta();
      _jetInfo.genPhi     = genJet->phi();
      _jetInfo.genMass    = genJet->mass();
      double genJetEnergy = genJet->energy();
      _jetInfo.genEMF     = genJet->emEnergy() / genJetEnergy;
      _jetInfo.genHadF    = genJet->hadEnergy() / genJetEnergy;
      _jetInfo.genInvF    = genJet->invisibleEnergy() / genJetEnergy;
      _jetInfo.genAuxF    = genJet->auxiliaryEnergy() / genJetEnergy;
    }
    else {
      _jetInfo.genMatched = false;
      _jetInfo.genPx      = -1;
      _jetInfo.genPy      = -1;
      _jetInfo.genPz      = -1;
      _jetInfo.genPt      = -1;
      _jetInfo.genEta     = -1;
      _jetInfo.genPhi     = -1;
      _jetInfo.genMass    = -1;
      _jetInfo.genEMF     = -1;
      _jetInfo.genHadF    = -1;
      _jetInfo.genInvF    = -1;
      _jetInfo.genAuxF    = -1;
    }
    
    if ( fabs( jet.eta() ) < 2.4 ) nJetsCent += 1;
    else                           _nJetsFwd += 1;
    // https://twiki.cern.ch/twiki/bin/view/CMS/BtagPOG
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X - updated deepCSV WP 2018.06.01 (PB)
    // https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods
    if ( fabs( jet.eta() ) < 2.4 ) {
      if ( _jetInfo.CSV > 0.1522 )   _nBLoose  += 1;
      if ( _jetInfo.CSV > 0.4941 )   _nBMed    += 1;
      if ( _jetInfo.CSV > 0.8001 )   _nBTight  += 1;
    }
    _jetInfos.push_back( _jetInfo );

  }  // End loop: for (int i = 0; i < nJets; i++)

  if ( nJetsCent + _nJetsFwd != int(_jetInfos.size()) )
    std::cout << "Bizzare error: _jetInfos.size() = " << _jetInfos.size()
	      << ", nJetsCent = " << nJetsCent
	      << ", _nJetsFwd = " << _nJetsFwd << std::endl;
  
}


pat::JetCollection SelectJets( const edm::Handle<pat::JetCollection>& jets, 
			       const JetCorrectorParameters& JetCorPar, JME::JetResolution& JetRes,
			       JME::JetResolutionScaleFactor& JetResSF, const std::string _JEC_syst,
			       const MuonInfos&_muonInfos, const EleInfos& _eleInfos, const double _rho,
			       const std::string _jet_ID, const double _jet_pT_min, const double _jet_eta_max,
			       TLorentzVector& _dMet ) {
  
  // Following https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID#Recommendations_for_13_TeV_data
  //       and https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2016
  // Last check that cuts were up-to-date: March 10, 2017 (AWB)
  // Modeled after "isGoodJet" in https://github.com/cms-ttH/MiniAOD/blob/master/MiniAODHelper/src/MiniAODHelper.cc
  // VBF H-->bb analysis: http://cms.cern.ch/iCMS/analysisadmin/cadilines?line=HIG-16-003
  // Is PU jet ID used at some point in the sequence? (http://cds.cern.ch/record/1581583) Or just charged hadron subtraction (CHS)?
  // B-tagging docmuentation (CSV_v2) here: http://cds.cern.ch/record/2138504

  pat::JetCollection jetsSelected;
  jetsSelected.clear();
  _dMet.SetPtEtaPhiM( 0., 0., 0., 0.);

  if ( !jets.isValid() ) {
    std::cout << "No valid jet collection" << std::endl;
    return jetsSelected;
  }

  if (_jet_ID.find("loose") == std::string::npos && _jet_ID.find("tight") == std::string::npos)
    std::cout << "Jet ID is neither tight nor loose: " << _jet_ID
              << "\nWill not be used, no jet ID cuts applied" << std::endl;

  // HAVE TO DELETE AFTER LOOP TO AVOID MEMORY LEAK!!!!
  JetCorrectionUncertainty *JecUnc = new JetCorrectionUncertainty(JetCorPar);
  
  for (pat::JetCollection::const_iterator jet = jets->begin(), jetsEnd = jets->end(); jet !=jetsEnd; ++jet) {

    pat::Jet corr_jet = (*jet);
    TLorentzVector pre_vec;
    TLorentzVector post_vec;
    pre_vec.SetPtEtaPhiM( corr_jet.pt(), corr_jet.eta(), corr_jet.phi(), corr_jet.mass() );

    // Clean out jets with dR < 0.4 to a selected muon
    bool pass_muon_dR = true;
    TLorentzVector mu_vec;
    for (int iMu = 0; iMu < int(_muonInfos.size()); iMu++) {
      mu_vec.SetPtEtaPhiM( _muonInfos.at(iMu).pt, _muonInfos.at(iMu).eta, _muonInfos.at(iMu).phi, 0.10566 );
      if ( pre_vec.DeltaR(mu_vec) < 0.4 ) pass_muon_dR = false;
    }
    if (!pass_muon_dR) continue;
    
    // Apply jet energy scale systematics
    // Modeled after https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#JetCorUncertainties
    //           and https://github.com/cms-ttH/MiniAOD/blob/master/MiniAODHelper/src/MiniAODHelper.cc#L374
    JecUnc->setJetEta( corr_jet.eta() );
    JecUnc->setJetPt ( corr_jet.pt()  );
    double JES_uncert = JecUnc->getUncertainty(true);

    // Apply jet energy resolution systematics
    // Modeled after https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyResolution
    //   - Last check that procedure was up-to-date: March 10, 2017 (AWB)
    JME::JetParameters JetResParams;
    JetResParams.setJetEta( corr_jet.eta() );
    JetResParams.setJetPt ( corr_jet.pt()  );
    JetResParams.setRho   ( _rho           );
    JetRes.getResolution  ( JetResParams );
    double JER_nom  = JetResSF.getScaleFactor( JetResParams );
    double JER_up   = JetResSF.getScaleFactor( JetResParams, Variation::UP );
    double JER_down = JetResSF.getScaleFactor( JetResParams, Variation::DOWN );
    // std::cout << "JER_nom = " << JER_nom << ", JER_up = " << JER_up << ", JER_down = " << JER_down << std::endl;
    
    if      ( _JEC_syst.find("JES_up")   != std::string::npos )
      corr_jet.scaleEnergy( 1. + JES_uncert );
    else if ( _JEC_syst.find("JES_down") != std::string::npos )
      corr_jet.scaleEnergy( 1. - JES_uncert );
    else if ( _JEC_syst.find("JER_nom")  != std::string::npos )
      corr_jet.scaleEnergy( JER_nom );
    else if ( _JEC_syst.find("JER_up")   != std::string::npos )
      corr_jet.scaleEnergy( JER_up );
    else if ( _JEC_syst.find("JER_down") != std::string::npos )
      corr_jet.scaleEnergy( JER_down );
    else if ( _JEC_syst.find("none")     == std::string::npos )
      std::cout << "Invalid jet energy systematic " << _JEC_syst << ". Leaving uncorrected." << std::endl;

    // Set negative for cancellation
    post_vec.SetPtEtaPhiM( corr_jet.pt(), corr_jet.eta(), corr_jet.phi(), corr_jet.mass() );

    // Use 15 GeV jets with < 90% EM energy and not overlapping a muon to correct MET
    // Modeled after https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETRun2Corrections#Type_I_Correction_Propagation_of
    //  - Last check that procedure was up-to-date: March 10, 2017 (AWB)
    bool use_for_MET_corr = true;
    if ( pre_vec.Pt() < 15 || corr_jet.chargedEmEnergyFraction() + corr_jet.neutralEmEnergyFraction() > 0.9 )
      use_for_MET_corr = false;

    // // Seems to find all jets? - AWB 13.03.17
    // const std::vector<reco::CandidatePtr> & cands = corr_jet.daughterPtrVector();
    // for ( std::vector<reco::CandidatePtr>::const_iterator cand = cands.begin(); cand != cands.end(); ++cand ) {
    //   const reco::PFCandidate *pfcand = dynamic_cast<const reco::PFCandidate *>(cand->get());
    //   const reco::Candidate *mu = (pfcand != 0 ? ( pfcand->muonRef().isNonnull() ? pfcand->muonRef().get() : 0) : cand->get());
    //   if ( mu != 0 ) use_for_MET_corr = false;
    // }
    
    if (use_for_MET_corr) {
      _dMet = _dMet + pre_vec - post_vec;
      // std::cout << "pre_vec.Pt() = " << pre_vec.Pt() << ", post_vec.Pt() = " << post_vec.Pt() << ", _dMet.Pt() = " << _dMet.Pt() << std::endl;
    }

    // Apply cuts for selected jets
    if ( corr_jet.pt()          < _jet_pT_min  ) continue;
    if ( fabs( corr_jet.eta() ) > _jet_eta_max ) continue;
    
    bool isLoose = false;
    bool isTight = false;

    if ( fabs( corr_jet.eta() ) < 2.7 ) {

      isLoose = ( corr_jet.neutralHadronEnergyFraction() < 0.99 &&
		  corr_jet.neutralEmEnergyFraction()     < 0.99 &&
		  ( corr_jet.chargedMultiplicity() + 
		    corr_jet.neutralMultiplicity() )     > 1 );

      isTight = ( isLoose                                       && 
		  corr_jet.neutralHadronEnergyFraction() < 0.90 &&
		  corr_jet.neutralEmEnergyFraction()     < 0.90 );

      if ( fabs( corr_jet.eta() ) < 2.4 ) {
	
	isLoose &= ( corr_jet.chargedHadronEnergyFraction() > 0.   &&
		     corr_jet.chargedMultiplicity()         > 0    &&
		     corr_jet.chargedEmEnergyFraction()     < 0.99 );
	
	isTight &= isLoose;
      }
    } // End if ( fabs( corr_jet.eta() ) < 2.7 )
    else if ( fabs( corr_jet.eta() ) < 3.0 ) {

      isLoose = ( corr_jet.neutralEmEnergyFraction()     > 0.01 &&
		  corr_jet.neutralHadronEnergyFraction() < 0.98 &&
		  corr_jet.neutralMultiplicity()         > 2 );
      isTight = isLoose;
    }
    else {
      isLoose = ( corr_jet.neutralEmEnergyFraction() < 0.90 &&
		  corr_jet.neutralMultiplicity()     > 10 );
      isTight = isLoose;
    }

    if (_jet_ID.find("loose") != std::string::npos && !isLoose) continue;
    if (_jet_ID.find("tight") != std::string::npos && !isTight) continue;
    
    jetsSelected.push_back(corr_jet);
  } // End loop: for (pat::JetCollection::const_iterator jet = jets->begin(), jetsEnd = jets->end(); jet !=jetsEnd; ++jet)

  delete JecUnc; // AVOID NASTY MEMORY LEAK!!!
  
  return jetsSelected;
}
