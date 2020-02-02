/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#ifndef _VrBuilder_H
#define _VrBuilder_H

#include "VrModelFactory.h"

class VrModel ;
class VrShape ;

class VrBuilderConfig {
public:
	VrBuilderConfig() {}
	VrBuilderConfig(VrModelFactory *pItemFactory, 
		const bwSize3& dimensions, 
		const bwSize3& spacing, bwPartStyle style = PS_DEFAULT, bool usesPlaces = true) ;
	VrModelFactory* getItemFactory() { return p_itemFactory ; }
	VrModelFactory* getContainerFactory() { return p_itemFactory ; }
	bwSize3 getSpacing() { return m_spacing ; }
	bwSize3 getDimensions() { return m_dimensions ; }
	VrModel* createItem(VrGroup *pGroup) ;
	VrGroup* createContainer(VrGroup *pGroup) ;
	/*Data Members*/
	VrModelFactory *p_itemFactory ;
	VrModelFactory *p_containerFactory ;
	bwSize3 m_dimensions ;
	bwSize3 m_spacing ;
	bool m_usesPlaces ;
	bwPartStyle m_style ;
};
class VrBuilder : public BwKit {
public:
	VrBuilder(BwPart *pPart) ;
	void create() {}
	VrModelFactoryContainer* getFactories() { return & m_factories ; }
	void createFactory(VrModelFactory *pFactory) ;
	void addFactory(VrModelFactory *pFactory) ;
	void addFactoryAlias(const bwString& name, const bwString& alias) ;
	VrModelFactory* getFactory(const bwString& name) ;
	VrModel* build(const bwString& name, VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) ; //build using factory name
	VrModel* buildEnabled(const bwString& name, VrGroup *pGroup, bwPartStyle style = PS_DEFAULT) ;
	VrGroup* buildGrid(VrBuilderConfig *pConfig, VrGroup *pGroup) ;
	VrGroup* buildStack(VrBuilderConfig *pConfig, VrGroup *pGroup) ;
	VrGroup* buildColumn(VrBuilderConfig *pConfig, VrGroup *pGroup) ;
	VrGroup* buildRow(VrBuilderConfig *pConfig, VrGroup *pGroup) ;
	VrGroup* buildWall(VrBuilderConfig *pConfig, VrGroup *pGroup) ;
	VrGroup* buildMatrix(VrBuilderConfig *pConfig, VrGroup *pGroup) ;
	//Data
protected:
	VrModelFactoryContainer m_factories ;
	VrModelFactoryMap m_factoryMap ;
	//Singleton support
public:
	typedef BwSingletonT<VrBuilder> singleton ;
	singleton m_singleton ;
} ;

#endif //_VrBuilder_H
