/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbSector.h>
#include <buggybots/BbMap.h>

#include <bwvr/VrLayout.h>
#include <bwvr/VrVu.h>
#include <bwvr/VrDynamicLines.h>
#include <bwvr/config/ogre.h>
#include <bwvr/config/options_debug.h>

using namespace Ogre ;

class BbSectorVu : public VrVu {
public:
	BbSectorVu(VrGroup* pGroup) : VrVu(pGroup) {
	}
	virtual void createAssets() ;
	void drawRectangle(const bwPoint3& pos, const bwSize3& size, int crossHatch = 0) ;
	/*Data Members*/
public:
	VrDynamicLines* p_lines ;
};

void BbSectorVu::createAssets() {
	createSceneNode() ;
    p_lines = new VrDynamicLines(RenderOperation::OT_LINE_LIST);
	BbSector* pSector = dynamic_cast<BbSector*>(p_model) ;
	bwPoint3 sectorPos = pSector->getPos() ;
	bwSize3 sectorSize = pSector->getSize() ;
	drawRectangle(sectorPos, sectorSize) ;

	BbMapPortalList& portals = pSector->getMapSector()->portals() ;
	for(BbMapPortalListIter iter = portals.begin() ; iter != portals.end() ; ++iter) {
		BbMapPortal& portal = **iter ;
		bwPoint3 pos = portal.getPos() ;
		bwSize3 size = portal.getSize() ;
		if(portal.getNeighbor() == NULL)
			drawRectangle(pos, size, 2) ;
		else
			drawRectangle(pos, size, 1) ;
	}
	
    p_sceneNode->attachObject(p_lines);
}
void BbSectorVu::drawRectangle(const bwPoint3& pos, const bwSize3& size, int crossHatch) {
	bwPoint3 relPos = pos - p_model->getPos() ;
	Real x, y, z ;
	Real a, b, c ;
	Real d, e, f ;
	Real g, h, i ;
	Real j, k, l ;
	//North Line
	a = x = relPos[0] - (size[0]/2) ;
	b = y = 0 ;
	c = z = relPos[2] - (size[2]/2) ;
	p_lines->addPoint(x, y, z) ;
	//
	d = x = relPos[0] + (size[0]/2) ;
	e = y = 0 ;
	f = z = relPos[2] - (size[2]/2) ;
	p_lines->addPoint(x, y, z) ;
	//East Line
	p_lines->addPoint(x, y, z) ;
	//
	g = x = relPos[0] + (size[0]/2) ;
	h = y = 0 ;
	i = z = relPos[2] + (size[2]/2) ;
	p_lines->addPoint(x, y, z) ;
	//South Line
	p_lines->addPoint(x, y, z) ;
	//
	j = x = relPos[0] - (size[0]/2) ;
	k = y = 0 ;
	l = z = relPos[2] + (size[2]/2) ;
	p_lines->addPoint(x, y, z) ;
	//West Line
	p_lines->addPoint(x, y, z) ;
	p_lines->addPoint(a, b, c) ;

	//cross hatch
	switch(crossHatch) {
		case 2 :
			p_lines->addPoint(d, e, f) ;
			p_lines->addPoint(j, k, l) ;
		case 1 :
			p_lines->addPoint(a, b, c) ;
			p_lines->addPoint(g, h, i) ;
	}
    p_lines->update();
}
///////////////////
BbSector::BbSector(VrGroup *pGroup) : VrPlace(pGroup) {
	m_isViewable = true ;
	vuInfo().setIsAutoScaler(false) ;
	//VrRelLay newLay ;
	//setLay(newLay) ;
	setLay(VrRelLay()) ;
}
void BbSector::createVu() {
	p_vu = new BbSectorVu(this) ;
	p_vu->create() ;
}
//////////
void BbSector::onModelAddition(VrModel *pModel) {
	VrGroup::onModelAddition(pModel) ;
#if VR_OPTION_DEBUG_MIGRATE
	if(getMain() != NULL) {
		VrVu *pFloorVu = getMain()->getVu() ;
		if(pFloorVu != NULL)
			if(m_stage.getActorCount() > 1)
				pFloorVu->setShowBoundingBox(true) ;
	}
#endif
}
void BbSector::onModelRemoval(VrModel *pModel) {
	VrGroup::onModelRemoval(pModel) ;
#if VR_OPTION_DEBUG_MIGRATE
	if(getMain() != NULL) {
		VrVu *pFloorVu = getMain()->getVu() ;
		if(pFloorVu != NULL)
			if(m_stage.getActorCount() == 1)
				pFloorVu->setShowBoundingBox(false) ;
	}
#endif
}