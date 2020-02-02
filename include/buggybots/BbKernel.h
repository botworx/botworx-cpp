/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbKernel_H
#define _BbKernel_H

#include <bwcore/BwKernel.h>

class BbKernel : public BwKernel {
public:
	BbKernel() ;
	virtual void doCreate(const BwPartInfo& info) ;
	//Singleton support
	static void startup() ;
} ;
#endif //_BbKernel_H
