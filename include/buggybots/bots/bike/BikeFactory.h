/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#ifndef _BikeFactory_H
#define _BikeFactory_H

#include <bwvr/VrModelFactory.h>

class VrGroup ;

namespace Bike {
class Bike ;
class BikeWheel ;
//
//BikeWheelFactory
//
class BikeWheelFactory : public VrModelFactory {
public:
	BikeWheelFactory(BwKit *pKit) ;
	virtual VrModel* rent(int indice, VrGroup *pGroup) ;
	//Data
	bwReal m_wheelRadius;
	bwPoint3 m_followPos ;
	bwReal m_wheelDensity;
	bwReal m_wheelJointERP;
	bwReal m_wheelJointCFM;
	//Singleton support
public:
	struct singleton_alloc {
		static BikeWheelFactory* alloc() ;
	} ;
	typedef BwAutoSingletonT<BikeWheelFactory, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;
//
//BikeFactory
//
class BikeFactory : public VrModelFactory {
public:
	BikeFactory(BwKit *pKit) ;
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) ;
	Bike* rentBike(VrGroup *pGroup) ;
	//Data Members
	bwVector3 m_chassisPos;
	bwReal m_chassisDensity;	
	//Singleton support
public:
	struct singleton_alloc {
		static BikeFactory* alloc() ;
	} ;
	typedef BwAutoSingletonT<BikeFactory, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;
}//end namespace Bike
#endif //_BikeFactory_H