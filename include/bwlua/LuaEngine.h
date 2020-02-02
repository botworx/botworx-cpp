/*Botworx Lua - A support framework for Lua.
Copyright (C) 2004  Kurtis Fields. See BotworxLua_License.txt for details.
*/
#ifndef _LuaEngine_H
#define _LuaEngine_H

struct lua_State ;
struct lua_Debug ;

class LuaSession {
public:
	LuaSession() {}
	/*Data Members*/
};

class LuaEngine {
public:
	LuaEngine() ;
	lua_State* getState() { return p_state ; }
	//
	void setSession(LuaSession* pSession) { p_session = pSession ; }
	LuaSession* getSession() { return p_session ; }
	//
	bool dostring(const char* str) ;
	/*bool dostring(const char* str) ;
	void manual_input() ;
	int load_string() ;
	int incomplete (int status) ;
	int lcall(int narg, int clear) ;
	static void lstop (lua_State *l, lua_Debug *ar) ;
	static void laction (int i) ;
	int report (int status) ;
	void l_message (const char *pname, const char *msg) ;
	const char *get_prompt (int firstline) ;*/
	//Singleton support
	static LuaEngine *s_singleton ;
	static LuaEngine& singleton() ;
	/*Data Members*/
	lua_State* p_state ;
	std::string m_progname ;
	//
	LuaSession* p_session ;
};

#endif //_LuaEngine_H
