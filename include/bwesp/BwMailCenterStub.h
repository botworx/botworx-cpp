#ifndef _BwMailCenterStub_H
#define _BwMailCenterStub_H

#include <bwmessaging/BwMailCenter.h>
#include <bwesp/BwConnection.h>

class BwServiceStub ;

class BwMailCenterStub : public BwMailCenter {
public:
	BwMailCenterStub() ;
	virtual void doCreate(const BwPartInfo& info) ;
	bwHandle addBox(BwMailBox* pBox, BwPart *pAddressee) ;
	void removeBox(bwHandle handle) ;
	//
	virtual BwMailBox* findBox(bwHandle handle) ;
	BwPart* findAddressee(bwHandle handle) ;
	//
	BwServiceStub* getServiceStub() ;
	BwServiceStub& serviceStub() { return *getServiceStub() ; }
	//
	BwConnection& getConnection() { return m_connection ; }
	//Data Members
	//Net
	BwConnection m_connection ;
} ;

class BwMailBoxStub : public BwMailBox {
public:
	BwMailBoxStub(BwMailCenterStub* pOwner) : BwMailBox(pOwner) {}
	//~BwMailBoxStub() ;
	virtual BwMailSlot* findSlot(const bwString& name) ;
	//
	BwMailCenterStub& getMailCenter() ;
	//
	BwServiceStub& serviceStub() { return *getServiceStub() ; }
	BwServiceStub* getServiceStub() { return getMailCenter().getServiceStub() ; }
	//Data Members
} ;

class BwMailSlotStub : public BwMailSlot {
public:
	BwMailSlotStub(BwPart *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {}
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void receive(const BwMessage& msg, bool selfReflective = false) ;
	//
	BwMailBoxStub& getMailBox() ;
} ;

#endif //_BwMailCenterStub_H