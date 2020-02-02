/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaMind_H
#define _MiaMind_H

#include "MiaSpace.h"
#include "MiaPattern.h"
#include <bwai/AiList.h>
#include "MiaBinder.h"
//TODO:NEWSTUFF
#include "MiaDomain.h"
#include "MiaMethod.h"

typedef std::vector<MiaMethodPtr> MiaMethodQueue ;

//
//MiaMindMailBox
//
class MiaMindMailBox : public BwMailBox {
public:
	MiaMindMailBox(BwPart* pOwner) ;
	BwMailSlot& getInSlot() { return *p_inSlot ; }
	BwMailSlot& getOutSlot() { return *p_outSlot ; }
	BwMailSlot& getEventSlot() { return *p_eventSlot ; }
	BwMailSlot& getLogSlot() { return *p_logSlot ; }
	//
	BwMailSlot *p_inSlot ;
	BwMailSlot *p_outSlot ;
	BwMailSlot *p_eventSlot ;
	BwMailSlot *p_logSlot ;
} ;
//
//MiaMind
//
class MiaMind  : public MiaSpace {
public:
	MiaMind(MiaMind* pParent, AiSymbol* pSymbol) ;
	virtual ~MiaMind() ;
	virtual void doCreate(const BwPartInfo& info) ;
	//
	BwMailSlot& getEventSlot() { return getMailBox().getEventSlot() ; }
	BwMailSlot& getOutSlot() { return getMailBox().getOutSlot() ; }
	////////////////
	//Monitoring
	enum monitorFlag_E {
		MONITOR_ON = 1,
		MONITOR_LIVE = 2,
		MONITOR_LOG = 4,
		MONITOR_EMIT = 8
	} ;
	typedef monitorFlag_E monitorFlag ;
	typedef unsigned int monitorFlags ;
	void setMonitorFlags(monitorFlags flags) { m_monitorFlags = flags ; }
	monitorFlags getMonitorFlags() { return m_monitorFlags ; }
	void setMf(monitorFlag flag) { setFlag(m_monitorFlags, flag) ; }
	bool getMf(monitorFlag flag) { return getFlag(m_monitorFlags, flag) ; }
	void clearMf(monitorFlag flag) { clearFlag(m_monitorFlags, flag) ; }
	void setIsMonitored(bool val) { val ? setMf(MONITOR_ON) :	clearMf(MONITOR_ON) ; }
	bool isMonitored() { return getMf(MONITOR_ON) ; }
	void setIsLogging(bool val) { val ? setMf(MONITOR_LOG) :	clearMf(MONITOR_LOG) ; }
	bool isLogging() { return getMf(MONITOR_LOG) ; }
	void setIsEmitting(bool val) { val ? setMf(MONITOR_EMIT) :	clearMf(MONITOR_EMIT) ; }
	bool isEmitting() { return getMf(MONITOR_EMIT) ; }
	monitorFlags m_monitorFlags ;
	//
	void outputFacts() ;
	void outputLog() ;
	enum {
		LOG_RESERVE = 256
	} ;
	MiaPrinter* getLogger() { return &m_logger ; }
	MiaPrinter& logger() { return *getLogger() ; }
	bwString m_log ;

	MiaPrinter m_logger ;
	BwStringSink m_logSink ;

	//Messaging
	virtual void createMailBox() ;
	MiaMindMailBox& getMailBox() { return *p_mailBox ; }
	MiaMindMailBox* p_mailBox ;
	//
	friend MiaPrinter& operator<<(MiaPrinter& printer, const MiaMind& data) ;
	virtual void dump() ;
	void printBranch(MiaPrinter& printer) ;
	void print(MiaPrinter& printer) const ;
	//
	//bwString getPath() ;
	/////////
	void setName(const bwString& name) ;
	MiaMind* getParent() { return p_parent ; }
	bool hasParent() { return p_parent != NULL ; }
	bool isRoot() { return p_parent == NULL ; }
	//Data Members
	MiaMind* p_parent ;
	//TODO:NEWSTUFF from MiaState
	void setDomain(MiaDomain* pFactory) { p_domain = pFactory ; }
	MiaDomain* getDomain() { return p_domain.get() ; }
	MiaDomainPtr p_domain ;
	//
	void spawnMethod(MiaBinder& binder, MiaMethodFactory* pFactory, MiaFact* pFact) ;
	void scheduleMethod(MiaMethod* pMethod) { m_methodQueue.push_back(pMethod) ; }
	MiaMethodQueue m_methodQueue ;
	//
	void post(MiaFact* pFact) ;
	virtual void receive(MiaFact* pFact) {} //fact as message to mind...
	AiList m_posts ; //list for posting goals and facts
	//
	void propose(AiPair* pProposals) ;
	AiList m_output ; //list for outgoing proposals
} ;

#endif //_MiaMind_H
