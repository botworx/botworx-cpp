/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwCluster_H
#define _BwCluster_H

#include "BwServer.h"

//
//BwCluster
//
class BwCluster : public BwSystem {
public:
	BwCluster() ;
	//Servers
	void addServer(BwServer* pServer) ;
	//Services
	virtual BwService* createService(BwServiceRequest& request) ;
	//Service Providers
	virtual BwServiceProvider* findServiceProvider(const bwString& spName) ;
	//Data Members
	BwServers m_servers ; //shared
} ;
//
//BwLocalCluster
//
class BwLocalCluster : public BwCluster {
public:
	BwLocalCluster() {}
	//Singleton support
	struct singleton_alloc {
		static BwLocalCluster* alloc() ;
	} ;
	typedef BwAutoSingletonT<BwLocalCluster, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;
//
//BwRemoteCluster
//
class BwRemoteCluster : public BwCluster {
public:
	BwRemoteCluster() {}
	//Singleton support
	struct singleton_alloc {
		static BwRemoteCluster* alloc() ;
	} ;
	typedef BwAutoSingletonT<BwRemoteCluster, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;
#endif //_BwCluster_H