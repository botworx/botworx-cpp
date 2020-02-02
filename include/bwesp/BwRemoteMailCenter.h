#ifndef _BwRemoteMailCenter_H
#define _BwRemoteMailCenter_H

#include <bwmessaging/BwMailCenter.h>
#include <bwesp/BwConnection.h>

class BwRemoteServer ;
class BwRemoteService ;

class BwRemoteMailCenter : public BwMailCenter {
public:
	BwRemoteMailCenter() ;
	virtual void doCreate(const BwPartInfo& info) ;
	bwHandle addBox(BwMailBox* pBox, BwPart *pAddressee) ;
	void removeBox(bwHandle handle) ;
	//
	virtual BwMailBox* findBox(bwHandle handle) ;
	BwPart* findAddressee(bwHandle handle) ;
	//
	BwRemoteService& getService() ;
	//
	BwRemoteServer& getServer() ;
	//
	BwConnection& getConnection() { return m_connection ; }
	//Data Members
	//Net
	BwConnection m_connection ;
} ;

class BwMailBoxProxy : public BwMailBox {
public:
	BwMailBoxProxy(BwRemoteMailCenter* pOwner) : BwMailBox(pOwner) {}
	//
	virtual BwMailSlot* findSlot(const bwString& name) ;
	//
	BwRemoteMailCenter& getMailCenter() ;
	BwRemoteService& getService() { return getMailCenter().getService() ; }
	BwRemoteServer& getServer() { return getMailCenter().getServer() ; }
	//Data Members
} ;

class BwMailSlotProxy : public BwMailSlot {
public:
	BwMailSlotProxy(BwPart *pOwner, const bwString& name) : BwMailSlot(pOwner, name) {}
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void receive(const BwMessage& msg, bool selfReflective = false) ;
	//
	BwMailBoxProxy& getMailBox() ;
} ;
#endif //_BwRemoteMailCenter_H
