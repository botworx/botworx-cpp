/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/BbWorld.h>

#include <bwvr/VrSharedVu.h>

BbWorld::BbWorld(BwActor *pParent) : VrWorld(pParent){
	m_isViewable = true ; //needed to create batched geometry
	setIsAutoSleeper(false) ; //very important!
	//VrAbsLay lay ;
	//setLay(lay) ;
	setLay(VrAbsLay()) ;
}
BbWorld::~BbWorld(){
}
void BbWorld::createVu(void) {
	p_vu = new VrSharedVu(this) ;
	p_vu->create() ;
}
void BbWorld::createNodeKit() {
	bwSize3 size = getSize() ;
	p_nodeKit = new VrQuadNodeKit(this, bwPoint3(0,0,0), size, 7) ;
	p_nodeKit->create() ;
}
void BbWorld::createNode() {
	VrWorld::createNode() ;
	getNodeKit()->setRoot(p_node) ;
}