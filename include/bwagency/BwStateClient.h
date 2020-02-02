#ifndef _BwStateClient_H
#define _BwStateClient_H

#include <bwagency/BwAgent.h>

class BwAgentClient ;
class BwCmd ; 

class BwStateClient : public BwPart {
public:
	//BwStateClient(const bwString& name) ;
	BwStateClient(bwHandle handle) ;
	void connect(BwAgentClient *pAgentClient) ;
	void disconnect() ;
	void dropConnection() ;
	void createState(stateType type, const bwString& name, BwMessage params, bool enabled = true) ;
	void createAsyncState(stateType type, const bwString& name, BwMessage params, bool enabled = true) ;
	void close() ;
	void noticeStateExit() ;
	void destroyState() ;
	void doCommand(const BwCmd& cmd) ;
	void doCommandSync(const BwCmd& cmd) ;
	virtual void onOutput(const BwMessage& msg) ;
	virtual void onLog(const BwMessage& msg) ;
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	virtual void onIo(const BwMessage& msg) ;
	void onStateExit() ;
	//
	bool isClosed() ;
	BwAgentClient* getAgentClient() { return p_agentClient ; }
	//Data Members
	bool m_hasResponse ;
	bool m_stateHasExited ;
	long *p_params ;
	//BwState *p_state ;
	BwAgentClient *p_agentClient ;
	BwMailSlot *p_stateIn ;
	BwMailSlot *p_stateOut ;
	BwMailSlot *p_stateLog ;
	BwMailSlot *p_stateEvents ;
} ;
typedef std::vector<BwStateClient> BwStateProxies ;
typedef BwStateProxies::iterator BwStateClientIter ;

#endif //_BwStateClient_H
