/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include "MgScenario.h"
#include "MgPlace.h"

MgScenario::MgScenario() : BwActor(NULL) {
	p_stage = &m_stage ; 	
	m_stage.setOwner(this) ; 
	m_stage.create() ;

	p_noMansLand = new MgPlace(this,mgPos(-1,-1)) ;
	p_noMansLand->set_isNoMansLand(true) ;
}
void MgScenario::doCreate(const BwPartInfo& info) {
	BwActor::doCreate(info) ;

	char buffer1[16] ;
	char buffer2[16] ;
	MgPlace* pPlace = NULL ;
	m_grid.reserve(m_rowCount) ;
	for(int i = 0 ; i < m_rowCount ; i++) {
		m_grid.push_back(MgRow()) ;
		m_grid[i].reserve(m_colCount) ;
		for(int j = 0 ; j < m_colCount ; j++) {
			pPlace = new MgPlace(this, mgPos(i,j)) ;
			bwString name = "Place_" ;
			itoa(i, buffer1, 10) ;
			name += buffer1 ; name += "_" ;
			itoa(j, buffer2, 10) ;
			name += buffer2 ;
			pPlace->setName(name) ;
			m_grid[i].push_back(pPlace) ;
		}
	}
}
void MgScenario::add_entity(MgEntity *pEntity) {
	m_stage.addActor(pEntity) ;
}
void MgScenario::remove_entity(MgEntity *pEntity) {
	m_stage.removeActor(pEntity) ;
}
MgPlace* MgScenario::getPlaceAt(const mgPos& pos) {
	if( (pos.x < 0) || (pos.x >= m_colCount) || (pos.y < 0) || (pos.y >= m_rowCount))
		return p_noMansLand ;
	//else
	return m_grid[pos.x][pos.y] ; 
}
void MgScenario::set_placeAt(MgPlace *pPlace, const mgPos& pos) { 
	m_grid[pos.x][pos.y] = pPlace ; 
}
