#include "stdafx.h"

#include <bwesp/BwLocalSession.h>
#include <bwesp/BwClient.h>

#include <bwmessaging/BwMailCenter.h>

#include <bwesp/_BwService.h>
using namespace _BwService ;

void BwLocalSession::connectClient(BwClient* pClient) {
	addClient(pClient) ;
}
void BwLocalSession::connectSlot(const bwString& name, BwClient* pClient, BwMailSlot* pSlot) {
	BwMailCenter& mailCenter = p_service->getMailCenter() ;
	BwMailBox* pBox = mailCenter.findBox(pClient->getBoxHandle()) ;
	pSlot->connect(pBox->findSlot(name)) ;
}