#ifndef _BwcReader_H
#define _BwcReader_H

#include <bwkernel/BwPart.h>

class VrGroup ;
class VrShape ;

typedef domRigid_body::domTechnique_common::domShapeRef bwcShapeRef ;

namespace Ogre {
	class Material ;
}
//
class BwcImageLib ;
class BwcGeometryLib ;
class BwcMaterialLib ;
class BwcEffectLib ;

class BwcNode ;
class BwcGeometry ;
class BwcInstanceGeometry ;
class BwcPolyGroup ;
class BwcMaterial ;
class BwcEffect ;
//
class BwcReader : public BwPart {
public:
	BwcReader(BwPart* pOwner, VrGroup* pGroup, const bwString& name) ;
	void read(const bwPath& path) ;
	void readAssets() ;
	void readImages() ;
	void readImage(domImageRef lib) ;
	void readGeometries() ;
	void readGeometry(domGeometryRef geomRef) ;
	void readMesh(domGeometryRef geomRef) ;
	void readTriangles(BwcGeometry* pGeom) ;
	void readVertices(BwcPolyGroup* pPolyGroup, const domListOfUInts indexArray, domInputLocalRef localRef) ;
	void readNormals(BwcPolyGroup* pPolyGroup, const domListOfUInts indexArray, domInputLocalRef localRef) ;
	void readTextureCoords(BwcPolyGroup* pPolyGroup) ;
	void readPolygons(BwcGeometry* pGeom, const domPolygons_Array& polygons, domVerticesRef vertsRef) ;
	void readPolygon(BwcGeometry* pGeom, domPolygonsRef polyRef, domPRef pRef, domVerticesRef vertsRef) ;
	bool getInputInfo(BwcPolyGroup* pPolyGroup, 
					  const char* semantic, 
					  int& sourceIndex, 
					  int& inputOffset) ;
	//
	void readScenes() ;
	void readScene(domVisual_sceneRef scene) ;
	BwcNode* readNode(domNodeRef node, BwcNode* parentNode) ;
	void readNodeTransform(domNodeRef node, BwcNode* pNode) ;
	void readNodeMatrix(domNodeRef node, BwcNode* pNode) ;
	void readNodeTranslation(domNodeRef node, BwcNode* pNode) ;
	void readNodeRotation(domNodeRef node, BwcNode* pNode) ;
	void readNodeScale(domNodeRef node, BwcNode* pNode) ;
	//
	void addNode(const bwString& name, BwcNode* pNode) { m_nodes[name] = pNode ; }
	BwcNode* getNode(const bwString& name) { return m_nodes[name] ; }
	//
	void readPhysics() ;
	void readModels(domPhysics_sceneRef physicsSceneRef) ;
	void readModel(domInstance_physics_modelRef instance_physicsModelRef) ;
	void readBodies(domInstance_physics_modelRef instance_physicsModelRef) ;
	void readBody(domPhysics_modelRef model, domInstance_rigid_bodyRef rigidbodyRef) ;
	void readShape(bwcShapeRef shapeRef, BwcNode* pNode) ;
	void readConcave(domGeometryRef geomRef) ;
	void readConvex(domGeometryRef geomRef) ;
	//
	void readMaterials() ;
	void readMaterial(domMaterialRef lib) ;
	void readEffects() ;
	void readEffect(domEffectRef lib) ;
	void applyEffect(BwcMaterial& material, BwcEffect& effect) ;
	//
	void prepShape(BwcNode* pNode) ;
	//
	bwPoint3 makePoint(bwReal x, bwReal y, bwReal z) {
		if(m_yIsUp) return bwPoint3(x, y, z) * m_unit ;
		//else
		return bwPoint3(x, z, -y) * m_unit;
	}
	bwVector3 makeVector(bwReal x, bwReal y, bwReal z) {
		if(m_yIsUp) return bwVector3(x, y, z) * m_unit ;
		//else
		return bwVector3(x, z, -y)  * m_unit ;
	}
	bwSize3 makeSize(bwReal x, bwReal y, bwReal z) {
		if(x == 0) x = 1 ; if(y == 0) y = 1 ; if(z == 0) z = 1 ;
		if(m_yIsUp) return bwSize3(x, y, z) * m_unit ;
		//else
		return bwSize3(x, z, y) * m_unit ;
	}
	bwSize3 makeSize(const bwSize3& size) {
		return makeSize(size[0], size[1], size[2]) ;
	}
	bwSize3 makeScale(bwReal x, bwReal y, bwReal z) {
		if(x == 0) x = 1 ; if(y == 0) y = 1 ; if(z == 0) z = 1 ;
		if(m_yIsUp) return bwSize3(x, y, z) ;
		//else
		return bwSize3(x, z, y) ;
	}
	bwSize3 makeScale(const bwSize3& size) {
		return makeScale(size[0], size[1], size[2]) ;
	}
	//TODO:implement yIsUp code.
	bwMatrix3x3 makeMatrix(bwReal v00, bwReal v01, bwReal v02,
             bwReal v10, bwReal v11, bwReal v12,
             bwReal v20, bwReal v21, bwReal v22) {
		bwMatrix3x3 temp ;
		temp.set(v00, v01, v02, v10, v11, v12, v20, v21, v22);
		return temp ;
	}
	bwAxisAngle makeAxisAngle(bwReal angle, bwReal x, bwReal y, bwReal z) {
		bwVector3 v = makeVector(x, y, z) ;
		normalize(v) ;
		return bwAxisAngle(angle, v) ;
	}
	//
	BwcImageLib& imageLib() { return *p_imageLib ; }
	BwcGeometryLib& geometryLib() { return *p_geometryLib ; }
	BwcMaterialLib& materialLib() { return *p_materialLib ; }
	BwcEffectLib& effectLib() { return *p_effectLib ; }
	//Data Members
	DAE* collada ;
	domCOLLADA* dom ;
	//
	VrGroup* p_topGroup ;
	BwcNode* p_root ;
	std::map<std::string, BwcNode*> m_nodes ;
	//Asset
	bool m_yIsUp ;
	bwReal m_unit ;
	//
	BwcImageLib* p_imageLib ;
	BwcGeometryLib* p_geometryLib ;
	BwcMaterialLib* p_materialLib ;
	BwcEffectLib* p_effectLib ;
} ;
///////////
inline bwPath convert_fileURI(const bwString& uriRef) {
	bwPath path(cdom::uriToNativePath(uriRef, cdom::Windows), boost::filesystem::no_check) ;
	if(path.empty())
		return bwPath(uriRef) ;
	//else
	return path ;
}

#endif //_BwcReader_H