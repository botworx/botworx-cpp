/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include "MgEntity.h"
#include "MgScenario.h"
#include "MgPlace.h"
#include "MgVu.h"

MgEntity::MgEntity(MgScenario *pWorld) : BwActor(pWorld), p_world(pWorld) {
	m_hasMoved = false ;
}
void MgEntity::doCreate(const BwPartInfo& info) {
	BwActor::doCreate(info) ;
	createVu() ;
}
bool MgEntity::onCreate(const BwPartInfo& info) {
	p_world->add_entity(this) ;
	return BwActor::onCreate(info) ;
}
void MgEntity::createVu() {
	p_vu = new MgVu(this) ;
	p_vu->create() ;
}
void MgEntity::doPostStep(BwStepper& stepper) {
	BwActor::doPostStep(stepper) ;
	p_vu->doPostStep(stepper) ;
	m_hasMoved = false ;
}
void MgEntity::setPos(const mgPos& pos) { 
	if(pos.x == m_pos.x && pos.y == m_pos.y)
		return ;
	m_hasMoved = true ;
	p_world->getPlaceAt(m_pos)->setEntity(NULL) ;
	p_world->getPlaceAt(pos)->setEntity(this) ;
	m_pos = pos ;
}