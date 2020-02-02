/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _Kernel_defines_H
#define _Kernel_defines_H

/*Std defines*/
typedef std::string bwString ;
/*Boost defines*/
typedef boost::filesystem::path bwPath ;

typedef float bwDT ;

#define BWDT_MIN 0.01
#define BWDT_MAX 0.03
#define BWDT_RAMP 0.001

typedef bool bwBool ;
typedef unsigned char bwByte;
typedef uint16_t bwInt16U ;
typedef int64_t bwInt64 ;
typedef int32_t bwInt32 ;
typedef uint32_t bwInt32U ;
typedef float bwFloat ;

typedef unsigned int bwIndex ;
typedef unsigned int bwIndex32 ;
typedef unsigned short bwIndex16 ;

typedef size_t bwHandle ;
const bwHandle bwAnyHandle = (size_t)-1 ;

typedef size_t bwWhat ;

/////////////////////////////////////
class BwMessage ;
class BwKernel ;
class BwFactory ;
class BwDefaultFactory ;
class BwDefaultKit ;

class BwPart ;
typedef std::list<BwPart*> BwPartList ;
typedef BwPartList BwPartContainer ;
typedef BwPartContainer::iterator BwPartIter ;

class BwActor ;
typedef std::list<BwActor*> BwActorList ;
typedef BwActorList BwActorContainer ;
typedef BwActorContainer::iterator BwActorIter ;

#endif //_Kernel_defines_H
