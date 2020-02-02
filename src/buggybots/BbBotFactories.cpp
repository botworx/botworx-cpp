/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbBotFactories.h>

//
//BbRobotFactory
//
BbRobotFactory::BbRobotFactory(BwKit *pKit) : Character::CharacterFactory(pKit) {
	setName("Robot") ;
	m_vuInfo.setMeshName("robot.mesh") ;
	m_vuInfo.setMeshSize(bwSize3(50, 100, 25)) ;
	bwQuat quat ;
	set(quat, bwAxisAngle(-bwRealTraits::PiDiv2, bwVector3(0,1,0))) ;
	m_vuInfo.setMeshQuat(quat) ;
	m_vuInfo.setMeshPos(bwPoint3(0, -50, 0)) ;
}
//
//BbRobotFactory
//
BbNinjaFactory::BbNinjaFactory(BwKit *pKit) : Character::CharacterFactory(pKit) {
	setName("Ninja") ;
	m_vuInfo.setMeshName("ninja.mesh") ;
	m_vuInfo.setMeshSize(bwSize3(75, 200, 50)) ;
	bwQuat quat ;
	set(quat, bwAxisAngle(bwRealTraits::Pi, bwVector3(0,1,0))) ;
	m_vuInfo.setMeshQuat(quat) ;
	m_vuInfo.setMeshPos(bwPoint3(0, -100, 0)) ;
}
//
//BbFrankieFactory
//
BbFrankieFactory::BbFrankieFactory(BwKit *pKit) : Character::CharacterFactory(pKit) {
	setName("Frankie") ;
	m_vuInfo.setMeshName("frankie.mesh") ;
	m_vuInfo.setIsAutoScaler(false) ;
}
