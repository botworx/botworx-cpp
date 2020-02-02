/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaMind.h>
#include <bwmia/MiaAgent.h>
#include <bwai/AiInt.h>

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaMind.h>
#include <bwmia/MiaMatcher.h>
#include <bwmia/MiaBinder.h>
#include <bwmia/config/options.h>

//
#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;
#include <bwagency/_BwState.h>
using namespace _BwState ;

MiaMind::MiaMind(MiaMind* pParent, AiSymbol* pSymbol) 
	: MiaSpace(pParent, pSymbol), m_logSink(true)  {

	p_parent = pParent ;
	//
	if(pParent != NULL) {
		setMonitorFlags(pParent->getMonitorFlags()) ;
	}
	else
		m_monitorFlags = 0 ;
}
MiaMind::~MiaMind() {
}
void MiaMind::doCreate(const BwPartInfo& info) {
	MiaSpace::doCreate(info) ;
	//
	m_log.reserve(LOG_RESERVE) ;
	m_logSink.setString(m_log) ;
	m_logger.pushSink(&m_logSink) ;
	if(isEmitting())
		createMailBox() ;
}
void MiaMind::createMailBox() {
	p_mailBox = &k_agent().getMindMailBox() ;
	setHandle(k_agent().getMailCenter().addBox(p_mailBox, this)) ;
}
//
MiaMindMailBox::MiaMindMailBox(BwPart* pOwner) : BwMailBox(pOwner) {
	p_inSlot = new BwMailSlot(&k_core(), "IN") ;
	p_inSlot->create() ;
	addSlot(p_inSlot) ;

	p_outSlot = new BwMailSlot(&k_core(), "OUT") ;
	p_outSlot->create() ;
	addSlot(p_outSlot) ;

	p_logSlot = new BwMailSlot(&k_core(), "LOG") ;
	p_logSlot->create() ;
	addSlot(p_logSlot) ;

	p_eventSlot = new BwMailSlot(&k_core(), "EVENT") ;
	p_eventSlot->create() ;
	addSlot(p_eventSlot) ;
}
//
inline char* slash_to_underscore(char *s) {
  while (*s) {
    if (*s == '/')
		*s = '_' ;
	s++ ;
  }
  return s ;
}
void MiaMind::dump() {
	char nameString[64] ;
	strcpy(nameString, p_symbol->getCstring()) ;
	slash_to_underscore(nameString) ;
	std::string fileName = ("../BwMia/logs/" + bwString(nameString) + ".xml") ;
	std::ofstream out(fileName.c_str(), std::ios_base::out | std::ios_base::trunc );
	std::cout << "\nFile dump.\n\n" ;
	MiaPrinter dumper(out) ;
	print(dumper) ;
	dumper.flush() ;
	out.close() ;
}
void MiaMind::outputFacts() {
	MiaPrinter printer ;
	BwStringSink printSink(true) ;
	bwString tempBuffer ;
	printSink.setString(tempBuffer) ;
	printer.pushSink(&printSink) ;
	//
	printFacts(printer) ;
	getOutSlot().send(BwFactsOutput(tempBuffer)) ;
}
void MiaMind::outputLog() {
	getOutSlot().send(BwLogOutput(m_log)) ;
}
void MiaMind::printBranch(MiaPrinter& printer) {
	print(printer) ;
	if(hasParent())
		p_parent->printBranch(printer) ;
}
void MiaMind::print(MiaPrinter& printer) const {
	MiaTopic* pTopic = NULL ;
	printer << "<space>\n" ;
	printFacts(printer) ;
	printer << "</space>\n" ;
}
MiaPrinter& operator<<(MiaPrinter& printer, const MiaMind& space) {
	space.print(printer) ;
	return printer ;
}
//TODO:NEWSTUFF
void MiaMind::spawnMethod(MiaBinder& binder, MiaMethodFactory* pFactory, MiaFact* pFact) {
	MiaMethod* pMethod = pFactory->produce(*this, binder, pFact) ;
	scheduleMethod(pMethod) ;
}
//Posts a new fact
void MiaMind::post(MiaFact* pFact) {
	MiaFact* pSubject = pFact->getSubject() ;

	if(pSubject == getId())
		receive(pFact) ;

	MiaTopic* pTopic = lookup(pSubject) ;

	if(pTopic == NULL) {
		pTopic = new MiaTopic(*this, pSubject) ;
		addTopic(pTopic) ;
	}
	pTopic->assertFact(this, pFact) ;
	m_posts.push_back(pFact) ;

#if AI_OPTION_INSTRUMENT
	if(isLogging()) {
		if(pFact->getTruth() > 0)
			logger() << ":  Asserting  :  " ;
		else
			logger() << ":  Retracting  :  " ;
		logger() << *pFact << endl ;
	}
#endif
}
void MiaMind::propose(AiPair* pProposals) {
	m_output.push_back(pProposals) ;
#if AI_OPTION_INSTRUMENT
	if(isLogging()) {
		logger() << p_symbol->getString() ;
		logger() << ":  Proposing  :  " ;
		logger() << *pProposals << endl ;
	}
#endif
}