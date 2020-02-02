/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwBrain_H
#define _BwBrain_H

#include "BwTask.h"
#include <bwcore/BwStage.h>

typedef std::list<BwBrain*> BwBrainContainer ;
typedef BwBrainContainer::iterator BwBrainIter ;
/////////////////////
class BwBrainStage ;
template<>
struct BwSigT<BwBrainStage> : BwSigT<BwStage> {
	typedef BwBrain				T_Owner ;
	typedef BwBrain				T_Part ;
	typedef BwBrainContainer	T_Container ;
	static bwString name() { return "BwBrainStage" ; }
} ;
typedef BwStageT<BwBrainStage, BwStage> BwBrainStageBase ;
class BwBrainStage : public BwBrainStageBase {} ;

/////////////////////
class BwTaskStage ;
template<>
struct BwSigT<BwTaskStage> : BwSigT<BwStage> {
	typedef BwBrain				T_Owner ;
	typedef BwTask			T_Part ;
	typedef BwTaskContainer	T_Container ;
	static bwString name() { return "BwTaskStage" ; }
} ;
typedef BwStageT<BwTaskStage, BwStage> BwTaskStageBase ;
class BwTaskStage : public BwTaskStageBase {} ;
/////////////////////
class BwBrain : public BwTask {
public:
	BwBrain(BwActor* pActor) ;
	virtual void doConfig() ;
	virtual void doPostConfig() ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doPostEnable(bool sleeping = false) ;
	virtual void doDisable(bool sleeping = true) ;
	virtual void doPostDisable(bool sleeping = true) ;
	virtual void doStep(BwStepper& stepper) ;
	virtual void doPostStep(BwStepper& stepper) ;
	//Tasks
	virtual void createPersonality() {}
	BwTask* useTask(const bwString& name) ;
	//Masters
	void setMaster(BwBrain *pBrain) ;
	BwBrain* getMaster() { return p_master ; }
	//Slaves
	void addSlave(BwBrain *pBrain) ;
	void removeSlave(BwBrain *pBrain) ;
	void setIsSlave(bool val) { m_isSlave = val ; }
	bool isSlave() { return m_isSlave ; }
	//
	virtual void schedule() ;
	//
	virtual bool processMessage(const BwMessage& msg) ;
protected:
	/*Data Members*/
public:
	BwBrain *p_master ;
	BwTaskStage m_taskStage ;
	BwBrainStage m_slaveStage ;
	bool m_isSlave ;
};

#endif //_BwBrain_H