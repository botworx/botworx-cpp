#include "stdafx.h"

#include "EspProtoProxy.h"
#include <bwesp/BwSession.h>
#include <bwmessaging/BwIoSlot.h>
#include <bwmessaging/BwCmd.h>

#include <bwesp/_BwService.h>
using namespace _BwService ;

namespace _EspProtoClient {
class MyMailSlot : public BwMailSlot {
public:
	MyMailSlot(EspProtoClient *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {
		p_proxy = pOwner ;
	}
	//Data Members
	EspProtoClient *p_proxy ;
} ;
class SvcOut : public MyMailSlot {
public:
	SvcOut(EspProtoClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void on_message(BwMessage msg) {
		switch(msg.what()) {
			case RESPONSE_TEXT :
				p_proxy->onResponse(msg) ;
				break ;
			case OUTPUT_TEXT :
				p_proxy->onOutput(msg) ;
			break ;
		}
	}
} ;
class SvcLog : public MyMailSlot {
public:
	SvcLog(EspProtoClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void on_message(BwMessage msg) {
		switch(msg.what()) {
			case OUTPUT_TEXT :
				p_proxy->onLog(msg) ;
			break ;
		}
	}
} ;
class SvcEvents : public MyMailSlot {
public:
	SvcEvents(EspProtoClient *pOwner, const bwString& name) : MyMailSlot(pOwner, name) {
	}
	virtual void on_message(BwMessage msg) {
		p_proxy->onEvent(msg) ;
	}
} ;
} ; //namespace _EspProtoClient
/////////////////
using namespace _EspProtoClient ;

EspProtoClient::EspProtoClient(BwPart *pOwner) : BwClient(pOwner) {

	p_outSlot = new SvcOut(this, "OUT") ;
	p_outSlot->create() ;
	addSlot(p_outSlot) ;

	p_logSlot = new SvcLog(this, "LOG") ;
	p_logSlot->create() ;
	addSlot(p_logSlot) ;

	p_inSlot = new BwMailSlot(this, "IN") ;
	p_inSlot->create() ;
	addSlot(p_inSlot) ;

	p_eventSlot = new SvcEvents(this, "EVENT") ;
	p_eventSlot->create() ;
	addSlot(p_eventSlot) ;
}
void EspProtoClient::onOutput(BwMessage msg) {
	bwString out ;
	msg()->findString("Output", out) ;
	std::cout << out ;
}
void EspProtoClient::onLog(BwMessage msg) {
}
void EspProtoClient::onResponse(BwMessage msg) {
	m_hasResponse = true ;
}
void EspProtoClient::onEvent(BwMessage msg) {
	switch(msg.what()) {
		case EVENT_DESTROY :
			onServiceExit() ;
		break ;
	}
}