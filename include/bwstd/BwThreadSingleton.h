/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwThreadSingleton_H
#define _BwThreadSingleton_H

#include "BwSingleton.h"
#include <bwcore/config/boost_thread.h>

//
//BwThreadSingletonT
//
template<typename T_Class>
class BwThreadSingletonT {
public:
	typedef boost::thread_specific_ptr<T_Class> pointer ;

	BwThreadSingletonT() {
		bwAssert( g_singleton == nullptr) ;
		g_singleton.reset( ((T_Class*)((bwByte*)this - offsetof(T_Class, m_singleton))) ) ;
	}
	~BwThreadSingletonT() {
		//g_singleton.reset(nullptr) ; //smart pointer will do this.
	}
	static T_Class& get() { return *g_singleton.get() ; }
	static T_Class* getPtr() { return g_singleton.get() ; }
	//
	static pointer g_singleton ;
} ;
//
//BwAutoThreadSingletonT
//
template<typename T_Class, typename T_Alloc = BwAutoSingletonAlloc<T_Class> >
class BwAutoThreadSingletonT {
public:
	typedef boost::thread_specific_ptr<T_Class> pointer ;

	BwAutoThreadSingletonT() {
	}
	~BwAutoThreadSingletonT() {
		//g_singleton.reset(nullptr) ; //smart pointer will do this.
	}
	static T_Class* getPtr() {
		if(g_singleton.get() == nullptr) {
			g_singleton.reset(T_Alloc::alloc()) ;
		}
		return g_singleton.get() ;
	}
	static T_Class& get() { return *getPtr() ; }
	//
	static pointer g_singleton ;
} ;

#endif //_BwThreadSingleton_H
