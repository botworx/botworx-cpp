/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbProjection.h>

#include <bwvr/VrVu.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrCollider.h>
#include <bwvr/VrNode.h>

#include <bwvr/config/ogre.h>
#include <bwvr/VrScene.h>

#include <OGRE/OgreRibbonTrail.h>

#define VR_OPTION_DEBUG_TRAIL 0

class BbProjectionVu : public VrVu {
public:
	BbProjectionVu(BbProjection *pModel) : VrVu (pModel) {
		p_projection = pModel ;
		p_trail = NULL ;
	}
	~BbProjectionVu() {
	}
	void createSceneNode() {
		VrVu::createSceneNode() ;
		#if VR_OPTION_DEBUG_TRAIL == 0
			return ;
		#endif

		p_trail = VrScene::singleton::get().getManager()->createRibbonTrail(p_projection->makeThingName("RibbonTrail"));
		//p_trail->setInitialColour(0, Ogre::ColourValue::White) ;
		p_trail->setInitialWidth(0, .1) ;
		p_trailNode = VrScene::singleton::get().getManager()->getRootSceneNode()->createChildSceneNode(); 
		p_trailNode->translate(Ogre::Vector3(0,0,0)); 
		p_trailNode->attachObject(p_trail); 
		p_trail->addNode(getSceneNode()); 
	}
	virtual void doPostDisable(bool sleeping = true) {
		if(!sleeping) {
			p_sceneNode->detachAllObjects() ; //TODO:shouldn't this go into VrVu proper?
			if(p_trail != NULL) {
				p_trailNode->detachAllObjects() ;
				VrScene::singleton::get().getManager()->getRootSceneNode()->removeAndDestroyChild(p_trailNode->getName()) ;
				VrScene::singleton::get().getManager()->destroyRibbonTrail(p_trail) ;
			}
		}
		VrVu::doPostDisable(sleeping) ;
	}
	//Data Members
	BbProjection *p_projection ;
	Ogre::SceneNode* p_trailNode ;
	Ogre::RibbonTrail* p_trail ;
} ;
//
BbProjection::BbProjection(VrGroup *pGroup) : VrTetrahedron(pGroup) {
	m_isAutoSleeper = false ;
	_setSize(bwSize3(.25, 1, .25)) ;
	setMotionType(MOTION_KINEMATIC) ;
	setIsGhost(true) ;

	bwReal scale = .5 ;
	bwPoint3 p1 = bwPoint3(0, -.5, 1) * scale ;
	bwPoint3 p2 = bwPoint3(-.75, -.5, -1) * scale ;
	bwPoint3 p3 = bwPoint3(.75, -.5, -1) * scale ;
	bwPoint3 p4 = bwPoint3(0, .25, -.75) * scale ;

	setPoint(0, p1) ;
	setPoint(1, p2) ;
	setPoint(2, p3) ;
	setPoint(3, p4) ;
}
//
void BbProjection::createVu() {
	p_vu = new BbProjectionVu(this) ;
	p_vu->create() ;
}