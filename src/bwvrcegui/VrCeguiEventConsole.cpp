/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvrcegui/VrCeguiEventConsole.h>
#include <bwvrcegui/VrCeguiGuiController.h>
#include <bwvrcegui/VrCeguiControlPanel.h>
#include <bwvrcegui/VrCeguiUserMode.h>

#include <bwvr/VrScene.h>

#include <bwmessaging/BwMailSlot.h>

#include <bwcore/BwKernel.h>
#include <bwcore/_BwKernel.h>
using namespace _BwKernel ;

#include <CEGUI/CEGUI.h>
/////////////////////////////////////////
class VrCeguiEventConsole_KernelEvents : public BwMailSlot {
public:
	VrCeguiEventConsole_KernelEvents(VrCeguiEventConsole *pConsole, const bwString& name) : BwMailSlot(pConsole, name) {
		p_console = pConsole ; 
	}
	virtual void dispatch(BwMessage& msg) {
		bwWhat what = msg.what() ;
		switch(what) {
			case KERNEL_WARNING :
			case KERNEL_INFO : {
				bwString description ;
				msg()->findString("Description", description) ;
				p_console->write(description) ;
			}
		}
	}
	//Data Members
	VrCeguiEventConsole *p_console ;
} ;
/////////////////////////////////////////

VrCeguiEventConsole::VrCeguiEventConsole(VrCeguiGui *pGui) : VrCeguiConsole(pGui) {
}
VrCeguiEventConsole::~VrCeguiEventConsole() {
	p_kernelEvents->disconnect() ;
	delete p_kernelEvents ;
}
void VrCeguiEventConsole::doCreate(const BwPartInfo& info) {
	VrCeguiConsole::doCreate(info) ;

	p_kernelEvents = new VrCeguiEventConsole_KernelEvents(this, "EVENT") ;
	p_kernelEvents->create() ;
	p_kernelEvents->connect(BwKernel::singleton::get().getEventSlot()) ;
}