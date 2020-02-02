#ifndef _BwServiceContext_H
#define _BwServiceContext_H

#include "_BwServer.h"

class BwServiceProvider ;

class BwServiceContext {
public:
	BwServiceContext(BwServiceProvider* pProvider, BwServiceRequest& request)
		: p_provider(pProvider), m_request(request), p_service(nullptr), m_isCreated(false), p_thread(nullptr) {

	}
	BwServiceRequest& getRequest() { return m_request ; }
	bwString getSvcName() { return m_request.getSvcName() ; }
	void setThread(boost::thread* pThread) { p_thread = pThread ; }
	boost::thread* getThread() { return p_thread ; }
	void setService(BwService *pSvc) { p_service = pSvc ; }
	BwService& getService() { return *p_service ; }
	bool hasService() { return p_service != nullptr ; }
	BwServiceProvider* getProvider() { return p_provider ; }
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
	BwServiceProvider* p_provider ;
	BwServiceRequest m_request ;
	BwService* p_service ;
	//
	bool m_isCreated ;
	boost::thread *p_thread ;
	boost::mutex m_createMutex ;
	boost::condition m_openEnd ;
	boost::mutex m_exitMutex ;
	boost::condition m_closeEnd ;
} ;

#endif //_BwServiceContext_H
