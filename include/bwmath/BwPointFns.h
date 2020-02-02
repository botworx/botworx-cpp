#ifndef _BwPointFns_H
#define _BwPointFns_H

namespace bwmath {

//! calculate the square of the magnitude
inline Real mag2(const Point3& point) {
	return (Real) (point[0]*point[0]+point[1]*point[1]+point[2]*point[2]);
}
//! calculate the magnitude
inline Real mag(const Point3& point) {return Real(bwSqrt(mag2(point))) ;}

inline Real distance(const Point3& point, const Point3& point2) {
	if( (point[0] == point2[0]) &&
		(point[1] == point2[1]) &&
		(point[2] == point2[2]) )
		return Real(0) ;

	Real posX(0), posY(0), posZ(0), result(0) ;

	posX = point2[0] - point[0] ;
	posY = point2[1] - point[1] ;
	posZ = point2[2] - point[2] ;

	posX *= posX;
	posY *= posY;
	posZ *= posZ;

	result = bwSqrt(posX + posY + posZ);
	return result ;
}

} //namespace bwmath

#endif //_BwPointFns_H
