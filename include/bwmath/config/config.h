/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxPZ_License.txt for details.
*/
#ifndef _BwMath_cfg_H
#define _BwMath_cfg_H

#include "bwmath/config/options.h"

#if MATH_OPTION_SINGLE_PRECISION
namespace bwmath {
typedef int Integer ;
typedef float Real ;
} //namespace bwmath {

#else //DOUBLE PRECISION
namespace bwmath {
typedef int Integer ; //long?
typedef double Real ;
} //namespace bwmath {

#endif

#include "bwmath/config/includes.h"

#endif //_BwMath_cfg_H
