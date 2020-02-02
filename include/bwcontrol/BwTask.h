/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwTask_H
#define _BwTask_H

#include <bwcore/BwActor.h>

class BwBrain ;
class BwTask ;
class BwPersonality ;
class BwTaskGroup ;
class BwScript ;

typedef std::list<BwTask*> BwTaskContainer ;
typedef BwTaskContainer::iterator BwTaskIter ;

typedef std::map<bwString, BwTask*> BwTaskMap ;
typedef BwTaskMap::iterator BwTaskMapIter ;

class BwTask : public BwActor {
public:
	enum taskStates {
		PLAN_START = 0,
		PLAN_BUSY,
		PLAN_SUCCESS,
		PLAN_FAILURE,
		
		TASK_START,
		TASK_BUSY,
		TASK_SUCCESS,
		TASK_FAILURE
	} ;
	typedef taskStates taskState ;
	BwTask(BwActor* pOwner) ; //constructor for brain
	BwTask(BwBrain *pBrain) ;
	void init() ;
	virtual ~BwTask() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doStep(BwStepper& stepper) ;

	void setStatus(taskState status) { m_status = status ; }
	taskState getStatus() { return m_status ; }
	bool testStatus(taskState status) { return m_status == status ; }

	bool taskBusy() { return m_status == TASK_BUSY ; }
	bool taskSuccess() { return m_status ==  TASK_SUCCESS ; }
	bool taskFinished() { return m_status == TASK_SUCCESS || TASK_FAILURE ; }
	//
	void addDependency(BwTask *pTask) { m_dependencies.push_front(pTask) ; }
	void clearDependencies() { m_dependencies.clear() ; }
	bool testDependencies(taskState status) ;
	//
	bool planBusy() { return m_status == PLAN_BUSY ; }
	bool planSuccess() { return m_status ==  PLAN_SUCCESS ; }
	bool planFinished() { return m_status == PLAN_SUCCESS || PLAN_FAILURE ; }

	virtual void think() {
		if(m_hasPlan == false)
    		plan() ;
	}
	virtual void plan() {
		m_hasPlan = true ;
	}
	void setScript(BwScript* pScript) { p_script = pScript ; }
	BwScript* getScript() { return p_script ; }
	//
	void setPersonality(BwPersonality* pPersonality) { p_personality = pPersonality ; }
	BwPersonality& personality() { return *getPersonality() ; }
	BwPersonality* getPersonality() { return p_personality ; }
	void setTaskGroup(BwTaskGroup* pTaskGroup) { p_taskGroup = pTaskGroup ; }
	BwTaskGroup* getTaskGroup() { return p_taskGroup ; }
	//
	BwBrain* getBrain() { return p_brain ; }
	//
	virtual void weigh() ;
	void setBaseWeight(int val){ m_baseWeight = val ; }
	int getBaseWeight(){ return m_baseWeight ; }
	void setWeight(int val){ m_weight = val ; }
	int getWeight(){ return m_weight ; }
	int m_baseWeight ;
	int m_weight ;
	/*Data Members*/
public:
	taskState m_status ;
	BwBrain *p_brain ;
	BwTaskContainer m_dependencies ;
	//
	bool m_hasPlan ;
	//
	BwScript *p_script ;
	//
	BwPersonality* p_personality ;
	BwTaskGroup* p_taskGroup ;
};
#endif //_BwTask_H

