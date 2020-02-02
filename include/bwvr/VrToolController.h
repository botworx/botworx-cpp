/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrToolController_H
#define _VrToolController_H

#include "VrController.h"

class VrToolController : public VrController
{
public:
	VrToolController(VrController *pSuper) ;
	virtual void bind() ;
	virtual void unbind() ;
	virtual bool processEvent(BwControllerEvent&& evt) ;
	VrModel* getTool() { return p_tool ; }
	/*Data Members*/
	VrModel *p_tool ;
};

#endif //_VrToolController_H