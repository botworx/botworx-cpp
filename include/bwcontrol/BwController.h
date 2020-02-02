/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwController_H
#define _BwController_H

#include <bwcore/BwActor.h>

class BwBrain ;

class BwMessage ;
class BwControllerEvent ;

class BwController : public BwActor {
public:
	BwController(BwController *pSuper) ;
	virtual void activate() ;
	virtual void deactivate() ;
	bool isActive() { return m_isActive ; }
	virtual void bind() { m_isBound = true ; }
	virtual void unbind() { m_isBound = false ; }
	bool isBound() { return m_isBound ; }
	virtual bool processEvent(BwControllerEvent&& evt) ;
	//Data Members
	bool m_isActive ;
	bool m_isBound ;
	BwController *p_super ;
};

#endif //_BwController_H