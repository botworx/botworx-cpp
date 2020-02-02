/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrGroup.h>
#include <bwvr/VrLayout.h>
#include <bwvr/VrShape.h>
#include <bwvr/VrNode.h>
#include <bwvr/VrNodeKit.h>

#include <bwvr/VrMech.h>
#include <bwvr/VrJoint.h>

VrGroup::VrGroup(VrGroup *pGroup) : VrModel(pGroup) {
	p_stage = &m_stage ; 	
	m_stage.setOwner(this) ; 
	m_stage.create() ;

	p_layout = NULL ;
	p_main = NULL ;

	setNodeType(NODE_GROUP) ;
	m_isMigrant = false ;
	#if VR_OPTION_DEBUG_BOUNDS
	m_isViewable = true ; //this will create a scenenode for every space.
	#else 
	m_isViewable = false ;
	#endif
}
void VrGroup::invalidate(VrModel *pModel, invalid flags) {
	if(pModel != this) {
		invalid myFlags = INVALID_NONE ;
		if(flags & INVALID_MASS)
			setFlag(myFlags, INVALID_MASS) ;

		if(flags & (INVALID_POSE | INVALID_SIZE)) {
				setFlag(myFlags, INVALID_SIZE) ;
		}
		VrModel::invalidate(pModel, myFlags) ;
		return ;
	}
	//else
	VrModel::invalidate(pModel, flags) ;
}
void VrGroup::validateBounds() {
	m_bounds = bwBounds3(getWorldMin(), getWorldMax()) ;
}
void VrGroup::recenter(const bwPoint3& point) {
	m_lay._setPos(point) ;
}
void VrGroup::validateSize() {
	if(getModels().empty())
		return ;

	VrNode *pNode = getNode() ;
	pNode->fit() ;
	bwBounds3 worldBounds = pNode->getBounds() ;

	_setSize(worldBounds.getMax() - worldBounds.getMin()) ;

	bwPoint3 min = worldBounds.getMin() ;

	if(isEnabled()) {
		m_lay._setPos(pNode->getPos()) ;
	}
	VrModel::validateSize() ;
}
void VrGroup::setLayout(VrLayout *pLayout) {
	if(p_layout != NULL)
		destroyPart(p_layout) ;
	p_layout = pLayout ; 
}
void VrGroup::layout() {
	VrModel::layout() ;
	if(p_layout != NULL)
		p_layout->layout() ;
}
void VrGroup::setIsAutoSleeper(bool val) {
	VrModel::setIsAutoSleeper(val) ;

	VrModelContainer& models = getModels() ;

	for (VrModelContainer::iterator iter = models.begin();
			iter != models.end(); ++iter)	{
		(*iter)->setIsAutoSleeper(val) ;
	}
}
bool VrGroup::doze() {
	VrModel *pModel = NULL ;
	VrModelContainer& models = getModels() ;
	for (VrModelContainer::iterator iter = models.begin();
			iter != models.end(); ++iter)	{
		pModel = *iter ;
		pModel->doze() ;
	}
	return VrModel::doze() ;
}
void VrGroup::addModel(VrModel *pModel) {
	m_stage.addActor(pModel) ;
}
void VrGroup::removeModel(VrModel *pModel) {
	m_stage.removeActor(pModel) ;
}
void VrGroup::wakeAll() {
	VrModelContainer& models = getModels() ;
	for (VrModelContainer::iterator iter = models.begin();
			iter != models.end(); ++iter)	{
		(*iter)->wake() ;
	}
}
//
VrModel* VrGroup::getPrimary() {
	VrModel* pPrimary = p_main ;
	while(pPrimary->isGroup() == true) {
		pPrimary = pPrimary->getMain() ; //need to drill down ... groups are axis aligned now.  good? or bad?
		if(pPrimary == NULL)
			break ;
	}
	return pPrimary ;
}
////////////////
void VrModelStage::onActorAddition(T_Part *pActor) {
	owner().onModelAddition(pActor) ;
}
void VrModelStage::onActorRemoval(T_Part *pActor) {
	owner().onModelRemoval(pActor) ;
}

