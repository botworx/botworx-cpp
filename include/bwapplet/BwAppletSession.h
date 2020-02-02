#ifndef _BwAppletSession_H
#define _BwAppletSession_H

#include "BwApplet.h"
#include <bwmessaging/BwMessage.h>

class BwAppletClient ;

typedef std::list<BwAppletClient*> BwAppletClientList ;
typedef BwAppletClientList::iterator BwAppletClientIter ;

class BwAppletSession : public BwPart {
public:
	//BwAppletSession(documentType type, const bwString& name, BwMessage params, bool enabled = true) ;
	BwAppletSession() ;
	BwApplet* create_applet() ;
	virtual BwApplet* produce() ;
	void close_applet() ;
	void notice_appletClose() ;
	//
	void connect() ;
	void disconnectClients() ;
	void addClient(BwAppletClient *pClient) ;
	void removeClient(BwAppletClient *pClient) ;
	//
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwMailBox& getMailBox() { return p_applet->getMailBox() ; }
	//
	BwApplet* getApplet() { return p_applet ; }
	//Data Members
	BwApplet *p_applet ;
	//documentType m_type ;
	BwMessage m_params ;
	//bool m_enabled ;
	bool m_appletHasExited ;
	BwAppletClientList m_clients ;
	BwMailSlot *p_outSlot ; //out to documents inslot..
	BwMailSlot *p_appletEvents ; //in from document events
} ;


#endif //_BwAppletSession_H
