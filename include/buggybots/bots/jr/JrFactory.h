/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#ifndef _JrFactory_H
#define _JrFactory_H

#include <bwvr/VrModelFactory.h>

class VrGroup ;

namespace Jr {
class Jr ;
class JrWheel ;
//
//JrWheelFactory
//
class JrWheelFactory : public VrModelFactory {
public:
	JrWheelFactory(BwKit *pKit) ;
	virtual VrModel* rent(int indice, VrGroup *pGroup) ;
	//Data Members
public:
	bwReal m_wheelRadius;
	bwPoint3 m_followPos ;
	bwReal m_wheelDensity;
	bwReal m_wheelJointERP;
	bwReal m_wheelJointCFM;
	//Singleton support
public:
	struct singleton_alloc {
		static JrWheelFactory* alloc() ;
	} ;
	typedef BwAutoSingletonT<JrWheelFactory, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;
//
//JrFactory
//
class JrFactory : public VrModelFactory {
public:
	JrFactory(BwKit *pKit) ;
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) ;
	//Data Members
	bwVector3 m_chassisPos;
	bwReal m_chassisDensity;
	//Singleton support
public:
	struct singleton_alloc {
		static JrFactory* alloc() ;
	} ;
	typedef BwAutoSingletonT<JrFactory, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;
}//end namespace BwVr::Bots::Jr
#endif //_JrFactory_H