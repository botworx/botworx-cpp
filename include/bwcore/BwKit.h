/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwKit_H
#define _BwKit_H

#include "BwPart.h"

class BwKit ;
typedef std::list<BwKit*> BwKitList ;
typedef BwKitList::iterator BwKitListIter ;

class BwFactory ;
class BwKitFactory ;
class BwSystem ;
class BwMailSlot ;
class BwMessage ;

template<>
struct BwSigT<BwKit> {
	typedef BwKitList		T_Container ;
	//
	static bwString name() { return "Kit" ; }
} ;

class BwKit : public BwPart {
public:
	BwKit(BwPart *pPart) ;
	~BwKit() ;
	//
	void* operator new(size_t count) {
		return BW_USERMALLOC(count, TT_KIT) ;
	}
	void operator delete(void* object) {
		BW_USERFREE(object, TT_KIT) ;
	}
	//
	virtual void* rent(size_t size) { assert(0) ; return nullptr ; }
	virtual void release(void *pCell) { assert(0) ; }
	//
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doConfig() ;
	virtual void doPostConfig() ;
	virtual void doEnable(bool sleeping) ;
	virtual void doPostEnable(bool sleeping) ;
	virtual void doDisable(bool sleeping) ;
	virtual void doPostDisable(bool sleeping) ;
	//
	virtual void createEventSlot() ;
	BwMailSlot* getEventSlot() { return p_eventSlot ; }
	void raiseEvent(const BwMessage& msg) ;
	//
	virtual void addKit(BwKit* pKit) ;
	void removeKit(BwKit* pKit) ;
	void destroyKits() ;
	//
	BwFactory* getDefaultFactory() { return  p_defaultFactory ; }
	/*Data Members*/
	size_t m_size ;
	BwFactory *p_defaultFactory ;
	BwMailSlot *p_eventSlot ;
	BwKitList m_kits ;
} ;
///////////////
template<typename T_Class, typename T_Base = BwKit>
class BwHeapKitT : public T_Base {
public:
public:
	BwHeapKitT(BwPart *pPart) : T_Base(pPart) {
	}
	//virtual void* rent(size_t size) { return ::malloc(size) ; }
	virtual void* rent(size_t size) { return BW_MALLOC(size) ; }
	//virtual void release(void *pCell) { ::free(pCell) ; }
	virtual void release(void *pCell) { BW_FREE(pCell) ; }
	//Data Members
};
///////////////
template<typename T_Class, typename T_Base = BwKit>
class BwPoolKitT : public T_Base {
public:
	typedef boost::pool<>					T_Pool ;
	typedef BwSigT<T_Class>		T_Sig ;
	typedef typename T_Sig::T_Part			T_Part ;
public:
	BwPoolKitT(BwPart *pPart) : T_Base(pPart), m_pool(sizeof(T_Part)) {
	    size_t size = sizeof(T_Part) ;
		assert(size != 0) ;
		assert(size != 1) ;
		this->m_size = size ;
	}
	//Data Members
	T_Pool m_pool ;
	virtual void* rent(size_t size) {
		assert(this->m_size != 0) ;
		assert(this->m_size != 1) ;
		assert(size == this->m_size) ;
		return m_pool.malloc() ;
	}
	virtual void release(void* pCell) { m_pool.free(pCell) ; }
};

#endif //_BwKit_H
