/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/jr/JrFactory.h>
#include <buggybots/bots/jr/Jr.h>
#include <buggybots/bots/jr/JrBrain.h>
#include <buggybots/bots/jr/JrBody.h>
#include <buggybots/bots/jr/JrBodyVu.h>
#include <buggybots/bots/jr/JrWheel.h>

#include <bwvr/VrBody.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrModelOps.h>

namespace Jr {
JrBody::JrBody(VrGroup *pGroup, Jr *pJr) : VrBox(pGroup) {
	p_jr = pJr ;
	m_size = bwSize3(1,1,1) ;
}
void JrBody::doCreate(const BwPartInfo& info) {
	VrShape::doCreate(info) ;
	bodyInfo().setDensity(p_jr->factory().m_chassisDensity) ;
}
void JrBody::createVu() {
	p_vu = new JrBodyVu(this) ;
	p_vu->create() ;
}
void JrBody::createGeom() {
	VrBox::createGeom() ;
}
void JrBody::doStep(BwStepper& stepper) {
	VrBox::doStep(stepper) ;

	bwEuler e = getEuler(*this) ;
	bwReal power = getBody()->bodyInfo().getMass() * VrPhysics::singleton::get().getInvDt() ;
	bwVector3 force ;
	//falling forward
	if(e[2] < 0) {
		force = bwVector3(power*-e[2],0,0) ;
	}
	//falling backward
	else if(e[2] > 0) {
		force = bwVector3(-(power*e[2]),0,0) ;
	}
	//falling left
	//if(e[0] < -threshold)
	//	force[2] = power*e[0] ;
	//falling right
	//else if(e[0] > threshold) {
	//	force[2] = -power*e[0] ;
	p_body->addRelTorque(force) ;
}
}//end namespace Jr {
