#include "stdafx.h"

#include <bwesp/BwRemoteSession.h>
#include <bwesp/BwClient.h>
#include <bwesp/BwConnection.h>
#include <bwesp/BwCStream.h>

#include <bwesp/_BwService.h>
using namespace _BwService ;

BwRemoteService& BwRemoteSession::getService() { 
	return *static_cast<BwRemoteService*>(p_owner) ; 
}
void BwRemoteSession::doCreate(const BwPartInfo& info) {
	BwSession::doCreate(info) ;
	m_connection = getService().getConnection() ;
}
void BwRemoteSession::connectClient(BwClient* pClient) {
	addClient(pClient) ;
}
void BwRemoteSession::connectSlot(const bwString& name, BwClient* pClient, BwMailSlot* pSlot) {
	BwMailCenter& mailCenter = p_service->getMailCenter() ;
	BwMailBox* pBox = mailCenter.findBox(pClient->getBoxHandle()) ;
	pSlot->connect(pBox->findSlot(name)) ;
}