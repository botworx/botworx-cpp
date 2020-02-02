/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcontrol/BwController.h>

BwController::BwController(BwController *pSuper) : BwActor(pSuper) {
	m_isStageDriven = false ; //TODO:TODO:? right now ... just trying to preserve my sanity.
	p_super = pSuper ;
	m_isActive =  false ;
	m_isBound = false ;
}
void BwController::activate() {
	m_isActive = true ; 
}
void BwController::deactivate() { 
	m_isActive =  false ; 
}
bool BwController::processEvent(BwControllerEvent&& evt) {
	return true ;
}
