/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrAssembly.h>
//
VrAssembly::VrAssembly(VrGroup *pGroup) : VrGroup(pGroup) {
	m_stage.setIsEnsemble(true) ;
}
void VrAssembly::validateMass() {

	VrBodyInfo m0 ;
	VrBodyInfo m1 ;
	VrBodyInfo m2 ;

	VrModel *pShape ;

	/*compute new mass*/
	for(VrModelContainer::iterator iter = getModels().begin();
		iter != getModels().end(); ++iter)	{
		pShape = *iter ;
		
		copyBodyInfo(&m2, pShape->getBodyInfo()) ;
		m0.add(m2) ;
		//Translation
		bwPoint3 point = pShape->getRelPos() ;
		m2.translate(point) ;
		//Rotation
		bwQuat quat = pShape->getQuat() ;
		m2.rotate(quat) ;
		m1.add(m2) ;
	}
	setBodyInfo(&m1) ;
	//
	VrModel::validateMass() ;
}
void VrAssembly::onModelAddition(VrModel *pModel) {
	pModel->setIsAutoSleeper(isAutoSleeper()) ;
	pModel->setIsMigrant(false) ;
	VrGroup::onModelAddition(pModel) ;
}