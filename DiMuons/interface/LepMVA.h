
#ifndef LEP_MVA
#define LEP_MVA

#include <memory>  // For shared_ptr

#include "TMVA/Reader.h"        // TMVA::Reader
#include "Math/LorentzVector.h" // ROOT::Math::LorentzVector

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/MuonInfo.h"
#include "Ntupliser/DiMuons/interface/EleInfo.h"

struct LepMVAVars {

  float pt                     = -999;
  float eta                    = -999;
  float trackMultClosestJet    = -999;
  float miniIsoCharged         = -999;
  float miniIsoNeutral         = -999;
  float ptRel                  = -999;
  float ptRatio                = -999;
  float relIso                 = -999;
  float deepCsvClosestJet      = -999;
  float sip3d                  = -999;
  float dxy                    = -999;
  float dz                     = -999;
  float electronMva            = -999;
  float electronMvaFall17NoIso = -999;
  float segmentCompatibility   = -999;

  void print () {
    std::cout << "pt                     = " << pt                     << std::endl;
    std::cout << "eta                    = " << eta                    << std::endl;
    std::cout << "trackMultClosestJet    = " << trackMultClosestJet    << std::endl;
    std::cout << "miniIsoCharged         = " << miniIsoCharged         << std::endl;
    std::cout << "miniIsoNeutral         = " << miniIsoNeutral         << std::endl;
    std::cout << "ptRel                  = " << ptRel                  << std::endl;
    std::cout << "ptRatio                = " << ptRatio                << std::endl;
    std::cout << "relIso                 = " << relIso                 << std::endl;
    std::cout << "deepCsvClosestJet      = " << deepCsvClosestJet      << std::endl;
    std::cout << "sip3d                  = " << sip3d                  << std::endl;
    std::cout << "dxy                    = " << dxy                    << std::endl;
    std::cout << "dz                     = " << dz                     << std::endl;
    std::cout << "electronMva            = " << electronMva            << std::endl;
    std::cout << "electronMvaFall17NoIso = " << electronMvaFall17NoIso << std::endl;
    std::cout << "segmentCompatibility   = " << segmentCompatibility   << std::endl;
  };

};


std::shared_ptr<TMVA::Reader> BookLepMVA( LepMVAVars & mvaVars, const std::string era, const std::string flav, const std::string xml );

void FillLepMVAVars( LepMVAVars & mvaVars, const MuonInfo & mu, const edm::Handle<pat::JetCollection>& jets, const reco::Vertex PV );
void FillLepMVAVars( LepMVAVars & mvaVars, const EleInfo & ele, const edm::Handle<pat::JetCollection>& jets, const reco::Vertex PV );

int JetTrackMultiplicity( const pat::Jet jet, const TLorentzVector lep_jet_vec, const reco::Vertex PV );


#endif  // #ifndef LEP_MVA
