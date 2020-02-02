/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxPZ_License.txt for details.
*/
#ifndef _BwMath_options_H
#define _BwMath_options_H

//disable size_t conversion warning
#ifdef _MSC_VER
#  pragma warning(disable: 4267 4311)
#endif

//Math
#define _USE_MATH_DEFINES
#undef PI //TODO:used for gmtl ...

/*===================================*/
/*Change to zero for double precision*/
// #define MATH_OPTION_SINGLE_PRECISION  1
#define MATH_OPTION_SINGLE_PRECISION  0
/*===================================*/

#endif //_BwMath_options_H
