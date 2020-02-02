/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwmessaging/BwMessaging.h>
#include <bwcore/BwKernel.h>

void purgeMsgData(BwMsgData *pData) {
	pData->BwMsgData::~BwMsgData() ;
	BwMessaging::singleton::get().p_msgDataKit->release(pData) ;
}
//
BwMessaging::BwMessaging(BwPart *pPart) : BwSystem(pPart) {
	p_msgDataKit = new BwMsgDataKit(this) ;
	addKit(p_msgDataKit) ;
	p_msgFieldKit = new BwMsgFieldKit(this) ;
	addKit(p_msgFieldKit) ;
}
//Singleton support
template<> BwMessaging* BwMessaging::singleton::g_singleton = 0 ;