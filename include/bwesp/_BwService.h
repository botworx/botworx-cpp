#ifndef __BwService_H
#define __BwService_H

//#include <bwmessaging/BwMessage.h>
#include <bwcore/_BwPart.h>

/*namespace _BwService {
	using namespace _BwPart ;
	enum {
		EVENT_OPEN = BWPART_EVENT_TTL,
		EVENT_SAVE,
		EVENT_CLOSE,
		BWSERVICE_EVENT_TTL
	} ;
	enum {
		BWSERVICE_INPUT_TTL = BWPART_INPUT_TTL
	} ;
	enum {
		BWSERVICE_OUTPUT_TTL = BWPART_OUTPUT_TTL
	} ;
} //end namespace _BwService {*/

namespace _BwService {
	using namespace _BwPart ;
	enum {
		EVENT_OPEN = BWPART_MSG_TTL,
		EVENT_SAVE,
		EVENT_CLOSE,
		BWSERVICE_MSG_TTL
	} ;
} //end namespace _BwService {

class BwOpenEvent : public BwEvent {
public:
	BwOpenEvent(const bwString& txt) : BwEvent(_BwService::EVENT_OPEN) {
		m_data->addString("FILENAME", txt) ;
	}
} ;
#endif //__BwService_H