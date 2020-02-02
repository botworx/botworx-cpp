#ifndef _BwConnectionWorker_H
#define _BwConnectionWorker_H

#include "BwWorker.h"
#include <bwmessaging/BwAddress.h>
#include <bwesp/BwConnection.h>

class BwConnectionWorker : public BwWorker {
public:
	BwConnectionWorker(BwPart *pPart) ;
	virtual void work() ;
	//
	void connect(const BwAddress& address) ;
	void send(const BwMessage& msg) ;
	void receive(const BwMessage& msg) ;
	//
	void setConnection(BwConnection& socket) { m_connection = socket ; }
	BwConnection& getConnection() { return m_connection ; }
	//Data Members
	BwAddress m_address ;
	BwConnection m_connection ;
} ;

#endif //_BwConnectionWorker_H
