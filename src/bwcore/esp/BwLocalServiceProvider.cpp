#include "stdafx.h"

#include <bwesp/BwLocalServer.h>
#include <bwesp/BwLocalServiceProvider.h>
#include <bwesp/BwRemoteService.h>
#include <bwesp/BwServiceContext.h>

#include <bwmessaging/BwPostOffice.h>

BwLocalServiceProvider::BwLocalServiceProvider(BwServer *pServer, const bwString& name)
	: BwServiceProvider(pServer, name) {
}
BwService* BwLocalServiceProvider::createService(BwServiceRequest& request) {
	BwService* pSvc = nullptr ;
	if(request.getAsync() == true)
		pSvc =  createAsyncService(request) ;
	else
		pSvc =  createSyncService(request) ;
	return pSvc ;
}
BwService* BwLocalServiceProvider::createSyncService(BwServiceRequest& request) {
	BwService* pSvc = produceService(request) ;
	bwAssert(pSvc) ;
	BwServiceContext *pContext = new BwServiceContext(this, request) ;
	pContext->setThread(nullptr) ;
	pContext->setService(pSvc) ;
	m_context[pSvc] = pContext ;
	return pSvc ;
}
struct thread_fn
{
	thread_fn(BwServiceContext *pContext) : p_context(pContext) { }
	void operator()() {
		BwService *pSvc = p_context->getProvider()->produceService(p_context->getRequest()) ;
		p_context->setService(pSvc) ;
		p_context->signalCreateEnd() ;
		//main dispatch loop.
		while(!pSvc->isClosing()) {
			BwEnvelope env = BwPostOffice::singleton::get().pickupNotify() ;
			env.deliver() ;
		}
	}
	BwServiceContext *p_context ;
} ;
BwService* BwLocalServiceProvider::createAsyncService(BwServiceRequest& request) {
	BwServiceContext *pContext = new BwServiceContext(this, request) ;
	boost::thread *pThread = new boost::thread(thread_fn(pContext)) ;
	pContext->setThread(pThread) ; //kindof chicken and egg ...
	if(!pContext->hasService())
		pContext->waitOnOpen() ; //resume after creation ends...
	BwService *pSvc = &pContext->getService() ;
	m_context[pSvc] = pContext ;
	return pSvc ;
}
void BwLocalServiceProvider::closeService(BwService *pSvc) {
	BwServiceContext *pContext = m_context[pSvc] ;
	if(pContext->getThread() != nullptr) {
		pContext->waitOnClose() ; //resume after exit ends...
	}
	else
		pSvc->close() ;
}
void BwLocalServiceProvider::onServiceClose(BwService *pSvc) {
	BwServiceContext *pContext = m_context[pSvc] ;
	pContext->setService(nullptr) ;
	pContext->setThread(nullptr) ;
	pContext->signalExitEnd() ;
}
