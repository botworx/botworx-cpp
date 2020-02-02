#ifndef _BwRemoteServiceProvider_H
#define _BwRemoteServiceProvider_H

#include "BwServiceProvider.h"
#include <bwesp/BwConnection.h>

class BwRemoteServer ;

class BwRemoteServiceProvider : public BwServiceProvider {
public:
	BwRemoteServiceProvider(BwRemoteServer *pServer, const bwString& name) ;
	virtual void doCreate(const BwPartInfo& info) ;
	//
	virtual BwService* createService(const BwServiceRequest& request) ;
	virtual BwService* produceService(const BwServiceRequest& request) ;
	//
	BwConnection& getConnection() { return m_connection ; }
	BwRemoteServer& getServer() ;
	//Data Members
	//Net
	BwConnection m_connection ;
};
typedef std::vector<BwRemoteServiceProvider*> BwRemoteServiceProviders ;
typedef BwRemoteServiceProviders::iterator BwRemoteServiceProviderIter ;

#endif //_BwRemoteServiceProvider_H
