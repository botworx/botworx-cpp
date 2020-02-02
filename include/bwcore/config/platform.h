/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/

#ifndef BW_CORE_CONFIG_PLATFORM_H
#define BW_CORE_CONFIG_PLATFORM_H


#if defined(_MSC_VER)
//_itoa(val, buffer, 10) ;
#define bwItoa(val, buffer, size, radix) _itoa_s(val, buffer, size, radix)
#elif defined(__GNUC__)
#define bwItoa(val, buffer, size, radix) snprintf(buffer, bufferSize, "%d", val)
#else
//boost::asio problems on mingw
#ifdef WIN32
#define swprintf _snwprintf
#endif

#endif

#endif //BW_CORE_CONFIG_PLATFORM_H
