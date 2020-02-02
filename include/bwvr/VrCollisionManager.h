/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCollisionManager_H
#define _VrCollisionManager_H

#include <bwcore/BwSystem.h>

class VrCollision ;
class VrCollisionKit ;
struct VrContact ;

class VrCollisionManager : public BwSystem {
public:
	VrCollisionManager(BwPart *pPart) ;
	virtual void doCreate(const BwPartInfo& info) ;
	//
	virtual void createContactBuffer() ;
	VrContact* getContactBuffer() { return p_contacts ; }
	void setContactMax(int ttl) { m_contactMax = ttl ; }
	int getContactMax() { return m_contactMax ; }

	static const int MAXCONTACTS = 1000 ;
	int m_contactMax ;
	VrContact* p_contacts ;
	//TODO:newstuff
	VrCollision* createCollision(collisionType type) ;
	void destroyCollision(VrCollision* pCollision) ;
	//TODO:shouldn't have to modify physics class for new collision types?
	VrCollisionKit *p_odeCollisionKit ;
	//Data Members
	//Singleton support
public:
	struct singleton_alloc {
		static VrCollisionManager* alloc() ;
	} ;
	typedef BwAutoSingletonT<VrCollisionManager, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;

#endif //_VrCollisionManager_H