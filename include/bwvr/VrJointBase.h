/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrJointBase_H
#define _VrJointBase_H

#include "VrModel.h"
class VrRod ;

class VrJointBase : public VrModel {
public:
	VrJointBase(VrGroup *pGroup) ;
	virtual ~VrJointBase() ;
	virtual void doCreate(const BwPartInfo& info) ;
	virtual void createBody() { return ; } //override to prevent body creation ... better than using boolean?

	virtual bwString getClassName() { return "VrJointBase" ; }
	virtual void setJointERP(bwReal erp) {}
	virtual void setJointCFM(bwReal cfm) {}

	void attachModels(VrModel *pModel1, VrModel *pModel2) ;
	VrModel* getModel1() { return p_model_1 ; }
	VrModel* getModel2() { return p_model_2 ; }
	VrModel *p_model_1 ;
	VrModel *p_model_2 ;
	virtual VrRod* getRod1() ;
	virtual VrRod* getRod2() ;
	//////////////////////////
	virtual void setAnchor(const bwPoint3& pos) { setPos(pos) ; }
	void setAnchor(bwReal x, bwReal y, bwReal z) { setAnchor(bwPoint3(x, y, z)) ; }
	virtual bwPoint3 getAnchor() { return getPos() ; }
} ;

#endif //_VrJointBase_H