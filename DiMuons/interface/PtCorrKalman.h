
#ifndef PT_CORR_KALMAN
#define PT_CORR_KALMAN

#include "KaMuCa/Calibration/interface/KalmanMuonCalibrator.h"
#include <math.h>
#include "TROOT.h"
#include <assert.h>

void CorrectPtKaMu( KalmanMuonCalibrator& _calib, const bool _doSys,
		    double& _pt, double& _dPt, double& _pt_sys_up, 
		    double& _pt_sys_down, double& _pt_clos_up, double& _pt_clos_down,
		    const double _eta, const double _phi, const int _charge, const bool _isData );

#endif  // #ifndef PT_CORR_KALMAN
