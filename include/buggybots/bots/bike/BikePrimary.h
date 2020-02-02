/*BikeBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BikeBots_License.txt for details.
*/
#ifndef _BikePrimary_H
#define _BikePrimary_H

#include <bwvr/VrCapsule.h>
#include <bwvr/VrMech.h>
#include "BikeBrain.h"

class VrGroup ;

namespace Bike {

class Bike ;
class BikeFactory ;
class BikePrimary ;
class BikePrimary ;
class BikeMech ;

class BikePrimaryMech : public VrMech {
public:
	BikePrimaryMech(BikePrimary *pPrimary) ;

	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doConfig() ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doPostEnable(bool sleeping = false) ;
	//virtual bool doStep(BwStepper& stepper) ;
	virtual void doStep(BwStepper& stepper) ;
	//void setWheelPosition() ;
	BikeBrain& master() { return *static_cast<BikeBrain*>(p_master) ; }
	BikePrimary& primary() { return *getPrimary() ; }
	BikePrimary* getPrimary() { return p_primary ; }
	//Data Members
	BikePrimary *p_primary ;
	VrModel *p_chassis ;
} ;

class BikePrimary : public VrCapsule {
public:
	BikePrimary(VrGroup *pGroup, Bike *pRoot) ;
	virtual bwString getClassName() { return "BikePrimary" ; }
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createVu() ;
	virtual void createGeom() ;
	/*Data Members*/
	Bike *p_buggy ;
} ;
}//end namespace Bike
#endif //_BikePrimary_H
