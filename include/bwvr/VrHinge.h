/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrHinge_H
#define _VrHinge_H

#include "VrJoint.h"
#include "VrJointRod.h"

//
//VrHingeRod1
//
class VrHingeRod1 : public VrJointRod {
public:
	VrHingeRod1(BwActor *pParent) : VrJointRod(pParent) {}
	virtual void setAxis(bwReal x, bwReal y, bwReal z) ;
	virtual bwReal getAngle() ;
	virtual void setLoStop(bwReal loStop) ;
	virtual void setHiStop(bwReal hiStop) ;
	virtual void setVelocity(bwReal value) ;
	virtual void setForceMax(bwReal value) ;
	virtual void addTorque(bwReal value) ;
};
//
//VrHinge
//
class VrHinge : public VrJoint {
public:
	VrHinge(VrGroup *pGroup) ;
	virtual ~VrHinge() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bwString getClassName() { return "VrHinge" ; }
	virtual VrRod* getRod1() { return &m_rod_1 ; }
	virtual void setAnchor(const bwPoint3& pos);
	virtual bwPoint3 getAnchor() ;
	virtual void setJointERP(bwReal erp) ;
	virtual void setJointCFM(bwReal cfm) ;
private:
	//Data
	VrHingeRod1 m_rod_1 ;
} ;

#endif //_VrHinge_H