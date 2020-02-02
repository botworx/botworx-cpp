/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrContactListener.h>

//void VrContactCollector::onContact(VrShape *pShape, VrSurfaceInfo& surfaceInfo, VrContact *contact) {
void VrContactCollector::onContact(VrNodePair pair, VrSurfaceInfo& surfaceInfo, VrContact *contact) {
	m_contacts.push_front(contact) ;
}
VrContact* VrContactCollector::getClosest(const bwPoint3& point) {
	if(m_contacts.empty())
		return NULL ;
	VrContact *pClosest = &(*m_contacts.begin()) ;
	bwReal dist ;
	bwReal closest = bwmath::distance(pClosest->getPos(), point) ;
	for(VrContactListIter iter = m_contacts.begin() ; iter != m_contacts.end() ; ++iter) {
		dist = bwmath::distance((*iter).getPos(), point) ;
		if(dist < closest) {
			closest = dist ;
			pClosest = &(*iter) ;
		}
	}
	return pClosest ;
}