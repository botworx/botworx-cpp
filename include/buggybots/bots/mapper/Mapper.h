/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _Mapper_H
#define _Mapper_H

#include <bwvr/VrBox.h>
#include <buggybots/BbMap.h>

class Mapper : public VrBox {
public:
	Mapper(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "Mapper" ; }
	virtual void createCollider() ;
	virtual void doPostStep(BwStepper& stepper) ;
	void mapIt(BwStepper& stepper, const bwPoint3& pos) ;
	//Data Members
};

#endif //_Mapper_H
