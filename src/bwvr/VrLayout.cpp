/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrLayout.h>
#include <bwvr/VrGroup.h>

VrLayout::VrLayout(VrGroup *pGroup) : BwPart(pGroup) {	
	p_group = pGroup ;
	//m_spacing = 0 ;
	m_direction[0] = 1 ;
	m_direction[1] = 1 ;
	m_direction[2] = 1 ;
	//
	m_total = 0 ;
	m_max  = 0;
}
bool VrLayout::onCreate(const BwPartInfo& info) {
	if(p_group != NULL)
		p_group->setLayout(this) ;
	return BwPart::onCreate(info) ;
}
//TODO:
void VrLayout::addModel(VrModel *pModel) {
	pModel->migrate(p_group) ;
	m_total++ ;
	return ;
}