/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwPart_H
#define _BwPart_H

#if !defined(_BwCommon_H)
#error Do not include this file directly.  Use BwCommon.h instead.
#endif

#include "BwCell.h"
#include "BwPartInfo.h"

class BwPart : public BwCell {
public:
	BwPart(BwPart *pOwner) ;
	virtual ~BwPart() ;
	virtual bwString getClassName() { return "BwPart" ; }

	bool isInitialised() { return m_isInitialised ; }
	bool isConfigured() { return m_isConfigured ; }
	bool isOperational() { return m_isOperational ; }
	bool isEnabled() { return m_isEnabled ; }
	bool isDisabled() { return !m_isEnabled ; }
	//
	bool halt() { return m_isOperational = false ; }
	bool isHalted() { return isEnabled() && !isOperational() ; }
	//
	bool create(const BwPartInfo& info = BwPartInfo()) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	void config() ;
	virtual void doConfig() ;
	virtual void doPostConfig() ;
	virtual void onConfig() {}
	void enable(bool sleeping = false) ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doPostEnable(bool sleeping = false) ;
	virtual void onEnable(bool sleeping) {}
	void disable(bool sleeping = true) ;
	virtual void doDisable(bool sleeping = true) ;
	virtual void doPostDisable(bool sleeping = true) ;
	virtual void onDisable(bool sleeping) {}

	void createAndConfig() ;
	void configAndEnable() ;
	void createEnabled() ;
	//Utility
	virtual void dispatch(const BwMessage& msg) {}
	virtual bwString makeName() ;
	virtual bwString makeThingName(const bwString& thingName, bwIndex index=0) ;
	//Accessors
	void setName(const bwString &pName) { m_name = pName ; }
	const bwString& getName() { return m_name ; }
	void setOwner(BwPart *pOwner) { p_owner = pOwner ; }
	BwPart* getOwner() { return p_owner ; }
	void setFactory(BwFactory *pFactory) ;
	BwFactory* getFactory() { return p_factory ; }
	//
	//Data Members
	//
	BwPart *p_owner ;
	bwString m_name ;
	BwFactory *p_factory ;
	int m_serial ;
	//
	void setHandle(bwHandle handle) { m_handle = handle ; }
	bwHandle getHandle() { return m_handle ; }
	bwHandle m_handle ;

	bool m_isInitialised ;
	bool m_isConfigured ;
	bool m_isEnabled ;
	bool m_isOperational ; //set true on first enablement
	//
	/*//in place
	void *operator new(size_t count, void *object) throw() ;
	void operator delete(void *object, void *memory) throw() ;
	//heap
	void *operator new(size_t count) throw() ;
	void operator delete(void* _Ptr) throw() ;
	//array
	void* operator new[](size_t sz) throw()	;
	void operator delete[](void* m) throw()	;*/
} ;

#endif //_BwPart_H
