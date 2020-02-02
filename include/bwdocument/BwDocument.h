#ifndef _BwDocument_H
#define _BwDocument_H

#include <bwcore/BwKit.h>
#include <bwmessaging/BwMailBox.h>

class BwDocument : public BwKit {
public:
    BwDocument(void) ;
    ~BwDocument(void) ;
	void setFilename(const bwString& filename, bool notify) ;
	virtual bool onNew() ;
    virtual bool onSave(const bwString& filename);
    virtual bool onOpen(const bwString& filename);
	virtual bool onClose() ;
    virtual bool isModified(void) const;
    virtual void modify(bool val) ;

	/*Messaging*/
	virtual void createMailCenter() ;

	BwMailBox& getMailBox() { return m_mailBox ; }
	BwMailBox m_mailBox ;
	
	BwMailSlot& getInSlot() { return *p_inSlot ; }
	BwMailSlot& getOutSlot() { return *p_outSlot ; }
	BwMailSlot& getEventSlot() { return *p_eventSlot ; }
	BwMailSlot& getLogSlot() { return *p_logSlot ; }

	BwMailSlot *p_inSlot ;
	BwMailSlot *p_outSlot ;
	BwMailSlot *p_eventSlot ;
	BwMailSlot *p_logSlot ;

	//Data Members
	bwString m_fileName ;
	bool m_isNew ;
	bool m_isModified ;
	bool m_isClosed ;
};


#endif
