/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrJointBase.h>
#include <bwvr/VrBody.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrMech.h>

VrJointBase::VrJointBase(VrGroup *pGroup) : VrModel(pGroup) {
	m_isMigrant = false ;
	setMotionType(MOTION_KINEMATIC) ;
	vuInfo().setMeshName("VrBall.mesh") ;
	p_model_1 = NULL ;
	p_model_2 = NULL ;
}
VrJointBase::~VrJointBase() {
}
//TODO:can't we do this in the constructor?
void VrJointBase::doCreate(const BwPartInfo& info) {
	VrModel::doCreate(info) ;
	setRadius(.1f) ;
}
void VrJointBase::attachModels(VrModel *pModel1, VrModel *pModel2) {
	p_model_1 = pModel1 ;
	p_model_2 = pModel2 ;
}
VrRod* VrJointBase::getRod1() {
	return NULL ;
}
VrRod* VrJointBase::getRod2() {
	return NULL ;
}