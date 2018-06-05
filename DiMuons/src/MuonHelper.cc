
#include "Ntupliser/DiMuons/interface/MuonHelper.h"

void FillMuonInfos( MuonInfos& _muonInfos, 
		    const pat::MuonCollection muonsSelected,
		    const reco::Vertex primaryVertex, const int _nPV,
		    const edm::Handle<reco::BeamSpot>& beamSpotHandle,  
		    const edm::Event& iEvent, const edm::EventSetup& iSetup,
		    const edm::Handle<pat::TriggerObjectStandAloneCollection>& _trigObjsHandle,
		    const edm::Handle<edm::TriggerResults>& _trigResultsHandle,
		    const std::vector<std::string> _trigNames, const double _muon_trig_dR, 
		    const bool _muon_use_pfIso, const double _muon_iso_dR, const bool _isData,
		    KalmanMuonCalibrator& _KaMu_calib, const bool _doSys_KaMu,
		    const RoccoR _Roch_calib, const bool _doSys_Roch,
		    const edm::Handle < reco::GenParticleCollection >& genPartons ) {
  
  double const MASS_MUON = 0.105658367; // GeV/c^2

  _muonInfos.clear();
  int nMuons = muonsSelected.size();

  for (int i = 0; i < nMuons; i++) {

    pat::Muon muon = muonsSelected.at(i);
    MuonInfo _muonInfo;
    _muonInfo.init();

    reco::Track track;
    // Do we want to use the inner tracker track by default for the Kalman corrections? - AWB 12.11.16
    if      ( muon.isGlobalMuon()  ) track = *(muon.globalTrack() );
    else if ( muon.isTrackerMuon() ) track = *(muon.innerTrack()  );
    else {
      std::cout << "ERROR: The muon is NOT global NOR tracker ?!?\n";
      continue;
    }

    // Basic kinematics
    // "muon.pt()" returns PF quantities if PF is available - and all loose/med/tight muons are PF
    _muonInfo.charge = muon.charge();
    _muonInfo.pt     = muon.pt();
    _muonInfo.ptErr  = muon.muonBestTrack()->ptError();
    _muonInfo.eta    = muon.eta();
    _muonInfo.phi    = muon.phi();

    // Basic quality
    _muonInfo.isTightID      = MuonIsTight  ( muon, primaryVertex );
    _muonInfo.isMediumID     = MuonIsMedium ( muon ) && muon.innerTrack()->validFraction() > 0.8;
    _muonInfo.isMediumID2016 = MuonIsMedium ( muon );
    _muonInfo.isLooseID      = MuonIsLoose  ( muon );
    
    // Basic isolation
    if ( _muon_use_pfIso )
      _muonInfo.relIso = MuonCalcRelIsoPF ( muon, _muon_iso_dR );
    else
      _muonInfo.relIso = MuonCalcRelIsoTrk( muon, _muon_iso_dR );
    
    // Basic vertexing? - AWB 12.11.16

    // Basic trigger (which triggers are in the list? - AWB 12.11.16)
    for (unsigned int iTrig = 0; iTrig < _trigNames.size(); iTrig++) {
      if (iTrig >= _muonInfo.nTrig) {
    	std::cout << "Found " << i+1 << "th muon trigger; only " << _muonInfo.nTrig << " allowed in array" << std::endl;
    	continue;
      }
      _muonInfo.isHltMatched[iTrig] = IsHltMatched( muon, iEvent, iSetup, _trigObjsHandle, _trigResultsHandle,  
    							  _trigNames[iTrig], _muon_trig_dR );
      _muonInfo.hltEff[iTrig] = MuonCalcTrigEff( muon, _nPV, _trigNames[iTrig] );
    }


    // // -------------------------
    // // ONLY SAVE BASIC VARIABLES - AWB 12.11.16
    // // -------------------------
    // if ( _outputLevel == "Slim") 
    //   continue;

    // Inner track kinematics
    if (muon.isTrackerMuon()) {
      _muonInfo.pt_trk    = muon.innerTrack()->pt();
      _muonInfo.ptErr_trk = muon.innerTrack()->ptError();
      _muonInfo.eta_trk   = muon.innerTrack()->eta();
      _muonInfo.phi_trk   = muon.innerTrack()->phi();

      // Kalman-calibrated pT
      double pt_KaMu    = muon.innerTrack()->pt();
      double ptErr_KaMu = muon.innerTrack()->ptError();
      double eta_KaMu   = muon.innerTrack()->eta();
      double phi_KaMu   = muon.innerTrack()->phi();
      int charge_KaMu   = muon.innerTrack()->charge();
      double pt_KaMu_sys_up, pt_KaMu_sys_down, pt_KaMu_clos_up, pt_KaMu_clos_down;

      CorrectPtKaMu( _KaMu_calib, _doSys_KaMu, 
      		     pt_KaMu, ptErr_KaMu, pt_KaMu_sys_up, 
      		     pt_KaMu_sys_down, pt_KaMu_clos_up, pt_KaMu_clos_down,
      		     eta_KaMu, phi_KaMu, charge_KaMu, _isData );

      _muonInfo.pt_KaMu           = pt_KaMu;
      _muonInfo.ptErr_KaMu        = ptErr_KaMu;
      _muonInfo.pt_KaMu_sys_up    = pt_KaMu_sys_up;
      _muonInfo.pt_KaMu_sys_down  = pt_KaMu_sys_down;
      _muonInfo.pt_KaMu_clos_up   = pt_KaMu_clos_up;
      _muonInfo.pt_KaMu_clos_down = pt_KaMu_clos_down;

      // Rochester-calibrated pT
      TLorentzVector mu_vec_Roch, GEN_vec;
      mu_vec_Roch.SetPtEtaPhiM( muon.innerTrack()->pt(), muon.innerTrack()->eta(),
      				muon.innerTrack()->phi(), MASS_MUON );
      float pt_Roch, pt_Roch_sys_up, pt_Roch_sys_down;
      float ptErr_Roch    = muon.innerTrack()->ptError();
      int charge_Roch     = muon.innerTrack()->charge();
      int trk_layers_Roch = muon.innerTrack()->hitPattern().trackerLayersWithMeasurement(); 

      int iMatch = -99;
      if (not _isData) {
	for (unsigned int i = 0; i < genPartons->size(); i++) {
	  const reco::Candidate& GEN_mu = genPartons->at(i);
	  if ( abs(GEN_mu.pdgId()) != 13 ) continue;
	  if ( GEN_mu.status() != 1 ) continue;
	  if ( GEN_mu.charge() != _muonInfo.charge ) continue;
	
	  GEN_vec.SetPtEtaPhiM( GEN_mu.pt(), GEN_mu.eta(), GEN_mu.phi(), GEN_mu.mass() );
	  if (GEN_vec.DeltaR(mu_vec_Roch) > 0.005) continue;
	  if (iMatch > 0) {
	    std::cout << "\nBizzare situation: two muons match!" << std::endl;
	    std::cout << "RECO pT = " << mu_vec_Roch.Pt() << ", eta = " << mu_vec_Roch.Eta() 
		      << ", phi = " << mu_vec_Roch.Phi() << ", charge = " << _muonInfo.charge << std::endl;
	    std::cout << "GEN1 pT = " << genPartons->at(i).pt()<< ", eta = " << genPartons->at(i).eta() 
		      << ", phi = " << genPartons->at(i).phi() << std::endl;
	    std::cout << "GEN2 pT = " << GEN_vec.Pt()<< ", eta = " << GEN_vec.Eta() << ", phi = " << GEN_vec.Phi() << std::endl;
	  }
	  
	  iMatch = i;
	  _muonInfo.GEN_pt = GEN_vec.Pt();
	  _muonInfo.GEN_dR = GEN_vec.DeltaR(mu_vec_Roch);
	}
      } // End conditional: if (not _isData)

      float GEN_pt = (iMatch > 0) ? _muonInfo.GEN_pt : -99;
      
      CorrectPtRoch( _Roch_calib, _doSys_Roch, mu_vec_Roch, 
      		     pt_Roch, ptErr_Roch, pt_Roch_sys_up, pt_Roch_sys_down,
      		     charge_Roch, trk_layers_Roch, GEN_pt, _isData );
      
      _muonInfo.pt_Roch           = pt_Roch;
      _muonInfo.ptErr_Roch        = ptErr_Roch;
      _muonInfo.pt_Roch_sys_up    = pt_Roch_sys_up;
      _muonInfo.pt_Roch_sys_down  = pt_Roch_sys_down;
      
    } // End if (muon.isTrackerMuon())

    // Particle flow kinematics
    if ( muon.isPFMuon() ) {
      reco::Candidate::LorentzVector pfmuon = muon.pfP4();
      _muonInfo.pt_PF    = pfmuon.Pt();
      _muonInfo.ptErr_PF = muon.muonBestTrack()->ptError();
      // Would be nice if we could access deltaP() from PFCandidate.h, but not in PAT::Muon - AWB 10.03.17
      _muonInfo.eta_PF   = pfmuon.Eta();
      _muonInfo.phi_PF   = pfmuon.Phi();
    }

    // Standard quality
    _muonInfo.isGlobal     = muon.isGlobalMuon();
    _muonInfo.isTracker    = muon.isTrackerMuon();
    _muonInfo.isStandAlone = muon.isStandAloneMuon();
    _muonInfo.isPF         = muon.isPFMuon();
    
    // Standard vertexing
    _muonInfo.d0_BS= muon.innerTrack()->dxy( beamSpotHandle->position() );
    _muonInfo.dz_BS= muon.innerTrack()->dz ( beamSpotHandle->position() );
    
    _muonInfo.d0_PV = track.dxy( primaryVertex.position() );
    _muonInfo.dz_PV = track.dz ( primaryVertex.position() );

    // Standard isolation
    _muonInfo.trackIsoSumPt     = muon.isolationR03().sumPt;
    _muonInfo.trackIsoSumPtCorr = muon.isolationR03().sumPt; // no correction with only 1 muon (??? - AWB 08.11.16)
    
    // Correct Iso calculation? - AWB 08.11.16
    double isovar = muon.isolationR03().sumPt;
    isovar += muon.isolationR03().hadEt; // tracker + HCAL
    isovar /= muon.pt(); // relative combine isolation
    _muonInfo.relCombIso = isovar;

    // // Standard trigger variables
    // for (unsigned int iTrig = 0; iTrig < _trigNames.size(); iTrig++) {
    //   if (iTrig >= trigArraySize) {
    // 	std::cout << "Found " << i+1 << "th muon trigger; only " << trigArraySize << " allowed in array" << std::endl;
    // 	continue;
    //   }
    //   // _muonInfo.hltPt[iTrig]  = ???; - AWB 12.11.16
    //   // _muonInfo.hltEta[iTrig] = ???; - AWB 12.11.16
    //   // _muonInfo.hltPhi[iTrig] = ???; - AWB 12.11.16
    // }

    // // -----------------------------
    // // DON'T SAVE ADVANCED VARIABLES - AWB 12.11.16
    // // -----------------------------
    // if ( _outputLevel != "Fat") 
    //   continue;
    
    // Advanced isolation
    _muonInfo.ecalIso = muon.isolationR03().emEt;
    _muonInfo.hcalIso = muon.isolationR03().hadEt;

    if ( muon.isPFMuon() ) {

      _muonInfo.sumChargedHadronPtR03   = muon.pfIsolationR03().sumChargedHadronPt  ;
      _muonInfo.sumChargedParticlePtR03 = muon.pfIsolationR03().sumChargedParticlePt;
      _muonInfo.sumNeutralHadronEtR03   = muon.pfIsolationR03().sumNeutralHadronEt  ;
      _muonInfo.sumPhotonEtR03          = muon.pfIsolationR03().sumPhotonEt         ;
      _muonInfo.sumPUPtR03              = muon.pfIsolationR03().sumPUPt             ;
      
      _muonInfo.sumChargedHadronPtR04   = muon.pfIsolationR04().sumChargedHadronPt  ;
      _muonInfo.sumChargedParticlePtR04 = muon.pfIsolationR04().sumChargedParticlePt;
      _muonInfo.sumNeutralHadronEtR04   = muon.pfIsolationR04().sumNeutralHadronEt  ;
      _muonInfo.sumPhotonEtR04          = muon.pfIsolationR04().sumPhotonEt         ;
      _muonInfo.sumPUPtR04              = muon.pfIsolationR04().sumPUPt             ;
    }

    _muonInfos.push_back( _muonInfo );
  } // End loop: for (unsigned int i = 0; i < nMuons; i++)

} // End function: void FillMuonInfos
    

pat::MuonCollection SelectMuons( const edm::Handle<pat::MuonCollection>& muons, 
				 const reco::Vertex primaryVertex, const std::string _muon_ID,
				 const double _muon_pT_min, const double _muon_eta_max, const double _muon_trig_dR, 
				 const bool _muon_use_pfIso, const double _muon_iso_dR, const double _muon_iso_max ) {
  
  // Following https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_Identification
  
  pat::MuonCollection muonsSelected;
  muonsSelected.clear();
  
  if ( !muons.isValid() ) {
    std::cout << "No valid muon collection" << std::endl;
    return muonsSelected;
  }
  
  for (pat::MuonCollection::const_iterator muon = muons->begin(), muonsEnd = muons->end(); muon !=muonsEnd; ++muon) {

    if ( muon->pt()        < _muon_pT_min  ) continue;
    if ( fabs(muon->eta()) > _muon_eta_max ) continue;
    
    if ( _muon_ID.find("loose")  != std::string::npos && !MuonIsLoose ( (*muon) )                ) continue;
    if ( _muon_ID.find("medium") != std::string::npos && !MuonIsMedium( (*muon) )                ) continue;
    if ( _muon_ID.find("tight")  != std::string::npos && !MuonIsTight ( (*muon), primaryVertex ) ) continue;

    if ( _muon_use_pfIso ) {
      if ( MuonCalcRelIsoPF ( (*muon), _muon_iso_dR ) > _muon_iso_max ) continue;
    } else {
      if ( MuonCalcRelIsoTrk( (*muon), _muon_iso_dR ) > _muon_iso_max ) continue;
    }
    
    muonsSelected.push_back(*muon);
  }
  
  return muonsSelected;
}

bool MuonIsLoose ( const pat::Muon muon ) {
  bool _isLoose = ( muon.isPFMuon() && ( muon.isGlobalMuon() || muon.isTrackerMuon() ) );
  if ( _isLoose  != muon::isLooseMuon(muon)  )
    std::cout << "Manual muon isLoose = " << _isLoose << ", muon::isLooseMuon = " 
	      << muon::isLooseMuon(muon) << ". Using manual version ..." << std::endl;
  return _isLoose;
}

bool MuonIsMedium( const pat::Muon muon ) {
  bool _goodGlob = ( muon.isGlobalMuon()                           && 
		     muon.globalTrack()->normalizedChi2() < 3      && 
		     muon.combinedQuality().chi2LocalPosition < 12 && 
		     muon.combinedQuality().trkKink < 20           ); 
  bool _isMedium = ( MuonIsLoose( muon )                                            && 
		     muon.innerTrack()->validFraction() > 0.49                      && 
		     muon::segmentCompatibility(muon) > (_goodGlob ? 0.303 : 0.451) ); 
  if ( _isMedium  != muon::isMediumMuon(muon) && muon.innerTrack()->validFraction() > 0.8 )
    std::cout << "Manual muon isMedium = " << _isMedium << ", muon::isMediumMuon = " 
	      << muon::isMediumMuon(muon) << ". Using manual version ..." << std::endl;
  return _isMedium;
}

bool MuonIsTight( const pat::Muon muon, const reco::Vertex primaryVertex ) {
  bool _isTight  = ( muon.isGlobalMuon() && muon.isPFMuon()                            && 
		     muon.globalTrack()->normalizedChi2() < 10.                        &&
		     muon.globalTrack()->hitPattern().numberOfValidMuonHits() > 0      && 
		     muon.numberOfMatchedStations() > 1                                &&
		     // fabs(muon.muonBestTrack()->dB()) < 0.2                            &&  // How do we implement this? - AWB 14.11.16 
		     fabs(muon.muonBestTrack()->dz( primaryVertex.position() )) < 0.5  &&
		     muon.innerTrack()->hitPattern().numberOfValidPixelHits() > 0      &&
		     muon.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5 );
  
  if ( _isTight  != muon::isTightMuon(muon, primaryVertex)  )
    std::cout << "Manual muon isTight = " << _isTight << ", muon::isTightMuon = " 
	      << muon::isTightMuon(muon, primaryVertex) << ". Using manual version ..." << std::endl;
  return _isTight;
}

double MuonCalcRelIsoPF( const pat::Muon muon, const double _muon_iso_dR ) {
  // Following https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_Isolation
  double iso = -999.;
  if ( _muon_iso_dR == 0.4 ) {
    iso  = muon.pfIsolationR04().sumChargedHadronPt;
    iso += std::max( 0., muon.pfIsolationR04().sumNeutralHadronEt + muon.pfIsolationR04().sumPhotonEt - 0.5*muon.pfIsolationR04().sumPUPt );
  } 
  else if ( _muon_iso_dR == 0.3 ) {
    iso  = muon.pfIsolationR03().sumChargedHadronPt;
    iso += std::max( 0., muon.pfIsolationR03().sumNeutralHadronEt + muon.pfIsolationR03().sumPhotonEt - 0.5*muon.pfIsolationR03().sumPUPt );
  }
  else {
    std::cout << "Muon isolation dR = " << _muon_iso_dR << ", not 0.3 or 0.4.  Cannot compute, setting to -999." << std::endl;
    return iso;
  }
  return (iso / muon.pt() );
}

double MuonCalcRelIsoTrk( const pat::Muon muon, const double _muon_iso_dR ) {
  // Following https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_Isolation
  double iso = -999.;
  // if ( _muon_iso_dR == 0.4 )
  //   iso = muon.isolationR04().sumPt;  // Apparently not an option
  if ( _muon_iso_dR == 0.3 )
    iso = muon.isolationR03().sumPt;
  else {
    std::cout << "Muon isolation dR = " << _muon_iso_dR << ", not 0.3.  Cannot compute, setting to -999." << std::endl;
    return iso;
  }
  return (iso / muon.pt() );
}

double MuonCalcTrigEff( const pat::Muon muon, const int _nPV, const std::string _trigName ) {

  // Guestimates based on https://indico.cern.ch/event/570616/contributions/2359949/attachments/1365003/2067370/Muon_HLT_Budapest_WS.pdf
  
  double _HLT_eff_vs_nPV = 0.99 - 0.04 * pow( (_nPV/40.), 2 );
  double _HLT_eff_vs_pT  = 1.;  // Depends on muon.pt() near the threshold? - AWB 14.11.16

  double _L1T_eff_vs_eta = -999.;
  if      ( fabs(muon.eta()) < 1.2 ) _L1T_eff_vs_eta = 0.96;
  else if ( fabs(muon.eta()) < 1.6 ) _L1T_eff_vs_eta = 0.94;
  else if ( fabs(muon.eta()) < 2.1 ) _L1T_eff_vs_eta = 0.85;
  else                               _L1T_eff_vs_eta = 0.82;
  
  if ( _trigName.find("Iso") != std::string::npos ) {
    return _L1T_eff_vs_eta * _HLT_eff_vs_nPV * _HLT_eff_vs_pT; }
  else
    return _L1T_eff_vs_eta * _HLT_eff_vs_pT;
}

bool IsHltMatched( const pat::Muon& muon, const edm::Event& iEvent, const edm::EventSetup& iSetup,
		   const edm::Handle<pat::TriggerObjectStandAloneCollection>& _trigObjsHandle,
		   const edm::Handle<edm::TriggerResults>& _trigResultsHandle,
		   const std::string _desiredTrigName, const double _muon_trig_dR ) {
  
  // Check if the muon is the one firing the HLT path
  
  using namespace std;
  using namespace edm;
  using namespace pat;
  using namespace reco;
  using namespace trigger;
  
  const boost::regex rgx("_v[0-9]+");
  
  const TriggerNames &trigNames = iEvent.triggerNames(*_trigResultsHandle);
  
  const unsigned nTrigs = _trigResultsHandle->size();
  for (unsigned iTrig = 0; iTrig < nTrigs; ++iTrig) {
    const string trigName = trigNames.triggerName(iTrig);
    string trigNameStripped = boost::regex_replace(trigName, rgx, "", boost::match_default | boost::format_sed);
    if ( _desiredTrigName == trigNameStripped && _trigResultsHandle->accept(iTrig) ) {
      stringstream debugString;
      debugString << "IsHltMatched: ";
      debugString << "'" << _desiredTrigName << "'\n";
      debugString << "  Trigger " << iTrig << ": " << trigName << "(" << trigNameStripped
		  << ") passed: " << _trigResultsHandle->accept(iTrig) << endl;
      
      for ( TriggerObjectStandAloneCollection::const_iterator trigObj = (*_trigObjsHandle).begin();
	    trigObj != (*_trigObjsHandle).end(); trigObj++) {
	
	TriggerObjectStandAlone tmpTrigObj(*trigObj); // Get rid of const which messes up unpackPathNames
	tmpTrigObj.unpackPathNames(trigNames);
	bool isRightObj = tmpTrigObj.hasPathName(trigName, true, true); // Name, is L3 filter accepted, is last filter
	if (isRightObj) {
	  debugString << "    TriggerObject:  " << tmpTrigObj.collection() << endl;
	  bool isMatched = ( deltaR(tmpTrigObj, muon) < _muon_trig_dR );
	  if (isMatched) {
	    debugString << "      is Matched*****" << endl;
	    LogVerbatim("UFHLTTests") << debugString.str();
	    return true;
	  }
	} // if isRightObj
      } // trigObj lookp
      LogVerbatim("UFHLTTests") << debugString.str();
    } // if desiredTrigger
  } // iTrig loop
  
  return false;
}

void CalcTrigEff( float& _muon_eff, float& _muon_eff_up, float& _muon_eff_down, 
		  const TH2F* _muon_eff_hist, const MuonInfos _muonInfos, const bool EMTF_bug ) {

  // EMTF_bug not yet implemented - AWB 18.01.17
  // https://twiki.cern.ch/twiki/bin/view/CMS/EndcapHighPtMuonEfficiencyProblem

  float ineff      = 1.;
  float ineff_up   = 1.;
  float ineff_down = 1.;

  int   nFound   =    0;
  int   mu_end_1 =    0;
  int   mu_end_2 =    0;
  float mu_phi_1 = -99.;
  float mu_phi_2 = -99.;

  for (int iMu = 0; iMu < int(_muonInfos.size()); iMu++) {
    float mu_pt  = std::min( _muonInfos.at(iMu).pt, 
			     _muon_eff_hist->GetYaxis()->GetBinLowEdge( _muon_eff_hist->GetNbinsY() ) +
			     _muon_eff_hist->GetYaxis()->GetBinWidth(   _muon_eff_hist->GetNbinsY() ) - 0.01 );
    float mu_eta = std::min( fabs(_muonInfos.at(iMu).eta),
			     _muon_eff_hist->GetXaxis()->GetBinLowEdge( _muon_eff_hist->GetNbinsX() ) +
			     _muon_eff_hist->GetXaxis()->GetBinWidth(   _muon_eff_hist->GetNbinsX() ) - 0.01 );
    bool found_mu = false;

    if ( mu_pt < _muon_eff_hist->GetYaxis()->GetBinLowEdge(1) ) continue;
    // Find endcap and phi value of EMTF muons
    if ( EMTF_bug && fabs(_muonInfos.at(iMu).eta) > 1.24 ) {
      if ( mu_end_1 == 0 ) {
	mu_end_1 = ( _muonInfos.at(iMu).eta > 0 ? 1 : -1 );
	mu_phi_1 = CalcL1TPhi(_muonInfos.at(iMu).pt, _muonInfos.at(iMu).eta, _muonInfos.at(iMu).phi, _muonInfos.at(iMu).charge);
      } else if ( mu_end_2 == 0 ) {
	mu_end_2 = ( _muonInfos.at(iMu).eta > 0 ? 1 : -1 );
	mu_phi_2 = CalcL1TPhi(_muonInfos.at(iMu).pt, _muonInfos.at(iMu).eta, _muonInfos.at(iMu).phi, _muonInfos.at(iMu).charge);
      }
    }
    
    for (int iPt = 1; iPt <= _muon_eff_hist->GetNbinsY(); iPt++) {
      if ( found_mu ) continue;
      if ( mu_pt < _muon_eff_hist->GetYaxis()->GetBinLowEdge(iPt) ) continue;
      if ( mu_pt > _muon_eff_hist->GetYaxis()->GetBinLowEdge(iPt) + _muon_eff_hist->GetYaxis()->GetBinWidth(iPt) ) continue;
      
      for (int iEta = 1; iEta <= _muon_eff_hist->GetNbinsX(); iEta++) {
	if ( found_mu ) continue;
	if ( mu_eta < _muon_eff_hist->GetXaxis()->GetBinLowEdge(iEta) ) continue;
	if ( mu_eta > _muon_eff_hist->GetXaxis()->GetBinLowEdge(iEta) + _muon_eff_hist->GetXaxis()->GetBinWidth(iEta) ) continue;

	found_mu = true;
	nFound += 1;

	if ( EMTF_bug && nFound == 2 && mu_end_1*mu_end_2 == 1 && SameSector(mu_phi_1, mu_phi_2) ) {
	  float eff_1      = 1. - ineff;
	  float eff_1_up   = 1. - ineff_up;
	  float eff_1_down = 1. - ineff_down;
	  float eff_2      = _muon_eff_hist->GetBinContent(iEta, iPt);
	  float eff_2_up   = _muon_eff_hist->GetBinContent(iEta, iPt) + _muon_eff_hist->GetBinError(iEta, iPt);
	  float eff_2_down = _muon_eff_hist->GetBinContent(iEta, iPt) - _muon_eff_hist->GetBinError(iEta, iPt);
	  ineff      = (1. - (eff_1      + eff_2     ) / 2.);
	  ineff_up   = (1. - (eff_1_up   + eff_2_up  ) / 2.);
	  ineff_down = (1. - (eff_1_down + eff_2_down) / 2.);
	} else {
	  ineff      *= ( 1. - _muon_eff_hist->GetBinContent(iEta, iPt) );
	  ineff_up   *= ( 1. - _muon_eff_hist->GetBinContent(iEta, iPt) - _muon_eff_hist->GetBinError(iEta, iPt) );
	  ineff_down *= ( 1. - _muon_eff_hist->GetBinContent(iEta, iPt) + _muon_eff_hist->GetBinError(iEta, iPt) );
	}

      } // End loop: for (int iEta = 1; iEta <= _muon_eff_hist->GetNbinsX(); iEta++)
    } // End loop: for (int iPt = 1; iPt <= _muon_eff_hist->GetNbinsY(); iPt++)
  } // End loop: for (int iMu = 0; iMu < int(_muonInfos.size()); iMu++)

  _muon_eff      = 1. - ineff;
  _muon_eff_up   = 1. - ineff_up;
  _muon_eff_down = 1. - ineff_down;

}

float CalcL1TPhi( const float mu_pt, const float mu_eta, float mu_phi, const int mu_charge ) {

  if (fabs(mu_eta) < 1.24)
    return mu_phi; // Only computed for EMTF

  float PI = 3.14159265359;

  // Input muon phi is in radians
  mu_phi  *= (180./PI);  // Convert to degrees
  float mu_theta = 2. * atan( exp(-1. * fabs(mu_eta) ) ) * (180./PI);
  float l1t_phi  = mu_phi + mu_charge * (1./mu_pt) * (10.48 - 5.1412 * mu_theta + 0.02308 * pow(mu_theta, 2) );

  mu_phi  *= (PI/180.);
  l1t_phi *= (PI/180.);  // Convert to radians
  if (l1t_phi >     PI) l1t_phi -= 2*PI;
  if (l1t_phi < -1.*PI) l1t_phi += 2*PI;

  // std::cout << "Muon pt " << mu_pt << ", eta " << mu_eta << ", charge " << mu_charge 
  // 	    << ", phi " << mu_phi << " converted to L1T phi " << l1t_phi << std::endl;
  return l1t_phi;

}

bool SameSector( float phi1, float phi2 ) {

  bool same_sector = false;
  float PI = 3.14159265359;
  
  phi1 *= (180./PI);
  phi2 *= (180./PI);
  if (phi1 < 0) phi1 += 360.;
  if (phi2 < 0) phi2 += 360.;
  for (int iSect = 0; iSect < 6; iSect++) {
    if ( phi1 > 15 + 60*iSect && phi1 < 65 + 60*iSect &&
	 phi2 > 15 + 60*iSect && phi2 < 65 + 60*iSect ) same_sector = true;
    if ( phi1 >  5 + 60*iSect && phi1 < 15 + 60*iSect &&
	 phi2 >  5 + 60*iSect && phi2 < 15 + 60*iSect ) same_sector = true;
  }

  // if ( same_sector ) {
  //   std::cout << "\n********************************************************************************************" << std::endl;
  //   std::cout << "Muons with phi1 " << phi1 << " and phi2 " << phi2 << " are in the same sector" << std::endl;
  //   std::cout << "********************************************************************************************\n" << std::endl;
  // }

  return same_sector;
}
  
float CalcDPhi( const float phi1, const float phi2 ) {

  float abs_dPhi  = acos( cos(phi2 - phi1) );
  float sign_dPhi = sin(phi2 - phi1) / fabs( sin(phi2 - phi1) );
  std::cout << "phi1 = " << phi1 << ", phi2 = " << phi2 << ", dPhi = " << abs_dPhi*sign_dPhi << " (sign = " << sign_dPhi << ")" << std::endl;
  return abs_dPhi*sign_dPhi;
}


void CalcMuIDIsoEff(float& _ID_eff, float& _ID_eff_up, float& _ID_eff_down,
         float& _Iso_eff, float& _Iso_eff_up, float& _Iso_eff_down,
         const boost::property_tree::ptree json_iso, const boost::property_tree::ptree json_id, 
         const MuonInfos _muonInfos) {

  // needed to change the separator http://www.boost.org/doc/libs/1_47_0/doc/html/boost_propertytree/accessing.html
  typedef boost::property_tree::ptree::path_type path;
  //eta bins for SF
  std::vector<float> absetabins{0.00, 0.90, 1.20, 2.10, 2.40};
  //pt bins for SF
  std::vector<float> ptbins{20.00, 25.00, 30.00, 40.00, 50.00, 60.00, 120.00};

  _ID_eff       = 1.;
  _ID_eff_up    = 1.;
  _ID_eff_down  = 1.;
  _Iso_eff      = 1.;
  _Iso_eff_up   = 1.;
  _Iso_eff_down = 1.;

  //getting a specific value 
  // float scale_factor = 0.;
  // scale_factor = json_iso.get<float>(path("NUM_LooseRelIso_DEN_MediumID/abseta_pt/abseta:[1.20,2.10]/pt:[20.00,25.00]/value",'/'));
  // std::cout << scale_factor << std::endl;

  std::string _value_string, _err_string; 
  std::ostringstream _min_eta, _max_eta, _min_pt, _max_pt;
  _min_pt.str(""); _min_eta.str(""); _max_pt.str(""); _max_eta.str("");

  int nMu = int(_muonInfos.size());
  // Compute muon ID efficiency or scale factor
  for (int iMu = 0; iMu < nMu; iMu++){
    for ( int _abseta=0; _abseta<int(absetabins.size())-1; _abseta++){
      if ( abs(_muonInfos.at(iMu).eta) < absetabins.at(_abseta)) continue; 
      if ( abs(_muonInfos.at(iMu).eta) > absetabins.at(_abseta+1) ) continue;
      _min_eta << std::fixed << std::setprecision(2) << absetabins.at(_abseta);
      _max_eta << std::fixed << std::setprecision(2) << absetabins.at(_abseta+1);
   }
   if(_min_eta.str().compare(_max_eta.str()) == 0) { // if compare is ==0 the two strings are equal
      std::cout << "WARNING: Something fishy in the SF assignment. Setting all SF and uncertainties to 1.0. for this muon." << std::endl;
      _min_pt.str(""); _min_eta.str(""); _max_pt.str(""); _max_eta.str("");
      continue;
    }
    for ( int _pt=0; _pt<int(ptbins.size())-1; _pt++){
      if ( _muonInfos.at(iMu).pt < ptbins.at(_pt) ) continue; 
      if ( _muonInfos.at(iMu).pt > ptbins.at(_pt+1) ) continue; 
      _min_pt << std::fixed << std::setprecision(2) << ptbins.at(_pt);
      _max_pt << std::fixed << std::setprecision(2) << ptbins.at(_pt+1);
    } // loop pt bin 
   if(_min_pt.str().compare(_max_pt.str()) == 0 ){ // if compare is ==0 the two strings are equal. String are equal when muon_pt is over or under the min or max bin: in that case I set the SF to 1.0.
      std::cout << "WARNING: Setting all SF and uncertainties to 1.0. for this muon." << std::endl;
      _min_pt.str(""); _min_eta.str(""); _max_pt.str(""); _max_eta.str("");
      continue;
    }
    // ID
    _value_string = "NUM_SoftID_DEN_genTracks/abseta_pt/abseta:["+_min_eta.str()+","+_max_eta.str()+"]/pt:["+_min_pt.str()+","+_max_pt.str()+"]/value";
    _ID_eff = json_id.get<float>(path(_value_string.c_str(),'/'));
    _err_string = "NUM_SoftID_DEN_genTracks/abseta_pt/abseta:["+_min_eta.str()+","+_max_eta.str()+"]/pt:["+_min_pt.str()+","+_max_pt.str()+"]/error";
    _ID_eff_up = _ID_eff + json_id.get<float>(path(_err_string.c_str(),'/'));
    _ID_eff_down = _ID_eff - json_id.get<float>(path(_err_string.c_str(),'/'));
    // Iso
    _value_string = "NUM_LooseRelIso_DEN_MediumID/abseta_pt/abseta:["+_min_eta.str()+","+_max_eta.str()+"]/pt:["+_min_pt.str()+","+_max_pt.str()+"]/value";
    _Iso_eff = json_iso.get<float>(path(_value_string.c_str(),'/'));
//    std::cout << "Mu eta = " << abs(_muonInfos.at(iMu).eta)  << std::endl;
//    std::cout << "Mu pt = " <<  _muonInfos.at(iMu).pt << std::endl;
//    std::cout << "Iso_eff = " << _Iso_eff << std::endl;
    _err_string = "NUM_LooseRelIso_DEN_MediumID/abseta_pt/abseta:["+_min_eta.str()+","+_max_eta.str()+"]/pt:["+_min_pt.str()+","+_max_pt.str()+"]/error";
    _Iso_eff_up = _Iso_eff + json_iso.get<float>(path(_err_string.c_str(),'/'));
    _Iso_eff_down = _Iso_eff - json_iso.get<float>(path(_err_string.c_str(),'/'));
    //cleaning the strings
    _min_pt.str(""); _min_eta.str(""); _max_pt.str(""); _max_eta.str("");
  } // loop muons

  // for (auto& array_element : json_iso) {
  //   std::cout << array_element.first << std::endl;
  //   for (auto& property : array_element.second) {
  //       std::cout << property.first << " = " << property.second.get_value<std::string>() << std::endl;
  //   }
  // }
return;
}

void CalcMuIDIsoEff( float& _ID_eff, float& _ID_eff_up, float& _ID_eff_down,
		     float& _Iso_eff, float& _Iso_eff_up, float& _Iso_eff_down, 
		     const TH2F* _ID_hist, const TH2F* _Iso_hist, 
		     const TH1F* _ID_vtx, const TH1F* _Iso_vtx,
		     const MuonInfos _muonInfos, const int _nVtx ) {

  _ID_eff       = 1.;
  _ID_eff_up    = 1.;
  _ID_eff_down  = 1.;
  _Iso_eff      = 1.;
  _Iso_eff_up   = 1.;
  _Iso_eff_down = 1.;

  int nMu = int(_muonInfos.size());
  int nFound_ID  = 0;
  int nFound_Iso = 0;

  // Compute muon ID efficiency or scale factor
  for (int iMu = 0; iMu < nMu; iMu++) {
    float mu_pt  = std::min( _muonInfos.at(iMu).pt, 
			     _ID_hist->GetYaxis()->GetBinLowEdge( _ID_hist->GetNbinsY() ) +
			     _ID_hist->GetYaxis()->GetBinWidth(   _ID_hist->GetNbinsY() ) - 0.01 );
    float mu_eta = std::min( fabs(_muonInfos.at(iMu).eta),
			     _ID_hist->GetXaxis()->GetBinLowEdge( _ID_hist->GetNbinsX() ) +
			     _ID_hist->GetXaxis()->GetBinWidth(   _ID_hist->GetNbinsX() ) - 0.01 );
    mu_pt = std::max( mu_pt*1.0, _ID_hist->GetYaxis()->GetBinLowEdge(1) + 0.01 );
    bool found_mu = false;

    for (int iPt = 1; iPt <= _ID_hist->GetNbinsY(); iPt++) {
      if ( found_mu ) continue;
      if ( mu_pt < _ID_hist->GetYaxis()->GetBinLowEdge(iPt) ) continue;
      if ( mu_pt > _ID_hist->GetYaxis()->GetBinLowEdge(iPt) + _ID_hist->GetYaxis()->GetBinWidth(iPt) ) continue;
      
      for (int iEta = 1; iEta <= _ID_hist->GetNbinsX(); iEta++) {
	if ( found_mu ) continue;
	if ( mu_eta < _ID_hist->GetXaxis()->GetBinLowEdge(iEta) ) continue;
	if ( mu_eta > _ID_hist->GetXaxis()->GetBinLowEdge(iEta) + _ID_hist->GetXaxis()->GetBinWidth(iEta) ) continue;

	found_mu = true;
	nFound_ID += 1;

	_ID_eff      *= _ID_hist->GetBinContent(iEta, iPt);
	_ID_eff_up   *= _ID_hist->GetBinContent(iEta, iPt) + _ID_hist->GetBinError(iEta, iPt);
	_ID_eff_down *= _ID_hist->GetBinContent(iEta, iPt) - _ID_hist->GetBinError(iEta, iPt);

      } // End loop: for (int iEta = 1; iEta <= _ID_hist->GetNbinsX(); iEta++)
    } // End loop: for (int iPt = 1; iPt <= _ID_hist->GetNbinsY(); iPt++)
  } // End loop: for (int iMu = 0; iMu < nMu; iMu++)


  // Compute muon isolation efficiency or scale factor
  for (int iMu = 0; iMu < nMu; iMu++) {
    float mu_pt  = std::min( _muonInfos.at(iMu).pt, 
			     _Iso_hist->GetYaxis()->GetBinLowEdge( _Iso_hist->GetNbinsY() ) +
			     _Iso_hist->GetYaxis()->GetBinWidth(   _Iso_hist->GetNbinsY() ) - 0.01 );
    float mu_eta = std::min( fabs(_muonInfos.at(iMu).eta),
			     _Iso_hist->GetXaxis()->GetBinLowEdge( _Iso_hist->GetNbinsX() ) +
			     _Iso_hist->GetXaxis()->GetBinWidth(   _Iso_hist->GetNbinsX() ) - 0.01 );
    mu_pt = std::max( mu_pt*1.0, _Iso_hist->GetYaxis()->GetBinLowEdge(1) + 0.01 );
    bool found_mu = false;

    for (int iPt = 1; iPt <= _Iso_hist->GetNbinsY(); iPt++) {
      if ( found_mu ) continue;
      if ( mu_pt < _Iso_hist->GetYaxis()->GetBinLowEdge(iPt) ) continue;
      if ( mu_pt > _Iso_hist->GetYaxis()->GetBinLowEdge(iPt) + _Iso_hist->GetYaxis()->GetBinWidth(iPt) ) continue;
      
      for (int iEta = 1; iEta <= _Iso_hist->GetNbinsX(); iEta++) {
	if ( found_mu ) continue;
	if ( mu_eta < _Iso_hist->GetXaxis()->GetBinLowEdge(iEta) ) continue;
	if ( mu_eta > _Iso_hist->GetXaxis()->GetBinLowEdge(iEta) + _Iso_hist->GetXaxis()->GetBinWidth(iEta) ) continue;

	found_mu = true;
	nFound_Iso += 1;

	_Iso_eff      *= _Iso_hist->GetBinContent(iEta, iPt);
	_Iso_eff_up   *= _Iso_hist->GetBinContent(iEta, iPt) + _Iso_hist->GetBinError(iEta, iPt);
	_Iso_eff_down *= _Iso_hist->GetBinContent(iEta, iPt) - _Iso_hist->GetBinError(iEta, iPt);

      } // End loop: for (int iEta = 1; iEta <= _Iso_hist->GetNbinsX(); iEta++)
    } // End loop: for (int iPt = 1; iPt <= _Iso_hist->GetNbinsY(); iPt++)
  } // End loop: for (int iMu = 0; iMu < nMu; iMu++)


  assert( nFound_ID == nMu && nFound_Iso == nMu );

  // Add pileup dependence
  for (int iPU = 1; iPU <= _ID_vtx->GetNbinsX(); iPU++) {
    if ( _nVtx < _ID_vtx->GetXaxis()->GetBinLowEdge(iPU) ) continue;
    if ( _nVtx > _ID_vtx->GetXaxis()->GetBinLowEdge(iPU) + _ID_vtx->GetXaxis()->GetBinWidth(iPU) ) continue;
    _ID_eff      *= pow(_ID_vtx->GetBinContent(iPU), nMu);
    _ID_eff_up   *= pow(_ID_vtx->GetBinContent(iPU), nMu);
    _ID_eff_down *= pow(_ID_vtx->GetBinContent(iPU), nMu);
    break;
  }

  for (int iPU = 1; iPU <= _Iso_vtx->GetNbinsX(); iPU++) {
    if ( _nVtx < _Iso_vtx->GetXaxis()->GetBinLowEdge(iPU) ) continue;
    if ( _nVtx > _Iso_vtx->GetXaxis()->GetBinLowEdge(iPU) + _Iso_vtx->GetXaxis()->GetBinWidth(iPU) ) continue;
    _Iso_eff      *= pow(_Iso_vtx->GetBinContent(iPU), nMu);
    _Iso_eff_up   *= pow(_Iso_vtx->GetBinContent(iPU), nMu);
    _Iso_eff_down *= pow(_Iso_vtx->GetBinContent(iPU), nMu);
    break;
  }

}

