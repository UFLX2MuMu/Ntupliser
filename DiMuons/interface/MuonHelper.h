
#ifndef MUON_HELPER
#define MUON_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/MuonInfo.h"
#include "Ntupliser/DiMuons/interface/PtCorrKalman.h"
#include "Ntupliser/DiMuons/interface/PtCorrRoch.h"
#include "Ntupliser/DiMuons/interface/KinematicFitMuonCorrections.h"
#include "Ntupliser/DiMuons/interface/GenMuonInfo.h"
// Classes or json handling
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include <iomanip> // setprecision

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
		    const GenMuonInfos _genMuonInfos );

pat::MuonCollection SelectMuons( const edm::Handle<pat::MuonCollection>& muons,
				 const reco::Vertex primaryVertex, const std::string _muon_ID,
				 const double _muon_pT_min, const double _muon_eta_max, const double _muon_trig_dR,
				 const bool _muon_use_pfIso, const double _muon_iso_dR, const double _muon_iso_max );

bool MuonIsLoose ( const pat::Muon muon );
bool MuonIsMedium( const pat::Muon muon );
bool MuonIsTight ( const pat::Muon muon, const reco::Vertex primaryVertex );

double MuonCalcRelIsoPF ( const pat::Muon muon, const double _muon_iso_dR );
double MuonCalcRelIsoTrk( const pat::Muon muon, const double _muon_iso_dR );
double MuonCalcTrigEff  ( const pat::Muon muon, const int _nPV, const std::string _trigName );

bool IsHltMatched( const pat::Muon& mu, const edm::Event& iEvent, const edm::EventSetup& iSetup,
		   const edm::Handle<pat::TriggerObjectStandAloneCollection>& _trigObjsHandle,
		   const edm::Handle<edm::TriggerResults>& _trigResultsHandle,
		   const std::string _desiredTrigName, const double _muon_trig_dR );

void CalcTrigEff( float& _muon_eff, float& _muon_eff_up, float& _muon_eff_down,
		  const TH2F* _muon_eff_hist, const MuonInfos _muonInfos, const bool EMTF_bug );

float CalcL1TPhi( const float mu_pt, const float mu_eta, float mu_phi, const int mu_charge );
bool SameSector( float phi1, float phi2 );
float CalcDPhi( const float phi1, const float phi2 );

void CalcMuIDIsoEff( float& _ID_eff, float& _ID_eff_up, float& _ID_eff_down, std::string _id_wp_num, std::string _id_wp_den,
                     float& _Iso_eff, float& _Iso_eff_up, float& _Iso_eff_down, std::string _iso_wp_num, std::string _iso_wp_den,
                     const boost::property_tree::ptree _iso_json, const boost::property_tree::ptree _id_json, 
                     const MuonInfos _muonInfos );

void CalcMuIDIsoEff( float& _ID_eff, float& _ID_eff_up, float& _ID_eff_down,
                     float& _Iso_eff, float& _Iso_eff_up, float& _Iso_eff_down,
                     const TH2F* _ID_hist, const TH2F* _Iso_hist,
                     const TH1F* _ID_vtx, const TH1F* _Iso_vtx,
                     const MuonInfos _muonInfos, const int _nVtx );

#endif  // #ifndef MUON_HELPER
