
#ifndef MHT_HELPER
#define MHT_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/MhtInfo.h"
#include "Ntupliser/DiMuons/interface/MuonInfo.h"
#include "Ntupliser/DiMuons/interface/EleInfo.h"
#include "Ntupliser/DiMuons/interface/JetInfo.h"

void FillMhtInfo( MhtInfo& _mhtInfo, const MuonInfos _muonInfos, 
		  const EleInfos _eleInfos, const JetInfos _jetInfos );

#endif  // #ifndef MHT_HELPER
