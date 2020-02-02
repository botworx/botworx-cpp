#ifndef _BwMessenger_H
#define _BwMessenger_H

#include "BwMessengerBase.h"

class BwMailSlot ;
class BwAddress ;

class BwMessenger : public BwMessengerBase {
public:
	BwMessenger(BwPart *pOwner) : BwMessengerBase(pOwner) {}
	virtual bwString getClassName() { return "BwMessenger" ; }
	virtual void connect(BwMailSlot* pSlot) = 0;
	virtual void disconnect()  = 0;
	virtual void send(const BwMessage& msg)  = 0;
	virtual void receive(const BwMessage& msg, bool selfReflective = false)  = 0;
	void setDownLink(BwMailSlot *pSlot) { p_downLink = pSlot ; }
	//Data
	BwMailSlot *p_downLink ;
};

typedef std::list<BwMessenger*> BwMessengerContainer ;
typedef BwMessengerContainer::iterator BwMessengerIter ;

#endif //_BwMessenger_H
