
#ifndef GEN_MU_PAIR_HELPER
#define GEN_MU_PAIR_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/GenMuPairInfo.h"
#include "Ntupliser/DiMuons/interface/GenMuonInfo.h"

void FillGenMuPairInfos( GenMuPairInfos& _genPairInfos, const GenMuonInfos _muonInfos );

bool gen_pair_is_OS( std::pair< bool, std::pair<int, int> > i,
		     std::pair< bool, std::pair<int, int> > j );

#endif  // #ifndef GEN_MU_PAIR_HELPER
