/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MgEntity_H
#define _MgEntity_H

#include <bwkernel/BwActor.h>

class MgScenario ;
class MgVu ;

class MgEntity : public BwActor {
public:
	MgEntity(MgScenario *pWorld) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void createVu() ;
	//virtual bool doPostStep(BwStepper& stepper) ;
	virtual void doPostStep(BwStepper& stepper) ;
	void setPos(const mgPos& pos) ;
	mgPos getPos() { return m_pos ; }
	//
	bool hasMoved() { return m_hasMoved ; }
	//Data Members
	MgScenario* p_world ;
	MgVu* p_vu ;
	mgPos m_pos ;
	bool m_hasMoved ;
} ;

#endif //_MgEntity_H
