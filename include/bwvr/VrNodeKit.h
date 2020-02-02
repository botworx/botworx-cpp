/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrNodeKit_H
#define _VrNodeKit_H

#include "VrNode.h"
#include "VrModel.h"
//
//VrNodeKit
//
class VrNodeKit : public BwKit {
public:
	VrNodeKit(BwPart *pPart) ;
	virtual VrNode* createNode(VrModel *pModel) = 0 ;
	virtual void releaseNode(VrNode *pNode) = 0 ;
	void setRoot(VrNode* pNode) { p_root = pNode ; }
	VrNode* getRoot() { return p_root ; }
	//
	virtual void collide(VrNode* pCollider) = 0 ;
	//Data Members
	VrNode* p_root ;
} ;
//
//VrNodeKitT
//
template<typename T_Class, typename T_Base = VrNodeKit>
class VrNodeKitT : public BwPoolKitT<T_Class, T_Base> {
	using T_Part = typename VrNodeKitT<T_Class, T_Base>::T_Part;
public:
	VrNodeKitT(VrModel *pModel) : BwPoolKitT<T_Class, T_Base>(pModel) {}
	virtual VrNode* createNode(VrModel *pModel) { 
		return new(this->rent(sizeof(T_Part))) T_Part(pModel) ; }
	virtual void releaseNode(VrNode *pNode) { this->release(pNode) ; }
	//Data Members
public:
};
//
//VrDefaultNodeKit
//
class VrDefaultNodeKit ;
template<>
struct BwSigT<VrDefaultNodeKit> : BwSigT<BwKit> {
	typedef VrNode	T_Part ;
} ;
typedef VrNodeKitT<VrDefaultNodeKit> VrDefaultNodeKitBase ;

class VrDefaultNodeKit : public VrDefaultNodeKitBase {
public:
	VrDefaultNodeKit(VrModel *pModel) : VrDefaultNodeKitBase(pModel) {}
	virtual void collide(VrNode* pNode) ;
};

#endif //_VrNodeKit_H
