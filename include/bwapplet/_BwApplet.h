#ifndef __BwApplet_H
#define __BwApplet_H

#include <bwcore/_BwPart.h>

/*namespace _BwApplet {
	using namespace _BwPart ;
	enum {
		EVENT_OPEN = BWPART_EVENT_TTL,
		EVENT_SAVE,
		EVENT_CLOSE,
		BWAPPLET_EVENT_TTL
	} ;
} //end namespace _BwApplet {*/

namespace _BwApplet {
	using namespace _BwPart ;
	enum {
		EVENT_OPEN = BWPART_MSG_TTL,
		EVENT_SAVE,
		EVENT_CLOSE,
		BWAPPLET_MSG_TTL
	} ;
} //end namespace _BwApplet {

#endif //__BwApplet_H