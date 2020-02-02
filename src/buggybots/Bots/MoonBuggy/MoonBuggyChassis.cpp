/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/moonbuggy/MoonBuggy.h>
#include <buggybots/bots/moonbuggy/MoonBuggyChassis.h>
#include <buggybots/bots/moonbuggy/MoonBuggyBody.h>
#include <buggybots/bots/moonbuggy/MoonBuggyBodyVu.h>

#include <bwvr/VrBox.h>

namespace MoonBuggy {

BuggyChassis::BuggyChassis(Buggy *pBuggy) : VrFixedAssembly(pBuggy) {
	p_buggy = pBuggy ;
	p_buggyBody = NULL ;
	//
	m_isViewable = true ;
	vuInfo().setMeshName("Jeep.mesh") ;
}
void BuggyChassis::doCreate(const BwPartInfo& info) {
	VrFixedAssembly::doCreate(info) ;
	p_buggyBody = new BuggyBody(this, p_buggy) ;
	p_buggyBody->create() ;
	setMain(p_buggyBody) ;
	//
	VrBox *pBox = new VrBox(this) ;
	pBox->setIsViewable(false) ;
	pBox->bodyInfo().setSolidity(.000001) ;
	pBox->create() ;
	pBox->setSize(2, 1, 4) ;
	pBox->setLay(VrRelLay(bwPoint3(0,1.0f,0))) ;
}
void BuggyChassis::createVu() {
	p_vu = new BuggyChassisVu(this) ;
	p_vu->create() ;
}
}//end namespace MoonBuggy