// BwProtoServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//Agent stuff
#include <bwagency/BwAgency.h>
#include <BwMiaAgentSystem.h>
#include <bwkernel/BwKernel.h>

#include <bwesp/BwLocalServer.h>
#include <bwesp/BwLocalServiceProvider.h>
#include <bwesp/BwLocalService.h>

#include <bwesp/_BwServer.h>
using namespace _BwServer ;

void BwServerTest() {
	std::cout << "Botworx Agent Daemon\n" ;
	BwLocalAgency::singleton::get().addAgentSystem(new BwMiaAgentSystem(BwLocalAgency::singleton::getPtr())) ;
	BwLocalServer::singleton::get().listen() ;
	char buf[32] ;
	std::cin >> buf ;
}

int main(int argc, char* argv[]) {

	BwKernel::startup() ;

	BwServerTest() ;

	BwKernel::shutdown() ;

	return 0;
}