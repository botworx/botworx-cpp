#ifndef __BwxAgentApplet_H
#define __BwxAgentApplet_H

#include <bwapplet/_BwApplet.h>

/*namespace _BwxAgentApplet {
	using namespace _BwApplet ;
	enum {
		EVENT_STATE_SELECTED = BWAPPLET_EVENT_TTL,
		EVENT_QUERY,
		BWAGENTAPPLET_EVENT_TTL
	} ;
} //end namespace _BwxAgentApplet {*/
namespace _BwxAgentApplet {
	using namespace _BwApplet ;
	enum {
		EVENT_STATE_SELECTED = BWAPPLET_MSG_TTL,
		EVENT_QUERY,
		BWAGENTAPPLET_MSG_TTL
	} ;
} //end namespace _BwxAgentApplet {

class BwxStateSelectedEvent : public BwEvent {
public:
	//BwxStateSelectedEvent(const bwString& path) : BwEvent(_BwxAgentApplet::EVENT_STATE_SELECTED) {
	BwxStateSelectedEvent(bwHandle handle) : BwEvent(_BwxAgentApplet::EVENT_STATE_SELECTED) {
		//m_data->addString("PATH", path) ;
		m_data->addHandle("HANDLE", handle) ;
	}
} ;
class BwxQueryEvent : public BwEvent {
public:
	BwxQueryEvent(const bwString& query) : BwEvent(_BwxAgentApplet::EVENT_QUERY) {
		m_data->addString("QUERY", query) ;
	}
} ;

#endif //__BwxAgentApplet_H