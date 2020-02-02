/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrContact_H
#define _VrContact_H

class VrShape ;

struct VrContact : dContact {
	VrContact() {
		//TODO:is this going to be overhead?
		::memchr(this, 0, sizeof(this)) ;
	}
	VrContact(dContact *contact) {
		memcpy(this, contact, sizeof(dContact)) ;
	}
	VrContact(VrShape* pShape1, VrShape* pShape2, const bwPoint3& pos, const bwVector3& normal, bwReal depth) ;
	void setPos(const bwPoint3& pos) { geom.pos[0] = pos[0] ; geom.pos[1] = pos[1] ; geom.pos[2] = pos[2]; }
	bwPoint3 getPos() { return bwPoint3(geom.pos[0], geom.pos[1], geom.pos[2]) ; }
	void setNormal(const bwVector3& normal) { 
		geom.normal[0] = normal[0] ; geom.normal[1] = normal[1] ; geom.normal[2] = normal[2] ;
	}
	bwVector3 getNormal() { return bwVector3(geom.normal[0], geom.normal[1], geom.normal[2]) ; }
	void setDepth(bwReal depth) { geom.depth = depth ; }
	bwReal getDepth() { return bwReal(geom.depth) ; }
	//Data Members
	VrShape* getCollider() { return static_cast<VrShape*>(dGeomGetData(geom.g1)) ; }
	VrShape* getCollidee() { return static_cast<VrShape*>(dGeomGetData(geom.g2)) ; }
} ;
typedef std::vector<VrContact> VrContactVector ;
typedef VrContactVector::iterator VrContactVectorIter ;

typedef std::list<VrContact> VrContactList ;
typedef VrContactList::iterator VrContactListIter ;

#endif //_VrContact_H
