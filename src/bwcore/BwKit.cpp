/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcore/BwFactory.h>
#include <bwmessaging/BwMailSlot.h>

BwKit::BwKit(BwPart *pPart) : BwPart(pPart) {
	p_eventSlot = nullptr ;
	p_defaultFactory = new BwFactory(this, this) ;
}
BwKit::~BwKit() {
	delete p_defaultFactory ;
	destroyKits() ;
	destroyPart(p_eventSlot) ;
}
void BwKit::addKit(BwKit *pKit) {
	m_kits.push_back(pKit) ;
}
void BwKit::removeKit(BwKit *pKit) {
	BwKitListIter kit = std::find(m_kits.begin(),m_kits.end(),pKit) ;
	if(kit != m_kits.end())
		m_kits.erase(kit) ;
}
void BwKit::destroyKits() {
	BwKit* pKit = nullptr ;
	for (BwKitListIter iter = m_kits.begin();
		iter != m_kits.end(); ++iter)	{
		pKit = (*iter) ;
		destroyPart(pKit) ;
	}
}
void BwKit::createEventSlot() {
	p_eventSlot = new BwMailSlot(this, "EVENT") ;
	p_eventSlot->create() ;
}
void BwKit::raiseEvent(const BwMessage& msg) {
	p_eventSlot->send(msg) ; 
}
void BwKit::doCreate(const BwPartInfo& info) {
	BwPart::doCreate(info) ;
	createEventSlot() ;
}
void BwKit::doConfig() {
	BwKit *pKit = nullptr ;
	for (BwKitListIter iter = m_kits.begin(); iter != m_kits.end(); ++iter)	{
		pKit = (*iter) ;
		pKit->doConfig() ;
	}
	BwPart::doConfig() ;
}
void BwKit::doPostConfig() {
	BwKit *pKit = nullptr ;
	for (BwKitListIter iter = m_kits.begin(); iter != m_kits.end(); ++iter)	{
		pKit = (*iter) ;
		pKit->doPostConfig() ;
	}
	BwPart::doPostConfig() ;
}
void BwKit::doEnable(bool sleeping) {
	BwKit *pKit = nullptr ;
	for (BwKitListIter iter = m_kits.begin(); iter != m_kits.end(); ++iter)	{
		pKit = (*iter) ;
		pKit->doEnable(sleeping) ;
	}
	return BwPart::doEnable(sleeping) ;
}
void BwKit::doPostEnable(bool sleeping) {
	BwKit *pKit = nullptr ;
	for (BwKitListIter iter = m_kits.begin(); iter != m_kits.end(); ++iter)	{
		pKit = (*iter) ;
		pKit->doPostEnable(sleeping) ;
	}
	BwPart::doPostEnable(sleeping) ;
}
void BwKit::doDisable(bool sleeping) {
	BwKit *pKit = nullptr ;
	for (BwKitListIter iter = m_kits.begin(); iter != m_kits.end(); ++iter)	{
		pKit = (*iter) ;
		pKit->doDisable(sleeping) ;
	}
	BwPart::doDisable(sleeping) ;
}
void BwKit::doPostDisable(bool sleeping) {
	BwKit *pKit = nullptr ;
	for (BwKitListIter iter = m_kits.begin(); iter != m_kits.end(); ++iter)	{
		pKit = (*iter) ;
		pKit->doPostDisable(sleeping) ;
	}
	BwPart::doPostDisable(sleeping) ;
}