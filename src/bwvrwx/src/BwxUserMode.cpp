/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include "BwxUserMode.h"
#include "BwxUser.h"

#include "BwxCard.h"
#include "BwxDeckFrame.h"
#include "BwxGui.h"

BwxUserMode::BwxUserMode(BwxUserMode* pParent, bwString shortName) : BwPart(pParent) {
	//m_state = TASK_START ;
	m_success = false ;
	m_isBusy = false ;
	m_shortName = shortName ;
	p_user = NULL ;
	p_parent = pParent ;
	p_controlPanel = NULL ;
}
BwxUserMode::~BwxUserMode() {
	//p_user->removePersona(this) ;
}
void BwxUserMode::doCreate(const BwPartInfo& info) {
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
bool BwxUserMode::onCreate(const BwPartInfo& info) {
	createControlPanel(p_user->getGui()->getControlFrame()) ;
	return BwPart::onCreate(info) ;
}
BwxCard* BwxUserMode::createControlPanel(BwxDeckFrame *pFrame) {
	BwxUserMode *pMode = NULL ;
	//p_controlPanel = new BwxCard(pFrame) ;
	p_controlPanel = new BwxCard(pFrame) ;
	p_controlPanel->Show(false) ;
	p_controlPanel->setName(m_name) ;

	for(BwxUserModeCollection::iterator iter = m_modes.begin();
		iter != m_modes.end(); ++iter)	{
		pMode = (*iter) ;
		p_controlPanel->createButton(pMode) ;
	}
	return p_controlPanel ;
}
void BwxUserMode::activate() {
	p_user->pushMode(this) ;
}