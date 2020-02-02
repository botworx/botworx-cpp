/*BwKernel - 
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwmessaging/BwMailBox.h>

BwMailer::BwMailer(BwPart* pOwner) : BwPart(pOwner) {
	m_slotHandleCount = 0 ;
}
BwMailer::~BwMailer() {
	for(BwMailSlotMapIter iter = m_slots.begin() ; iter != m_slots.end() ; ++iter) {
		delete (*iter).second ;
	}
}
void BwMailer::addSlot(BwMailSlot* pSlot) {
	pSlot->setHandle(m_slotHandleCount++) ;
	m_slots[pSlot->getName()] = pSlot ;
}
BwMailSlot* BwMailer::findSlot(const bwString& name) {
	return m_slots[name] ;
}
void BwMailer::removeSlot(const bwString& name) {
	m_slots.erase(name) ;
}

///////////////

BwMailBox::BwMailBox(BwPart* pOwner) : BwMailer(pOwner) {
}
BwMailBox::~BwMailBox() {
}