#ifndef _BwAgentClient_H
#define _BwAgentClient_H

#include <bwesp/BwClient.h>
#include <bwagency/BwAgent.h>

class BwAgentSession ;
class BwCmd ; 
class BwStateClient ;

class BwAgentClient : public BwClient {
public:
	BwAgentClient() ;
	void disconnect() ;
	void dropConnection() ;
	//
	void createAgent(agentType type, const bwString& name, BwMessage params, bool async = true, bool enabled = true) ;
	void createRemoteAgent(agentType type, const bwString& name, BwMessage params, bool async = true, bool enabled = true) ;
	//
	void close() ;
	void doCommand(const BwCmd& cmd) ;
	void doCommandSync(const BwCmd& cmd) ;
	virtual void onOutput(const BwMessage& msg) ;
	virtual void onLog(const BwMessage& msg) ;
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	virtual void onIo(const BwMessage& msg) ;
	//onEvent
	void onAgentClose() ;
	//
	bool isClosed() ;
	//Data Members
	bool m_hasResponse ;
	bool m_agentHasExited ;
	long *p_params ;
	//
	BwMailSlot *p_agentIn ;
	BwMailSlot *p_agentOut ;
	BwMailSlot *p_agentLog ;
	BwMailSlot *p_agentEvents ;
	//
	//f6:newstuff
	void addStateClient(const bwString& name, BwStateClient* pClient) { m_stateMap[name] = pClient ; }
	BwStateClient* findStateClient(const bwString& name) { return m_stateMap[name] ; }
	virtual BwStateClient* createStateClient(const bwString& name) { return NULL ; }
	virtual BwMailCenter& getMailCenter() ;
	std::map<bwString, BwStateClient*> m_stateMap ;
} ;


#endif //_BwAgentClient_H
