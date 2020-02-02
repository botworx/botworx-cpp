/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwRunner_H
#define _BwRunner_H

#include <bwcore/BwStage.h>
#include <bwscheduling/BwTimer.h>

namespace boost {
	class thread ;
}
typedef BwLoTimer BwStepTimer ;
typedef BwHiTimer BwStepTimer ;

class BwApplet ;

class BwRunner : public BwActor {
public:
	BwRunner(BwRunner* pOwner);
	virtual ~BwRunner();
public:
	//virtual void signalStep() ;
	//void waitTillStepEnd() { m_stepEnd.wait(m_stepEndLock) ; }
	virtual void doStep() ;
	virtual void doPostStep() ;
	virtual void go() ;
	virtual void goSimple() ;
	virtual void goSync() ;
	virtual void goAsync() ;
	virtual void run() ;
	virtual void stop() ;
	virtual void onGo() {}
	virtual void onStop() {}
	void finish() {	stop() ; m_isFinished = true ; }
	virtual void doStep(BwStepper& stepper) ;
	virtual void stepSimple() ;
	virtual void stepSync() ;
	virtual void stepAsync() ;
	bool isRunning() { return m_isRunning ; }
	bool isFinished() {	return m_isFinished ; }
	void setIsRunner(bool val) { m_isRunner = val ; }
	BwApplet* getApplet() { return p_applet ; }

protected:
	struct thread_fn
	{
		thread_fn(BwRunner *pRunner) : p_runner(pRunner) { }
		void operator()() {
			p_runner->run() ;
		}

		BwRunner *p_runner ;
	};

protected:
	BwApplet *p_applet ;

	BwDefaultStage m_stage ;

	bool m_isRunner ;
	bool m_isFinished ;
	bool m_isRunning ;
	bool m_isFirstGo ;

	/*boost::try_mutex m_stepMutex ;
	boost::try_mutex::scoped_lock m_stepBeginLock, m_stepEndLock ;
	boost::condition m_stepBegin, m_stepEnd ;*/
	boost::thread *p_thread ;

	BwStepTimer m_stepTimer ;
	float m_time ;
	float m_elapsedTime ;
public:
	enum runnerType {
		RUNNER_SIMPLE,
		RUNNER_SYNC,
		RUNNER_ASYNC
	} ;
	int m_runnerType ;
	void setRunnerType(int type) { m_runnerType = type ; }
	void setIsCoRunner(bool val) { m_isCoRunner = val ; }
	/*Data Members*/
	bool m_isCoRunner ;
	//TODO:newstuff
	BwStepper m_stepper ;
};

#endif //_BwRunner_H

