#ifndef _VrScenarioLoader_H
#define _VrScenarioLoader_H

#include <bwcore/BwActor.h>

namespace boost {
	class thread ;
}

class VrApplet ;
class VrScenarioFactory ;
class VrScenario ;

class VrScenarioLoader : public BwActor {
public:
	enum loadingStyle {
		LOAD_DEFAULT = 0,
		LOAD_ASYNC = 1,
		LOAD_ENABLED = 2
	} ;
	VrScenarioLoader(VrApplet* pApplet, VrScenarioFactory* pFactory, loadingStyle style = LOAD_DEFAULT) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	virtual void load() ;
	virtual void onFinish() ;
	//
	struct thread_fn
	{
		thread_fn(VrScenarioLoader *pLoader) : p_loader(pLoader) { }
		void operator()() {
			p_loader->load() ;
		}

		VrScenarioLoader *p_loader ;
	};
	//Data Members
	VrApplet* p_applet ;
	VrScenarioFactory* p_factory ;
	VrScenario* p_scenario ;
	boost::thread *p_thread ;
	//bool m_isAsync ;
	loadingStyle m_style ;
	bool m_isFinished ;
} ;

#endif //_VrScenarioLoader_H