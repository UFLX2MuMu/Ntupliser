
#ifndef JET_INFO
#define JET_INFO

#include <vector>
#include "TMath.h"

struct SlimJetInfo {

  Float_t pt       = -999;
  Float_t eta      = -999;
  Float_t phi      = -999;
  Float_t mass     = -999;
  Int_t   partonID = -999;

  Float_t jecFactor = -999;
  Float_t jecUnc    = -999;

  Float_t CSV     = -999;
  Float_t deepCSV = -999;
  Float_t puID    = -999;

};

struct JetInfo {

  Float_t px       = -999;
  Float_t py       = -999;
  Float_t pz       = -999;
  Float_t pt       = -999;
  Float_t eta      = -999;
  Float_t phi      = -999;
  Float_t mass     = -999;
  Float_t charge   = -999;
  Int_t   partonID = -999;

  /////// Energy Fractions //////
  Float_t chf  = -999;  // Charged Hadron
  Float_t nhf  = -999;  // NeutralHadron
  Float_t cef  = -999;  // Charged EM
  Float_t nef  = -999;  // Neutral EM
  Float_t muf  = -999;  // Mu
  Float_t hfhf = -999;  // HF Hadron Fraction
  Float_t hfef = -999;  // HF EM Fraction

  /////// Multiplicities //////
  Int_t cm   = -999;  // Total Charged Mult
  Int_t chm  = -999;  // Charged Hadron Mult
  Int_t nhm  = -999;  // NeutralHadron Mult
  Int_t cem  = -999;  // Charged EM Mult
  Int_t nem  = -999;  // Neutral EM Mult
  Int_t mum  = -999;  // Mu Mult
  Int_t hfhm = -999;  // HF Hadron Mult
  Int_t hfem = -999;  // HF EM Mult

  // Jet Correction Factor--Above momentum is already corrected!!
  // This factor will return momentum to uncorrected value!!
  Float_t jecFactor = -999;
  Float_t jecUnc    = -999;  // Jet Energy Correction Uncertainty

  // Gen Jet Values
  Bool_t  genMatched = -999;
  Float_t genPx      = -999;
  Float_t genPy      = -999;
  Float_t genPz      = -999;
  Float_t genPt      = -999;
  Float_t genEta     = -999;
  Float_t genPhi     = -999;
  Float_t genMass    = -999;

  ///// Gen Jet Energy Fractions ///////
  Float_t genEMF  = -999;  // EM Fraction
  Float_t genHadF = -999;  // Had Fraction
  Float_t genInvF = -999;  // Invisible Fraction
  Float_t genAuxF = -999;  // Auxiliary Fraction (Undecayed Sigmas, etc.)

  Float_t CSV     = -999;  // Btag CSV_v2
  Float_t deepCSV = -999;  // DeepFlavor tagger, sum of p(b) + p(bb)
  Float_t puID    = -999;  // PUID

};

typedef std::vector<SlimJetInfo> SlimJetInfos;
typedef std::vector<JetInfo>     JetInfos;

#endif  // #ifndef JET_INFO
