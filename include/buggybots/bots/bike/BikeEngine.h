#ifndef _BUGGYENGINE_H
#define _BUGGYENGINE_H

#include <bwvr/VrMotor.h>
#include <bwvr/VrMech.h>

namespace Bike {
class BikeEngine : public VrMotor {
public:
	BikeEngine(VrMech *pMech) ;
	void setPower(bwReal power) ;
};
}//end namespace BwVr::Bots::Bike
#endif //_BUGGYENGINE_H