#ifndef _EspProtoClient_H
#define _EspProtoClient_H

#include <bwesp/BwClient.h>

class BwSession ;
class BwCmd ; 

class EspProtoClient : public BwClient {
public:
	EspProtoClient(BwPart *pPart) ;
	virtual void onOutput(BwMessage msg) ;
	virtual void onLog(BwMessage msg) ;
	virtual void onResponse(BwMessage msg) ;
	virtual void onEvent(BwMessage msg) ;
	//onEvent
	//Data Members
	BwMailSlot *p_inSlot ;
	BwMailSlot *p_outSlot ;
	BwMailSlot *p_logSlot ;
	BwMailSlot *p_eventSlot ;
} ;


#endif //_EspProtoClient_H
