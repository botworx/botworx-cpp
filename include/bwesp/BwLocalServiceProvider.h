#ifndef _BwLocalServiceProvider_H
#define _BwLocalServiceProvider_H

#include "BwServiceProvider.h"

class BwLocalServiceProvider : public BwServiceProvider {
public:
	BwLocalServiceProvider(BwServer *pServer, const bwString& name) ;
	//
	virtual BwService* createService(BwServiceRequest& request) ;
	virtual BwService* createSyncService(BwServiceRequest& request) ;
	virtual BwService* createAsyncService(BwServiceRequest& request) ;
	virtual void closeService(BwService *pSvc) ;
	virtual void onServiceClose(BwService *pSvc) ;
	//Data Members
};
typedef std::vector<BwLocalServiceProvider*> BwLocalServiceProviders ;
typedef BwLocalServiceProviders::iterator BwLocalServiceProviderIter ;

#endif //_BwLocalServiceProvider_H
