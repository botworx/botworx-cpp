#ifndef _BwPersonality_H
#define _BwPersonality_H

#include "BwTaskGroup.h"
#include "BwTaskFactory.h"

class BwPersonality : public BwTaskGroup {
public:
	BwPersonality(BwBrain* pBrain) ;
	virtual void useTask(BwTask* pTask) ;
	virtual BwTask* useTask(const bwString& name) ;
	BwTask* createTask(const bwString& name) ;
	virtual BwTask* produceTask(const bwString& name) { return nullptr ; }
	//
	BwTaskFactoryContainer* getFactories() { return & m_factories ; }
	void addFactory(BwTaskFactory *pFactory) ;
	void addFactoryAlias(const bwString& name, const bwString& alias) ;
	BwTaskFactory* findFactory(const bwString& name) ;
	//
	void setBrain(BwBrain* pBrain) { p_brain = pBrain ; }
	BwBrain* getBrain() { return p_brain ; }
	//Data Members
protected:
	BwBrain* p_brain ;
	BwTaskFactoryContainer m_factories ;
	BwTaskFactoryMap m_factoryMap ;
} ;

#endif //_BwPersonality_H