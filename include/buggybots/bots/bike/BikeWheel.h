/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#ifndef _BikeWheel_H
#define _BikeWheel_H

#include <bwvr/VrBall.h>
class VrRod ;

#include <bwvr/VrHinge2.h>
#include <bwvr/VrMech.h>
#include "BikeBrain.h"
namespace Bike {

class BikeWheelFactory ;
class BikePrimary ;
class BikeWheel ;
class BikeMech ;

class BikeWheelMech : public VrJointMech {
public:
	BikeWheelMech(BikeWheel *pWheel) ;

	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doConfig() ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doPostEnable(bool sleeping = false) ;
	void setWheelPosition() ;
	BikeBrain& master() { return *static_cast<BikeBrain*>(p_master) ; }
	//Data Members
	BikeWheel *p_wheel ;
	VrModel *p_chassis ;
} ;

class BikeWheel : public VrBall {
public:
	BikeWheel(int indice, Bike *pBike) ;
	virtual bwString getClassName() { return "Wheel" ; }
	virtual void doCreate(const BwPartInfo& info) ;
	BikeWheelFactory& factory() { return *static_cast<BikeWheelFactory*>(p_factory) ; }
	BikeWheelMech& brain() { return *static_cast<BikeWheelMech*>(p_brain) ; }
	virtual void createBrain() ;
	/*Data Members*/
	Bike *p_bike ;
private:
} ;
}//end namespace BwVr::Bots::Bike
#endif //_BikeWheel_H
