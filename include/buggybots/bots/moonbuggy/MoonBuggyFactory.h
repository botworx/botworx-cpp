/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _MoonBuggyFactory_H
#define _MoonBuggyFactory_H

#include <bwvr/VrModelFactory.h>

class VrGroup ;

namespace MoonBuggy {
class Buggy ;
class BuggyWheel ;
//
//BuggyWheelFactory
//
class BuggyWheelFactory : public VrModelFactory {
public:
	BuggyWheelFactory(BwKit *pKit) ;
	virtual VrModel* rent(int indice, VrGroup *pGroup) ;
	//Data Members
	bwReal m_wheelRadius;
	bwPoint3 m_followPos ;
	bwReal m_wheelDensity;
	bwReal m_wheelJointERP;
	bwReal m_wheelJointCFM;
	//Singleton support
public:
	struct singleton_alloc {
		static BuggyWheelFactory* alloc() ;
	} ;
	typedef BwAutoSingletonT<BuggyWheelFactory, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;
//
//BuggyFactory
//
class BuggyFactory : public VrModelFactory {
public:
	BuggyFactory(BwKit *pKit) ;
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) ;
	Buggy* rentBuggy(VrGroup *pGroup) ;
	//Data Members
	bwVector3 m_chassisPos;
	bwReal m_chassisDensity;
	//Singleton support
public:
	struct singleton_alloc {
		static BuggyFactory* alloc() ;
	} ;
	typedef BwAutoSingletonT<BuggyFactory, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;

}//end namespace BwVr::Bots::MoonBuggy

#endif //_MoonBuggyFactory_H