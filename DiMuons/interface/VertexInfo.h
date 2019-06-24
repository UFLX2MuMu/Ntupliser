
#ifndef VERTEX_INFO
#define VERTEX_INFO

#include <vector>
#include "TMath.h"

struct VertexInfo {

  Bool_t  isValid  = -999;
  Float_t x        = -999;	
  Float_t y        = -999;	
  Float_t z        = -999;	
  Float_t rho      = -999;	
  Float_t xErr     = -999;	
  Float_t yErr     = -999;	
  Float_t zErr     = -999;	
  Float_t chi2     = -999;
  Int_t   ndof     = -999;
  Float_t normChi2 = -999;

};

typedef std::vector<VertexInfo> VertexInfos;

#endif  // #ifndef VERTEX_INFO
