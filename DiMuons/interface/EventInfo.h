
#ifndef EVENT_INFO
#define EVENT_INFO

#include <vector>
#include "TMath.h"

struct EventInfo {
  
  Int_t    run;
  Int_t    lumi;
  Long64_t event;
  Long64_t bx;
  Long64_t orbit;

  void init();

};

#endif  // #ifndef EVENT_INFO
