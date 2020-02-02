/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrScenarioManager_H
#define _VrScenarioManager_H

#include "VrScenarioFactory.h"

//
//VrScenarioManager
//
class VrScenarioManager : public BwKit {
public:
	VrScenarioManager(BwPart *pParent) ;
	VrScenarioFactory* findFactory(const bwString &name) ;
	void addFactory(VrScenarioFactory *pFactory) ;
	VrScenarioFactories& factories() { return *getFactories() ; }
	VrScenarioFactories* getFactories() { return &m_factories ; }
	//Data Members
	VrScenarioFactories m_factories ;
	VrScenarioFactoryMap m_factoryMap ;
	//Singleton support
public:
	struct singleton_alloc {
		static VrScenarioManager* alloc() ;
	} ;
	typedef BwAutoSingletonT<VrScenarioManager, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;

#endif //_VrScenarioManager_H