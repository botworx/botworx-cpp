/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwagency/BwAgency.h>

#include <bwagency/BwAgentSystem.h>
#include <bwagency/BwAgent.h>

#include <bwesp/BwLocalServer.h>
#include <bwesp/_BwServer.h>

#include <bwmessaging/BwPostOffice.h>

using namespace _BwServer ;
//
//BwAgentContext
//
class BwAgentContext {
public:
	BwAgentContext(agentType type, const bwString& name, BwMessage params, bool enabled = true)
		: m_type(type), m_name(name), m_params(params), m_enabled(enabled), p_agent(NULL), m_isCreated(false), p_thread(NULL) {

	}
	bwString getName() { return m_name ; }
	BwMessage get_params() { return m_params ; }
	void setThread(boost::thread* pThread) { p_thread = pThread ; }
	boost::thread* getThread() { return p_thread ; }
	void set_agent(BwAgent *pAgent) { p_agent = pAgent ; }
	BwAgent* getAgent() { return p_agent ; }
	void waitOnOpen() {
		boost::mutex::scoped_lock lock(m_createMutex) ;
		m_openEnd.wait(lock) ;
	}
	void signalCreateEnd() {
		m_openEnd.notify_all();
	}
	void waitOnClose() {
		boost::mutex::scoped_lock lock(m_exitMutex) ;
		m_closeEnd.wait(lock) ;
	}
	void signalExitEnd() {
		m_closeEnd.notify_all();
	}
	//Data Members
	agentType m_type ;
	bool m_enabled ;
	bwString m_name ;
	BwMessage m_params ;
	BwAgent *p_agent ;
	bool m_isCreated ;
	boost::thread *p_thread ;
	boost::mutex m_createMutex ;
	boost::condition m_openEnd ;
	boost::mutex m_exitMutex ;
	boost::condition m_closeEnd ;
} ;
//
//BwAgentThreadFn
//
struct BwAgentThreadFn
{
	BwAgentThreadFn(BwAgentContext *pContext) : p_context(pContext) { }
	void operator()() {
		BwAgent *pAgent = BwLocalAgency::singleton::get().
			createSyncAgent(p_context->m_type, p_context->m_name, p_context->m_params, p_context->m_enabled) ;

		p_context->set_agent(pAgent) ;
		p_context->signalCreateEnd() ;
		//main dispatch loop.
		while(!pAgent->isClosing()) {
			BwEnvelope env = BwPostOffice::singleton::get().pickupNotify() ;
			env.deliver() ;
		}
	}
	BwAgentContext *p_context ;
} ;
//
//BwAgency
//
BwAgency::BwAgency(BwServer *pServer, bwString name) : BwServiceProvider(pServer, name) {
	m_agents.reserve(AGENT_TTL) ;
	for(int i = 0 ; i < AGENT_TTL ; ++i)
		//m_agents[i] = NULL ;
		m_agents.push_back(NULL) ;
}
BwAgent* BwAgency::getAgent(agentType type, const bwString& name, BwMessage params, bool enabled) {
	if(m_agents[type] == NULL)
		m_agents[type] = createAgent(type, name, params, enabled) ;
	return m_agents[type] ;
}
BwAgent* BwAgency::createAgent(agentType type, const bwString& name, BwMessage params, bool async, bool enabled) {
	if(async)
		return createAsyncAgent(type, name, params, enabled) ;
	else
		return createSyncAgent(type, name, params, enabled) ;
}
BwAgent* BwAgency::createSyncAgent(agentType type, const bwString& name, BwMessage params, bool enabled) {
	BwAgent* pAgent = NULL ;
	for(BwAgentSystemIter iter = m_agentSystems.begin() ; iter != m_agentSystems.end() ; ++iter) {
		pAgent = (*iter)->createAgent(type, name, params, enabled) ;
		if(pAgent)
			break ;
	}
	bwAssert(pAgent) ;
	BwAgentContext *pContext = new BwAgentContext(type, name, params, enabled) ;
	pContext->setThread(NULL) ;
	pContext->set_agent(pAgent) ;
	m_context[pAgent] = pContext ;
	return pAgent ;
}
BwAgent* BwAgency::createAsyncAgent(agentType type, const bwString& name, BwMessage params, bool enabled) {
	BwAgentContext *pContext = new BwAgentContext(type, name, params, enabled) ;
	boost::thread *pThread = new boost::thread(BwAgentThreadFn(pContext)) ;
	pContext->setThread(pThread) ; //kindof chicken and egg ...
	if(pContext->getAgent() == NULL)
		pContext->waitOnOpen() ; //resume after creation ends...
	BwAgent *pAgent = pContext->getAgent() ;
	m_context[pAgent] = pContext ;
	return pAgent ;
}
void BwAgency::closeAgent(BwAgent *pAgent) {
	BwAgentContext *pContext = m_context[pAgent] ;
	if(pContext->getThread()) {
		pContext->waitOnClose() ; //resume after exit ends...
	}
	else
		pAgent->close() ;
}
void BwAgency::onAgentClose(BwAgent *pAgent) {
	BwAgentContext *pContext = m_context[pAgent] ;
	pContext->set_agent(NULL) ;
	pContext->setThread(NULL) ;
	pContext->signalExitEnd() ;
}
//f6:fixme:a lot of this needs to be made thread safe!!!
void BwAgency::addAgent(BwAgent *pAgent) {
	//m_agents.push_front(pAgent) ;
	m_agents.push_back(pAgent) ; //f6:fixme:maybe use a list
	m_agentByName[pAgent->getName()] = pAgent ;
}
BwAgent* BwAgency::findAgent(const bwString& name) {
	BwAgent *pAgent = NULL ;
	pAgent = m_agentByName[name] ;
	return pAgent ;
}
//
//BwLocalAgency
//
BwService* BwLocalAgency::createService(const BwServiceRequest& request) {
	/*bwAssert(0) ;
	return NULL ;*/
	BwService* pSvc = createAgent(AGENT_DEFAULT, request.getSvcName(), request.getAsync(), request.getEnabled()) ;
	return pSvc ;
}
BwService* BwLocalAgency::produceService(const BwServiceRequest& request) {
	bwAssert(0) ;
	return NULL ;
}
template<> BwLocalAgency::singleton::pointer BwLocalAgency::singleton::g_singleton = 0 ;
BwLocalAgency* BwLocalAgency::singleton_alloc::alloc() {
	BwLocalAgency* pAgency = new BwLocalAgency(BwLocalServer::singleton::getPtr(), "AGENCY") ;
	pAgency->createEnabled() ;
	BwLocalServer::singleton::get().addServiceProvider(pAgency) ;
	return pAgency ;
}
