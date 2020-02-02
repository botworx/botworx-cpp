#ifndef _BwMessengerBase_H
#define _BwMessengerBase_H

class BwMessage ;
class BwMailSlot ;
class BwAddress ;
class BwLocalAddress ;
class BwAddress ;
class BwMessengerBase ;

class BwMessengerBase : public BwPart {
public:
	BwMessengerBase(BwPart *pOwner) : BwPart(pOwner) {}
	virtual bwString getClassName() { return "BwMessengerBase" ; }
	virtual void connect(BwMailSlot* pSlot) {}
	virtual void disconnect() {}
    virtual void send(const BwMessage& msg) {}
	virtual void receive(const BwMessage& msg, bool selfReflective = false) {}
	//Data
};

#endif //_BwMessengerBase_H
