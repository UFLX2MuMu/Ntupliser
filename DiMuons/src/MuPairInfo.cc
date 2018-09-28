
#include "Ntupliser/DiMuons/interface/MuPairInfo.h"

void MuPairInfo::init() {

  iMu1 = -999;
  iMu2 = -999;
  
  mass     = -999;
  massErr  = -999;
  pt       = -999;
  eta      = -999;
  rapid    = -999;
  phi      = -999;
  charge   = -999;
  dR       = -999;
  dEta     = -999;
  dPhi     = -999;
  dPhiStar = -999;
  
  mass_PF    = -999;
  massErr_PF = -999;
  pt_PF      = -999;
  
  mass_trk    = -999;
  massErr_trk = -999;
  pt_trk      = -999;

  mass_KaMu           = -999;
  massErr_KaMu        = -999;
  pt_KaMu             = -999;
  mass_KaMu_clos_up   = -999;
  pt_KaMu_clos_up     = -999;
  mass_KaMu_clos_down = -999;
  pt_KaMu_clos_down   = -999;
  mass_KaMu_sys_up    = -999;
  pt_KaMu_sys_up      = -999;
  mass_KaMu_sys_down  = -999;
  pt_KaMu_sys_down    = -999;

  mass_Roch          = -999;
  massErr_Roch       = -999;
  pt_Roch            = -999;
  mass_Roch_sys_up   = -999;
  pt_Roch_sys_up     = -999;
  mass_Roch_sys_down = -999;
  pt_Roch_sys_down   = -999;

  mass_kinfit          = -999;
  massErr_kinfit       = -999;
  pt_kinfit            = -999;
 
} // End void MuPairInfo::init()

