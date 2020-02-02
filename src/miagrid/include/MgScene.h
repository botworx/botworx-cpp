/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MgScene_H
#define _MgScene_H

class wxGrid ;

class MgScene {
public:
	MgScene() {}
	static MgScene& singleton() { return *g_singleton ; }
	wxGrid* get_grid() { return p_grid ; }
	//Data Members
	wxGrid* p_grid ;
	//
	static MgScene* g_singleton ;
} ;

#endif //_MgScene_H
