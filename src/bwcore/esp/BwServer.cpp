/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwesp/BwServer.h>

#include <bwesp/BwServiceProvider.h>
#include <bwesp/BwService.h>

BwServer::BwServer(BwPart *pPart, const BwAddress& address)
	: BwSystem(pPart), m_address(address) {

	m_serviceCount = 0 ;
}
void BwServer::addServiceProvider(BwServiceProvider* pProvider) {
	m_serviceProviders.push_back(pProvider) ;
	m_serviceProvidersByName[pProvider->getName()] = pProvider ;
	//TODO:kitstuff
	addKit(pProvider) ;
}
BwServiceProvider* BwServer::findServiceProvider(const bwString& spName) {
	return m_serviceProvidersByName[spName] ;
}
BwService* BwServer::createService(BwServiceRequest& request) {
	BwServiceProvider* pProvider = findServiceProvider(request.getSpName()) ;
	BwService* pSvc = pProvider->createService(request) ;
	bwAssert(pSvc) ;
	addService(pSvc) ;
	return pSvc ;
}
//TODO:a lot of this needs to be made thread safe!!!
void BwServer::addService(BwService *pSvc) {
	//m_services.push_front(pSvc) ;
	pSvc->setHandle(m_serviceCount++) ; //TODO:use handle pool
	m_services.push_back(pSvc) ; //TODO:maybe use a list
}
BwService* BwServer::findService(bwHandle svcHandle) {
	BwService *pSvc = m_services[svcHandle] ; //TODO:use hashmap ... and handle pool!!!
	return pSvc ;
}
