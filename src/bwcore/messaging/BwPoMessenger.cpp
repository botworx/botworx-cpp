/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwmessaging/BwPoMessenger.h>
#include <bwmessaging/BwAddress.h>
#include <bwmessaging/BwMailSlot.h>
#include <bwmessaging/BwPostOffice.h>

void BwPoMessenger::connect(BwMailSlot* pSlot) {
	BwLocalMessenger::connect(pSlot) ;
	p_upLinkPo = pSlot->getPo() ;
	p_downLinkPo = p_downLink->getPo() ;
}
void BwPoMessenger::send(const BwMessage& msg) {
	p_upLinkPo->holdMessage(msg, p_upLink) ;
}
void BwPoMessenger::receive(const BwMessage& msg, bool selfReflective) {
	//This is how we prevent a sender from receiving it's own message!
	if(p_downLink != msg.getSender())
		p_downLinkPo->holdMessage(msg, p_downLink) ;
}
