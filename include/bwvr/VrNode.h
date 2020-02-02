/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrNode_H
#define _VrNode_H

class VrNodeKit ;
class VrCollider ;
//
class VrShape ;

class VrNode {
public:
	VrNode(VrModel *pModel) ;
	void fit() ;
	virtual void validate() ;
	void setCollider(VrCollider *pCollider) { p_collider = pCollider; }
	VrCollider* getCollider() { return p_collider ; }
	//
	void setTestInternal(bool val) { m_testInternal = val ; }
	bool testInternal() { return m_testInternal ; }
	void setIsEntity(bool val) { m_isEntity = val ; if(val) p_entity = this ; }
	bool isEntity() { return m_isEntity ; }
	void setEntity(VrNode *pEntity) { p_entity = pEntity ; }
	VrNode* getEntity() { return p_entity ; }

	VrNode *p_entity ; //This represents the root of a coherent group such as a robot.
	bool m_isEntity ;
	//
	virtual void attachNode(VrNode *pNode) ;
	virtual void detachNode(VrNode *pNode) ;
	//
	void setPose(const bwPose& pose) { m_pose = pose ; }
	const bwPose& getPose() { return m_pose ; }
	void setPos(const bwPoint3& pos) { m_pose.m_pos = pos ; }
	void setPos(bwReal x, bwReal y, bwReal z) { setPos(bwPoint3(x,y,z)) ; }
	const bwPoint3& getPos() { return m_pose.m_pos ; }
	void setQuat(const bwQuat& quat) { m_pose.m_quat = quat ; }
	const bwQuat& getQuat() { return m_pose.m_quat ; }
	//Box
	void setBounds(const bwBounds3& box) { m_bounds = box ; }
	const bwBounds3& getBounds() { return m_bounds ; }
	void setMin(const bwPoint3& point) { m_bounds.setMin(point) ; }
	void setMax(const bwPoint3& point) { m_bounds.setMax(point) ; }
	const bwPoint3& getMin() { return m_bounds.getMin() ; }
	const bwPoint3& getMax() { return m_bounds.getMax() ; }
	//Sphere
	bwReal getRadius() { return m_radius ; }
	//Ray
	bwRay getRay() ;
	//LineSeg
	bwLine getLineSeg() ;
	//
	void collide(VrNode *pCollider, bool recursive = true) ;
	bool testOverlap(VrNode *pNode) ;
	void processOverlap(VrNode *pNode) ;
	void migrate() ;
	void host(VrNode *pMigrant) ;
	void setIsMigrating(bool val) { m_isMigrating = val ; }
	bool isMigrating() { return m_isMigrating ; }
	//
	void testMigrant(VrNode *pMigrant) ;
	//
	nodeType m_nodeType ;
	void setNodeType(nodeType type) { m_nodeType = type ; }
	nodeType getNodeType() { return m_nodeType ; }
	//
	bool isGroup() { return m_nodeType == NODE_GROUP ; }
	bool isPlace() { return m_nodeType == NODE_PLACE ; }
	//
	VrModel* p_model ;
	//void setModel(VrModel* pModel) { p_model = pModel ; }
	VrModel* getModel() { return p_model ; }
	//Data
public:
	VrNode	*p_parent ;
	VrNode	*p_next ;
	VrNode	*p_child ;
	VrCollider *p_collider ;
	//
	bwPose m_pose ;
	//AABB
	bwBounds3 m_bounds ;

	//Bounding Sphere
	bwReal m_radius ; //bounding radius
	bool m_testInternal ;
	bool m_isMigrant ;
	bool m_isMigrating ;
	//Inliners
	bool testSphereRay(VrNode *pNode) ;
	bool testSphereLineSeg(VrNode *pNode) ;
	bool testBoxRay(VrNode *pNode) ;
	bool testBoxLineSeg(VrNode *pNode) ;
	bool testSphereSphere(VrNode *pNode) {
		/*bwSphere s1(m_pos, m_radius) ;
		bwSphere s2(pNode->m_pos, pNode->m_radius) ;
		return gmtl::intersect(s1, s2) ;*/
		//TODO:replace with gmtl impl

		bwReal tempDistance = (m_radius + pNode->getRadius()) ;
		const bwPoint3& pos1 = getPos() ;
		const bwPoint3& pos2 = pNode->getPos() ;

		if (sqrt(((pos2[0] - pos1[0])*(pos2[0] - pos1[0]))+
					((pos2[1] - pos1[1])*(pos2[1] - pos1[1]))+
					((pos2[2] - pos1[2])*(pos2[2] - pos1[2]))
					) < tempDistance )
			return true ;
		else
			return false ;
	}
	bool testSphereInSphere(VrNode *pNode) {
		bwReal tempDistance = m_radius ;
		const bwPoint3& pos1 = getPos() ;
		const bwPoint3& pos2 = pNode->getPos() ;
		if (((sqrt(((pos2[0] - pos1[0])*(pos2[0] - pos1[0]))+
					((pos2[1] - pos1[1])*(pos2[1] - pos1[1]))+
					((pos2[2] - pos1[2])*(pos2[2] - pos1[2]))
					)) + pNode->getRadius() ) < tempDistance )
			return true ;
		else
			return false ;
	}

	bool testBoxBox(VrNode* pNode) {
		return intersect(m_bounds, pNode->getBounds()) ;
	}
	bool testBoxInBox(VrNode *pNode) {
		/*bwBounds3 box1(getWorldMin(), getWorldMax()) ;
		bwBounds3 box2(pNode->getWorldMin(), pNode->getWorldMax()) ;
		return gmtl::isInVolume(box1, box2) ;*/
		bool success = false ;
		bwPoint3 min1, max1, min2, max2 ;

		min1 = getMin() ;
		max1 = getMax() ;
		min2 = pNode->getMin() ;
		max2 = pNode->getMax() ;

		if( ( min1[0] < min2[0] ) &&
			( min1[1] < min2[1] ) &&
			( min1[2] < min2[2] ) &&
			( max1[0] > max2[0] ) &&
			( max1[1] > max2[1] ) &&
			( max1[2] > max2[2] ) )
			success = true ;
		else
			success = false ;

		return success;
	}
///////////////
	bool testBox(VrNode *pNode) {
		switch(pNode->m_nodeType) {
			case NODE_BOX :
				return testBoxBox(pNode) ;
			case NODE_BALL :
				return testBoxBox(pNode) ;
			case NODE_RAY :
				return testBoxRay(pNode) ;
			case NODE_LINESEG :
				return testBoxLineSeg(pNode) ;
			default :
				return testBoxBox(pNode) ;
		}
		return false ;
	}
	bool testBall(VrNode *pNode) {
		switch(pNode->m_nodeType) {
			case NODE_BOX :
				return testBoxBox(pNode) ;
			case NODE_BALL :
				return testSphereSphere(pNode) ;
			case NODE_RAY :
				return testSphereRay(pNode) ;
			case NODE_LINESEG :
				return testSphereLineSeg(pNode) ;
			default :
				return testBoxBox(pNode) ;
		}
		return false ;
	}
	bool testMesh(VrNode *pNode) {
		switch(pNode->m_nodeType) {
			case NODE_BOX :
				return testBoxBox(pNode) ;
			case NODE_BALL :
				return testBoxBox(pNode) ;
			case NODE_CONVEXMESH :
			case NODE_CONCAVEMESH :
				return testBoxBox(pNode) ;
			case NODE_RAY :
				return testBoxRay(pNode) ;
			case NODE_LINESEG :
				return testBoxLineSeg(pNode) ;
			default :
				return testBoxBox(pNode) ;
		}
		return false ;
	}
	bool testRay(VrNode *pNode) {
		switch(pNode->m_nodeType) {
			case NODE_BOX :
				return testBoxRay(pNode) ;
			case NODE_BALL :
				return testSphereRay(pNode) ;
			case NODE_RAY :
			case NODE_LINESEG :
				return testBoxBox(pNode) ;
			default :
				return testBoxRay(pNode) ;
		}
		return false ;
	}
	bool testLineSeg(VrNode *pNode) {
		switch(pNode->m_nodeType) {
			case NODE_BOX :
				return testBoxLineSeg(pNode) ;
			case NODE_BALL :
				return testSphereLineSeg(pNode) ;
			case NODE_RAY :
			case NODE_LINESEG :
				return testBoxBox(pNode) ;
			default :
				return testBoxLineSeg(pNode) ;
		}
		return false ;
	}
};

#endif //_VrNode_H
