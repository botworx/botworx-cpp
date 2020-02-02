/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrScenarioLoader.h>
#include <bwvr/VrScenarioFactory.h>
#include <bwvr/VrScenario.h>
#include <bwvr/VrApplet.h>
#include <bwvr/VrScenario.h>

#include <bwcore/BwStage.h>

VrScenarioLoader::VrScenarioLoader(VrApplet* pApplet, VrScenarioFactory* pFactory, loadingStyle style) : BwActor(pApplet) {
	p_applet = pApplet ;
	m_style = style ;
	p_factory = pFactory ;
	m_isFinished = false ;
}
void VrScenarioLoader::doCreate(const BwPartInfo& info) {
	BwPart::doCreate(info) ;
	//
	//p_applet->clearScene() ;
	//
	if(getFlag(m_style, LOAD_ASYNC)) {
		p_applet->getStage()->addActor(this) ;
		p_thread = 	new boost::thread(thread_fn(this)) ;
		return ;
	}
	//else
	load() ;
	onFinish() ;
}
bool VrScenarioLoader::onPostStep(BwStepper& stepper) {
	if(m_isFinished) {
		onFinish() ;
		return die() ;
	}
	//else
	return BwActor::onPostStep(stepper) ;
}
void VrScenarioLoader::load() {
	p_scenario = p_factory->produce(p_applet) ;
	//
	if(getFlag(m_style, LOAD_ASYNC) || getFlag(m_style, LOAD_ENABLED)) {
		p_scenario->config() ;
	}
	m_isFinished = true ;
}
void VrScenarioLoader::onFinish() {
	p_scenario->onLoad() ;
	//
	if(getFlag(m_style, LOAD_ASYNC) || getFlag(m_style, LOAD_ENABLED))
		p_scenario->enable() ;
	else
		p_applet->getStage()->addActor(p_scenario) ;

	//newstuff
	p_scenario->bind() ;
}