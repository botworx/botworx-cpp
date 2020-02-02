#ifndef _BwAgentSession_H
#define _BwAgentSession_H

#include <bwesp/BwSession.h>
#include <bwagency/BwAgent.h>

class BwAgentClient ;

typedef std::list<BwAgentClient*> BwAgentClientList ;
typedef BwAgentClientList::iterator BwAgentClientIter ;

class BwAgentSession : public BwSession {
public:
	BwAgentSession(BwAgent* pAgent) ;
	virtual void closeService() ;
	//
	virtual void connectClient(BwClient* pClient) ; //??? BwSession?
	//f6:fixme:local/remote mixin?
	virtual void connectSlot(const bwString& name, BwClient* pClient, BwMailSlot* pSlot) ;
	//
	virtual void onEvent(const BwMessage& msg) ;
	virtual void onAgentClose() ;
	//
	BwAgent* getAgent() { return p_agent ; }
	//Data Members
	BwAgent *p_agent ;
	bool m_agentHasExited ;
	BwMailSlot *p_outSlot ; //out to agents inslot..
	BwMailSlot *p_agentEvents ; //in from agent events
} ;


#endif //_BwAgentSession_H
