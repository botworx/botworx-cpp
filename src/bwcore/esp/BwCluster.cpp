/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwesp/BwCluster.h>

#include <bwesp/BwServiceProvider.h>
#include <bwesp/BwService.h>
#include <bwesp/BwServiceContext.h>

#include <bwcore/BwKernel.h>

#include <bwesp/_BwServer.h>
using namespace _BwServer ;

BwCluster::BwCluster() : BwSystem(nullptr) {
}
BwService* BwCluster::createService(BwServiceRequest& request) {
	BwServiceProvider* pProvider = findServiceProvider(request.getSpName()) ;
	BwService* pSvc = pProvider->createService(request) ;
	bwAssert(pSvc) ;
	return pSvc ;
}
BwServiceProvider* BwCluster::findServiceProvider(const bwString& spName) {
	BwServiceProvider* pProvider = nullptr ;
	for(BwServerIter iter = m_servers.begin() ; iter != m_servers.end() ; ++iter) {
		BwServer* pServer = (*iter) ;
		pProvider = pServer->findServiceProvider(spName) ;
		if(pProvider != nullptr)
			break ;
	}
	return pProvider ;
}
void BwCluster::addServer(BwServer* pServer) {
	addKit(pServer) ;
	m_servers.push_back(pServer) ;
}
//Singleton support

//
//BwLocalCluster
//
template<> BwLocalCluster::singleton::pointer BwLocalCluster::singleton::g_singleton = 0 ;
//
BwLocalCluster* BwLocalCluster::singleton_alloc::alloc() {
	BwLocalCluster* pCluster = new BwLocalCluster() ;
	pCluster->createEnabled() ;
	//TODO:kitstuff
	BwKernel::singleton::get().addKit(pCluster) ;
	return pCluster ;
}
//
//BwRemoteCluster
//
template<> BwRemoteCluster::singleton::pointer BwRemoteCluster::singleton::g_singleton = 0 ;
//
BwRemoteCluster* BwRemoteCluster::singleton_alloc::alloc() {
	BwRemoteCluster* pCluster = new BwRemoteCluster() ;
	pCluster->createEnabled() ;
	//TODO:kitstuff
	BwKernel::singleton::get().addKit(pCluster) ;
	return pCluster ;
}
