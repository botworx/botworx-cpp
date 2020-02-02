#ifndef _BwxContext_H
#define _BwxContext_H

class BwAppletSession ;
class BwDocSession ;
class BwAgentSession ;
class BwAgentClient ;

class BwxContext {
public:
	BwxContext() 
		: p_appletSession(NULL), p_docSession(NULL), p_agentSession(NULL), p_agentClient(NULL)
	{}
	/*BwxContext(BwAppletSession *pAppletSession, BwDocSession *pDocSession = NULL, BwAgentSession *pAgentSession = NULL, BwAgentClient* pAgentClient = NULL) 
		: p_appletSession(pAppletSession), p_docSession(pDocSession), p_agentSession(pAgentSession), p_agentClient(pAgentClient)
	{}*/
	BwxContext(BwAppletSession *pAppletSession, BwDocSession *pDocSession = NULL, BwSession *pAgentSession = NULL, BwAgentClient* pAgentClient = NULL) 
		: p_appletSession(pAppletSession), p_docSession(pDocSession), p_agentSession(pAgentSession), p_agentClient(pAgentClient)
	{}
	void setAppletSession(BwAppletSession* pAppletSession) { p_appletSession = pAppletSession ; }
	BwAppletSession* getAppletSession() const { return p_appletSession ; }
	void setDocSession(BwDocSession* pDocSession) { p_docSession = pDocSession ; }
	BwDocSession *getDocSession() const { return p_docSession ; }
	/*void setAgentSession(BwAgentSession *pAgentSession) { p_agentSession = pAgentSession ; }
	BwAgentSession *getAgentSession() const { return p_agentSession ; }*/
	void setAgentSession(BwSession* pAgentSession) { p_agentSession = pAgentSession ; }
	BwSession* getAgentSession() const { return p_agentSession ; }
	void setAgentClient(BwAgentClient* pAgentClient) { p_agentClient = pAgentClient ; }
	BwAgentClient* getAgentClient() const { return p_agentClient ; }
	//Data Members
	BwAppletSession* p_appletSession ;
	BwDocSession *p_docSession ;
	//BwAgentSession *p_agentSession ;
	BwSession *p_agentSession ;
	BwAgentClient* p_agentClient ;
} ;

#endif //_BwxContext_H