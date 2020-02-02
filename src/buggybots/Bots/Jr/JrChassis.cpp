/*JrBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See JrBots_License.txt for details.
*/
#include "stdafx.h"

#include <buggybots/bots/jr/Jr.h>
#include <buggybots/bots/jr/JrChassis.h>
#include <buggybots/bots/jr/JrBody.h>

namespace Jr {

//JrChassis::JrChassis(VrGroup *pGroup, Jr *pJr) : VrFixedAssembly(pGroup) {
JrChassis::JrChassis(Jr *pJr) : VrFixedAssembly(pJr) {
	p_jr = pJr ;
	p_jrBody = NULL ;
}
void JrChassis::doCreate(const BwPartInfo& info) {
	VrFixedAssembly::doCreate(info) ;
	p_jrBody = new JrBody(this, p_jr) ;
	p_jrBody->create() ;
	setMain(p_jrBody) ;
}

}//end namespace Jr