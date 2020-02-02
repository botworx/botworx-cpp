/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwSingleton_H
#define _BwSingleton_H

//
//BwSingletonT
//
template<typename T_Class>
class BwSingletonT {
public:
	typedef T_Class* pointer ;

	BwSingletonT() {
		bwAssert( g_singleton == nullptr) ;
		g_singleton = ((pointer)((bwByte*)this - offsetof(T_Class, m_singleton))) ;
	}
	~BwSingletonT() {
		g_singleton = nullptr ;
	}
	static T_Class& get() { return *g_singleton ; }
	static T_Class* getPtr() { return g_singleton ; }
	//
	static pointer g_singleton ;
} ;
//
//BwAutoSingletonAlloc
//
template<typename T_Class>
struct BwAutoSingletonAlloc {
	static T_Class* alloc() { return new T_Class() ; }
	//TODO:implement free ...
} ;
//
//BwAutoSingletonT
//
template<typename T_Class, typename T_Alloc = BwAutoSingletonAlloc<T_Class> >
class BwAutoSingletonT {
public:
	typedef T_Class* pointer ;

	BwAutoSingletonT() {
	}
	~BwAutoSingletonT() {
		g_singleton = nullptr ;
	}
	static T_Class* getPtr() {
		if(g_singleton == nullptr) {
			g_singleton = T_Alloc::alloc() ;
		}
		return g_singleton ;
	}
	static T_Class& get() { return *getPtr() ; }
	//
	static pointer g_singleton ;
} ;

#endif //_BwSingleton_H
