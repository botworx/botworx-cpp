#ifndef _BwMailSlot_H
#define _BwMailSlot_H

#include <bwmessaging/BwMessengerBase.h>
#include <bwmessaging/BwMessenger.h>

#include <bwcore/config/boost_thread.h>

class BwPostOffice ;
class BwMessenger ;
class BwAddress ;
class BwLocalAddress ;

class BwMailSlot : public BwMessengerBase {
public:
	BwMailSlot(BwPart *pOwner, const bwString& name) ;
	BwMailSlot(const bwString& name) ;
	BwMailSlot() ;
	void init() {
		m_isSelfReflective = true ;
		p_messenger = nullptr ;
	}
	virtual ~BwMailSlot() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bwString getClassName() { return "BwMailSlot" ; }
	virtual void connect(BwMailSlot *pSlot) ;
	virtual BwMessenger* accept(BwMailSlot *pSlot) ;
	virtual void disconnect() ;
	void dropConnection() ;
	virtual void setMessenger(BwMessenger *pMessenger) ;
	virtual void send(const BwMessage& msg) ;
	virtual void receive(const BwMessage& msg, bool selfReflective = false) ;
	virtual void dispatch(const BwMessage& msg) {}
	void addSubscriber(BwMessenger *pMessenger) ;
	void removeSubscriber(BwMessenger *pMessenger) ;
	void removeOldSubscribers() ;
	BwPostOffice* getPo() { return p_po ; }
	//Usually we do want to get on_message sent through self.
	void setIsSelfReflective(bool val) { m_isSelfReflective = val ; }
	bool isSelfReflective() { return m_isSelfReflective ; }
	//Data Members
protected:
	BwPostOffice *p_po ;
	BwMessenger *p_messenger ;
	BwMessengerContainer m_subs ; //These are downlinks.
	BwMessengerContainer m_oldSubs ;
	bool m_isSelfReflective ;
	//
	boost::mutex m_dispatchMutex ;
	boost::condition m_dispatching ;
};
typedef std::vector<BwMailSlot*> BwMailSlots ;
typedef BwMailSlots::iterator BwMailSlotIter ;
//
typedef std::map<bwString, BwMailSlot*> BwMailSlotMap ;
typedef BwMailSlotMap::iterator BwMailSlotMapIter ;

#endif //_BwMailSlot_H
