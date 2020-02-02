/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwApplet_H
#define _BwApplet_H

#include <bwcore/BwRunner.h>
#include <bwmessaging/BwMailBox.h>

class BwKernel ;
class BwMailSlot ;
class BwDocSession ;

class BwApplet : public BwRunner
{
public:
	BwApplet();
	virtual ~BwApplet();
	virtual void doCreate(const BwPartInfo& info);
	virtual void doPostEnable(bool sleeping = false);
	//
	bwPath getMediaPath() ;
	//Messaging
	virtual void createMailCenter() ;
	BwDocSession* getDocSession() { return p_docSession ; }
	BwDocSession* p_docSession ;

	BwMailBox& getMailBox() { return m_mailBox ; }
	BwMailBox m_mailBox ;
	
	BwMailSlot& getInSlot() { return *p_inSlot ; }
	BwMailSlot& getOutSlot() { return *p_outSlot ; }
	BwMailSlot& getEventSlot() { return *p_eventSlot ; }
	BwMailSlot& getLogSlot() { return *p_logSlot ; }
	//
	BwMailSlot *p_inSlot ;
	BwMailSlot *p_outSlot ;
	BwMailSlot *p_eventSlot ;
	BwMailSlot *p_logSlot ;

protected:
	/*Data Members*/
	BwMailSlot* p_kernelEvents ;
private:
	virtual void onGo() ;
	virtual void onStop() ;
	virtual bool setup(void);
	virtual bool configure(void);
	virtual void setupResources(void) ;
	virtual void loadResources(void) ;
};

#endif //_BwApplet_H

