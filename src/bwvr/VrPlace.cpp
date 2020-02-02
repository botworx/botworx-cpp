/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrPlace.h>
#include <bwvr/VrSharedVu.h>

VrPlace::VrPlace(VrGroup *pGroup) : VrGroup(pGroup) {
	setNodeType(NODE_PLACE) ;
	setMotionType(MOTION_STATIC) ;
	m_isAutoSleeper = true ;
	// VrOriginRelLay newLay ;
	// setLay(newLay) ;
	setLay(VrOriginRelLay()) ;
}
void VrPlace::createDynamicLay() {
	// VrPlaceLay placeLay ;
	// placeLay.clone(m_lay) ;
	// setLay(placeLay) ;
	setLay(std::move(VrPlaceLay().clone(m_lay))) ;
}
void VrPlace::doConfig() {
	VrGroup::doConfig() ;
}
void merge_models(VrModelContainer *pSc1, VrModelContainer *pSc2) {
	for (VrModelContainer::iterator iter = pSc2->begin(); //copy
		iter != pSc2->end(); ++iter)	{
		pSc1->push_back(*iter) ;
		}			
}
VrModelContainer* VrPlace::collectStaticModels() {
	VrModelContainer *pModels = new VrModelContainer() ;
	VrModel *pModel = NULL ;
	if(getModels().empty())
		return NULL ;
	for (VrModelContainer::iterator iter = getModels().begin();
			iter != getModels().end(); ++iter)	{
		pModel = (*iter) ;
		switch(pModel->getMotionType()) {
			case MOTION_KINEMATIC :
			case MOTION_DYNAMIC :
				continue ;
			default :
			if(pModel->isPlace() == true) {
				VrPlace *pPlace = static_cast<VrPlace*>(pModel) ;
				VrModelContainer *pModels2 = pPlace->collectStaticModels() ;
				if(pModels2 != NULL)
					merge_models(pModels, pModels2) ;
			}
			else
				pModels->push_back(pModel) ;
		}
	}
	if(pModels->empty())
		return NULL ;
	//else
	return pModels ;
}
void VrPlace::invalidate(VrModel *pModel, invalid flags) {
	if(pModel->isPlace())
		VrGroup::invalidate(pModel, flags) ;
}