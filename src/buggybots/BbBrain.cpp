/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbBrain.h>
#include <buggybots/BbPilot.h>
#include <bwvr/VrPoser.h>
#include <bwvr/VrModel.h>

BbBrain::BbBrain(VrModel* pModel) : VrBrain(pModel) {
	p_marker = NULL ;
}
void BbBrain::doPostEnable(bool sleeping) {
	VrBrain::doPostEnable(sleeping) ;
	if(p_marker != NULL) {
		bwPoint3 pos = p_model->getMain()->getPos() ;
		p_marker->setPosition(pos) ;
		bwVector3 fwd = p_model->getMain()->getQuat() * bwVector3(0, 0, 1) ;
		p_marker->setForward(fwd) ;
	}
}