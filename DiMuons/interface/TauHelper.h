
#ifndef TAU_HELPER
#define TAU_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/TauInfo.h"

void FillTauInfos( TauInfos& _tauInfos, 
		   const pat::TauCollection tausSelected,
		   const std::vector<std::string> _tauIDNames);

pat::TauCollection SelectTaus( const edm::Handle<pat::TauCollection>& taus,
			       const double _tau_pT_min, const double _tau_eta_max );

#endif  // #ifndef TAU_HELPER
