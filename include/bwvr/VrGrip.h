/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrGrip_H
#define _VrGrip_H

#include "VrGroup.h"
#include "VrShape.h"

class VrJoint ;
class VrBody ;

class VrGrip {
public:
	VrGrip(VrShape *pGripper) : p_gripper(pGripper), m_power(0) {}
	bool invokeStep(BwStepper& stepper) {
		doStep(stepper) ;
		return onStep(stepper) ;
	}
	virtual void doStep(BwStepper& stepper) {}
	virtual bool onStep(BwStepper& stepper) { return true ; }
	bool invokePostStep(BwStepper& stepper) {
		doPostStep(stepper) ;
		return onPostStep(stepper) ;
	}
	virtual void doPostStep(BwStepper& stepper) {}
	virtual bool onPostStep(BwStepper& stepper) { return true ; }
	virtual void grab(const bwPoint3& pos) { m_grabPoint = pos ; }
	virtual void release() {}
	//Data Members
	VrShape* p_gripper ;
	bwReal m_power ; //how tightly are we gripping the grippee?
	bwPoint3 m_grabPoint ;
	bwPoint3 m_oldPos ; //use to calc velocity.
} ;
class VrShapeGrip : public VrGrip {
public:
	VrShapeGrip(VrShape *pGripper, VrShape *pGrippee) : VrGrip(pGripper), p_grippee(pGrippee) {}
	//Data Members
	VrShape *p_grippee ;
} ;
class VrDynamicGrip : public VrShapeGrip {
public:
	VrDynamicGrip(VrShape *pGripper, VrShape *pGrippee) : VrShapeGrip(pGripper, pGrippee) {}
	virtual void doStep(BwStepper& stepper) ;
	virtual void grab(const bwPoint3& pos) ;
	virtual void release() ;
	//Data Members
	VrJoint *p_grabJoint ;
	VrBody *p_grabBody ;
	VrModel *p_grabModel ;
} ;
class VrStaticGrip : public VrShapeGrip {
public:
	VrStaticGrip(VrShape *pGripper, VrShape *pGrippee) : VrShapeGrip(pGripper, pGrippee) {}
	virtual void doStep(BwStepper& stepper) ;
	virtual void doPostStep(BwStepper& stepper) ;
	virtual void grab(const bwPoint3& pos) ;
	//Data Members
	bwPoint3 m_offset ;
} ;

#endif //_VrGrip_H
