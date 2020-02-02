/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwcontrol/BwTaskGroup.h>

void BwTaskGroup::subsume(BwTask *pTask) {
	for(BwTaskMapIter iter = m_tasks.begin() ; iter != m_tasks.end() ; ++iter) {
		BwTask* pSubsumed = iter->second ;
		if(pSubsumed != nullptr && pSubsumed != pTask && pSubsumed->isActive()) {
			pSubsumed->doze() ;
		}
	}
}
//
void BwTaskGroup::addTask(BwTask *pTask) {
	m_tasks[pTask->getName()] = pTask ;
}
BwTask* BwTaskGroup::findTask(const bwString& name) {
	//return m_tasks[name] ;
	BwTask* pTask = m_tasks[name] ;
	if(pTask != nullptr)
		return pTask ;
	//else
	for(BwTaskGroupIter iter = m_taskGroups.begin() ; iter != m_taskGroups.end() ; ++iter) {
		BwTaskGroup& taskGroup = **iter ;
		pTask = taskGroup.findTask(name) ;
		if(pTask != nullptr)
			break ;
	}
	return pTask ;
}
BwTask* BwTaskGroup::findMrp() {
	for(BwTaskMapIter iter = m_tasks.begin() ; iter != m_tasks.end() ; ++iter) {
		BwTask* pTask = iter->second ;
		if(pTask != nullptr) {
			pTask->weigh() ;
		}
	}
	BwTask* pMrp = nullptr ;
	int maxWeight = 0 ;
	for(BwTaskMapIter iter = m_tasks.begin() ; iter != m_tasks.end() ; ++iter) {
		BwTask* pTask = iter->second ;
		if(pTask != nullptr && pTask->getWeight() > maxWeight) {
			pMrp = pTask ;
			maxWeight = pTask->getWeight() ;
		}
	}
	return pMrp ;
}
void BwTaskGroup::addTaskGroup(BwTaskGroup *pTaskGroup) {
	m_taskGroups.push_back(pTaskGroup) ;
}
void BwTaskGroup::removeTask(BwTask *pTask) {
	m_tasks.erase(pTask->getName()) ;
}
void BwTaskGroup::removeTaskGroup(BwTaskGroup *pTaskGroup) {
	for(BwTaskGroupIter iter = m_taskGroups.begin() ; iter != m_taskGroups.end() ; ++iter) {
		if(*iter == pTaskGroup) {
			m_taskGroups.erase(iter) ;
			break ;
		}
	}
}