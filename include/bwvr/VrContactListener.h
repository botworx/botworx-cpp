/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrContactListener_H
#define _VrContactListener_H

#include "VrContact.h"

class VrModel ;
class VrCollider ;
class VrSurfaceInfo ;

class VrContactListener {
public:
	VrContactListener() {}
	virtual void onContact(VrNodePair pair, VrSurfaceInfo& surfaceInfo, VrContact *contact) {}
	virtual void clear() {}
} ;

class VrContactCollector : public VrContactListener {
public:
	VrContactCollector() {}
	virtual void onContact(VrNodePair pair, VrSurfaceInfo& surfaceInfo, VrContact *contact) ;
	VrContact* getClosest(const bwPoint3& point) ;
	bool empty() { return m_contacts.empty() ; }
	virtual void clear() { m_contacts.clear() ; }
	VrContactList* getContacts() { return &m_contacts ; }
	//Data Members
	VrContactList m_contacts ;
} ;
#endif //_VrContactListener_H
