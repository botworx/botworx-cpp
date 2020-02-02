/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/soccerscenario/SocScenario_common.h>
#include <buggybots/scenarios/soccerscenario/SocScenario.h>
#include <buggybots/scenarios/soccerscenario/SocPursuer.h>

#include <bwvr/VrModel.h>

namespace SoccerScenario {
/////////////////////////
void SocPursuer::doStep(BwStepper& stepper)
{
	SocTask::doStep(stepper) ;
	if(personality().isAvoiding())
		return ;
	//else
	float elapsedTime = stepper.getDeltaTime() ;
	//
	bwVector3 steeringForce = pilot().forward() ;
	bwVector3 ballPos = setYtoOne(personality().m_Ball->position()) ;
	bwVector3 avatarPos = setYtoOne(personality().p_avatar->getPos()) ;
	const float distToAvatar = distance (avatarPos, pilot().position());
	const float distToBall = distance (avatarPos, ballPos);
    // go for ball if I'm on the 'right' side of the ball
	if( personality().b_ImTeamA ? pilot().position()[0]> ballPos[0] : pilot().position()[0] < ballPos[0]) {
		if(distToBall < 25) {
			steeringForce = pilot().steerForPursuit(*personality().m_Ball, 6);
		}
		else {
			//steeringForce = pilot().xxxsteerForSeek(ballPos) ;
			steeringForce = pilot().steerForSeek(ballPos) ;
		}
	}
	else {
		float Z = ballPos[2] - pilot().position()[2] > 0 ? -1.0f : 1.0f;
		bwVector3 behindBall = ballPos + (personality().b_ImTeamA ? bwVector3(2,0,Z) : bwVector3(-2,0,Z));
		bwVector3 behindBallForce = pilot().xxxsteerForSeek(behindBall);
		//annotationLine (position(), behindBall , bwVector3(0,1,0));
		bwVector3 evadeTarget = pilot().xxxsteerForFlee(ballPos);
		steeringForce = behindBallForce*bwReal(5.0)+ evadeTarget ;
	}

	steeringForce = setYtoZero (steeringForce) ;
	pilot().applySteeringForce (steeringForce, elapsedTime);
	// notify proximity database that our position has changed
    pilot().proximityToken->updateForNewPosition (pilot().position());
}

} //namespace SoccerScenario