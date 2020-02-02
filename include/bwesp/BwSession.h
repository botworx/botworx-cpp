#ifndef _BwSession_H
#define _BwSession_H

#include "BwService.h"

class BwClient ;

class BwSession : public BwPart {
public:
	BwSession(BwService* pSvc) ;
	virtual void doCreate(const BwPartInfo& info) ;
	//
	virtual void connectClient(BwClient* pClient) = 0 ;
	virtual void closeService() ;
	virtual void noticeServiceClose() ;
	//
	void disconnectClients() ;
	void addClient(BwClient *pClient) ;
	void removeClient(BwClient *pClient) ;
	BwClient* findClient(bwHandle clientHandle) ;
	//
	virtual void connectSlot(const bwString& name, BwClient* pClient, BwMailSlot* pSlot) = 0 ;
	//
	virtual void onEvent(const BwMessage& msg) {}
	//
	BwMailCenter& getMailCenter() { return p_service->getMailCenter() ; }
	BwMailBox& getMailBox() { return p_service->getMailBox() ; }
	//
	BwService& getService() { return *p_service ; }
	//Data Members
	BwService *p_service ;
	bool m_serviceHasClosed ;
	//Proxies
	int m_clientCount ;
	std::vector<BwClient*> m_clients ;
	//
	BwMailSlot *p_outSlot ; //out to services inslot..
	BwMailSlot *p_serviceEvents ; //in from service events
} ;


#endif //_BwSession_H
