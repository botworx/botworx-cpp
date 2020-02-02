/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrQuadNodeKit.h>
#include <bwvr/VrCollider.h>
#include <bwvr/VrModel.h>
//////////////
void VrQuadNode::validate() {
	VrNode::validate() ;
	if(tome != NULL)
		tome->Traverse(this) ;
}
//////////////
void VrQuadNodeKit::collide(VrNode *pCollider) {
	//pCollider->test_migration(p_root) ;
	Blocks[0].Collide(pCollider) ;
}
VrNode* VrQuadNodeKit::createNode(VrModel *pModel) {
	VrQuadNode* pNode = static_cast<VrQuadNode*>(VrQuadNodeKitBase::createNode(pModel)) ;
	//TODO:Unnecessary test?
	if(!pModel->isPlace())
		add(pNode) ;
	return pNode ;
}
void VrQuadNodeKit::releaseNode(VrNode *pNode) {
	if(!pNode->isPlace())
		remove(static_cast<VrQuadNode*>(pNode)) ;
	VrQuadNodeKitBase::releaseNode(pNode) ;
}
/////////////
// QuadTreeSpace by Erwin de Vries.

#define AXIS0 0
//#define AXIS1 1
#define AXIS1 2
//#define UP 2
#define UP 1

const int SPLITAXIS = 2;
const int SPLITS = SPLITAXIS * SPLITAXIS;

void Block::Create(const bwPoint3& Center, const bwSize3& Extents, Block* Parent, int Depth, Block*& Blocks){
	GeomCount = 0;
	First = 0;

	MinX = Center[AXIS0] - Extents[AXIS0];
	MaxX = Center[AXIS0] + Extents[AXIS0];

	MinZ = Center[AXIS1] - Extents[AXIS1];
	MaxZ = Center[AXIS1] + Extents[AXIS1];

	this->Parent = Parent;
	if (Depth > 0){
		Children = Blocks;
		Blocks += SPLITS;

		bwSize3 ChildExtents;
		ChildExtents[AXIS0] = Extents[AXIS0] / bwReal(SPLITAXIS) ;
		ChildExtents[AXIS1] = Extents[AXIS1] / bwReal(SPLITAXIS) ;
		ChildExtents[UP] = Extents[UP];

		for (int i = 0; i < SPLITAXIS; ++i){
			for (int j = 0; j < SPLITAXIS; ++j){
				int Index = i * SPLITAXIS + j;

				bwPoint3 ChildCenter;
				ChildCenter[AXIS0] = Center[AXIS0] - Extents[AXIS0] + ChildExtents[AXIS0] + bwReal(i) * (ChildExtents[AXIS0] * bwRealTraits::Two);
				ChildCenter[AXIS1] = Center[AXIS1] - Extents[AXIS1] + ChildExtents[AXIS1] + bwReal(j) * (ChildExtents[AXIS1] * bwRealTraits::Two);
				ChildCenter[UP] = Center[UP];
				
				Children[Index].Create(ChildCenter, ChildExtents, this, Depth - 1, Blocks);
			}
		}
	}
	else Children = 0;
}

void Block::Collide(VrNode* g1){
	// Collide against local list
	VrQuadNode* g2 = First ;
	while (g2){
		g2->collide(g1, false) ;
		g2 = g2->next;
	}

	// Collide against children
	if (Children){
		for (int i = 0; i < SPLITS; ++i){
			// Early out for empty blocks
			if (Children[i].GeomCount == 0){
				continue;
			}

			// Does the geom's AABB collide with the block?
			// Dont do AABB tests for single geom blocks.
			if (Children[i].GeomCount == 1 && Children[i].First){
				//
			}
			else if (true){
				bwPoint3 min = g1->getMin() ;
				bwPoint3 max = g1->getMax() ;
				if (min[0] > Children[i].MaxX ||
					max[0] < Children[i].MinX ||
					min[2] > Children[i].MaxZ ||
					max[2] < Children[i].MinZ) continue;
			}
			Children[i].Collide(g1);
		}
	}
}
void Block::AddObject(VrQuadNode* Object){
	// Add the geom
	Object->next = First;
	First = Object;
	Object->tome = this;

	// Now traverse upwards to tell that we have a geom
	Block* Block = this;
	do{
		Block->GeomCount++;
		Block = Block->Parent;
	}
	while (Block);
}
void Block::DelObject(VrQuadNode* Object){
	// Del the geom
	VrQuadNode* g = First;
	VrQuadNode* Last = 0;
	while (g){
		if (g == Object){
			if (Last){
				Last->next = g->next;
			}
			else First = g->next;

			break;
		}
		Last = g;
		g = g->next;
	}

	Object->tome = 0;

	// Now traverse upwards to tell that we have lost a geom
	Block* Block = this;
	do{
		Block->GeomCount--;
		Block = Block->Parent;
	}
	while (Block);
}

void Block::Traverse(VrQuadNode* Object){
	Block* NewBlock = GetBlock(Object->getBounds());

	if (NewBlock != this){
		// Remove the geom from the old block and add it to the new block.
		// This could be more optimal, but the loss should be very small.
		DelObject(Object);
		NewBlock->AddObject(Object);
	}
}

bool Block::Inside(const bwBounds3& AABB){
	//return AABB[AXIS0 * 2 + 0] >= MinX && AABB[AXIS0 * 2 + 1] <= MaxX && AABB[AXIS1 * 2 + 0] >= MinZ && AABB[AXIS1 * 2 + 1] <= MaxZ;
	bwPoint3 min = AABB.getMin() ;
	bwPoint3 max = AABB.getMax() ;
	return min[AXIS0] >= MinX && max[AXIS0] <= MaxX && min[AXIS1] >= MinZ && max[AXIS1] <= MaxZ;
}

Block* Block::GetBlock(const bwBounds3& AABB){
	if (Inside(AABB)){
		return GetBlockChild(AABB);	// Child or this will have a good block
	}
	else if (Parent){
		return Parent->GetBlock(AABB);	// Parent has a good block
	}
	else return this;	// We are at the root, so we have little choice
}

Block* Block::GetBlockChild(const bwBounds3& AABB){
	if (Children){
		for (int i = 0; i < SPLITS; ++i){
			if (Children[i].Inside(AABB)){
				return Children[i].GetBlockChild(AABB);	// Child will have good block
			}
		}
	}
	return this;	// This is the best block
}

//****************************************************************************
// quadtree space

VrQuadNodeKit::VrQuadNodeKit(VrModel* pModel, const bwPoint3& Center, const bwSize3& Extents, int Depth) : VrQuadNodeKitBase(pModel) {

	int BlockCount = 0;
	for (int i = 0; i <= Depth; ++i){
		BlockCount += (int)pow((bwReal)SPLITS, i);
	}

	Blocks = (Block*)dAlloc(BlockCount * sizeof(Block));
	Block* Blocks = this->Blocks + 1;	// This pointer gets modified!

	this->Blocks[0].Create(Center, Extents, 0, Depth, Blocks);

	CurrentBlock = 0;
	CurrentChild = (int*)dAlloc((Depth + 1) * sizeof(int));
	CurrentLevel = 0;
	CurrentObject = 0;
	CurrentIndex = -1;
}

VrQuadNodeKit::~VrQuadNodeKit(){
	int Depth = 0;
	Block* Current = &Blocks[0];
	while (Current){
		Depth++;
		Current = Current->Children;
	}

	int BlockCount = 0;
	for (int i = 0; i < Depth; ++i){
		BlockCount += (int)pow((bwReal)SPLITS, i);
	}

	dFree(Blocks, BlockCount * sizeof(Block));
	dFree(CurrentChild, (Depth + 1) * sizeof(int));
}
void VrQuadNodeKit::add(VrQuadNode* g){
	Blocks[0].GetBlock(g->getBounds())->AddObject(g);	// Add to best block
	count++;
}
void VrQuadNodeKit::remove(VrQuadNode* g){
	((Block*)g->tome)->DelObject(g);
	count--;
	// safeguard
	g->next = 0;
	g->tome = 0;
}