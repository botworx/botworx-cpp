/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrJoint_H
#define _VrJoint_H

#include <bwvr/VrJointBase.h>

class VrPhysics ;

class VrJoint : public VrJointBase {
public:
	VrJoint(VrGroup *pGroup) ;
	virtual ~VrJoint() ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doDisable(bool sleeping = true) ;

	virtual bwString getClassName() { return "VrJoint" ; }
	dJointID getJointID() { return m_jointID ; }
	virtual void setJointERP(bwReal erp) {}
	virtual void setJointCFM(bwReal cfm) {}
	//////////////////////////
	virtual void setAnchor(const bwPoint3& pos) { setPos(pos) ; }
	void setAnchor(bwReal x, bwReal y, bwReal z) { setAnchor(bwPoint3(x, y, z)) ; }
	virtual bwPoint3 getAnchor() { return getPos() ; }
	//
	virtual void createDynamicLay() ;
protected:
	//Data
	dJointID m_jointID ;
} ;

typedef std::list<VrJoint*> VrJointList ;

//
class VrJointLay : public VrAbsLay {
public:
	VrJointLay() : VrAbsLay() {}
	virtual bwString getClassName() { return "VrJointLay" ; }
	virtual void validate() ;
	//Accessors
	VrJoint& getJoint() ;
	/*Data Members*/
};

#endif //_VrJoint_H