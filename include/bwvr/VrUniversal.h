/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrUniversal_H
#define _VrUniversal_H

#include "VrJointRod.h"
#include "VrJoint.h"
//
//VrUniversalRod1
//
class VrUniversalRod1 : public VrJointRod {
public:
	VrUniversalRod1(BwPart *pOwner) : VrJointRod(pOwner) {}
	virtual void setAxis(bwReal x, bwReal y, bwReal z) ;
	virtual bwReal getAngle() ;
	virtual void setLoStop(bwReal loStop) ;
	virtual void setHiStop(bwReal hiStop) ;
	virtual void setVelocity(bwReal value) ;
	virtual void setForceMax(bwReal value) ;
};
//
//VrUniversalRod2
//
class VrUniversalRod2 : public VrJointRod {
public:
	VrUniversalRod2(BwPart *pOwner) : VrJointRod(pOwner) {}
	virtual void setAxis(bwReal x, bwReal y, bwReal z) ;
	virtual bwReal getAngle() ;
	virtual void setLoStop(bwReal loStop) ;
	virtual void setHiStop(bwReal hiStop) ;
	virtual void setVelocity(bwReal value) ;
	virtual void setForceMax(bwReal value) ;
};
//
//VrUniversal
//
class VrUniversal : public VrJoint {
public:
	VrUniversal(VrGroup *pGroup) ;
	virtual ~VrUniversal() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bwString getClassName() { return "VrUniversal" ; }
	virtual VrRod* getRod1() { return &m_rod_1 ; }
	virtual VrRod* getRod2() { return &m_rod_2 ; }
	virtual void setAnchor(const bwPoint3& pos);
	bwPoint3 getAnchor() ;
	virtual void setJointERP(bwReal erp) ;
	virtual void setJointCFM(bwReal cfm) ;
	//Data
	VrUniversalRod1 m_rod_1 ;
	VrUniversalRod2 m_rod_2 ;
} ;

#endif //_VrUniversal_H