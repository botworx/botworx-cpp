#ifndef _BwAgency_H
#define _BwAgency_H

#include <bwesp/BwServiceProvider.h>
#include <bwstd/BwSingleton.h>

class BwAgentSystem ;
class BwAgent ;

class BwAgentContext ;

class BwAgency : public BwServiceProvider {
public:
	BwAgency(BwServer *pServer, bwString name) ;
	//
	//f6:newstuff
	void addAgentSystem(BwAgentSystem* pSystem) { m_agentSystems.push_back(pSystem) ; }
	BwAgent* getAgent(agentType type, const bwString& name, BwMessage params, bool enabled = true) ;
	BwAgent* createAgent(agentType type, const bwString& name, BwMessage params, bool async = true, bool enabled = true) ;
	BwAgent* createSyncAgent(agentType type, const bwString& name, BwMessage params, bool enabled = true) ;
	BwAgent* createAsyncAgent(agentType type, const bwString& name, BwMessage params, bool enabled = true) ;
	void closeAgent(BwAgent *pAgent) ;
	virtual void onAgentClose(BwAgent *pAgent) ;
	void addAgent(BwAgent *pAgent) ;
	BwAgent* findAgent(const bwString& name) ;
	std::map<bwString, BwAgent*> m_agentByName ;
	std::map<BwAgent*, BwAgentContext*> m_context ;
	//Kits
	//Systems
	std::vector<BwAgentSystem*> m_agentSystems ;
	std::vector<BwAgent*> m_agents ; //shared
} ;

class BwLocalAgency : public BwAgency {
public:
	BwLocalAgency(BwServer *pServer, bwString name) : BwAgency(pServer, name) {}
	virtual BwService* createService(const BwServiceRequest& request) ;
	virtual BwService* produceService(const BwServiceRequest& request) ;
	//Singleton support
	struct singleton_alloc {
		static BwLocalAgency* alloc() ;
	} ;
	typedef BwAutoSingletonT<BwLocalAgency, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;
#endif //_BwAgency_H