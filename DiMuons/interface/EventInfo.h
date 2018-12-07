
#ifndef EVENT_INFO
#define EVENT_INFO

#include <vector>
#include "TMath.h"

struct EventInfo {
  
  Int_t    run   = -999;
  Int_t    lumi  = -999;
  Long64_t event = -999;
  Long64_t bx    = -999;
  Long64_t orbit = -999;

};

#endif  // #ifndef EVENT_INFO
