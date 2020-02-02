#include "stdafx.h"

#include <bwmessaging/BwMailSlot.h>

#include <bwdocument/BwDocument.h>
#include <bwdocument/BwDocSession.h>

#include <bwdocument/_BwDocument.h>
using namespace _BwDocument ;

////////////
class BwDocumentInSlot : public BwMailSlot {
public:
	BwDocumentInSlot(BwDocument *pDoc, const bwString& name) : BwMailSlot(pDoc, name) {
		p_document = pDoc ;
	}
	virtual void dispatch(const BwMessage& msg) {
		bwWhat what = msg.what() ;
		bwAssert(0) ; //TODO:implement
	}
	//Data Members
	BwDocument *p_document ;
} ;
////////////////
//EventSlot
class BwDocumentEventSlot : public BwMailSlot {
public:
	BwDocumentEventSlot(BwDocument *pDoc, const bwString& name) : p_document(pDoc), BwMailSlot(pDoc, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		//bwAssert(0) ; //TODO:implement
		//No .. this is just for self reflection
	}
	//Data Members
	BwDocument *p_document ;
} ;

////////////
BwDocument::BwDocument(void) : BwKit(nullptr), m_mailBox(nullptr) {
	m_mailBox.setOwner(this) ;
	m_isNew = true ;
	m_isClosed = false ;
	createMailCenter() ;
}
BwDocument::~BwDocument(void) {
}
void BwDocument::setFilename(const bwString& filename, bool notify) {
	m_fileName = filename ;
}
void BwDocument::createMailCenter() {
	p_inSlot = new BwDocumentInSlot(this, "IN") ;
	//p_inSlot->setIsSelfReflective(false) ;
	p_inSlot->create() ;
	m_mailBox.addSlot(p_inSlot) ;

	p_outSlot = new BwMailSlot(this, "OUT") ;
	p_outSlot->create() ;
	m_mailBox.addSlot(p_outSlot) ;

	p_logSlot = new BwMailSlot(this, "LOG") ;
	p_logSlot->create() ;
	m_mailBox.addSlot(p_logSlot) ;

	p_eventSlot = new BwDocumentEventSlot(this, "EVENT") ;
	p_eventSlot->create() ;
	m_mailBox.addSlot(p_eventSlot) ;
}
bool BwDocument::onClose() {
	if(!m_isNew && !m_isClosed) {
		m_isClosed = true ;
	}
	m_isNew = false ;

	return true ;
}
// Since text windows have their own method for saving to/loading from files,
// we override OnSave/OpenDocument instead of Save/LoadObject
bool BwDocument::onSave(const bwString& filename) {
    modify(false);
    return true;
}
bool BwDocument::onNew() {
	return true ;
}
bool BwDocument::onOpen(const bwString& filename) {
	m_isNew = false ;
    setFilename(filename, true);
    modify(false);
	p_eventSlot->send(BwOpenEvent(filename)) ;
    return true;
}

bool BwDocument::isModified(void) const {
	return m_isModified ;
}

void BwDocument::modify(bool val) {
    m_isModified = val ;
}
