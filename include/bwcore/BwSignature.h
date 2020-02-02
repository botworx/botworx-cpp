/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwTypes_H
#define _BwTypes_H

template<typename T_Class>
struct BwSigT {
	typedef BwPartContainer		T_Container ;
	typedef BwPart				T_Owner ;
	typedef BwPart				T_Part ;
	//
	static bwString name() { return "Part" ; }
} ;

#endif //_BwTypes_H
