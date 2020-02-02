/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbPilotBrain.h>
#include <buggybots/BbPilot.h>

#include <bwvr/VrPoser.h>
#include <bwvr/VrModel.h>

BbPilotBrain::BbPilotBrain(VrModel* pModel) : BbBrain(pModel) {
	p_poser = NULL ;
}
void BbPilotBrain::doPostConfig() {
	if(p_poser != NULL) {
		p_poser->setPos(p_model->getPos()) ;
		p_poser->setQuat(p_model->getQuat()) ;
	}
	BbBrain::doPostConfig() ;
}
void BbPilotBrain::doStep(BwStepper& stepper) {
	BbBrain::doStep(stepper) ;
	if(getPilot() != NULL) {
		pilot().invokeStep(stepper) ;
	}
	if(p_poser != NULL) {
		if(getPilot() != NULL) {
			bwPoint3 pilotPos = pilot().position() ;
			bwVector3 pilotFwd = pilot().forward() ;
			normalize(pilotFwd) ;
			//
			bwQuat targetOrientation  ;
			bwQuat currentOrient = p_model->getMain()->getQuat() ;
			//bwVector3 currentDir = currentOrient * bwVector3(0, 0, -1) ;
			bwVector3 currentDir = currentOrient * bwVector3(0, 0, 1) ;
			normalize(currentDir) ;
			if (lengthSquared(bwVector3(currentDir+pilotFwd)) < 0.00005f)
			{
				// Oops, a 180 degree turn (infinite possible rotation axes)
				// Default to yaw i.e. use current UP
				targetOrientation  =
					bwQuat(-currentOrient[1], -currentOrient[2], currentOrient[3], currentOrient[0]);
			}
			else
			{
				// Derive shortest arc to new direction
				bwQuat rotQuat ;
				setRot(rotQuat, currentDir, pilotFwd) ;
				targetOrientation = rotQuat * currentOrient;
			}
			//
			bwPoint3 nextPos = pilotPos ;
			//
			p_poser->setPos(nextPos) ;
			p_poser->setQuat(targetOrientation) ;
		}
		p_poser->invokeStep(stepper) ;
	}
}
bool BbPilotBrain::onPostStep(BwStepper& stepper) {
	if(p_poser != NULL) {
		p_poser->invokePostStep(stepper) ;
	}
	if(getPilot() != NULL) {
		pilot().setPosition(p_poser->getPos()) ;
		pilot().invokePostStep(stepper) ;
	}
	return BbBrain::onPostStep(stepper) ;
}
//TODO:there has to be a better way ...
void BbPilotBrain::setPilot(BbSteer::BbPilot* pPilot) { p_marker = pPilot ; }
BbSteer::BbPilot* BbPilotBrain::getPilot() { return static_cast<BbSteer::BbPilot*>(p_marker) ; }
