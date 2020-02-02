/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaAgent_H
#define _MiaAgent_H

#include "MiaCore.h"
#include "MiaExplorer.h"
#include "MiaDomain.h"
#include "MiaFrame.h"

#include <bwscheduling/BwTimer.h>

#include <boost/random.hpp>

class MiaAgent ;
DECLARE_KITINFO(MiaAgent) ;

//kit forward defs
class BwCmd ;
class MiaFact ;
class MiaDomain ;
class MiaProblem ;

class MiaAgent : public MiaCore {
public:
	MiaAgent(AiKit* pSuperKit, AiKitInfo *pKitInfo) ;
	MiaAgent() : MiaCore(NULL, KITINFOREF(MiaAgent)) {}
	~MiaAgent() ;
	virtual void doPostDisable(bool sleeping = true) ;
	static AiKit* produce(AiKit* pSuperKit, AiKitInfo *pKitInfo) {
		return new MiaAgent(pSuperKit, pKitInfo) ;
	}
	static AiKit* produce() {
		return new MiaAgent(NULL, KITINFOREF(MiaAgent)) ;
	}
	static MiaAgent* produceAgent() { return static_cast<MiaAgent*>(produce()) ; }
	virtual void createMailCenter() ;
	virtual void createPrinter() ;
	virtual void createLogger() ;
	virtual void changeIoMode() ;
	//
	void createRootDomain() ;
	MiaDomain& getRootDomain() { return *p_rootDomain.get() ; }
	//
	void createRootFrame() ;
	MiaFrame& getRootFrame() { return *p_rootFrame.get() ; }
	//
	MiaProblem* createProblem(AiSymbol* pName) ;
	void addProblem(MiaProblem* pProblem) ;
	void destroyProblems() ;
	//
	virtual void createCommander() ;
	//Run Status
	enum stepStatus_E {
		STEP_NONE = 0,
		STEP_SOME,
		STEP_ALL
	} ;
	typedef stepStatus_E stepStatus ;
	bool isSteppingNone() { return m_stepStatus == STEP_NONE ; }
	bool isSteppingSome() { return m_stepStatus == STEP_SOME ; }
	bool isSteppingAll() { return m_stepStatus == STEP_ALL ; }

	enum runStatus_E {
		RUN_STOPPED = 0,
		RUN_PAUSED,
		RUN_RUNNING
	} ;
	typedef runStatus_E runStatus ;
	bool isStopped() { return m_runStatus == RUN_STOPPED ; }
	bool isPaused() { return m_runStatus == RUN_PAUSED ; }
	bool isRunning() { return m_runStatus == RUN_RUNNING ; }

	//Commands
	void printPrompt() ;
	void printNews() ;
	void load(const bwString& fileName) ;
	void reload() ;
	void stop() ;
	void pause() ;
	void onInterrupt() ;
	void run() ;
	void runFor(int count) ;
	void preRun() ;
	void postRun() ;
	bool preStep() ;
	void postStep() ;
	//
	void doCommand(const BwCmd& cmd) ;
	void close() ;
	bool onClose() ;
	//Notices & Events
	//Data Members
	MiaDomainPtr p_rootDomain ;
	MiaFramePtr p_rootFrame ;
	//
	bwString m_fileName ; //root filename ...
	stepStatus m_stepStatus ;
	runStatus m_runStatus ;
	int m_steps ; //steps requested
	long m_stepCounter ;
	BwLoTimer m_stepTimer ;
	BwLoTimer m_runTimer ;
	//
	void pushExplorer(MiaExplorer* pExplorer) { m_explorers.push(pExplorer) ; }
	MiaExplorer* getExplorer() { return m_explorers.top() ; }
	MiaExplorer& explorer() { return *getExplorer() ; }
	void popExplorer() { m_explorers.pop() ; }
	std::stack<MiaExplorer*> m_explorers ;
	//
	//Randomization
	boost::mt19937 m_randomizer ;
	int rollInt(int first, int last) {
		boost::uniform_int<> distribution(first, last) ;
		boost::variate_generator<boost::mt19937&, boost::uniform_int<> >
           roll(m_randomizer , distribution);             // glues randomness with mapping
		int x = roll() ;                      // simulate rolling a die
		return x ;
	}
	double rollReal(double first, double last) {
		boost::uniform_real<> distribution(first, last) ;
		boost::variate_generator<boost::mt19937&, boost::uniform_real<> >
           roll(m_randomizer , distribution);             // glues randomness with mapping
		double x = roll() ;                      // simulate rolling a die
		return x ;
	}
} ;
#define asMiaAgent(X) (static_cast<MiaAgent*>(X)))

#endif //_MiaAgent_H
