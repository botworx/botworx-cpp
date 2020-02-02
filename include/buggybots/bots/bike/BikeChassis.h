/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BikeChassis_H
#define _BikeChassis_H

#include <bwvr/VrFixedAssembly.h>

namespace Bike {
class Bike ;
class BikeFactory ;
class BikeBrain ;
class BikeEngine ;
class BikePrimary ;
class BikeWheel ;

class BikeChassis : public VrFixedAssembly {
public:
	BikeChassis(Bike *pBike) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bwString getClassName() { return "BikeChassis" ; }
	BikePrimary* getBikePrimary() { return p_bikePrimary ; }
	/*Data Members*/
	Bike *p_bike ;
	BikePrimary *p_bikePrimary ;
};
}//end namespace Bike

#endif //_BikeChassis_H
