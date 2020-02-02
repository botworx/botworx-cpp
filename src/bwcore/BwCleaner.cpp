/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwstd/BwCleaner.h>
//
//BwCleaner
//
BwCleaner::~BwCleaner() {
	for(BwCleanUpListIter iter = m_cleanups.begin() ; iter != m_cleanups.end() ; ++iter) {
		(*iter)() ;
	}
}
void BwCleaner::addCleanup(const BwCleanUp& cleanup) {
	m_cleanups.push_back(cleanup) ;
}
//Singleton support
template<> BwCleaner* BwCleaner::singleton::g_singleton = 0 ;
