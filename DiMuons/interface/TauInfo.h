
#ifndef TAU_INFO
#define TAU_INFO

#include <vector>
#include "TMath.h"

struct TauInfo {

  /* Double_t tauID[idArraySize]; */
  
  Float_t charge;
  Float_t pt    ;
  Float_t eta   ;
  Float_t phi   ;

  Float_t d0_PV;
  Float_t dz_PV;
 
  Bool_t isPF;

  void init();

};

typedef std::vector<TauInfo> TauInfos;

#endif  // #ifndef TAU_INFO
