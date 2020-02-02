/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrModel_H
#define _VrModel_H

#include <bwcore/BwActor.h>
#include "VrLay.h"
#include "VrTracer.h"
//
#include "VrBodyInfo.h"
#include "VrVuInfo.h"

class VrPhysics ;
class VrGroup ;
class VrPlace ;
class VrBody ;
class VrVu ;
class VrCollider ;
class VrNode ;
class VrNodeKit ;
//
//VrModel
//
class VrModel : public BwActor {
public:
	VrModel(VrGroup *pGroup) ;
	virtual ~VrModel() ;
	virtual bwString getClassName() { return "VrModel" ; }
	virtual void doCreate(const BwPartInfo& info) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	virtual void doConfig() ;
	virtual void doPostConfig() ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doPostEnable(bool sleeping = false) ;
	virtual void doDisable(bool sleeping = true) ;
	virtual void doPostDisable(bool sleeping = true) ;
	virtual void doStep(BwStepper& stepper) ;
	virtual void doPostStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	//
	virtual void sleep() ;
	virtual void _sleep() ;
	virtual void wake() ;
	virtual void _wake() ;
	void touch(VrModel *pModel) ;
	void _touch(VrModel *pModel) ;
	//
	virtual void createStaticLay() ;
	virtual void createDynamicLay() ;
	virtual void layout() ;
	virtual void onLayout() ;
	//
	enum invalid_E {
		INVALID_NONE = 0,
		INVALID_POSE = 1,
		INVALID_SIZE = 2,
		INVALID_MASS = 4
	} ;
	typedef size_t invalid ;
	invalid m_invalidFlags ;

	void clearInvalid(invalid flag) { clearFlag(m_invalidFlags, flag) ; }
	void setInvalid(invalid flag) { setFlag(m_invalidFlags, flag) ; }
	bool getInvalid(invalid flag) { return getFlag(m_invalidFlags, flag) ; }
	//
	void clearInvalidFlags() { m_invalidFlags = INVALID_NONE ; }
	void allInvalidFlags() { m_invalidFlags = INVALID_POSE | INVALID_SIZE | INVALID_MASS ; }
	void setInvalidFlags(invalid flags) { m_invalidFlags = flags ; }
	invalid getInvalidFlags() { return m_invalidFlags ; }
	//
	bool invalidPose() { return getFlag(m_invalidFlags, INVALID_POSE) ; }
	bool invalidSize() { return getFlag(m_invalidFlags, INVALID_SIZE) ; }
	bool invalidMass() { return getFlag(m_invalidFlags, INVALID_MASS) ; }
	//
	void invalidatePose() ;
	void validatePose() ;
	void invalidateSize() ;
	virtual void invalidate(VrModel *pModel, invalid flag) ;
	void validate() ;
	virtual void doValidate() ;
	virtual void doPostValidate() ;
	void invalidateGroup(invalid flags) ;
	//
	void migrate(VrGroup *pGroup) ;
	virtual void migrate() ;
	void doMigrate(VrGroup* pOldGroup, VrGroup* pNewGroup) ;
	VrGroup* getFutureGroup() { return p_futureGroup ; }
	VrGroup *p_futureGroup ; //TODO:fix migration!!!
	//
	virtual void createNode() ;
	virtual void validateNode() ;
	VrNode* getNode() { return p_node ; }
	virtual void createNodeKit() ;
	void setNodeKit(VrNodeKit* pKit) { p_nodeKit = pKit ; }
	VrNodeKit* getNodeKit() { return p_nodeKit ; }
	VrNode *p_node ;
	VrNodeKit *p_nodeKit ;
	//
	void collide() ;
	VrCollider *p_collider ;
	void setCollider(VrCollider *pCollider) { p_collider = pCollider ; }
	VrCollider* getCollider() { return p_collider ; }
	//TODO:Use flags ...
	void setTestInternal(bool val) { m_testInternal = val ; }
	bool testInternal() { return m_testInternal ; }
	bool m_testInternal ;
	void setIsGhost(bool val) { m_isGhost = val ; }
	bool isGhost() { return m_isGhost ; }
	bool m_isGhost ;
	//
	void setPos(const bwPoint3& pos) {	m_lay.setPos(pos) ; }
	void setPos(bwReal x, bwReal y, bwReal z) { setPos(bwPoint3(x, y, z)) ; }
	const bwPoint3& getPos() { return m_lay.getPos() ; }
	void setQuat(const bwQuat &quat) { m_lay.setQuat(quat) ;	}
	const bwQuat& getQuat() { return m_lay.getQuat() ; }
	//
	void setRelPos(const bwPoint3& point) { m_lay.setRelPos(point) ;	}
	void setRelPos(bwReal x, bwReal y, bwReal z) { setRelPos(bwPoint3(x, y, z)) ; }
	const bwPoint3& getRelPos() { return m_lay.getRelPos() ; }
	void setRelQuat(const bwQuat &quat) {	m_lay.setRelQuat(quat) ; }
	const bwQuat& getRelQuat() { return m_lay.getRelQuat() ; }
	bwPoint3 getOrigin() { return m_lay.getOrigin() ; }
	//
	void setLeader(VrModel *pLeader) ;
	VrModel* getLeader() { return p_leader ; }
	virtual void onLeader() { m_lay.onLeader() ; }
	void addFollower(VrModel *pFollower) ;
	void removeFollower(VrModel *pFollower) ;
	void notifyFollowers() ; //TODO:make this protected or private
	VrModel *p_leader ; //position leader
	VrModelContainer m_followers ;

	//unfortunately for cylinders, capsules and probably rays ... need to make adjustments.
	bwQuat m_alignment ;
	void setAlignment(const bwQuat& alignment) { m_alignment = alignment ; }
	bwQuat getAlignment() { return m_alignment ; }
	enum upAxis {
		AXIS_X,
		AXIS_Y,
		AXIS_Z
	} ;
	void setUpAxis(upAxis axis) ;
	upAxis getUpAxis() ;
	//
	virtual void createVu(void) ;
	VrVu* getVu(void) { return p_vu ; }

	void setWidth(bwReal width) { setSize(bwSize3(width, m_size[1], m_size[2])) ; }
	bwReal getWidth() { return m_size[0] ; }
	void setHeight(bwReal height) { setSize(bwSize3(m_size[0], height, m_size[2])) ; }
	bwReal getHeight() { return m_size[1] ; }
	void setLength(bwReal length) { setSize(bwSize3(m_size[0], m_size[1], length)) ; }
	bwReal getLength() { return m_size[2] ; }
	void setMinSize(const bwSize3& size) { m_minSize = size ; }
	void setMaxSize(const bwSize3& size) { m_maxSize = size ; }
	bwSize3 constrainSize(const bwSize3& size) {
		bwSize3 result = size ;
		if(size[0] < m_minSize[0])
			result[0] = m_minSize[0] ;
		if(size[1] < m_minSize[1])
			result[1] = m_minSize[1] ;
		if(size[2] < m_minSize[2])
			result[2] = m_minSize[2] ;
		return result ;
	}
	void _setSize(const bwSize3& size) ;
	virtual void setSize(const bwSize3& size) { 
		_setSize(size) ; 
		invalidateSize() ;
	}
	void setSize(bwReal width, bwReal height, bwReal length) { setSize(bwSize3(width, height, length)) ; }
	bwSize3 getSize() { return m_size ; }
	void setRadius(bwReal radius) { setSize(radius * bwRealTraits::Two, radius * bwRealTraits::Two, radius * bwRealTraits::Two) ; }
	void expand(bwReal size) { 
		setSize(	m_size[0] + size,
					m_size[1] + size,
					m_size[2] + size ); }
	void expandBy(bwReal percent) { m_size[0] = m_size[0] + m_size[0] * percent ;
		m_size[1] = m_size[1] + m_size[1] * percent ;
		m_size[2] = m_size[2] + m_size[2] * percent ; invalidateSize() ;
	}
	void shrink(bwReal size) { m_size[0] = m_size[0] - size ;
	m_size[1] = m_size[1] - size ; m_size[2] = m_size[2] - size ; invalidateSize() ;
	}
	bwReal getRadius() { return m_radius ; }
	bwPoint3 getMin() ;
	bwPoint3 getMax() ;
	void computeBoundsCorners(bwPoint3* pCorners) ;
	virtual void validateBounds() ;
	const bwBounds3& getBounds() { return m_bounds ; }
	bwPoint3 getWorldMin() ;
	bwPoint3 getWorldMax() ;

	void setMotionType(motionType type) { m_motionType = type ; }
	motionType getMotionType() { return m_motionType ; }
	
	void setIsPlaceable(bool val) { m_isPlaceable = val ; }
	bool isPlaceable() { return m_isPlaceable ; }

	void setIsViewable(bool val) { m_isViewable = val ; }
	bool isViewable() { return m_isViewable ; }

	void setIsMigrant(bool val) { m_isMigrant = val ; }
	bool isMigrant() { return m_isMigrant; }

	void setVuInfo(const VrVuInfo& vuInfo) { m_vuInfo = vuInfo ; }
	const VrVuInfo* getVuInfo() { return &m_vuInfo ; }
	VrVuInfo& vuInfo() { return m_vuInfo ; }

	//
	virtual void validateSize() ;
	//Physics
	void setBody(VrBody *pBody) { p_body = pBody ; }
	VrBody* getBody() { return p_body ; }
	bool hasBody() { return p_body != NULL ; }
	bool ownsBody() ;
	virtual void createBody() ;
	void invalidateMass() ;
	virtual void validateMass() ;
	void setBodyInfo(const VrBodyInfo* bodyInfo) ;
	const VrBodyInfo* getBodyInfo() { return &m_bodyInfo ; }
	VrBodyInfo& bodyInfo() { return m_bodyInfo ; }
	void copyBodyInfo(VrBodyInfo *pDst, const VrBodyInfo *pSrc) { memcpy(pDst, pSrc, sizeof(VrBodyInfo)) ; }
	void setNodeType(nodeType nodeType) { m_nodeType = nodeType ; }
	nodeType getNodeType() { return m_nodeType ; }
	virtual void createCollider() ;
	//
	VrPlace* getWorld() ;
	void setIndice(int indice) { m_indice = indice ; }
	int getIndice() { return m_indice ; }
	void setGroup(VrGroup *pGroup) ;
	VrGroup* getGroup() { return p_group ; }
	VrPlace* getPlace() ; //search outward to find enclosing place!
	//
	bool isGroup() { return m_nodeType == NODE_GROUP ; }
	bool isPlace() { return m_nodeType == NODE_PLACE ; }
	//
	virtual VrModel* getMain() { return this ; }
	virtual VrModel* getPrimary() { return this ; }
	//
	void setLay(VrLay&& lay) ;
	VrLay* getLay() { return &m_lay ; }
	//
	void setIsEntity(bool val) { m_isEntity = val ; }
	bool isEntity() { return m_isEntity ; }
	//
	void setTracer(VrTracer&& tracer) ;
	VrTracer* getTracer() { return &m_tracer ; }
	void* getMarker() { return m_tracer.getMarker() ; }
	VrTracer m_tracer ;
	/*Data Members*/
public:
	VrLay m_lay ;
	VrGroup *p_group ;
	nodeType m_nodeType ;
	//Bounding Box
	bwBounds3 m_bounds ;
	bwSize3 m_size ;
	bwSize3 m_minSize ;
	bwSize3 m_maxSize ;
	bwReal m_radius ;
	//
	motionType m_motionType ;
	//
	bool m_isEntity ;
	bool m_isPlaceable ;
	bool m_isMigrant ;
	bool m_isViewable ; //means ... call createVu
	//
	//Mass Properties
public:
	VrBody *p_body ;
	VrBodyInfo	m_bodyInfo ;
	//View Properties
	VrVu *p_vu ;
	VrVuInfo m_vuInfo ;
protected:
	int m_indice ; //for multiple parts of same type attached to a part
	int m_dozeCounter ;
	int m_dozeAlarm ;
	static const int DOZEALARM ;
} ;

#endif //_VrModel_H
