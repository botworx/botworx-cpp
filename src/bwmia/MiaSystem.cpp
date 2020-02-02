/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaSystem.h>
#include <bwmia/MiaAgent.h>

#include <bwai/AiNumber.h>

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>

#include <bwmia/MiaDomain.h>

#include <bwmia/MiaBinder.h>

#include <bwcore/BwKernel.h>

MiaSystem::MiaSystem() {
}
MiaAgent* MiaSystem::createAgent(const std::string& name, const std::string& fileName) {
	MiaAgent* pAgent = produceAgent() ;
	pAgent->setName(name) ;
	pAgent->createEnabled() ;
	pAgent->load(fileName) ;
	p_agent = pAgent ;
	return pAgent ;
}
MiaAgent* MiaSystem::produceAgent() {
	MiaAgent* pAgent = MiaAgent::produceAgent() ;
	return pAgent ;
}
//Debug support
void __cdecl MiaSystem_dumper(void *ptr, size_t block_size) {
	//AiCore::dumpBlock(ptr, block_size) ;
}
void MiaSystem_debug_open() {
	/*
	//_CrtSetBreakAlloc(192) ;
	// Get the current bits
	int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpDbgFlag = (tmpDbgFlag & 0x0000FFFF) ; // Clear the upper 16 bits 
	// Clear the upper 16 bits and OR in the desired freqency
	tmpDbgFlag |= _CRTDBG_CHECK_EVERY_16_DF;
	//tmpDbgFlag |= _CRTDBG_CHECK_ALWAYS_DF;
	//tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;
	//tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
	// Set the new bits
	_CrtSetDbgFlag(tmpDbgFlag);

	// Set Debug Reporting Parameters
	//_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
	//_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );

	//_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
	_CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDERR );
	//Install Debug Hooks
	_CRT_DUMP_CLIENT pOldDumper = _CrtSetDumpClient(MiaSystem_dumper);
	*/
}
void MiaSystem_debug_close() {
	// _CrtDumpMemoryLeaks() ;
}
void MiaSystem::open() {
#if BW_DEBUG
	MiaSystem_debug_open() ;
#endif
	BwKernel::startup() ;
}
void MiaSystem::close() {
	destroyPart(p_agent) ;
	BwKernel::shutdown() ;
#if BW_DEBUG
	MiaSystem_debug_close() ;
#endif
}
//Singleton support
MiaSystem* MiaSystem::s_singleton = NULL;
MiaSystem& MiaSystem::singleton() {
    if(s_singleton == NULL) {
		s_singleton = new MiaSystem() ;
    }
	return *s_singleton ;
}