/*Botworx Lua - A support framework for Lua.
Copyright (C) 2004  Kurtis Fields. See BotworxLua_License.txt for details.
*/
#ifndef _MgLuaEngine_H
#define _MgLuaEngine_H

#include <bwlua/LuaEngine.h>

class MgBrain ;

class MgLuaSession : public LuaSession {
public:
	MgLuaSession(MgBrain* pBrain) : p_brain(pBrain) {}
	//Data Members
	MgBrain* p_brain ;
};

class MgLuaEngine : public LuaEngine {
public:
	MgLuaEngine() ;
	MgLuaSession& session() { return *static_cast<MgLuaSession*>(p_session) ; }
	//Singleton support
	static MgLuaEngine *s_singleton ;
	static MgLuaEngine& singleton() ;
};

#endif //_MgLuaEngine_H