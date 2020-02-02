#ifndef _BwLocalSession_H
#define _BwLocalSession_H

#include "BwSession.h"

class BwLocalSession : public BwSession {
public:
	BwLocalSession(BwService* pSvc) : BwSession(pSvc) {}
	//
	virtual void connectClient(BwClient* pClient) ;
	virtual void connectSlot(const bwString& name, BwClient* pClient, BwMailSlot* pSlot) ;
} ;


#endif //_BwLocalSession_H
