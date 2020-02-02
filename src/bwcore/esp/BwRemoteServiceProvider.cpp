#include "stdafx.h"

#include <bwesp/BwRemoteServiceProvider.h>
#include <bwesp/BwRemoteService.h>
#include <bwesp/BwRemoteServer.h>

BwRemoteServiceProvider::BwRemoteServiceProvider(BwRemoteServer *pServer, const bwString& name)
	: BwServiceProvider(pServer, name) {
}
void BwRemoteServiceProvider::doCreate(const BwPartInfo& info) {
	BwServiceProvider::doCreate(info) ;
	m_connection = getServer().getConnection() ;
}
BwRemoteServer& BwRemoteServiceProvider::getServer() {
	return *static_cast<BwRemoteServer*>(p_owner) ;
}
BwService* BwRemoteServiceProvider::createService(const BwServiceRequest& request) {
	BwService* pSvc = nullptr ;
	pSvc = produceService(request) ;
	return pSvc ;
}
BwService* BwRemoteServiceProvider::produceService(const BwServiceRequest& request) {
	BwService* pSvc = new BwRemoteService(this, request) ;
	pSvc->create() ;
	return pSvc ;
}
