/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcore/BwKernel.h>
#include <bwmessaging/BwMessaging.h>
#include <bwstd/BwCleaner.h>

//
#include <boost/filesystem/operations.hpp>
using namespace boost::filesystem;

//
//BwKernel
//
BwKernel::BwKernel() : BwSystem(nullptr) {
	m_currentPath = m_initialPath = initial_path();
}
BwKernel::~BwKernel() {
}
void BwKernel::doCreate(const BwPartInfo& info) {
	BwSystem::doCreate(info) ;
	BwMessaging* pMessaging = new BwMessaging(this) ;
	pMessaging->create() ;
	addKit(pMessaging) ;
}
bwPath BwKernel::getMediaPath() {
    return getInitialPath() / "../media" ;
}
//Singleton support
void BwKernel::startup() {
	new BwCleaner() ;
	BwKernel* pKernel = new BwKernel() ;
	pKernel->create() ;
	pKernel->configAndEnable() ;
}
void BwKernel::shutdown() {
	destroyPart(BwKernel::singleton::getPtr()) ;
	delete BwCleaner::singleton::getPtr() ;
}
template<> BwKernel* BwKernel::singleton::g_singleton = 0 ;
