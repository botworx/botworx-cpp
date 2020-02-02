/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbScenarioFactories_H
#define _BbScenarioFactories_H

#include <bwvr/VrScenarioFactory.h>

#include "BbScenario.h"
//#include "BbColladaScenario.h"
#include "BbTestScenario.h"
//#include "BbTsmDemo.h"

#include <buggybots/scenarios/soccerscenario/SocScenario.h>
#include <buggybots/scenarios/mpscenario/MpScenario.h>
//#include <buggybots/scenarios/CtfScenario/CtfScenario.h>
//
//BbSimpleScenarioFactory
//
class BbSimpleScenarioFactory : public VrScenarioFactory {
public:
	BbSimpleScenarioFactory(BwPart* pOwner, BwKit *pKit = NULL) : VrScenarioFactory(pOwner, pKit) {
		setName("SimpleScenario") ;
	}
	virtual VrScenario* produce(VrApplet *pApplet, bwPartStyle style = PS_DEFAULT) {
		VrScenario* pScenario = new BbSimpleScenario(pApplet) ;
		pScenario->setFactory(this) ;
		pScenario->create(style) ;
		return pScenario ;
	}
} ;
//
//BbDefaultScenarioFactory
//
class BbDefaultScenarioFactory : public VrScenarioFactory {
public:
	BbDefaultScenarioFactory(BwPart* pOwner, BwKit *pKit = NULL) : VrScenarioFactory(pOwner, pKit) {
		setName("DefaultScenario") ;
	}
	virtual VrScenario* produce(VrApplet *pApplet, bwPartStyle style = PS_DEFAULT) {
		VrScenario* pScenario = new BbDefaultScenario(pApplet) ;
		pScenario->setFactory(this) ;
		pScenario->create(style) ;
		return pScenario ;
	}
} ;
//
//BbTerrainScenarioFactory
//
class BbTerrainScenarioFactory : public VrScenarioFactory {
public:
	BbTerrainScenarioFactory(BwPart* pOwner, BwKit *pKit = NULL) : VrScenarioFactory(pOwner, pKit) {
		setName("TerrainScenario") ;
	}
	virtual VrScenario* produce(VrApplet *pApplet, bwPartStyle style = PS_DEFAULT) {
		VrScenario* pScenario = new BbTerrainScenario(pApplet) ;
		pScenario->setFactory(this) ;
		pScenario->create(style) ;
		return pScenario ;
	}
} ;
//
//BbTestScenarioFactory
//
class BbTestScenarioFactory : public VrScenarioFactory {
public:
	BbTestScenarioFactory(BwPart* pOwner, BwKit *pKit = NULL) : VrScenarioFactory(pOwner, pKit) {
		setName("TestScenario") ;
	}
	virtual VrScenario* produce(VrApplet *pApplet, bwPartStyle style = PS_DEFAULT) {
		VrScenario* pScenario = new BbTestScenario::BbTestScenario(pApplet) ;
		pScenario->setFactory(this) ;
		pScenario->create(style) ;
		return pScenario ;
	}
} ;
//
//BbTsmDemoFactory
//
/*class BbTsmDemoFactory : public VrScenarioFactory {
public:
	BbTsmDemoFactory(BwPart* pOwner, BwKit *pKit = NULL) : VrScenarioFactory(pOwner, pKit) {
		setName("TsmDemo") ;
	}
	virtual VrScenario* produce(VrApplet *pApplet, bwPartStyle style = PS_DEFAULT) {
		VrScenario* pScenario = new BbTsmDemo::BbTsmDemo(pApplet) ;
		pScenario->setFactory(this) ;
		pScenario->create(style) ;
		return pScenario ;
	}
} ;*/
//
//BbSoccerScenarioFactory
//
class BbSoccerScenarioFactory : public VrScenarioFactory {
public:
	BbSoccerScenarioFactory(BwPart* pOwner, BwKit *pKit = NULL) : VrScenarioFactory(pOwner, pKit) {
		setName("SoccerScenario") ;
	}
	virtual VrScenario* produce(VrApplet *pApplet, bwPartStyle style = PS_DEFAULT) {
		VrScenario* pScenario = new SoccerScenario::BbSoccerScenario(pApplet) ;
		pScenario->setFactory(this) ;
		pScenario->create(style) ;
		return pScenario ;
	}
} ;
//
//MpScenarioFactory
//
class MpScenarioFactory : public VrScenarioFactory {
public:
	MpScenarioFactory(BwPart* pOwner, BwKit *pKit = NULL) : VrScenarioFactory(pOwner, pKit) {
		setName("MpScenario") ;
	}
	virtual VrScenario* produce(VrApplet *pApplet, bwPartStyle style = PS_DEFAULT) {
		VrScenario* pScenario = new MpScenario::MpScenario(pApplet) ;
		pScenario->setFactory(this) ;
		pScenario->create(style) ;
		return pScenario ;
	}
} ;
//
//CtfScenarioFactory
//
/*class CtfScenarioFactory : public VrScenarioFactory {
public:
	CtfScenarioFactory(BwPart* pOwner, BwKit *pKit = NULL) : VrScenarioFactory(pOwner, pKit) {
		setName("CtfScenario") ;
	}
	virtual VrScenario* produce(VrApplet *pApplet, bwPartStyle style = PS_DEFAULT) {
		VrScenario* pScenario = new CtfScenario::CtfScenario(pApplet) ;
		pScenario->setFactory(this) ;
		pScenario->create(style) ;
		return pScenario ;
	}
} ;*/

//
//BbColladaScenarioFactory
//
#if BB_OPTION_USE_COLLADA

/*class BbColladaScenarioFactory : public VrScenarioFactory {
public:
	BbColladaScenarioFactory(BwPart* pOwner, const bwPath& path, BwKit *pKit = NULL) : VrScenarioFactory(pOwner, pKit) {
		m_path = path ;
		setName(path.leaf().string()) ;
	}
	virtual VrScenario* produce(VrApplet *pApplet, bwPartStyle style = PS_DEFAULT) {
		BbColladaScenario* pScenario = new BbColladaScenario(pApplet) ;
		pScenario->setFactory(this) ;
		pScenario->setName(getName()) ;
		pScenario->setPath(m_path) ;
		pScenario->create(style) ;
		return pScenario ;
	}
	//Data Members
	bwPath m_path ;
} ;*/

#endif //BB_OPTION_USE_COLLADA

#endif //_BbScenarioFactories_H
