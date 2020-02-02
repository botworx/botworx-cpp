/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwLocalServer_H
#define _BwLocalServer_H

#include "BwServer.h"
#include "BwServerStub.h"

class BwLocalServer : public BwServer {
public:
	BwLocalServer(BwPart *pPart, const BwAddress& address) ;
	virtual void doCreate(const BwPartInfo& info) ;
	//Net
	void listen() ;
	//Stubs
	virtual BwServerStub* createStub() ;
	void addStub(BwServerStub* pStub) { m_stubs.push_back(pStub) ; }
	//Data Members
	//Stubs
	int m_stubCount ;
	BwServerStubs m_stubs ;
	//Singleton support
	struct singleton_alloc {
		static BwLocalServer* alloc() ;
	} ;
	typedef BwAutoSingletonT<BwLocalServer, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;

#endif //_BwLocalServer_H