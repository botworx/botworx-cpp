/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCamera_H
#define _VrCamera_H

#include "VrBall.h"
#include <bwscheduling/BwTimer.h>

class VrCamera : public VrBall {
public:
	VrCamera(VrGroup *pGroup) ;
	virtual void createVu() ;
	virtual void createDynamicLay() ;
	virtual void createBrain() ;

	void setFocalPos(const bwPoint3& pos) { m_focalPos = pos ; }
	bwPoint3 getFocalPos() { return m_focalPos ; }

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
	//Data Members
	BwLoTimer m_modeSwitchTimer ;
	bwPoint3 m_focalPos ;
	bwEuler m_followEuler ;
	bwQuat m_followQuat ;
	bwReal m_followDistance ;
	bwReal m_followHeight ;
};

#endif //_VrCamera_H