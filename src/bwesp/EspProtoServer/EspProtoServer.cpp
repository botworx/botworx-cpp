// BwProtoServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <bwkernel/BwKernel.h>
#include <bwesp/BwConnection.h>
#include <bwesp/BwCStream.h>

#include <bwesp/BwLocalServer.h>
#include <bwesp/BwLocalServiceProvider.h>
#include <bwesp/BwLocalService.h>

#include <bwesp/_BwServer.h>
using namespace _BwServer ;

////////////
class ProtoServiceInSlot : public BwMailSlot {
public:
	ProtoServiceInSlot(BwService *pSvc, const bwString& name) : BwMailSlot(pSvc, name) {
		p_service = pSvc ; 
	}
	virtual void on_message(BwMessage msg) {
		bwWhat what = msg.what() ;
		_ASSERT(0) ; //f6:fixme:implement
	}
	//Data Members
	BwService *p_service ;
} ;
////////////////
//EventSlot
class ProtoServiceEventSlot : public BwMailSlot {
public:
	ProtoServiceEventSlot(BwService *pSvc, const bwString& name) : p_service(pSvc), BwMailSlot(pSvc, name) {
	}
	virtual void ProtoServiceEventSlot::on_message(BwMessage msg) {
		//_ASSERT(0) ; //f6:fixme:implement
		//No .. this is just for self reflection
	}
	//Data Members
	BwService *p_service ;
} ;


class ProtoService : public BwLocalService {
public:
	ProtoService(BwLocalServiceProvider *pProvider, const BwServiceRequest& request) : BwLocalService(pProvider, request) {}
	virtual void createMailCenter() {
		p_inSlot = new ProtoServiceInSlot(this, "IN") ;
		p_inSlot->create() ;
		m_mailBox.addSlot(p_inSlot) ;

		p_outSlot = new BwMailSlot(this, "OUT") ; 
		p_outSlot->create() ;
		m_mailBox.addSlot(p_outSlot) ;

		p_logSlot = new BwMailSlot(this, "LOG") ; 
		p_logSlot->create() ;
		m_mailBox.addSlot(p_logSlot) ;

		p_eventSlot = new ProtoServiceEventSlot(this, "EVENT") ;
		p_eventSlot->create() ;
		m_mailBox.addSlot(p_eventSlot) ;

		m_mailCenter.addBox(&m_mailBox, this) ;
	}
	virtual BwMailCenter& getMailCenter() { return m_mailCenter ; }
	//
	BwMailCenter m_mailCenter ;
} ;
class ProtoSP : public BwLocalServiceProvider {
public:
	ProtoSP(BwServer* pServer, bwString name) : BwLocalServiceProvider(pServer, name) {}
	virtual BwService* produceService(BwServiceRequest& request) {
		BwService* pSvc = new ProtoService(this, request) ;
		pSvc->create() ;
		return pSvc ;
	}
} ;
void BwServerTest() {
	BwLocalServer& server = BwLocalServer::singleton::get() ;
	ProtoSP* pSP = new ProtoSP(&server, "PROTO") ;
	server.addServiceProvider(pSP) ;

	server.listen() ;
	char buf[32] ;
	std::cin >> buf ;
}

int main(int argc, char* argv[])
{

	BwKernel::startup() ;

	BwServerTest() ;

	BwKernel::shutdown() ;
	return 0;
}

