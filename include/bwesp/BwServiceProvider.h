#ifndef _BwServiceProvider_H
#define _BwServiceProvider_H

#include <bwcore/BwSystem.h>

class BwServer ;
class BwService ;
class BwServiceRequest ;
class BwServiceContext ;

class BwServiceProvider : public BwSystem {
public:
	BwServiceProvider(BwServer *pServer, const bwString& name) ;
	//
	virtual BwService* createService(const BwServiceRequest& request) = 0 ;
	virtual BwService* produceService(const BwServiceRequest& request) = 0 ;
	//
	BwServer& getServer() ;
	//Data Members
	//Services
	std::map<BwService*, BwServiceContext*> m_context ;
};
typedef std::vector<BwServiceProvider*> BwServiceProviders ;
typedef BwServiceProviders::iterator BwServiceProviderIter ;

#endif //_BwServiceProvider_H
