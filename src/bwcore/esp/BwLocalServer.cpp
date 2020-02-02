/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwesp/BwLocalServer.h>
#include <bwesp/BwCluster.h>
#include <bwesp/BwServiceProvider.h>
#include <bwesp/BwService.h>
#include <bwesp/BwServiceContext.h>
#include <bwesp/BwConnection.h>
#include <bwesp/BwCStream.h>

#include <bwcore/BwKernel.h>

#include <bwesp/_BwServer.h>
using namespace _BwServer ;

BwLocalServer::BwLocalServer(BwPart *pPart, const BwAddress& address) : BwServer(pPart, address) {
	m_stubCount = 0 ;
}
void BwLocalServer::doCreate(const BwPartInfo& info) {
	BwServer::doCreate(info) ;
}
BwServerStub* BwLocalServer::createStub() {
	BwServerStub* pStub = new BwServerStub(this) ;
	pStub->create() ;
	return pStub ;
}
void BwLocalServer::listen() {
	BwConnectionData* pData = m_connection.listen(9665) ;
	BwServerStub* pStub = createStub() ;
	addStub(pStub) ;
	pStub->getConnection().p_data = pData ;
	pStub->enable() ;
}
//Singleton support
template<> BwLocalServer* BwLocalServer::singleton::g_singleton = 0 ;
BwLocalServer* BwLocalServer::singleton_alloc::alloc() { 
	BwLocalServer* pServer = new BwLocalServer(nullptr, BwAddress("localhost", "9665")) ;
	pServer->createEnabled() ;
	BwLocalCluster::singleton::get().addKit(pServer) ;
	return pServer ;
}