/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwRandom_H
#define _BwRandom_H

#include <stdlib.h>

namespace bwmath {

template<typename T>
inline const T& Sign(const T& x) {
	return x < 0.0f ? -1.0f : 1.0f;
}
template<typename T>
inline const T& Min(const T& a, const T& b) {
	return a < b ? a : b;
}
template<typename T>
inline const T& Max(const T& a, const T& b) {
	return a > b ? a : b;
}
template<typename T>
inline const T& Clamp(const T& a, const T& low, const T& high) {
	return Max(low, Min(a, high));
}

template<typename T> inline void Swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

inline void seedRandom(unsigned int seed) {
   ::srand(seed);
}

inline float unitRandom()
{
   return float(::rand())/float(RAND_MAX);
}

inline float rangeRandom( float x1, float x2 )
{
   float r = unitRandom();
   float size = x2 - x1;
   return float( r * size + x1 );
}

} //namespace bwmath {

#endif //_BwRandom_H