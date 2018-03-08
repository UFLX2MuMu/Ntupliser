
#include "Ntupliser/DiMuons/interface/GenParentInfo.h"

void GenParentInfo::init() {

  ID         = -999;
  status     = -999;
  nDaughters = -999;

  pt     = -999;
  eta    = -999;
  phi    = -999;
  mass   = -999;
  charge = -999;

  daughter_1_ID     = -999;
  daughter_2_ID     = -999;
  daughter_1_status = -999;
  daughter_2_status = -999;
  daughter_1_idx    = -999;
  daughter_2_idx    = -999;
}

