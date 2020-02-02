/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcontrol/BwPersonality.h>
#include <bwcontrol/BwBrain.h>

BwPersonality::BwPersonality(BwBrain* pBrain) {
	p_brain = pBrain ;
}
void BwPersonality::useTask(BwTask* pTask) {
	pTask->enable() ; //harmless if already active.

	BwTaskGroup* pTaskGroup = pTask->getTaskGroup() ;
	if(pTaskGroup->isMutex())
		pTaskGroup->subsume(pTask) ;
}
BwTask* BwPersonality::useTask(const bwString& name) {
	BwTask *pTask = findTask(name) ;

	if(pTask == nullptr)
		pTask = createTask(name) ;

	pTask->enable() ; //harmless if already active.

	BwTaskGroup* pTaskGroup = pTask->getTaskGroup() ;
	if(pTaskGroup->isMutex())
		pTaskGroup->subsume(pTask) ;

	return pTask ;
}
BwTask* BwPersonality::createTask(const bwString& name) {
	BwTask* pTask = produceTask(name) ;
	if(pTask == nullptr)
		return nullptr ;
	pTask->setName(name) ;
	pTask->setPersonality(this) ;
	//pTask->createEnabled() ;
	pTask->createAndConfig() ;
	addTask(pTask) ;
	return pTask ;
}
//
void BwPersonality::addFactory(BwTaskFactory *pFactory) {
	m_factories.push_back(pFactory) ;
	bwString name = pFactory->getName() ;
	BwTaskFactory *pFound = m_factoryMap[name] ;
	bwAssert(pFound == nullptr) ;
	m_factoryMap[name] = pFactory ;
}
void BwPersonality::addFactoryAlias(const bwString& name, const bwString& alias) {
	m_factoryMap[alias] = m_factoryMap[name] ;
}
BwTaskFactory* BwPersonality::findFactory(const bwString& name) {
	return m_factoryMap[name] ;
}
