/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwRemoteServer_H
#define _BwRemoteServer_H

#include "BwServer.h"
#include <bwcore/config/boost_thread.h>

class BwConnectionWorker ;
class BwPoWorker ;

class BwCall {
public:
	BwCall() : m_isBlocked(true) {}
	void wait() {
		boost::mutex::scoped_lock lock(m_mutex) ;
		if(isBlocked())
			m_condition.wait(lock) ;
	}
	void resume(const BwMessage& result) {
		boost::mutex::scoped_lock lock(m_mutex) ;
		m_result = result ;
		if(isBlocked())
			m_condition.notify_all();
		m_isBlocked = false ;
	}
	BwMessage& result() { return m_result ; }
	bool isBlocked() { return m_isBlocked ; }
	//Data Members
	boost::condition m_condition ;
	boost::mutex m_mutex ;
	bwHandle m_handle ;
	BwMessage m_result ;
	bool m_isBlocked ;
} ;
typedef std::list<BwCall*> BwCallList ;
typedef BwCallList BwCalls ;
typedef BwCalls::iterator BwCallIter ;

class BwRemoteServer : public BwServer {
public:
	BwRemoteServer(BwPart *pPart, const BwAddress& address) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void onEnable(bool sleeping) ;
	//
	virtual void dispatch(const BwMessage& msg) ;
	//
	void route(const BwMessage& msg) ; //route message to RemoteMailCenter from MailCenterStub
	//
	void send(const BwMessage& msg) ;
	void receive(const BwMessage& msg) ;
	//
	void callSync(const BwMessage& msg, BwMessage& result) ;
	void resumeCall(const BwMessage& msg) ;
	//Data Members
	boost::mutex m_dispatchMutex ;
	BwCalls m_calls ;
	int m_callCounter ;
	//
	boost::mutex m_syncMutex ;
	boost::condition m_syncEnd ;
	//
	void setPo(BwPostOffice* pPo) { p_po = pPo ; }
	BwPostOffice& po() { return *getPo() ; }
	BwPostOffice* getPo() { return p_po ; }
	BwPostOffice* p_po ;
	//
	BwConnectionWorker* p_connectionWorker ;
	BwPoWorker* p_poWorker ;
} ;

#endif //_BwRemoteServer_H
