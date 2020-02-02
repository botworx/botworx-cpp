#include "stdafx.h"


#include <bwesp/BwLocalService.h>
#include <bwesp/BwLocalServiceProvider.h>
#include <bwesp/BwLocalSession.h>
#include <bwesp/BwConnection.h>
#include <bwesp/BwCStream.h>

#include <bwmessaging/BwMailSlot.h>
#include <bwmessaging/BwAddress.h>

#include <bwesp/_BwServer.h>
using namespace _BwServer ;

BwLocalService::BwLocalService(BwLocalServiceProvider* pProvider, const BwServiceRequest& request) 
	: BwService(pProvider), m_request(request) {
}
BwLocalServiceProvider& BwLocalService::getProvider() { 
	return *static_cast<BwLocalServiceProvider*>(p_owner) ; 
}
BwSession* BwLocalService::produceSession() {
	BwLocalSession* pSession = new BwLocalSession(this) ;
	pSession->create() ;
	return pSession ;
}