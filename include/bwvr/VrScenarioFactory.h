/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrScenarioFactory_H
#define _VrScenarioFactory_H

#include <bwcore/BwFactory.h>

class VrApplet ;
class VrScenario ;
//
//VrScenarioFactory
//
class VrScenarioFactory : public BwFactory {
public:
	VrScenarioFactory(BwPart* pOwner, BwKit *pKit = NULL) : BwFactory(pOwner, pKit) {}
	virtual VrScenario* produce(VrApplet *pApplet, bwPartStyle style = PS_DEFAULT) { return NULL ; }
	virtual void release(void *pCell) ;
	//Data
} ;
typedef std::vector<VrScenarioFactory*> VrScenarioFactories ;
typedef VrScenarioFactories::iterator VrScenarioFactoryIter ;
typedef std::map<std::string, VrScenarioFactory*> VrScenarioFactoryMap ;
typedef std::map<std::string, VrScenarioFactory*>::iterator VrScenarioFactoryMapIter ;

#endif //_VrScenarioFactory_H