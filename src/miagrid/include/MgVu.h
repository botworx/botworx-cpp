/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MgVu_H
#define _MgVu_H

#include <bwkernel/BwActor.h>

class MgEntity ;
class wxGridCellStringRenderer ;

class MgVu : public BwActor {
public:
	MgVu(MgEntity *pEntity) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void create_renderer() ;
	//virtual bool doPostStep(BwStepper& stepper) ;
	virtual void doPostStep(BwStepper& stepper) ;
	virtual void updateScene() ;
	//Data Members
	MgEntity *p_entity ;
	wxGridCellStringRenderer *p_renderer ;
	mgPos m_savedPos ;
	wxGridCellRenderer *p_savedRenderer ;
} ;

#endif //_MgVu_H
