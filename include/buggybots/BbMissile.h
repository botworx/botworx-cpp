/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbMissile_H
#define _BbMissile_H

#include <bwvr/VrGroup.h>
#include <bwvr/VrBall.h>
#include <bwscheduling/BwTimer.h>

#define MAX_MISSILES 3

class BbMissile ;

typedef std::list<BbMissile*> BbMissileList ;
typedef std::list<BbMissile*>::iterator BbMissileIter ;

class BbMissileConfig {
public:
	bwPoint3 m_pos ;
	bwQuat m_quat ;
	bwVector3 m_linearVel ;
};

class BbMissile : public VrBall {
public:
	BbMissile(VrGroup *pGroup) ;
	virtual ~BbMissile() ;
	void createEnabled(BbMissileConfig *pConfig) ;
	virtual void createCollider() ;
	virtual void createVu() ;
	//virtual bool doStep(BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	virtual bwString getClassName() { return "BbMissile" ; }
	/*Data Members*/
public:
	static const bwReal diameter ;
	bwPoint3 m_impactPos ;
	BwLoTimer m_lifeTimer ;
};

#endif //_BbMissile_H
