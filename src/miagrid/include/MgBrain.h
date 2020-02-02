/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _MgBrain_H
#define _MgBrain_H

#include <bwcontrol/BwBrain.h>

class MgEntity ;
class MiaAgent ;
class MiaExplorer ;
class MiaState ;
class MgPlace ;
class BwPlan ;
class BwTask ;

class MgLuaSession ;

class MgBrain : public BwBrain {
public:
	MgBrain(MgEntity* pEntity) ;
	virtual ~MgBrain() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createAgent() ;
	//virtual bool doPostStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	void think() ;
	void plan() ;
	virtual void sense() ;
	void sensePlace(MgPlace* pPlace) ;
	void senseVacancy(MgPlace* pPlace) ;
	void senseEntity(MgEntity* pEntity) ;
	//
	void doPlan() ;
	void doTask() ;
	//
	void moveTo(int x, int y) ;
	void setExplorer(MiaExplorer* pExplorer) { p_explorer = pExplorer ; }
	/*Data Members*/
public:
	MgEntity* p_entity ;
	MiaAgent* p_agent ;
	MiaExplorer* p_explorer ;
	MiaState* p_problem ;
	//
	MgLuaSession* p_luaSession ;
};

#endif //_MgBrain_H
