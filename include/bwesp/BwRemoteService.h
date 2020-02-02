#ifndef _BwRemoteService_H
#define _BwRemoteService_H

#include <bwesp/BwService.h>
#include <bwesp/BwRemoteMailCenter.h>
#include <bwesp/BwConnection.h>
#include "_BwServer.h"

class BwCmd ;
class BwMailSlot ;
class BwRemoteServer ;
class BwRemoteServiceProvider ;

class BwRemoteService : public BwService {
public:
    BwRemoteService(BwRemoteServiceProvider* pProvider, const BwServiceRequest& request) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual BwSession* produceSession() ;
	~BwRemoteService() {}
	//
	virtual void createMailCenter() ;
	virtual BwMailCenter& getMailCenter() { return m_mailCenter ; }
	//
	BwRemoteServiceProvider& getProvider() ;
	//
	BwRemoteServer& getServer() ;
	//TODO:strange
	void createOuter() ;
	//void createOuterSession() ;
	void createStub() ;
	//
	BwConnection& getConnection() { return m_connection ; }
	//Data Members
	BwServiceRequest m_request ;
	//Net
	BwConnection m_connection ;
	//
	bwHandle h_outer ; //handle of service
	//bwHandle m_outerSessionHandle ;
	//bwHandle m_outerClientHandle ;
	bwHandle getStubHandle() { return m_stubHandle ; }
	bwHandle m_stubHandle ;

	BwRemoteMailCenter m_mailCenter ;
};


#endif
