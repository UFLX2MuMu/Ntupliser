
#ifndef JET_HELPER
#define JET_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/JetInfo.h"
#include "Ntupliser/DiMuons/interface/MuonInfo.h"
#include "Ntupliser/DiMuons/interface/EleInfo.h"

void FillJetInfos( JetInfos& _jetInfos, int& _nJetsFwd,
		   int& _nBLoose, int& _nBMed, int& _nBTight,
		   const pat::JetCollection jetsSelected, 
		   const std::string _btagName, const int _year );

void FillSlimJetInfos( SlimJetInfos& _slimJetInfos, const JetInfos _jetInfos );

pat::JetCollection SelectJets( const edm::Handle<pat::JetCollection>& jets,
			       const JetCorrectorParameters& JetCorPar, JME::JetResolution& JetRes,
                               JME::JetResolutionScaleFactor& JetResSF, const std::string _JES_syst,
			       const MuonInfos& _muonInfos, const EleInfos& _eleInfos, const double _rho,
			       const std::string _jet_ID, const double _jet_pT_min, const double _jet_eta_max,
			       const int _year, TLorentzVector& _dMet );

#endif  // #ifndef JET_HELPER
