/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"
#include <bwapplet/BwApplet.h>
#include <bwmessaging/BwMessaging.h>
#include <bwcore/BwKernel.h>
#include <bwcore/_BwKernel.h>
#include <bwapplet/_BwApplet.h>
using namespace _BwApplet ;

////////////
class BwAppletInSlot : public BwMailSlot {
public:
	BwAppletInSlot(BwApplet *pDoc, const bwString& name) : BwMailSlot(pDoc, name) {
		p_document = pDoc ;
	}
	virtual void dispatch(const BwMessage& msg) {
		bwWhat what = msg.what() ;
		bwAssert(0) ; //TODO:implement
	}
	//Data Members
	BwApplet *p_document ;
} ;
////////////////
//EventSlot
class BwAppletEventSlot : public BwMailSlot {
public:
	BwAppletEventSlot(BwApplet *pDoc, const bwString& name) : p_document(pDoc), BwMailSlot(pDoc, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
	}
	//Data Members
	BwApplet *p_document ;
} ;

class BwApplet_KernelEvents : public BwMailSlot {
public:
	BwApplet_KernelEvents(BwApplet *pApplet, const bwString& name) : BwMailSlot(pApplet, name) {
		p_applet = pApplet ;
	}
	virtual void receive(const BwMessage& msg, bool selfReflective = false) {
		if(msg.what() == _BwKernel::KERNEL_SHUTDOWN)
			p_applet->stop() ;
	}
	//Data Members
	BwApplet *p_applet ;
} ;

BwApplet::BwApplet(void) : BwRunner(nullptr), m_mailBox(nullptr) {
	m_mailBox.setOwner(this) ;
	m_name = "Applet" ;
}
BwApplet::~BwApplet() {
}
void BwApplet::doCreate(const BwPartInfo& info) {
	BwRunner::doCreate(info) ;
	createMailCenter() ;
	bool success = setup();
	//if(!success) throw BwGeneralException("BwApplet:  Setup failed") ;
}
void BwApplet::doPostEnable(bool sleeping) {
	BwRunner::doPostEnable(sleeping) ;
}
void BwApplet::createMailCenter() {
	p_inSlot = new BwAppletInSlot(this, "IN") ;
	//p_inSlot->setIsSelfReflective(false) ;
	p_inSlot->create() ;
	m_mailBox.addSlot(p_inSlot) ;

	p_outSlot = new BwMailSlot(this, "OUT") ;
	p_outSlot->create() ;
	m_mailBox.addSlot(p_outSlot) ;

	p_logSlot = new BwMailSlot(this, "LOG") ;
	p_logSlot->create() ;
	m_mailBox.addSlot(p_logSlot) ;

	p_eventSlot = new BwAppletEventSlot(this, "EVENT") ;
	p_eventSlot->create() ;
	m_mailBox.addSlot(p_eventSlot) ;

	//External Connections
	p_kernelEvents = new BwApplet_KernelEvents(this, "KERNEL_EVENT") ;
	p_kernelEvents->create() ;
	//p_kernelEvents->connect(p_kernel->getEventSlot()) ;
	p_kernelEvents->connect(BwKernel::singleton::get().getEventSlot()) ;
}
void BwApplet::onStop() {
}
void BwApplet::onGo() {
}
bool BwApplet::setup(void) {
    return true;
}
bool BwApplet::configure(void) {
	return true ;
}
void BwApplet::setupResources(void) {
}
void BwApplet::loadResources(void) {
}
bwPath BwApplet::getMediaPath() {
	bwPath path = BwKernel::singleton::get().getMediaPath() / getName() ;
	return path ;
}
