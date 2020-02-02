#ifndef _BbBrain_H
#define _BbBrain_H

#include <bwvr/VrBrain.h>

namespace BbSteer {
	class BbMarker ;
}
class VrPoser ;

class BbBrain : public VrBrain {
public:
	BbBrain(VrModel* pModel) ;
	virtual void doPostEnable(bool sleeping = false) ;
	//
	void setMarker(BbSteer::BbMarker* pMarker) { p_marker = pMarker ; }
	BbSteer::BbMarker& marker() { return *getMarker() ; }
	BbSteer::BbMarker* getMarker() { return p_marker ; }
	//Data Members
	BbSteer::BbMarker *p_marker ;
} ;

#endif _BbBrain_H