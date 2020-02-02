/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _CrawlerLegSeg_H
#define _CrawlerLegSeg_H

#include <bwvr/VrBox.h>
#include <bwvr/VrMech.h>
class VrRod ;

#include <bwvr/VrHinge.h>
////////////////////////////////////////////////////
namespace Crawler {
//////////////////////////
class CrawlerChassis ;
class CrawlerLegMotor ;
//
//CrawlerLegSegFactory
//
class CrawlerLegSegFactory : public BwFactory {
public:
	CrawlerLegSegFactory(BwPart* pOwner, BwKit *pKit = NULL) ;
	CrawlerLegSeg* createLegSeg(CrawlerLeg *pLeg, int indice) ;
public:
	//Data
	int m_segIndice ;
	bwReal m_legRadius;
	bwReal m_legLength ;
	bwPoint3 m_followPos[2] ;
	bwReal m_legDensity;
	bwReal m_legJointERP;
	bwReal m_legJointCFM;
} ;
//
//CrawlerLegSeg1Factory
//
class CrawlerLegSeg1Factory : public CrawlerLegSegFactory {
public:
	CrawlerLegSeg1Factory(BwKit *pKit) ;
	//Singleton support
public:
	struct singleton_alloc {
		static CrawlerLegSeg1Factory* alloc() ;
	} ;
	typedef BwAutoSingletonT<CrawlerLegSeg1Factory, singleton_alloc> singleton ;
	singleton m_singleton ;
};
//
//CrawlerLegSeg2Factory
//
class CrawlerLegSeg2Factory : public CrawlerLegSegFactory {
public:
	CrawlerLegSeg2Factory(BwKit *pKit) ;
	//Singleton support
public:
	struct singleton_alloc {
		static CrawlerLegSeg2Factory* alloc() ;
	} ;
	typedef BwAutoSingletonT<CrawlerLegSeg2Factory, singleton_alloc> singleton ;
	singleton m_singleton ;
};
//
//CrawlerLegSegMech
//
class CrawlerLegMotorBrain ;

class CrawlerLegSegMech : public VrMotorizedJointMech {
public:
	CrawlerLegSegMech(CrawlerLegSeg *pSeg) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void doConfig() ;
	virtual void doPostEnable(bool sleeping = false) ;
	void createJoint(VrModel *pModel) ;
	void setSegPosition() ;
	//
	CrawlerBrain& master() { return *static_cast<CrawlerBrain*>(p_master) ; }
	//Data Members
	CrawlerLegSeg *p_seg ;
	//
	CrawlerLegMotorBrain *p_mech_1 ;
	CrawlerLegMotorBrain *p_mech_2 ;
} ;
//
//CrawlerLegSeg
//
class CrawlerLegSeg : public VrBox {
public:
	CrawlerLegSeg(CrawlerLeg *pLeg, int indice, int segIndice) ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createBrain() ;
	virtual bool onCreate(const BwPartInfo& info) ;
	CrawlerLegSegFactory& factory() { return *static_cast<CrawlerLegSegFactory*>(p_factory) ; }
	virtual bwString getClassName() { return "Leg" ; }
	virtual void createGeom() ;
	virtual void attachTo(VrModel *pLeader) ;
	CrawlerLegSegMech& brain() { return *static_cast<CrawlerLegSegMech*>(p_brain) ; }
	/*Data Members*/
	CrawlerLeg *p_leg ;
	VrModel *p_chassis ;
	int m_segIndice ;
} ;
//////////////////////////
}//namespace Crawler
////////////////////////////////////////////////////

#endif //_CrawlerLegSeg_H
