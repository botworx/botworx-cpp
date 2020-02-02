#include "stdafx.h"

#include <bwvr/VrScenario.h>
#include <bwvr/VrWorld.h>
#include <bwvr/VrPhysics.h>
#include <bwvr/VrCollider.h>
#include <bwvr/VrNodeKit.h>

VrWorld::VrWorld(BwActor *pParent) : VrPlace(NULL) {
	m_isViewable = true ; //needed to create batched geometry
	m_isAutoSleeper = false ; //very important!
	m_isEntity = true ;
	p_owner = pParent ;
	// VrPlaceLay placeLay ;
	// setLay(placeLay) ;
	setLay(VrPlaceLay()) ;
 }
bool VrWorld::onCreate(const BwPartInfo& info) {
	return VrPlace::onCreate(info) ;
}
VrWorld::~VrWorld() {
}