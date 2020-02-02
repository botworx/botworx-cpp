/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcore/BwKernel.h>
#include <bwmessaging/BwMessaging.h>

#include <bwvr/config/options_debug.h>
#include <bwvr/VrModel.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrWorld.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrGroup.h>
#include <bwvr/VrCollider.h>
#include <bwvr/VrNode.h>
#include <bwvr/VrNodeKit.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrBuilder.h>

#include <bwvr/VrMech.h>
#include <bwvr/VrLay.h>

#include <bwvr/VrBrain.h>

const int VrModel::DOZEALARM = 10 ;

VrModel::VrModel(VrGroup *pGroup) : BwActor(pGroup) {
	m_serial = BwKernel::singleton::get().getDefaultFactory()->incSerialCounter() ; //temporary fix?
	m_name = makeName() ;

	m_dozeCounter = 0 ;
	m_dozeAlarm = DOZEALARM ;
	p_group = pGroup ;
	p_leader = NULL ; //position leader
	m_nodeType = NODE_BOX ;

	//clearInvalid() ;
	allInvalidFlags() ;

	m_isEntity = false ;

	m_isPlaceable = true ;
	m_isViewable = true ; //this will create a scenenode for every space.
	setMotionType(MOTION_STATIC) ;
	//
	m_isMigrant = true ;
	p_node = NULL ;
	p_nodeKit = NULL ;
	p_futureGroup = NULL ;
	//
	m_testInternal = true ;
	m_isGhost = false ;
	//TODO:newstuff:end
	_setSize(bwSize3(bwReal(1), bwReal(1), bwReal(1))) ;
	m_radius = 1 ;
	p_collider = NULL ;
	p_body = NULL ;
	//
	p_vu = NULL ;
	//
	m_indice = 0 ; //for multiple parts of same type attached to a part
	//
	// VrRelLay newLay ;
	// setLay(newLay) ;
	setLay(VrRelLay()) ;
}
VrModel::~VrModel() {
	if(p_collider != NULL)
		delete p_collider ;
	if(p_vu != NULL)
		delete p_vu ;
	//
	VrGroup* pGroup = getGroup() ;
	if(p_node != NULL) {
		if(pGroup != NULL)
			pGroup->getNode()->detachNode(p_node) ;
		getNodeKit()->releaseNode(p_node) ;
	}
}
void VrModel::doCreate(const BwPartInfo& info) {
	BwActor::doCreate(info) ;
	if(p_group != NULL)
		p_group->addModel(this) ;

	if(info.getCreateStyle() & PS_STATIC)
		setMotionType(MOTION_STATIC) ;
	if(info.getCreateStyle() & PS_QUASISTATIC)
		setMotionType(MOTION_QUASISTATIC) ;

	//createStaticLay() ;
	invalidate(this, INVALID_POSE | INVALID_SIZE) ;
	createBody() ;
	if(!isGhost())
		createCollider() ;
	//
	createNodeKit() ;
	createNode() ;
	validateNode() ;
	//
	if(m_isViewable)
		createVu() ;
}
bool VrModel::onCreate(const BwPartInfo& info) {
	validateMass() ; //mass calc won't work without this.
	return BwActor::onCreate(info) ;
}
void VrModel::createBody() {
	switch(getMotionType()) {
		case MOTION_DYNAMIC :
			p_body = VrPhysics::singleton::get().createBody(this) ;
			break ;
	}
	validateMass() ; //this will call setMass for us
}
bool VrModel::ownsBody() {
	return p_body->p_owner == this ;
}
void VrModel::doConfig() {
	BwActor::doConfig() ;
	invalidate(this, INVALID_POSE | INVALID_SIZE) ; //layout won't work without this.
	if(p_vu != NULL)
		p_vu->doConfig() ;
}
void VrModel::doPostConfig() {
	validateMass() ; //mass calc won't work without this.
	layout() ;
	BwActor::doPostConfig() ;
	if(p_vu != NULL)
		p_vu->doPostConfig() ;
}
void VrModel::doEnable(bool sleeping) {
	if(!sleeping && isDozing())
		sleeping = true ;

	if(hasBody() && ownsBody())
		p_body->doEnable(sleeping) ;
	if(p_vu != NULL)
		p_vu->doEnable(sleeping) ;

	BwActor::doEnable(sleeping) ;

	validateSize() ;
	validateBounds() ;
	validateNode() ;
}
void VrModel::doPostEnable(bool sleeping) {
	//TODO:bigtime collider needs config & enable pass-through!!!!!!!!!!!!!!!!
	if(!sleeping) {
		createDynamicLay() ;
	}
	BwActor::doPostEnable(sleeping) ;

	if(hasBody() && ownsBody())
		p_body->doPostEnable(sleeping) ;
	if(p_vu != NULL)
		p_vu->doPostEnable(sleeping) ;
}
void VrModel::doDisable(bool sleeping) {
	if(!m_isEnabled)
		return ;
	if(hasBody() && ownsBody())
		p_body->doDisable(sleeping) ;
	if(p_vu != NULL)
		p_vu->doDisable(sleeping) ;
	BwActor::doDisable(sleeping) ;
}
void VrModel::doPostDisable(bool sleeping) {
	if(hasBody() && ownsBody())
		p_body->doPostDisable(sleeping) ;
	if(p_vu != NULL)
		p_vu->doPostDisable(sleeping) ;
	BwActor::doPostDisable(sleeping) ;
}
void VrModel::_sleep() {
	BwActor::sleep() ;
}
void VrModel::sleep() {
	if(isSleeping())
		return ;

	if(p_body != NULL)
		p_body->_sleep() ;
	else
		_sleep() ;
}
void VrModel::_touch(VrModel *pModel) {
	/*TODO:improveme:must be a better way!*/
	if(isIdle() && pModel->isIdle())
		return ;
	m_dozeCounter = 0 ;
	if(getMotionType() == MOTION_STATIC)
		return ;
	//else
	if(isSleeping()) {
		wake() ;
		return ;
	}
}
void VrModel::touch(VrModel *pModel) {
	if(p_body != NULL)
		p_body->_touch(pModel) ;
	else
		_touch(pModel) ;
}
void VrModel::_wake() {
	m_dozeCounter = 0 ;
	BwActor::wake() ;
}
void VrModel::wake() {
	if(!isSleeping())
		return ;
	if(p_body != NULL)
		p_body->_wake() ;
	else
		_wake() ;
}
void VrModel::setLay(VrLay&& lay) {
	memcpy(&m_lay, &lay, sizeof(VrLay)) ;
	invalidate(this, INVALID_POSE | INVALID_SIZE) ;
}
void VrModel::createStaticLay() {
	/*If ... no special lay type has already been assigned ... then*/
	if(m_lay.getLayType() == VrLay::LAY_DEFAULT) {
		if(!isPlace()) {
			// VrRelLay newLay ;
			// setLay(newLay) ;
			setLay(VrRelLay()) ;
		}
		else {
			if(p_group != NULL) {
				// VrOriginRelLay newLay ;
				// setLay(newLay) ;
				setLay(VrOriginRelLay()) ;
			}
			else {
				// VrAbsLay newLay ;
				// setLay(newLay) ;
				setLay(VrAbsLay()) ;
			}
		}
	}
}
void VrModel::createDynamicLay() {
	switch(getMotionType()) {
		case MOTION_DYNAMIC :
			if(p_body != NULL) {
				// VrBodyAbsLay bodyLay ;
				// bodyLay.clone(m_lay) ;
				// setLay(bodyLay) ;
				setLay(std::move(VrBodyAbsLay().clone(m_lay)));
			}
			else {
				// VrRelLay newLay ;
				// newLay.clone(m_lay) ;
				// setLay(newLay) ;
				setLay(std::move(VrRelLay().clone(m_lay)));
			}
			break ;
		case MOTION_FIXED :
			if(p_body != NULL) {
				// VrBodyRelLay bodyLay ;
				// bodyLay.clone(m_lay) ;
				// setLay(bodyLay) ;
				setLay(std::move(VrBodyRelLay().clone(m_lay)));
			}
			else {
				// VrRelLay newLay ;
				// newLay.clone(m_lay) ;
				// setLay(newLay) ;
				setLay(std::move(VrRelLay().clone(m_lay)));
			}
			break ;

		default :
			// VrAbsLay absLay ;
			// absLay.clone(m_lay) ;
			// setLay(absLay) ;
			setLay(std::move(VrAbsLay().clone(m_lay)));
	}
}
void VrModel::createCollider() {
	p_collider = NULL ;
}
void VrModel::collide() {
	if(p_collider == NULL)
		return ;
	//else
	p_collider->collide(p_nodeKit, p_node) ;
	//TODO:need to deal with migrating to other roots...
	setIsMigrating(p_node->isMigrating()) ;
}
void VrModel::doStep(BwStepper& stepper) {
	BwActor::doStep(stepper);
	collide() ;
	if(hasBody() && ownsBody()) {
		p_body->invokeStep(stepper) ;
	}
}
void VrModel::doPostStep(BwStepper& stepper) {
	BwActor::doPostStep(stepper) ;

	if(hasBody() && ownsBody()) {
		p_body->invokePostStep(stepper) ;
		if(m_isAutoSleeper && p_body->isIdle())
			rest() ;
		else {
			unrest() ;
			m_dozeCounter = 0 ;
		}
	}
	if(m_isAutoSleeper && isIdle()) {
		if(m_dozeCounter >= m_dozeAlarm)
			setState(DOZING) ;
		else
			m_dozeCounter ++ ;
	}
	if(getMotionType() != MOTION_STATIC)
		invalidatePose() ;
	else
		validate() ;
	//
	validateNode() ; //TODO ... only validate when necessary!

	if(p_vu != NULL && !isPlace())
		p_vu->invokePostStep(stepper) ;
}
bool VrModel::onPostStep(BwStepper& stepper) {
	return BwActor::onPostStep(stepper) ;
}
void VrModel::invalidatePose() {
	invalidate(this, INVALID_POSE) ;
}
void VrModel::validatePose() {
	m_lay.validate() ;
	notifyFollowers() ;
	//TODO:newstuff
	if(m_tracer.isActive())
		m_tracer.validate() ;
}
void VrModel::invalidateSize() {
	invalidate(this, INVALID_SIZE | INVALID_MASS) ;
}
void VrModel::invalidateMass() {
	invalidate(this, INVALID_MASS) ;
}
void VrModel::validateMass() {
	if(hasBody() && ownsBody()) {
		if(m_bodyInfo.getMass() == bwRealTraits::Zero) {
			m_bodyInfo.setBox(m_size) ;
		}
		p_body->setBodyInfo(&m_bodyInfo);
	}
} ;
void VrModel::validateSize() {
	switch(m_nodeType) {
		case NODE_HEIGHTFIELD :
			m_radius = m_size[1] * bwRealTraits::Half ;
			break ;
		default :
			m_radius = m_size[2] * bwRealTraits::Half ;
	}
}
void VrModel::computeBoundsCorners(bwPoint3* pCorners) {
	bwPoint3 min = getMin() ;
	bwPoint3 max = getMax() ;

	pCorners[0] = min ;
	pCorners[1][0] = min[0]; pCorners[1][1] = max[1]; pCorners[1][2] = min[2];
	pCorners[2][0] = max[0]; pCorners[2][1] = max[1]; pCorners[2][2] = min[2];
	pCorners[3][0] = max[0]; pCorners[3][1] = min[1]; pCorners[3][2] = min[2];

	pCorners[4] = max;
	pCorners[5][0] = min[0]; pCorners[5][1] = max[1]; pCorners[5][2] = max[2];
	pCorners[6][0] = min[0]; pCorners[6][1] = min[1]; pCorners[6][2] = max[2];
	pCorners[7][0] = max[0]; pCorners[7][1] = min[1]; pCorners[7][2] = max[2];
}
void VrModel::validateBounds() {
	if(m_nodeType == NODE_BALL)
		m_bounds = bwBounds3(getWorldMin(), getWorldMax()) ;
	//else
	bwBounds3 spaceBounds ;
	bwPoint3 corners[8] ;
	computeBoundsCorners(corners) ;
	const bwQuat& quat = getQuat() ;
	for(size_t i = 0; i < 8; ++i ) {
		extendVolume(spaceBounds, bwPoint3(quat * corners[i])) ;
	}
	m_bounds = bwBounds3(spaceBounds.getMin() + getPos(), spaceBounds.getMax() + getPos()) ;
}
void VrModel::invalidate(VrModel *pModel, invalid flags) {
	if(flags == m_invalidFlags)
		return ;
	//else
	m_invalidFlags |= flags ;
	invalidateGroup(m_invalidFlags) ;
	if(pModel == this) {
		validate() ;
	}
}
void VrModel::validate() {
	doValidate() ;
	doPostValidate() ;
}
void VrModel::doValidate() {
	if(invalidPose())
		validatePose() ;
	if(invalidSize())
		validateSize() ;
	if(invalidPose() || invalidSize())
		validateBounds() ;
	if(invalidMass())
		validateMass() ;
	if(m_invalidFlags != INVALID_NONE)
		validateNode() ;
}
void VrModel::doPostValidate() {
	clearInvalidFlags() ;
}
void VrModel::invalidateGroup(invalid flags) {
	if(p_group == NULL)
		return ;
	p_group->invalidate(this, flags) ;
}
void VrModel::migrate() {
	m_isMigrating = false ;

	VrGroup *pGroup = getFutureGroup() ;
	if(pGroup == p_group)
		return ;
	if(pGroup == NULL)
		return ;
	doMigrate(p_group, pGroup) ;
	BwStage *pNewStage = pGroup->getStage() ;
	if(pNewStage != NULL) {
		pNewStage->scheduleActor(this) ;
	}
	pGroup->addModel(this) ;

	setGroup(pGroup) ;
}
//TODO:note:this should only be used for layout purposes!!!
void VrModel::migrate(VrGroup *pGroup) {
	m_isMigrating = false ;
	if(pGroup == p_group)
		return ;
	if(p_group != NULL) {
			doMigrate(p_group, pGroup) ;
		p_group->removeModel(this) ;
	}
	pGroup->addModel(this) ;
	setGroup(pGroup) ;
}
//
void VrModel::doMigrate(VrGroup* pOldGroup, VrGroup* pNewGroup) {
	pOldGroup->getNode()->detachNode(p_node) ;
	if(p_node != NULL)
		pNewGroup->getNode()->attachNode(p_node) ;
	p_futureGroup = NULL ;
	m_isMigrating = false ;
	p_node->m_isMigrating = false ;
}
void VrModel::createNode() {
	p_node = getNodeKit()->createNode(this) ;
	p_node->setNodeType(getNodeType()) ;
	//
	p_node->setCollider(p_collider) ;
	//
	p_node->setTestInternal(testInternal()) ;

	p_node->setIsEntity(isEntity()) ;
	p_node->m_isMigrant = m_isMigrant ;

	VrGroup *pGroup = getGroup() ;
	if(pGroup != NULL)
		pGroup->getNode()->attachNode(p_node) ;
}
void VrModel::validateNode() {
	if(p_node == NULL)
		return ;
	p_node->setPose(bwPose(getPos(), getQuat())) ;
	p_node->setBounds(getBounds()) ;
	p_node->m_radius = getRadius() ;
	p_node->validate() ;
}
void VrModel::createNodeKit() {
	p_nodeKit = getGroup()->getNodeKit() ;
}
//
void VrModel::setGroup(VrGroup *pGroup) {
	p_owner = p_group = pGroup ;
}
void VrModel::layout() {
	m_lay.validate() ;
	onLayout() ;
}
void VrModel::onLayout() {
}
void VrModel::createVu(void) {
	p_vu = new VrVu(this) ;
	p_vu->create() ;
}
void VrModel::_setSize(const bwSize3& size) {
	setInvalid(INVALID_SIZE) ;
	m_size = constrainSize(size) ;
}
//
bwPoint3 VrModel::getMin() {
	bwReal halfWidth = m_size[0] * bwRealTraits::Half ;
	bwReal halfHeight = m_size[1] * bwRealTraits::Half ;
	bwReal halfLength = m_size[2] * bwRealTraits::Half ;
	//AABB
	return bwPoint3(- halfWidth, - halfHeight, - halfLength) ;
}
bwPoint3 VrModel::getMax() {
	bwReal halfWidth = m_size[0] * bwRealTraits::Half ;
	bwReal halfHeight = m_size[1] * bwRealTraits::Half ;
	bwReal halfLength = m_size[2] * bwRealTraits::Half ;
	//AABB
	return bwPoint3(halfWidth, halfHeight, halfLength) ;
}
bwPoint3 VrModel::getWorldMin() { 	return getPos() + getMin() ;	}
bwPoint3 VrModel::getWorldMax() { 	return getPos() + getMax() ;	}

//
VrPlace* VrModel::getWorld() {
	return VrScenario::singleton::getPtr()->getWorld() ;
}
VrPlace* VrModel::getPlace() {
	if(isPlace())
		return static_cast<VrPlace*>(this) ;
	//else
	if(p_group != NULL)
		return p_group->getPlace() ;
	//else ... must be the world!
	return static_cast<VrPlace*>(this) ;
}
void VrModel::setLeader(VrModel *pLeader) {
	bwAssert(pLeader != this) ;
	if(p_leader != NULL)
		p_leader->removeFollower(this) ;

	p_leader = pLeader ;

	if(pLeader != NULL)
		pLeader->addFollower(this) ;
}
void VrModel::addFollower(VrModel *pFollower) {
	m_followers.push_back(pFollower) ;
}
void VrModel::removeFollower(VrModel *pFollower) {
	m_followers.erase(std::find(m_followers.begin(),m_followers.end(),pFollower)) ;
}
void VrModel::notifyFollowers() {
	if(!m_followers.empty()) {
		for (VrModelContainer::iterator iter = m_followers.begin();
				iter != m_followers.end(); ++iter)	{
			(*iter)->onLeader() ;
		}
	}
}
/////////
/*
 w,x,y,z
sqrt(0.5) 	sqrt(0.5) 	0 	0 	90' rotation around X axis
sqrt(0.5) 	0 	sqrt(0.5) 	0 	90' rotation around Y axis
sqrt(0.5) 	0 	0 	sqrt(0.5) 	90' rotation around Z axis

*/
void VrModel::setUpAxis(upAxis axis) {
	if(axis == AXIS_Z) m_alignment = bwQuat() ;
	if(axis == AXIS_Y) m_alignment = bwQuat(sqrt(0.5), 0, 0, sqrt(0.5)) ;
	if(axis == AXIS_X) m_alignment = bwQuat(sqrt(0.5), 0, sqrt(0.5), 0) ;
	//x ... later.
}
VrModel::upAxis VrModel::getUpAxis() {
	if(m_alignment[3] == bwRealTraits::One) return AXIS_Z ;
	if(m_alignment[2] == bwRealTraits::Zero) return AXIS_Y ;
	//else
	return AXIS_X ;
}
void VrModel::setBodyInfo(const VrBodyInfo *bodyInfo) {
	memcpy(&m_bodyInfo, bodyInfo, sizeof(VrBodyInfo)) ;
}
//
void VrModel::setTracer(VrTracer&& tracer) {
	memcpy(&m_tracer, &tracer, sizeof(VrTracer)) ;
	m_tracer.init() ;
}
