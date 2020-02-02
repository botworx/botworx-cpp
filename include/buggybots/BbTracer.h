/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbTracer_H
#define _BbTracer_H

#include <bwvr/VrTracer.h>
#include <buggybots/BbPilot.h>

class BbTracer : public VrTracer {
public:
	BbTracer(BbSteer::BbMarker* pMarker) : VrTracer() { p_marker = pMarker ;	}
	virtual ~BbTracer() ;
	virtual void init() ;
	virtual bwString getClassName() { return "BbTracer" ; }
	virtual void validate() ;
	//convenience functions
	BbSteer::BbMarker& marker() { return *static_cast<BbSteer::BbMarker*>(p_marker) ; }
	//Data Members
} ;
///////////////////////////////////////////////
class BbDynamicTracer : public BbTracer {
public:
	BbDynamicTracer(BbSteer::BbMarker* pMarker) : BbTracer(pMarker) {}
	virtual ~BbDynamicTracer() ;
	//virtual void init() ;
	virtual bwString getClassName() { return "BbDynamicTracer" ; }
	virtual void validate() ;
	//convenience functions
	//Data Members
} ;
///////////////////////////////////////////////
class BbPilotTracer : public BbTracer {
public:
	BbPilotTracer(BbSteer::BbMarker* pMarker) : BbTracer(pMarker) {}
	virtual ~BbPilotTracer() ;
	//virtual void init() ;
	virtual bwString getClassName() { return "BbPilotTracer" ; }
	virtual void validate() ;
	//convenience functions
	BbSteer::BbPilot& pilot() { return *static_cast<BbSteer::BbPilot*>(p_marker) ; }
	//Data Members
} ;

#endif //_BbTracer_H