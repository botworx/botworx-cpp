/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrController_H
#define _VrController_H

#include <bwcontrol/BwController.h>
#include <bwcontrol/BwControllerEvent.h>

class VrUser ;
class VrScene ;
class BwBrain ;
class VrScenario ;

class VrController : public BwController {
public:
	VrController(VrController *pSuper) ;
	virtual void bind() ;
	virtual void unbind() ;
	VrScenario& scenario() { return *getScenario() ; }
	VrScenario* getScenario() ;
	//Data Members
};

#endif //_VrController_H