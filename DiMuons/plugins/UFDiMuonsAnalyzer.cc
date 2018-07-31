
#include "Ntupliser/DiMuons/plugins/UFDiMuonsAnalyzer.h"

// Constructor
UFDiMuonsAnalyzer::UFDiMuonsAnalyzer(const edm::ParameterSet& iConfig):
  _numEvents(0)
{
  // Initialize the weighted count and the trees.
  // Use the file service to make the trees so that it knows to save them.
  _sumEventWeights = 0;
  _outTree = fs->make<TTree>("tree", "myTree");
  _outTreeMetadata = fs->make<TTree>("metadata", "Metadata Tree");

  // Get the collections designated from the python config file and load them into the tokens

  // Boolean switches from config file
  _isVerbose	 = iConfig.getUntrackedParameter<bool>("isVerbose", false);
  _isMonteCarlo	 = iConfig.getParameter         <bool>("isMonteCarlo");
  _doSys         = iConfig.getParameter         <bool>("doSys");
  _slimOut       = iConfig.getParameter         <bool>("slimOut");
  
  // Event selection from config file
  _skim_nMuons = iConfig.getParameter<int>  ("skim_nMuons");
  _skim_trig   = iConfig.getParameter<bool> ("skim_trig");

  // Trigger info
  _processName  = iConfig.getParameter            <std::string> ("processName");
  _trigNames    = iConfig.getParameter<std::vector<std::string>>("trigNames");

  _trigResultsToken = consumes<edm::TriggerResults>                    (iConfig.getParameter<edm::InputTag>("trigResults"));
  _trigObjsToken    = consumes<pat::TriggerObjectStandAloneCollection> (iConfig.getParameter<edm::InputTag>("trigObjs"));
  // _trigObjsToken    = consumes<pat::TriggerObjectStandAloneCollection> (edm::InputTag("slimmedPatTrigger","","PAT"));

  // Event flags
  _evtFlagsToken = consumes<edm::TriggerResults>( iConfig.getParameter<edm::InputTag>("evtFlags") );

  // Underlying event
  _beamSpotToken      = consumes<reco::BeamSpot>        (iConfig.getParameter<edm::InputTag>("beamSpotTag"));
  _primaryVertexToken = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("primaryVertexTag"));
  _PupInfoToken       = consumes< std::vector<PileupSummaryInfo> >           (edm::InputTag ("slimmedAddPileupInfo"));

  // Muons
  _muonCollToken = consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonColl"));

  // Electrons
  _eleCollToken     = consumes<edm::View<pat::Electron>> (iConfig.getParameter<edm::InputTag>("eleColl"));
  _eleIdVetoToken   = consumes< edm::ValueMap<bool> >    (iConfig.getParameter<edm::InputTag>("eleIdVeto"));
  _eleIdLooseToken  = consumes< edm::ValueMap<bool> >    (iConfig.getParameter<edm::InputTag>("eleIdLoose"));
  _eleIdMediumToken = consumes< edm::ValueMap<bool> >    (iConfig.getParameter<edm::InputTag>("eleIdMedium"));
  _eleIdTightToken  = consumes< edm::ValueMap<bool> >    (iConfig.getParameter<edm::InputTag>("eleIdTight"));

  // // Taus
  // _tauCollToken = consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("tauColl"));
  // _tauIDNames   = iConfig.getParameter<std::vector<std::string> >("tauIDNames");

   // Jets / MET
  _jetsToken = consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jetsTag"));
  _metToken  = consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("metTag"));  // Correct(ed) MET? - AWB 08.11.16
  _rhoToken  = consumes<double>( iConfig.getParameter<edm::InputTag>("rhoTag"));
  _jetType   = iConfig.getParameter<std::string>("jetType");
  _btagName  = iConfig.getParameter<std::string>("btagName");

  // GEN objects
  _genJetsToken           = consumes<reco::GenJetCollection>          (iConfig.getParameter<edm::InputTag>("genJetsTag"));
  _prunedGenParticleToken = consumes<reco::GenParticleCollection>     (iConfig.getParameter<edm::InputTag>("prunedGenParticleTag"));
  _packedGenParticleToken = consumes<pat::PackedGenParticleCollection>(iConfig.getParameter<edm::InputTag>("packedGenParticleTag"));
  _genEvtInfoToken        = consumes<GenEventInfoProduct>                                  (edm::InputTag ("generator"));

  // LHE weights and info for MC
  _LHE_token = consumes<LHEEventProduct>   (edm::InputTag("externalLHEProducer"));
  
  // Object selection from config file
  _vertex_ndof_min = iConfig.getParameter<double> ("vertex_ndof_min");
  _vertex_rho_max  = iConfig.getParameter<double> ("vertex_rho_max");
  _vertex_z_max    = iConfig.getParameter<double> ("vertex_z_max");

  _muon_ID        = iConfig.getParameter<std::string> ("muon_ID");
  _muon_pT_min    = iConfig.getParameter<double>      ("muon_pT_min");
  _muon_eta_max   = iConfig.getParameter<double>      ("muon_eta_max");
  _muon_trig_dR   = iConfig.getParameter<double>      ("muon_trig_dR");
  _muon_use_pfIso = iConfig.getParameter<bool>        ("muon_use_pfIso");
  _muon_iso_dR    = iConfig.getParameter<double>      ("muon_iso_dR");
  _muon_iso_max   = iConfig.getParameter<double>      ("muon_iso_max");
  // Muon scale factors working points 
  _muon_id_wp_num     = iConfig.getParameter<std::string>  ("muon_id_sf_wp_num");
  _muon_id_wp_den     = iConfig.getParameter<std::string>  ("muon_id_sf_wp_den");
  _muon_iso_wp_num    = iConfig.getParameter<std::string>  ("muon_iso_sf_wp_num");
  _muon_iso_wp_den    = iConfig.getParameter<std::string>  ("muon_iso_sf_wp_den");

  _ele_ID      = iConfig.getParameter<std::string> ("ele_ID");
  _ele_pT_min  = iConfig.getParameter<double>      ("ele_pT_min");
  _ele_eta_max = iConfig.getParameter<double>      ("ele_eta_max");

  // _tau_pT_min  = iConfig.getParameter<double>       ("tau_pT_min");
  // _tau_eta_max = iConfig.getParameter<double>       ("tau_eta_max");

  _jet_ID      = iConfig.getParameter<std::string> ("jet_ID");
  _jet_pT_min  = iConfig.getParameter<double>      ("jet_pT_min");
  _jet_eta_max = iConfig.getParameter<double>      ("jet_eta_max");

  if (_isMonteCarlo) _KaMu_calib = KalmanMuonCalibrator("MC_80X_13TeV");
  else               _KaMu_calib = KalmanMuonCalibrator("DATA_80X_13TeV");
  _doSys_KaMu  = iConfig.getParameter<bool>("doSys_KaMu");

  // Jigger path name for crab
  edm::FileInPath cfg_RochCor("Ntupliser/RochCor/data/RoccoR2017v0.txt");
  std::string path_RochCor = cfg_RochCor.fullPath().c_str();
  std::string file_RochCor = "/RoccoR2017v0.txt";
  std::string::size_type find_RochCor = path_RochCor.find(file_RochCor);
  if (find_RochCor != std::string::npos)
    path_RochCor.erase(find_RochCor, file_RochCor.length());

  std::cout << "Rochester correction files located in " << path_RochCor << std::endl;
  _Roch_calib.init(path_RochCor+file_RochCor);
  _doSys_Roch = iConfig.getParameter<bool>("doSys_Roch");

  if (_isMonteCarlo) {
    edm::FileInPath path_PU_wgt("Ntupliser/DiMuons/data/Pileup/"+iConfig.getParameter<std::string>("PU_wgt_file"));
    _PU_wgt_file      = new TFile(path_PU_wgt.fullPath().c_str());
    _PU_wgt_hist      = (TH1D*) _PU_wgt_file->Get("PU_wgt");
    _PU_wgt_hist_up   = (TH1D*) _PU_wgt_file->Get("PU_wgt_up");
    _PU_wgt_hist_down = (TH1D*) _PU_wgt_file->Get("PU_wgt_down");
  }

  edm::FileInPath path_IsoMu_eff_3("Ntupliser/DiMuons/data/MuonTrig/"+iConfig.getParameter<std::string>("Trig_eff_3_file"));
  _IsoMu_eff_3_file = new TFile(path_IsoMu_eff_3.fullPath().c_str());
  _IsoMu_eff_3_hist = (TH2F*) _IsoMu_eff_3_file->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/efficienciesDATA/abseta_pt_DATA");
  _IsoMu_SF_3_hist = (TH2F*) _IsoMu_eff_3_file->Get("IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");

  edm::FileInPath path_MuID_SF_3("Ntupliser/DiMuons/data/MuonIDIso/"+iConfig.getParameter<std::string>("MuID_eff_3_file"));
  //edm::FileInPath path_MuID_eff_4("Ntupliser/DiMuons/data/MuonIDIso/"+iConfig.getParameter<std::string>("MuID_eff_4_file"));

  std::ifstream _MuID_SF_3_json_file(path_MuID_SF_3.fullPath().c_str(), std::ifstream::binary);
  if (!_MuID_SF_3_json_file){
    std::cerr << "Error opening file " << path_MuID_SF_3.fullPath().c_str() << std::endl;
    return;
  }
  boost::property_tree::json_parser::read_json(_MuID_SF_3_json_file, _MuID_SF_3_json);

  //_MuID_eff_3_file = new TFile(path_MuID_eff_3.fullPath().c_str());
  //_MuID_eff_4_file = new TFile(path_MuID_eff_4.fullPath().c_str());
  //_MuID_eff_3_hist = (TH2F*) _MuID_eff_3_file->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_eta/efficienciesDATA/abseta_pt_DATA");
  //_MuID_eff_4_hist = (TH2F*) _MuID_eff_4_file->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_eta/efficienciesDATA/abseta_pt_DATA");
  //_MuID_SF_3_hist  = (TH2F*) _MuID_eff_3_file->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
  //_MuID_SF_4_hist  = (TH2F*) _MuID_eff_4_file->Get("MC_NUM_MediumID_DEN_genTracks_PAR_pt_eta/abseta_pt_ratio");
  //_MuID_eff_3_vtx  = (TH1F*) _MuID_eff_3_file->Get("MC_NUM_MediumID_DEN_genTracks_PAR_vtx/efficienciesDATA/histo_tag_nVertices_DATA_norm");
  //_MuID_eff_4_vtx  = (TH1F*) _MuID_eff_4_file->Get("MC_NUM_MediumID_DEN_genTracks_PAR_vtx/efficienciesDATA/histo_tag_nVertices_DATA_norm");
  //_MuID_SF_3_vtx   = (TH1F*) _MuID_eff_3_file->Get("MC_NUM_MediumID_DEN_genTracks_PAR_vtx/tag_nVertices_ratio_norm");
  //_MuID_SF_4_vtx   = (TH1F*) _MuID_eff_4_file->Get("MC_NUM_MediumID_DEN_genTracks_PAR_vtx/tag_nVertices_ratio_norm");

  edm::FileInPath path_MuIso_SF_3("Ntupliser/DiMuons/data/MuonIDIso/"+iConfig.getParameter<std::string>("MuIso_eff_3_file"));
//  edm::FileInPath path_MuIso_eff_4("Ntupliser/DiMuons/data/MuonIDIso/"+iConfig.getParameter<std::string>("MuIso_eff_4_file"));

  std::ifstream _MuIso_SF_3_json_file(path_MuIso_SF_3.fullPath().c_str(), std::ifstream::binary);
  if (!_MuIso_SF_3_json_file){
    std::cerr << "Error opening file " << path_MuIso_SF_3.fullPath().c_str() << std::endl;
    return;
  }
  boost::property_tree::json_parser::read_json(_MuIso_SF_3_json_file, _MuIso_SF_3_json);

  // _MuIso_eff_3_file = new TFile();//path_MuIso_eff_3.fullPath().c_str());  
  // _MuIso_eff_3_hist = (TH2F*) _MuIso_eff_3_file->Get("LooseISO_MediumID_pt_eta/efficienciesDATA/abseta_pt_DATA");
  // _MuIso_SF_3_hist  = (TH2F*) _MuIso_eff_3_file->Get("LooseISO_MediumID_pt_eta/abseta_pt_ratio");
  // _MuIso_eff_3_vtx  = (TH1F*) _MuIso_eff_3_file->Get("LooseISO_MediumID_vtx/efficienciesDATA/histo_tag_nVertices_DATA_norm");
  // _MuIso_SF_3_vtx   = (TH1F*) _MuIso_eff_3_file->Get("LooseISO_MediumID_vtx/tag_nVertices_ratio_norm");

} // End constructor: UFDiMuonsAnalyzer::UFDiMuonsAnalyzer

// Destructor
UFDiMuonsAnalyzer::~UFDiMuonsAnalyzer() {

  if (_isMonteCarlo)
    _PU_wgt_file->Close();

  _IsoMu_eff_3_file->Close();
//  _IsoMu_eff_4_file->Close();

}

// Called once per event
void UFDiMuonsAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // ------------------------
  // COUNT EVENTS AND WEIGHTS 
  // ------------------------
  _numEvents++;
  if (_isVerbose) std::cout << "\n\n A N A L Y Z I N G   E V E N T = " << _numEvents << std::endl << std::endl;
  
  if (!_isMonteCarlo)
    _sumEventWeights += 1;
  else {
    // The generated weight. Due to the interference of terms in QM in the
    // NLO simulations there are negative weights that need to be accounted for. 
    edm::Handle<GenEventInfoProduct> genEvtInfo;
    iEvent.getByToken(_genEvtInfoToken, genEvtInfo );
    _GEN_wgt = (genEvtInfo->weight() > 0) ? 1 : -1;  // Why don't we use the decimal weight? - AWB 08.11.16
    _sumEventWeights += _GEN_wgt;

    if (_isVerbose) std::cout << "\nAccessing LHEEventProduct info" << std::endl;
    edm::Handle<LHEEventProduct> LHE_handle;
    iEvent.getByToken(_LHE_token, LHE_handle);
    if (!LHE_handle.isValid()) {
      std::cout << "UFDiMuonsAnalyzer::analyze: Error in getting LHEEventProduct from Event!" << std::endl;
      return;
    }

    _LHE_HT = calcHtLHE( LHE_handle );

    // std::cout << "\n\n***  Printing LHEEventProduct variables  ***" << std::endl;
    // std::cout << "Original weight = " << LHE_handle->originalXWGTUP() <<  std::endl;
    // for (uint i = 0; i < LHE_handle->weights().size(); i++) {
    //   std::cout << "  * Weight " << i << ", " << LHE_handle->weights()[i].id << " = " << LHE_handle->weights()[i].wgt << std::endl;
    // }

  }

  // -------------------
  // HLT TRIGGER HANDLES
  // -------------------
  if (_isVerbose) std::cout << "\nAccessing HLT info" << std::endl;
  edm::Handle<edm::TriggerResults> trigResultsHandle;
  iEvent.getByToken(_trigResultsToken, trigResultsHandle);
  if (!trigResultsHandle.isValid()) {
    std::cout << "UFDiMuonsAnalyzer::analyze: Error in getting TriggerResults product from Event!" << std::endl;
    return;
  }

  edm::Handle<pat::TriggerObjectStandAloneCollection> trigObjsHandle;
  iEvent.getByToken(_trigObjsToken, trigObjsHandle);
  if (!trigObjsHandle.isValid()) {
    std::cout << "UFDiMuonsAnalyzer::analyze: Error in getting TriggerObjects product from Event!" << std::endl;
    return;
  }

  // If all the HLT paths are not fired, will discard the event immediately
  // Do we store trigger decisions somewhere? - AWB 12.11.16
  if ( _skim_trig && !isHltPassed(iEvent, iSetup, trigResultsHandle, _trigNames) ) {
    if (_isVerbose) std::cout << "None of the HLT paths fired -> discard the event\n";
    return;
  }

  // -----------
  // EVENT FLAGS
  // -----------  

  // "Flag_badMuons", "Flag_duplicateMuons", etc.
  // https://twiki.cern.ch/twiki/bin/view/CMSPublic/ReMiniAOD03Feb2017Notes
  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#Analysis_Recommendations_for_ana
  if (_isVerbose) std::cout << "\nAccessing PAT info" << std::endl;
  edm::Handle<edm::TriggerResults> evtFlagsHandle;
  iEvent.getByToken(_evtFlagsToken, evtFlagsHandle);
  if (!evtFlagsHandle.isValid()) {
    std::cout << "UFDiMuonsAnalyzer::analyze: Error in getting event flags from Event!" << std::endl;
    return;
  }

  FillEventFlags( iEvent, iSetup, evtFlagsHandle,
		  _Flag_all, _Flag_badMu, _Flag_dupMu, _Flag_halo, 
		  _Flag_PV, _Flag_HBHE, _Flag_HBHE_Iso, _Flag_ECAL_TP,
                   _Flag_BadChCand, _Flag_eeBadSc, _Flag_ecalBadCalib );

  // if ( !iEvent->HBHENoiseFilter()                    ) break;
  // if ( !iEvent->HBHENoiseIsoFilter()                 ) break;
  // if ( !iEvent->EcalDeadCellTriggerPrimitiveFilter() ) break;
  // if ( !iEvent->goodVertices()                       ) break;
  // if ( !iEvent->eeBadScFilter()                      ) break;
  // if ( !iEvent->globalTightHalo2016Filter()          ) break;



  // ----------------
  // RUN / EVENT INFO
  // ----------------
  if (_isVerbose) std::cout << "\nFilling EventInfo" << std::endl;
  FillEventInfo( _eventInfo, iEvent );

  // ----------------------------
  // BEAMSPOT / VERTICES / PILEUP
  // ----------------------------
  if (_isVerbose) std::cout << "\nFilling VertexInfo" << std::endl;
  edm::Handle<reco::BeamSpot> beamSpotHandle;
  iEvent.getByToken(_beamSpotToken, beamSpotHandle);

  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByToken(_primaryVertexToken, vertices);

  bool goodPV = false;
  reco::VertexCollection verticesSelected = SelectVertices( vertices, _vertex_ndof_min, _vertex_rho_max, 
							    _vertex_z_max, goodPV );
  if (verticesSelected.size() == 0) {
    std::cout << "BUGGY EVENT!  There are no good vertices!  Skipping ..." << std::endl;
    return;
  }
  if (!goodPV) {
    std::cout << "BUGGY EVENT!  Primary vertex fails quality cuts!  Skipping ..." << std::endl;
    return;
  }
  reco::Vertex primaryVertex = verticesSelected.at(0);
  
  bool _onlyPV = true;  // Only fill primary vertex
  FillVertexInfos( _vertexInfos, _nVertices, verticesSelected, _onlyPV );
  
  // -----
  // MUONS
  // -----
  if (_isVerbose) std::cout << "\nFilling MuonInfo" << std::endl;
  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByToken(_muonCollToken, muons);

  pat::MuonCollection muonsSelected = SelectMuons( muons, primaryVertex, _muon_ID,
						   _muon_pT_min, _muon_eta_max, _muon_trig_dR,
						   _muon_use_pfIso, _muon_iso_dR, _muon_iso_max );
  // Throw away event if there are too few muons
  if ( muonsSelected.size() < (unsigned int) _skim_nMuons )
    return;

  // Sort the selected muons by pT
  sort(muonsSelected.begin(), muonsSelected.end(), sortMuonsByPt);
  
  // Get GEN muons for Rochester corrections
  edm::Handle<reco::GenParticleCollection> genPartons;
  iEvent.getByToken(_prunedGenParticleToken, genPartons);

  FillMuonInfos( _muonInfos, muonsSelected, primaryVertex, verticesSelected.size(), beamSpotHandle, 
		 iEvent, iSetup, trigObjsHandle, trigResultsHandle, _trigNames,
		 _muon_trig_dR, _muon_use_pfIso, _muon_iso_dR, !(_isMonteCarlo), 
		 _KaMu_calib, _doSys_KaMu, _Roch_calib, _doSys_Roch, genPartons ); 
  _nMuons = _muonInfos.size();


// No need to calculate SF or to store efficiency for data. - PB 30.07.2018
//  CalcTrigEff( _IsoMu_eff_3, _IsoMu_eff_3_up, _IsoMu_eff_3_down, 
//	       _IsoMu_eff_3_hist, _muonInfos, false );
//  // CalcTrigEff( _IsoMu_eff_4, _IsoMu_eff_4_up, _IsoMu_eff_4_down, 
//	 //       _IsoMu_eff_4_hist, _muonInfos, false );
//  CalcTrigEff( _IsoMu_eff_bug, _IsoMu_eff_bug_up, _IsoMu_eff_bug_down, 
//	       _IsoMu_eff_3_hist, _muonInfos, true );
//  Calculate efficiency from json file. - PB
//  CalcMuIDIsoEff( _MuID_SF_3, _MuID_SF_3_up, _MuID_SF_3_down, _muon_id_wp_num, _muon_id_wp_den, 
//     _MuIso_SF_3, _MuIso_SF_3_up, _MuIso_SF_3_down, _muon_iso_wp_num, _muon_iso_wp_den,
//     _MuIso_SF_3_json, _MuID_SF_3_json, _muonInfos );
// Calculate efficiency from ROOT file (old way). Moved to json - PB 
  // CalcMuIDIsoEff( _MuID_eff_3, _MuID_eff_3_up, _MuID_eff_3_down,
		//   _MuIso_eff_3, _MuIso_eff_3_up, _MuIso_eff_3_down,
		//   _MuID_eff_3_hist, _MuIso_eff_3_hist,
		//   _MuID_eff_3_vtx, _MuIso_eff_3_vtx,
		//   _muonInfos, _nVertices);
  //CalcMuIDIsoEff( _MuID_eff_4, _MuID_eff_4_up, _MuID_eff_4_down,
		  // _MuIso_eff_4, _MuIso_eff_4_up, _MuIso_eff_4_down,
		  // _MuID_eff_4_hist, _MuIso_eff_4_hist,
		  // _MuID_eff_4_vtx, _MuIso_eff_4_vtx,
		  // _muonInfos, _nVertices);

  if (_isMonteCarlo) {

// Calculate trigger SF from ROOT file as old way as the json is not well formatted. - PB
    CalcTrigEff( _IsoMu_SF_3, _IsoMu_SF_3_up, _IsoMu_SF_3_down, 
		 _IsoMu_SF_3_hist, _muonInfos, false );
   //  CalcTrigEff( _IsoMu_SF_4, _IsoMu_SF_4_up, _IsoMu_SF_4_down, 
		 // _IsoMu_SF_4_hist, _muonInfos, false );
    CalcTrigEff( _IsoMu_SF_bug, _IsoMu_SF_bug_up, _IsoMu_SF_bug_down, 
		 _IsoMu_SF_3_hist, _muonInfos, true );
// Calculate scale factor using json file - PB
    CalcMuIDIsoEff( _MuID_SF_3, _MuID_SF_3_up, _MuID_SF_3_down, _muon_id_wp_num, _muon_id_wp_den, 
      _MuIso_SF_3, _MuIso_SF_3_up, _MuIso_SF_3_down, _muon_iso_wp_num, _muon_iso_wp_den,
      _MuIso_SF_3_json, _MuID_SF_3_json, _muonInfos );

// Calculate scale factor using ROOT file (old way) moved to json for 2017. = PB
    // CalcMuIDIsoEff( _MuID_SF_3, _MuID_SF_3_up, _MuID_SF_3_down,
		  //   _MuIso_SF_3, _MuIso_SF_3_up, _MuIso_SF_3_down,
		  //   _MuID_SF_3_hist, _MuIso_SF_3_hist,
		  //   _MuID_SF_3_vtx, _MuIso_SF_3_vtx,
		  //   _muonInfos, _nVertices);
    // CalcMuIDIsoEff( _MuID_SF_4, _MuID_SF_4_up, _MuID_SF_4_down,
		  //   _MuIso_SF_4, _MuIso_SF_4_up, _MuIso_SF_4_down,
		  //   _MuID_SF_4_hist, _MuIso_SF_4_hist,
		  //   _MuID_SF_4_vtx, _MuIso_SF_4_vtx,
		  //   _muonInfos, _nVertices);
  }


  // ------------
  // DIMUON PAIRS
  // ------------
  if (_isVerbose) std::cout << "\nFilling MuPairInfo" << std::endl;
  FillMuPairInfos( _muPairInfos, _muonInfos );
  _nMuPairs = _muPairInfos.size();

  // Throw away events with only low-mass pairs
  if ( _skim_nMuons == 2 && _nMuPairs == 1 )
    if ( _muPairInfos.at(0).mass < 10 )
      return;

  // Throw away events without a high-mass pair
//  bool hasHighMass = false;
//  for (int iPair = 0; iPair < _nMuPairs; iPair++) {
//    if ( _muPairInfos.at(iPair).mass > 100              || _muPairInfos.at(iPair).mass_PF > 100          || 
//	 _muPairInfos.at(iPair).mass_trk > 100          || _muPairInfos.at(iPair).mass_KaMu > 100        || 
//	 _muPairInfos.at(iPair).mass_KaMu_clos_up > 100 || _muPairInfos.at(iPair).mass_KaMu_sys_up > 100 ||
//	 _muPairInfos.at(iPair).mass_Roch > 100         || _muPairInfos.at(iPair).mass_Roch_sys_up > 100  )
//      hasHighMass = true;
//  }
//  if (!hasHighMass)
//    return;


  // -----------------------
  // MC PILEUP / GEN WEIGHTS
  // -----------------------
  if (_isVerbose) std::cout << "\nAccessing piluep info" << std::endl;
  _nPU = -1;
  _PU_wgt      = 1.0;
  _PU_wgt_up   = 1.0;
  _PU_wgt_down = 1.0;
  if (_isMonteCarlo) {
    edm::Handle< std::vector<PileupSummaryInfo> > PupInfo;
    iEvent.getByToken(_PupInfoToken, PupInfo);
    
    std::vector<PileupSummaryInfo>::const_iterator PVI;
    for (PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
      if (PVI->getBunchCrossing() == 0) { 
	_nPU = PVI->getTrueNumInteractions();
	_PU_wgt      = _PU_wgt_hist->GetBinContent(_nPU);
	_PU_wgt_up   = _PU_wgt_hist_up->GetBinContent(_nPU);
	_PU_wgt_down = _PU_wgt_hist_down->GetBinContent(_nPU);
	continue;
      }
    }
  }
  
  // ---------
  // ELECTRONS
  // ---------
  if (_isVerbose) std::cout << "\nFilling EleInfo" << std::endl;
  edm::Handle<edm::View<pat::Electron>>  eles;
  edm::Handle<edm::ValueMap<bool>>       ele_id_veto;
  edm::Handle<edm::ValueMap<bool>>       ele_id_loose;
  edm::Handle<edm::ValueMap<bool>>       ele_id_medium;
  edm::Handle<edm::ValueMap<bool>>       ele_id_tight;

  iEvent.getByToken(_eleCollToken,     eles);
  iEvent.getByToken(_eleIdVetoToken,   ele_id_veto); 
  iEvent.getByToken(_eleIdLooseToken,  ele_id_loose); 
  iEvent.getByToken(_eleIdMediumToken, ele_id_medium); 
  iEvent.getByToken(_eleIdTightToken,  ele_id_tight); 

  std::vector<std::array<bool, 4>> ele_ID_pass;
  pat::ElectronCollection elesSelected = SelectEles( eles, primaryVertex, ele_id_veto,
  						     ele_id_loose, ele_id_medium, ele_id_tight,
  						     _ele_ID, _ele_pT_min, _ele_eta_max,
						     ele_ID_pass );
  
  // Sort the selected electrons by pT
  sort(elesSelected.begin(), elesSelected.end(), sortElesByPt);
  
  FillEleInfos( _eleInfos, elesSelected, primaryVertex, iEvent, ele_ID_pass );
  _nEles = _eleInfos.size();

  // // ----
  // // TAUS
  // // ----
  // if (_isVerbose) std::cout << "\nFilling TauInfo" << std::endl;
  // edm::Handle<pat::TauCollection> taus;
  // iEvent.getByToken(_tauCollToken, taus);

  // pat::TauCollection tausSelected = SelectTaus( taus, _tau_pT_min, _tau_eta_max );

  // // Sort the selected taus by pT
  // sort(tausSelected.begin(), tausSelected.end(), sortTausByPt);

  // FillTauInfos( _tauInfos, tausSelected, _tauIDNames );  // Sort first? - AWB 09.11.16
  // _nTaus = _tauInfos.size();
    
  // ----
  // JETS
  // ----
  if (_isVerbose) std::cout << "\nFilling JetInfo" << std::endl;
  edm::Handle < pat::JetCollection > jets;
  if(!_jetsToken.isUninitialized()) 
    iEvent.getByToken(_jetsToken, jets);

  edm::Handle<double> rhoHandle;
  iEvent.getByToken(_rhoToken, rhoHandle);
  double _rho = *rhoHandle;

  // Following https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyCorrections#JetCorUncertainties
  //   - Last check that procedure was up-to-date: March 10, 2017 (AWB) 
  edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
  iSetup.get<JetCorrectionsRecord>().get(_jetType, JetCorParColl);
  JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];

  // Following https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution
  //       and https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookJetEnergyResolution
  //   - Last check that procedure was up-to-date: March 10, 2017 (AWB) 
  JME::JetResolution            JetRes   = JME::JetResolution::get(iSetup, _jetType+"_pt");
  JME::JetResolutionScaleFactor JetResSF = JME::JetResolutionScaleFactor::get(iSetup, _jetType);
  
  pat::JetCollection jetsSelected = SelectJets( jets, JetCorPar, JetRes, JetResSF, "none",
						_muonInfos, _eleInfos, _rho,
						_jet_ID, _jet_pT_min, _jet_eta_max, _dMet );
  
  sort(jetsSelected.begin(), jetsSelected.end(), sortJetsByPt);

  FillJetInfos( _jetInfos, _nJetsFwd, 
		_nBLoose, _nBMed, _nBTight, 
		jetsSelected, _btagName );
  _nJets = _jetInfos.size();
  _nJetsCent = _nJets - _nJetsFwd;
  if (_slimOut) FillSlimJetInfos( _slimJetInfos, _jetInfos );
  
  // Alternate collections corresponding to jet energy scale up / down
  if (_doSys) {
    pat::JetCollection jets_JES_up   = SelectJets( jets, JetCorPar, JetRes, JetResSF, "JES_up",
						   _muonInfos, _eleInfos, _rho, 
						   _jet_ID, _jet_pT_min, _jet_eta_max, _dMet_JES_up );
    pat::JetCollection jets_JES_down = SelectJets( jets, JetCorPar, JetRes, JetResSF, "JES_down",
						   _muonInfos, _eleInfos, _rho,
						   _jet_ID, _jet_pT_min, _jet_eta_max, _dMet_JES_down );
    // pat::JetCollection jets_JER_nom  = SelectJets( jets, JetCorPar, JetRes, JetResSF, "JER_nom",
    // 						   _muonInfos, _eleInfos, _rho,
    // 						   _jet_ID, _jet_pT_min, _jet_eta_max, _dMet_JER_nom );
    // pat::JetCollection jets_JER_up   = SelectJets( jets, JetCorPar, JetRes, JetResSF, "JER_up",
    // 						   _muonInfos, _eleInfos, _rho,
    // 						   _jet_ID, _jet_pT_min, _jet_eta_max, _dMet_JER_up );
    // pat::JetCollection jets_JER_down = SelectJets( jets, JetCorPar, JetRes, JetResSF, "JER_down",
    // 						   _muonInfos, _eleInfos, _rho,
    // 						   _jet_ID, _jet_pT_min, _jet_eta_max, _dMet_JER_down );

    sort(jets_JES_up.begin(),   jets_JES_up.end(),   sortJetsByPt);
    sort(jets_JES_down.begin(), jets_JES_down.end(), sortJetsByPt);
    // sort(jets_JER_nom.begin(),  jets_JER_nom.end(),  sortJetsByPt);
    // sort(jets_JER_up.begin(),   jets_JER_up.end(),   sortJetsByPt);
    // sort(jets_JER_down.begin(), jets_JER_down.end(), sortJetsByPt);
    
    FillJetInfos( _jetInfos_JES_up,   _nJetsFwd_JES_up,   
		  _nBLoose_JES_up, _nBMed_JES_up, _nBTight_JES_up, 
		  jets_JES_up,   _btagName );
    FillJetInfos( _jetInfos_JES_down, _nJetsFwd_JES_down, 
		  _nBLoose_JES_down, _nBMed_JES_down, _nBTight_JES_down, 
		  jets_JES_down, _btagName );
    _nJets_JES_up   = _jetInfos_JES_up.size();
    _nJets_JES_down = _jetInfos_JES_down.size();
    _nJetsCent_JES_up   = _nJets_JES_up   - _nJetsFwd_JES_up;
    _nJetsCent_JES_down = _nJets_JES_down - _nJetsFwd_JES_down;
    if (_slimOut) FillSlimJetInfos( _slimJetInfos_JES_up,   _jetInfos_JES_up   );
    if (_slimOut) FillSlimJetInfos( _slimJetInfos_JES_down, _jetInfos_JES_down );

    // FillJetInfos( _jetInfos_JER_nom,  _nJetsFwd_JER_nom,   
    // 		  _nBLoose_JER_nom,  _nBMed_JER_nom,  _nBTight_JER_nom, 
    // FillJetInfos( _jetInfos_JER_up,   _nJetsFwd_JER_up,   
    // 		  _nBLoose_JER_up,   _nBMed_JER_up,   _nBTight_JER_up, 
    // 		  jets_JER_up,   _btagName );
    // FillJetInfos( _jetInfos_JER_down, _nJetsFwd_JER_down, 
    // 		  _nBLoose_JER_down, _nBMed_JER_down, _nBTight_JER_down, 
    // 		  jets_JER_down, _btagName );
    // _nJets_JER_nom  = _jetInfos_JER_nom.size();
    // _nJets_JER_up   = _jetInfos_JER_up.size();
    // _nJets_JER_down = _jetInfos_JER_down.size();
    // _nJetsCent_JER_nom  = _nJets_JER_nom  - _nJetsFwd_JER_nom;
    // _nJetsCent_JER_up   = _nJets_JER_up   - _nJetsFwd_JER_up;
    // _nJetsCent_JER_down = _nJets_JER_down - _nJetsFwd_JER_down;
    // if (_slimOut) FillSlimJetInfos( _slimJetInfos_JER_nom,  _jetInfos_JER_nom  );
    // if (_slimOut) FillSlimJetInfos( _slimJetInfos_JER_up,   _jetInfos_JER_up   );
    // if (_slimOut) FillSlimJetInfos( _slimJetInfos_JER_down, _jetInfos_JER_down );
  }

  // -----------
  // DIJET PAIRS
  // -----------
  if (_isVerbose) std::cout << "\nFilling JetPairInfo" << std::endl;
  FillJetPairInfos( _jetPairInfos, _jetInfos );
  _nJetPairs = _jetPairInfos.size();
  if (_doSys) {
    FillJetPairInfos( _jetPairInfos_JES_up, _jetInfos_JES_up );
    FillJetPairInfos( _jetPairInfos_JES_down, _jetInfos_JES_down );
    // FillJetPairInfos( _jetPairInfos_JER_nom, _jetInfos_JER_nom );
    // FillJetPairInfos( _jetPairInfos_JER_up, _jetInfos_JER_up );
    // FillJetPairInfos( _jetPairInfos_JER_down, _jetInfos_JER_down );
  }
  
  // Instructions for re-miniAOD: https://twiki.cern.ch/twiki/bin/view/CMS/MissingETUncertaintyPrescription - AWB 01.03.17
  // ---
  // MET
  // ---
  if (_isVerbose) std::cout << "\nFilling MetInfo" << std::endl;
  edm::Handle < pat::METCollection > mets;
  if (!_metToken.isUninitialized()) 
    iEvent.getByToken(_metToken, mets);
  
  FillMetInfo( _metInfo, mets, iEvent, _dMet );
  if (_doSys) {
    FillMetInfo( _metInfo_JES_up, mets, iEvent, _dMet_JES_up );
    FillMetInfo( _metInfo_JES_down, mets, iEvent, _dMet_JES_down );
    // FillMetInfo( _metInfo_JER_nom, mets, iEvent, _dMet_JER_nom );
    // FillMetInfo( _metInfo_JER_up, mets, iEvent, _dMet_JER_up );
    // FillMetInfo( _metInfo_JER_down, mets, iEvent, _dMet_JER_down );
  }

  // ---
  // MHT
  // ---
  if (_isVerbose) std::cout << "\nFilling MhtInfo" << std::endl;
  
  FillMhtInfo( _mhtInfo, _muonInfos, _eleInfos, _jetInfos ); 
  if (_doSys) {
    FillMhtInfo( _mhtInfo_JES_up, _muonInfos, _eleInfos, _jetInfos_JES_up ); 
    FillMhtInfo( _mhtInfo_JES_down, _muonInfos, _eleInfos, _jetInfos_JES_down ); 
    // FillMhtInfo( _mhtInfo_JER_nom, _muonInfos, _eleInfos, _jetInfos_JER_nom); 
    // FillMhtInfo( _mhtInfo_JER_up, _muonInfos, _eleInfos, _jetInfos_JER_up ); 
    // FillMhtInfo( _mhtInfo_JER_down, _muonInfos, _eleInfos, _jetInfos_JER_down ); 
  }

  // -------------
  // GEN PARTICLES
  // -------------
  if (_isMonteCarlo) {
    // Parents
    if (_isVerbose) std::cout << "\nFilling GenParentInfo" << std::endl;

    FillGenParentInfos( _genParentInfos, genPartons, 
			std::vector<int> {6, 22, 23, 24, 25}, 
			_isMonteCarlo );
    _nGenParents = _genParentInfos.size();

    // Muons
    if (_isVerbose) std::cout << "\nFilling GenMuonInfo" << std::endl;
    FillGenMuonInfos( _genMuonInfos, _genParentInfos, genPartons, _isMonteCarlo );
    _nGenMuons = _genMuonInfos.size();
    _nGenParents = _genParentInfos.size();

    if (_isVerbose) std::cout << "\nFilling GenMuPairInfo" << std::endl;
    FillGenMuPairInfos( _genMuPairInfos, _genMuonInfos );
    _nGenMuPairs = _genMuPairInfos.size();

    // Jets
    if (_isVerbose) std::cout << "\nFilling GenJetInfo" << std::endl;
    edm::Handle < reco::GenJetCollection > genJets;
    if (!_genJetsToken.isUninitialized()) 
      iEvent.getByToken(_genJetsToken, genJets);

    FillGenJetInfos( _genJetInfos, genJets, _isMonteCarlo );
    _nGenJets = _genJetInfos.size();

  } // End conditional: if (_isMonteCarlo)


  // ============================
  // Store everything in an NTuple
  // ============================
  if (_isVerbose) std::cout << "\nFilling tree" << std::endl;
  _outTree->Fill();
  if (_isVerbose) std::cout << "\nD O N E !!! WITH EVENT!" << std::endl;
  return;  
} // End void UFDiMuonsAnalyzer::analyze

	
///////////////////////////////////////////////////////////
// BeginJob ==============================================
//////////////////////////////////////////////////////////

// Method called once each job just before starting event loop
// Set up TTrees where we save all of the info gathered in the analyzer
void UFDiMuonsAnalyzer::beginJob() {

  displaySelection();

  // // Include user-defined structs (or classes) in the output tree
  // gROOT->ProcessLine("#include <Ntupliser/DiMuons/interface/LinkDef.h>");

  if (_slimOut) {
    _outTree->Branch("jets",          (SlimJetInfos*)      &_slimJetInfos          );
    if (_doSys) {
      _outTree->Branch("jets_JES_up",   (SlimJetInfos*)      &_slimJetInfos_JES_up   );
      _outTree->Branch("jets_JES_down", (SlimJetInfos*)      &_slimJetInfos_JES_down );
      // _outTree->Branch("jets_JER_nom",  (SlimJetInfos*)      &_slimJetInfos_JER_nom  );
      // _outTree->Branch("jets_JER_up",   (SlimJetInfos*)      &_slimJetInfos_JER_up   );
      // _outTree->Branch("jets_JER_down", (SlimJetInfos*)      &_slimJetInfos_JER_down );
    }
  } else {
    _outTree->Branch("jets",          (JetInfos*)      &_jetInfos          );
    if (_doSys) {
      _outTree->Branch("jets_JES_up",   (JetInfos*)      &_jetInfos_JES_up   );
      _outTree->Branch("jets_JES_down", (JetInfos*)      &_jetInfos_JES_down );
      // _outTree->Branch("jets_JER_nom",  (JetInfos*)      &_jetInfos_JER_nom  );
      // _outTree->Branch("jets_JER_up",   (JetInfos*)      &_jetInfos_JER_up   );
      // _outTree->Branch("jets_JER_down", (JetInfos*)      &_jetInfos_JER_down );
    }
  }

  // Set up the _outTree branches
  _outTree->Branch("event",             (EventInfo*)     &_eventInfo             );
  _outTree->Branch("vertices",      (VertexInfos*)   &_vertexInfos       );
  _outTree->Branch("jetPairs",          (JetPairInfos*)  &_jetPairInfos          );
  if (_doSys) {
    _outTree->Branch("jetPairs_JES_up",   (JetPairInfos*)  &_jetPairInfos_JES_up   );
    _outTree->Branch("jetPairs_JES_down", (JetPairInfos*)  &_jetPairInfos_JES_down );
    // _outTree->Branch("jetPairs_JER_nom",  (JetPairInfos*)  &_jetPairInfos_JER_nom  );
    // _outTree->Branch("jetPairs_JER_up",   (JetPairInfos*)  &_jetPairInfos_JER_up   );
    // _outTree->Branch("jetPairs_JER_down", (JetPairInfos*)  &_jetPairInfos_JER_down );
  }
  _outTree->Branch("muons",             (MuonInfos*)     &_muonInfos         );
  _outTree->Branch("muPairs",           (MuPairInfos*)   &_muPairInfos       );
  _outTree->Branch("eles",              (EleInfos*)      &_eleInfos          );
  // _outTree->Branch("taus",              (TauInfos*)      &_tauInfos          );
  _outTree->Branch("met",               (MetInfo*)       &_metInfo           );
  if (_doSys) {
    _outTree->Branch("met_JES_up",        (MetInfo*)       &_metInfo_JES_up    );
    _outTree->Branch("met_JES_down",      (MetInfo*)       &_metInfo_JES_down  );
    // _outTree->Branch("met_JER_nom",       (MetInfo*)       &_metInfo_JER_nom   );
    // _outTree->Branch("met_JER_up",        (MetInfo*)       &_metInfo_JER_up    );
    // _outTree->Branch("met_JER_down",      (MetInfo*)       &_metInfo_JER_down  );
  }
  _outTree->Branch("mht",               (MhtInfo*)       &_mhtInfo           );
  if (_doSys) {
    _outTree->Branch("mht_JES_up",        (MhtInfo*)       &_mhtInfo_JES_up    );
    _outTree->Branch("mht_JES_down",      (MhtInfo*)       &_mhtInfo_JES_down  );
    // _outTree->Branch("mht_JER_nom",       (MhtInfo*)       &_mhtInfo_JER_nom   );
    // _outTree->Branch("mht_JER_up",        (MhtInfo*)       &_mhtInfo_JER_up    );
    // _outTree->Branch("mht_JER_down",      (MhtInfo*)       &_mhtInfo_JER_down  );
  }

  _outTree->Branch("nVertices",          (int*) &_nVertices          );
  _outTree->Branch("nMuons",             (int*) &_nMuons             );
  _outTree->Branch("nMuPairs",           (int*) &_nMuPairs           );
  _outTree->Branch("nEles",              (int*) &_nEles              );
  // _outTree->Branch("nTaus",              (int*) &_nTaus              );
  _outTree->Branch("nJets",              (int*) &_nJets              );
  _outTree->Branch("nJetPairs",          (int*) &_nJetPairs           );
  _outTree->Branch("nJetsCent",          (int*) &_nJetsCent          );
  _outTree->Branch("nJetsFwd",           (int*) &_nJetsFwd           );
  _outTree->Branch("nBLoose",            (int*) &_nBLoose            );
  _outTree->Branch("nBMed",              (int*) &_nBMed              );
  _outTree->Branch("nBTight",            (int*) &_nBTight            );

  if (_doSys) {
    _outTree->Branch("nJets_JES_up",       (int*) &_nJets_JES_up       );
    _outTree->Branch("nJetsCent_JES_up",   (int*) &_nJetsCent_JES_up   );
    _outTree->Branch("nBLoose_JES_up",     (int*) &_nBLoose_JES_up     );
    _outTree->Branch("nBMed_JES_up",       (int*) &_nBMed_JES_up       );
    _outTree->Branch("nBTight_JES_up",     (int*) &_nBTight_JES_up     );
    _outTree->Branch("nJetsFwd_JES_up",    (int*) &_nJetsFwd_JES_up    );
    _outTree->Branch("nJets_JES_down",     (int*) &_nJets_JES_down     );
    _outTree->Branch("nJetsCent_JES_down", (int*) &_nJetsCent_JES_down );
    _outTree->Branch("nJetsFws_JES_down",  (int*) &_nJetsFwd_JES_down  );
    _outTree->Branch("nBLoose_JES_down",   (int*) &_nBLoose_JES_down   );
    _outTree->Branch("nBMed_JES_down",     (int*) &_nBMed_JES_down     );
    _outTree->Branch("nBTight_JES_down",   (int*) &_nBTight_JES_down   );
    // _outTree->Branch("nJets_JER_nom",      (int*) &_nJets_JER_nom      );
    // _outTree->Branch("nJetsCent_JER_nom",  (int*) &_nJetsCent_JER_nom  );
    // _outTree->Branch("nJetsFwd_JER_nom",   (int*) &_nJetsFwd_JER_nom   );
    // _outTree->Branch("nBLoose_JER_nom",    (int*) &_nBLoose_JER_nom    );
    // _outTree->Branch("nBMed_JER_nom",      (int*) &_nBMed_JER_nom      );
    // _outTree->Branch("nBTight_JER_nom",    (int*) &_nBTight_JER_nom    );
    // _outTree->Branch("nJets_JER_up",       (int*) &_nJets_JER_up       );
    // _outTree->Branch("nJetsCent_JER_up",   (int*) &_nJetsCent_JER_up   );
    // _outTree->Branch("nJetsFwd_JER_up",    (int*) &_nJetsFwd_JER_up    );
    // _outTree->Branch("nBLoose_JER_up",     (int*) &_nBLoose_JER_up     );
    // _outTree->Branch("nBMed_JER_up",       (int*) &_nBMed_JER_up       );
    // _outTree->Branch("nBTight_JER_up",     (int*) &_nBTight_JER_up     );
    // _outTree->Branch("nJets_JER_down",     (int*) &_nJets_JER_down     );
    // _outTree->Branch("nJetsCent_JER_down", (int*) &_nJetsCent_JER_down );
    // _outTree->Branch("nJetsFws_JER_down",  (int*) &_nJetsFwd_JER_down  );
    // _outTree->Branch("nBLoose_JER_down",   (int*) &_nBLoose_JER_down   );
    // _outTree->Branch("nBMed_JER_down",     (int*) &_nBMed_JER_down     );
    // _outTree->Branch("nBTight_JER_down",   (int*) &_nBTight_JER_down   );
  }

  _outTree->Branch("hltPaths",      &_trigNames);
  _outTree->Branch("btagName",      &_btagName   );
  // _outTree->Branch("tauIDNames",    &_tauIDNames  );

  // Weights and efficiencies
  _outTree->Branch("Flag_all",      &_Flag_all,      "Flag_all/I"      );
  _outTree->Branch("Flag_badMu",    &_Flag_badMu,    "Flag_badMu/I"    );
  _outTree->Branch("Flag_dupMu",    &_Flag_dupMu,    "Flag_dupMu/I"    );
  _outTree->Branch("Flag_halo",     &_Flag_halo,     "Flag_halo/I"     );
  _outTree->Branch("Flag_PV",       &_Flag_PV,       "Flag_PV/I"       );
  _outTree->Branch("Flag_HBHE",     &_Flag_HBHE,     "Flag_HBHE/I"     );
  _outTree->Branch("Flag_HBHE_Iso", &_Flag_HBHE_Iso, "Flag_HBHE_Iso/I" );
  _outTree->Branch("Flag_ECAL_TP",  &_Flag_ECAL_TP,  "Flag_ECAL_TP/I"  ); 
  _outTree->Branch("Flag_BadChCand",    &_Flag_BadChCand,    "Flag_BadChCand/I"     );
  _outTree->Branch("Flag_eeBadSc",      &_Flag_eeBadSc,      "Flag_eeBadSc/I"       );
  _outTree->Branch("Flag_ecalBadCalib", &_Flag_ecalBadCalib, "Flag_ecalBadCalib/I"  );
 
  _outTree->Branch("IsoMu_eff_3",        &_IsoMu_eff_3,        "IsoMu_eff_3/F"        );
  _outTree->Branch("IsoMu_eff_3_up",     &_IsoMu_eff_3_up,     "IsoMu_eff_3_up/F"     );
  _outTree->Branch("IsoMu_eff_3_down",   &_IsoMu_eff_3_down,   "IsoMu_eff_3_down/F"   );
  _outTree->Branch("IsoMu_eff_bug",      &_IsoMu_eff_bug,      "IsoMu_eff_bug/F"      );
  _outTree->Branch("IsoMu_eff_bug_up",   &_IsoMu_eff_bug_up,   "IsoMu_eff_bug_up/F"   );
  _outTree->Branch("IsoMu_eff_bug_down", &_IsoMu_eff_bug_down, "IsoMu_eff_bug_down/F" );

  _outTree->Branch("MuID_eff_3",        &_MuID_eff_3,        "MuID_eff_3/F"        );
  _outTree->Branch("MuID_eff_3_up",     &_MuID_eff_3_up,     "MuID_eff_3_up/F"     );
  _outTree->Branch("MuID_eff_3_down",   &_MuID_eff_3_down,   "MuID_eff_3_down/F"   );
  _outTree->Branch("MuID_eff_4",        &_MuID_eff_4,        "MuID_eff_4/F"        );
  _outTree->Branch("MuID_eff_4_up",     &_MuID_eff_4_up,     "MuID_eff_4_up/F"     );
  _outTree->Branch("MuID_eff_4_down",   &_MuID_eff_4_down,   "MuID_eff_4_down/F"   );

  _outTree->Branch("MuIso_eff_3",        &_MuIso_eff_3,        "MuIso_eff_3/F"        );
  _outTree->Branch("MuIso_eff_3_up",     &_MuIso_eff_3_up,     "MuIso_eff_3_up/F"     );
  _outTree->Branch("MuIso_eff_3_down",   &_MuIso_eff_3_down,   "MuIso_eff_3_down/F"   );
  // _outTree->Branch("MuIso_eff_4",        &_MuIso_eff_4,        "MuIso_eff_4/F"        );
  // _outTree->Branch("MuIso_eff_4_up",     &_MuIso_eff_4_up,     "MuIso_eff_4_up/F"     );
  // _outTree->Branch("MuIso_eff_4_down",   &_MuIso_eff_4_down,   "MuIso_eff_4_down/F"   );

  if (_isMonteCarlo) {
      _outTree->Branch("IsoMu_SF_3",        &_IsoMu_SF_3,        "IsoMu_SF_3/F"        );
    _outTree->Branch("IsoMu_SF_3_up",     &_IsoMu_SF_3_up,     "IsoMu_SF_3_up/F"     );
    _outTree->Branch("IsoMu_SF_3_down",   &_IsoMu_SF_3_down,   "IsoMu_SF_3_down/F"   );
    _outTree->Branch("IsoMu_SF_bug",      &_IsoMu_SF_bug,      "IsoMu_SF_bug/F"      );
    _outTree->Branch("IsoMu_SF_bug_up",   &_IsoMu_SF_bug_up,   "IsoMu_SF_bug_up/F"   );
    _outTree->Branch("IsoMu_SF_bug_down", &_IsoMu_SF_bug_down, "IsoMu_SF_bug_down/F" );
    
    _outTree->Branch("MuID_SF_3",        &_MuID_SF_3,        "MuID_SF_3/F"        );
    _outTree->Branch("MuID_SF_3_up",     &_MuID_SF_3_up,     "MuID_SF_3_up/F"     );
    _outTree->Branch("MuID_SF_3_down",   &_MuID_SF_3_down,   "MuID_SF_3_down/F"   );
    _outTree->Branch("MuID_SF_4",        &_MuID_SF_4,        "MuID_SF_4/F"        );
    _outTree->Branch("MuID_SF_4_up",     &_MuID_SF_4_up,     "MuID_SF_4_up/F"     );
    _outTree->Branch("MuID_SF_4_down",   &_MuID_SF_4_down,   "MuID_SF_4_down/F"   );
    
    _outTree->Branch("MuIso_SF_3",        &_MuIso_SF_3,        "MuIso_SF_3/F"        );
    _outTree->Branch("MuIso_SF_3_up",     &_MuIso_SF_3_up,     "MuIso_SF_3_up/F"     );
    _outTree->Branch("MuIso_SF_3_down",   &_MuIso_SF_3_down,   "MuIso_SF_3_down/F"   );
  //   _outTree->Branch("MuIso_SF_4",        &_MuIso_SF_4,        "MuIso_SF_4/F"        );
  //   _outTree->Branch("MuIso_SF_4_up",     &_MuIso_SF_4_up,     "MuIso_SF_4_up/F"     );
  //   _outTree->Branch("MuIso_SF_4_down",   &_MuIso_SF_4_down,   "MuIso_SF_4_down/F"   );
  }

  // MC information
  if (_isMonteCarlo) {

    _outTree->Branch("LHE_HT",      &_LHE_HT,      "LHT_HT/F"      );
    _outTree->Branch("nPU", 	    &_nPU,         "nPU/I"         );
    _outTree->Branch("PU_wgt",      &_PU_wgt,      "PU_wgt/F"      );
    _outTree->Branch("PU_wgt_up",   &_PU_wgt_up,   "PU_wgt_up/F"   );
    _outTree->Branch("PU_wgt_down", &_PU_wgt_down, "PU_wgt_down/F" );
    _outTree->Branch("GEN_wgt",     &_GEN_wgt,     "GEN_wgt/I"     );
    
    _outTree->Branch("nGenParents", (int*) &_nGenParents );
    _outTree->Branch("nGenMuons",   (int*) &_nGenMuons   );
    _outTree->Branch("nGenMuPairs", (int*) &_nGenMuPairs );
    
    _outTree->Branch("genParents", (GenParentInfos*) &_genParentInfos );
    _outTree->Branch("genMuons",   (GenMuonInfos*)   &_genMuonInfos   );
    _outTree->Branch("genMuPairs", (GenMuPairInfos*) &_genMuPairInfos );

    if (!_slimOut) {
      _outTree->Branch("nGenJets", (int*)         &_nGenJets    );
      _outTree->Branch("genJets",  (GenJetInfos*) &_genJetInfos );
    }  // End conditional: if (!_slimOut)

  }

}

///////////////////////////////////////////////////////////
// BeginJob ==============================================
//////////////////////////////////////////////////////////

void UFDiMuonsAnalyzer::endJob() 
{
// Method called once each job just after ending the event loop
// Set up the meta data ttree and save it.

  std::cout << "Total Number of Events Read: "<< _numEvents << std::endl <<std::endl;
  std::cout << "Number of events weighted: "  << _sumEventWeights << std::endl <<std::endl;

  std::cout<<"number of dimuon candidates: "
           <<_outTree->GetEntries()<<std::endl;

  // create the metadata tree branches
  _outTreeMetadata->Branch("originalNumEvents", &_numEvents,        "originalNumEvents/I");
  _outTreeMetadata->Branch("sumEventWeights",   &_sumEventWeights,  "sumEventWeights/I");
  _outTreeMetadata->Branch("isMonteCarlo",      &_isMonteCarlo,     "isMonteCarlo/O");

  _outTreeMetadata->Branch("trigNames",  "std::vector< std::string >", &_trigNames);
  _outTreeMetadata->Branch("btagName",   "std::string",                &_btagName);
  // _outTreeMetadata->Branch("tauIDNames", "std::vector< std::string >", &_tauIDNames);

  _outTreeMetadata->Fill();

}

////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////

bool UFDiMuonsAnalyzer::isHltPassed(const edm::Event& iEvent, const edm::EventSetup& iSetup, 
				    const edm::Handle<edm::TriggerResults>& trigResultsHandle,
                                    const std::vector<std::string> desiredTrigNames) 
{
// this method will simply check if the selected HLT path (via triggerName)
// is run and accepted and no error are found
//
// bool true  if (run && accept && !error)
//      false if any other combination
  
  using namespace std;
  using namespace edm;
  using namespace reco;
  using namespace trigger;


  const boost::regex re("_v[0-9]+");

  const TriggerNames &trigNames = iEvent.triggerNames(*trigResultsHandle);

  const unsigned nTrigs = trigResultsHandle->size();
  for (unsigned iTrig = 0; iTrig < nTrigs; ++iTrig)
  {
    const string trigName = trigNames.triggerName(iTrig);
    string trigNameStripped = boost::regex_replace(trigName,re,"",boost::match_default | boost::format_sed);
    for(std::vector<std::string>::const_iterator desiredTrigName=desiredTrigNames.begin();
            desiredTrigName!=desiredTrigNames.end();desiredTrigName++)
    {
     if (*desiredTrigName == trigNameStripped && trigResultsHandle->accept(iTrig))
      {
        stringstream debugString;
        debugString << "isHltPassed:" <<endl;
        debugString << "  Trigger "<<iTrig<<": "<< trigName << "("<<trigNameStripped<<") passed: "<<trigResultsHandle->accept(iTrig)<<endl;
        debugString << "    Desired Trigger Names: ";
        debugString <<"'"<< *desiredTrigName<<"' ";
        debugString << endl << "    Accept Trigger" << endl;
        LogVerbatim("UFHLTTests") << debugString.str();
        return true;
      }
    }
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////

void UFDiMuonsAnalyzer::FillEventFlags(const edm::Event& iEvent, const edm::EventSetup& iSetup,
				       const edm::Handle<edm::TriggerResults>& evtFlagsHandle,
				       int& _Flag_all, int& _Flag_badMu, int& _Flag_dupMu, int& _Flag_halo, 
				       int& _Flag_PV, int& _Flag_HBHE, int& _Flag_HBHE_Iso, int& _Flag_ECAL_TP,
                                       int& _Flag_BadChCand, int& _Flag_eeBadSc, int& _Flag_ecalBadCalib  ) {
  using namespace std;
  using namespace edm;
  using namespace reco;
  using namespace trigger;

  _Flag_all      = -99;
  _Flag_badMu    = -99;
  _Flag_dupMu    = -99;
  _Flag_halo     = -99;
  _Flag_PV       = -99;
  _Flag_HBHE     = -99;
  _Flag_HBHE_Iso = -99;
  _Flag_ECAL_TP  = -99;
  _Flag_BadChCand = -99;
  _Flag_eeBadSc   = -99;
  _Flag_ecalBadCalib = -99;

  const TriggerNames &flagNames = iEvent.triggerNames(*evtFlagsHandle);
  const unsigned nFlags = evtFlagsHandle->size();
  for (unsigned iFlag = 0; iFlag < nFlags; ++iFlag) {
    const string flagName = flagNames.triggerName(iFlag);
    const int flagResult = evtFlagsHandle->accept(iFlag);
   
    // Updating the flag for 2017 data and Fall17 MC - PB 2018.07.31 
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#Moriond_2018
    // std::cout << "  * " << flagName << " = " << flagResult << std::endl;
    if (flagName == "Flag_BadPFMuonFilter")
      _Flag_badMu = flagResult;
    if (flagName == "Flag_duplicateMuons")
      _Flag_dupMu = 1;
    if (flagName == "Flag_globalTightHalo2016Filter")
      _Flag_halo = flagResult;
    if (flagName == "Flag_goodVertices")
      _Flag_PV = flagResult;
    if (flagName == "Flag_HBHENoiseFilter")
      _Flag_HBHE = flagResult;
    if (flagName == "Flag_HBHENoiseIsoFilter")
      _Flag_HBHE_Iso = flagResult;
    if (flagName == "Flag_EcalDeadCellTriggerPrimitiveFilter")
      _Flag_ECAL_TP = flagResult;

    if (flagName == "Flag_BadChargedCandidateFilter")
      _Flag_BadChCand = flagResult;
    if (flagName == "Flag_eeBadScFilter") // suggested only in data
      _Flag_eeBadSc = flagResult;
    if (flagName == "Flag_ecalBadCalibFilter")
      _Flag_ecalBadCalib = flagResult;

// PB: need to add some more flags. Flag_BadChargedCandidateFilter, Flag_eeBadScFilter (not suggested in MC), Flag_ecalBadCalibFilter

  } // End loop: for (unsigned iFlag = 0; iFlag < nFlags; ++iFlag)

  if ( _Flag_badMu == 0 || _Flag_dupMu == 0 || _Flag_halo == 0 ||
       _Flag_PV == 0 || _Flag_HBHE == 0 || _Flag_HBHE_Iso == 0 || 
       _Flag_ECAL_TP == 0  || _Flag_BadChCand == 0 || _Flag_ecalBadCalib == 0 || ((!_isMonteCarlo) && _Flag_eeBadSc == 0) )
      _Flag_all = 0;
  if ( _Flag_badMu == 1 && _Flag_dupMu == 1 && _Flag_halo == 1 &&
       _Flag_PV == 1 && _Flag_HBHE == 1 && _Flag_HBHE_Iso == 1 && 
       _Flag_ECAL_TP == 1 && _Flag_BadChCand == 1 && _Flag_ecalBadCalib == 1 && ((!_isMonteCarlo) && _Flag_eeBadSc == 1) )
      _Flag_all = 1;
 
} // End function: void UFDiMuonsAnalyzer::FillEventFlags()

////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////

float UFDiMuonsAnalyzer::calcHtLHE(const edm::Handle<LHEEventProduct>& LHE_handle) {

  int   num_isr_me = 0;
  float ht_isr_me  = 0;

  for (int i = 0 ; i < LHE_handle->hepeup().NUP; i++) {
    int pdgid    = abs(LHE_handle->hepeup().IDUP[i]);
    int status   = LHE_handle->hepeup().ISTUP[i];
    int mom1_idx = LHE_handle->hepeup().MOTHUP[i].first;
    int mom2_idx = LHE_handle->hepeup().MOTHUP[i].second;
    int mom1id   = mom1_idx==0 ? 0 : abs(LHE_handle->hepeup().IDUP[mom1_idx-1]);
    int mom2id   = mom2_idx==0 ? 0 : abs(LHE_handle->hepeup().IDUP[mom2_idx-1]);
    
    float px = (LHE_handle->hepeup().PUP[i])[0];
    float py = (LHE_handle->hepeup().PUP[i])[1];
    float pt = sqrt(px*px+py*py);
    
    if ( status == 1 && (pdgid < 6 || pdgid == 21) && mom1id != 6 && mom2id != 6 && 
	 abs(mom1id - 24) > 1 && abs(mom2id - 24) > 1 ) {
      num_isr_me += 1;
      ht_isr_me  += pt;
    }
  }

  // std::cout << "\n\nOut of " << LHE_handle->hepeup().NUP << " particles, nISR = " << num_isr_me << ", HT = " << ht_isr_me << std::endl;
  return ht_isr_me;
  
}

////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////

void UFDiMuonsAnalyzer::displaySelection() {

  std::cout << "\n\n*** UFDiMuonsAnalyzer Configuration ***\n";

  // cout object / event cuts - AWB 14.11.16
  std::cout << "_vertex_ndof_min = " << _vertex_ndof_min << std::endl;
  std::cout << "_vertex_rho_max  = " << _vertex_rho_max << std::endl;
  std::cout << "_vertex_z_max    = " << _vertex_z_max << std::endl;

  std::cout << "_muon_ID        = " << _muon_ID << std::endl;
  std::cout << "_muon_pT_min    = " << _muon_pT_min << std::endl;
  std::cout << "_muon_eta_max   = " << _muon_eta_max << std::endl;
  std::cout << "_muon_trig_dR   = " << _muon_trig_dR << std::endl;
  std::cout << "_muon_use_pfIso = " << _muon_use_pfIso << std::endl;
  std::cout << "_muon_iso_dR    = " << _muon_iso_dR << std::endl;
  std::cout << "_muon_iso_max   = " << _muon_iso_max << std::endl;

  std::cout << "_ele_ID      = " << _ele_ID << std::endl;
  std::cout << "_ele_pT_min  = " << _ele_pT_min << std::endl;
  std::cout << "_ele_eta_max = " << _ele_eta_max << std::endl;

  // std::cout << "_tau_pT_min  = " << _tau_pT_min << std::endl;
  // std::cout << "_tau_eta_max = " << _tau_eta_max << std::endl;

  std::cout << "_jet_ID      = " << _jet_ID << std::endl;
  std::cout << "_jet_pT_min  = " << _jet_pT_min << std::endl;
  std::cout << "_jet_eta_max = " << _jet_eta_max << std::endl;

  // module config parameters
  std::cout << " - _skim_trig: " << _skim_trig << std::endl;
  std::cout << " - Triggers To Probe:\n";
  unsigned int trigSize = _trigNames.size();
  for (unsigned int i=0; i < trigSize; i++) 
    std::cout << "    * trigNames["<<i<<"]: " << _trigNames[i] << std::endl;
  
  std::cout << std::endl << std::endl;

}

////////////////////////////////////////////////////////////////////////////
//-- ----------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////

bool UFDiMuonsAnalyzer::sortMuonsByPt    (pat::Muon i,     pat::Muon j    ) { return (i.pt() > j.pt()); }
bool UFDiMuonsAnalyzer::sortElesByPt     (pat::Electron i, pat::Electron j) { return (i.pt() > j.pt()); }
// bool UFDiMuonsAnalyzer::sortTausByPt     (pat::Tau i,      pat::Tau j     ) { return (i.pt() > j.pt()); }
bool UFDiMuonsAnalyzer::sortJetsByPt     (pat::Jet i,      pat::Jet j     ) { return (i.pt() > j.pt()); }

