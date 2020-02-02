/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _BbPropFactories_H
#define _BbPropFactories_H
//
//BbObstaclesFactory
//
class BbObstaclesFactory : public VrModelFactory {
public:
	BbObstaclesFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Obstacles") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrModelFactory *pFactory = BbBuilder::singleton::get().getFactory("Box") ;
		VrBuilderConfig config(pFactory, bwSize3(10, 0, 10), bwSize3(6, 3, -6), PS_STATIC) ;
		return BbBuilder::singleton::get().buildGrid(&config, pGroup) ;	
	}
} ;
//
//BbSidewalkFactory
//
class BbSidewalkFactory : public VrModelFactory {
public:
	BbSidewalkFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Sidewalk") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrModelFactory *pFactory = BbBuilder::singleton::get().getFactory("Tile") ;
		VrBuilderConfig config(pFactory, bwSize3(0, 0, 10), bwSize3(.1f, 0, .1f), style) ;
		return BbBuilder::singleton::get().buildColumn(&config, pGroup) ;	
	}
} ;
//
//BbRampFactory
//
class BbRampFactory : public VrModelFactory {
public:
	BbRampFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Ramp") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrModelFactory *pFactory = BbBuilder::singleton::get().getFactory("Tile") ;
		VrBuilderConfig config(pFactory, bwSize3(0, 0, 2), bwSize3(.1f, 0, .1f), style) ;
		VrModel *pRamp = BbBuilder::singleton::get().buildColumn(&config, pGroup) ;
		bwQuat quat ;
		set(quat, bwAxisAngle(bwRealTraits::PiDiv6, bwVector3(1,0,0))) ;
		pRamp->setQuat(quat) ;
		return pRamp ;
	}
} ;
//
//BbTilesFactory
//
class BbTilesFactory : public VrModelFactory {
public:
	BbTilesFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Tiles") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrModelFactory *pFactory = BbBuilder::singleton::get().getFactory("Tile") ;
		VrBuilderConfig config(pFactory, bwSize3(10, 0, 10), bwSize3(.1f, 0, .1f), style) ;
		return BbBuilder::singleton::get().buildGrid(&config, pGroup) ;	
	}
} ;
//
//BbParkingL1Factory
//
class BbParkingL1Factory : public VrModelFactory {
public:
	BbParkingL1Factory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("ParkingL1") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		BbParkingL1 *pLevel = new BbParkingL1(pGroup) ;
		pLevel->setFactory(this) ;
		pLevel->create(style) ;
		return pLevel ;
	}
} ;
//
//BbParkingFactory
//
class BbParkingFactory : public VrModelFactory {
public:
	BbParkingFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Parking") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		BbParking *pLevel = new BbParking(pGroup) ;
		pLevel->setFactory(this) ;
		pLevel->create(style) ;
		return pLevel ;
	}
} ;
//
//BbTileFactory
//
class BbTileFactory : public VrModelFactory {
public:
	BbTileFactory(BwKit *pKit) : VrModelFactory(pKit) {
		setName("Tile") ;
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		BbTile *pFloor = new BbTile(pGroup) ;
		pFloor->setFactory(this) ;
		pFloor->create(style) ;
		bwReal scale = 10 ;
		pFloor->setSize(scale, 1, scale) ;
		return pFloor ;
	}
} ;
//
//BbDuneFactory
//
class BbDuneFactory : public VrModelFactory {
public:
	BbDuneFactory (BwPart* pOwner, BwKit *pKit = NULL) : VrModelFactory(pOwner, pKit) {
		setName("Dune") ; 
	}
	virtual VrModel* produce(VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) {
		VrConvexMesh *pDune = new VrConvexMesh(pGroup) ;
		pDune->vuInfo().setMeshName("Dune.mesh") ;
		pDune->vuInfo().setMeshSize(bwSize3(10, 2.5, 10)) ;
		pDune->setMotionType(MOTION_STATIC) ;

		pDune->create(style) ;
		pDune->setSize(10, 2.5, 10) ;
		return pDune; 
	}
} ;

#endif //_BbPropFactories_H
