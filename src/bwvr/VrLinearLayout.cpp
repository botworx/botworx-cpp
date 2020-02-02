/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrLinearLayout.h>
#include <bwvr/VrGroup.h>

VrLinearLayout::VrLinearLayout(VrGroup *pGroup) : VrLayout(pGroup) {
}
void VrLinearLayout::layout() {
	bwPoint3 relPos ;

	bwReal xOffset = 0 ;
	bwReal yOffset = 0 ; 
	bwReal zOffset = 0 ; 

	bwReal width = 0, height = 0, length = 0 ;
	bwReal halfWidth = 0, halfHeight = 0, halfLength = 0 ;

	int xDir = m_direction[0], yDir = m_direction[1], zDir = m_direction[2] ;

	VrModelContainer& models = p_group->getModels() ;
	VrModel *pModel = NULL ;

	for(VrModelContainer::iterator iter = models.begin();
		iter != models.end(); ++iter)	{
		pModel = (*iter) ;

		width = (pModel->getWidth()) * bwReal(xDir) ;
		halfWidth = width * bwRealTraits::Half ;
		height = (pModel->getHeight()) * bwReal(yDir) ;
		halfHeight = height * bwRealTraits::Half ;
		length = (pModel->getLength()) * bwReal(zDir) ;
		halfLength = length * bwRealTraits::Half ;

		relPos = bwPoint3(
			xOffset, 
			yOffset, 
			zOffset) ;

		pModel->setLay(VrOriginRelLay(relPos)) ;

		if(xDir != 0) {
			xOffset = xOffset + width + m_spacing[0] ;
		}

		if(yDir != 0) {
			yOffset = yOffset + height + m_spacing[1] ;
		}

		if(zDir != 0) {
			zOffset = zOffset + length + m_spacing[2] ;
		}
	}
}