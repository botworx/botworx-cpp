#ifndef _BwPoMessenger_H
#define _BwPoMessenger_H

#include "BwLocalMessenger.h"

class BwMailSlot ;
class BwPostOffice ;

class BwPoMessenger : public BwLocalMessenger {
public:
	BwPoMessenger(BwPart *pOwner) : BwLocalMessenger(pOwner) {}
	virtual bwString getClassName() { return "BwPoMessenger" ; }
	virtual void connect(BwMailSlot* pSlot) ;
	virtual void send(const BwMessage& msg) ;
	virtual void receive(const BwMessage& msg, bool selfReflective = false) ;
	//Data Members
	BwPostOffice *p_upLinkPo ;
	BwPostOffice *p_downLinkPo ;
};

#endif //_BwPoMessenger_H