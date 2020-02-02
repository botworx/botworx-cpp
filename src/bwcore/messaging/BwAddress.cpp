/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwmessaging/BwAddress.h>

BwAddress::BwAddress() {
	m_hostName = DEFAULT_HOST ;
	m_serviceName = DEFAULT_SERVICE ;
}
BwAddress::BwAddress(
			const bwString& hostName, 
			const bwString& serviceName = DEFAULT_SERVICE) {
	m_hostName = hostName ;
	m_serviceName = serviceName ;
}
//
const bwString BwAddress::DEFAULT_HOST = "localhost" ;
const bwString BwAddress::DEFAULT_SERVICE = "9665" ;
