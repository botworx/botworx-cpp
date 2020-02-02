#ifndef _BwDocSession_H
#define _BwDocSession_H

#include "BwDocument.h"

class BwDocClient ;

typedef std::list<BwDocClient*> BwDocClientList ;
typedef BwDocClientList::iterator BwDocClientIter ;

class BwDocSession : public BwPart {
public:
	BwDocSession() ;
	BwDocument* createDocument() ;
	virtual BwDocument* produce() ;
	void closeDocument() ;
	void noticeDocumentClose() ;
	//
	void connect() ;
	void disconnectClients() ;
	void addClient(BwDocClient *pClient) ;
	void removeClient(BwDocClient *pClient) ;
	//
	virtual void onEvent(const BwMessage& msg) ;
	//
	BwMailBox& getMailBox() { return p_document->getMailBox() ; }
	//
	BwDocument* getDocument() { return p_document ; }
	//Data Members
	BwDocument *p_document ;
	BwMessage m_params ;
	bool m_documentHasExited ;
	BwDocClientList m_clients ;
	BwMailSlot *p_outSlot ; //out to documents inslot..
	BwMailSlot *p_documentEvents ; //in from document events
} ;


#endif //_BwDocSession_H
