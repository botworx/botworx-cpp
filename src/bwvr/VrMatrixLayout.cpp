/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrMatrixLayout.h>
#include <bwvr/VrGroup.h>
#include <bwvr/VrGridLayout.h>

VrMatrixLayout::VrMatrixLayout(VrGroup *pGroup) : VrStackLayout(pGroup) {
}
void VrMatrixLayout::addModel(VrModel *pModel) {
	p_gridLayout->addModel(pModel) ;
	return ;
}
void VrMatrixLayout::beginRow() {
	p_gridLayout->beginRow() ;
	return ;
}
void VrMatrixLayout::endRow() {
	p_gridLayout->endRow() ;
	return ;
}
void VrMatrixLayout::beginGrid() {
	p_grid = new VrGroup(p_group) ;
	p_grid->create() ;

	p_gridLayout = new VrGridLayout(p_grid) ;
	p_gridLayout->create() ;
	return ;
}
void VrMatrixLayout::endGrid() {
	VrStackLayout::addModel(p_grid) ;
}