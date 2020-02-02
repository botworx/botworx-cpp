/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrContact.h>
#include <bwvr/VrShape.h>

VrContact::VrContact(VrShape* pShape1, VrShape* pShape2, const bwPoint3& pos, const bwVector3& normal, bwReal depth) {
	geom.g1 = pShape1->getGeomID() ;
	geom.g2 = pShape2->getGeomID() ;
	setPos(pos) ;
	setNormal(normal) ;
	setDepth(depth) ;
}
