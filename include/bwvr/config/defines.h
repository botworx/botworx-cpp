/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _Vr_defines_H
#define _Vr_defines_H

enum motionType_E {
	MOTION_STATIC,
	MOTION_QUASISTATIC,
	MOTION_KINEMATIC,
	MOTION_FIXED,
	MOTION_DYNAMIC
};
typedef motionType_E motionType ;

enum nodeType_E {
	NODE_BOX,
	NODE_BALL,
	NODE_GROUP,
	NODE_PLACE,
	NODE_PLANE,
	NODE_CAPSULE,
	NODE_CYLINDER,
	NODE_CONVEXMESH,
	NODE_CONCAVEMESH,
	NODE_HEIGHTFIELD,
	NODE_PARTICLEMESH,
	NODE_RAY,
	NODE_LINESEG,
	NODE_TTL
} ;
typedef nodeType_E nodeType ;

enum collisionType_E {
	COLLISION_NULL,
	COLLISION_ODE,
	COLLISION_BT
} ;
typedef collisionType_E collisionType ;

enum physicsType_E {
	PHYSICS_DEFAULT,
	PHYSICS_ODE_DEFAULT = PHYSICS_DEFAULT,
	PHYSICS_ODE_QUICK = PHYSICS_ODE_DEFAULT,
	PHYSICS_ODE_STABLE,
	PHYSICS_TTL
} ;
typedef physicsType_E physicsType ;

enum jointType_E {
	JOINT_DEFAULT,
	JOINT_BALL = JOINT_DEFAULT,
	JOINT_HINGE,
	JOINT_HINGE2,
	JOINT_UNIVERSAL,
	JOINT_TTL
} ;
typedef jointType_E jointType ;

typedef int vrIndex32 ;
typedef vrIndex32 vrIndex ;
typedef short vrIndex16 ;

typedef vrIndex32 vrTriFace32[3] ;
typedef vrIndex16 vrTriFace16[3] ;
typedef vrTriFace32 vrTriFace ;

typedef vrIndex32 vrQuadFace[4] ;

typedef char vrDirection[4] ;

enum vrCompass_E {
	VR_NW,
	VR_NE,
	VR_SE,
	VR_SW,
	VR_NORTH,
	VR_EAST,
	VR_SOUTH,
	VR_WEST
} ;
typedef vrCompass_E vrCompass ;

class VrNode ;
struct VrNodePair {
	VrNodePair(VrNode* pCollider, VrNode* pCollidee) : p_collider(pCollider), p_collidee(pCollidee) {} 
	VrNode& collider() { return *p_collider ; }
	VrNode& collidee() { return *p_collidee ; }
	//Data Members
	VrNode* p_collider ;
	VrNode* p_collidee ;
} ;
typedef std::vector<VrNodePair> VrNodePairs ;
typedef VrNodePairs::iterator VrNodePairIter ;

class VrModel ;
typedef boost::pool_allocator<VrModel*> VrModelContainerAllocator ; 
typedef std::list<VrModel*,  VrModelContainerAllocator> VrModelContainer ;
typedef VrModelContainer::iterator VrModelIter ;

class VrModelFactory ;
typedef std::list<VrModelFactory*> VrModelFactoryContainer ;
typedef VrModelFactoryContainer::iterator VrModelFactoryIter ;
typedef std::map<std::string, VrModelFactory*> VrModelFactoryMap ;

#endif //_Vr_defines_H