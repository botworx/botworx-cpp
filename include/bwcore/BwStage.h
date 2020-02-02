/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwStage_H
#define _BwStage_H

#include "BwActor.h"

class BwStage ;
class BwDefaultStage ;

template<>
struct BwSigT<BwStage> : BwSigT<BwPart> {
	typedef BwActor				T_Owner ;
	typedef BwActor				T_Part ;
	typedef BwActorContainer	T_Container ;
	static bwString name() { return "BwStage" ; }
} ;

class BwStage : public BwPart {
public:
	BwStage() : BwPart(nullptr) {} //class must be embedded!!!
	virtual bwString getClassName() { return "BwStage" ; }

	virtual void addActor(BwActor *pActor) = 0 ;
	virtual void removeActor(BwActor *pActor) = 0 ;
	virtual void scheduleActor(BwActor *pActor) = 0 ;
	virtual void doStep(BwStepper& stepper) = 0 ;
	virtual bool onStep(BwStepper& stepper) = 0 ;
	virtual void doPostStep(BwStepper& stepper) = 0 ;
	//
	virtual bool onPostStep(BwStepper& stepper) = 0 ;
	bool invokeStep(BwStepper& stepper) {
		doStep(stepper) ;
		return onStep(stepper) ;
	}
	bool invokePostStep(BwStepper& stepper) {
		doPostStep(stepper) ;
		return onPostStep(stepper) ;
	}
	/*Data Members*/
public:
};
///////////////////////////////////
template<typename T_Class, typename T_Base = BwStage>
class BwStageT : public T_Base {
public:
	typedef BwSigT<T_Class>					        T_Sig ;
	typedef typename T_Sig::T_Part			        T_Part ;
	typedef typename T_Sig::T_Container		        T_Container ;
	typedef typename T_Sig::T_Container::iterator   T_ContainerIter ;
	typedef typename T_Sig::T_Owner			        T_Owner ;
	typedef std::list<T_Part*>				        T_List ;
	typedef typename T_List::iterator               T_ListIter ;
	//
	enum JobType_E {
		JOB_WAKE,
		JOB_SLEEP
	} ;
	typedef JobType_E JobType ;
	typedef typename std::pair<JobType, T_Part*> Job ;
	typedef std::list<Job> T_Jobs ;
	typedef typename T_Jobs::iterator JobIter ;
///
	/*Data Members*/
public:
	T_Container m_actors ;
	T_List m_actingActors ;
	T_Jobs m_jobs ;
	//
	void addJob(Job& job) { m_jobs.push_back(job) ; }
	bool hasJobs() { return !m_jobs.empty() ; }
	//
	bool m_isEnsemble ;
	void setIsEnsemble(bool val) { m_isEnsemble = val ; }
	bool isEnsemble() { return m_isEnsemble ; }
///
	BwStageT() : T_Base(), m_isEnsemble(false) {
	}
	~BwStageT() {
		destroyActors() ;
	}
	void destroyActors() {
		if(m_actors.empty())
			return ;
		BwActor *pActor = nullptr ;
		for (T_ContainerIter iter = m_actors.begin();
			iter != m_actors.end(); ++iter)	{
			pActor = (*iter) ;
			destroyPart(pActor) ;
		}
	}
	T_Owner& owner() { return *static_cast<T_Owner*>(this->p_owner) ; }
	T_Container& getActors() { return m_actors ; }
	int getActorCount() { return m_actors.size() ; }

	virtual void onActorStep(T_Part *pActor) {
		if(pActor->isMigrating())
			onMigratingActor(pActor) ;
	}
	virtual void onActorPostStep(T_Part *pActor) {
		if(!pActor->isAlive())
			onDeadActor(pActor) ;
		else if(pActor->isDozing())
			onDozingActor(pActor) ;
	}
	virtual void onDeadActor(T_Part *pActor) {
		removeActor(pActor) ;
		destroyPart(pActor) ;
	}
	virtual void onDozingActor(T_Part *pActor) {
		pActor->sleep() ;
	}
	virtual void onMigratingActor(T_Part *pActor) {
		removeActor(pActor) ;
		pActor->migrate() ;
	}
	virtual void doConfig() {
		if(m_actors.empty())
			return ;
		BwActor *pActor = nullptr ;
		for (T_ContainerIter iter = m_actors.begin();
			iter != m_actors.end(); ++iter)	{
			pActor = (*iter) ;
			pActor->doConfig() ;
		}
		T_Base::doConfig() ;
	}
	virtual void doPostConfig() {
		if(m_actors.empty())
			return ;
		BwActor *pActor = nullptr ;
		for (T_ContainerIter iter = m_actors.begin();
			iter != m_actors.end(); ++iter)	{
			pActor = (*iter) ;
			pActor->doPostConfig() ;
		}
		T_Base::doPostConfig() ;
	}
	virtual void doEnable(bool sleeping) {
		if(m_actors.empty())
			return T_Base::doEnable(sleeping) ; //is sleeping
		//most stages will not want to wake up all actors
		if(!sleeping && this->isOperational() && !isEnsemble())
			return T_Base::doEnable(sleeping) ; //is sleeping
		BwActor *pActor = nullptr ;
		for (T_ContainerIter iter = m_actors.begin();
			iter != m_actors.end(); ++iter)	{
			pActor = (*iter) ;
			pActor->doEnable(sleeping) ;
		}
		return T_Base::doEnable(sleeping) ;
	}
	virtual void doPostEnable(bool sleeping) {
		if(m_actors.empty())
			return T_Base::doPostEnable(sleeping) ;
		//most stages will not want to wake up all actors
		if(!sleeping && this->isOperational() && !isEnsemble())
			return T_Base::doEnable(sleeping) ; //is sleeping

		BwActor *pActor = nullptr ;
		for (T_ContainerIter iter = m_actors.begin();
			iter != m_actors.end(); ++iter)	{
			pActor = (*iter) ;
			pActor->doPostEnable(sleeping) ;
		}
		T_Base::doPostEnable(sleeping) ;
	}
	virtual void doDisable(bool sleeping) {
		if(m_actors.empty())
			return ;
		BwActor *pActor = nullptr ;
		for (T_ContainerIter iter = m_actors.begin();
			iter != m_actors.end(); ++iter)	{
			pActor = (*iter) ;
			pActor->doDisable(sleeping) ;
		}
		T_Base::doDisable(sleeping) ;
	}
	virtual void doPostDisable(bool sleeping) {
		if(m_actors.empty())
			return ;
		BwActor *pActor = nullptr ;
		for (T_ContainerIter iter = m_actors.begin();
			iter != m_actors.end(); ++iter)	{
			pActor = (*iter) ;
			pActor->doPostDisable(sleeping) ;
		}
		T_Base::doPostDisable(sleeping) ;
	}
	virtual void doStep(BwStepper& stepper) {
		T_Part *pActor = nullptr ;
		bool success ;
		//Step the Actors!!!
		if(!m_actingActors.empty()) {
			for (T_ListIter iter = m_actingActors.begin();
				iter != m_actingActors.end(); ++iter)	{
				pActor = (*iter) ;
				//success = pActor->doStep(stepper) ;
				success = pActor->invokeStep(stepper) ;
				if(!success) {
					if(pActor->isHalted()) {
						this->halt() ;
						return ;
					}
					//else
					addIdleActor(pActor) ;
				}
				onActorStep(pActor) ;
			}
		}
		//Step actors that were woken by previously stepped actors.
		if(hasJobs())
			processJobs(stepper) ;
	}
	virtual bool onStep(BwStepper& stepper) {
	    return !this->isHalted() ;
    }
	void addIdleActor(T_Part* pActor) {
	    Job job = Job(JOB_SLEEP, pActor);
		addJob(job) ;
	}
	virtual void doPostStep(BwStepper& stepper) {
		T_Part *pActor ;
		bool success ;
		if(!m_actingActors.empty()) {
			for (T_ListIter iter = m_actingActors.begin();
					iter != m_actingActors.end(); ++iter)	{
				pActor = (*iter) ;
				success = pActor->invokePostStep(stepper) ;
				if(!success) {
					if(pActor->isHalted()) {
						this->halt() ;
						return ;
					}
					//else
					addIdleActor(pActor) ;
				}
				onActorPostStep(pActor) ;

			}
		}
		if(hasJobs())
			processJobs(stepper) ;
	}
	virtual bool onPostStep(BwStepper& stepper) {
		if(owner().isAutoSleeper() && !isActive()) {
			owner()._doze() ;
			return false ;
		}
		else
			return true ;
	}
	void processJobs(BwStepper& stepper) {
		T_Part *pActor ;
		for (JobIter iter = m_jobs.begin(); iter != m_jobs.end(); ++iter) {
			pActor = iter->second ;
			switch(iter->first) {
				case JOB_WAKE :
					if(pActor->invokeStep(stepper))
						addActingActor(pActor) ;
					onActorStep(pActor) ;
					break ;
				case JOB_SLEEP :
					removeActingActor(pActor) ;
					break ;
			}
		}
		m_jobs.clear() ;
	}
	virtual void addActor(BwActor *pActor) {
		m_actors.push_back(static_cast<T_Part*>(pActor)) ;
		onActorAddition(static_cast<T_Part*>(pActor)) ;
	}
	virtual void onActorAddition(T_Part *pActor) {
	}
	virtual void removeActor(BwActor *pActor) {
		T_ContainerIter actor = std::find(m_actors.begin(),m_actors.end(),pActor) ;
		if(actor != m_actors.end())
			m_actors.erase(actor) ;
		onActorRemoval(static_cast<T_Part*>(pActor)) ;
	}
	virtual void onActorRemoval(T_Part *pActor) {
	}
	void addActingActor(T_Part *pActor) {
		m_actingActors.push_back(pActor) ;
	}
	void addWakingActor(T_Part *pActor) {
	    Job job = Job(JOB_WAKE, pActor);
		addJob(job) ;
	}
	void removeActingActor(BwActor *pActor) {
		T_ListIter actor
			= std::find(m_actingActors.begin(),m_actingActors.end(),pActor) ;
		if(actor != m_actingActors.end())
			m_actingActors.erase(actor) ;
	}
	virtual void scheduleActor(BwActor *pActor) {
		addWakingActor(static_cast<T_Part*>(pActor)) ;
		if(owner().isSleeping())
			owner().wake() ;
	}
	bool isEmpty() {
		return m_actors.empty() ;
	}
	bool isIdle() {
		return !isActive() ;
	}
	bool isActive() {
		return ! ( m_actingActors.empty() && m_jobs.empty() ) ;
	}
	void clear() {
		m_actingActors.clear() ;
		m_jobs.clear() ;
	}
} ;
///////////////////////////////////
template<>
struct BwSigT<BwDefaultStage> : BwSigT<BwStage> {
	typedef BwActor				T_Part ;
	typedef BwActorContainer	T_Container ;
	static bwString name() { return "BwDefaultStage" ; }
} ;
typedef BwStageT<BwDefaultStage, BwStage> BwDefaultStageBase ;

class BwDefaultStage : public BwDefaultStageBase {
public:
	BwDefaultStage() : BwDefaultStageBase() {}
} ;

#endif //_BwStage_H
