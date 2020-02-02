#ifndef __BwServer_H
#define __BwServer_H

#include <bwcore/_BwPart.h>

/*namespace _BwServer {
	using namespace _BwPart ;
	enum {
		BWSERVER_EVENT_TTL = BWPART_EVENT_TTL
	} ;
	enum {
		//COMMAND_CREATE_SERVER_STUB = BWPART_INPUT_TTL,
		COMMAND_CREATE_SERVER_STUB = 65000,
		COMMAND_CREATE_SERVICE,
		COMMAND_CREATE_SESSION,
		COMMAND_CREATE_SERVICE_STUB,
		COMMAND_FIND_BOX,
		COMMAND_FIND_SLOT,
		BWSERVER_INPUT_TTL
	} ;
	enum {
		//RESPONSE_SERVER_STUB_CREATED = BWPART_OUTPUT_TTL,
		RESPONSE_SERVER_STUB_CREATED = 65000,
		RESPONSE_SERVICE_CREATED,
		RESPONSE_SESSION_CREATED,
		RESPONSE_SERVICE_STUB_CREATED,
		RESPONSE_BOX_FOUND,
		RESPONSE_SLOT_FOUND,
		BWSERVER_OUTPUT_TTL
	} ;
} //end namespace _BwServer {*/
namespace _BwServer {
	using namespace _BwPart ;
	enum {
		//COMMAND_CREATE_SERVER_STUB = BWPART_INPUT_TTL,
		COMMAND_CREATE_SERVER_STUB = 65000,
		COMMAND_CREATE_SERVICE,
		COMMAND_CREATE_SESSION,
		COMMAND_CREATE_SERVICE_STUB,
		COMMAND_FIND_BOX,
		COMMAND_FIND_SLOT,
		RESPONSE_SERVER_STUB_CREATED,
		RESPONSE_SERVICE_CREATED,
		RESPONSE_SESSION_CREATED,
		RESPONSE_SERVICE_STUB_CREATED,
		RESPONSE_BOX_FOUND,
		RESPONSE_SLOT_FOUND,
		BWSERVER_MSG_TTL
	} ;
} //end namespace _BwServer {

//Command
class BwCreateServerStub : public BwCommand {
public:
	BwCreateServerStub() : BwCommand(_BwServer::COMMAND_CREATE_SERVER_STUB) {
	}
} ;
//Response
class BwServerStubCreated : public BwResponse {
public:
	BwServerStubCreated(const BwMessage& msg, bwHandle hServerStub) : BwResponse(msg, _BwServer::RESPONSE_SERVER_STUB_CREATED) {
		m_data->addHandle("H_SERVER_STUB", hServerStub) ;
	}
} ;
//Command
class BwServiceRequest : public BwMessage {
public:
	BwServiceRequest(const BwMessage& msg) : BwMessage(msg) {}
	BwServiceRequest(const bwString& spName,
		const bwString& svcName = "NONAME",
		bool async = true,
		bool enabled = true,
		bwWhat what = _BwServer::COMMAND_CREATE_SERVICE)
	{
		data().m_what = what ;
		data().addString("SPNAME", spName) ;
		data().addString("SVCNAME", svcName) ;
		data().addBool("ASYNC", async) ;
		data().addBool("ENABLED", enabled) ;
	}
	bwString getSpName() const {
		bwString val ;
		data().findString("SPNAME", val) ;
		return val ;
	}
	bwString getSvcName() const {
		bwString val ;
		data().findString("SVCNAME", val) ;
		return val ;
	}
	bool getAsync() const {
		bwBool val ;
		data().findBool("ASYNC", val) ;
		return val ;
	}
	bool getEnabled() const {
		bwBool val ;
		data().findBool("ENABLED", val) ;
		return val ;
	}
} ;
class BwCreateService : public BwServiceRequest {
public:
	BwCreateService(const bwString& spName,
		const bwString& svcName = "NONAME",
		bool async = true,
		bool enabled = true)
		: BwServiceRequest(spName, svcName, async, enabled, _BwServer::COMMAND_CREATE_SERVICE)
	{}
} ;
//Response
class BwServiceCreated : public BwResponse {
public:
	BwServiceCreated(const BwMessage& msg, bwHandle serviceHandle) : BwResponse(msg, _BwServer::RESPONSE_SERVICE_CREATED) {
		m_data->addHandle("H_SERVICE", serviceHandle) ;
	}
} ;
class BwCreateServiceStub : public BwCommand {
public:
	BwCreateServiceStub(bwHandle hService, bwHandle hProxy) : BwCommand(_BwServer::COMMAND_CREATE_SERVICE_STUB) {
		m_data->addHandle("H_SERVICE", hService) ;
		m_data->addHandle("H_PROXY", hProxy) ;
	}
} ;
//Response
class BwServiceStubCreated : public BwResponse {
public:
	BwServiceStubCreated(const BwMessage& msg, bwHandle hStub) : BwResponse(msg, _BwServer::RESPONSE_SERVICE_STUB_CREATED) {
		m_data->addHandle("H_STUB", hStub) ;
	}
} ;
//Boxes
class BwFindBox : public BwCommand {
public:
	BwFindBox(bwHandle hStub, bwHandle hBox) : BwCommand(_BwServer::COMMAND_FIND_BOX) {
		m_data->addHandle("H_STUB", hStub) ;
		m_data->addHandle("H_BOX", hBox) ;
	}
} ;
//Response
class BwBoxFound : public BwResponse {
public:
	BwBoxFound(const BwMessage& msg, bwHandle hBox) : BwResponse(msg, _BwServer::RESPONSE_BOX_FOUND) {
		m_data->addHandle("H_BOX", hBox) ;
	}
} ;
//Slots
class BwFindSlot : public BwCommand {
public:
	BwFindSlot(bwHandle hStub, bwHandle hBox, const bwString& slotName) : BwCommand(_BwServer::COMMAND_FIND_SLOT) {
		m_data->addHandle("H_STUB", hStub) ;
		m_data->addHandle("H_BOX", hBox) ;
		m_data->addString("N_SLOT", slotName) ;
	}
} ;
//Response
class BwSlotFound : public BwResponse {
public:
	BwSlotFound(const BwMessage& msg, bwHandle slotHandle) : BwResponse(msg, _BwServer::RESPONSE_SLOT_FOUND) {
		m_data->addHandle("H_SLOT", slotHandle) ;
	}
} ;

#endif //__BwServer_H
