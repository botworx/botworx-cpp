/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrCamera.h>
#include <bwvr/VrCameraVu.h>
#include <bwvr/VrCollider.h>
#include <bwvr/VrLay.h>
#include <bwvr/VrModelOps.h>

/////////////////
////////////////////
#include <bwvr/VrBrain.h>
#include <bwcontrol/BwPersonality.h>
#include <bwcontrol/BwTaskGroup.h>
#include <bwvr/VrPhysics.h>

class VrCameraBrain ;

class VrCameraPersonality : public BwPersonality {
public:
	VrCameraPersonality(BwBrain* pBrain) : BwPersonality(pBrain) {
		m_taskGroup.setIsMutex(true) ;
	}
	virtual BwTask* produceTask(const bwString& name) ;
	//Data Members
	BwTaskGroup m_taskGroup ;
};
class VrCameraBrain : public VrBrain {
public:
	VrCameraBrain(VrCamera *pCamera) ;
	virtual void doPostEnable(bool sleeping = false) ;
	virtual void createPersonality() ;
	//Data Members
public:
	VrCamera *p_camera ;
	VrCameraPersonality m_personality ;
};
class VrCameraTask : public BwTask {
public:
	VrCameraTask(VrCameraBrain *pBrain) : BwTask(pBrain) {
		p_brain = pBrain ;
		p_camera = pBrain->p_camera ;
	}
	//Data
public:
	VrCameraBrain *p_brain ;
	VrCamera *p_camera ;
};
class VrCamera_FollowFollow : public VrCameraTask {
public:
	VrCamera_FollowFollow(VrCameraBrain *pBrain) : VrCameraTask(pBrain) {
		m_name = "FOLLOW_FOLLOW" ;
	}
	virtual void doStep(BwStepper& stepper) ;
	//Data
public:
};
class VrCamera_FollowLook : public VrCameraTask {
public:
	VrCamera_FollowLook(VrCameraBrain *pBrain) : VrCameraTask(pBrain) {
		m_name = "FOLLOW_LOOK" ;
	}
	virtual void doStep(BwStepper& stepper) ;
	//Data
public:
};
class VrCamera_LookLook : public VrCameraTask {
public:
	VrCamera_LookLook(VrCameraBrain *pBrain) : VrCameraTask(pBrain) {
		m_name = "LOOK_LOOK" ;
	}
	virtual void doStep(BwStepper& stepper) ;
	//Data
public:
};

VrCameraBrain::VrCameraBrain(VrCamera *pCamera) : VrBrain(pCamera), m_personality(NULL) {
	p_camera = pCamera ;
}
void VrCameraBrain::createPersonality() {
	p_personality = &m_personality ;
	m_personality.setBrain(this) ;
}
void VrCameraBrain::doPostEnable(bool sleeping){
	BwBrain::doPostEnable(sleeping) ;
	personality().useTask("FOLLOW_FOLLOW") ;
}
BwTask* VrCameraPersonality::produceTask(const bwString& name) {
	BwTask* pTask = NULL ;
	VrCameraBrain* pBrain = static_cast<VrCameraBrain*>(p_brain) ;
	//TODO:need to replace with factories soon.
	if(name == "FOLLOW_FOLLOW")
		pTask = new VrCamera_FollowFollow(pBrain) ;
	else
	if(name == "FOLLOW_LOOK")
		pTask = new VrCamera_FollowLook(pBrain) ;
	else
	if(name == "LOOK_LOOK")
		pTask = new VrCamera_LookLook(pBrain) ;

	if(pTask != NULL) {
		pTask->setTaskGroup(&m_taskGroup) ;
	}
	return pTask ;
}
void VrCamera_FollowFollow::doStep(BwStepper& stepper) {
	BwTask::doStep(stepper) ;
	bwDT deltaTime = VrPhysics::singleton::get().getDeltaTime() ;
	VrModel* pLeader = p_camera->getLeader() ;
	if(pLeader == NULL)
		return ;
	bwPoint3 leaderPos = p_camera->getLeader()->getPos() ;
	p_camera->setFocalPos(leaderPos) ;
	bwMatrix3x3 r ;
	bwQuat followQuat ;

	bwQuat quat = p_camera->getLeader()->getQuat() ;
	gmtl::setRot(r, quat) ;

	bwVector3 worldVector = vectorToWorld(r, 0, 0, -1) ;

	bwReal followDistance = p_camera->getFollowDistance() ;
	bwReal followHeight = p_camera->getFollowHeight() ;
	bwVector3 desiredPos( leaderPos[0] + worldVector[0] * followDistance,
						//leaderPos[1] + worldVector[1] * followDistance + followHeight, 
						leaderPos[1]  + followHeight, 
						leaderPos[2] + worldVector[2] * followDistance) ;

	bwPoint3 camPos = p_camera->getPos() + (bwReal(4 * deltaTime) * (desiredPos - p_camera->getPos()) );

	//if(camPos[1] < followHeight) camPos[1] = followHeight ;

	p_camera->setPos(camPos) ;
	p_camera->setQuat(quat) ;
}
void VrCamera_FollowLook::doStep(BwStepper& stepper) {
	BwTask::doStep(stepper) ;
	bwDT deltaTime = VrPhysics::singleton::get().getDeltaTime() ;
	VrModel* pLeader = p_camera->getLeader() ;
	if(pLeader == NULL)
		return ;
	bwPoint3 leaderPos = p_camera->getLeader()->getPos() ;
	p_camera->setFocalPos(leaderPos) ;
	bwMatrix3x3 r ;
	bwQuat quat ;
	bwQuat followQuat ;

	//unique
	quat = p_camera->getLeader()->getQuat() * p_camera->m_followQuat ;

	gmtl::setRot(r, quat) ;

	bwVector3 worldVector = vectorToWorld(r, 0, 0, -1) ;

	bwReal followDistance = p_camera->getFollowDistance() ;
	bwReal followHeight = p_camera->getFollowHeight() ;
	bwVector3 desiredPos( leaderPos[0] + worldVector[0] * followDistance,
						leaderPos[1] + worldVector[1] * followDistance + followHeight, 
						leaderPos[2] + worldVector[2] * followDistance) ;

	bwPoint3 camPos = p_camera->getPos() + (bwReal(4 * deltaTime) * (desiredPos - p_camera->getPos()) );

	//if(camPos[1] < followHeight) camPos[1] = followHeight ;

	p_camera->setPos(camPos) ;
	p_camera->setQuat(quat) ;
}
void VrCamera_LookLook::doStep(BwStepper& stepper) {
	BwTask::doStep(stepper) ;
	bwDT deltaTime = VrPhysics::singleton::get().getDeltaTime() ;
	VrModel* pLeader = p_camera->getLeader() ;
	if(pLeader == NULL)
		return ;
	bwPoint3 leaderPos = p_camera->getLeader()->getPos() ;
	bwMatrix3x3 r ;
	bwQuat quat ;
	bwQuat followQuat ;

	//unique
	quat = p_camera->m_followQuat ;

	gmtl::setRot(r, quat) ;

	bwVector3 worldVector = vectorToWorld(r, 0, 0, -1) ;

	bwReal followDistance = p_camera->getFollowDistance() ;
	bwReal followHeight = p_camera->getFollowHeight() ;
	bwVector3 desiredPos( leaderPos[0] + worldVector[0] * followDistance,
						leaderPos[1] + worldVector[1] * followDistance + followHeight, 
						leaderPos[2] + worldVector[2] * followDistance) ;

	bwPoint3 camPos = p_camera->getPos() + (bwReal(4 * deltaTime) * (desiredPos - p_camera->getPos()) );

	//if(camPos[1] < followHeight) camPos[1] = followHeight ;

	p_camera->setPos(camPos) ;
	p_camera->setQuat(quat) ;

	bwMatrix3x3 fr ;
	set(fr, quat) ;
	bwPoint3 focusPos = p_camera->getPos() + ( r * bwVector3(0,0,10) ) ;
	p_camera->setFocalPos(focusPos) ;
}

/////////////////

VrCamera::VrCamera(VrGroup *pGroup) : VrBall(pGroup) {
	m_modeSwitchTimer.setAlarm(std::chrono::seconds(1)) ;
	setMotionType(MOTION_KINEMATIC) ;
	setIsGhost(true) ;
	m_isAutoSleeper = false ;
}
void VrCamera::createBrain() {
	p_brain = new VrCameraBrain(this) ;
	p_brain->create() ;
}
void VrCamera::createDynamicLay() {
	// VrAbsLay absLay ;
	// absLay.clone(m_lay) ;
	// setLay(absLay) ;
	setLay(std::move(VrAbsLay().clone(m_lay))) ;
}
void VrCamera::createVu() {
	p_vu = new VrCameraVu(this) ;
	p_vu->create() ;
}