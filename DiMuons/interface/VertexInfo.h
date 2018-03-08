
#ifndef VERTEX_INFO
#define VERTEX_INFO

#include <vector>
#include "TMath.h"

struct VertexInfo {

  Bool_t  isValid ;
  Float_t x       ;	
  Float_t y       ;	
  Float_t z       ;	
  Float_t rho     ;	
  Float_t xErr    ;	
  Float_t yErr    ;	
  Float_t zErr    ;	
  Float_t chi2    ;
  Int_t   ndof    ;
  Float_t normChi2;

  void init();
  
};

typedef std::vector<VertexInfo> VertexInfos;

#endif  // #ifndef VERTEX_INFO
