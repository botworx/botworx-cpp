#ifndef _BwIoSlot_H
#define _BwIoSlot_H

#include "BwMailSlot.h"
#include "BwMessage.h"
//class BwIo ;
#include "BwIo.h"

class BwIoSlot : public BwMailSlot {
public:
	BwIoSlot(BwPart *pOwner, const bwString& name) ;
	virtual void doCreate(const BwPartInfo& info) ;
	//
	BwIo* findOrCreateIo(const bwPath& path) ;
	BwIo* findIo(const bwPath& path) ;
	//factory method called by the ios...override in your specialized ioslot class
	virtual BwIo* createIo(BwIo* pParent, const bwString& name, BwIo::ioType type) ;
	void notify(BwMessage evt) ;
	void update() ;
	//
	void printTree() ;
	//Events
	class Event : public BwMessage {
	public:
		Event(bwWhat what) : BwMessage(what) {}
		enum what_enum {
			EVENT_TOPIC_ADDED = 1
		} ;
	} ;
	class IoAddedEvent : public Event {
	public:
		IoAddedEvent(const bwPath& path) ;
	} ;
	//Data Members
	BwIo *p_root ;
} ;

#endif //_BwIoSlot_H
