/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/mapper/Mapper.h>
#include <buggybots/bots/mapper/MapperBrain.h>
//
#include <buggybots/BbScenario.h>
#include <buggybots/BbBuilder.h>
#include <buggybots/BbSector.h>
//
#include <bwvr/VrVu.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrShapeCollider.h>
#include <bwvr/VrNode.h>
#include <bwvr/VrPlace.h>
///
class MapperCollider : public VrShapeCollider {
public:
	MapperCollider(Mapper *pMapper) : VrShapeCollider(pMapper) {
		p_mapper = pMapper ;
	}
	virtual bool canCollide(VrNode* pCollider, VrNode* pCollidee) { return false ; }
	virtual void addCollisionPair(VrNode* pCollider, VrNode* pCollidee) {
		if(pCollidee->getModel()->getMotionType() == MOTION_STATIC)
			return VrShapeCollider::addCollisionPair(pCollider, pCollidee) ;
	}
	//
	Mapper *p_mapper ;
};
///
Mapper::Mapper(VrGroup *pGroup) : VrBox(pGroup) {
	setMotionType(MOTION_KINEMATIC) ;
	_setSize(bwSize3(1, 2, 1)) ;
	vuInfo().setMeshName("BbLaser.mesh") ;
}
void Mapper::createCollider() {
	p_collider = new MapperCollider(this) ;
}
struct BbMapCoord {
	BbMapCoord(size_t x, size_t y) : m_x(x), m_y(y) {
	}
	size_t m_x ;
	size_t m_y ;
} ;
typedef std::stack<BbMapCoord> BbMapCoordStackBase ;
class BbMapCoordStack : public BbMapCoordStackBase {
public:
	bool push(size_t x, size_t y) {
		BbMapCoordStackBase::push(BbMapCoord(x, y)) ;
		return true ;
	}
	bool pop(size_t& x, size_t& y) {
		if(empty())
			return false ;
		//else
		x = top().m_x ;
		y = top().m_y ;
		BbMapCoordStackBase::pop() ;
		return true ;
	}
} ;

inline bool exploreAt(Mapper& mapper, BbMap& map, bwPoint3& origin, size_t x, size_t y) {
	BbMapCell& cell = map.cellAt(x, y) ;
	if(cell.isClosed())
		return false ;
	//else
	if(cell.isExplored())
		return !cell.isClosed() ;
	//else
	mapper.setPos(origin + bwPoint3(x, 0, y)) ;
	mapper.collide() ;
	if(mapper.getCollider()->isContacting()) {
		cell.setCellType(MCF_OBSTACLE) ;
		cell.setIsClosed(true) ;
		return false ;
	}
	//else
	cell.setCellType(MCF_PATH) ;
	return true ;
}
void Mapper::mapIt(BwStepper& stepper, const bwPoint3& startPos) {
	BbMapCoordStack stack ;
	BbMap& map = BbScenario::singleton().getMap() ;
	size_t h = map.getHeight() ;
	size_t w = map.getWidth() ;
	bwPoint3 origin(startPos[0] - (map.getSize()[0] / 2), startPos[1], startPos[2] - (map.getSize()[2] / 2)) ;

    size_t y1; 
    bool spanLeft, spanRight;
    
	size_t x = startPos[0] - origin[0] ;
	size_t y = startPos[2] - origin[2] ;

    if(!stack.push(x, y)) return;
    
    while(stack.pop(x, y))
    {    
        y1 = y;
        while(y1 != 0 && exploreAt(*this, map, origin, x, y1)) y1--;
		y1++ ;
        spanLeft = spanRight = 0;
        while(y1 < h && exploreAt(*this, map, origin, x, y1)) {
			map.cellAt(x, y1).setIsClosed(true) ;
            if(!spanLeft && x > 0 && exploreAt(*this, map, origin, x - 1, y1))
            {
                if(!stack.push(x - 1, y1)) return;
                spanLeft = 1;
            }
            else if(spanLeft && x > 0 && !exploreAt(*this, map, origin, x - 1, y1))
            {
                spanLeft = 0;
            }
            if(!spanRight && x < w - 1 && exploreAt(*this, map, origin, x + 1, y1)) 
            {
                if(!stack.push(x + 1, y1)) return;
                spanRight = 1;
            }
            else if(spanRight && x < w - 1 && !exploreAt(*this, map, origin, x + 1, y1))
            {
                spanRight = 0;
            } 
            y1++;
        }
    }
}
void Mapper::doPostStep(BwStepper& stepper) {
	VrBox::doPostStep(stepper) ;
	die() ;
}