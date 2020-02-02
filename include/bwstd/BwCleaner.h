/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwCleaner_H
#define _BwCleaner_H

#include "BwSingleton.h"

#include <boost/function.hpp>
//
//BwCleaner
//
typedef boost::function0<void> BwCleanUp ;
typedef std::list<BwCleanUp> BwCleanUpList ;
typedef BwCleanUpList::iterator BwCleanUpListIter ;

class BwCleaner {
public:
	~BwCleaner() ;
	void addCleanup(const BwCleanUp& cleanup) ;
	BwCleanUpList m_cleanups ;
	//
	typedef BwSingletonT<BwCleaner> singleton ;
	singleton m_singleton ;
} ;

#endif //_BwCleaner_H
