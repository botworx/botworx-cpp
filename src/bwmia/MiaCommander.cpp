/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaCommander.h>
#include <bwmia/MiaAgent.h>
#include <bwmia/MiaState.h>

#include <bwmessaging/BwCmd.h>
#include <bwmessaging/BwIoSlot.h>

#include <bwcore/BwFileKit.h>

#include <sol/sol.hpp>
//
//MiaCommander
//
MiaCommander::MiaCommander(MiaAgent* pAgent) : BwPart(pAgent) {
	p_agent = pAgent ;
	p_cmdSession = new CmdSession(this) ;
	p_mindSelection = NULL ;
}
MiaCommander::~MiaCommander() {
	delete p_cmdSession ;
}
void MiaCommander::dispatch(const BwCmd& cmd) {
	CmdEngine& lua = CmdEngine::singleton::get() ;
	lua.setSession(p_cmdSession) ;
	lua.dostring(cmd.c_str()) ;
}
//TODO:???!!!
// #undef max
namespace _MiaCommander {
void news() {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	pAgent->printNews() ;
	pAgent->printPrompt() ;
}
void load(const std::string& fileName) {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	pAgent->p_fileKit->changeDir() ;
	pAgent->load(fileName) ;
	pAgent->printPrompt() ;
}
void reload() {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	pAgent->p_fileKit->changeDir() ;
	pAgent->reload() ;
	pAgent->printPrompt() ;
}
void stop() {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	pAgent->stop() ;
}
void pause() {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	pAgent->pause() ;
}
void run() {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	pAgent->run() ;
}
void step(int count) {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	pAgent->runFor(count) ;
}
void chdir(const std::string& dirName) {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	pAgent->p_fileKit->setDir(dirName) ;
}
/////////
void listIo() {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	pAgent->getIoSlot().printTree() ;
	k_printer().flush() ;
}
void setString(const std::string& path, const std::string& value)  {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	BwIo* pNode = pAgent->getIoSlot().findOrCreateIo(path) ;
	pNode->setValue(BwIo::StringValue(value)) ;
}
void setInt(const std::string& path, int value)  {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	BwIo* pNode = pAgent->getIoSlot().findOrCreateIo(path) ;
	pNode->setValue(BwIo::IntValue(value)) ;
}
void setFloat(const std::string& path, float value)  {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	BwIo* pNode = pAgent->getIoSlot().findOrCreateIo(path) ;
	pNode->setValue(BwIo::FloatValue(value)) ;
}
//TODO:may want get to actually send an io pulse?
void getIo(const std::string& path) {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	BwIo* pNode = pAgent->getIoSlot().findIo(path) ;
	pNode->print() ;
	k_printer().flush() ;
}
///
void selectMind(bwHandle handle) {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaCommander *pCommander = session.p_commander ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	MiaMind* pMind = dynamic_cast<MiaMind*>(pAgent->getMailCenter().findAddressee(handle)) ;
	pMind->outputFacts() ; //refresh subscribers
	pMind->outputLog() ; //refresh subscribers
	pCommander->setMindSelection(pMind) ;
}
void printMind() {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaCommander *pCommander = session.p_commander ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	MiaMind* pMind = pCommander->getMindSelection() ;
	if(pMind != NULL)
		k_printer() << *pMind ;
	else
		k_printer() << "No mind selected!!!" ;
	pAgent->printPrompt() ; //flushes printer also.
}
void printBranch() {
	MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaCommander *pCommander = session.p_commander ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	MiaMind* pMind = pCommander->getMindSelection() ;
	pMind->printBranch(k_printer()) ;
	pAgent->printPrompt() ;
}
void query(const std::string& query) {
	bwAssert(0) ;
	/*MiaCommander::CmdSession& session = MiaCommander::CmdEngine::singleton::get().session() ;
	MiaCommander *pCommander = session.p_commander ;
	MiaAgent *pAgent = session.p_commander->getAgent() ;
	MiaMind* pMind = pCommander->getMindSelection() ;
	//
	std::strstream stream ;
	//Domain
	stream << "(domain " ;
	AiSymbol* pDomainSym = genSym("Domain") ;
	stream << pDomainSym->getString() << " () " ;
	stream << "(method main () " ;
	stream << "(rule " << query ;
	stream << " ==> halt ==> halt))" ; //end of method
	//stream << " ==> success ==> failure)))" ; //end of method
	stream << ")" ; //end of domain
	//Task
	stream << "(task " ;
	stream << pDomainSym->getString() ;
	stream << ")\n " ;
	//
	stream.str()[stream.pcount()] = 0 ; //TODO:I hate this stream termination bullshit.
	k_printer() << stream.str() << flush ;
	//Okay here is the real fun
	MiaExplorer* pExplorer = new MiaExplorer() ;
	k_agent().pushExplorer(pExplorer) ;
	pExplorer->getRoot()->load(stream) ;
	pExplorer->getTask()->getSpace()->copyTopics(pMind->getSpace(), false) ; //shallow copy
	k_agent().run() ;
	k_agent().popExplorer() ;
	delete pExplorer ;*/
}
//////////
} //end namespace _MiaCommander
using namespace _MiaCommander ;

MiaCommander::CmdEngine::CmdEngine() {
	// using namespace luabind;
	sol::state_view lua(getState());
	lua.set_function("news", &news);
	lua.set_function("load", &load);
	lua.set_function("reload", &reload);
	lua.set_function("stop", &stop);
	lua.set_function("pause", &_MiaCommander::pause);
	lua.set_function("run", &run);
	lua.set_function("step", &step);
	lua.set_function("chdir", &_MiaCommander::chdir);
	//
	lua.set_function("listIo", &listIo);
	lua.set_function("setString", &setString);
	lua.set_function("setInt", &setInt);
	lua.set_function("setFloat", &setFloat);
	lua.set_function("getIo", &getIo);
	//
	lua.set_function("selectMind", &selectMind);
	lua.set_function("printMind", &printMind);
	lua.set_function("printBranch", &printBranch);
	lua.set_function("query", &query);
}
//Singleton support
template<> MiaCommander::CmdEngine* BwAutoSingletonT<MiaCommander::CmdEngine>::g_singleton = 0 ;
