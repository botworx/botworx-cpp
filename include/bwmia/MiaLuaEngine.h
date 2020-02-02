/*Botworx Lua - A support framework for Lua.
Copyright (C) 2004  Kurtis Fields. See BotworxLua_License.txt for details.
*/
#ifndef _MiaLuaEngine_H
#define _MiaLuaEngine_H

#include <bwlua/LuaEngine.h>

class MiaAgent ;

class MiaLuaSession : public LuaSession {
public:
	MiaLuaSession(MiaAgent* pAgent) : p_agent(pAgent) {}
	//Data Members
	MiaAgent* p_agent ;
};

class MiaLuaEngine : public LuaEngine {
public:
	MiaLuaEngine() ;
	MiaLuaSession& session() { return *static_cast<MiaLuaSession*>(p_session) ; }
	//Singleton support
	/*static MiaLuaEngine *s_singleton ;
	static MiaLuaEngine& singleton() ;*/
	typedef BwAutoSingletonT<MiaLuaEngine> singleton ;
	singleton m_singleton ;
};

#endif //_MiaLuaEngine_H