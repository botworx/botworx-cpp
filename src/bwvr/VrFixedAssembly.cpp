/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrFixedAssembly.h>
#include <bwvr/VrVu.h>

VrFixedAssembly::VrFixedAssembly(VrGroup *pGroup) : VrAssembly(pGroup) {
	setMotionType(MOTION_DYNAMIC) ;
	setIsAutoSleeper(true) ;
	setTestInternal(false) ;
	/* Don't need a body absolute lay since we're not technically connected to the body */
}
void VrFixedAssembly::createBody() {
	VrModel::createBody() ;
}
void VrFixedAssembly::onModelAddition(VrModel *pModel) {
	VrShape *pShape = static_cast<VrShape*>(pModel) ;
	pShape->embed() ;
	invalidateMass() ;
	VrAssembly::onModelAddition(pModel) ;
}
void VrFixedAssembly::onLayout() {
	VrBodyInfo &m1 = m_bodyInfo ;
	VrModel* pModel = NULL ;
	// adjust relative positions of objects so that the center of mass is (0,0,0)
	for(VrModelContainer::iterator iter = getModels().begin();
		iter != getModels().end(); ++iter)	{
		pModel = (*iter) ;
		bwPoint3 point = pModel->getRelPos() ;
		bwPoint3 relPoint = point - m1.getCenter() ;
		pModel->setRelPos(relPoint) ;
      }
	bwPoint3 pos = getPos() ;
	setRelPos(getRelPos() + m_bodyInfo.getCenter()) ;
	VrAssembly::onLayout() ;
}