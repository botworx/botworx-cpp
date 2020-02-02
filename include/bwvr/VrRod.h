/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrRod_H
#define _VrRod_H

#include <bwcore/BwPart.h>

class VrRod : public BwPart {
public:
	VrRod(BwPart *pOwner) ;
	virtual void setAxis(bwReal x, bwReal y, bwReal z) ;
	virtual void setLoStop(bwReal value) ;
	virtual void setHiStop(bwReal value) ;
	virtual void setVelocity(bwReal value) ;
	virtual void setForceMax(bwReal value) ;
	virtual void addTorque(bwReal value) ;
	//
	virtual void setAngle(bwReal angle) ;
	virtual bwReal getAngle() ;
	void setHasAngleLimits(bool val) { m_hasAngleLimits = val ; }
	bool hasAngleLimits() { return m_hasAngleLimits ; }
	void setAngleMin(bwReal value) { m_angleMin = value ; }
	bwReal getAngleMin() { return m_angleMin ; }
	void setAngleMax(bwReal value) { m_angleMax = value ; }
	bwReal getAngleMax() { return m_angleMax ; }
	//Data
	bool m_hasAngleLimits ;
	bwReal m_angle ;
	bwReal m_angleMin ;
	bwReal m_angleMax ;
	//bwReal m_angleRate ;
} ;

typedef std::list<VrRod*> VrRodContainer ;

#endif //_VrRod_H