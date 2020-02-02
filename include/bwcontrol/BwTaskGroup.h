#ifndef _BwTaskGroup_H
#define _BwTaskGroup_H

#include "BwTask.h"

class BwTaskGroup ;

typedef std::vector<BwTaskGroup*> BwTaskGroups ;
typedef BwTaskGroups::iterator BwTaskGroupIter ;

class BwTaskGroup {
public:
	BwTaskGroup() {
		m_isMutex = true ;
	}
	void addTask(BwTask *pTask) ;
	void removeTask(BwTask *pTask) ;
	BwTask* findTask(const bwString& name) ;
	BwTask* findMrp() ; //mrp = most relevant task
	//
	void subsume(BwTask *pTask) ;
	//
	void addTaskGroup(BwTaskGroup *pTaskGroup) ;
	void removeTaskGroup(BwTaskGroup *pTaskGroup) ;
	//
	void setIsMutex(bool val) { m_isMutex = val ; }
	bool isMutex() { return m_isMutex ; }
	//Data Members
	BwTaskMap m_tasks ;
	BwTaskGroups m_taskGroups ;

	bool m_isMutex ;
} ;

#endif //_BwTaskGroup_H
