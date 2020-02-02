/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#ifndef _Jr_H
#define _Jr_H

#include <bwvr/VrDynamicAssembly.h>
#include "JrFactory.h"

class BbMissileLauncher ;
class BbLaserGun ;
class VrSteering ;

#include <bwvr/VrMech.h>

namespace Jr {
class Jr ;
class JrFactory ;
class JrBrain ;
class JrEngine ;
class JrChassis ;
class JrBody ;
class JrWheel ;

class Jr : public VrDynamicAssembly
{
public:
	Jr(VrGroup *pGroup) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createBrain() ;
	virtual ~Jr();

	JrFactory& factory() { return *static_cast<JrFactory*>(p_factory) ; }
	virtual bwString getClassName() { return "Jr::Jr" ; }

	BbMissileLauncher* getMissiles() { return p_missiles ; }

	virtual void fireMissile() ;
	virtual void fireLaser() ;

	JrWheel* getWheelAt(int index) { return p_wheel[index] ; }
	enum {
		WHEEL_RL = 0,
		WHEEL_RR,
		WHEEL_TTL
	} ;
private:
	JrWheel *p_wheel[WHEEL_TTL] ;
	BbMissileLauncher *p_missiles ;
	BbLaserGun *p_lasers ;
public:
	void rollLeft(bwReal degree) ;
	void rollRight(bwReal degree) ;

	void flip(bwReal fx, bwReal fy, bwReal fz, bwReal px, bwReal py, bwReal pz) ;
	//
};
} //end namespace BwVr::Bots::Jr
#endif

