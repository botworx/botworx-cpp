/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include "MgBrain.h"
#include "MgScenario.h"
#include "MgPlace.h"
#include "MgBrain.h"

#include <bwmia/MiaSystem.h>
#include <bwmia/MiaAgent.h>
#include <bwmia/MiaState.h>
//
//#include "BwLua.h"
#include "MgLuaEngine.h"
//
#include <bwcontrol/BwTask.h>
//
MgBrain::MgBrain(MgEntity* pEntity) : BwBrain(pEntity), p_entity(pEntity) {
	p_agent = NULL ;
	p_explorer = NULL ;
	p_problem = NULL ;
}
MgBrain::~MgBrain() {
	destroyPart(p_agent) ;
	delete p_luaSession ;
}
void MgBrain::doCreate(const BwPartInfo& info) {
	BwBrain::doCreate(info) ;
	createAgent() ;
	p_luaSession = new MgLuaSession(this) ;
}
void MgBrain::createAgent() {
	p_explorer = p_agent->getExplorer() ;
}
/*bool MgBrain::doPostStep(BwStepper& stepper) {
	if(p_explorer != NULL && planBusy()) {
		bool more = p_explorer->doStep() ;
		if(!more)
			setStatus(PLAN_SUCCESS) ; //f6:fixme:handle plan failure!
	}
	return BwBrain::doPostStep(stepper) ;
}*/
bool MgBrain::onPostStep(BwStepper& stepper) {
	if(p_explorer != NULL && planBusy()) {
		bool more = p_explorer->doStep() ;
		if(!more)
			setStatus(PLAN_SUCCESS) ; //f6:fixme:handle plan failure!
	}
	return BwBrain::onPostStep(stepper) ;
}
void MgBrain::think() {
	switch(m_status) {
		case PLAN_START :
			plan() ;
			break ;
		case PLAN_BUSY :
			break ;
		case PLAN_SUCCESS :
		case PLAN_FAILURE :
			doPlan() ;
			break ;
		case TASK_START :
			doTask() ;
			break ;
		case TASK_BUSY : 
			break ;
		case TASK_SUCCESS :
			setStatus(PLAN_START) ;
			break ;
	}
	//BwBrain::think() ;
}
void MgBrain::plan() {
	setStatus(PLAN_BUSY) ;
	//create new top state.
	p_explorer->destroyProblem() ;
	p_problem = p_explorer->createProblem("MOUSE") ;
	//
	p_explorer->clearSolutions() ;
	//f6:fixme
	p_explorer->getRoot()->setState(ACTING) ;
	//
	sense() ; // populate top state.
	//BwBrain::plan() ;
}
void MgBrain::doPlan() {
	setStatus(TASK_START) ;
	p_task = p_explorer->makeTask() ;
}
void MgBrain::doTask() {
	_ASSERT(p_task != NULL) ;
	//setStatus(TASK_BUSY) ;
	MgLuaEngine& lua = MgLuaEngine::singleton() ;
	lua.setSession(p_luaSession) ;
	std::string script = p_task->m_script ;
	lua.dostring(script.c_str()) ;
	setStatus(TASK_SUCCESS) ;
	//
	delete p_task ;
	p_task = NULL ;
}
void MgBrain::sense() {
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
void MgBrain::sensePlace(MgPlace* pPlace) {
	if(pPlace->isNoMansLand())
		return ;
	//else
	MgEntity* pEntity = pPlace->getEntity() ;
	if(pEntity == NULL)
		return senseVacancy(pPlace) ;
	//else
	senseEntity(pEntity) ;
}
void MgBrain::senseVacancy(MgPlace* pPlace) {
	std::stringstream s ;
	s << "{topic " ;
	s << pPlace->getName() << " " ;
	s << "(type place) " ;
	s << "(is vacant) " ;
	//
	mgPos pos = pPlace->getPos() ;
	char buffer1[16] ;
	char buffer2[16] ;
	
	s << "(coord-x " ;
	itoa(pos.x, buffer1, 10) ;
	s << buffer1 ; s << ") " ;

	s << "(coord-y " ;
	itoa(pos.y, buffer2, 10) ;
	s << buffer2 ; s << ") " ;
	
	s << "}\n" ;
	//
	//std::stringstream s ;
	s << "{topic " ;
	s << "(:agent sees " << pPlace->getName() << ") " ;
	s << "(type event) " ;
	s << "}\n" ; //f6:fixme:actually need to fix AiReader eof problem.

	p_problem->load(s) ;
}
void MgBrain::senseEntity(MgEntity* pEntity) {
	std::stringstream s ;
	s << "{topic " ;
	s << pEntity->getName() << " " ;
	s << "(type entity) " ;
	//
	mgPos pos = pEntity->getPos() ;
	char buffer1[16] ;
	char buffer2[16] ;
	
	s << "(coord-x " ;
	itoa(pos.x, buffer1, 10) ;
	s << buffer1 ; s << ") " ;

	s << "(coord-y " ;
	itoa(pos.y, buffer2, 10) ;
	s << buffer2 ; s << ") " ;
	
	s << "}\n" ;

	p_problem->load(s) ;
}
//
void MgBrain::moveTo(int x, int y) {
	p_entity->setPos(mgPos(x,y)) ;
}