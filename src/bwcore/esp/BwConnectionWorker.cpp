/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwesp/BwConnectionWorker.h>
#include <bwesp/BwConnection.h>
#include <bwesp/BwCStream.h>

BwConnectionWorker::BwConnectionWorker(BwPart *pPart) 
	: BwWorker(pPart) {
}
void BwConnectionWorker::connect(const BwAddress& address) {
	m_connection.connect(address.getHostName(), address.getServiceName()) ;
}
void BwConnectionWorker::work() {
	while(isEnabled()) {
		BwMessage msg ;
		receive(msg) ;
		p_owner->dispatch(msg) ;
	}
}
void BwConnectionWorker::send(const BwMessage& msg) {
	BwCBuffer	espOutBuf(m_connection) ;
	BwCStreamOut	espOut(&espOutBuf) ;
	espOut << msg << end ;
}
void BwConnectionWorker::receive(const BwMessage& msg) {
	BwCBuffer	espInBuf(m_connection) ;
	BwCStreamIn	espIn(&espInBuf) ;
	espIn >> msg ;
}
