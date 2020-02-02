#ifndef _BwcGeometry_H
#define _BwcGeometry_H

#include "BwcPolyGroup.h"

class BwcGeometry : public BwPart {
public:
	BwcGeometry(BwPart* pOwner) : BwPart(pOwner) { 
		m_type = GEOM_BAD ;
	}
	void setElement(const domGeometryRef pElement) { p_element = pElement ; }
	domGeometryRef getElement() { return p_element ; }
	void setMesh(const domMeshRef pMesh) { p_mesh = pMesh ; }
	domMeshRef getMesh() { return p_mesh ; }
	void setConvexMesh(const domConvex_meshRef pMesh) { p_convexMesh = pMesh ; }
	domConvex_meshRef getConvexMesh() { return p_convexMesh ; }
	//
	domTriangles_Array &getTriangles_array() ;
	const domVerticesRef getVertices() const ;
	domSource_Array &getSource_array() ;
	//
	void setSize(const bwSize3& size) { m_size = size ; }
	bwSize3 getSize() { return m_size ; }
	//
	void setMaterialSymbol(const bwString& materialSymbol) { m_materialSymbol = materialSymbol ; }
	bwString getMaterialSymbol() { return m_materialSymbol ; }
	enum geomType {
		GEOM_BAD = 0,
		GEOM_TRIANGLES,
		GEOM_POLYGONS
	} ;
	void setType(geomType type) { m_type = type ; }
	geomType getType() { return m_type ; }
	bool isBad() { return m_type == GEOM_BAD ; }
	bool isGood() { return !isBad() ; }
	//
	void addPolyGroup(BwcPolyGroup* pPolyGroup) ;
	//Data Members
	bwString m_materialSymbol ;
	geomType m_type ;
	bwSize3 m_size ;
	//
	domGeometryRef p_element ; 
	domMeshRef p_mesh ;
	domConvex_meshRef p_convexMesh ;
	//
	BwcPolyGroups m_polyGroups ;
} ;
typedef std::map<bwString, BwcGeometry*> BwcGeometryMap ;
typedef BwcGeometryMap::iterator BwcGeometryMapIter ;
//
class BwcInstanceMaterial ;

class BwcInstanceGeometry : public BwPart {
public:
	BwcInstanceGeometry(BwcNode* pNode, BwcGeometry* pOriginal) : BwPart((BwPart*)pNode), p_original(pOriginal) {}
	//
	BwcGeometry* getOriginal() { return p_original ; }
	bool isBad() { return p_original->isBad() ; }
	bool isGood() { return !p_original->isBad() ; }
	//
	void build() ;
	//
	void setMeshName(const bwString& name) { m_meshName = name ; }
	bwString getMeshName() { return m_meshName ; }
	void setMaterialName(const bwString& name) { m_materialName = name ; }
	bwString getMaterialName() { return m_materialName ; }
	//
	void addInstanceMaterial(BwcInstanceMaterial* pMaterial) ;
	BwcInstanceMaterial* getInstanceMaterial(const bwString& symbol) { return m_instanceMaterials[symbol] ; }
	//Data Members
	BwcGeometry* p_original ;
	bwString m_meshName ;
	bwString m_materialName ;

	std::map<bwString, BwcInstanceMaterial*> m_instanceMaterials ;
} ;
//
class BwcGeometryLib : public BwPart {
public:
	BwcGeometryLib(BwPart* pOwner) : BwPart(pOwner) {}
	BwcGeometry* createGeometry() ;
	void addGeometry(BwcGeometry* pGeom) ;
	BwcGeometry* findGeometry(const bwString& name) ;
	//Data Members
	BwcGeometryMap m_geometryMap ;
} ;

#endif //_BwcGeometry_H