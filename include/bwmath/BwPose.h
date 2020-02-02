#ifndef _BwPose_H
#define _BwPose_H

namespace bwmath {

class Pose {
public:
	Pose() {}
	Pose(const Point3& pos, const Quat& quat) {
		m_pos = pos ;
		m_quat = quat ;
	}
	void setPos(const Point3& pos) { m_pos = pos ; }
	const Point3& getPos() const { return m_pos ; }
	const Quat& setQuat(const Quat& quat) { m_quat = quat ; return quat; }
	const Quat& getQuat() const { return m_quat ; }
	//Data Members
	Point3 m_pos ;
	Quat m_quat ;
} ;

inline Point3 operator*(const Point3& point, const Pose& pose) {
	return pose.m_quat * point + pose.m_pos ;
}

inline Pose operator*(const Pose& pose1, const Pose& pose2) {
	//return pose.mRot * point + pose.mPos ;
	return Pose(pose2.m_quat * pose1.m_pos + pose2.m_pos, pose1.m_quat * pose2.m_quat) ;
}

} //namespace
//
typedef bwmath::Pose		bwPose ;

#endif //_BwPose_H
