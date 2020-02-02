/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxPZ_License.txt for details.
*/
#ifndef _BwMath_aliases_H
#define _BwMath_aliases_H

namespace bwmath {
	typedef gmtl::Vec<bwReal, 3> Vector3 ;
	typedef gmtl::Point<bwReal, 3> Point3 ;
	typedef gmtl::Quat<bwReal> Quat ;
	typedef gmtl::Matrix<bwReal, 3, 3> Matrix33 ;
	typedef gmtl::Matrix<bwReal, 4, 4> Matrix44 ;
	///
	typedef gmtl::Vec<bwReal, 3> Size3 ;
	typedef gmtl::AABox<bwReal> Bounds3 ;
	typedef gmtl::Ray<bwReal> Ray ;
	typedef gmtl::LineSeg<bwReal> Line ;
	typedef gmtl::AxisAngle<bwReal> AxisAngle ;
	typedef gmtl::Tri<bwReal> Triangle ;
	typedef gmtl::Plane<bwReal> Plane ;
	//
	typedef gmtl::Sphere<bwReal> Sphere ;
	//X=pitch, Y=yaw, Z=roll
	typedef gmtl::EulerAngle<bwReal, gmtl::XYZ> EulerAngle ;
	typedef gmtl::Vec<bwReal, 2> Size2 ;
}
//Userland Aliases
typedef bwReal bwRadian ;
typedef bwReal bwDegree ;

typedef bwmath::Vector3		bwVector3 ;
typedef bwmath::Point3		bwPoint3 ;
typedef bwmath::Quat		bwQuat ;
///
typedef bwmath::Size3		bwSize3 ;
typedef bwmath::Size2		bwSize2 ;
//
typedef bwmath::Bounds3		bwBounds3 ;
//
#define BW_UP (bwVector3(0, 1, 0))
#define BW_FORWARD (bwVector3(0, 0, 1))
#define BW_SIDE (bwVector3(-1, 0, 0))
//
typedef bwmath::Matrix33 bwMatrix3x3 ;
typedef bwmath::Matrix44 bwMatrix4x4 ;
/////
typedef bwmath::EulerAngle bwEuler ;
typedef bwmath::AxisAngle bwAxisAngle ;
///
typedef bwmath::Plane bwPlane ;
///
typedef bwmath::Ray bwRay ;
typedef bwRay bwParticle ;
//
typedef bwmath::Line bwLine ;
//
typedef bwmath::Sphere bwSphere ;
typedef bwmath::Triangle bwTriangle ;

//////////
#endif //_BwMath_aliases_H
