#ifndef _BbPersonality_H
#define _BbPersonality_H

#include <bwcontrol/BwPersonality.h>
#include "BbBrain.h"

class BbPersonality : public BwPersonality {
public:
	BbPersonality(BbBrain* pBrain) : BwPersonality(pBrain) {
	}
	BbBrain& brain() { return *static_cast<BbBrain*>(getBrain()) ; }
	BbSteer::BbMarker& marker() { return *getMarker() ; }
	BbSteer::BbMarker* getMarker() { return brain().getMarker() ; }
	//Data Members
} ;

#endif //_BbPersonality_H
