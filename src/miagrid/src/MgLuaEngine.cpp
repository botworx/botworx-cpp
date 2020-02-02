/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"


#include "MgLuaEngine.h"

//f6:fixme:undef max at higher level?
#undef max
#include <luabind/luabind.hpp>

#include "MgBrain.h"

void moveTo(int x, int y) {
	MgLuaSession& session = MgLuaEngine::singleton().session() ;
	MgBrain *pBrain = session.p_brain ;
	pBrain->moveTo(x, y) ;
}
MgLuaEngine::MgLuaEngine() {
	using namespace luabind;
	module(getState())
    [
        def("moveTo", &moveTo)
    ];
}
//Singleton support
MgLuaEngine* MgLuaEngine::s_singleton = NULL;
MgLuaEngine& MgLuaEngine::singleton() {
    if(s_singleton == NULL) {
		s_singleton = new MgLuaEngine() ;
    }
	return *s_singleton ;
}