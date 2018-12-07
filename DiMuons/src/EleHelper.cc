
#include "Ntupliser/DiMuons/interface/EleHelper.h"

void FillEleInfos( EleInfos& _eleInfos, 
		   const pat::ElectronCollection elesSelected,
		   const reco::Vertex primaryVertex, const edm::Event& iEvent,
		   const std::vector<std::array<bool, 4>> ele_ID_pass, const double ele_mva_val,
		   LepMVAVars & _lepVars_ele, std::shared_ptr<TMVA::Reader> & _lepMVA_ele,
                   const double _rho, const edm::Handle<pat::JetCollection>& jets,
                   const edm::Handle<pat::PackedCandidateCollection> pfCands,
                   EffectiveAreas eleEffArea ) {
  
  _eleInfos.clear();
  int nEles = elesSelected.size();
  
  for (int i = 0; i < nEles; i++) {

    pat::Electron ele  = elesSelected.at(i);
    EleInfo _eleInfo;

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

    // EGamma POG MVA quality
    _eleInfo.mvaID = ele_mva_val;

    // Basic isolation
    _eleInfo.relIso         = EleCalcRelIsoPF( ele, _rho, eleEffArea, "DeltaBeta" );
    _eleInfo.relIsoEA       = EleCalcRelIsoPF( ele, _rho, eleEffArea, "EffArea" );
    _eleInfo.miniIso        = EleCalcMiniIso ( ele, pfCands, _rho, eleEffArea, false );
    _eleInfo.miniIsoCharged = EleCalcMiniIso ( ele, pfCands, _rho, eleEffArea, true );


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
    _eleInfo.d0_PV  = ele.gsfTrack()->dxy( primaryVertex.position() );
    _eleInfo.dz_PV  = ele.gsfTrack()->dz ( primaryVertex.position() );
    _eleInfo.IP_3D  = ele.dB(pat::Electron::PV3D);
    _eleInfo.SIP_3D = fabs( ele.dB(pat::Electron::PV3D) / ele.edB(pat::Electron::PV3D) );

    // Standard isolation
    _eleInfo.sumChargedHadronPtR03 = ele.pfIsolationVariables().sumChargedHadronPt;
    _eleInfo.sumNeutralHadronEtR03 = ele.pfIsolationVariables().sumNeutralHadronEt;
    _eleInfo.sumPhotonEtR03        = ele.pfIsolationVariables().sumPhotonEt;
    _eleInfo.sumPUPtR03            = ele.pfIsolationVariables().sumPUPt;


    // Fill lepMVA input variables
    // https://github.com/wverbeke/ewkino/blob/tZq/src/skimmer.cc#L128
    FillLepMVAVars( _lepVars_ele, _eleInfo, jets, primaryVertex );
    // Evaluate the lepMVA
    _eleInfo.lepMVA = _lepMVA_ele->EvaluateMVA("BDTG method");
    // Fill the remaining lepMVA input variables
    _eleInfo.jet_trkMult = _lepVars_ele.trackMultClosestJet;
    _eleInfo.jet_ptRel   = _lepVars_ele.ptRel;
    _eleInfo.jet_ptRatio = _lepVars_ele.ptRatio;
    _eleInfo.jet_deepCSV = _lepVars_ele.deepCsvClosestJet;

    // std::cout << "LepMVA input variables for electron:" << std::endl;
    // _lepVars_ele.print();
    // std::cout << "LepMVA output value = " << _eleInfo.lepMVA << std::endl;

    _eleInfos.push_back( _eleInfo );
  } // End loop: for (int i = 0; i < nEles; i++)

}


pat::ElectronCollection SelectEles( const edm::Handle<edm::View<pat::Electron>>& eles, const reco::Vertex primaryVertex,
				    const edm::Handle< edm::ValueMap<bool> >& ele_id_veto, const edm::Handle< edm::ValueMap<bool> >& ele_id_loose,
				    const edm::Handle< edm::ValueMap<bool> >& ele_id_medium, const edm::Handle< edm::ValueMap<bool> >& ele_id_tight,
				    const edm::Handle< edm::ValueMap<float> >& ele_id_mva, const std::string _ele_ID,
				    const double _ele_pT_min, const double _ele_eta_max,
				    std::vector<std::array<bool, 4>>& ele_ID_pass, double & ele_mva_val ) {
  
  // Main Egamma POG page: https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPOG
  // Following https://twiki.cern.ch/twiki/bin/view/CMS/EgammaIDRecipesRun2
  //       and https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Recipe_for_regular_users_formats
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
    ele_mva_val    = (*ele_id_mva   )[ele];

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
  
  // From https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Electron_ID_Working_Points_WP_de
  // Different than https://github.com/cms-ttH/MiniAOD/blob/master/MiniAODHelper/src/MiniAODHelper.cc#L890
  bool passDXY = dXY != -999 && ( isBarrel ? (dXY < 0.05) : (dXY < 0.10 ) );
  bool passDZ  = dZ  != -999 && ( isBarrel ? (dZ  < 0.10) : (dZ  < 0.20 ) );

  return (passDXY && passDZ );  // Is this really all we need? - AWB 16.01.17
  // // What about passMVAId53x? no_exp_inner_trkr_hits? myTrigPresel? - AWB 15.11.16
  // return (passDXY && passDZ && ele.passConversionVeto() && !inCrack);
  // // Does ele->passConversionVeto() return the same thing as ConversionTools::hasMatchedConversion? - AWB 15.11.16
  // // https://github.com/ikrav/EgammaWork/blob/ntupler_and_VID_demos_8.0.3/ElectronNtupler/plugins/ElectronNtuplerVIDDemo.cc#L358
}  
  

double EleCalcRelIsoPF( const pat::Electron ele, const double rho,
                         EffectiveAreas eleEffArea, const std::string type ) {
  // Following https://twiki.cern.ch/twiki/bin/view/CMS/EgammaPFBasedIsolationRun2 and
  // https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/src/LeptonAnalyzerIso.cc#L29
  // Last check that cuts were up-to-date: 18.10.2018 - AWB
  
  // Electron isolation cone radius is always 0.3
   assert(type == "DeltaBeta" || type == "EffArea");

  double iso = -999;
  float  PU  = -999;

  if      (type == "DeltaBeta") PU = 0.5 * ele.pfIsolationVariables().sumPUPt;
  else if (type == "EffArea")   PU = rho * eleEffArea.getEffectiveArea( ele.eta() );
  PU   = 0.5 * ele.pfIsolationVariables().sumPUPt;
  iso  = ele.pfIsolationVariables().sumChargedHadronPt;
  iso += std::fmax( 0., ele.pfIsolationVariables().sumNeutralHadronEt + ele.pfIsolationVariables().sumPhotonEt - PU );

  return (iso / ele.pt() );
} // End function: EleCalcRelIsoPF()


double EleCalcMiniIso( const pat::Electron ele, const edm::Handle<pat::PackedCandidateCollection> pfCands,
		       const double rho, EffectiveAreas eleEffArea, const bool charged ) {
  // Following https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/src/LeptonAnalyzerIso.cc#L79
  //       and https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/src/LeptonAnalyzerIso.cc#L36
  
  // Variable cone size based on electron pT: from 0.2 at low pT (<= 5 GeV) up to 0.05 (>= 200 GeV)
  double max_pt   = 10.0 / 0.05;  // kT scale (GeV) / dR_min
  double min_pt   = 10.0 / 0.20;  // kT scale (GeV) / dR_max
  double coneSize = 10.0 / std::fmax(std::min(ele.pt(), max_pt), min_pt);

  double dR_nh(0.0), dR_ch(0.015), dR_ph(0.08), dR_pu(0.015);  // Candidates not considered if they're too close to the electron
  if ( fabs(ele.superCluster()->eta()) < 1.479 ) { dR_ch = 0; dR_ph = 0; dR_pu = 0; }  // No cut in the barrel
  double iso_nh(0.0), iso_ch(0.0), iso_ph(0.0), iso_pu(0.0);    // Separate isolation quantities by PF candidate type
  double minPt = 0.0;

  for (const pat::PackedCandidate & pfc : *pfCands) {

    if (fabs(pfc.pdgId()) < 7) continue;  // What does this do? - AWB 15.10.2018

    double dR = deltaR(pfc, ele);
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

  double puCorr = rho * eleEffArea.getEffectiveArea( ele.superCluster()->eta() );

  double iso  = iso_ch;
  if (!charged) iso += std::fmax(0., iso_ph + iso_nh - puCorr * pow(coneSize / 0.3, 2));

  return ( iso / ele.pt() );
}
