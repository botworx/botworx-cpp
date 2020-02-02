/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCollision_H
#define _VrCollision_H

class VrNode ;
//
//VrCollision
//
class VrCollision {
public:
	VrCollision() {
		m_type = COLLISION_NULL ;
		p_collider = NULL ;
		p_collidee = NULL ;
	}
	virtual ~VrCollision() {}
	virtual void set(VrNode* pCollider, VrNode* pCollidee) { p_collider = pCollider ; p_collidee = pCollidee ; }
	virtual void clear() { p_collider = NULL ; p_collidee = NULL ; }
	VrNodePair pair() { return VrNodePair(p_collider, p_collidee) ; }
	//Data Members
public:
	collisionType m_type ;
	VrNode *p_collider ;
	VrNode *p_collidee ;
} ;
//
//VrCollisionRecord
//
class VrCollisionRecord {
public:
	VrCollisionRecord() : m_type(COLLISION_NULL), p_collider(NULL), p_collidee(NULL), p_collision(NULL), p_inner(NULL), m_counter(COLLISIONDECAY), m_touched(true) {}
	VrCollisionRecord(collisionType type, VrNode* pCollider, VrNode* pCollidee, VrCollision *pCollision = NULL, int counter=COLLISIONDECAY, bool touched=true) {
		m_type = type ;
		p_collider = pCollider ;
		p_collidee = pCollidee ;
		p_collision = pCollision ;
		p_inner = NULL ;
		m_counter = counter ;
		m_touched = touched ;
		m_hits = 0 ;
	}
	void touch() {
		m_touched = true ;
		m_counter = COLLISIONDECAY ;
	}
	VrNode& collider() { return *p_collider ; }
	VrNode& collidee() { return *p_collidee ; }
	VrNodePair pair() { return VrNodePair(p_collider, p_collidee) ; }
	/*TODO:is this going to be used?
	bool operator==(const VrCollisionRecord& rhs) const {
			return true ;
	}*/
	//Data Members
	static const int COLLISIONDECAY = 10 ;
	collisionType m_type ;
	VrNode *p_collidee ; //make this first since this is the major search criteria.
	VrNode *p_collider ;
	VrCollision *p_collision ;
	void* p_inner ; //points to collision object native to physics engine ...
	int m_counter ;
	int m_hits ;
	bool m_touched ;
} ;
//typedef std::vector<VrCollisionRecord> VrCollisionRecords ;
typedef std::list<VrCollisionRecord> VrCollisionRecords ;
typedef VrCollisionRecords::iterator VrCollisionRecordIter ;

#endif //_VrCollision_H
