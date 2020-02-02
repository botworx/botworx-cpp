#ifndef _BwcNode_H
#define _BwcNode_H

class BwcInstanceGeometry ;

class BwcNode : public BwPart {
public:
	BwcNode(BwcNode* pParent) 
		: BwPart(pParent),
		p_model(0), 
		m_size(bwVector3(1,1,1)), 
		m_scale(bwVector3(1,1,1)),
		m_motionType(MOTION_STATIC),
		m_mass(1.f)
	{
	}
	//
	BwcNode* getParent() { return ((BwcNode*)p_owner) ; }
	//
	void setId(const bwString& id) { m_id = id ; }
	bwString getId() { return m_id ; }
	//
	void setSid(const bwString& id) { m_sid = id ; }
	bwString getSid() { return m_sid ; }
	//
	void setSize(const bwSize3 size) { m_size = size ; }
	bwSize3 getSize() { return m_size ; }
	void setScale(const bwSize3 scale) { m_scale = scale ; }
	bwSize3 getScale() { return m_scale ; }
	//
	void setPos(const bwPoint3& pos) { m_pos = pos ; }
	bwPoint3 getPos() { return m_pos ; }
	void setQuat(const bwQuat& quat) { m_quat = quat ; }
	bwQuat getQuat() { return m_quat ; }
	//
	void setMotionType(motionType type) { m_motionType = type ; }
	motionType getMotionType() { return m_motionType ; }
	//
	void setMass(bwReal mass) { m_mass = mass ; }
	bwReal getMass() { return m_mass ; }
	//
	void addChild(BwcNode* pChild) { m_children.push_back(pChild) ; }
	//
	void addVuGeometry(BwcInstanceGeometry* pGeom) { m_vuGeoms.push_back(pGeom) ; }
	BwcInstanceGeometry* firstVuGeometry() { return m_vuGeoms.front() ; }
	bool hasVuGeometries() { return !m_vuGeoms.empty() ; }
	//
	void addColGeometry(BwcInstanceGeometry* pGeom) { m_colGeoms.push_back(pGeom) ; }
	BwcInstanceGeometry* firstColGeometry() { return m_colGeoms.front() ; }
	bool hasColGeometries() { return !m_colGeoms.empty() ; }
	//
	void setModel(VrModel* pModel) { p_model = pModel ; }
	VrModel* getModel() { return p_model ; }
	//
	void build(BwcReader& rdr) ;
	void buildChildren(BwcReader& rdr) ;
	//Data Members
	bwString m_id ;
	bwString m_sid ;
	//
	bwSize3 m_size ;
	bwSize3 m_scale ;
	bwPoint3 m_pos ;
	bwQuat m_quat ;
	//
	motionType m_motionType ;
	bwReal m_mass ;
	//
	VrModel* p_model ;
	//
	std::list<BwcNode*> m_children ;
	std::list<BwcInstanceGeometry*> m_vuGeoms ;
	std::list<BwcInstanceGeometry*> m_colGeoms ;
} ;
typedef std::map<bwString, BwcNode*> BwcNodeMap ;
typedef BwcNodeMap::iterator BwcNodeMapIter ;

//
class BwcNodeLib : public BwPart {
public:
	BwcNodeLib(BwPart* pOwner) : BwPart(pOwner) {}
	BwcNode* createNode(BwcNode* pParent) ;
	void addNode(BwcNode* pNode) ;
	BwcNode* findNode(const bwString& name) ;
	//Data Members
	BwcNodeMap m_nodeMap ;
} ;

#endif _BwcNode_H