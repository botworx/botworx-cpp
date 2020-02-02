#ifndef _BwcEffect_H
#define _BwcEffect_H

class BwcEffect : public BwPart {
public:
	BwcEffect(BwPart* pOwner) : BwPart(pOwner) {}
	void setElement(domEffect* pElement) { p_element = pElement ; }
	domEffect* getElement() { return p_element ; }
	//Data Members
	domEffect* p_element ;
} ;
typedef std::map<bwString, BwcEffect*> BwcEffectMap ;
typedef BwcEffectMap::iterator BwcEffectMapIter ;

class BwcEffectLib : public BwPart {
public:
	BwcEffectLib(BwPart* pOwner) : BwPart(pOwner) {}
	BwcEffect* createEffect() ;
	void addEffect(BwcEffect* pEffect) ;
	BwcEffect* findEffect(const bwString& name) ;
	//Data Members
	BwcEffectMap m_effectMap ;
} ;

#endif //_BwcEffect_H