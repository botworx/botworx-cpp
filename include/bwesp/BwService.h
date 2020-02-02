#ifndef _BwService_H
#define _BwService_H

#include <bwcore/BwKit.h>
#include <bwmessaging/BwMailBox.h>

class BwCmd ;
class BwMailSlot ;
class BwMailCenter ;
class BwServer ;
class BwServiceProvider ;
class BwSession ;

class BwService : public BwKit {
public:
    BwService(BwServiceProvider* pProvider) ; //TODO:Server should be owner!
    ~BwService() ;
	virtual void doCreate(const BwPartInfo& info) ;
	//
	virtual BwSession* createSession() ;
	virtual BwSession* produceSession() = 0 ;
	void addSession(BwSession *pSession) ;
	BwSession* find_session(bwHandle sessionHandle) ;

	void setFilename(const bwString& filename, bool notify) ;
	virtual bool onNew() ;
    virtual bool onSave(const bwString& filename);
    virtual bool onOpen(const bwString& filename);
	virtual bool onClose() ;
	virtual void close() ;
	virtual bool isClosing() { return false ; }
    virtual bool isModified(void) const;
    virtual void modify(bool val) ;

	/*Messaging*/
	virtual void createMailCenter() {}
	virtual BwMailCenter& getMailCenter() = 0 ;

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
	//
	BwServiceProvider& getProvider() { return *p_provider ; }
	//
	BwServer& getServer() ;
	//Data Members
	BwServiceProvider* p_provider ;
	//Sessions
	int m_sessionCount ;
	std::vector<BwSession*> m_sessions ;
	//
	bwString m_fileName ;
	bool m_isNew ;
	bool m_isModified ;
	bool m_isClosed ;
};


#endif
