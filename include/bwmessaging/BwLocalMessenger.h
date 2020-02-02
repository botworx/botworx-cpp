#ifndef _BwLocalMessenger_H
#define _BwLocalMessenger_H

#include "BwMessenger.h"

class BwMailSlot ;

class BwLocalMessenger : public BwMessenger {
public:
	BwLocalMessenger(BwPart *pOwner) : BwMessenger(pOwner) {}
	virtual bwString getClassName() { return "BwLocalMessenger" ; }
	virtual void connect(BwMailSlot* pSlot) ;
	virtual void disconnect() ;
	virtual void send(const BwMessage& msg) ;
	virtual void receive(const BwMessage& msg, bool selfReflective = false) ;
	//Data Members
	BwMailSlot *p_upLink ;
};

#endif //_BwLocalMessenger_H