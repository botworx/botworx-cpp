#ifndef _AiMeta_meta_H
#define _AiMeta_meta_H

class AiType ;

struct AiTypeDescriptor {
	AiType* p_type ;
} ;
#define AITYPE_MAX 512
#define TYPEDIR(N) (g_core->p_typeDir[N].p_type)

//
/*A bit of explanation:
	ASize: Size of a struct or class
	BSize: Size of an area that immediately follows a struct
*/
#define getThingASize(M) (M->m_thingASize)
#define getThingBSize(M) (asBlobType(M)->m_thingBSize)
#define getThingSize(M) (M->m_thingSize)
//
template <typename T>
class TypeAccessor {
public:
	static AiType& get() ;
	static AiType* getPtr() ;
} ;
#define THINGMETAOF(C) (TypeAccessor<C##Type>::getPtr())
///////////////
class AiCore ;

typedef unsigned long RawHash ;

typedef size_t ThingSize ;
typedef size_t ThingPos ;
typedef size_t ThingLength ;
typedef int ThingCount ;
typedef unsigned int ThingIndex ;
/////////////////////
#define NIL ((BwCell*)0)
#define UNBOUND ((BwCell*)1)
//
#define asCell(C) (static_cast<BwCell*>(C))
#define asConstCell(C) (static_cast<const BwCell*>(C))
#define isNil(C) (C == NULL)
#define notNil(C) (C != NIL)
#define isEq(X,Y) (asConstCell(X) == asConstCell(Y))
//
//#define setTT(C, T) (C->m_typeID = T)
#define getTT(C) (C->getTypeId())
#define isTT(X, T) (X == T)
#define isAboveTT(X, T) (X > T)
#define isOrAboveTT(X, T) (X >= T)
#define isBelowTT(X, T) (X < T)
#define isOrBelowTT(X, T) (X <= T)
#define ofTT(X,T) (isOrAboveTT(X, T) && isOrBelowTT(X, T##_UNKNOWN))
#define ifTT(X, T) isTT(X, T) ? T
#define ifOfTT(X, T) ofTT(X, T) ? T

#endif//_AiMeta_meta_H
