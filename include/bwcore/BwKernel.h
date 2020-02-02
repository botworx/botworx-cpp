/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwKernel_H
#define _BwKernel_H

#include "BwSystem.h" 
#include <bwmessaging/BwMessage.h>

class BwMailSlot ;

class BwKernel : public BwSystem {
public:
	BwKernel() ;
	~BwKernel() ;
	virtual void doCreate(const BwPartInfo& info) ;
	//
	static void startup() ;
	static void shutdown() ;
	//
	bwPath getInitialPath() { return m_initialPath ; }
	void setCurrentPath(const bwPath& path) { m_currentPath = path ; }
	bwPath getCurrentPath() { return m_currentPath ; }
	bwPath getMediaPath();
	bwPath m_initialPath ;
	bwPath m_currentPath ;
	//Singleton support
	typedef BwSingletonT<BwKernel> singleton ;
	singleton m_singleton ;
} ;

#endif //_BwKernel_H
