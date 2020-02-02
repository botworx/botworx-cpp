/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwesp/BwPoWorker.h>
#include <bwmessaging/BwPostOffice.h>

BwPoWorker::BwPoWorker(BwPart *pOwner) : BwWorker(pOwner) {
	p_po = nullptr ;
}
void BwPoWorker::doCreate(const BwPartInfo& info) {
	BwWorker::doCreate(info) ;
	if(p_po == nullptr)
		p_po = &BwPostOffice::singleton::get() ;
}
void BwPoWorker::work() {
	while(isEnabled()) {
		p_po->deliver_notify() ;
	}
}
