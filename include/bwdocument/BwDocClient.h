#ifndef _BwDocClient_H
#define _BwDocClient_H

#include "BwDocument.h"

class BwDocSession ;
class BwCmd ; 

class BwDocClient : public BwPart {
public:
	BwDocClient() ;
	void connect(BwDocSession *pSession) ;
	void disconnect() ;
	void dropConnection() ;
	void close() ;
	void noticeDocumentClose() ;
	void destroyDocument() ;
	//void doCommand(const bwString& cmdString) ;
	void doCommand(const BwCmd& cmd) ;
	//void doCommandSync(const bwString& cmdString) ;
	void doCommandSync(const BwCmd& cmd) ;
	virtual void onOutput(const BwMessage& msg) ;
	virtual void onLog(const BwMessage& msg) ;
	virtual void onResponse(const BwMessage& msg) ;
	virtual void onEvent(const BwMessage& msg) ;
	virtual void onIo(const BwMessage& msg) ;
	//onEvent
	void onDocumentExit() ;
	//
	bool isClosed() ;
	BwDocSession* getDocumentSession() { return p_session ; }
	//Data Members
	bool m_hasResponse ;
	bool m_documentHasExited ;
	long *p_params ;
	//BwxDoc *p_document ;
	BwDocSession *p_session ;
	BwMailSlot *p_documentIn ;
	BwMailSlot *p_documentOut ;
	BwMailSlot *p_documentLog ;
	BwMailSlot *p_documentEvents ;
	//BwMailSlot *p_documentIos ;
} ;


#endif //_BwDocClient_H
