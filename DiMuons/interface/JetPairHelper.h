
#ifndef JET_PAIR_HELPER
#define JET_PAIR_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/JetPairInfo.h"
#include "Ntupliser/DiMuons/interface/JetInfo.h"

void FillJetPairInfos( JetPairInfos& _pairInfos, const JetInfos _jetInfos );

bool sort_jet_pairs_by_mass( std::pair< float, std::pair<int, int> > i,
                             std::pair< float, std::pair<int, int> > j );

#endif  // #ifndef JET_PAIR_HELPER
