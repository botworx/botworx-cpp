#ifndef _BwMessaging_H
#define _BwMessaging_H

#include <bwcore/BwSystem.h>
#include <bwmessaging/BwMessage.h>

class BwMailSlot ;
/////////////////
class BwMsgDataKit ;
class BwMsgFieldKit ;

template<>
struct BwSigT<BwMsgDataKit> : BwSigT<BwKit> {
	typedef BwMsgData	T_Part ;
	static bwString name() { return "BwMsgDataKit" ; }
} ;
typedef BwPoolKitT<BwMsgDataKit, BwKit> BwMsgDataKitBase ;

class BwMsgDataKit : public BwMsgDataKitBase {
public:
	BwMsgDataKit(BwPart *pPart) : BwMsgDataKitBase(pPart) {}
	static BwMsgDataKit *singleton ;
} ;
//
template<>
struct BwSigT<BwMsgFieldKit> : BwSigT<BwKit> {
	typedef BwMsgField	T_Part ;
	static bwString name() { return "BwMsgFieldKit" ; }
} ;
typedef BwPoolKitT<BwMsgFieldKit, BwKit> BwMsgFieldKitBase ;

class BwMsgFieldKit : public BwMsgFieldKitBase {
public:
	BwMsgFieldKit(BwPart *pPart) : BwMsgFieldKitBase(pPart) {}
	static BwMsgFieldKit *singleton ;
} ;
/////////////////
class BwMessaging : public BwSystem {
public:
	BwMessaging(BwPart *pPart) ;
	//
	BwMessage createMessage() ;
	void releaseMessage() ;
	//Kits
	BwMsgDataKit* p_msgDataKit ;
	BwMsgFieldKit* p_msgFieldKit ;
	//Singleton support
	typedef BwSingletonT<BwMessaging> singleton ;
	singleton m_singleton ;
} ;

#endif //_BwMessaging_H