/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwCommon_H
#define _BwCommon_H

#define bwAssert(x) assert(x)
#ifdef _DEBUG
#define BW_DEBUG 1
#endif

#include <bwstd/BwMemory.h>
#include <bwstd/BwException.h>
#include <bwstd/BwSingleton.h>

#include "BwSignature.h"
#include "BwFactory.h"

#endif //_BwCommon_H
