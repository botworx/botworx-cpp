/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrBallJoint_H
#define _VrBallJoint_H

#include "VrJoint.h"
//
//VrBallJoint
//
class VrBallJoint : public VrJoint {
public:
	VrBallJoint(VrGroup *pGroup) ;
	virtual ~VrBallJoint() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void setAnchor(const bwPoint3& pos) ;
	virtual bwPoint3 getAnchor() ;
	//Data
} ;

#endif //_VrBallJoint_H