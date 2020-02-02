/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrModelOps_H
#define _VrModelOps_H

#include "VrModel.h"

//Ray Functionality
inline void setRay(VrModel& model, const bwPoint3& start, const bwQuat &quat) {
	model.setQuat(quat) ;
	model.setPos(start + model.getQuat() * bwVector3(bwReal(0),bwReal(0),model.getRadius())) ;
}
inline bwPoint3 getStart(VrModel& model) {
	bwReal length = model.getLength() ;
	bwReal halfLength = length * bwReal(.5) ;
	bwPoint3 start = model.getPos() + model.getQuat() * bwVector3(bwReal(0), bwReal(0), -halfLength) ;
	return start ;
}
inline bwPoint3 getEnd(VrModel& model) {
	bwReal length = model.getLength() ;
	bwReal halfLength = length * bwReal(.5) ;
	bwPoint3 end = model.getPos() + model.getQuat() * bwVector3(bwReal(0), bwReal(0), halfLength) ;
	return end ;
}
inline bwRay getRay(VrModel& model) {
	bwReal length = model.getLength() ;
	bwReal halfLength = length * bwReal(.5) ;
	bwPoint3 start = model.getPos() + model.getQuat() * bwVector3(bwReal(0), bwReal(0), -halfLength) ;
	bwVector3 dir = model.getQuat() * bwVector3(bwReal(0), bwReal(0), length) ;
	bwRay ray(start, dir) ;
	return ray ; 
}
inline bwLine getLineSeg(VrModel& model) {
	bwReal length = model.getLength() ;
	bwReal halfLength = length * bwReal(.5) ;
	bwPoint3 start = model.getPos() + model.getQuat() * bwVector3(bwReal(0), bwReal(0), -halfLength) ;
	bwVector3 dir = model.getQuat() * bwVector3(bwReal(0), bwReal(0), length) ;
	bwLine seg(start, dir) ;
	return seg ; 
}
inline void setDirection(VrModel& model, const bwVector3& dir) { model.setQuat(makePure(dir)) ; }
inline bwVector3 getDirection(VrModel& model) { return makeVec(model.getQuat()) ; }

inline bwEuler getEuler(VrModel& model) { return makeEulerFromQuaternion(model.getQuat()) ; }
//huh?
inline bwVector3 vectorToWorld(const bwMatrix3x3 &r, bwReal x, bwReal y, bwReal z) {
	return r * bwVector3(x, y, z) ;
}
//
inline bwReal getPointDistance(VrModel& model, const bwPoint3& point) { return bwmath::distance(model.getPos(), point) ; }
inline bwPoint3 getRelPoint(VrModel& model, const bwVector3& vector) {
	bwQuat quat = model.getQuat() ;
	return model.getPos() + (normalize(quat) * vector) ;
}
inline bwVector3 getUnitVector(VrModel& model, const bwPoint3& point) {
	bwVector3 unit ;
	unit = point - model.getPos() ;
	normalize(unit) ;
	return unit ;
}

#endif //_VrModelOps_H
