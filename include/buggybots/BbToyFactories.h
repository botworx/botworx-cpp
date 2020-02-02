/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbToyFactories_H
#define _BbToyFactories_H

#include <bwvr/VrFixedAssembly.h>
//
//BbToy1Factory
//
class BbToy1Factory : public VrModelFactory {
public:
	BbToy1Factory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Toy1") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrModel *pModel = NULL ;
		VrBuilder *pBuilder = VrBuilder::singleton::getPtr() ;
		VrFixedAssembly *pToy = new VrFixedAssembly(pGroup) ;
		pToy->setIsEntity(true) ;
		pToy->create(style) ;
		pModel = pBuilder->getFactory("Ball")->produce(pToy) ;
		pModel->setSize(2.25, 2.25, 2.25) ;
		pModel = pBuilder->getFactory("Ball")->produce(pToy) ;
		pModel->setSize(2.25, 2.25, 2.25) ;
		pModel->setRelPos(0,0,-2) ;
		//
		pModel = pBuilder->getFactory("Ball")->produce(pToy) ;
		pModel->setSize(2.25, 2.25, 2.25) ;
		pModel->setRelPos(0,0,6) ;

		return pToy ;
	}
} ;
//
//BbToy2Factory
//
class BbToy2Factory : public VrModelFactory {
public:
	BbToy2Factory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Toy2") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrModel *pModel = NULL ;
		VrBuilder *pBuilder = VrBuilder::singleton::getPtr() ;
		VrFixedAssembly *pToy = new VrFixedAssembly(pGroup) ;
		pToy->setIsEntity(true) ;
		pToy->create(style) ;
		/*pModel = pBuilder->getFactory("Ball")->produce(pToy) ;
		pModel->setSize(2.25, 2.25, 2.25) ;*/

		pModel = pBuilder->getFactory("Box")->produce(pToy) ;
		pModel->setSize(1, 4, 1) ;
		pModel->setRelPos(-2,0,-2) ;
		//
		pModel = pBuilder->getFactory("Box")->produce(pToy) ;
		pModel->setSize(1, 4, 1) ;
		pModel->setRelPos(2,1,-2) ;
		//	
		pModel = pBuilder->getFactory("Box")->produce(pToy) ;
		pModel->setSize(1, 4, 1) ;
		pModel->setRelPos(2,0,2) ;

		pModel = pBuilder->getFactory("Box")->produce(pToy) ;
		pModel->setSize(1, 4, 1) ;
		pModel->setRelPos(-2,1,2) ;

		//Top
		pModel = pBuilder->getFactory("Box")->produce(pToy) ;
		pModel->setSize(4, 1, 4) ;
		pModel->setRelPos(0,2,0) ;

		//Ball on Top
		pModel = pBuilder->getFactory("Box")->produce(pToy) ;
		pModel->setSize(4, 4, 4) ;
		pModel->setRelPos(-2,4,2) ;

		return pToy ;
	}
} ;
//
//BbToy3Factory
//
class BbToy3Factory : public VrModelFactory {
public:
	BbToy3Factory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Toy3") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrModel *pShape = NULL ;
		//Doodad
		VrBuilder *pBuilder = VrBuilder::singleton::getPtr() ;
		VrFixedAssembly *pToy = new VrFixedAssembly(pGroup) ;
		pToy->setIsEntity(true) ;
		pToy->create(style) ;

		pShape = pBuilder->build("Ball", pToy) ;
		pShape->setSize(2, 2, 2) ;
		pShape->setRelPos(-2,0,0) ;
		//
		pShape = pBuilder->build("Ball", pToy) ;
		pShape->setSize(2, 2, 2) ;
		pShape->setRelPos(2,0,0) ;
		//Top
		pShape = pBuilder->build("Box", pToy) ;

		pShape->setSize(8, .25, 32) ;
		pShape->setRelPos(0,2,0) ;

		return pToy ;
	}
} ;
//
//BbToy4Factory
//
class BbToy4Factory : public VrModelFactory {
public:
	BbToy4Factory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Toy4") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrModel *pModel = NULL ;
		VrBuilder& builder = VrBuilder::singleton::get() ;
		VrFixedAssembly *pToy = new VrFixedAssembly(pGroup) ;
		pToy->setIsEntity(true) ;
		pToy->create(style) ;
		//
		for(float i = 0 ; i < M_PI*2 ; i += M_PI/4) {
			pModel = builder.getFactory("Box")->produce(pToy) ;
			pModel->setSize(.5, .5, 2) ;
			bwQuat quat ;
			set(quat, bwAxisAngle(i, bwVector3(0,1,0))) ;
			//pModel->setRay(bwPoint3(), quat) ;
			pModel->setRelQuat(quat) ;
		}
		return pToy ;
	}
} ;
//
//BbToy5Factory
//
class BbToy5Factory : public VrModelFactory {
public:
	BbToy5Factory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Toy5") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrModel *pModel = NULL ;
		VrBuilder& builder = VrBuilder::singleton::get() ;
		VrDynamicAssembly *pToy = new VrDynamicAssembly(pGroup) ;
		pToy->setIsEntity(true) ;
		pToy->create(style) ;
		//
		for(float i = 0 ; i < M_PI*2 ; i += M_PI/4) {
			pModel = builder.getFactory("Box")->produce(pToy) ;
			pModel->setSize(.5, .5, 2) ;
			bwQuat quat ;
			set(quat, bwAxisAngle(i, bwVector3(0,1,0))) ;
			//pModel->setRay(bwPoint3(), quat) ;
			pModel->setRelQuat(quat) ;
		}
		return pToy ;
	}
} ;

#endif //_BbToyFactories_H
