/*BwKernel -
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwesp/BwRemoteMailCenter.h>
#include <bwesp/BwRemoteServer.h>
#include <bwesp/BwRemoteService.h>
#include <bwesp/BwConnection.h>
#include <bwesp/BwCStream.h>

#include <bwesp/_BwService.h>
using namespace _BwService ;

BwRemoteService& BwRemoteMailCenter::getService() {
	return *static_cast<BwRemoteService*>(p_owner) ;
}
BwRemoteServer& BwRemoteMailCenter::getServer() {
	return getService().getServer() ;
}
//TODO:implement destructor that destroys all boxes. This is an Owner class.
BwRemoteMailCenter::BwRemoteMailCenter() {
}
void BwRemoteMailCenter::doCreate(const BwPartInfo& info) {
	BwMailCenter::doCreate(info) ;
	m_connection = getService().getConnection() ;
}
bwHandle BwRemoteMailCenter::addBox(BwMailBox* pBox, BwPart *pAddressee) {
	m_boxes.push_back(BwMailBoxMapPair(pBox, pAddressee)) ;
	return m_nextHandle++ ;
}
BwMailBox* BwRemoteMailCenter::findBox(bwHandle handle) {
	BwMailBox* pBox = BwMailCenter::findBox(handle) ;
	if(pBox == nullptr) {
		//Command
		BwMessage result ;
		getServer().callSync(BwFindBox(getService().getStubHandle(), handle), result) ;
		//Response
		bwHandle boxHandle ;
		result()->findHandle("H_BOX", boxHandle) ;
		pBox = new BwMailBoxProxy(this) ;
		m_boxes[boxHandle] = BwMailBoxMapPair(pBox, nullptr) ;
		pBox->setHandle(boxHandle) ; //???
	}
	return pBox ;
}
BwPart* BwRemoteMailCenter::findAddressee(bwHandle handle) {
	return m_boxes[handle].second ;
}
void BwRemoteMailCenter::removeBox(bwHandle handle) {
	//m_boxes.erase(name) ;
	bwAssert(0) ; //until I implement handle recycling ...
}
//////////////
BwRemoteMailCenter& BwMailBoxProxy::getMailCenter() {
	return *static_cast<BwRemoteMailCenter*>(p_owner) ;
}
BwMailSlot* BwMailBoxProxy::findSlot(const bwString& name) {
	BwMailSlot* pSlot = m_slots[name] ;
	if(pSlot == nullptr) {
		//Command
		BwMessage result ;
		getServer().callSync(BwFindSlot(getService().getStubHandle(), getHandle(), name), result) ;
		//Response
		bwHandle hSlot ;
		result()->findHandle("H_SLOT", hSlot) ; //TODO:check to see if handle is valid
		pSlot = new BwMailSlotProxy(this, name) ;
		pSlot->create() ;
		m_slots[name] = pSlot ;
	}
	return pSlot ;
}
//////////////
BwMailBoxProxy& BwMailSlotProxy::getMailBox() {
	return *static_cast<BwMailBoxProxy*>(p_owner) ;
}
void BwMailSlotProxy::doCreate(const BwPartInfo& info) {
	BwMailSlot::doCreate(info) ;
	p_po = getMailBox().getServer().getPo() ;
}
void BwMailSlotProxy::receive(const BwMessage& msg, bool selfReflective) {
	if(selfReflective)
		return BwMailSlot::receive(msg, selfReflective) ;

	bwHandle hStub = getMailBox().getService().getStubHandle() ;
	bwHandle hBox = getMailBox().getHandle() ; //mailbox and mailslot handles are the same across machine boundaries.
	//
	msg.data().addHandle("H_STUB", hStub) ;
	msg.data().addHandle("H_BOX", hBox) ;
	msg.data().addString("N_SLOT", getName()) ;
	//
	BwCBuffer	espOutBuf(getMailBox().getMailCenter().getConnection()) ;
	BwCStreamOut	espOut(&espOutBuf) ;
	espOut << msg << end ;
}
