/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MgPlace_H
#define _MgPlace_H

#include "bwkernel/BwPart.h"

class MgPlace : public BwPart {
public:
	MgPlace(MgScenario *pWorld, mgPos pos) 
		: BwPart(pWorld), p_world(pWorld), p_entity(NULL), m_isNoMansLand(false), m_pos(pos) {}
	void setEntity(MgEntity* pEntity) { p_entity = pEntity ; }
	MgEntity* getEntity() { return p_entity ; }
	bool hasVacancy() { return p_entity == NULL && !isNoMansLand() ; }
	void set_isNoMansLand(bool val) { m_isNoMansLand = val ; }
	bool isNoMansLand() { return m_isNoMansLand ; }
	void setPos(const mgPos& pos) ;
	mgPos getPos() { return m_pos ; }
	//Data Members
	MgScenario* p_world ;
	MgEntity* p_entity ;
	mgPos m_pos ;
	bool m_isNoMansLand ;
} ;

#endif //_MgPlace_H