#ifndef _MiaCommander_H
#define _MiaCommander_H

#include <bwcore/BwPart.h>
#include <bwmia/MiaLuaEngine.h>

class MiaMind ;
class MiaSpace ;
class MiaAgent ;
class BwCmd ;

class MiaCommander : public BwPart {
public:
	MiaCommander(MiaAgent* pAgent) ;
	~MiaCommander() ;
	MiaAgent* getAgent() { return p_agent ; }
	MiaAgent& agent() { return *p_agent ; }
	void dispatch(const BwCmd& cmd) ;
	void setMindSelection(MiaMind* pMind) { p_mindSelection = pMind ; }
	MiaMind* getMindSelection() { return p_mindSelection ; }
	//Data Members
	MiaAgent* p_agent ;
	MiaMind* p_mindSelection ; //TODO:this looks dangerous...
	//Classes
	class CmdSession : public LuaSession {
	public:
		CmdSession(MiaCommander* pCommander) : p_commander(pCommander) {}
		//Data Members
		MiaCommander* p_commander ;
	};
	CmdSession* p_cmdSession ;
	class CmdEngine : public LuaEngine {
	public:
		CmdEngine() ;
		CmdSession& session() { return *static_cast<CmdSession*>(p_session) ; }
		//Singleton support
		typedef BwAutoSingletonT<CmdEngine> singleton ;
		singleton m_singleton ;
	};
} ;

#endif //_MiaCommander_H