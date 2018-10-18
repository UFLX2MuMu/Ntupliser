
#include "Ntupliser/DiMuons/interface/PtCorrKalman.h"

// Based off KaMuCa/Calibration/test/test.py
// Use tracker-only pT as input
void CorrectPtKaMu( KalmanMuonCalibrator& _calib, const bool _doSys,
		    double& _pt, double& _ptErr, double& _pt_sys_up, 
		    double& _pt_sys_down, double& _pt_clos_up, double& _pt_clos_down,
		    const double _eta, const double _phi, const int _charge, const bool _isData ) {

  _calib.reset();

  _pt_sys_up    = -999;
  _pt_sys_down  = -999;
  _pt_clos_up   = -999;
  _pt_clos_down = -999;

  double pt_v0    = _pt;
  double ptErr_v0 = _ptErr;

  // ============================================================
  // AWB 10.11.16
  // Tracker-only pT: to be updated sometime?
  // Corrects only up to 200 GeV.  How much signal is above that?
  // ============================================================

  // Initial correction
  double pt_v1 = _calib.getCorrectedPt( pt_v0, _eta, _phi, _charge );

  // Smear muon pt
  // Used for data by W mass measurement, since data is better than MC at higher pt
  // We only smear MC, since we're doing a search, not a precision mass measurement
  double pt_v2 = _calib.smear( pt_v1, _eta );
  if (_isData) pt_v2 = pt_v1;

  // Corrected ptErr
  double ptErr_v2 = pt_v2 * _calib.getCorrectedError( pt_v2, _eta, (ptErr_v0/pt_v0) );

  // Variations on the scale of the muon pt
  // In principle not an uncertainty on the pt resolution
  // Quadruples the running time of the entire DiMuons NTuple-maker
  // Goes from ~31s per 4k events to ~2m 08s
  std::vector< std::pair<double, double> > pt_up_down;
  double sum_sq_up   = 0;
  double sum_sq_down = 0;
  if (_doSys) {
    for (int i = 0; i < _calib.getN(); i++) {
      _calib.vary(i, +1);
      double pt_sys_up   = _calib.getCorrectedPt( pt_v2, _eta, _phi, _charge ) - pt_v2;
      assert( pt_sys_up >= 0 );
      _calib.vary(i, -1);
      double pt_sys_down = _calib.getCorrectedPt( pt_v2, _eta, _phi, _charge ) - pt_v2;
      assert( pt_sys_down <= 0 );
      _calib.reset();
      
      std::pair<double, double> pt_pair;
      pt_pair.first  = (pt_sys_up >= pt_sys_down ? pt_sys_up : pt_sys_down );
      pt_pair.second = (pt_sys_up <  pt_sys_down ? pt_sys_up : pt_sys_down );
      pt_up_down.push_back( pt_pair );
      
      sum_sq_up   += pow(pt_pair.first,  2);
      sum_sq_down += pow(pt_pair.second, 2);
    }
  }
  
  // Increases the running fime of the DiMuons NTuple-maker by ~33%
  // Goes from ~31s per 4k events to ~42s
  _calib.varyClosure(+1);
  double pt_clos_up   = _calib.getCorrectedPt( pt_v2, _eta, _phi, _charge );
  _calib.varyClosure(-1);
  double pt_clos_down = _calib.getCorrectedPt( pt_v2, _eta, _phi, _charge );
  // Sometimes the closure "up" varies the pT lower, and "down" varies the pT higher

  _pt           = pt_v2;
  _ptErr        = ptErr_v2;
  _pt_sys_up    = ( _doSys ? pt_v2 + sqrt( sum_sq_up )   : -999 );
  _pt_sys_down  = ( _doSys ? pt_v2 - sqrt( sum_sq_down ) : -999 );
  _pt_clos_up   = pt_clos_up;
  _pt_clos_down = pt_clos_down;

  _calib.reset();

}
