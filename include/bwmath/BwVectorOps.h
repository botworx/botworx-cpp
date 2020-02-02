#ifndef _BwVectorOps_H
#define _BwVectorOps_H

/////////////////
//TODO:should be template specialization?
//tried ... meta templates are insane to figure out
inline bwVector3 operator*(const bwVector3& v1, const bwVector3& v2)
{
	return bwVector3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}
/*inline bwVector3 operator*=( const bwVector3& a, bwReal s )
{
	a[0]*=s;
	a[1]*=s;
	a[2]*=s;
	return a;
}*/

#include "BwVectorFns.h"

#endif //_BwVectorOps_H
