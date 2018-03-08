
#include "Ntupliser/DiMuons/interface/GenMuonInfo.h"

void GenMuonInfo::init() {

  status     = -999;
  nMothers   = -999;
  postFSR    = -999;

  pt     = -999;
  eta    = -999;
  phi    = -999;
  mass   = -999;
  charge = -999;

  FSR_pt     = -999;
  FSR_eta    = -999;
  FSR_phi    = -999;
  FSR_mass   = -999;

  mother_ID     = -999;
  mother_status = -999;
  mother_idx    = -999;

}
