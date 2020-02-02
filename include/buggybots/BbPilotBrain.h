#ifndef _BbPilotBrain_H
#define _BbPilotBrain_H

#include "BbBrain.h"

namespace BbSteer {
	class BbPilot ;
}
class VrPoser ;

class BbPilotBrain : public BbBrain {
public:
	BbPilotBrain(VrModel* pModel) ;
	virtual void doPostConfig() ;
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	//
	void setPilot(BbSteer::BbPilot* pPilot) ;
	BbSteer::BbPilot& pilot() { return *getPilot() ; }
	BbSteer::BbPilot* getPilot() ;
	//Data Members
	VrPoser* getPoser() { return p_poser ; }
	VrPoser *p_poser ;
} ;

#endif _BbPilotBrain_H