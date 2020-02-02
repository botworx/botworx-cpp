/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwScript_H
#define _BwScript_H

class BwScript ;
typedef std::list<BwScript*> BwScriptList ;
typedef BwScriptList::iterator BwScriptIter ;

class BwScript {
public:
	BwScript(const bwString& script) : m_script(script) {}
	void addScript(BwScript *pScript) { m_scripts.push_back(pScript) ; }
	BwScriptList& getScripts() { return m_scripts ; }
	//Data Members
	BwScriptList m_scripts ;
	bwString m_script ;
};

#endif //_BwScript_H