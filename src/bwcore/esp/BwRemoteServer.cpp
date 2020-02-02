/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwesp/BwRemoteServer.h>

#include <bwesp/BwServiceProvider.h>
#include <bwesp/BwService.h>

#include <bwesp/BwConnectionWorker.h>
#include <bwesp/BwPoWorker.h>

#include <bwmessaging/BwMailCenter.h>
#include <bwmessaging/BwPostOffice.h>

#include <bwesp/BwConnection.h>
#include <bwesp/BwCStream.h>

#include <bwesp/_BwServer.h>
using namespace _BwServer ;

BwRemoteServer::BwRemoteServer(BwPart *pPart, const BwAddress& address)
	: BwServer(pPart, address) {
	m_callCounter = 0 ;
	p_po = nullptr ;
}
//*********
void BwRemoteServer::doCreate(const BwPartInfo& info) {
	BwServer::doCreate(info) ;
	//
	p_connectionWorker = new BwConnectionWorker(this) ;
	p_connectionWorker->create() ;
	p_connectionWorker->connect(m_address) ;
	m_connection = p_connectionWorker->getConnection() ;
	//
	p_connectionWorker->enable() ;
	//
	p_po = new BwPostOffice() ;
	p_po->createEnabled() ;
	p_poWorker = new BwPoWorker(this) ;
	p_poWorker->setPo(p_po) ;
	p_poWorker->createEnabled() ;
}
void BwRemoteServer::onEnable(bool sleeping) {
	//Command
	BwMessage result ;
	callSync(BwCreateServerStub(), result) ;
	//Response
	bwAssert(result.what() == RESPONSE_SUCCESS) ;
	return BwServer::onEnable(sleeping) ;
}
void BwRemoteServer::dispatch(const BwMessage& msg) {
	if(msg.handle() == bwAnyHandle)
		route(msg) ;
	else
		resumeCall(msg) ;
}
void BwRemoteServer::route(const BwMessage& msg) {
	bwHandle hProxy, hBox ;
	bwString slotName ;
	msg.data().findHandle("H_PROXY", hProxy) ;
	BwService* pSvcProxy = findService(hProxy) ;
	msg.data().findHandle("H_BOX", hBox) ;
	BwMailBox* pBox = pSvcProxy->getMailCenter().findBox(hBox) ;
	msg.data().findString("N_SLOT", slotName) ;
	BwMailSlot* pSlot = pBox->findSlot(slotName) ;
	pSlot->receive(msg, true) ;
}
void BwRemoteServer::send(const BwMessage& msg) {
	BwCBuffer	espOutBuf(m_connection) ;
	BwCStreamOut	espOut(&espOutBuf) ;
	espOut << msg << end ;
}
void BwRemoteServer::receive(const BwMessage& msg) {
	BwCBuffer	espInBuf(m_connection) ;
	BwCStreamIn	espIn(&espInBuf) ;
	espIn >> msg ;
}
void BwRemoteServer::callSync(const BwMessage& msg, BwMessage& result) {
	BwCall syncCall ;
	{
	boost::mutex::scoped_lock lock(m_dispatchMutex) ;
	bwHandle hCall = m_callCounter++ ;
	msg.data().m_handle = hCall ;
	syncCall.m_handle = hCall ;

	m_calls.push_front(&syncCall) ; //dangerous but ... how else???
	//
	bwAssert(m_calls.size() != 0) ;
	send(msg) ;
	bwAssert(m_calls.size() != 0) ;
	}
	//
	syncCall.wait() ;
	result = syncCall.result() ;
}
void BwRemoteServer::resumeCall(const BwMessage& msg) {
	boost::mutex::scoped_lock lock(m_dispatchMutex) ;
	BwCall* pCall = nullptr ;
	bwHandle hCall = msg.handle() ;
	for(BwCallIter iter = m_calls.begin() ; iter != m_calls.end() ; ++iter) {
		if((*iter)->m_handle == hCall) {
			pCall = (*iter) ;
			m_calls.erase(iter) ; //TODO:this function erases found item...
			pCall->resume(msg) ;
			break ;
		}
	}
}
