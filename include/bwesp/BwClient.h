#ifndef _BwClient_H
#define _BwClient_H

#include <bwmessaging/BwMailBox.h>
#include "BwService.h"

class BwSession ;
class BwCmd ; 

class BwClient : public BwMailer {
public:
	BwClient(BwPart* pOwner) ;
	void connect(BwSession *pSession, bwHandle hBox = MB_PRIMARY) ;
	void disconnect() ;
	void dropConnection() ;
	void close() ;
	void noticeServiceClose() ;
	virtual void onOutput(const BwMessage& msg) ;
	virtual void onLog(const BwMessage& msg) ;
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	virtual void onIo(const BwMessage& msg) ;
	//onEvent
	void onServiceExit() ;
	//
	void connectSlot(const bwString& name, BwMailSlot* pSlot) ;
	BwMailSlot* createSlot(const bwString& name) ;
	//
	bool isClosed() ;
	BwSession* getSession() { return p_session ; }
	bwHandle getBoxHandle() { return m_boxHandle ; }
	//Data Members
	bool m_hasResponse ;
	bool m_serviceHasClosed ;
	long *p_params ;
	BwSession *p_session ;
	bwHandle m_boxHandle ; //box we want to connect to.
} ;

typedef std::vector<BwClient*> BwProxies ;
typedef BwProxies::iterator BwClientIter ;

typedef std::list<BwClient*> BwClientList ;
typedef BwClientList::iterator BwClientListIter ;

#endif //_BwClient_H
