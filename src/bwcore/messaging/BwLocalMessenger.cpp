/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwmessaging/BwLocalMessenger.h>
#include <bwmessaging/BwAddress.h>
#include <bwmessaging/BwMailSlot.h>

void BwLocalMessenger::connect(BwMailSlot* pSlot) {
	p_upLink = pSlot ;
	p_upLink->addSubscriber(this) ;
}
void BwLocalMessenger::disconnect() {
	p_upLink->removeSubscriber(this) ;
}
void BwLocalMessenger::send(const BwMessage& msg) {
	p_upLink->send(msg) ;
}
void BwLocalMessenger::receive(const BwMessage& msg, bool selfReflective) {
	//This is how we prevent a sender from receiving it's own message!
	if(p_downLink != msg.getSender())
		p_downLink->receive(msg) ;
}
