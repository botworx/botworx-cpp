#ifndef __BwState_H
#define __BwState_H

#include <bwdocument/_BwDocument.h>

namespace _BwState {
	using namespace _BwDocument ;
	enum {
		EVENT_FACT_ADDED = BWDOCUMENT_MSG_TTL,
		EVENT_FACT_REMOVED,
		OUTPUT_FACTS,
		OUTPUT_LOG,
		BWSTATE_MSG_TTL 
	} ;

} //end namespace _BwState {

//
class BwFactAddedEvent : public BwEvent {
public:
	BwFactAddedEvent(const bwString& txt) : BwEvent(_BwState::EVENT_FACT_ADDED) {
		m_data->addString("FACT", txt) ;
	}
} ;
class BwFactRemovedEvent : public BwEvent {
public:
	BwFactRemovedEvent(const bwString& txt) : BwEvent(_BwState::EVENT_FACT_REMOVED) {
		m_data->addString("FACT", txt) ;
	}
} ;
//
class BwFactsOutput : public BwOutput {
public:
	BwFactsOutput(const bwString& txt) : BwOutput(_BwState::OUTPUT_FACTS) {
		m_data->addString("FACTS", txt) ;
	}
} ;
class BwLogOutput : public BwOutput {
public:
	BwLogOutput(const bwString& txt) : BwOutput(_BwState::OUTPUT_LOG) {
		m_data->addString("LOG", txt) ;
	}
} ;
#endif //__BwState_H