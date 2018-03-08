
#include "Ntupliser/DiMuons/interface/EventHelper.h"

void FillEventInfo( EventInfo& _eventInfo,
		    const edm::Event& iEvent ) {

  _eventInfo.run   = iEvent.id().run();
  _eventInfo.lumi  = iEvent.luminosityBlock();
  _eventInfo.event = iEvent.id().event();
  _eventInfo.bx    = iEvent.bunchCrossing();
  _eventInfo.orbit = iEvent.orbitNumber();
}
