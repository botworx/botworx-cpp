/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See botworx_license.txt for details.
*/
#include "stdafx.h"
#include "BbCeguiApplet.h"
#include <buggybots/BbKernel.h>

#include <OGRE/OgreException.h>

//INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
int main()
{
	//TODO:Have kernel do this!
	//_CrtSetBreakAlloc(192) ;
	// Get the current bits
	/*
	int tmpDbgFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpDbgFlag = (tmpDbgFlag & 0x0000FFFF) ; // Clear the upper 16 bits 
	*/
	// Clear the upper 16 bits and OR in the desired freqency
	//tmpDbgFlag |= _CRTDBG_CHECK_EVERY_16_DF;
	//tmpDbgFlag |= _CRTDBG_CHECK_ALWAYS_DF;
	//tmpDbgFlag |= _CRTDBG_DELAY_FREE_MEM_DF;
	//tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF;
	// Set the new bits
	/*
	_CrtSetDbgFlag(tmpDbgFlag);
	*/
	/*Set Debug Reporting Parameters*/
	//_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
	//_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );

	//_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG);
	/*
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
	_CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDERR );
	*/
	/*Install Debug Hooks*/
	//////////////_CRT_DUMP_CLIENT pOldDumper = _CrtSetDumpClient(MiaSystem_dumper);
//
	BbKernel::startup() ;
    // Create application object
    BbCeguiApplet app;

	#if VR_OPTION_THREADING
		app.setRunnerType(BwApplet::RUNNER_ASYNC) ;
	#endif

	try {
		app.createEnabled() ;
	}
	catch(BwException &e) {
		return 0 ;
	}

    try {
 		app.go();
    } 
	catch( Ogre::Exception& e ) {
		std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
    }

	try {
		app.disable(false) ;
	}
	catch(BwException &e) {
		return 0 ;
	}

	BbKernel::shutdown() ;

    return 0;
}
