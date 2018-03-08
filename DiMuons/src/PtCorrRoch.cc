
#include "Ntupliser/DiMuons/interface/PtCorrRoch.h"

void CorrectPtRoch( const RoccoR _calib, const bool _doSys, const TLorentzVector _mu_vec, 
		    float& _pt, float& _ptErr, float& _pt_sys_up, float& _pt_sys_down, 
		    const int _charge, const int _trk_layers, const float _GEN_pt, const bool _isData ) {
  
  _pt = _mu_vec.Pt();
  _pt_sys_up = -999;
  _pt_sys_down = -999;
  float q_term     = 1.0;
  float q_term_sys = -99;

  float fRand_1 = gRandom->Rndm();
  float fRand_2 = gRandom->Rndm();

  // For default computation, error set and error member are 0
  if (_isData)            q_term = _calib.kScaleDT( _charge, _mu_vec.Pt(), _mu_vec.Eta(), _mu_vec.Phi(), 0, 0 );
  else if (_GEN_pt > 0) { q_term = _calib.kScaleFromGenMC( _charge, _mu_vec.Pt(), _mu_vec.Eta(), _mu_vec.Phi(),
							   _trk_layers, _GEN_pt, fRand_1, 0, 0 );
  } else {                q_term = _calib.kScaleAndSmearMC( _charge, _mu_vec.Pt(), _mu_vec.Eta(), _mu_vec.Phi(),
							    _trk_layers, fRand_1, fRand_2, 0, 0 );
  }
  if ( fabs(q_term - 1.0) > 0.4 ) {
    std::cout << "\n*** BIZZARELY HIGH QTERM ***" << std::endl;
    std::cout << "GEN pT = " << _GEN_pt << ", RECO pT = " << _mu_vec.Pt() << ", Q term = " << q_term
	      << ", fRand_1 = " << fRand_1 << ", fRand_2 = " << fRand_2 << std::endl;
    std::cout << "Layers = " << _trk_layers << ", charge = " << _charge 
	      << ", eta = " << _mu_vec.Eta() << ", phi = " << _mu_vec.Phi() << std::endl;
  }
    
    
  int nUp   = 0;
  int nDown = 0;
  double sum_sq_up   = 0;
  double sum_sq_down = 0;
  
  // Throw 100 toys to generate uncertainty on correction
  // Even with 100 toys, only increases UFDiMuonsAnalyzer NTuple-maker time from 2 min for 10k events to 2:20
  for (int i = 0; i < 100; i++) {
    if (!_doSys) break;
    
    if (_isData)          q_term_sys = _calib.kScaleDT( _charge, _mu_vec.Pt(), _mu_vec.Eta(), _mu_vec.Phi(), 1, i );
    else if (_GEN_pt > 0) q_term_sys = _calib.kScaleFromGenMC( _charge, _mu_vec.Pt(), _mu_vec.Eta(), _mu_vec.Phi(),
							       _trk_layers, _GEN_pt, fRand_1, 1, i );
    else                  q_term_sys = _calib.kScaleAndSmearMC( _charge, _mu_vec.Pt(), _mu_vec.Eta(), _mu_vec.Phi(),
								_trk_layers, fRand_1, fRand_2, 1, i );
    if ( q_term_sys >= q_term ) {
      nUp   += 1;
      sum_sq_up   += pow( q_term_sys - q_term, 2 );
    } else {
      nDown += 1;
      sum_sq_down += pow( q_term_sys - q_term, 2 );
    }
  }
  
  _pt          = _mu_vec.Pt() * q_term;
  _ptErr       = _ptErr * q_term; // Account for shift in pT scale
  if (!_isData)  _ptErr *= std::fmax(q_term, 1./q_term); // Account for smearing in MC
  _pt_sys_up   = ( _doSys ? _pt * sqrt(sum_sq_up   / nUp)   : -999 );
  _pt_sys_down = ( _doSys ? _pt * sqrt(sum_sq_down / nDown) : -999 ); 

  // std::cout << "\n*******   RESULT   *******" << std::endl;
  // std::cout << "_mu_vec.Pt() = " << _mu_vec.Pt() << ", corrected = " << _pt << std::endl;
  // std::cout << "nUp = " << nUp << ", _pt_sys_up = " << _pt_sys_up << std::endl;
  // std::cout << "nDown = " << nDown << ", _pt_sys_down = " << _pt_sys_down << std::endl;
  
}
