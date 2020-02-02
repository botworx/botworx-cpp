/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/

#ifndef _Kernel_includes_H
#define _Kernel_includes_H

#ifdef BW_WINDOWS

#define NOMINMAX
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <process.h>
#include <tchar.h>

#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <stack>
#include <bitset>
//
#include <unordered_map>
/////////////////////////
# pragma warning ( disable : 4244 )
# pragma warning ( disable : 4251 )
# pragma warning ( disable : 4275 )
# pragma warning ( disable : 4800 )

#include <bwcore/config/boost_smart_ptr.h>
#include <bwcore/config/boost_pool.h>
#include <bwcore/config/boost_filesystem.h>
//
#include <bwcore/config/defines.h>
//TODO:note:must include BwCommon before any Cell/Part dependent code is actually instantiated.
#include <bwcore/BwCommon.h>
//
#include <bwcore/BwStepper.h>
//
#include <bwmessaging/BwMessage.h>

#endif //_Kernel_includes_H
