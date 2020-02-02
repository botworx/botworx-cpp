/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrGridLayout.h>
#include <bwvr/VrGroup.h>
#include <bwvr/VrPlace.h>

VrGridLayout::VrGridLayout(VrGroup *pGroup) : VrColumnLayout(pGroup) {
	p_row = NULL ;
	p_rowLayout = NULL ;
	m_colMax = 0 ;
	m_colSpacing = 0 ;
}
void VrGridLayout::addModel(VrModel *pModel) {
	if(p_rowLayout != NULL)
		p_rowLayout->addModel(pModel) ;
	return ;
}
void VrGridLayout::beginRow() {
	p_row = new VrPlace(p_group) ;
	p_row->create() ;
	p_rowLayout = new VrRowLayout(p_row) ;
	p_rowLayout->create() ;
	p_rowLayout->setSpacing(this->m_spacing) ;
	return ;
}
void VrGridLayout::endRow() {
	VrColumnLayout::addModel(p_row) ;
}
