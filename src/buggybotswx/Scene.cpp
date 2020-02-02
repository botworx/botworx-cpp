/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include "Scene.h"
#include "User.h"

#include "Applet.h"
#include <bwvr/VrScenario.h>
#include <bwvr/VrPhysics.h>

#include <bwvr/config/ogre.h>

Scene::Scene(VrScenario *pScenario) : BbScene(pScenario){
}
Scene::~Scene(){
}
void Scene::doCreate(const BwPartInfo& info) {
	//fixme:this is a hack
	p_frame = ((Applet&)VrApplet::singleton::get()).getFrame() ;
}
/*void Scene::createUser() {
	p_user = new User(this, p_frame) ;
	p_user->create() ;
}*/