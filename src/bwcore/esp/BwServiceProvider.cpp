#include "stdafx.h"

#include <bwesp/BwServiceProvider.h>
#include <bwesp/BwService.h>
#include <bwesp/BwServer.h>

BwServiceProvider::BwServiceProvider(BwServer *pServer, const bwString& name) : BwSystem(pServer) {
	setName(name) ;
}
BwServer& BwServiceProvider::getServer() { 
	return *static_cast<BwServer*>(p_owner) ; 
}
