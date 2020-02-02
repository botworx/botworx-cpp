#ifndef _VrMath_vector_H
#define _VrMath_vector_H

#include "Utilities.h"  // for interpolate, etc.

namespace OpenSteer {

inline bwReal distance (const bwVector3& a, const bwVector3& b) {
	bwReal val = length(bwVector3(a-b)) ; 
	return val ;
}
inline bwVector3 truncateLength (const bwVector3& vec, const float maxLength)
{
    const float maxLengthSquared = maxLength * maxLength;
    const float vecLengthSquared = lengthSquared(vec);
    if (vecLengthSquared <= maxLengthSquared)
        return vec ;
    else
        return vec * bwReal(maxLength / sqrtXXX (vecLengthSquared));
}
inline bwVector3 sphericalWrapAround (const bwVector3& vec, const bwVector3& center, float radius)
{
    const bwVector3 offset = vec - center;
    const bwReal r = length(offset);
    if (r > radius)
        return vec + ((offset/r) * bwReal(radius * -2.0f)) ;
    else
        return vec ;
}

// --------------------------- utility member functions used in OpenSteer

// return component of vector parallel to a unit basis vector
// (IMPORTANT NOTE: assumes "basis" has unit magnitude (length==1))

inline bwVector3 parallelComponent (const bwVector3& v, const bwVector3& unitBasis)
{
    const bwReal projection = dot(v, unitBasis) ;
    return unitBasis * projection;
}

// return component of vector perpendicular to a unit basis vector
// (IMPORTANT NOTE: assumes "basis" has unit magnitude (length==1))

inline bwVector3 perpendicularComponent (const bwVector3& v, const bwVector3& unitBasis)
{
    //return (*this) - parallelComponent (unitBasis);
	return v - parallelComponent (v, unitBasis);
}
//TODO:fixme:set implies changing the input.
inline bwVector3 setX(const bwVector3& vec, bwReal val) { return bwVector3(val, vec[1], vec[2]) ; }
inline bwVector3 setY(const bwVector3& vec, bwReal val) { return bwVector3(vec[0], val, vec[2]) ; }
inline bwVector3 setZ(const bwVector3& vec, bwReal val) { return bwVector3(vec[0], vec[1], val) ; }
inline bwVector3 setXtoZero (const bwVector3& vec) { return setX(vec,0) ; }
inline bwVector3 setYtoZero (const bwVector3& vec) { return setY(vec,0) ; }
inline bwVector3 setZtoZero (const bwVector3& vec) { return setZ(vec,0) ; }
inline bwVector3 setXtoOne(const bwVector3& vec) { return setX(vec,1) ; }
inline bwVector3 setYtoOne(const bwVector3& vec) { return setY(vec,1) ; }
inline bwVector3 setZtoOne(const bwVector3& vec) { return setZ(vec,1) ; }
// ----------------------------------------------------------------------------
// Returns a position randomly distributed inside a sphere of unit radius
// centered at the origin.  Orientation will be random and length will range
// between 0 and 1


bwVector3 RandomVectorInUnitRadiusSphere (void);


// ----------------------------------------------------------------------------
// Returns a position randomly distributed on a disk of unit radius
// on the XZ (Y=0) plane, centered at the origin.  Orientation will be
// random and length will range between 0 and 1


bwVector3 randomVectorOnUnitRadiusXZDisk (void);


// ----------------------------------------------------------------------------
// Returns a position randomly distributed on the surface of a sphere
// of unit radius centered at the origin.  Orientation will be random
// and length will be 1


inline bwVector3 RandomUnitVector (void)
{
    //return RandomVectorInUnitRadiusSphere().normalize();
	bwVector3 temp = RandomVectorInUnitRadiusSphere() ;
	normalize(temp) ;
	return temp ;
}


// ----------------------------------------------------------------------------
// Returns a position randomly distributed on a circle of unit radius
// on the XZ (Y=0) plane, centered at the origin.  Orientation will be
// random and length will be 1


inline bwVector3 RandomUnitVectorOnXZPlane (void)
{
    //return RandomVectorInUnitRadiusSphere().setYtoZero().normalize();
	bwVector3 temp = setYtoZero(RandomVectorInUnitRadiusSphere()) ;
	normalize(temp) ;
	return temp ;
}


// ----------------------------------------------------------------------------
// used by limitMaxDeviationAngle / limitMinDeviationAngle below


bwVector3 vecLimitDeviationAngleUtility (const bool insideOrOutside,
                                    const bwVector3& source,
                                    bwReal cosineOfConeAngle,
                                    const bwVector3& basis);


// ----------------------------------------------------------------------------
// Enforce an upper bound on the angle by which a given arbitrary vector
// diviates from a given reference direction (specified by a unit basis
// vector).  The effect is to clip the "source" vector to be inside a cone
// defined by the basis and an angle.


inline bwVector3 limitMaxDeviationAngle (const bwVector3& source,
                                    const float cosineOfConeAngle,
                                    const bwVector3& basis)
{
    return vecLimitDeviationAngleUtility (true, // force source INSIDE cone
                                            source,
                                            cosineOfConeAngle,
                                            basis);
}


// ----------------------------------------------------------------------------
// Enforce a lower bound on the angle by which a given arbitrary vector
// diviates from a given reference direction (specified by a unit basis
// vector).  The effect is to clip the "source" vector to be outside a cone
// defined by the basis and an angle.


inline bwVector3 limitMinDeviationAngle (const bwVector3& source,
                                    const float cosineOfConeAngle,
                                    const bwVector3& basis)
{    
    return vecLimitDeviationAngleUtility (false, // force source OUTSIDE cone
                                            source,
                                            cosineOfConeAngle,
                                            basis);
}


// ----------------------------------------------------------------------------
// Returns the distance between a point and a line.  The line is defined in
// terms of a point on the line ("lineOrigin") and a UNIT vector parallel to
// the line ("lineUnitTangent")


inline float distanceFromLine (const bwVector3& point,
                                const bwVector3& lineOrigin,
                                const bwVector3& lineUnitTangent)
{
    const bwVector3 offset = point - lineOrigin;
    //const bwVector3 perp = offset.perpendicularComponent (lineUnitTangent);
	const bwVector3 perp = perpendicularComponent (offset, lineUnitTangent);
    //return perp.length();
	return length(perp);
}


// ----------------------------------------------------------------------------
// given a vector, return a vector perpendicular to it (note that this
// arbitrarily selects one of the infinitude of perpendicular vectors)


bwVector3 findPerpendicularIn3d (const bwVector3& direction);

} //namespace OpenSteer {
#endif //_VrMath_vector_H