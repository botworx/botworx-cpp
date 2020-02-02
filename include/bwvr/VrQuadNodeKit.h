/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _VrQuadNodeKit_H
#define _VrQuadNodeKit_H

#include "VrNode.h"
#include "VrNodeKit.h"

class VrQuadNodeKit ;
class VrQuadNode ;

class Block{
public:
	bwReal MinX, MaxX;
	bwReal MinZ, MaxZ;

	VrQuadNode* First;
	int GeomCount;

	Block* Parent;
	Block* Children;

	void Create(const bwPoint3& Center, const bwSize3& Extents, Block* Parent, int Depth, Block*& Blocks);

	void Collide(VrNode* Object);

	void AddObject(VrQuadNode* Object);
	void DelObject(VrQuadNode* Object);
	void Traverse(VrQuadNode* Object);

	bool Inside(const bwBounds3& AABB);
	
	Block* GetBlock(const bwBounds3& AABB);
	Block* GetBlockChild(const bwBounds3& AABB);
};

class VrQuadNode : public VrNode {
public:
	VrQuadNode(VrModel* pModel) : VrNode(pModel), next(NULL), tome(NULL) {}
	virtual void validate() ;
	/*Data Members*/
	VrQuadNode* next ;
	Block* tome ;
};
////////////////////////////////////
class VrQuadNodeKit ;
template<>
struct BwSigT<VrQuadNodeKit> : BwSigT<BwKit> {
	typedef VrQuadNode	T_Part ;
} ;
typedef VrNodeKitT<VrQuadNodeKit> VrQuadNodeKitBase ;

class VrQuadNodeKit : public VrQuadNodeKitBase {
public:
	VrQuadNodeKit(VrModel* pOwner, const bwPoint3& Center, const bwSize3& Extents, int Depth) ;
	~VrQuadNodeKit();
	virtual VrNode* createNode(VrModel* pModel) ;
	virtual void releaseNode(VrNode *pNode)  ;
	virtual void collide(VrNode* pCollider) ;
	////////
	Block* Blocks;	// Blocks[0] is the root

	void add(VrQuadNode* g);
	void remove(VrQuadNode* g);
	// Temp data
	Block* CurrentBlock;	// Only used while enumerating
	int* CurrentChild;	// Only used while enumerating
	int CurrentLevel;	// Only used while enumerating
	VrQuadNode* CurrentObject;	// Only used while enumerating
	int CurrentIndex;
	//
	size_t count ;
};


#endif //_VrQuadNodeKit_H
