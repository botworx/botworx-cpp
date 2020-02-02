#ifndef _BwRemoteSession_H
#define _BwRemoteSession_H

#include "BwSession.h"
#include "BwRemoteService.h"

class BwRemoteSession : public BwSession {
public:
	BwRemoteSession(BwRemoteService* pSvc) : BwSession(pSvc) {}
	virtual void doCreate(const BwPartInfo& info) ;
	//
	virtual void connectClient(BwClient* pClient) ;
	virtual void connectSlot(const bwString& name, BwClient* pClient, BwMailSlot* pSlot) ;
	//
	BwRemoteService& getService() ;
	//
	BwConnection& getConnection() { return m_connection ; }
	//Data Members
	//Net
	BwConnection m_connection ;
} ;


#endif //_BwRemoteSession_H
