/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MgScenario_H
#define _MgScenario_H

#include <bwkernel/BwStage.h>

//class MgEntity ;
#include "MgEntity.h"

class MgScenario ;
class MgPlace ;
typedef	std::vector<MgPlace*> MgRow ;
typedef	MgRow::iterator MgRowIter ;
typedef std::vector<MgRow> MgCol ;
typedef	MgCol::iterator MgColIter ;

class MgEntityStage ;
template<>
struct BwSigT<MgEntityStage> : BwSigT<BwStage> {
	typedef MgEntity	T_Part ;
} ;
typedef BwStageT<MgEntityStage> MgEntityStageBase ;

class MgEntityStage : public MgEntityStageBase {
public:
	MgEntityStage() : MgEntityStageBase() {}
};

class MgScenario : public BwActor {
public:
	MgScenario() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void add_entity(MgEntity *pEntity) ;
	virtual void remove_entity(MgEntity *pEntity) ;

	MgPlace* getPlaceAt(const mgPos& pos) ;
	void set_placeAt(MgPlace *pPlace, const mgPos& pos) ;
	void set_rowCount(int rowCount) { m_rowCount = rowCount ; }
	int getRowCount() { return m_rowCount ; }
	void set_colCount(int colCount) { m_colCount = colCount ; }
	int get_colCount() { return m_colCount ; }
	//Data Members
	MgEntityStage m_stage ;
	int m_rowCount ;
	int m_colCount ;
	MgCol m_grid ;
	MgPlace *p_noMansLand ;
} ;

#endif //_MgScenario_H
