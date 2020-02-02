/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Kernel_config_H
#define _Kernel_config_H

#include "platform.h"
//
//BOTWORX_OPTIONS
//
#if !defined(BOTWORX_OPTIONS)
#define BOTWORX_OPTIONS <bwcore/config/options.h>
#endif

#include BOTWORX_OPTIONS
//
//BOTWORX_PREFIX
//
#if !defined(BOTWORX_PREFIX)
#define BOTWORX_PREFIX <bwcore/config/prefix.h>
#endif

#include BOTWORX_PREFIX
//
//BOTWORX_INCLUDES
//
#if !defined(BOTWORX_INCLUDES)
#define BOTWORX_INCLUDES <bwcore/config/includes.h>
#endif

#include BOTWORX_INCLUDES
//
//BOTWORX_CORE
//
#if !defined(BOTWORX_CORE)
#define BOTWORX_CORE <bwcore/config/core.h>
#endif

#include BOTWORX_CORE
//
//BOTWORX_ACCESS
//
#if !defined(BOTWORX_ACCESS)
#define BOTWORX_ACCESS <bwcore/config/access.h>
#endif

#include BOTWORX_ACCESS
//
//BOTWORX_SUFFIX
//
#if !defined(BOTWORX_SUFFIX)
#define BOTWORX_SUFFIX <bwcore/config/suffix.h>
#endif

#include BOTWORX_SUFFIX

//include other configs here?

#endif //_Kernel_config_H
