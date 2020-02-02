#ifndef _BwPostOffice_H
#define _BwPostOffice_H

#include <bwstd/BwThreadSingleton.h>

class BwMessengerBase ;

class BwEnvelope {
public:
	BwEnvelope(const BwMessage& msg, BwMessengerBase *pRecipient) : m_msg(msg), p_recipient(pRecipient) {
	}
	BwEnvelope() { p_recipient = nullptr ; }
	void deliver() ;
	bool empty() { return p_recipient == nullptr ; }
	//Data Members
	BwMessage m_msg ;
	BwMessengerBase *p_recipient ;
} ;
class BwPoCall {
public:
	virtual bool exec() = 0 ;
} ;
class BwPostOffice : public BwPart {
public:
	BwPostOffice() ;
	void holdMessage(const BwMessage& msg, BwMessengerBase *pRecipient) ;
	BwEnvelope pickup() ;
	BwEnvelope pickupNotify() ;
	void release() ;
	void deliver() ;
	void deliver_notify() ;
	void setCall(BwPoCall *pCall) { p_call = pCall ; }
	//Data Members
	BwPoCall *p_call ;
	std::queue<BwEnvelope> m_mail ;
	boost::mutex m_holdingMutex ;
	boost::mutex m_dispatchMutex ;
	boost::condition m_holding ;
	boost::condition m_dispatching ;
	//Singleton Support
	struct singleton_alloc {
		static BwPostOffice* alloc() ;
	} ;
	typedef BwAutoThreadSingletonT<BwPostOffice, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;
#endif //_BwPostOffice_H