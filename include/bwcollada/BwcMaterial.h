#ifndef _BwcMaterial_H
#define _BwcMaterial_H

#include <OgreMaterial.h>

class BwcMaterial : public BwPart {
public:
	BwcMaterial(BwPart* pOwner) : BwPart(pOwner) {}
	void setElement(domMaterial* pElement) { p_element = pElement ; }
	domMaterial* getElement() { return p_element ; }
	void setPeer(Ogre::MaterialPtr pPeer) { p_peer = pPeer ; }
	Ogre::Material& peer() { return *getPeer() ; }
	Ogre::Material* getPeer() { return p_peer.getPointer() ; }
	//
	void setResourceName(const bwString& name) { m_resourceName = name ; }
	bwString getResourceName() { return m_resourceName ; }
	//Data Members
	domMaterial* p_element ;
	Ogre::MaterialPtr p_peer ;
	bwString m_resourceName ;
} ;
typedef std::map<bwString, BwcMaterial*> BwcMaterialMap ;
typedef BwcMaterialMap::iterator BwcMaterialMapIter ;
//
class BwcNode ;

class BwcInstanceMaterial : public BwPart {
public:
	BwcInstanceMaterial(BwcNode* pNode, BwcMaterial* pOriginal) : BwPart((BwPart*)pNode), p_original(pOriginal) {}
	//
	BwcMaterial* getOriginal() { return p_original ; }
	void setSymbol(const bwString& symbol) { m_symbol = symbol ; }
	bwString getSymbol() { return m_symbol ; }
	void setTarget(const bwString& target) { m_target = target ; }
	bwString getTarget() { return m_target ; }
	//Data Members
	BwcMaterial* p_original ;
	bwString m_symbol ;
	bwString m_target ;
} ;
//
class BwcMaterialLib : public BwPart {
public:
	BwcMaterialLib(BwPart* pOwner) : BwPart(pOwner) {}
	BwcMaterial* createMaterial() ;
	void addMaterial(BwcMaterial* pMaterial) ;
	BwcMaterial* findMaterial(const bwString& name) ;
	//Data Members
	BwcMaterialMap m_materialMap ;
} ;

#endif //_BwcMaterial_H