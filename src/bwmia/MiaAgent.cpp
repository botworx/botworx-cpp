/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaAgent.h>
#include <bwmia/MiaProblem.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaCommander.h>

#include <bwai/AiInt.h>
#include <bwai/AiFloat.h>

#include <bwmia/MiaReader.h>
#include <bwmia/MiaPrinter.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaBinder.h>

#include <bwmessaging/BwPostOffice.h>
#include <bwmessaging/BwCmd.h>

#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;
//
//MiaAgent
//
class MiaAgentInSlot : public BwMailSlot {
public:
	MiaAgentInSlot(MiaAgent *pAgent, const bwString& name) : BwMailSlot(pAgent, name) {
		p_agent = pAgent ;
	}
	virtual void dispatch(const BwMessage& msg) {
		bwWhat what = msg.what() ;
		switch(what) {
			case COMMAND_TEXT : {
				bwString cmdString ;
				msg()->findString("Command", cmdString) ;
				BwCmd cmd ; cmd.set(cmdString) ;
				p_agent->doCommand(cmd) ;
				}
				break ;
			//Handled by Outer
			/*case COMMAND_CLOSE :
				p_agent->close() ;
				break ;*/
		}
	}
	//Data Members
	MiaAgent *p_agent ;
} ;
////////////////
//EventSlot
class MiaAgentEventSlot : public BwMailSlot {
public:
	MiaAgentEventSlot(MiaAgent *pAgent, const bwString& name) : p_root(pAgent), BwMailSlot(pAgent, name) {
	}
	virtual void dispatch(const BwMessage& msg) {
		switch(msg.what()) {
			case EVENT_INIT :
				break ;
			case EVENT_DESTROY :
				break ;
		}
	}
	//Data Members
	MiaAgent *p_root ;
} ;
//
// MiaAgent
//
MiaAgent::MiaAgent(AiKit* pKit, AiKitInfo *pKitInfo) : MiaCore(pKit, pKitInfo)  {
	m_stepStatus = STEP_NONE ;
	m_runStatus = RUN_STOPPED ;
	m_steps = 1 ;
	m_stepCounter = 0 ;
}
MiaAgent::~MiaAgent() {
	delete p_mindMailBox ;
}
void MiaAgent::doPostDisable(bool sleeping) {
	if(!sleeping) {
		destroyProblems() ;
		destroyPart(p_commander) ;
	}
	MiaCore::doPostDisable(sleeping) ;
}
void MiaAgent::close() {
	onClose() ;
}
bool MiaAgent::onClose() {
	return true ;
}
void MiaAgent::createMailCenter() {
	p_inSlot = new MiaAgentInSlot(this, "IN") ;
	p_inSlot->create() ;
	m_mailBox.addSlot(p_inSlot) ;

	p_outSlot = new BwMailSlot(this, "OUT") ;
	p_outSlot->create() ;
	m_mailBox.addSlot(p_outSlot) ;

	p_logSlot = new BwMailSlot(this, "LOG") ;
	p_logSlot->create() ;
	m_mailBox.addSlot(p_logSlot) ;

	p_eventSlot = new MiaAgentEventSlot(this, "EVENT") ;
	p_eventSlot->create() ;
	m_mailBox.addSlot(p_eventSlot) ;

	setHandle(m_mailCenter.addBox(&m_mailBox, this)) ;
	///////////////
	p_mindMailBox = new MiaMindMailBox(this) ;
}
//TODO:need to chain sinks ...?
void MiaAgent::createPrinter() {
	p_printer = new MiaPrinter(std::cout) ;
}
void MiaAgent::createLogger() {
	MiaCore::createLogger() ;
	/*std::string fileName = "../log/log.txt" ;
	std::ofstream* pOut = new std::ofstream(fileName.c_str(), std::ios_base::out | std::ios_base::trunc );

	p_logger = new MiaPrinter(*pOut) ;*/
}
void MiaAgent::changeIoMode() {
	switch(m_ioMode) {
		case IO_MESSAGING : {
			BwMailSlotSink* pOutSink = new BwMailSlotSink() ;
			pOutSink->setMailslot(p_outSlot) ;
			p_printer->pushSink(pOutSink) ;
			//
			BwMailSlotSink* pLogSink = new BwMailSlotSink() ;
			pLogSink->setMailslot(p_logSlot) ;
			p_logger->pushSink(pLogSink) ;
			//may as well chain here
			p_printer->chain(p_logger) ;
			break;
		}
		case IO_CRT:
			break;
	}
}
//
void MiaAgent::createRootDomain() {
	AiSymbol* pName = intern("/") ;
	MiaDomain& domain = *new MiaDomain(NULL, pName, NULL) ;
	AiSymbol *pMethodName = SYM_MAIN ;
	MiaMethodFactory *pMethodFactory = new MiaMethodFactory(domain, pMethodName) ;
	domain.addMethodFactory(pMethodFactory) ;
	pMethodName = SYM_MAIN ;
	pMethodFactory = new MiaMethodFactory(domain, pMethodName) ;
	domain.addMethodFactory(pMethodFactory) ;
	pMethodName = SYM_OUTPUT ;
	pMethodFactory = new MiaMethodFactory(domain, pMethodName) ;
	domain.addMethodFactory(pMethodFactory) ;
	p_rootDomain = &domain ;
}
void MiaAgent::createRootFrame() {
	AiSymbol* pName = intern("/") ;
	MiaFrame& frame = *new MiaFrame(NULL, pName) ;
	frame.create() ;
	p_rootFrame = &frame ;
}
//
MiaProblem* MiaAgent::createProblem(AiSymbol* pName) {
	MiaDomain* pDomain = getRootDomain().findDomain(pName) ;
	//TODO:Brain?
	MiaProblem* pProblem = new MiaProblem(pDomain) ;
	return pProblem ;
}
void MiaAgent::addProblem(MiaProblem* pProblem) {
	MiaExplorer* pExplorer = pProblem->getExplorer() ;
	pushExplorer(pExplorer) ;
}
void MiaAgent::destroyProblems() {
	delete getExplorer() ;
}
void MiaAgent::createCommander() {
	p_commander = new MiaCommander(this) ;
	p_commander->createEnabled() ;
}
//Commands
void MiaAgent::printPrompt() {
	k_printer() << "\nUSER > " << flush ;
}
void MiaAgent::printNews() {
	k_printer() << "***************************\n" ;
	k_printer() << "*  Mia .02\n" ;
	k_printer() << "***************************\n" ;
	k_printer().flush() ;
}
void MiaAgent::load(const bwString& fileName) {
	bool fReload = m_fileName == fileName ;
	m_fileName = fileName ;
	k_printer() << "Loading:  " << fileName << endl ;
	std::ifstream file ;
	file.open(fileName.c_str(), std::ios::out | std::ios::app | std::ios::binary) ;
	bwAssert(!file.fail()) ;
	//
	createRootDomain() ; //TODO:onCreate?
	createRootFrame() ; //TODO:onCreate?
	//
	MiaReader reader(file) ;
	reader.pushDomain(&getRootDomain()) ;
	reader.pushMind(&getRootFrame()) ;
	reader.read() ;
	if(fReload)
		getEventSlot().send(BwEvent(EVENT_RELOAD_ENDED)) ;
	else
		getEventSlot().send(BwEvent(EVENT_LOAD_ENDED)) ;
	k_printer().flush() ;
}
void MiaAgent::reload() {
	destroyProblems() ;
	load(m_fileName) ;
}
void MiaAgent::stop() {
	m_runStatus = RUN_STOPPED ;
}
void MiaAgent::pause() {
	m_runStatus = RUN_PAUSED ;
}
void MiaAgent::onInterrupt() {
	k_printer() << "Execution Interrupted:  \n" ;
}
void MiaAgent::run() {
	if(isPaused() && isSteppingSome())
		return runFor(m_steps) ;
	//else
	m_stepStatus = STEP_ALL ;
	bool success = true ;
	preRun() ;
	while(success) {
		if(!preStep()) break ;
		success = explorer().doStep() ;
		postStep() ;
	}
	postRun() ;
}
void MiaAgent::runFor(int count) {
	if(!(isPaused() && isSteppingSome()))
		m_steps = count ;

	m_stepStatus = STEP_SOME ;

	bool success = true ;
	preRun() ;
	for(int i = 0 ; i < count ; ++i) {
		if(!preStep()) break ;
		success = explorer().doStep() ;
		postStep() ;
		if(!success)
			break ;
	}
	postRun() ;
}
void MiaAgent::preRun() {
	m_stepCounter = 0 ;
	m_stepTimer.getElapsed() ;
	m_runTimer.getElapsed() ;
	m_runStatus = RUN_RUNNING ;
	k_printer() << "\nRun Started:  " ;
}
void MiaAgent::postRun() {
	k_printer() << "\nRun Ended:  " ;
	k_printer() << "\nTotal Steps:  " << m_stepCounter ;
	//k_printer() << ", Elapsed Time:  " << m_runTimer.getRealElapsed() << " seconds " << endl << flush ;
	k_printer() << ", Elapsed Time:  " << m_runTimer.getElapsed() << " ms " << endl << flush ;
	getEventSlot().send(BwEvent(EVENT_RUN_ENDED)) ;
	if(isPaused())
		m_steps = m_steps - m_stepCounter ;
	else {
		m_steps = 0 ;
		m_runStatus = RUN_STOPPED ;
	}
	printPrompt() ;
}
bool MiaAgent::preStep() {
	//TODO:is there a more transparent way? Yes but it involves spawning another thread. future stuff.
	//f6:todo: use BwPoWorker
	BwEnvelope env = BwPostOffice::singleton::get().pickup() ;
	if(!env.empty())
		env.deliver() ;
	bool running = isRunning() ;
	if(!running)
		onInterrupt() ;
	return running ;
}
void MiaAgent::postStep() {
	++m_stepCounter ;
	const char *spinner = "|" ;
	switch(m_stepCounter % 8) {
		case 0 :
		case 4 :
			spinner = "|" ;
			break ;
		case 1 :
		case 5 :
			spinner = "/" ;
			break ;
		case 2 :
		case 6 :
			spinner = "-" ;
			break ;
		case 3 :
		case 7 :
			spinner = "\\" ;
			break ;
	}
	//k_printer() << "\b" + spinner ;
	k_printer() << spinner << "\b" << flush ;
	//k_printer() << "Step #:  " << m_stepCounter++ ;
	//k_printer() << ", Elapsed Time:  " << m_stepTimer.getElapsed() << "ms " << endl << flush ;
	getEventSlot().send(BwEvent(EVENT_STEP_ENDED)) ;
}
void MiaAgent::doCommand(const BwCmd& cmd) {
	p_commander->dispatch(cmd) ;
}
//Notices & Events
////////////////////////////////
//MetaData
DECLARE_KITINFO(MiaDomainKit) ;
DECLARE_KITINFO(MiaMethodKit) ;
DECLARE_KITINFO(MiaRuleKit) ;
DECLARE_KITINFO(MiaTopicKit) ;
DECLARE_KITINFO(MiaIdentifierKit) ;
DECLARE_KITINFO(MiaCallKit) ;

KITINFO_BEGIN(MiaAgent)
	KITINFOREF(MiaFactKit),
	KITINFOREF(MiaIdentifierKit),
	KITINFOREF(MiaStateKit),
	KITINFOREF(MiaDomainKit),
	KITINFOREF(MiaMethodKit),
	KITINFOREF(MiaRuleKit),
	KITINFOREF(MiaTopicKit)
KITINFO_END
//
TYPEINFO_NONE(MiaAgent) ;

DEFINE_KITTYPE(MiaAgent) ;
DECLARE_KITINFO(AxlCore) ;
KITINFO_EX("MiaAgent", MIA_KT_AGENT, MiaAgent, AxlCore) ;

