
#ifndef EVENT_HELPER
#define EVENT_HELPER

#include "Ntupliser/DiMuons/interface/CommonIncludes.h"
#include "Ntupliser/DiMuons/interface/EventInfo.h"

void FillEventInfo( EventInfo& _eventInfo, const edm::Event& iEvent );

#endif  // #ifndef EVENT_HELPER
