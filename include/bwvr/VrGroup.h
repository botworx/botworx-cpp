/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrGroup_H
#define _VrGroup_H

#include "VrModel.h"
#include "VrModelFactory.h"
#include <bwcore/BwStage.h>

class VrShape ;
class VrShape ;
class VrLayout ;
class VrPhysics ;
class VrNodeKit ;
//
//VrModelStage
//
class VrModelStage ;
template<>
struct BwSigT<VrModelStage> : BwSigT<BwStage> {
	typedef VrGroup				T_Owner ;
	typedef VrModel				T_Part ;
	typedef VrModelContainer	T_Container ;
} ;
typedef BwStageT<VrModelStage, BwStage>	VrModelStageBase ;

class VrModelStage : public VrModelStageBase {
public:
	VrModelStage() : VrModelStageBase() {}
	virtual void onActorAddition(T_Part *pActor) ;
	virtual void onActorRemoval(T_Part *pActor) ;
	//Data Members
} ;
//
//VrGroup
//
class VrGroup : public VrModel {
public:
	VrGroup(VrGroup *pGroup) ;
	virtual void createBody() { return ; } //override to prevent body creation ... better than using boolean?
	virtual bwString getClassName() { return "VrGroup" ; }
	virtual void invalidate(VrModel *pModel, invalid flags) ;
	virtual void validateBounds() ;
	virtual void layout() ;

	VrModelContainer& getModels() { return m_stage.getActors() ; }

	virtual void onModelAddition(VrModel *pModel) {}
	virtual void onModelRemoval(VrModel *pModel) {}
	virtual bool doze() ;
	virtual void wakeAll() ;
	virtual void setIsAutoSleeper(bool val) ;
	virtual void addModel(VrModel *pModel) ;
	virtual void removeModel(VrModel *pModel) ;
	//
	void setMain(VrModel *pModel) { p_main = pModel ; }
	virtual VrModel* getMain() { return p_main ; }
	virtual VrModel* getPrimary() ;
	//
	virtual void setLayout(VrLayout *pLayout) ;
	virtual void validateSize() ;
	virtual void recenter(const bwPoint3& point) ;
/*Data Members*/
public:
	VrLayout *p_layout ;
	VrModel *p_main ; //The main member ... usually a chassis of some sort.
	VrModelStage m_stage ;
};

#endif //_VrGroup_H