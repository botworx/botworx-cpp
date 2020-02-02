/*BwKernel -
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwmessaging/BwMailCenter.h>

//TODO:implement destructor that destroys all boxes. This is an Owner class.
BwMailCenter::BwMailCenter() : BwPart(nullptr) {
	m_nextHandle = 0 ;
}
BwMailCenter::~BwMailCenter() {
}
bwHandle BwMailCenter::addBox(BwMailBox* pBox, BwPart *pAddressee) {
	m_boxes.push_back(BwMailBoxMapPair(pBox, pAddressee)) ;
	return m_nextHandle++ ;
}
BwMailBox* BwMailCenter::findBox(bwHandle handle) {
	if(m_boxes.size() <= handle)
		m_boxes.resize(handle + 16) ;
	return m_boxes[handle].first ;
}
BwPart* BwMailCenter::findAddressee(bwHandle handle) {
	return m_boxes[handle].second ;
}
void BwMailCenter::removeBox(bwHandle handle) {
	//m_boxes.erase(name) ;
	bwAssert(0) ; //until I implement handle recycling ...
}
