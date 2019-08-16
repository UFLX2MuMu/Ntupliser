
#include "Ntupliser/DiMuons/interface/MuonHelper.h"
#include "Ntupliser/DiMuons/interface/GenMuonInfo.h"

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
		    const RoccoR _Roch_calib, const bool _doSys_Roch, const GenMuonInfos _genMuonInfos,
		    LepMVAVars & _lepVars_mu, std::shared_ptr<TMVA::Reader> & _lepMVA_mu,
		    const double _rho, const edm::Handle<pat::JetCollection>& jets,
		    const edm::Handle<pat::PackedCandidateCollection> pfCands,
		    EffectiveAreas muEffArea ) {

  // std::cout << "\nInside FillMuonInfos" << std::endl;

  double const MASS_MUON = 0.105658367; // GeV/c^2

  _muonInfos.clear();
  int nMuons = muonsSelected.size();


  // Testing Kinematic fit : Needs to be integrated in the Ntupliser data format - PB 10.09.2018

  TLorentzVector mu1_tlv;
  TLorentzVector mu2_tlv;

  Double_t mu1_ptErr_kinfit; mu1_ptErr_kinfit = 0.;
  Double_t mu2_ptErr_kinfit; mu2_ptErr_kinfit = 0.;
  
  RefCountedKinematicVertex dimu_vertex;
  
  // TODO: Handle higher order effecrs when the events has more than 2 selected muons. For the moment the kinematic fit is run on all possible muons in the collections selectedMuons. 
  // The result is store for the first fit and for the first two muons. For ggH and VBF this should be enough, but ttH or VH might need to cover higher order effects.
  // Ideally we should run it only for opposite signed couple of muons and store the pt_kinfit as a vector/array per each muons with an index to the pair related to it.
  if( nMuons > 1){
    //Instatiate KinematicVertexFitter object
    KinematicVertexFitter kinfit;
    //Fit and retrieve the tree
    RefCountedKinematicTree kinfittree = kinfit.Fit(muonsSelected); 
 
    if(kinfittree->isEmpty() == 1 || kinfittree->isConsistent() == 0)
       std::cout << "Kinematic Fit unsuccesfull" << std::endl;
    else{
      //accessing the tree components 
      kinfittree->movePointerToTheTop();
      //We are now at the top of the decay tree getting the dimuon reconstructed KinematicPartlcle
      RefCountedKinematicParticle dimu_kinfit = kinfittree->currentParticle();
      
      //getting the dimuon decay vertex
      //RefCountedKinematicVertex 
      dimu_vertex = kinfittree->currentDecayVertex();
   
      //Now navigating down the tree 
      bool child = kinfittree->movePointerToTheFirstChild();
      //TLorentzVector mu1_tlv;
    
      if (child){
        RefCountedKinematicParticle mu1_kinfit = kinfittree->currentParticle();
        AlgebraicVector7 mu1_kinfit_par = mu1_kinfit->currentState().kinematicParameters().vector();
        AlgebraicSymMatrix77 mu1_kinfit_cov = mu1_kinfit->currentState().kinematicParametersError().matrix();
        mu1_ptErr_kinfit = sqrt(mu1_kinfit_cov(3,3) + mu1_kinfit_cov(4,4)); 
        mu1_tlv.SetXYZM(mu1_kinfit_par.At(3),mu1_kinfit_par.At(4),mu1_kinfit_par.At(5), mu1_kinfit_par.At(6));
//        std::cout << "Mu1 chi2 = " << mu1_kinfit->chiSquared() << std::endl;
//        std::cout << "Mu1 ndf = " << mu1_kinfit->degreesOfFreedom() << std::endl;
//        std::cout << "Covariant matrix" << std::endl;
//        std::cout << mu1_kinfit_cov(3,3) << std::endl;
//        std::cout << " - " << mu1_kinfit_cov(4,4) << std::endl;
//        std::cout << " -      -    " << mu1_kinfit_cov(5,5) << std::endl;
//        std::cout << "Muon pt uncertainty = " << sqrt(mu1_kinfit_cov(3,3) + mu1_kinfit_cov(4,4)) << std::endl;
      }
     
    
      //Now navigating down the tree 
      bool nextchild = kinfittree->movePointerToTheNextChild();
   
      if (nextchild){
        RefCountedKinematicParticle mu2_kinfit = kinfittree->currentParticle();
        AlgebraicVector7 mu2_kinfit_par = mu2_kinfit->currentState().kinematicParameters().vector();
        AlgebraicSymMatrix77 mu2_kinfit_cov = mu2_kinfit->currentState().kinematicParametersError().matrix(); 
        mu2_ptErr_kinfit = sqrt(mu2_kinfit_cov(3,3) + mu2_kinfit_cov(4,4)); 
        mu2_tlv.SetXYZM(mu2_kinfit_par.At(3),mu2_kinfit_par.At(4),mu2_kinfit_par.At(5),mu2_kinfit_par.At(6));
      }

    } // end else - isEmpty()

    //std::cout << "Kin Fitted muons 1 :" << mu1_tlv.Pt() << "  -- Pat muons : " << muonsSelected.at(0).pt() << std::endl;
    //std::cout << "Kin Fitted muons 2 :" << mu2_tlv.Pt() << "  -- Pat muons : " << muonsSelected.at(1).pt() << std::endl;
    //std::cout << "Kin fit mass from kinfit: " << higgs_tlv.M()  << " - Kin fit mass from tlv: " << (mu1_tlv+mu2_tlv).M()<< std::endl; 
 
  } //if nMuons>1



  for (int i = 0; i < nMuons; i++) {

    pat::Muon muon = muonsSelected.at(i);
    MuonInfo _muonInfo;

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
      _muonInfo.relIso = MuonCalcRelIsoPF ( muon, _muon_iso_dR, _rho, muEffArea, "DeltaBeta" );
    else
      _muonInfo.relIso = MuonCalcRelIsoTrk( muon, _muon_iso_dR );

    // Uses effective area calculation
    _muonInfo.relIsoEA03     = MuonCalcRelIsoPF ( muon, 0.3, _rho, muEffArea, "EffArea" );
    _muonInfo.relIsoEA04     = MuonCalcRelIsoPF ( muon, 0.4, _rho, muEffArea, "EffArea" );
    _muonInfo.miniIso        = MuonCalcMiniIso  ( muon, pfCands, _rho, muEffArea, false );
    _muonInfo.miniIsoCharged = MuonCalcMiniIso  ( muon, pfCands, _rho, muEffArea, true );
    
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
	for (unsigned int i = 0; i < _genMuonInfos.size(); i++) {
	  const GenMuonInfo GEN_mu = _genMuonInfos.at(i);
	  if ( GEN_mu.status != 1 ) continue; // TODO: understand status
	  if ( GEN_mu.charge != _muonInfo.charge ) continue;
	
	  GEN_vec.SetPtEtaPhiM( GEN_mu.pt, GEN_mu.eta, GEN_mu.phi, GEN_mu.mass );
	  if (GEN_vec.DeltaR(mu_vec_Roch) > 0.005) continue;
	  if (iMatch > 0) {
	    std::cout << "\nBizzare situation: two muons match!" << std::endl;
	    std::cout << "RECO pT = " << mu_vec_Roch.Pt() << ", eta = " << mu_vec_Roch.Eta() 
		      << ", phi = " << mu_vec_Roch.Phi() << ", charge = " << _muonInfo.charge << std::endl;
	    std::cout << "GEN1 pT = " << _genMuonInfos.at(i).pt << ", eta = " << _genMuonInfos.at(i).eta 
		      << ", phi = " << _genMuonInfos.at(i).phi << std::endl;
	    std::cout << "GEN2 pT = " << GEN_vec.Pt()<< ", eta = " << GEN_vec.Eta() << ", phi = " << GEN_vec.Phi() << std::endl;
	  }
	  
	  iMatch = i;
	  _muonInfo.GEN_pt = GEN_vec.Pt();
	  _muonInfo.GEN_dR = GEN_vec.DeltaR(mu_vec_Roch);
          _muonInfo.GEN_idx = iMatch;
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

    // DEBUG: Rochester pt
    // std::cout << "Rochester pt and uncert = " << pt_Roch << " +- " << ptErr_Roch << std::endl;
     
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
    _muonInfo.d0_BS  = muon.innerTrack()->dxy( beamSpotHandle->position() );
    _muonInfo.dz_BS  = muon.innerTrack()->dz ( beamSpotHandle->position() );
    _muonInfo.d0_PV  = track.dxy( primaryVertex.position() );
    _muonInfo.dz_PV  = track.dz ( primaryVertex.position() );
    _muonInfo.IP_3D  = muon.dB(pat::Muon::PV3D);
    _muonInfo.SIP_3D = fabs( muon.dB(pat::Muon::PV3D) / muon.edB(pat::Muon::PV3D) );
    
    _muonInfo.d0_PV = track.dxy( primaryVertex.position() );
    _muonInfo.dz_PV = track.dz ( primaryVertex.position() );
 

    // Kinematic Fit corrections and vertex
    if( dimu_vertex != NULL ){
      GlobalVector IPVec(dimu_vertex->position().x()-primaryVertex.position().x(),dimu_vertex->position().y()-primaryVertex.position().y(),dimu_vertex->position().z()-primaryVertex.position().z());
      _muonInfo.d0_PV_kinfit = sqrt( pow(dimu_vertex->position().x()-primaryVertex.position().x(),2) + pow(dimu_vertex->position().y()-primaryVertex.position().y(),2) );
      _muonInfo.dz_PV_kinfit = fabs(dimu_vertex->position().z()-primaryVertex.position().z());
      _muonInfo.chi2_kinfit = dimu_vertex->chiSquared();
      _muonInfo.ndf_kinfit =  dimu_vertex->degreesOfFreedom(); 
      if(i==0){ //first muon
        GlobalVector direction(mu1_tlv.Px(),mu1_tlv.Py(),mu1_tlv.Pz()); 
        float prod = IPVec.dot(direction);
        int sign = (prod>=0) ? 1. : -1.;
        _muonInfo.d0_PV_kinfit *= sign;
        _muonInfo.dz_PV_kinfit *= sign;
        _muonInfo.pt_kinfit  = mu1_tlv.Pt();
        _muonInfo.phi_kinfit = mu1_tlv.Phi();
        _muonInfo.eta_kinfit = mu1_tlv.Eta();
        _muonInfo.ptErr_kinfit = mu1_ptErr_kinfit;
      }
      if(i==1){ //second muon
        GlobalVector direction(mu2_tlv.Px(),mu2_tlv.Py(),mu2_tlv.Pz()); 
        float prod = IPVec.dot(direction);
        int sign = (prod>=0) ? 1. : -1.;
        _muonInfo.d0_PV_kinfit *= sign;
        _muonInfo.dz_PV_kinfit *= sign;
        _muonInfo.pt_kinfit  = mu2_tlv.Pt();
        _muonInfo.phi_kinfit = mu2_tlv.Phi();
        _muonInfo.eta_kinfit = mu2_tlv.Eta();
        _muonInfo.ptErr_kinfit = mu2_ptErr_kinfit;
     }
    } 
    else{ // if the kinfit was not succesful for this muon use the muonBestTrack 
        _muonInfo.pt_kinfit = muon.muonBestTrack()->pt();
        _muonInfo.ptErr_kinfit = muon.muonBestTrack()->ptError();
        _muonInfo.phi_kinfit = muon.muonBestTrack()->phi();
        _muonInfo.eta_kinfit = muon.muonBestTrack()->eta(); 
    }

    //DEBUG: Checking dO
    //if(dimu_vertex != NULL )
    //  std::cout << "d0_PV track = " << track.dxy( primaryVertex.position() ) << ", d0_PV muons " << muon.muonBestTrack()->dxy(primaryVertex.position()) << ", kinfit d0_PV = " << sqrt( pow(dimu_vertex->position().x()-primaryVertex.position().x(),2) + pow(dimu_vertex->position().y()-primaryVertex.position().y(),2) ) << std::endl;

    // Standard isolation
    _muonInfo.trackIsoSumPt     = muon.isolationR03().sumPt;
    _muonInfo.trackIsoSumPtCorr = muon.isolationR03().sumPt; // no correction with only 1 muon (??? - AWB 08.11.16)
    
    // Compatibility with outer muon detector segments
    _muonInfo.segCompat = muon::segmentCompatibility( muon );

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

    // Fill lepMVA input variables
    // https://github.com/wverbeke/ewkino/blob/tZq/src/skimmer.cc#L128
    FillLepMVAVars( _lepVars_mu, _muonInfo, jets, primaryVertex );
    // Evaluate the lepMVA
    _muonInfo.lepMVA = _lepMVA_mu->EvaluateMVA("BDTG method");
    // Fill the remaining lepMVA input variables
    _muonInfo.jet_trkMult = _lepVars_mu.trackMultClosestJet;
    _muonInfo.jet_ptRel   = _lepVars_mu.ptRel;
    _muonInfo.jet_ptRatio = _lepVars_mu.ptRatio;
    _muonInfo.jet_deepCSV = _lepVars_mu.deepCsvClosestJet;

    // std::cout << "LepMVA input variables for muon:" << std::endl;
    // _lepVars_mu.print();
    // std::cout << "LepMVA output value = " << _muonInfo.lepMVA << std::endl;

    _muonInfos.push_back( _muonInfo );
  } // End loop: for (unsigned int i = 0; i < nMuons; i++)

} // End function: void FillMuonInfos
    

pat::MuonCollection SelectMuons( const edm::Handle<pat::MuonCollection>& muons, 
				 const reco::Vertex primaryVertex, const std::string _muon_ID,
				 const double _muon_pT_min, const double _muon_eta_max, const double _muon_trig_dR, 
				 const bool _muon_use_pfIso, const double _muon_iso_dR, const double _muon_iso_max,
				 const double _rho, EffectiveAreas muEffArea ) {
  
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
      if ( MuonCalcRelIsoPF ( (*muon), _muon_iso_dR, _rho, muEffArea , "DeltaBeta" ) > _muon_iso_max ) continue;
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

double MuonCalcRelIsoPF( const pat::Muon muon, const double _muon_iso_dR, const double rho,
			 EffectiveAreas muEffArea, const std::string type ) {
  // Following https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_Isolation and
  // https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/src/LeptonAnalyzerIso.cc#L23
  assert(_muon_iso_dR == 0.3 || _muon_iso_dR == 0.4);
  assert(type == "DeltaBeta" || type == "EffArea");

  double iso = -999;
  float  PU  = -999;

  if ( _muon_iso_dR == 0.4 ) {
    if      (type == "DeltaBeta") PU = 0.5 * muon.pfIsolationR04().sumPUPt;
    else if (type == "EffArea")   PU = rho * muEffArea.getEffectiveArea( muon.eta() ) * pow(0.4/0.3, 2);
    iso  = muon.pfIsolationR04().sumChargedHadronPt;
    iso += std::fmax( 0., muon.pfIsolationR04().sumNeutralHadronEt + muon.pfIsolationR04().sumPhotonEt - PU );
  } 
  else if ( _muon_iso_dR == 0.3 ) {
    if      (type == "DeltaBeta") PU = 0.5 * muon.pfIsolationR03().sumPUPt;
    else if (type == "EffArea")   PU = rho * muEffArea.getEffectiveArea( muon.eta() );
    PU   = 0.5 * muon.pfIsolationR03().sumPUPt;
    iso  = muon.pfIsolationR03().sumChargedHadronPt;
    iso += std::fmax( 0., muon.pfIsolationR03().sumNeutralHadronEt + muon.pfIsolationR03().sumPhotonEt - PU );
  }

  return (iso / muon.pt() );
} // End function: MuonCalcRelIsoPF()

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

double MuonCalcMiniIso( const pat::Muon muon, const edm::Handle<pat::PackedCandidateCollection> pfCands,
			const double rho, EffectiveAreas muEffArea, const bool charged ) {
  // Following https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/src/LeptonAnalyzerIso.cc#L79
  //       and https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/src/LeptonAnalyzerIso.cc#L36

  // Variable cone size based on muon pT: from 0.2 at low pT (<= 5 GeV) up to 0.05 (>= 200 GeV)
  double max_pt   = 10.0 / 0.05;  // kT scale (GeV) / dR_min
  double min_pt   = 10.0 / 0.20;  // kT scale (GeV) / dR_max
  double coneSize = 10.0 / std::fmax(std::min(muon.pt(), max_pt), min_pt);

  double dR_nh(0.01), dR_ch(0.0001), dR_ph(0.01), dR_pu(0.01);  // Candidates not considered if they're too close to the muon
  double iso_nh(0.0), iso_ch(0.0), iso_ph(0.0), iso_pu(0.0);    // Separate isolation quantities by PF candidate type
  double minPt = 0.5;

  for (const pat::PackedCandidate & pfc : *pfCands) {

    if (fabs(pfc.pdgId()) < 7) continue;  // What does this do? - AWB 15.10.2018

    double dR = deltaR(pfc, muon);
    if (dR > coneSize) continue;

    if (pfc.charge() == 0) { // Neutral
      if (pfc.pt() > minPt) {
	if      (fabs(pfc.pdgId()) ==  22 and dR > dR_ph) iso_ph += pfc.pt(); // Photons
	else if (fabs(pfc.pdgId()) == 130 and dR > dR_nh) iso_nh += pfc.pt(); // Neutral hadrons
      }
    } else if (pfc.fromPV() > 1) {
      if (fabs(pfc.pdgId()) == 211 and dR > dR_ch) iso_ch += pfc.pt(); // Charged from PV
    } else if (pfc.pt()    > minPt and dR > dR_pu) iso_pu += pfc.pt(); // Charged from PU
  }

  double puCorr = rho * muEffArea.getEffectiveArea( muon.eta() );

  double iso  = iso_ch;
  if (!charged) iso += std::fmax(0., iso_ph + iso_nh - puCorr * pow(coneSize / 0.3, 2));

  return ( iso / muon.pt() );
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
  // std::cout << "phi1 = " << phi1 << ", phi2 = " << phi2 << ", dPhi = " << abs_dPhi*sign_dPhi << " (sign = " << sign_dPhi << ")" << std::endl;
  return abs_dPhi*sign_dPhi;
}


// Function toi calculate muon ID and Isolation scale factor from json file. - PB 30.07.2018
// Could be used also to calculate the efficiency from json file but it would require some small adaptation. For the moment we need only SF.
void CalcMuIDIsoEff(float& _ID_sf, float& _ID_sf_up, float& _ID_sf_down, std::string _id_wp_num, std::string _id_wp_den,
         float& _Iso_sf, float& _Iso_sf_up, float& _Iso_sf_down, std::string _iso_wp_num, std::string _iso_wp_den,
         const boost::property_tree::ptree json_iso, const boost::property_tree::ptree json_id, 
         const MuonInfos _muonInfos) {

  // needed to change the separator http://www.boost.org/doc/libs/1_47_0/doc/html/boost_propertytree/accessing.html
  typedef boost::property_tree::ptree::path_type path;
  //eta bins for SF
  std::vector<float> absetabins{0.00, 0.90, 1.20, 2.10, 2.40};
  //pt bins for SF
  std::vector<float> ptbins{20.00, 25.00, 30.00, 40.00, 50.00, 60.00, 120.00};

  _ID_sf       = 1.;
  _ID_sf_up    = 1.;
  _ID_sf_down  = 1.;
  _Iso_sf      = 1.;
  _Iso_sf_up   = 1.;
  _Iso_sf_down = 1.;

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
      if ( abs(_muonInfos.at(iMu).eta) >= absetabins.at(_abseta+1) ) continue;
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
      if ( _muonInfos.at(iMu).pt >= ptbins.at(_pt+1) ) continue; 
      _min_pt << std::fixed << std::setprecision(2) << ptbins.at(_pt);
      _max_pt << std::fixed << std::setprecision(2) << ptbins.at(_pt+1);
    } // loop pt bin 
   if(_min_pt.str().compare(_max_pt.str()) == 0 ){ // if compare is ==0 the two strings are equal. String are equal when muon_pt is over or under the min or max bin: in that case I set the SF to 1.0.
      //std::cout << "WARNING: Setting all SF and uncertainties to 1.0. for this muon." << std::endl;
      _min_pt.str(""); _min_eta.str(""); _max_pt.str(""); _max_eta.str("");
      continue;
    }
    // ID
    _value_string = "NUM_"+_id_wp_num+"_DEN_"+_id_wp_den+"/abseta_pt/abseta:["+_min_eta.str()+","+_max_eta.str()+"]/pt:["+_min_pt.str()+","+_max_pt.str()+"]/value";
    _ID_sf = json_id.get<float>(path(_value_string.c_str(),'/'));
    _err_string = "NUM_"+_id_wp_num+"_DEN_"+_id_wp_den+"/abseta_pt/abseta:["+_min_eta.str()+","+_max_eta.str()+"]/pt:["+_min_pt.str()+","+_max_pt.str()+"]/error";
    _ID_sf_up = _ID_sf + json_id.get<float>(path(_err_string.c_str(),'/'));
    _ID_sf_down = _ID_sf - json_id.get<float>(path(_err_string.c_str(),'/'));
    // Iso
    _value_string = "NUM_"+_iso_wp_num+"_DEN_"+_iso_wp_den+"/abseta_pt/abseta:["+_min_eta.str()+","+_max_eta.str()+"]/pt:["+_min_pt.str()+","+_max_pt.str()+"]/value";
    _Iso_sf = json_iso.get<float>(path(_value_string.c_str(),'/'));
//    std::cout << "Mu eta = " << abs(_muonInfos.at(iMu).eta)  << std::endl;
//    std::cout << "Mu pt = " <<  _muonInfos.at(iMu).pt << std::endl;
//    std::cout << "Iso_eff = " << _Iso_sf << std::endl;
    _err_string = "NUM_"+_iso_wp_num+"_DEN_"+_iso_wp_den+"/abseta_pt/abseta:["+_min_eta.str()+","+_max_eta.str()+"]/pt:["+_min_pt.str()+","+_max_pt.str()+"]/error";
    _Iso_sf_up = _Iso_sf + json_iso.get<float>(path(_err_string.c_str(),'/'));
    _Iso_sf_down = _Iso_sf - json_iso.get<float>(path(_err_string.c_str(),'/'));
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
    mu_pt = std::fmax( mu_pt*1.0, _ID_hist->GetYaxis()->GetBinLowEdge(1) + 0.01 );
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
    mu_pt = std::fmax( mu_pt*1.0, _Iso_hist->GetYaxis()->GetBinLowEdge(1) + 0.01 );
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

