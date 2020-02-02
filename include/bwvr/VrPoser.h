/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrPoser_H
#define _VrPoser_H

#include <bwcore/BwActor.h>

class VrPoser : public BwActor {
public:
	VrPoser(VrModel* pModel) ;
	virtual bwString getClassName() { return "VrPoser" ; }
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	//
	void pitchUp(bwReal degree) ;
	void pitchDown(bwReal degree) ;
	void rollLeft(bwReal degree) ;
	void rollRight(bwReal degree) ;
	void turnLeft(bwReal degree) ;
	void turnRight(bwReal degree) ;
	//
	void pitch(bwReal angle) ;
	void roll(bwReal angle) ;
	void yaw(bwReal angle) ;
	void rotate(const bwAxisAngle& axisAngle) ;
	//
	void moveForward(bwReal dist) ;
	void moveReverse(bwReal dist) ;
	void move(bwReal dist) ;
	void moveNone() ;

	//Jumping
	virtual void jump() ;
	virtual void jumpNone() ;

	void setPos(const bwPoint3& pos) { m_pos = pos ; }
	bwPoint3 getPos() { return m_pos ; }
	void setOldPos(const bwPoint3& pos) { m_oldPos = pos ; }
	bwPoint3 getOldPos() { return m_oldPos ; }

	void setQuat(const bwQuat& quat) ;
	bwQuat getQuat() { return m_quat ; }
	void setDirection(const bwVector3& dir) { setQuat(gmtl::makePure(dir)) ; }
	bwVector3 getDirection() { return gmtl::makeVec(getQuat()) ; }
	bwEuler getEuler() { return makeEulerFromQuaternion(getQuat()) ; }
	//
	VrModel* getModel() { return p_model ; }
	/*Data Members*/
	bwPoint3 m_pos ;
	bwPoint3 m_oldPos ;
	bwQuat m_quat ;
	bool m_isJumping ;

	VrModel *p_model ;

};

#endif //_VrPoser_H
