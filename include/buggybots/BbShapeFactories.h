/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbShapeFactories_H
#define _BbShapeFactories_H

#include <bwvr/VrBox.h>
#include <bwvr/VrHexahedron.h>
#include <bwvr/VrCylinder.h>
#include <bwvr/VrCapsule.h>
#include <bwvr/VrTetrahedron.h>

////////////////////////////////////////
class BbBallFactory ;
class BbBallKit ;

//
//BbBallFactory
//
class BbBall : public VrBall {
public:
	BbBall(VrGroup *pGroup) : VrBall(pGroup) {}
} ;
class BbBallFactory : public VrModelFactory {
public:
	BbBallFactory(BwKit *pKit) : VrModelFactory(pKit) { 
		setName("Ball") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		BbBall *pBall = new BbBall(pGroup) ;
		pBall->create(style) ;
		bwReal scale = 2 ;
		pBall->setSize(scale, scale, scale) ;
		pBall->bodyInfo().setAngularDrag(-100) ;
		return pBall ;
	}
} ;
//
//BbBoxFactory
//
class BbBox : public VrBox {
public:
	BbBox(VrGroup *pGroup) : VrBox(pGroup) {}
} ;
class BbBoxFactory : public VrModelFactory {
public:
	BbBoxFactory(BwKit *pKit) : VrModelFactory(pKit) { 
		setName("Box") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		BbBox *pBox = new BbBox(pGroup) ;
		pBox->create(style) ;
		bwReal scale = 2 ;
		pBox->setSize(scale, scale, scale) ;
		return pBox; 
	}
} ;
//
//BbSuzanneFactory
//
class BbSuzanneFactory : public VrModelFactory {
public:
	BbSuzanneFactory(BwKit *pKit) : VrModelFactory(pKit) { 
		setName("Suzanne") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrConcaveMesh* pModel = new VrConcaveMesh(pGroup) ;
		pModel->vuInfo().setMeshName("Suzanne.mesh") ;
		pModel->create(style) ;
		bwReal scale = 2 ;
		pModel->setSize(scale, scale, scale) ;
		return pModel; 
	}
} ;
//
//BbTetraFactory
//
class BbTetraFactory : public VrModelFactory {
public:
	BbTetraFactory (BwKit *pKit) : VrModelFactory(pKit) { 
		setName("Tetrahedron") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrTetrahedron *pModel = new VrTetrahedron(pGroup) ;

		bwPoint3 p1(0, -1, -1) ;
		bwPoint3 p2(1, -1, 1) ;
		bwPoint3 p3(-1, -1, 1) ;
		bwPoint3 p4(0, 1, 0) ;

		pModel->setPoint(0, p1) ;
		pModel->setPoint(1, p2) ;
		pModel->setPoint(2, p3) ;
		pModel->setPoint(3, p4) ;
		
		pModel->create(style) ;

		return pModel ; }
} ;
//
//BbHexaFactory
//
class BbHexaFactory : public VrModelFactory {
public:
	BbHexaFactory (BwKit *pKit) : VrModelFactory(pKit) { 
		setName("Hexahedron") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrHexahedron *pModel = new VrHexahedron(pGroup) ;

		bwPoint3 p1(-1, 1, 1) ;
		bwPoint3 p2(1, 1, 1) ;
		bwPoint3 p3(1, 1, -1) ;
		bwPoint3 p4(-1, 1,- 1) ;

		pModel->setPoint(0, p1) ;
		pModel->setPoint(1, p2) ;
		pModel->setPoint(2, p3) ;
		pModel->setPoint(3, p4) ;

		pModel->setPoint(4, bwPoint3(p1[0]*1.5, p1[1] - 2, p1[2]*1.5)) ;
		pModel->setPoint(5, bwPoint3(p2[0]*1.5, p2[1] - 2, p2[2]*1.5)) ;
		pModel->setPoint(6, bwPoint3(p3[0]*1.5, p3[1] - 2, p3[2]*1.5)) ;
		pModel->setPoint(7, bwPoint3(p4[0]*1.5, p4[1] - 2, p4[2]*1.5)) ;

		pModel->create(style) ;

		return pModel ; }
} ;
//
//BbCylinderFactory
//
class BbCylinderFactory : public VrModelFactory {
public:
	BbCylinderFactory(BwKit *pKit) : VrModelFactory(pKit) { 
		setName("Cylinder") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrCylinder *pObject = new VrCylinder(pGroup) ;
		pObject->create(style) ;
		return pObject ; 
	}
} ;
//
//BbCapsuleFactory
//
class BbCapsuleFactory : public VrModelFactory {
public:
	BbCapsuleFactory(BwKit *pKit) : VrModelFactory(pKit) { 
		setName("Capsule") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrCapsule *pCapsule = new VrCapsule(pGroup) ;
		pCapsule->create(style) ;
		pCapsule->setSize(2, 2, 4) ;
		return pCapsule ; 
	}
} ;
//
//BbConeFactory
//
class BbConeFactory : public VrModelFactory {
public:
	BbConeFactory(BwKit *pKit) : VrModelFactory(pKit) { 
		setName("Cone") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrConvexMesh *pCone = new VrConvexMesh(pGroup) ;
		pCone->vuInfo().setMeshName("VrCone.mesh") ;
		pCone->create(style) ;
		return pCone; 
	}
} ;
//
//BbTorusFactory
//
class BbTorusFactory : public VrModelFactory {
public:
	BbTorusFactory(BwKit *pKit) : VrModelFactory(pKit) { 
		setName("Torus") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrConcaveMesh *pTorus = new VrConcaveMesh(pGroup) ;
		pTorus->vuInfo().setMeshName("Torus.mesh") ;
		pTorus->create(style) ;
		bwReal scale = 1 ;
		pTorus->setSize(2, .5, 2) ;
		return pTorus ; 
	}
} ;
//
//BbTorusFactory
//
class BbBunnyFactory : public VrModelFactory {
public:
	BbBunnyFactory(BwKit *pKit) : VrModelFactory(pKit) { 
		setName("Bunny") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		BbBunny *pModel = new BbBunny(pGroup) ;
		pModel->create(style) ;
		//bwReal scale = 1 ;
		//pModel->setSize(2, .5, 2) ;
		return pModel ; 
	}
} ;
#endif //_BbShapeFactories_H
