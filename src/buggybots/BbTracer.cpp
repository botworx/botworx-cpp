/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbTracer.h>

#include <bwvr/VrGroup.h>
#include <bwvr/VrBody.h>

BbTracer::~BbTracer() {
	if(isActive())
		marker().destroy() ; //TODO:marker will be reference counted.
	//delete p_marker ; //TODO:to be implemented
}
/*TODO:note:couldn't use a virtual destructor because these objects are used as temporaries also.
	better to explicitly call than to maintain state. right?
	could have m_isInitialized ... if(m_isInitialized) marker.destroy() ;
*/
void BbTracer::init() {
	bwAssert(p_marker) ;
	bwPoint3 pos = model().getMain()->getPos() ;
	marker().setPosition(pos) ;
	bwVector3 forward = model().getMain()->getQuat() * bwVector3(0, 0, 1) ;
	normalize(forward) ;
	marker().setForward(forward) ;
	VrTracer::init() ;
}
void BbTracer::validate() {
	marker().validate() ;
}
//////////////////////
BbDynamicTracer::~BbDynamicTracer() {
}
void BbDynamicTracer::validate() {
	bwAssert(p_marker) ;
	bwPoint3 pos = model().getMain()->getPos() ;
	marker().setPosition(pos) ;
	if(model().hasBody()) {
		bwVector3 forward = model().p_body->getLinearVel() ;
		bwReal speed = length(forward) ;
		normalize(forward) ;
		marker().setForward(forward) ;
		marker().setSpeed(speed) ;
	}
	BbTracer::validate() ;
}
//////////////////////
BbPilotTracer::~BbPilotTracer() {
}
void BbPilotTracer::validate() {
	bwAssert(p_marker) ;
}
