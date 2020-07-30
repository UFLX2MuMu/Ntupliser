///////////////////////////////////////////////////////////
//=========================================================
// UFDiMuonsAnalyzer.h                                   //
//=========================================================
//                                                       //
// H->MuMu Analyzer for UF. Handed down and revamped     //
// too many times.                                       //
//                                                       //
//========================================================
///////////////////////////////////////////////////////////

#ifndef ADD_UDAV2
#define ADD_UDAV2

// All the possible includes in CMSSW
#include "Ntupliser/DiMuons/interface/CommonIncludes.h"

// Add the data formats that we store most of the info into
#include "Ntupliser/DiMuons/interface/NTupleBranches.h"
#include "Ntupliser/DiMuons/interface/NTupleHelpers.h"

// Special calibration and lepton ID classes
#include "KaMuCa/Calibration/interface/KalmanMuonCalibrator.h"
#include "Ntupliser/RochCor/interface/RoccoR.h"
#include "Ntupliser/DiMuons/interface/LepMVA.h"

// Classes or json handling
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"

///////////////////////////////////////////////////////////
// Class Definition ======================================
//////////////////////////////////////////////////////////

class UFDiMuonsAnalyzer : public edm::EDAnalyzer {

public:

  ///////////////////////////////////////////////////////////
  // Constructors/Destructors===============================
  //////////////////////////////////////////////////////////

  explicit UFDiMuonsAnalyzer(const edm::ParameterSet&);
  ~UFDiMuonsAnalyzer();

  ///////////////////////////////////////////////////////////
  // Basic types ===========================================
  ///////////////////////////////////////////////////////////

  // meta-data not given in python config file
  // info gathered from py cfg defined later (py-cfg meta data: isMonteCarlo, trigNames, tauIDNames, bTagName)
  int _numEvents;
  float _sumEventWeights;
  int   _sumEventWeightsOld;

  // tracks pairs, e.g. cocktail
  typedef std::pair<reco::Track,reco::Track> TrackPair;
  typedef std::vector<TrackPair> TrackPairs;

  // GEN info
  float  _LHE_HT;
  int    _nPU;     // True number of vertices
  float  _PU_wgt;  // Pileup weight
  float  _PU_wgt_up;
  float  _PU_wgt_down;
  TH1D*  _PU_wgt_hist;
  TH1D*  _PU_wgt_hist_up;
  TH1D*  _PU_wgt_hist_down;
  TFile* _PU_wgt_file;
  int   _GEN_wgt_old;    // +1 or -1 weight for nlo samples, -1 simulates interference when filling histos
  float _GEN_wgt;

  ///////////////////////////////////////////////////////////
  // Structs  ==============================================
  //////////////////////////////////////////////////////////
  
  // general event information	
  EventInfo _eventInfo;

  // event flags
  int _Flag_all;
  int _Flag_badMu;
  int _Flag_dupMu;
  int _Flag_halo;
  int _Flag_PV;
  int _Flag_HBHE;
  int _Flag_HBHE_Iso;
  int _Flag_ECAL_TP;
  int _Flag_BadChCand;
  int _Flag_eeBadSc;
  int _Flag_ecalBadCalib;
 
  // vector of vertex information
  VertexInfos _vertexInfos;
  int _nVertices;

  // vector of muons
  MuonInfos _muonInfos;
  int _nMuons;

  // info about the dimuon candidates in _muonInfos
  MuPairInfos _muPairInfos;
  int _nMuPairs;

  // vector of electrons
  EleInfos  _eleInfos;
  int _nEles;

  // vector of photons
  PhotInfos _photInfos;
  int _nPhots;

  // vector of taus
  TauInfos  _tauInfos;
  int _nTaus;

  // generator level info Gamma pre-FSR
  GenPartInfo _genGpreFSR, _genM1GpreFSR, _genM2GpreFSR;

  // generator level info Gamma post-FSR
  GenPartInfo _genGpostFSR, _genM1GpostFSR, _genM2GpostFSR;

  // generator level info Z pre-FSR
  GenPartInfo _genZpreFSR, _genM1ZpreFSR, _genM2ZpreFSR;

  // generator level info Z post-FSR
  GenPartInfo _genZpostFSR, _genM1ZpostFSR, _genM2ZpostFSR;

  // generator level info W pre-FSR
  GenPartInfo _genWpreFSR, _genMWpreFSR;

  // generator level info W post-FSR
  GenPartInfo _genWpostFSR, _genMWpostFSR;

  // generator level info H pre-FSR
  GenPartInfo _genHpreFSR, _genM1HpreFSR,_genM2HpreFSR;

  // generator level info H post-FSR
  GenPartInfo _genHpostFSR, _genM1HpostFSR,_genM2HpostFSR;

  // Jets and MET
  JetInfos     _jetInfos;
  SlimJetInfos _slimJetInfos;
  int _nJets, _nJetsCent, _nJetsFwd;
  int _nBLoose, _nBMed, _nBTight;
  JetInfos     _jetInfos_JES_up;
  SlimJetInfos _slimJetInfos_JES_up;
  int _nJets_JES_up, _nJetsCent_JES_up, _nJetsFwd_JES_up;
  int _nBLoose_JES_up, _nBMed_JES_up, _nBTight_JES_up;
  JetInfos     _jetInfos_JES_down;
  SlimJetInfos _slimJetInfos_JES_down;
  int _nJets_JES_down, _nJetsCent_JES_down, _nJetsFwd_JES_down;
  int _nBLoose_JES_down, _nBMed_JES_down, _nBTight_JES_down;
  JetInfos     _jetInfos_JER_nom;
  SlimJetInfos _slimJetInfos_JER_nom;
  int _nJets_JER_nom, _nJetsCent_JER_nom, _nJetsFwd_JER_nom;
  int _nBLoose_JER_nom, _nBMed_JER_nom, _nBTight_JER_nom;
  JetInfos     _jetInfos_JER_up;
  SlimJetInfos _slimJetInfos_JER_up;
  int _nJets_JER_up, _nJetsCent_JER_up, _nJetsFwd_JER_up;
  int _nBLoose_JER_up, _nBMed_JER_up, _nBTight_JER_up;
  JetInfos     _jetInfos_JER_down;
  SlimJetInfos _slimJetInfos_JER_down;
  int _nJets_JER_down, _nJetsCent_JER_down, _nJetsFwd_JER_down;
  int _nBLoose_JER_down, _nBMed_JER_down, _nBTight_JER_down;

  int _nJetPairs;
  JetPairInfos _jetPairInfos;
  JetPairInfos _jetPairInfos_JES_up;
  JetPairInfos _jetPairInfos_JES_down;
  JetPairInfos _jetPairInfos_JER_nom;
  JetPairInfos _jetPairInfos_JER_up;
  JetPairInfos _jetPairInfos_JER_down;

  GenParentInfos _genParentInfos;
  int _nGenParents;
  GenMuonInfos _genMuonInfos;
  int _nGenMuons;
  GenMuPairInfos _genMuPairInfos;
  int _nGenMuPairs;
  GenJetInfos _genJetInfos;
  int _nGenJets;

  TLorentzVector _dMet;
  TLorentzVector _dMet_JES_up;
  TLorentzVector _dMet_JES_down;
  TLorentzVector _dMet_JER_nom;
  TLorentzVector _dMet_JER_up;
  TLorentzVector _dMet_JER_down;

  MetInfo _metInfo;
  MetInfo _metInfo_JES_up;
  MetInfo _metInfo_JES_down;
  MetInfo _metInfo_JER_nom;
  MetInfo _metInfo_JER_up;
  MetInfo _metInfo_JER_down;

  MhtInfo _mhtInfo;
  MhtInfo _mhtInfo_JES_up;
  MhtInfo _mhtInfo_JES_down;
  MhtInfo _mhtInfo_JER_nom;
  MhtInfo _mhtInfo_JER_up;
  MhtInfo _mhtInfo_JER_down;

  // Weights and efficiencies
  TFile* _IsoMu_eff_3_file;
  TFile* _IsoMu_eff_4_file;
  TFile* _MuID_eff_3_file;
  TFile* _MuID_eff_4_file;
  TFile* _MuIso_eff_3_file;
  TFile* _MuIso_eff_4_file;

  TH2F* _IsoMu_eff_3_hist;
  TH2F* _IsoMu_eff_4_hist;
  TH2F* _IsoMu_SF_3_hist;
  TH2F* _IsoMu_SF_4_hist;

  TH2F* _MuID_eff_3_hist;
  TH2F* _MuID_eff_4_hist;
  TH2F* _MuID_SF_3_hist;
  TH2F* _MuID_SF_4_hist;
  TH1F* _MuID_eff_3_vtx;
  TH1F* _MuID_eff_4_vtx;
  TH1F* _MuID_SF_3_vtx;
  TH1F* _MuID_SF_4_vtx;

  TH2F* _MuIso_eff_3_hist;
  TH2F* _MuIso_eff_4_hist;
  TH2F* _MuIso_SF_3_hist;
  TH2F* _MuIso_SF_4_hist;
  TH1F* _MuIso_eff_3_vtx;
  TH1F* _MuIso_eff_4_vtx;
  TH1F* _MuIso_SF_3_vtx;
  TH1F* _MuIso_SF_4_vtx;

  float  _IsoMu_eff_3;
  float  _IsoMu_eff_3_up;
  float  _IsoMu_eff_3_down;
  float  _IsoMu_eff_4;
  float  _IsoMu_eff_4_up;
  float  _IsoMu_eff_4_down;
  float  _IsoMu_eff_bug;
  float  _IsoMu_eff_bug_up;
  float  _IsoMu_eff_bug_down;

  float  _IsoMu_SF_3;
  float  _IsoMu_SF_3_up;
  float  _IsoMu_SF_3_down;
  float  _IsoMu_SF_4;
  float  _IsoMu_SF_4_up;
  float  _IsoMu_SF_4_down;
  float  _IsoMu_SF_bug;
  float  _IsoMu_SF_bug_up;
  float  _IsoMu_SF_bug_down;

  float  _MuID_eff_3;
  float  _MuID_eff_3_up;
  float  _MuID_eff_3_down;
  float  _MuID_eff_4;
  float  _MuID_eff_4_up;
  float  _MuID_eff_4_down;

  float  _MuID_SF_3;
  float  _MuID_SF_3_up;
  float  _MuID_SF_3_down;
  float  _MuID_SF_4;
  float  _MuID_SF_4_up;
  float  _MuID_SF_4_down;

  float  _MuIso_eff_3;
  float  _MuIso_eff_3_up;
  float  _MuIso_eff_3_down;
  float  _MuIso_eff_4;
  float  _MuIso_eff_4_up;
  float  _MuIso_eff_4_down;

  float  _MuIso_SF_3;
  float  _MuIso_SF_3_up;
  float  _MuIso_SF_3_down;
  float  _MuIso_SF_4;
  float  _MuIso_SF_4_up;
  float  _MuIso_SF_4_down;

  //json
  boost::property_tree::ptree _MuIso_SF_3_json;
  boost::property_tree::ptree _MuID_SF_3_json;

  ///////////////////////////////////////////////////////////
  // Trees  ================================================
  //////////////////////////////////////////////////////////

  // where to save all the info  
  TTree* _outTree;
  TTree* _outTreeMetadata;


private:

  ///////////////////////////////////////////////////////////
  // Inheritance from EDAnalyzer ===========================
  //////////////////////////////////////////////////////////

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  ///////////////////////////////////////////////////////////
  // Useful Functions ======================================
  //////////////////////////////////////////////////////////

  edm::Service<TFileService> fs;

  // methods for selection
  bool isHltPassed ( const edm::Event&, const edm::EventSetup&, 
		     const edm::Handle<edm::TriggerResults>& trigResultsHandle,
		     const std::vector<std::string> trigNames );

  void FillEventFlags( const edm::Event& iEvent, const edm::EventSetup& iSetup,
		       const edm::Handle<edm::TriggerResults>& evtFlagsHandle,
		       int& _Flag_all, int& _Flag_badMu, int& _Flag_dupMu, int& _Flag_halo,
		       int& _Flag_PV, int& _Flag_HBHE, int& _Flag_HBHE_Iso, int& _Flag_ECAL_TP, 
                       int& _Flag_BadChCand, int& _Flag_eeBadSc, int& _Flag_ecalBadCalib  );

  float calcHtLHE(const edm::Handle<LHEEventProduct>& LHE_handle);
  
  void displaySelection();

  static bool sortMuonsByPt (pat::Muon i,         pat::Muon j        );
  static bool sortElesByPt  (pat::Electron i,     pat::Electron j    );
  static bool sortPhotsByPt (reco::PFCandidate i, reco::PFCandidate j);
  static bool sortTausByPt  (pat::Tau i,          pat::Tau j         );
  static bool sortJetsByPt  (pat::Jet i,          pat::Jet j         );

  KalmanMuonCalibrator _KaMu_calib;
  bool _doSys_KaMu;
  RoccoR _Roch_calib;
  bool _doSys_Roch;

  EffectiveAreas muEffArea;
  EffectiveAreas eleEffArea;

  LepMVAVars _lepVars_mu;
  LepMVAVars _lepVars_ele;
  std::shared_ptr<TMVA::Reader> _lepMVA_mu;
  std::shared_ptr<TMVA::Reader> _lepMVA_ele;

  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  // Gather info from the python config file ==============
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////
  // Handles/Tokens  =======================================
  //////////////////////////////////////////////////////////
  // you get access to the information from the collections designated by the python config file
  // using the handle-token infrastructure. Get the name of the collection from the config
  // and load it into the token, then pass the token and the handle into the Event.

  // Trigger
  std::string _processName;
  std::vector<std::string> _trigNames;

  edm::EDGetTokenT<edm::TriggerResults> _trigResultsToken;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> _trigObjsToken;

  // Event flags
  edm::EDGetTokenT< edm::TriggerResults > _evtFlagsToken;
  
  // Muons
  edm::EDGetTokenT<pat::MuonCollection> _muonCollToken;

  // Electrons
  edm::EDGetTokenT<edm::View<pat::Electron>> _eleCollToken;
  std::string _eleIdVetoName;
  std::string _eleIdLooseName;
  std::string _eleIdMediumName;
  std::string _eleIdTightName;
  std::string _eleIdMvaWp90Name;
  std::string _eleIdMvaWp90NoIsoName;
  std::string _eleIdMvaWpLooseName;
  std::string _elePOGMvaName;

  // Taus
  edm::EDGetTokenT<pat::TauCollection> _tauCollToken;
  std::vector<std::string> _tauIDNames;

  // Jets / MET
  edm::EDGetTokenT<pat::JetCollection> _jetsToken;
  edm::EDGetTokenT<pat::METCollection> _metToken;
  edm::EDGetTokenT<double> _rhoToken;
  std::string _jetType;
  std::string _btagName;

  // PF candidates
  edm::EDGetTokenT<std::vector<pat::PackedCandidate>> _pfCandsToken;

  // Event info
  edm::EDGetTokenT<reco::BeamSpot> _beamSpotToken;		
  edm::EDGetTokenT<reco::VertexCollection> _primaryVertexToken;		
  edm::EDGetTokenT< std::vector< PileupSummaryInfo > > _PupInfoToken;		

  // Gen Info
  edm::EDGetTokenT<reco::GenJetCollection> _genJetsToken;
  edm::EDGetTokenT<reco::GenParticleCollection> _prunedGenParticleToken;		
  edm::EDGetTokenT<pat::PackedGenParticleCollection> _packedGenParticleToken;		
  edm::EDGetTokenT<GenEventInfoProduct> _genEvtInfoToken;		

  // LHE weights and info for MC
  edm::EDGetTokenT<LHEEventProduct> _LHE_token;

  ///////////////////////////////////////////////////////////
  // Basic types  ===========================================
  //////////////////////////////////////////////////////////

  // Selection Criteria for event and objects in config file
  bool _isVerbose;   
  bool _isMonteCarlo;
  bool _doSys;
  bool _slimOut;

  int  _skim_nMuons;
  int  _skim_nLeptons;
  bool _skim_trig;

  double _vertex_ndof_min;
  double _vertex_rho_max;
  double _vertex_z_max;

  std::string _muon_ID;
  double _muon_pT_min;
  double _muon_eta_max;
  double _muon_trig_dR;
  bool   _muon_use_pfIso;
  double _muon_iso_dR;
  double _muon_iso_max;

  std::string _muon_id_wp_num;// = "MediumID";
  std::string _muon_id_wp_den;// = "genTracks";
  std::string _muon_iso_wp_num;// = "LooseRelIso";
  std::string _muon_iso_wp_den;// = "MediumID";

  std::string _ele_ID;
  double _ele_pT_min;
  double _ele_eta_max;

  double _ele_missing_hits_barrel_max;
  double _ele_sigmaIEtaIEta_barrel_max;
  double _ele_hOverEm_barrel_max;
  double _ele_dEtaIn_barrel_max;
  double _ele_dPhiIn_barrel_max;
  double _ele_eInverseMinusPInverse_barrel_max;
  double _ele_eInverseMinusPInverse_barrel_min;

  double _ele_missing_hits_endcap_max;
  double _ele_sigmaIEtaIEta_endcap_max;
  double _ele_hOverEm_endcap_max;
  double _ele_dEtaIn_endcap_max;
  double _ele_dPhiIn_endcap_max;
  double _ele_eInverseMinusPInverse_endcap_max;
  double _ele_eInverseMinusPInverse_endcap_min;

  double _tau_pT_min;
  double _tau_eta_max;

  std::string _jet_ID;
  double _jet_pT_min;
  double _jet_eta_max;

  double _phot_pT_min;       
  double _phot_eta_max;      
  double _phot_dRPhoMu_max;  
  double _phot_dROverEt2_max; 
  double _phot_iso_dR;       
  double _phot_iso_max;      

  // Not currently used, since we don't use prescaled triggers with this analysis
  // Can probably delete these vars from the class
  std::vector < int > _l1Prescale;
  std::vector < int > _hltPrescale;
};

DEFINE_FWK_MODULE(UFDiMuonsAnalyzer);
#endif

