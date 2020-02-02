/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwServerStub_H
#define _BwServerStub_H

#include "BwServer.h"
#include "BwServiceStub.h"
#include <bwesp/BwConnection.h>

class BwServer ;
class BwConnectionWorker ;
class BwPoWorker ;

class BwServerStub : public BwPart {
public:
	BwServerStub(BwServer* pServer) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void onEnable(bool sleeping) ;
	virtual void dispatch(const BwMessage& msg) ;
	//
	BwConnection& getConnection() { return m_connection ; }
	BwServer& getServer() { return *static_cast<BwServer*>(p_owner) ; }
	//Data Members
	//Net
	BwConnection m_connection ;
	//
	void createServiceStub(const BwMessage& msg) ;
	void addServiceStub(BwServiceStub *pClient) ;
	void removeServiceStub(BwServiceStub *pClient) ;
	BwServiceStub* findServiceStub(bwHandle serviceStubHandle) ;

	int m_serviceStubCount ;
	std::vector<BwServiceStub*> m_serviceStubs ;
	//
	void setPo(BwPostOffice* pPo) { p_po = pPo ; }
	BwPostOffice& po() { return *getPo() ; }
	BwPostOffice* getPo() { return p_po ; }
	BwPostOffice* p_po ;
	//
	BwConnectionWorker* p_connectionWorker ;
	BwPoWorker* p_poWorker ;
} ;
typedef std::vector<BwServerStub*> BwServerStubs ;
typedef BwServerStubs::iterator BwServerStubIter ;

#endif //_BwServerStub_H