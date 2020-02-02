/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrTriMesh_H
#define _VrTriMesh_H

#include "VrGroup.h"
#include "VrShape.h"

class VrTriMeshData ;

class VrTriMesh : public VrShape {
public:
	VrTriMesh(VrGroup *pGroup) ;
	virtual bwString getClassName() { return "VrTriMesh" ; }
	virtual void doCreate(const BwPartInfo& info) ;
	//
	virtual void createTriMeshData() ;
	virtual void generateMesh() ;
	virtual void validateMass() ;
	//
	virtual void createGeom() ;
	virtual void validateGeom() ;
	void buildMeshData() ;
	void captureTransform() ;
	//
	virtual void doPostEnable(bool sleeping = false) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	//
	void setTriMeshData(VrTriMeshData* pTriMeshData) { p_triMeshData = pTriMeshData ; }
	VrTriMeshData* getTriMeshData() { return p_triMeshData ; }	
	//Data Members
	VrTriMeshData* p_triMeshData ;
	dTriMeshDataID m_meshDataID ;
};

#endif //_VrTriMesh_H
