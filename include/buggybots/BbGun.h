/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbGun_H
#define _BbGun_H

#include <bwvr/VrGroup.h>
//#include "VrBox.h"
#include <bwvr/VrCapsule.h>

//class BbGun : public VrBox {
class BbGun : public VrCapsule {
public:
	BbGun(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "BbGun" ; }
	//
	void pullTrigger() { m_triggerState = true ; onTrigger() ; }
	void releaseTrigger() { m_triggerState = false ; onTrigger() ; }
	bool getTriggerState() { return m_triggerState ; }
	virtual void onTrigger() {}
	/*Data Members*/
	bool m_triggerState ;
};

#endif //_BbGun_H
