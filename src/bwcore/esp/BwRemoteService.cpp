#include "stdafx.h"

#include <bwmessaging/BwMailSlot.h>
#include <bwmessaging/BwAddress.h>

#include <bwesp/BwRemoteServer.h>
#include <bwesp/BwRemoteService.h>
#include <bwesp/BwRemoteServiceProvider.h>
#include <bwesp/BwRemoteSession.h>

#include <bwesp/BwConnection.h>
#include <bwesp/BwCStream.h>

#include <bwesp/_BwServer.h>
using namespace _BwServer ;

BwRemoteService::BwRemoteService(BwRemoteServiceProvider* pProvider, const BwServiceRequest& request) 
	: BwService(pProvider), m_request(request) {
}
BwRemoteServiceProvider& BwRemoteService::getProvider() { 
	return *static_cast<BwRemoteServiceProvider*>(p_owner) ; 
}
BwRemoteServer& BwRemoteService::getServer() { 
	return getProvider().getServer() ; 
}
void BwRemoteService::doCreate(const BwPartInfo& info) {
	BwService::doCreate(info) ;
	//TODO:may need to connect to existing remote service...
	createOuter() ;
	createStub() ;
}
void BwRemoteService::createOuter() {
	//Command
	BwMessage result ;
	getServer().callSync(BwCreateService(getProvider().getName()), result) ;
	//Response
	bwHandle serviceHandle ;
	result()->findHandle("H_SERVICE", serviceHandle) ;
	h_outer = serviceHandle ;
}
void BwRemoteService::createStub() {
	//Command
	BwMessage result ;
	getServer().callSync(BwCreateServiceStub(h_outer, this->getHandle()), result) ;
	//Response
	bwHandle hStub ;
	result()->findHandle("H_STUB", hStub) ;
	m_stubHandle = hStub ;
}
void BwRemoteService::createMailCenter() {
	m_connection = getProvider().getConnection() ;
	m_mailCenter.setOwner(this) ;
	m_mailCenter.create() ;
}
BwSession* BwRemoteService::produceSession() {
	BwRemoteSession* pSession = new BwRemoteSession(this) ;
	pSession->create() ;
	return pSession ;
}