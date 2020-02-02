/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BwMath_H
#define _BwMath_H

//namespace bwmath {

inline bwDegree makeDegree(const bwRadian& r) {
	return (r * bwReal(180.0f)) / bwRealTraits::Pi ;
}
inline bwRadian makeRadian(const bwDegree& d) {
	return (d * bwRealTraits::Pi) / bwReal(180.0f) ;
}

enum {
	yawElem = 0,
	pitchElem,
	rollElem
} ;

/////////////////
/*courtesy of euclideanspace*/
inline bwQuat makeQuatFromEuler(bwReal yaw, bwReal pitch, bwReal roll) {
	bwReal cosY = cos(yaw / bwReal(2)) ;
	bwReal sinY = sin(yaw / bwReal(2)) ;
	bwReal cosP = cos(pitch / bwReal(2)) ;
	bwReal sinP = sin(pitch / bwReal(2)) ;
	bwReal cosR = cos(roll / bwReal(2)) ;
	bwReal sinR = sin(roll / bwReal(2)) ;

	bwQuat quat ;
	quat[3] = cosR * sinP * cosY + sinR * cosP * sinY ;
	quat[0] = cosR * cosP * sinY - sinR * sinP * cosY ;
	quat[1] = sinR * cosP * cosY - cosR * sinP * sinY ;
	quat[2] = cosR * cosP * cosY + sinR * sinP * sinY ;

	return quat ;
}
inline void makePitch(bwEuler &euler, bwReal degree) {
	bwReal d = euler[0] + degree ;
	if(d < bwRealTraits::Zero)
		d = bwRealTraits::Pi2 - degree ;
	else
	if(d > bwRealTraits::Pi2)
		d = degree ;
	euler[0] = d ;
}
/*courtesy of euclideanspace*/
inline bwEuler makeEulerFromQuaternion(const bwQuat &quat) {
	bwEuler euler ;
	bwReal sqw = quat[3]*quat[3] ;    
	bwReal sqx = quat[0]*quat[0] ;
	bwReal sqy = quat[1]*quat[1] ;
	bwReal sqz = quat[2]*quat[2] ;
	bwReal unit = sqx + sqy + sqz + sqw ; // if normalised is one, otherwise is correction factor
	bwReal test = quat[0]*quat[1] + quat[2]*quat[3] ;
	if (test > bwReal(0.499)*unit) { // singularity at north pole ... constant ... AlmostHalf???
		euler[0] = bwRealTraits::Two * atan2(quat[0],quat[3]);
		euler[1] = bwRealTraits::PiDiv2 ;
		euler[2] = 0;
		return euler ;
	}	if (test < -bwReal(0.499)*unit) { // singularity at south pole
		euler[0] = -bwRealTraits::Two * atan2(quat[0],quat[3]);
		euler[1] = bwRealTraits::NegPiDiv2 ;
		euler[2] = 0;
		return euler ;
	}    
	euler[0] = atan2(bwRealTraits::Two*quat[1]*quat[3]-bwRealTraits::Two*quat[0]*quat[2] , sqx - sqy - sqz + sqw);
	euler[1] = asin(bwRealTraits::Two*test/unit);
	euler[2] = atan2(bwRealTraits::Two*quat[0]*quat[3]-bwRealTraits::Two*quat[1]*quat[2] , -sqx + sqy - sqz + sqw) ;

	return euler ;
}

//} //namespace bwmath

#endif //_BwMath_H
