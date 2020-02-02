/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwServer_H
#define _BwServer_H

#include <bwcore/BwSystem.h>
#include <bwmessaging/BwAddress.h>
#include <bwesp/BwConnection.h>

#include "_BwServer.h"

class BwServiceProvider ;
class BwService ;
class BwServiceContext ;

class BwServer : public BwSystem {
public:
	BwServer(BwPart *pPart, const BwAddress& address) ;
	//
	BwConnection& getConnection() { return m_connection ; }
	//Service Providers
	void addServiceProvider(BwServiceProvider* pSystem) ;
	virtual BwServiceProvider* findServiceProvider(const bwString& spName) ;
	//Services
	virtual BwService* createService(BwServiceRequest& request) ;
	void addService(BwService *pSvc) ;
	BwService* findService(bwHandle handle) ;
	//Data Members
	//Net
	BwAddress m_address ;
	BwConnection m_connection ;
	//Service Providers
	std::vector<BwServiceProvider*> m_serviceProviders ;
	std::map<bwString, BwServiceProvider*> m_serviceProvidersByName ;
	//Services
	int m_serviceCount ;
	std::vector<BwService*> m_services ; //shared
} ;
typedef std::vector<BwServer*> BwServers ;
typedef BwServers::iterator BwServerIter ;

#endif //_BwServer_H