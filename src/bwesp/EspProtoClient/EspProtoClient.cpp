// BwProtoClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <bwmessaging/BwAddress.h>
#include <bwkernel/BwKernel.h>
#include <bwesp/BwConnection.h>
#include <bwesp/BwCBuffer.h>
#include <bwesp/BwCStream.h>

#include <bwesp/BwLocalServer.h>
#include <bwesp/BwCluster.h>
#include <bwesp/BwRemoteServer.h>
#include <bwesp/BwRemoteServiceProvider.h>
#include <bwesp/BwService.h>

#include "EspProtoProxy.h"

#include <bwkernel/_BwPart.h>
using namespace _BwPart ;

void BwClientTest() {
	
	BwRemoteServer* pRemoteServer = new BwRemoteServer(BwLocalServer::singleton::getPtr(), BwNetAddress("/", "localhost", "9665")) ;
	pRemoteServer->create() ;
	BwServiceProvider* pProvider = new BwRemoteServiceProvider(pRemoteServer, "PROTO") ;
	pProvider->create() ;
	pRemoteServer->addServiceProvider(pProvider) ;

	BwRemoteCluster::singleton::get().addServer(pRemoteServer) ;
	//
	BwServiceRequest request("PROTO") ;
	BwService* pService = BwRemoteCluster::singleton::get().createService(request) ;	
	BwSession* pSession = pService->createSession() ;

	EspProtoClient *pClient = new EspProtoClient(NULL) ;
	pClient->connect(pSession) ;
}

int main(int argc, char* argv[])
{
	BwKernel::startup() ;

	BwClientTest() ;

	BwKernel::shutdown() ;

	return 0;
}

