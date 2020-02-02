/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrShape_H
#define _VrShape_H

#include "VrModel.h"
#include "VrSurfaceInfo.h"

class VrGroup ;
class VrBody ;
class VrCollider ;
class VrCollision ;
class VrTriMeshData ;

class VrShape : public VrModel {
public:
	VrShape(VrGroup *pGroup) ;
	virtual ~VrShape() ;
	virtual bwString getClassName() { return "VrShape" ; }
	//
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doValidate() ;
	virtual void createCollider() ;
	virtual void doEnable(bool sleeping = false) ;
	virtual void doDisable(bool sleeping = true) ;
	//Geom
	virtual void createGeom() ;
	virtual void enableGeom() ;
	virtual void disableGeom() ;
	virtual void validateGeom() ;
	void setGeomPos(const bwPoint3& pos) ;
	void setGeomQuat(const bwQuat &pQuat) ;
	dGeomID getGeomID() { return m_geomID ; }
	//Convex
	virtual void createConvex() ;
	virtual void validateConvex() ;
	dGeomID getConvex() { return p_convex ; }
	//
	VrSurfaceInfo& getSurfaceInfo() { return m_surfaceInfo ; }

	void embed() ; //make embedded
	//Data Members
protected:
	VrSurfaceInfo m_surfaceInfo ;
	//Geom
	dGeomID m_geomID ;
	//Convex
	dGeomID p_convex ;
} ;
#endif //_VrShape_H