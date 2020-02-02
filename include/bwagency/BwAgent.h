#ifndef _BwAgent_H
#define _BwAgent_H

#include <bwesp/BwService.h>

class BwCmd ;

class BwAgency ;
class BwAgentSession ;

class BwAgent : public BwService {
public:
	BwAgent(BwAgency *pAgency) ;
	virtual void doCreate(const BwPartInfo& info) ;
	//
	virtual BwSession* produceSession() ;
	//
	void doCommand(const BwCmd& cmd) ;
	//Event Handlers
	virtual bool onClose() ;
	//f6:fixme:move into BwService
	void setParams(BwMessage params) { m_params = params ; }
	BwMessage m_params ;
} ;

#endif //_BwAgent_H