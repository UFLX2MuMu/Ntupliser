
#ifndef PT_CORR_ROCH
#define PT_CORR_ROCH

#include "Ntupliser/RochCor/interface/RoccoR.h"
#include <math.h>
#include "TLorentzVector.h"
#include "TRandom.h"

void CorrectPtRoch( const RoccoR _calib, const bool _doSys, const TLorentzVector _mu_vec, 
		    float& _pt, float& _ptErr, float& _pt_sys_up, float& _pt_sys_down, 
		    const int _charge, const int _trk_layers, const float _GEN_pt, const bool _isData );

#endif  // #ifndef PT_CORR_ROCH
