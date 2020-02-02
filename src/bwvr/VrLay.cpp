/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrLay.h>
#include <bwvr/VrGroup.h>
#include <bwvr/VrBody.h>

VrModel& VrLay::model() { 
	VrModel *pModel = ((VrModel*)((bwByte*)this - offsetof(VrModel, m_lay))) ;
	return *pModel ;
}
VrGroup* VrLay::getGroup() { return model().getGroup() ; }
VrBody* VrLay::getBody() { return model().getBody() ; }
VrLay& VrLay::clone(const VrLay& lay) {
	if(&lay == NULL) //TODO:Wtf?  References can't be NULL
		return *this;
	m_pos = lay.m_pos ;
	m_relPos = lay.m_relPos ;
	m_quat = lay.m_quat ;
	m_relQuat = lay.m_relQuat ;
	return *this;
}
void VrLay::invalidate() { 
	model().invalidatePose() ;
}
void VrLay::validate() {
}
void VrLay::setPos(const bwPoint3& point) {
	_setPos(point) ;
	invalidate() ;
}
void VrLay::setRelPos(const bwPoint3& point) { 
	_setRelPos(point) ;
	invalidate() ;
}
void VrLay::setQuat(const bwQuat& quat) { 
	_setQuat(quat) ;
	invalidate() ;
}
void VrLay::setRelQuat(const bwQuat& quat) { 
	_setRelQuat(quat) ;
	invalidate() ;
}
//
void VrLay::_setPos(const bwPoint3& point) {
	m_pos = point ;
}
void VrLay::_setRelPos(const bwPoint3& point) {
	m_relPos = point ;
}
void VrLay::_setQuat(const bwQuat& quat) {
	m_quat = quat ;
}
void VrLay::_setRelQuat(const bwQuat& quat) {
	m_relQuat = quat ;
}

//
bwPoint3 VrLay::getOrigin() {
	return m_pos ;
}
//
//VrAbsLay
//
void VrAbsLay::_setPos(const bwPoint3& point) {
	m_pos = point ;
}
void VrAbsLay::_setRelPos(const bwPoint3& point) {
	m_relPos = point ;
}
void VrAbsLay::_setQuat(const bwQuat& quat) {
	m_quat = quat ;
}
void VrAbsLay::_setRelQuat(const bwQuat& quat) {
	m_relQuat = quat ;
}
//
//VrRelLay
//
void VrRelLay::_setPos(const bwPoint3& point) {
	VrGroup *pGroup = getGroup() ;
	if(pGroup != NULL) {
		bwPoint3 groupPos = pGroup->getPos() ;
		m_relPos = point - groupPos ;
	}
	else
		m_relPos = point ;

	m_pos = point ;
}
void VrRelLay::_setRelPos(const bwPoint3& point) {
	VrGroup *pGroup = getGroup() ;
	if(pGroup != NULL) {
		bwPoint3 groupPos = pGroup->getPos() ;
		m_pos = groupPos + point ;
	}
	else
		m_pos = point ;

	m_relPos = point ;
}
void VrRelLay::_setQuat(const bwQuat& quat) {
	m_quat = quat ; 
	VrGroup *pGroup = getGroup() ;
	if(pGroup != NULL)
		m_relQuat = quat / pGroup->getQuat() ;
	else
		m_relQuat = quat ;
}
void VrRelLay::_setRelQuat(const bwQuat& quat) {
	m_relQuat = quat ;
	VrGroup *pGroup = getGroup() ;
	if(pGroup != NULL)
		m_quat = pGroup->getQuat() * quat ;
	else
		m_quat = quat ;
}
void VrRelLay::validate() {
	VrGroup *pGroup = getGroup() ;
	if(pGroup == NULL)
		return ;
	bwQuat groupQuat = pGroup->getQuat() ;

	m_pos = groupQuat * m_relPos + pGroup->getPos() ;
	m_quat = groupQuat * m_relQuat ;
}
/////
void VrFollowLay::validate() {
	bwQuat leaderQuat = model().getLeader()->getQuat() ;

	m_pos  = leaderQuat * m_relPos + model().getLeader()->getPos() ;
	m_quat = leaderQuat * m_relQuat ;
}
void VrFollowLay::onLeader() {
	invalidate() ;
}
//
//VrBodyAbsLay
//
void VrBodyAbsLay::validate() {
	m_pos = getBody()->getPos() ;
	m_quat = getBody()->getQuat() ;
}
//
//VrBodyRelLay
//
void VrBodyRelLay::validate() {
	bwQuat bodyQuat = getBody()->getQuat() ;

	m_pos = bodyQuat * m_relPos + getBody()->getPos() ;
	m_quat = bodyQuat * m_relQuat ;
}
//
//VrOriginRelLay
//
bwPoint3 VrOriginRelLay::getOrigin() {
	bwSize3 size = model().getSize() ;

	if(	size == bwSize3())
		return m_pos ;

	bwReal halfWidth = size[0] * bwRealTraits::Half ;
	bwReal halfHeight = size[1] * bwRealTraits::Half ;
	bwReal halfLength = size[2] * bwRealTraits::Half ;

	bwQuat quat = model().getQuat() ;

	bwPoint3 halfPoint(-halfWidth, -halfHeight, halfLength) ;
	bwPoint3 origin = quat * halfPoint + m_pos ;
	return origin ;
}
//
void VrOriginRelLay::_setPos(const bwPoint3& point) {
	VrGroup *pGroup = getGroup() ;
	if(pGroup != NULL) {
		bwPoint3 groupOrigin = pGroup->getOrigin() ;
		m_relPos = point - groupOrigin ;
	}
	else
		m_relPos = point ;

	m_pos = point ;
}
void VrOriginRelLay::_setRelPos(const bwPoint3& point) {
	VrGroup *pGroup = getGroup() ;
	if(pGroup != NULL) {
		bwPoint3 groupOrigin = pGroup->getOrigin() ;
		m_pos = groupOrigin + point ;
	}
	else
		m_pos = point ;

	m_relPos = point ;
}
void VrOriginRelLay::_setQuat(const bwQuat& quat) {
	m_quat = quat ; 
	VrGroup *pGroup = getGroup() ;
	if(pGroup != NULL)
		m_relQuat = quat / pGroup->getQuat() ;
	else
		m_relQuat = quat ;
}
void VrOriginRelLay::_setRelQuat(const bwQuat& quat) {
	m_relQuat = quat ;
	VrGroup *pGroup = getGroup() ;
	if(pGroup != NULL)
		m_quat = pGroup->getQuat() * quat ;
	else
		m_quat = quat ;
}
void VrOriginRelLay::validate() {
	VrGroup *pGroup = getGroup() ;
	if(pGroup == NULL)
		return ;
	bwQuat groupQuat = pGroup->getQuat() ;
	bwQuat spaceQuat = groupQuat * m_relQuat ;

	bwSize3 size = model().getSize() ;
	bwReal halfWidth = size[0] * bwRealTraits::Half ;
	bwReal halfHeight = size[1] * bwRealTraits::Half ;
	bwReal halfLength = size[2] * bwRealTraits::Half ;

	bwPoint3 centerPoint = spaceQuat * bwPoint3(halfWidth, halfHeight, -halfLength) ;

	m_pos = groupQuat * m_relPos + pGroup->getOrigin() + centerPoint ;
	m_quat = spaceQuat ;
}