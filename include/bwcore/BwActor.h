/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwActor_H
#define _BwActor_H

class BwBrain ;
class BwStage ;
class BwActor ;

template<>
struct BwSigT<BwActor> {
	typedef BwActorContainer	T_Container ;
	typedef BwActor				T_Owner ;
	//
	static bwString name() { return "Kit" ; }
} ;

class BwActor : public BwPart {
public:
	BwActor(BwActor *pParent) ;
	virtual ~BwActor() ;

	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void doConfig() ;
	virtual void doPostConfig() ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doPostEnable(bool sleeping = false) ;
	virtual void doDisable(bool sleeping = true) ;
	virtual void doPostDisable(bool sleeping = true) ;
public: 
	bool invokeStep(BwStepper& stepper) {
		doStep(stepper) ;
		return onStep(stepper) ;
	}
	bool invokePostStep(BwStepper& stepper) {
		doPostStep(stepper) ;
		return onPostStep(stepper) ;
	}
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onStep(BwStepper& stepper) ;
	virtual void doPostStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	//
	virtual void schedule() ;
	virtual void sleep() ;
	virtual void wake() ;
	virtual bool die() { setState(DEAD) ; return false ; }
	enum actorState_t {
		DISABLED = 0,
		WAKING, //intermediate state
		ACTING, //Enabled state 1
		IDLE, //intermediate state, still ACTING!
		WAITING, //intermediate state, still ACTING!
		DOZING, //intermediate state, still ACTING!
		SLEEPING, //Enabled state 2
		DEAD
	} ;
	typedef actorState_t actorState ;

	void setState(actorState state) { m_state = state ; }
	actorState getState() { return m_state ; }

	bool isWaking() { return m_state == WAKING ; }
	bool isActive() { 
		return m_state == ACTING || 
			m_state == IDLE || 
			m_state == WAITING || 
			m_state == DOZING ; 
	}
	bool isIdle() { return m_state == IDLE ; }
	bool isWaiting() { return m_state == WAITING ; }
	bool isDozing() { return m_state == DOZING ; }
	bool isSleeping() { return m_state == SLEEPING ; }
	bool isAlive() { return m_state != DEAD ; }
	bool isDead() { return m_state == DEAD ; }

	virtual void setIsAutoSleeper(bool val) ;
	bool isAutoSleeper() { return m_isAutoSleeper ; }
	bool _doze() ;
	virtual bool doze() ;
	void rest() { setState(IDLE) ; }
	void unrest() { if(isIdle()) setState(ACTING) ; }
	void wait() { setState(WAITING) ; }
	void unwait() { if(isWaiting()) setState(ACTING) ; }
	//
	void setIsMigrating(bool val) { m_isMigrating = val ; }
	bool isMigrating() { return m_isMigrating ; }
	virtual void migrate() {}
	//
	virtual void createBrain() {}
	BwBrain* getBrain() { return p_brain ; }
	BwBrain *p_brain ;
	//
	BwStage* getStage() { return p_stage ; }
	/*Some Actors are manually stepped ... brain, mech ...*/
	void setIsStageDriven(bool val) { m_isStageDriven = val ; }
	bool isStageDriven() { return m_isStageDriven ; }
	void setIsStageDriver(bool val) { m_isStageDriver = val ; }
	bool isStageDriver() { return m_isStageDriver ; }
	//Accessors
	BwActor& owner() { return *static_cast<BwActor*>(p_owner) ; }
	//Data Members
	BwStage *p_stage ;
	//Flags
	bool m_isStageDriven ;
	bool m_isStageDriver ;
	bool m_isAutoSleeper ;
	bool m_isMigrating ;

	actorState m_state ;
};

#endif //_BwActor_H
