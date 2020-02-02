/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/crawler/Crawler.h>
#include <buggybots/bots/crawler/CrawlerFactory.h>
#include <buggybots/bots/crawler/CrawlerBrain.h>
#include <buggybots/bots/crawler/CrawlerChassis.h>
#include <buggybots/bots/crawler/CrawlerLeg.h>
#include <buggybots/bots/crawler/CrawlerLegSeg.h>

#include <bwvr/VrMotor.h>
#include <bwvr/VrSteering.h>
#include <bwvr/VrJoint.h>
#include <bwvr/VrBody.h>
////////////////////////////////////////////////////
namespace Crawler {

//////////////////////////
Crawler::Crawler(VrGroup *pGroup) : VrDynamicAssembly(pGroup) {
	//TODO:why is this necessary? Groups should size to fit members!
	setIsEntity(true) ;
	setIsAutoSleeper(false) ;
	setSize(bwSize3(3, 3, 3)) ;
	setMaxSize(bwSize3(6, 6, 6)) ;
}
void Crawler::doCreate(const BwPartInfo& info) {
	VrDynamicAssembly::doCreate(info) ;

	p_main = new CrawlerChassis(this) ;
	p_main->create() ;

	p_steering = new VrSteering(this) ;
	p_steering->create() ;

	CrawlerLegFactory& legFactory = CrawlerLegFactory::singleton::get() ;

	CrawlerLeg *pLeg = NULL ;

	for(int i = 0 ; i < 4; ++i) {
		p_leg[i] = static_cast<CrawlerLeg*>(legFactory.rent(i, this)) ;
	}
}
bool Crawler::onCreate(const BwPartInfo& info) {
	return VrDynamicAssembly::onCreate(info) ;
}
void Crawler::createBrain() {
	p_brain = new CrawlerBrain(this) ;
	p_brain->create() ;
}
Crawler::~Crawler()
{
}
void Crawler::setPos(const bwPoint3& p) {
	VrDynamicAssembly::setPos(p) ;
	p_main->setPos(factory().m_chassisPos + getPos()) ;
}
void Crawler::flip(bwReal fx, bwReal fy, bwReal fz, bwReal px, bwReal py, bwReal pz) {
	p_main->getBody()->addRelForceAtRelPos(bwVector3(fx,fy,fz), bwPoint3(px,py,pz)) ;
}
void Crawler::rollLeft(bwReal degree) {
	bwReal force = p_main->getBody()->bodyInfo().getMass() * -5000 ;
	flip(0, 1, 0, force, 0, 0) ;
}
void Crawler::rollRight(bwReal degree) {
	bwReal force = p_main->getBody()->bodyInfo().getMass() * 5000 ;
	flip(0, 1 , 0, force, 0, 0) ;
}
void Crawler::fireMissile() {
}
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////