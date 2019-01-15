
#ifndef ELE_HELPER
#define ELE_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/EleInfo.h"
#include "Ntupliser/DiMuons/interface/LepMVA.h"

void FillEleInfos( EleInfos& _eleInfos,
		   const pat::ElectronCollection elesSelected,
		   const reco::Vertex primaryVertex, const edm::Event& iEvent,
		   const std::array<std::string, 5> ele_ID_names,
		   LepMVAVars & _lepVars_ele, std::shared_ptr<TMVA::Reader> & _lepMVA_ele,
		   const double _rho, const edm::Handle<pat::JetCollection>& jets,
		   const edm::Handle<pat::PackedCandidateCollection> pfCands,
		   EffectiveAreas eleEffArea );


pat::ElectronCollection SelectEles( const edm::Handle<edm::View<pat::Electron>>& eles, const reco::Vertex primaryVertex,
				    const std::array<std::string, 5> ele_ID_names, const std::string _ele_ID,
				    const double _ele_pT_min, const double _ele_eta_max );

bool   ElePassKinematics( const pat::Electron ele, const reco::Vertex primaryVertex );
double EleCalcRelIsoPF  ( const pat::Electron ele, const double rho, EffectiveAreas eleEffArea, const std::string type );
double EleCalcMiniIso   ( const pat::Electron ele, const edm::Handle<pat::PackedCandidateCollection> pfCands,
			  const double rho, EffectiveAreas eleEffArea, const bool charged );


#endif  // #ifndef ELE_HELPER
