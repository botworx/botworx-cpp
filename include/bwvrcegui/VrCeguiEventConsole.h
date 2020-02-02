/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrCeguiEventConsole_H
#define _VrCeguiEventConsole_H

#include "VrCeguiConsole.h"

class BwMailSlot ;
//
//VrCeguiEventConsole
//
class VrCeguiEventConsole : public VrCeguiConsole {
public:
    VrCeguiEventConsole(VrCeguiGui *pGui) ;
    virtual ~VrCeguiEventConsole() ;
    virtual void doCreate(const BwPartInfo& info) ;
public:
	//Data Members
	BwMailSlot *p_kernelEvents ;
};
#endif //_VrCeguiEventConsole_H
