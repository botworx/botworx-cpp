/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvrcegui/VrCeguiUserMode.h>
#include <bwvrcegui/VrCeguiUser.h>
#include <bwvrcegui/VrCeguiControlPanel.h>
//
#include <bwvr/VrGroup.h>

VrCeguiUserMode::VrCeguiUserMode(VrCeguiUserMode* pParent, const bwString& shortName) : BwPart(pParent) {
	m_shortName = shortName ;
	p_user = NULL ;
	p_parent = pParent ;
	p_controlPanel = NULL ;
}
VrCeguiUserMode::~VrCeguiUserMode() {
}
void VrCeguiUserMode::doCreate(const BwPartInfo& info) {
	BwPart::doCreate(info) ;
	if(p_parent != NULL) {
		m_name = p_parent->getName() + "/" + m_shortName ;
		p_user = p_parent->getUser() ;
		p_parent->addMode(this) ;
	}
	else
		m_name = m_shortName ;

	p_user->addMode(this) ;
}
void VrCeguiUserMode::createControlPanel() {
	if(m_modes.empty())	return ;
	if(p_controlPanel != NULL)	return ;
	VrCeguiUserMode *pMode = NULL ;
	p_controlPanel = new VrCeguiControlPanel(p_user->getGui()) ;
	p_controlPanel->setName(m_name) ;
	p_controlPanel->create() ;

	for(VrCeguiUserModeContainer::iterator iter = m_modes.begin();
		iter != m_modes.end(); ++iter)	{
		pMode = (*iter) ;
		p_controlPanel->createButton(pMode) ;
	}
}
void VrCeguiUserMode::destroyControlPanel() {
	//destroyPart(p_controlPanel) ;
}
void VrCeguiUserMode::activate() {
	createControlPanel() ;
	p_user->pushMode(this) ;
}
void VrCeguiUserMode::deactivate() {
	destroyControlPanel() ;
}