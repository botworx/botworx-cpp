#ifndef _BwLocalService_H
#define _BwLocalService_H

#include <bwesp/BwService.h>
#include <bwesp/BwConnection.h>
#include "_BwServer.h"

class BwCmd ;
class BwMailSlot ;
class BwLocalServiceProvider ;

class BwLocalService : public BwService {
public:
    BwLocalService(BwLocalServiceProvider* pProvider, const BwServiceRequest& request) ;
	virtual BwSession* produceSession() ;
	~BwLocalService() {}
	//
	BwLocalServiceProvider& getProvider() ;
	//
	BwConnection& getConnection() { return m_connection ; }
	//Data Members
	BwServiceRequest m_request ;
	//Net
	BwConnection m_connection ;
	//bwHandle m_serviceHandle ; //TODO:note:our handle is counterparts handle?
};


#endif
