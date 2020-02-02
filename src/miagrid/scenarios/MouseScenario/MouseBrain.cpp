/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <MouseScenario/MouseBrain.h>
#include "MgScenario.h"
#include "MgPlace.h"

#include <bwmia/MiaSystem.h>
#include <bwmia/MiaAgent.h>
//
//#include "BwLua.h"
#include "MgLuaEngine.h"
//
#include <bwcontrol/BwTask.h>
//
MouseBrain::MouseBrain(MgEntity* pEntity) : MgBrain(pEntity) {
}
void MouseBrain::createAgent() {
	p_agent = MiaSystem::singleton().createAgent(p_entity->getName(), "../BwMia/demos/Mouse.mia") ;
	MgBrain::createAgent() ;
}

void MouseBrain::sense() {
	mgPos pos = p_entity->getPos() ;
	pos.x -= 1 ;
	pos.y -= 1 ;
	MgScenario *pWorld = p_entity->p_world ;
	MgPlace *pPlace = NULL ;
	for(int i = 0 ; i < 3 ; i++) {
		for(int j = 0 ; j < 3 ; j++) {
			mgPos pos2(pos.x + i, pos.y + j) ;
			pPlace = pWorld->getPlaceAt(pos2) ;
			sensePlace(pPlace) ;
		}
	}
}