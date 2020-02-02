/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/scenarios/soccerscenario/SocScenario_common.h>
#include <buggybots/scenarios/soccerscenario/SocScenario.h>
#include <buggybots/scenarios/soccerscenario/SocKicker.h>

#include <bwvr/VrModel.h>
#include <bwvr/VrBody.h>

namespace SoccerScenario {
/////////////////////////
void SocKicker::doStep(BwStepper& stepper)
{
	SocTask::doStep(stepper) ;
	bwReal deltaTime = stepper.getDeltaTime() ;
	///////////////////////////////////
	bwVector3 ballPos = setYtoOne(personality().m_Ball->position()) ;
	//
	bwVector3 teamHomePos = setYtoOne(personality().p_teamHome->getPos()) ;
	//
	bwVector3 enemyTeamHomePos = setYtoOne(personality().p_enemyTeamHome->getPos()) ;
	const float distToEnemyTeamHomePos = distance (enemyTeamHomePos, pilot().position());
	//
	bwVector3 avatarPos = setYtoOne(personality().p_avatar->getPos()) ;
	const float distToAvatar = distance (avatarPos, pilot().position());
	const float distToBall = distance (avatarPos, ballPos);
	const float sumOfRadii = pilot().radius() + personality().m_Ball->radius();
	//const float sumOfRadii = 1 + m_Ball->getRadius();
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (distToBall < sumOfRadii) {
		bwVector3 force ;
		bwReal power = 30 ;
		if(distToEnemyTeamHomePos < 45) {
			force = enemyTeamHomePos - ballPos ;
		}
		else {
			force = ballPos - avatarPos ;
		}
		VrBody* pBody = personality().m_Ball->getModel()->getBody() ;
		//
		normalize(force) ;
		force = force * power * deltaTime ;
		pBody->addForce(force) ;
	}
}

} //namespace SoccerScenario