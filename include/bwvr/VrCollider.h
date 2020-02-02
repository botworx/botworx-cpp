/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCollider_H
#define _VrCollider_H

#include "VrCollision.h"

class VrGroup ;
class VrPhysics ;
class VrNode ;
class VrNodeKit ;

struct VrContact ;
class VrCollider ;
class VrContactListener ;
class VrSurfaceInfo ;
//
//VrCollider
//
class VrCollider {
public:
	VrCollider(VrModel *pModel) ;
	virtual ~VrCollider() ;
	virtual void collide(VrNodeKit *pNodeKit, VrNode* pNode) ;
	//
	virtual bool canCollide(VrNode* pCollider, VrNode* pCollidee) { return true ; }
	virtual void addCollisionPair(VrNode* pCollider, VrNode* pCollidee) ;
	virtual VrCollisionRecord& createCollision(VrNode* pCollider, VrNode* pCollidee) ;
	virtual int processCollision(VrCollisionRecord& record) { return 0 ; }
	void setListener(VrContactListener *pListener) { p_listener = pListener ; }
	virtual void processContact(VrCollisionRecord& record, VrSurfaceInfo& surfaceInfo, VrContact *contact) ;
	virtual void onCollider(VrCollider *pCollider) ;
	virtual void onCollidee(VrCollider *pCollider) ;
	virtual void onCollision(VrCollider *pCollider) ;
	virtual void processCollisions() ;
	//
	bool isContacting() { return m_isContacting ; }
	bool isColliding() { return m_isColliding ; }
	void setContactMax(int ttl) { m_contactMax = ttl ; }
	int getContactMax() { return m_contactMax ; }
	//
	VrModel* getModel() { return p_model ; }
	//
	VrCollisionRecord& cacheCollision(VrNode* pCollider, VrNode* pCollidee) ;
	bool findCollision(VrNode* pCollider, VrNode* pCollidee) ;
	void destroyCollision(VrCollisionRecord& record) ;
	/*Data Members*/
protected:
	VrContactListener *p_listener ;
public:
	static const int MAXCONTACTS = 32 ;
	int m_contactMax ;
	bool m_isColliding ;
	bool m_isContacting ;
protected:
	VrModel *p_model ;
	VrCollisionRecords m_collisions ;
} ;

#endif //_VrCollider_H
