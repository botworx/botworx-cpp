/*BwKernel -
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwesp/BwMailCenterStub.h>
#include <bwesp/BwServiceStub.h>
#include <bwesp/BwServerStub.h>
#include <bwesp/BwSession.h>
#include <bwesp/BwConnection.h>
#include <bwesp/BwCStream.h>

#include <bwesp/_BwService.h>
using namespace _BwService ;

BwServiceStub* BwMailCenterStub::getServiceStub() {
	return static_cast<BwServiceStub*>(p_owner) ;
}
//TODO:implement destructor that destroys all boxes. This is an Owner class.
BwMailCenterStub::BwMailCenterStub() {
}
void BwMailCenterStub::doCreate(const BwPartInfo& info) {
	BwMailCenter::doCreate(info) ;
	m_connection = serviceStub().getConnection() ;
}
bwHandle BwMailCenterStub::addBox(BwMailBox* pBox, BwPart *pAddressee) {
	m_boxes.push_back(BwMailBoxMapPair(pBox, pAddressee)) ;
	return m_nextHandle++ ;
}
BwMailBox* BwMailCenterStub::findBox(bwHandle handle) {
	BwMailBox* pBox = BwMailCenter::findBox(handle) ;
	if(pBox == nullptr) {
		BwMailCenter& outerMailCenter = serviceStub().getSession()->getMailCenter() ;
		BwMailBox* pOuterBox = outerMailCenter.findBox(handle) ;
		bwAssert(pOuterBox) ;
		pBox = new BwMailBoxStub(this) ;
		pBox->setHandle(handle) ;
		m_boxes[handle] = BwMailBoxMapPair(pBox, nullptr) ;
	}
	return pBox ;
}
BwPart* BwMailCenterStub::findAddressee(bwHandle handle) {
	return m_boxes[handle].second ;
}
void BwMailCenterStub::removeBox(bwHandle handle) {
	//m_boxes.erase(name) ;
	bwAssert(0) ; //until I implement handle recycling ...
}
//////////////
BwMailCenterStub& BwMailBoxStub::getMailCenter() {
	return *static_cast<BwMailCenterStub*>(p_owner) ;
}
BwMailSlot* BwMailBoxStub::findSlot(const bwString& name) {
	BwMailSlot* pSlot = m_slots[name] ;
	if(pSlot == nullptr) {
		BwMailCenter& outerMailCenter = getMailCenter().serviceStub().getSession()->getMailCenter() ;
		BwMailBox* pOuter = outerMailCenter.findBox(getHandle()) ;
		BwMailSlot* pOuterSlot = pOuter->findSlot(name) ;
		bwAssert(pOuterSlot) ;
		pSlot = new BwMailSlotStub(this, name) ;
		pSlot->create() ;
		pSlot->setHandle(pOuterSlot->getHandle()) ;
		m_slots[name] = pSlot ;
		//TODO:may need separate connect method
		pSlot->connect(pOuterSlot) ;
	}
	//
	return pSlot ;
}
//////////////
BwMailBoxStub& BwMailSlotStub::getMailBox() {
	return *static_cast<BwMailBoxStub*>(p_owner) ;
}
void BwMailSlotStub::doCreate(const BwPartInfo& info) {
	BwMailSlot::doCreate(info) ;
	p_po = getMailBox().serviceStub().serverStub().getPo() ;
}
void BwMailSlotStub::receive(const BwMessage& msg, bool selfReflective) {
	if(selfReflective)
		return BwMailSlot::receive(msg, selfReflective) ;
	bwHandle hProxy = getMailBox().serviceStub().getProxyHandle() ;
	bwHandle hBox = getMailBox().getHandle() ; //mailbox and mailslot handles are the same across machine boundaries.
	//
	msg.data().addHandle("H_PROXY", hProxy) ;
	msg.data().addHandle("H_BOX", hBox) ;
	msg.data().addString("N_SLOT", getName()) ;
	//
	BwCBuffer	espOutBuf(getMailBox().getMailCenter().getConnection()) ;
	BwCStreamOut	espOut(&espOutBuf) ;
	espOut << msg << end ;
}
