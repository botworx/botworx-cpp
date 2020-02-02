/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbExplosion_H
#define _BbExplosion_H

#include <bwvr/VrGroup.h>
#include <bwvr/VrBall.h>

class BbExplosion : public VrBall {
public:
	BbExplosion(VrGroup *pGroup) ;
	virtual void createCollider() ;
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	virtual bwString getClassName() { return "BbExplosion" ; }
	void setPower(bwReal power) { m_power = power ; }
	bwReal getPower() { return m_power ; }
	void setParticleVel(bwParticle& particle, const bwVector3& unit) ;
	//
	/*Data Members*/
public:
	bwReal m_power ;
};

#endif //_BbExplosion_H
