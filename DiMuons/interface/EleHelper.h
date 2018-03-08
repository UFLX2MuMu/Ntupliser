
#ifndef ELE_HELPER
#define ELE_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/EleInfo.h"

void FillEleInfos( EleInfos& _eleInfos,
		   const pat::ElectronCollection elesSelected,
		   const reco::Vertex primaryVertex, const edm::Event& iEvent,
		   const std::vector<std::array<bool, 4>> ele_ID_pass );

pat::ElectronCollection SelectEles( const edm::Handle<edm::View<pat::Electron>>& eles, const reco::Vertex primaryVertex,
				    const edm::Handle< edm::ValueMap<bool> >& ele_id_veto, const edm::Handle< edm::ValueMap<bool> >& ele_id_loose,
				    const edm::Handle< edm::ValueMap<bool> >& ele_id_medium, const edm::Handle< edm::ValueMap<bool> >& ele_id_tight,
				    const std::string _ele_ID, const double _ele_pT_min, const double _ele_eta_max, 
				    std::vector<std::array<bool, 4>>& ele_ID_pass);

bool   ElePassKinematics( const pat::Electron ele, const reco::Vertex primaryVertex );
double EleCalcRelIsoPF_DeltaBeta( const pat::Electron ele );

#endif  // #ifndef ELE_HELPER
