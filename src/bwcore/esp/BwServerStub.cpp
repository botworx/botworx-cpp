/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwesp/BwServerStub.h>
#include <bwesp/BwService.h>
#include <bwesp/BwSession.h>
#include <bwesp/BwServiceStub.h>

#include <bwesp/BwConnectionWorker.h>
#include <bwesp/BwPoWorker.h>
#include <bwesp/BwConnection.h>
#include <bwesp/BwCStream.h>

#include <bwmessaging/BwPostOffice.h>

#include <bwesp/_BwServer.h>
using namespace _BwServer ;

///////////////////
BwServerStub::BwServerStub(BwServer *pServer) : BwPart(pServer) {
	m_serviceStubCount = 0 ;
}
void BwServerStub::doCreate(const BwPartInfo& info) {
	BwPart::doCreate(info) ;
	//
	p_connectionWorker = new BwConnectionWorker(this) ;
	p_connectionWorker->create() ;
	//
	p_po = new BwPostOffice() ;
	p_po->create() ;
	p_poWorker = new BwPoWorker(this) ;
	p_poWorker->setPo(p_po) ;
	p_poWorker->create() ;
}
void BwServerStub::onEnable(bool sleeping) {
	p_connectionWorker->setConnection(m_connection) ;
	p_connectionWorker->enable() ;
	p_poWorker->enable() ;
	return BwPart::onEnable(sleeping) ;
}
void BwServerStub::dispatch(const BwMessage& msg) {
	switch(msg.what()) {
		case COMMAND_CREATE_SERVER_STUB : {
			//Response
			BwCBuffer	espOutBuf(getConnection()) ;
			BwCStreamOut	espOut(&espOutBuf) ;
			espOut << BwSuccess(msg) << end ;
		}
		break ;
		case COMMAND_CREATE_SERVICE : {
			BwServiceRequest request(msg) ;
			BwService* pSvc = getServer().createService(request) ;
			//Response
			BwCBuffer	espOutBuf(getConnection()) ;
			BwCStreamOut	espOut(&espOutBuf) ;
			espOut << BwServiceCreated(msg, pSvc->getHandle()) << end ;
		}
		break ;
		case COMMAND_CREATE_SERVICE_STUB : {
			createServiceStub(msg) ;
		}
		break ;
		case COMMAND_FIND_BOX : {
			bwHandle hStub, hBox ;
			msg.data().findHandle("H_STUB", hStub) ;
			BwServiceStub* pSvcStub = findServiceStub(hStub) ;
			msg.data().findHandle("H_BOX", hBox) ;
			BwMailBox* pBox = pSvcStub->getMailCenter()->findBox(hBox) ;
			//Response
			BwCBuffer	espOutBuf(getConnection()) ;
			BwCStreamOut	espOut(&espOutBuf) ;
			espOut << BwBoxFound(msg, pBox->getHandle()) << end ;
		}
		break ;
		case COMMAND_FIND_SLOT : {
			bwHandle hStub, hBox ;
			bwString slotName ;
			msg.data().findHandle("H_STUB", hStub) ;
			BwServiceStub* pSvcStub = findServiceStub(hStub) ;
			msg.data().findHandle("H_BOX", hBox) ;
			BwMailBox* pBox = pSvcStub->getMailCenter()->findBox(hBox) ;
			msg.data().findString("N_SLOT", slotName) ;
			BwMailSlot* pSlot = pBox->findSlot(slotName) ;
			//Response
			BwCBuffer	espOutBuf(getConnection()) ;
			BwCStreamOut	espOut(&espOutBuf) ;
			espOut << BwSlotFound(msg, pSlot->getHandle()) << end ;
		}
		break ;
		default : {
			bwHandle hStub, hBox ;
			bwString slotName ;
			msg.data().findHandle("H_STUB", hStub) ;
			BwServiceStub* pSvcStub = findServiceStub(hStub) ;
			msg.data().findHandle("H_BOX", hBox) ;
			BwMailBox* pBox = pSvcStub->getMailCenter()->findBox(hBox) ;
			msg.data().findString("N_SLOT", slotName) ;
			BwMailSlot* pSlot = pBox->findSlot(slotName) ;
			pSlot->send(msg) ;
		}
			//bwAssert(0) ;
	}
}
void BwServerStub::createServiceStub(const BwMessage& msg) {
	bwHandle svcHandle, hProxy ;
	msg.data().findHandle("H_SERVICE", svcHandle) ;
	msg.data().findHandle("H_PROXY", hProxy) ;
	BwService* pSvc = getServer().findService(svcHandle) ;
	BwSession* pSession = pSvc->createSession() ;
	BwServiceStub* pSvcStub = new BwServiceStub(this, hProxy) ;
	pSvcStub->create() ;
	pSvcStub->connect(pSession, MB_PRIMARY) ;
	addServiceStub(pSvcStub) ;
	//Response
	BwCBuffer	espOutBuf(getConnection()) ;
	BwCStreamOut	espOut(&espOutBuf) ;
	espOut << BwServiceStubCreated(msg, pSvcStub->getHandle()) << end ;
}
void BwServerStub::addServiceStub(BwServiceStub *pSvcStub) {
	pSvcStub->setHandle(m_serviceStubCount++) ; //TODO:use handle pool
	m_serviceStubs.push_back(pSvcStub) ;
}
void BwServerStub::removeServiceStub(BwServiceStub *pSvcStub) {
	bwAssert(0) ; //TODO:whole hash map / handle pool thing!!!
	m_serviceStubs.erase(find(m_serviceStubs.begin(), m_serviceStubs.end(), pSvcStub)) ;
}
BwServiceStub* BwServerStub::findServiceStub(bwHandle serviceStubHandle) {
	BwServiceStub *pSvcStub = m_serviceStubs[serviceStubHandle] ; ////TODO:use hashmap ... and handle pool!!!
	return pSvcStub ;
}
