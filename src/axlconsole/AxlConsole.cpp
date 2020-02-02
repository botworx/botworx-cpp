/*AXL - A Lispish interpreter for Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"
#include <bwaxl/config/config.h>

void __cdecl BwDbg_dumper(void *ptr, size_t block_size) {
	// AiCore::dumpBlock(ptr, block_size) ;
}
void BwDbg_enter() {
	/*
	//_CrtSetBreakAlloc(1635) ;
	int tmpDbgFlag ;
	// Get the current bits
	tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	// Clear the upper 16 bits and OR in the desired freqency
	tmpDbgFlag = (tmpDbgFlag & 0x0000FFFF) | _CRTDBG_CHECK_EVERY_16_DF;
	//tmpDbgFlag = (tmpDbgFlag & 0x0000FFFF) | _CRTDBG_CHECK_ALWAYS_DF;
	//tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;
	//tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
	// Set the new bits
	_CrtSetDbgFlag(tmpDbgFlag);

	// Set Debug Reporting Parameters
	//_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
	//_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );

	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG);
	// Install Debug Hooks
	_CRT_DUMP_CLIENT pOldDumper = _CrtSetDumpClient(BwDbg_dumper);
	return ;
	*/
}
void BwDbg_exit() {
	// _CrtDumpMemoryLeaks() ;
}

// int _tmain(int argc, _TCHAR* argv[]) {
	int main() {
	// BwDbg_enter() ;
	AxlCore *pEngine = AxlCore::createInstance() ;
	printf("\t\t\tAXL 0.01 - Kurtis Fields - 2004\n");
	pEngine->run() ;
	//delete pEngine ;
	destroyPart(pEngine) ;
	BwDbg_exit() ;
	return 0;
}