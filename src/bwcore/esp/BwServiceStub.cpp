#include "stdafx.h"

#include <bwesp/BwServiceStub.h>
#include <bwesp/BwServerStub.h>
#include <bwesp/BwSession.h>

#include <bwesp/_BwService.h>
using namespace _BwService ;

BwServiceStub::BwServiceStub(BwServerStub* pOwner, bwHandle hProxy) : BwClient(pOwner) {
	p_serverStub = pOwner ;
	m_proxyHandle = hProxy ;
}
void BwServiceStub::doCreate(const BwPartInfo& info) {
	BwClient::doCreate(info) ;
	createMailCenter() ;
}
void BwServiceStub::createMailCenter() {
	m_connection = serverStub().getConnection() ;
	m_mailCenter.setOwner(this) ;
	m_mailCenter.create() ;
}