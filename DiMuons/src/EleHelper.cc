
#include "Ntupliser/DiMuons/interface/EleHelper.h"

void FillEleInfos( EleInfos& _eleInfos, 
		   const pat::ElectronCollection elesSelected,
		   const reco::Vertex primaryVertex, const edm::Event& iEvent,
		   const std::vector<std::array<bool, 4>> ele_ID_pass ) {
  
  _eleInfos.clear();
  int nEles = elesSelected.size();
  
  for (int i = 0; i < nEles; i++) {
    
    pat::Electron ele  = elesSelected.at(i);
    EleInfo _eleInfo;
    _eleInfo.init();

    // Basic kinematics
    _eleInfo.charge = ele.charge();
    _eleInfo.pt     = ele.pt();
    _eleInfo.eta    = ele.eta();
    _eleInfo.phi    = ele.phi();

    // Basic quality
    _eleInfo.isPF       = ele.isPF();
    _eleInfo.isVetoID   = ele_ID_pass.at(i)[0];
    _eleInfo.isLooseID  = ele_ID_pass.at(i)[1];
    _eleInfo.isMediumID = ele_ID_pass.at(i)[2];
    _eleInfo.isTightID  = ele_ID_pass.at(i)[3];

    // Basic isolation
    _eleInfo.relIso = EleCalcRelIsoPF_DeltaBeta( ele );

    // Basic vertexing?

    // Efficiencies and scale factors?
    // https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2#Electron_efficiencies_and_scale

    // // -------------------------
    // // ONLY SAVE BASIC VARIABLES - AWB 12.11.16
    // // -------------------------
    // if ( _outputLevel == "Slim")
    //   continue;

    // Standard quality
    _eleInfo.passConversionVeto = ele.passConversionVeto();
    _eleInfo.missingInnerHits   = ele.gsfTrack()->hitPattern().numberOfAllHits(reco::HitPattern::MISSING_INNER_HITS);

    // Standard vertexing
    _eleInfo.d0_PV = ele.gsfTrack()->dxy( primaryVertex.position() );
    _eleInfo.dz_PV = ele.gsfTrack()->dz ( primaryVertex.position() );

    // Standard isolation
    _eleInfo.sumChargedHadronPtR03 = ele.pfIsolationVariables().sumChargedHadronPt;
    _eleInfo.sumNeutralHadronEtR03 = ele.pfIsolationVariables().sumNeutralHadronEt;
    _eleInfo.sumPhotonEtR03        = ele.pfIsolationVariables().sumPhotonEt;
    _eleInfo.sumPUPtR03            = ele.pfIsolationVariables().sumPUPt;

    _eleInfos.push_back( _eleInfo );
  } // End loop: for (int i = 0; i < nEles; i++)

}


pat::ElectronCollection SelectEles( const edm::Handle<edm::View<pat::Electron>>& eles, const reco::Vertex primaryVertex,
				    const edm::Handle< edm::ValueMap<bool> >& ele_id_veto, const edm::Handle< edm::ValueMap<bool> >& ele_id_loose,
				    const edm::Handle< edm::ValueMap<bool> >& ele_id_medium, const edm::Handle< edm::ValueMap<bool> >& ele_id_tight,
				    const std::string _ele_ID, const double _ele_pT_min, const double _ele_eta_max,
				    std::vector<std::array<bool, 4>>& ele_ID_pass ) {
  
  // Main Egamma POG page: https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPOG
  // Following https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2
  //       and https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2#Working_points_for_2016_data_for
  // Modeled after https://github.com/ikrav/EgammaWork/blob/ntupler_and_VID_demos_8.0.3/ElectronNtupler/plugins/ElectronNtuplerVIDDemo.cc
  
  pat::ElectronCollection elesSelected;
  elesSelected.clear();
  ele_ID_pass.clear();

  if ( !eles.isValid() ) {
    std::cout << "No valid electron collection" << std::endl;
    return elesSelected;
  }
  if ( !ele_id_veto.isValid() || !ele_id_loose.isValid() || !ele_id_medium.isValid() || !ele_id_tight.isValid() ) {
    std::cout << "No valid electron ID" << std::endl;
    return elesSelected;
  }

  if ( _ele_ID.find("veto")   == std::string::npos && _ele_ID.find("loose") == std::string::npos && 
       _ele_ID.find("medium") == std::string::npos && _ele_ID.find("tight") == std::string::npos )
    std::cout << "Ele ID is neither tight, medium, loose, nor tight: " << _ele_ID
              << "\nWill not be used, no electron ID cuts applied" << std::endl;

  for (size_t i = 0; i < eles->size(); ++i) {
    
    const auto ele = eles->ptrAt(i);

    if ( ele->pt()          < _ele_pT_min  ) continue;
    if ( fabs( ele->eta() ) > _ele_eta_max ) continue;

    bool _isVeto   = (*ele_id_veto  )[ele] && ElePassKinematics(*ele, primaryVertex);
    bool _isLoose  = (*ele_id_loose )[ele] && ElePassKinematics(*ele, primaryVertex);
    bool _isMedium = (*ele_id_medium)[ele] && ElePassKinematics(*ele, primaryVertex);
    bool _isTight  = (*ele_id_tight )[ele] && ElePassKinematics(*ele, primaryVertex);

    if (_ele_ID.find("veto")   != std::string::npos && !_isVeto)   continue;
    if (_ele_ID.find("loose")  != std::string::npos && !_isLoose)  continue;
    if (_ele_ID.find("medium") != std::string::npos && !_isMedium) continue;
    if (_ele_ID.find("tight")  != std::string::npos && !_isTight)  continue;

    elesSelected.push_back(*ele);
    ele_ID_pass.push_back( {{_isVeto, _isLoose, _isMedium, _isTight}} );

  }
  
  return elesSelected;
}

bool ElePassKinematics( const pat::Electron ele, const reco::Vertex primaryVertex ) {

  double SC_eta = -999.;
  if ( ele.superCluster().isAvailable() )
    SC_eta = fabs( ele.superCluster()->position().eta() );
  bool isBarrel = ( SC_eta != -999 && SC_eta < 1.479 );
  // bool inCrack  = ( SC_eta != -999 && SC_eta > 1.4442 && SC_eta < 1.5660 );
  
  double dXY = -999.;
  double dZ  = -999.;
  if ( ele.gsfTrack().isAvailable() ) {
    dXY = fabs( ele.gsfTrack()->dxy( primaryVertex.position() ) );
    dZ  = fabs( ele.gsfTrack()->dz ( primaryVertex.position() ) );
  }
  
  // For 2016: https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2#Working_points_for_2016_data_for
  // For 2017: https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2#Offline_selection_criteria_for_V
  // Different than https://github.com/cms-ttH/MiniAOD/blob/master/MiniAODHelper/src/MiniAODHelper.cc#L895
  bool passDXY = dXY != -999 && ( isBarrel ? (dXY < 0.05) : (dXY < 0.10 ) );
  bool passDZ  = dZ  != -999 && ( isBarrel ? (dZ  < 0.10) : (dZ  < 0.20 ) );

  return (passDXY && passDZ);  // Is this really all we need? - AWB 16.01.17
  // // What about !inCrack? passMVAId53x? no_exp_inner_trkr_hits? myTrigPresel? - AWB 15.11.16
  // // https://github.com/cms-ttH/MiniAOD/blob/master/MiniAODHelper/src/MiniAODHelper.cc#L900
  // return (passDXY && passDZ && ele.passConversionVeto() && !inCrack);
  // // Does ele->passConversionVeto() return the same thing as ConversionTools::hasMatchedConversion? - AWB 15.11.16
  // // https://github.com/ikrav/EgammaWork/blob/ntupler_and_VID_demos_8.0.3/ElectronNtupler/plugins/ElectronNtuplerVIDDemo.cc#L358
}

double EleCalcRelIsoPF_DeltaBeta( const pat::Electron ele ) {
  // Following https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPFBasedIsolationRun2
  // Using Delta Beta corrections - simpler, only slightly worse performance
  // Last check that cuts were up-to-date: August 9, 2018 (AWB)
  
  double iso_charged    = ele.pfIsolationVariables().sumChargedHadronPt;
  double iso_neutral    = ele.pfIsolationVariables().sumNeutralHadronEt;
  double iso_photon     = ele.pfIsolationVariables().sumPhotonEt;
  double iso_PU_charged = ele.pfIsolationVariables().sumPUPt;
  
  double rel_iso = iso_charged;
  rel_iso += std::max( 0.0, iso_neutral + iso_photon - (0.5 * iso_PU_charged) );
  rel_iso /= ele.pt();
  
  return rel_iso;
}
