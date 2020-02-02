#ifndef __BwAgent_H
#define __BwAgent_H

#include <bwdocument/_BwDocument.h>

namespace _BwAgent {
	using namespace _BwDocument ;
	enum {
		EVENT_FRAME_ADDED = BWDOCUMENT_MSG_TTL,
		EVENT_STATE_ADDED,
		EVENT_STATE_REMOVED,
		EVENT_STATE_SOLUTION,
		EVENT_STATE_FAILED,
		EVENT_LOAD_ENDED,
		EVENT_RELOAD_ENDED,
		EVENT_STEP_ENDED,
		EVENT_RUN_ENDED,
		BWAGENT_MSG_TTL
	} ;
} //end namespace _BwAgent {

class BwMindAddedEvent : public BwEvent {
public:
	BwMindAddedEvent(bwWhat what, const bwString& name, bwHandle handle, bwHandle parentHandle) 
		: BwEvent(what) {
		m_data->addString("PATH", name) ;
		m_data->addHandle("HANDLE", handle) ;
		m_data->addHandle("PARENT", parentHandle) ;
	}
} ;

class BwFrameAddedEvent : public BwMindAddedEvent {
public:
	BwFrameAddedEvent(const bwString& name, bwHandle handle, bwHandle parentHandle) 
		: BwMindAddedEvent(_BwAgent::EVENT_FRAME_ADDED, name, handle, parentHandle) {
	}
} ;
class BwStateAddedEvent : public BwMindAddedEvent {
public:
	BwStateAddedEvent(const bwString& name, bwHandle handle, bwHandle parentHandle, const bwString& arcName) 
		: BwMindAddedEvent(_BwAgent::EVENT_STATE_ADDED, name, handle, parentHandle) {
		m_data->addString("ARC", arcName) ;
	}
} ;
class BwStateSolutionEvent : public BwEvent {
public:
	BwStateSolutionEvent(bwHandle handle) 
		: BwEvent(_BwAgent::EVENT_STATE_SOLUTION) {
		m_data->addHandle("HANDLE", handle) ;
	}
} ;
class BwStateFailedEvent : public BwEvent {
public:
	BwStateFailedEvent(bwHandle handle) 
		: BwEvent(_BwAgent::EVENT_STATE_FAILED) {
		m_data->addHandle("HANDLE", handle) ;
	}
} ;
#endif //__BwAgent_H