/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/moonbuggy/MoonBuggyFactory.h>
#include <buggybots/bots/moonbuggy/MoonBuggy.h>
#include <buggybots/bots/moonbuggy/MoonBuggyBrain.h>
#include <buggybots/bots/moonbuggy/MoonBuggyBody.h>
//#include <buggybots/bots/moonbuggy/MoonBuggyBodyVu.h>
#include <buggybots/bots/moonbuggy/MoonBuggyWheel.h>

namespace MoonBuggy {
BuggyBody::BuggyBody(VrGroup *pGroup, Buggy *pBuggy) : VrCapsule(pGroup) {
	p_buggy = pBuggy ;
	setSize(bwSize3(1,1,2)) ;
	//setSize(bwSize3(2,2,4)) ;
	//vuInfo().setMeshName("buggybot-body.mesh") ;
	//vuInfo().setMeshName("Jeep.mesh") ;
}
void BuggyBody::doCreate(const BwPartInfo& info) {
	VrShape::doCreate(info) ;
	bodyInfo().setDensity(p_buggy->factory().m_chassisDensity) ;
	//bodyInfo().setSolidity(.000001) ;
}
/*
void BuggyBody::createVu() {
	p_vu = new BuggyBodyVu(this) ;
	p_vu->create() ;
}
*/
void BuggyBody::createGeom() {
	VrCapsule::createGeom() ;
}
}//end namespace MoonBuggy {
