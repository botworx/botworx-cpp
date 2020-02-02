/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrLay_H
#define _VrLay_H

class VrModel ;
class VrGroup ;
class VrBody ;

class VrLay {
public:
	VrLay() {
		m_type = LAY_DEFAULT ;
	}
	VrLay& clone(const VrLay& lay) ;
	virtual bwString getClassName() { return "VrLay" ; }
	void invalidate() ;
	virtual void validate() ;
	void setPos(const bwPoint3& point) ;
	virtual void _setPos(const bwPoint3& point) ;
	const bwPoint3& getPos() { return m_pos ; }
	void setRelPos(const bwPoint3& point) ;
	virtual void _setRelPos(const bwPoint3& point) ;
	const bwPoint3& getRelPos() { return m_relPos ; }

	virtual bwPoint3 getOrigin() ;
	void setQuat(const bwQuat& quat) ;
	virtual void _setQuat(const bwQuat& quat) ;
	const bwQuat& getQuat() { return m_quat ; }
	void setRelQuat(const bwQuat& quat) ;
	virtual void _setRelQuat(const bwQuat& quat) ;
	const bwQuat& getRelQuat() { return m_relQuat ; }
	//
	virtual void onLeader() {}
	//convenience functions
	VrModel& model() ;
	VrGroup* getGroup() ;
	VrBody* getBody() ;
	//
	/*Data Members*/
	//
	bwPoint3 m_pos ;
	bwQuat m_quat ;
	bwPoint3 m_relPos ;
	bwQuat m_relQuat ;

	//bwPoint3 m_specialRelPos ;
	//bwQuat m_specialRelQuat ;

	enum layType {
		LAY_DEFAULT = 0,
		LAY_REL,
		LAY_ABS,
		LAY_FOLLOW,
		LAY_ORIGIN_REL,
		LAY_BODY_ABS,
		LAY_BODY_REL
	} ;
	layType m_type ;
	layType getLayType() { return m_type ; }
};
/*Absolute Position & Quaternion*/
class VrAbsLay : public VrLay {
public:
	VrAbsLay() : VrLay() { m_type = LAY_ABS ; }
	VrAbsLay(const bwPoint3& point)
		: VrLay() { 
			m_type = LAY_ABS ; 
			m_pos = point ;
	}
	virtual bwString getClassName() { return "VrAbsLay" ; }
	//
	virtual void _setPos(const bwPoint3& point) ;
	virtual void _setRelPos(const bwPoint3& point) ;
	virtual void _setQuat(const bwQuat& quat)  ;
	virtual void _setRelQuat(const bwQuat& quat)  ;
	/*Data Members*/
};
/*Group Relative Position & Quaternion*/
class VrRelLay : public VrLay {
public:
	VrRelLay() : VrLay() { m_type = LAY_REL ; }
	VrRelLay(const bwPoint3& point)
		: VrLay() { 
			m_type = LAY_REL ; 
			//m_specialRelPos = point ;
			m_relPos = point ;
	}
	virtual bwString getClassName() { return "VrRelLay" ; }
	//
	virtual void _setPos(const bwPoint3& point) ;
	virtual void _setRelPos(const bwPoint3& point) ;
	virtual void _setQuat(const bwQuat& quat)  ;
	virtual void _setRelQuat(const bwQuat& quat)  ;
	//
	virtual void validate() ;
	/*Data Members*/
};
/*Body Relative Position & Quaternion*/
class VrFollowLay : public VrRelLay {
public:
	VrFollowLay() : VrRelLay() { m_type = LAY_FOLLOW ; }
	virtual bwString getClassName() { return "VrFollowLay" ; }
	virtual void validate() ;
	virtual void onLeader() ;
	/*Data Members*/
};
/*Body Absolute Position & Quaternion*/
class VrBodyAbsLay : public VrAbsLay {
public:
	VrBodyAbsLay() : VrAbsLay() { m_type = LAY_BODY_ABS ; }
	virtual bwString getClassName() { return "VrBodyAbsLay" ; }
	virtual void validate() ;
	/*Data Members*/
};
/*Body Relative Position & Quaternion*/
class VrBodyRelLay : public VrRelLay {
public:
	VrBodyRelLay() : VrRelLay() { m_type = LAY_BODY_REL ; }
	virtual bwString getClassName() { return "VrBodyRelLay" ; }
	virtual void validate() ;
	/*Data Members*/
};
/*Body Relative Position & Quaternion*/
class VrOriginRelLay : public VrLay {
public:
	VrOriginRelLay() 
		: VrLay() { 
			m_type = LAY_ORIGIN_REL ; 
		}
	VrOriginRelLay(const bwPoint3& point) 
		: VrLay() { 
			m_type = LAY_ORIGIN_REL ; 
			//m_specialRelPos = point ;
			m_relPos = point ;
		}
	virtual bwString getClassName() { return "VrOriginRelLay" ; }
	//
	virtual bwPoint3 getOrigin() ;
	//
	virtual void _setPos(const bwPoint3& point) ;
	virtual void _setRelPos(const bwPoint3& point) ;
	virtual void _setQuat(const bwQuat& quat)  ;
	virtual void _setRelQuat(const bwQuat& quat)  ;
	//
	virtual void validate() ;
	/*Data Members*/
};
#endif //_VrLay_H
