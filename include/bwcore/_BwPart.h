#ifndef __BwPart_H
#define __BwPart_H

#include <bwmessaging/BwMessage.h>

namespace _BwPart {
	enum {
		MSG_nullptr = 0,
		EVENT_INIT,
		EVENT_DESTROY,
		INPUT_TEXT,
		COMMAND_TEXT,
		COMMAND_PAUSE,
		COMMAND_CLOSE,
		OUTPUT_TEXT,
		RESPONSE_SUCCESS,
		RESPONSE_FAILURE,
		RESPONSE_TEXT,
		BWPART_MSG_TTL
	} ;
} //end namespace _BwPart 

//Event
class BwEvent : public BwMessage {
public:
	BwEvent(bwWhat what) : BwMessage(what) {}
} ;
//Output
class BwOutput : public BwMessage {
public:
	BwOutput(bwWhat what) : BwMessage(what) {}
} ;
class BwTextOutput : public BwOutput {
public:
	BwTextOutput(const bwString& txt) : BwOutput(_BwPart::OUTPUT_TEXT) {
		m_data->addString("Output", txt) ;
	}
} ;
//Commands
class BwCommand : public BwMessage {
public:
	BwCommand(bwWhat what) : BwMessage(what) {}
} ;
class BwTextCommand : public BwCommand {
public:
	BwTextCommand(const bwString& cmd) : BwCommand(_BwPart::COMMAND_TEXT) {
		m_data->addString("Command", cmd) ;
	}
} ;
//Responses
class BwResponse : public BwMessage {
public:
	BwResponse(const BwMessage& msg, int what) : BwMessage(what) { m_data->m_handle = msg.handle() ; }
} ;
class BwSuccess : public BwResponse {
public:
	BwSuccess(const BwMessage& msg) : BwResponse(msg, _BwPart::RESPONSE_SUCCESS) {}
} ;
class BwFailure : public BwResponse {
public:
	BwFailure(const BwMessage& msg) : BwResponse(msg, _BwPart::RESPONSE_FAILURE) {}
} ;
class BwTextResponse : public BwResponse {
public:
	BwTextResponse(const BwMessage& msg, const bwString& cmd) : BwResponse(msg, _BwPart::RESPONSE_TEXT) {
		m_data->addString("Response", cmd) ;
	}
} ;

#endif //__BwPart_H