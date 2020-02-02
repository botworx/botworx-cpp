#ifndef _BwAppletClient_H
#define _BwAppletClient_H

#include "BwApplet.h"

class BwCmd ; 
class BwAppletSession ;

class BwAppletClient : public BwPart {
public:
	BwAppletClient() ;
	void connect(BwAppletSession *pSession) ;
	void disconnect() ;
	void dropConnection() ;
	void close() ;
	void notice_appletClose() ;
	void destroy_applet() ;
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
	void on_appletExit() ;
	//
	bool isClosed() ;
	BwAppletSession* getAppletSession() { return p_session ; }
	//Data Members
	bool m_hasResponse ;
	bool m_appletHasExited ;
	long *p_params ;
	//BwxDoc *p_applet ;
	BwAppletSession *p_session ;
	BwMailSlot *p_appletIn ;
	BwMailSlot *p_appletOut ;
	BwMailSlot *p_appletLog ;
	BwMailSlot *p_appletEvents ;
	//BwMailSlot *p_appletIos ;
} ;


#endif //_BwAppletClient_H
