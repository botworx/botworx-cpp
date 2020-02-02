/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrHand_H
#define _VrHand_H

#include "VrBall.h"
#include <bwscheduling/BwTimer.h>

class VrJoint ;
class VrBody ;

class VrGrip ;

class VrHand : public VrBall {
public:
	VrHand(VrGroup *pGroup) ;
	virtual void createCollider() ;
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	virtual bwString getClassName() { return "VrHand" ; }
	//
	void grabShape(VrShape *pShape, const bwPoint3& pos) ;
	void release() ;
	//
	void setFollowEuler(const bwEuler& euler) { 
		m_followEuler = euler ; 
		bwQuat pitchQ, yawQ, rollQ ;
		set(pitchQ, bwAxisAngle(m_followEuler[0], bwVector3(1,0,0))) ;
		set(yawQ, bwAxisAngle(m_followEuler[1], bwVector3(0,1,0))) ;
		set(rollQ, bwAxisAngle(m_followEuler[2], bwVector3(0,0,1))) ;
		m_followQuat = yawQ * pitchQ * rollQ ;
	}
	bwEuler getFollowEuler() { return m_followEuler ; }

	void setFollowQuat(const bwQuat& quat) { m_followQuat = quat ; }
	bwQuat getFollowQuat() { return m_followQuat ; }

	void setFollowDistance(bwReal distance) { m_followDistance = distance ; }
	bwReal getFollowDistance() { return m_followDistance ; }
	void setFollowHeight(bwReal height) { m_followHeight = height ; }
	bwReal getFollowHeight() { return m_followHeight ; }
	int getMotionMode() { return m_motionMode ; }
	//
	enum {
		FOLLOW_FOLLOW = 0,
		FOLLOW_LOOK,
		LOOK_FOLLOW,
		LOOK_LOOK,
		CM_TTL
	};
	void toggleMotionMode() { 
		if(!m_modeSwitchTimer.checkAlarm())
			return ;
		//else
		m_modeSwitchTimer.resetAlarm() ;

		m_motionMode += 1 ;
		if(m_motionMode >= CM_TTL)
			m_motionMode = 0 ;
	}
	//
	int m_motionMode ;
	BwLoTimer m_modeSwitchTimer ;
	bwEuler m_followEuler ;
	bwQuat m_followQuat ;
	bwReal m_followDistance ;
	bwReal m_followHeight ;

	void setGrabMode(int mode) { m_grabMode = mode ; }
	int getGrabMode() { return m_grabMode ; }
	//
	VrModel* build(const bwString& name, const bwPose& pose = bwPose(), bool sleeping = false) ;
	VrModel* buildEnabled(const bwString& name, const bwPose& pose = bwPose(), bool sleeping = false) ;
	/*Data Members*/
public:
	enum {
		GM_NONE = 0,
		GM_GRAB
	} ;
	int m_grabMode ;
	//TODO:newstuff
	VrGrip* p_grip ; //could allow multiple grips in the future? ...
};

#endif //_VrHand_H
