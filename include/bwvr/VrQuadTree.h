/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrQuadTree_H
#define _VrQuadTree_H

#include "VrQuad.h"

class VrQuadMesh ;

typedef boost::pool<> vrQuadPool ;

////////
//A minimalistic version ...
class VrQuadFactory : public BwFactory {
public:
	//typedef BwFactoryCommonSig CommonSig ;
	VrQuadFactory(size_t size) ;
	VrQuad* rentQuad() ;
	virtual void* rent(size_t size) ;
	virtual void release(void *pCell) ;
	//
	size_t m_quadSize ;
	vrQuadPool *p_pool ;
} ;

class VrQuadTree : public VrQuad {
public:
	VrQuadTree(VrGroup *pGroup) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createQuadFactory() ;
	virtual VrQuad* createQuad(VrGroup *pGroup, int index, int level) ;
	//TODO:implement release_quad:see VrNodeKit for reference
	void generateMesh(int level) ;
	//These next function may go into Terrain or SubTerrain classes
	void randomizeHeight(bwReal scale) ;
	int divide(bwReal minWidth) ;
	VrOmTriMesh* getMesh() { return p_mesh ; }
	VrQuad* getOuterQuad(vrCompass compass) { return m_outerQuads[compass] ; }
	int getRowCount() { return m_rowCount ; }
	int getLevelCount() { return m_levelCount ; }
	bwReal getTileUnit() { return m_tileUnit ; }
	void setMinQuadSize(bwReal size) { m_minQuadSize = size ; }
	bwReal getMinQuadSize() { return m_minQuadSize ; }
	//
	/*Data Members*/
public:	
	//vrQuadPool *p_pool ;
	VrQuadFactory* p_quadFactory ;
	bwReal m_minQuadSize ;
	int m_levelCount ; //actual levels
	int m_quadCount ; 
	int m_rowCount ;
	VrQuad* m_outerQuads[4] ;
	bwReal m_tileUnit ;
	VrOmTriMesh *p_mesh ;
};

#endif //_VrQuadTree_H
