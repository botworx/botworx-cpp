/*Botworx VR - A Virtual Reality Framework
Copyright (C) 2005  Kurtis Fields. See BotworxVR_License.txt for details.
*/
#ifndef _BbScenario_H
#define _BbScenario_H

#include <bwvr/VrScenario.h>

class BbBuilder ;
class BbMap ;

class BbScenario : public VrScenario {
public:
	BbScenario(VrApplet* pApplet) ;
	virtual ~BbScenario() ;
	virtual void createScene() ;
	virtual void createWorld() ;
	virtual void createGround() ;
	virtual void createProps() ;
	virtual void createAvatar() ;
	virtual void enableSky(bool val) ;
	virtual void onLoad() ;
protected:
	void createPlane() ;
	void createTerrain() ;
	void addObstacles() ;
	void addLevels() ;
	void addTiles() ;
	void addBuggies() ;
	void addCrawlers() ;
	void buildToy1(VrGroup *pGroup) ;
	void buildToy2(VrGroup *pGroup) ;
	void buildToy3(VrGroup *pGroup) ;
	//Data Members
	bwSize3 m_worldSize ;
	bool m_usesMap ;
	bool m_usesToys ;
	bool m_usesObstacles ;
	bool m_usesTiles ;
	bool m_usesLevels ;
	bool m_usesBalls ;
	//TODO:put ground and sky info into separate structures?
	//Ground
	enum groundType {
		GROUND_NONE,
		GROUND_PLANE,
		GROUND_TERRAIN
	} ;
	void setGroundType(groundType type) { m_groundType = type ; }
	groundType getGroundType() { return m_groundType ; }
	groundType m_groundType ;
	void setGroundMaterialName(const bwString& name) { m_groundMaterialName = name ; }
	bwString getGroundMaterialName() { return m_groundMaterialName ; }
	bwString m_groundMaterialName ;
	//Sky
	enum skyType {
		SKY_NONE,
		SKY_PLANE,
		SKY_BOX,
		SKY_DOME
	} ;
	void setSkyType(skyType type) { m_skyType = type ; }
	skyType getSkyType() { return m_skyType ; }
	skyType m_skyType ;
	void setSkyMaterialName(const bwString& name) { m_skyMaterialName = name ; }
	bwString getSkyMaterialName() { return m_skyMaterialName ; }
	bwString m_skyMaterialName ;

	//
	enum avatarType {
		AVATAR_NONE = 0,
		AVATAR_UFO,
		AVATAR_BUGGY,
		AVATAR_JR,
		AVATAR_CRAWLER
	} ;
	class AvatarInfo {
	public:
		AvatarInfo() : m_avatarType(AVATAR_UFO), m_pos(bwPoint3(0, 1, 155)) {}
		void setAvatarType(avatarType type) { m_avatarType = type ; }
		avatarType getAvatarType() { return m_avatarType ; }
		void setPos(const bwPoint3& pos) { m_pos = pos ; }
		bwPoint3 getPos() { return m_pos ; }
		void setQuat(const bwQuat& quat) { m_quat = quat ; }
		bwQuat getQuat() { return m_quat ; }
	protected:
		avatarType m_avatarType ;
		bwPoint3 m_pos ;
		bwQuat m_quat ;
	} m_avatarInfo ;
	AvatarInfo& avatarInfo() { return m_avatarInfo ; }
	//
	BbMap *p_map ;
public:
	BbMap& getMap() { return *p_map ; }
	//
	static BbScenario& singleton() { return static_cast<BbScenario&>(singleton::get()) ; }
};

class BbSimpleScenario : public BbScenario {
public:
	BbSimpleScenario(VrApplet* pApplet) ;
} ;
class BbDefaultScenario : public BbScenario {
public:
	BbDefaultScenario(VrApplet* pApplet) ;
} ;
class BbTerrainScenario : public BbScenario {
public:
	BbTerrainScenario(VrApplet* pApplet) ;
} ;

#endif //_BbScenario_H
