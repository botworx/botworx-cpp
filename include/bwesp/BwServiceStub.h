#ifndef _BwServiceStub_H
#define _BwServiceStub_H

#include "BwClient.h"
#include <bwesp/BwMailCenterStub.h>
#include <bwesp/BwConnection.h>

class BwServerStub ;
/***
Service Stub Masquerades as a Client.
Avoids redundant code to manage stubs. i.e. sending service status messages etc.
Seems like Stubs extend whichever class is most convenient.
***/
class BwServiceStub : public BwClient {
public:
	BwServiceStub(BwServerStub* pOwner, bwHandle hProxy) ;
	virtual void doCreate(const BwPartInfo& info) ;
	//
	virtual void createMailCenter() ;
	BwMailCenter& mailCenter() { return *getMailCenter() ; }
	BwMailCenter* getMailCenter() { return &m_mailCenter ; }
	//
	BwServerStub& serverStub() { return *getServerStub() ; }
	BwServerStub* getServerStub() { return p_serverStub ; }
	//Data Members
	BwServerStub* p_serverStub ;
	BwMailCenterStub m_mailCenter ;
	//
	BwConnection& getConnection() { return m_connection ; }
	//
	bwHandle getProxyHandle() { return m_proxyHandle ; }
	bwHandle m_proxyHandle ;
	//Net
	BwConnection m_connection ;
} ;

#endif //_BwServiceStub_H
