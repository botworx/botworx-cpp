/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrHinge2_H
#define _VrHinge2_H

#include "VrJointRod.h"
#include "VrJoint.h"
//
//VrHinge2Rod1
//
class VrHinge2Rod1 : public VrJointRod {
public:
	VrHinge2Rod1(BwActor *pParent) : VrJointRod(pParent) {}
	virtual void setAxis(bwReal x, bwReal y, bwReal z) ;
	virtual bwReal getAngle() ;
	virtual void setLoStop(bwReal loStop) ;
	virtual void setHiStop(bwReal hiStop) ;
};
//
//VrHinge2Rod2
//
class VrHinge2Rod2 : public VrJointRod {
public:
	VrHinge2Rod2(BwActor *pParent) : VrJointRod(pParent) {}
	virtual void setAxis(bwReal x, bwReal y, bwReal z) ;
	virtual bwReal getAngle() ;
	virtual void setVelocity(bwReal value) ;
	virtual void setForceMax(bwReal value) ;

};
//
//VrHinge2
//
class VrHinge2 : public VrJoint {
public:
	VrHinge2(VrGroup *pGroup) ;
	virtual ~VrHinge2() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bwString getClassName() { return "VrHinge2" ; }
	virtual VrRod* getRod1() { return &m_rod_1 ; }
	virtual VrRod* getRod2() { return &m_rod_2 ; }
	virtual void setAnchor(const bwPoint3& pos);
	bwPoint3 getAnchor() ;
	virtual void setJointERP(bwReal erp) ;
	virtual void setJointCFM(bwReal cfm) ;
	//Data
	VrHinge2Rod1 m_rod_1 ;
	VrHinge2Rod2 m_rod_2 ;
} ;

#endif //_VrHinge2_H
