#ifndef _BwVectorFns_H
#define _BwVectorFns_H

namespace bwmath {

//////////////////
//TODO:
#define bwAbs(x) (x > 0  ? x : x * -1)
#define BWSQRT12 bwReal(0.7071067811865475244008443621048490)
inline void planeSpace(const Vector3& n, Vector3& p, Vector3& q) {
	//if (gmtl::Math::abs(n[2]) > BWSQRT12) {
	if (bwAbs(n[2]) > BWSQRT12) {
		// choose p in y-z plane
		bwReal a = n[1]*n[1] + n[2]*n[2];
		bwReal k = bwRsqrt(a);
		//p[0] = 0 ;
		p[0] = bwmath::RealTraits<bwReal>::Zero ;
		p[1] = -n[2]*k;
		p[2] = n[1]*k;
		// set q = n x p
		q[0] = a*k;
		q[1] = -n[0]*p[2];
		q[2] = n[0]*p[1];
	}
	else {
		// choose p in x-y plane
		bwReal a = n[0]*n[0] + n[1]*n[1];
		bwReal k = bwRsqrt(a);
		p[0] = -n[1]*k;
		p[1] = n[0]*k;
		p[2] = 0;
		// set q = n x p
		q[0] = -n[2]*p[1];
		q[1] = n[2]*p[0];
		q[2] = a*k;
	}
}

}

#endif //_BwVectorFns_H
