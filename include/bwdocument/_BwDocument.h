#ifndef __BwDocument_H
#define __BwDocument_H

//#include <bwmessaging/BwMessage.h>
#include <bwcore/_BwPart.h>

/*namespace _BwDocument {
	using namespace _BwPart ;
	enum {
		EVENT_OPEN = BWPART_EVENT_TTL,
		EVENT_SAVE,
		EVENT_CLOSE,
		BWDOCUMENT_EVENT_TTL
	} ;
	enum {
		BWDOCUMENT_INPUT_TTL = BWPART_INPUT_TTL
	} ;
	enum {
		BWDOCUMENT_OUTPUT_TTL = BWPART_OUTPUT_TTL
	} ;
} //end namespace _BwDocument {*/
namespace _BwDocument {
	using namespace _BwPart ;
	enum {
		EVENT_OPEN = BWPART_MSG_TTL,
		EVENT_SAVE,
		EVENT_CLOSE,
		BWDOCUMENT_MSG_TTL
	} ;
} //end namespace _BwDocument {

class BwOpenEvent : public BwEvent {
public:
	BwOpenEvent(const bwString& txt) : BwEvent(_BwDocument::EVENT_OPEN) {
		m_data->addString("FILENAME", txt) ;
	}
} ;
#endif //__BwDocument_H