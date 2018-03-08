
#include "Ntupliser/DiMuons/interface/JetInfo.h"

void JetInfo::init() {

  px       = -999;
  py       = -999;
  pz       = -999;
  pt       = -999;
  eta      = -999;
  phi      = -999;
  mass     = -999;
  charge   = -999;
  partonID = -999;
  
  chf  = -999;
  nhf  = -999;
  cef  = -999;
  nef  = -999;
  muf  = -999;
  hfhf = -999;
  hfef = -999;
  
  cm   = -999;
  chm  = -999;
  nhm  = -999;
  cem  = -999;
  nem  = -999;
  mum  = -999;
  hfhm = -999;
  hfem = -999;
  
  jecFactor = -999;
  jecUnc    = -999;
  
  genMatched = -999;
  genPx      = -999;
  genPy      = -999;
  genPz      = -999;
  genPt      = -999;
  genEta     = -999;
  genPhi     = -999;
  genMass    = -999;
  genEMF     = -999;
  genHadF    = -999;
  genInvF    = -999;
  genAuxF    = -999;
  
  CSV  = -999;
  puID = -999;

} // End void JetInfo::init()

