#ifndef _BwMiaAgent_H
#define _BwMiaAgent_H

#include <bwagency/BwAgent.h>

class MiaAgent ;

class BwMiaAgent : public BwAgent {
public:
	BwMiaAgent(BwAgency *pAgency) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void close() ;
	//
	virtual BwMailCenter& getMailCenter() ;
	//Notices & Events
	//Data Members
	MiaAgent* p_inner ;
	BwMailSlot* p_innerIn ;
};

#endif //_BwMiaAgent_H