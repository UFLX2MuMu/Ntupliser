
#include "Ntupliser/DiMuons/interface/MhtHelper.h"

void FillMhtInfo( MhtInfo& _mhtInfo, const MuonInfos _muonInfos,
		  const EleInfos _eleInfos, const JetInfos _jetInfos ) {
  
  _mhtInfo.init();
  
  double const MASS_MUON  = 0.105658367; // GeV/c^2
  double const MASS_ELE   = 0.000510999; // GeV/c^2
  
  TLorentzVector all_vec;
  TLorentzVector jet_vec;
  TLorentzVector tmp_vec;
  
  for (int i = 0; i < int(_muonInfos.size()); i++) {
    tmp_vec.SetPtEtaPhiM(_muonInfos.at(i).pt, _muonInfos.at(i).eta, _muonInfos.at(i).phi, MASS_MUON);
    all_vec += tmp_vec;
  }
  for (int i = 0; i < int(_eleInfos.size()); i++) {
    tmp_vec.SetPtEtaPhiM(_eleInfos.at(i).pt, _eleInfos.at(i).eta, _eleInfos.at(i).phi, MASS_ELE);
    all_vec += tmp_vec;
  }
  for (int i = 0; i < int(_jetInfos.size()); i++) {
    tmp_vec.SetPtEtaPhiM(_jetInfos.at(i).pt, _jetInfos.at(i).eta, _jetInfos.at(i).phi, _jetInfos.at(i).mass);
    jet_vec += tmp_vec;
    all_vec += tmp_vec;
  }

  _mhtInfo.pt   = all_vec.Pt();
  _mhtInfo.phi  = all_vec.Phi();
  _mhtInfo.MT   = all_vec.Mt();
  _mhtInfo.mass = all_vec.M();

  _mhtInfo.pt_had   = jet_vec.Pt();
  _mhtInfo.phi_had  = jet_vec.Phi();
  _mhtInfo.MT_had   = jet_vec.Mt();
  _mhtInfo.mass_had = jet_vec.M();

}
