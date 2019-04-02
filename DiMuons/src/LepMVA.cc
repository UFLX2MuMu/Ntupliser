
#include "Ntupliser/DiMuons/interface/LepMVA.h"

// Book BDTs for distinguishing prompt from non-prompt leptons, using TOP-18-008 lepMVA
// From https://github.com/wverbeke/ewkino/blob/tZq/src/skimmer.cc#L64

std::shared_ptr<TMVA::Reader> BookLepMVA( LepMVAVars & mvaVars, const std::string era, const std::string flav, const std::string xml ) {

  // 2016 and 2017 trainings for electrons or muons
  assert(era == "2016" || era == "2017");
  assert(flav == "ele" || flav == "mu");

  std::shared_ptr<TMVA::Reader> mvaRead = std::make_shared<TMVA::Reader>( "!Color:!Silent");

  // Add variables to the reader
  mvaRead->AddVariable( "pt", &mvaVars.pt );
  mvaRead->AddVariable( "eta", &mvaVars.eta );
  mvaRead->AddVariable( "trackMultClosestJet", &mvaVars.trackMultClosestJet );
  mvaRead->AddVariable( "miniIsoCharged", &mvaVars.miniIsoCharged );
  mvaRead->AddVariable( "miniIsoNeutral", &mvaVars.miniIsoNeutral );
  mvaRead->AddVariable( "pTRel", &mvaVars.ptRel );
  mvaRead->AddVariable( "ptRatio", &mvaVars.ptRatio );
  mvaRead->AddVariable( "relIso", &mvaVars.relIso );
  mvaRead->AddVariable( "deepCsvClosestJet", &mvaVars.deepCsvClosestJet );
  mvaRead->AddVariable( "sip3d", &mvaVars.sip3d );
  mvaRead->AddVariable( "dxy", &mvaVars.dxy );
  mvaRead->AddVariable( "dz", &mvaVars.dz );
  if (flav == "ele") {
    if (era == "2016") {
      mvaRead->AddVariable( "electronMvaSpring16GP", &mvaVars.electronMva );
    } else {
      mvaRead->AddVariable( "electronMvaFall17NoIso", &mvaVars.electronMvaFall17NoIso );
    }
  } else {
    mvaRead->AddVariable( "segmentCompatibility", &mvaVars.segmentCompatibility );
  }

  // Book the BDT
  mvaRead->BookMVA("BDTG method", xml);

  return mvaRead;
}


// Fill input variables to lepMVA from muon or electron and jets, following:
// https://github.com/wverbeke/ewkino/blob/tZq/src/skimmer.cc#L128
// https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/src/LeptonAnalyzer.cc#L391
void FillLepMVAVars( LepMVAVars & vars, const MuonInfo & mu,
		     const edm::Handle<pat::JetCollection>& jets,
		     const reco::Vertex PV ) {

  if ( !jets.isValid() ) {
    std::cout << "No valid jet collection" << std::endl;
    return;
  }

  vars.pt                     = mu.pt;
  vars.eta                    = fabs(mu.eta);
  vars.trackMultClosestJet    = 0;     // Jet variable, filled below
  vars.miniIsoCharged         = mu.miniIsoCharged;
  vars.miniIsoNeutral         = mu.miniIso - mu.miniIsoCharged;
  vars.ptRel                  = 0;     // Jet variable, filled below
  vars.ptRatio                = 1;     // Jet variable, filled below
  vars.relIso                 = mu.relIsoEA03;  // dR = 0.3, EffectiveArea (rho-based) PU correction
  vars.deepCsvClosestJet      = 0;     // Jet variable, filled below
  vars.sip3d                  = mu.SIP_3D;
  vars.dxy                    = log(fabs(mu.d0_PV));
  vars.dz                     = log(fabs(mu.dz_PV));
  vars.electronMva            = -999;  // For 2016 electrons only
  vars.electronMvaFall17NoIso = -999;  // For 2017 electrons only
  vars.segmentCompatibility   = mu.segCompat;

  TLorentzVector mu_vec;
  mu_vec.SetPtEtaPhiM( mu.pt, mu.eta, mu.phi, 0.105658367 );
  ROOT::Math::LorentzVector< ROOT::Math::PxPyPzE4D<double> > mu_p4 ( mu_vec.Px(), mu_vec.Py(), mu_vec.Pz(), mu_vec.E() );

  float min_dR = 999;
  for (pat::JetCollection::const_iterator jet = jets->begin(), jetsEnd = jets->end(); jet !=jetsEnd; ++jet) {
    
    if (jet->pt() < 5 || fabs(jet->eta()) > 3) continue;

    auto jet_p4     = jet->p4();  // I *think* this "auto" is a ROOT::Math::LorentzVector< ROOT::Math::PxPyPzE4D<double> >
    auto l1_jet_p4  = jet->correctedP4("L1FastJet");  // Not really sure what this is - AWB 15.10.2018
    auto mu_jet_p4 = (l1_jet_p4 - mu_p4)*(jet_p4.E() / l1_jet_p4.E()) + mu_p4;

    TLorentzVector jet_vec    ( jet_p4.Px(),    jet_p4.Py(),    jet_p4.Pz(),    jet_p4.E()    );
    TLorentzVector l1_jet_vec ( l1_jet_p4.Px(), l1_jet_p4.Py(), l1_jet_p4.Pz(), l1_jet_p4.E() );
    TLorentzVector mu_jet_vec ( mu_jet_p4.Px(), mu_jet_p4.Py(), mu_jet_p4.Pz(), mu_jet_p4.E() );

    pat::Jet jet_tmp = (*jet);
    if (mu_vec.DeltaR(jet_vec) < min_dR) {
      min_dR = mu_vec.DeltaR(jet_vec);

      vars.trackMultClosestJet = JetTrackMultiplicity(jet_tmp, mu_jet_vec, PV);
      vars.ptRel               = mu_jet_vec.Perp((mu_jet_vec - mu_vec).Vect());
      vars.ptRatio             = mu_vec.Pt() / mu_jet_vec.Pt();
      vars.deepCsvClosestJet   = std::fmax( 0.0, jet->bDiscriminator("pfDeepCSVJetTags:probb") +
    					         jet->bDiscriminator("pfDeepCSVJetTags:probbb") );
    } // End conditional: if (mu_vec.DeltaR(jet_vec) < min_dR)

  } // End loop: for (const auto jet : jets)

} // End function: FillLepMVAVars( LepMVAVars & vars, const MuonInfo & mu, edm::Handle<std::vector<pat::Jet>>& jets, const reco::Vertex PV )

void FillLepMVAVars( LepMVAVars & vars, const EleInfo & ele,
		     const edm::Handle<pat::JetCollection>& jets,
		     const reco::Vertex PV ) {
  
  if ( !jets.isValid() ) {
    std::cout << "No valid jet collection" << std::endl;
    return;
  }

  vars.pt                     = ele.pt;
  vars.eta                    = fabs(ele.eta);
  vars.trackMultClosestJet    = 0;     // Jet variable, filled below
  vars.miniIsoCharged         = ele.miniIsoCharged;
  vars.miniIsoNeutral         = ele.miniIso - ele.miniIsoCharged;
  vars.ptRel                  = 0;     // Jet variable, filled below
  vars.ptRatio                = 1;     // Jet variable, filled below
  vars.relIso                 = ele.relIsoEA;  // dR = 0.3, EffectiveArea (rho-based) PU correction
  vars.deepCsvClosestJet      = 0;     // Jet variable, filled below
  vars.sip3d                  = ele.SIP_3D;
  vars.dxy                    = log(fabs(ele.d0_PV));
  vars.dz                     = log(fabs(ele.dz_PV));
  vars.electronMva            = ele.mvaID;  // "electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Values"
  vars.electronMvaFall17NoIso = ele.mvaID;  // "electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17NoIsoV1Values"
  vars.segmentCompatibility   = -999;  // For muons only

  TLorentzVector ele_vec;
  ele_vec.SetPtEtaPhiM( ele.pt, ele.eta, ele.phi, 0.105658367 );
  ROOT::Math::LorentzVector< ROOT::Math::PxPyPzE4D<double> > ele_p4 ( ele_vec.Px(), ele_vec.Py(), ele_vec.Pz(), ele_vec.E() );

  float min_dR = 999;
  for (pat::JetCollection::const_iterator jet = jets->begin(), jetsEnd = jets->end(); jet !=jetsEnd; ++jet) {
    
    if (jet->pt() < 5 || fabs(jet->eta()) > 3) continue;

    auto jet_p4     = jet->p4();  // I *think* this "auto" is a ROOT::Math::LorentzVector< ROOT::Math::PxPyPzE4D<double> >
    auto l1_jet_p4  = jet->correctedP4("L1FastJet");  // Not really sure what this is - AWB 15.10.2018
    auto ele_jet_p4 = (l1_jet_p4 - ele_p4)*(jet_p4.E() / l1_jet_p4.E()) + ele_p4;

    TLorentzVector jet_vec     ( jet_p4.Px(),     jet_p4.Py(),     jet_p4.Pz(),     jet_p4.E()     );
    TLorentzVector l1_jet_vec  ( l1_jet_p4.Px(),  l1_jet_p4.Py(),  l1_jet_p4.Pz(),  l1_jet_p4.E()  );
    TLorentzVector ele_jet_vec ( ele_jet_p4.Px(), ele_jet_p4.Py(), ele_jet_p4.Pz(), ele_jet_p4.E() );

    pat::Jet jet_tmp = (*jet);
    if (ele_vec.DeltaR(jet_vec) < min_dR) {
      min_dR = ele_vec.DeltaR(jet_vec);

      vars.trackMultClosestJet = JetTrackMultiplicity(jet_tmp, ele_jet_vec, PV);
      vars.ptRel               = ele_jet_vec.Perp((ele_jet_vec - ele_vec).Vect());
      vars.ptRatio             = ele_vec.Pt() / ele_jet_vec.Pt();
      vars.deepCsvClosestJet   = std::fmax( 0.0, jet->bDiscriminator("pfDeepCSVJetTags:probb") +
    					         jet->bDiscriminator("pfDeepCSVJetTags:probbb") );
    } // End conditional: if (ele_vec.DeltaR(jet_vec) < min_dR)
    
  } // End loop: for (const auto jet : jets)

} // End function: FillLepMVAVars( LepMVAVars & vars, const EleInfo & ele, const edm::Handle<pat::JetCollection>& jets, const reco::Vertex PV )


// Compute selected track multiplicity of closest jet, from
// https://github.com/GhentAnalysis/heavyNeutrino/blob/master/multilep/src/LeptonAnalyzer.cc#L435
int JetTrackMultiplicity( const pat::Jet jet, const TLorentzVector lep_jet_vec, const reco::Vertex PV ) {

  int trkMult = 0; // Number of tracks in jet?

  for (uint iDtr = 0; iDtr < jet.numberOfDaughters(); iDtr++) {
    const pat::PackedCandidate* dtr = (const pat::PackedCandidate*) jet.daughter(iDtr);

    if ( !dtr->hasTrackDetails() ) continue;

    const reco::Track & dtrTrk = dtr->pseudoTrack();

    // Good track fit
    if ( dtrTrk.charge()                              == 0 ||
	 dtrTrk.hitPattern().numberOfValidHits()      <= 7 ||
	 dtrTrk.hitPattern().numberOfValidPixelHits() <= 1 ||
	 dtrTrk.normalizedChi2() >= 5 ) continue;
    
    // Track from PV
    if ( fabs( dtrTrk.dz (PV.position()) ) >= 17 ||
	 fabs( dtrTrk.dxy(PV.position()) ) >= 0.2 ) continue;

    // Distance from jet core
    TLorentzVector trk_vec ( dtrTrk.px(), dtrTrk.py(), dtrTrk.pz(), dtrTrk.p() );
    double dtrDeltaR = trk_vec.DeltaR(lep_jet_vec);

    // Good track
    if ( dtrTrk.pt() > 1 && dtrDeltaR < 0.4 && dtr->fromPV() > 1 )
      trkMult += 1;

  } // End loop: for (uint iDtr = 0; iDtr < jet.numberOfDaughters(); iDtr++)

  return trkMult;

} // End function: float JetTrackMultiplicity( pat::Jet & jet, const TLorentzVector lep_jet_vec ) {
