/*BuggyBots - A Botworx VR reference app and AI playground
Copyright (C) 2005  Kurtis Fields. See BuggyBots_License.txt for details.
*/
#include "stdafx.h"

#include <bwvr/VrBuilder.h>
#include <bwvr/VrScenario.h>

#include <bwvr/VrPlace.h>

#include <bwvr/VrGridLayout.h>
#include <bwvr/VrMatrixLayout.h>

////////////////////////////
VrBuilderConfig::VrBuilderConfig(VrModelFactory *pItemFactory,
				const bwSize3& dimensions,
				const bwSize3& spacing, bwPartStyle style, bool usesPlaces) {
	p_itemFactory = pItemFactory ;
	m_dimensions = dimensions ;
	m_spacing = spacing ;
	m_style = style ;
	m_usesPlaces = usesPlaces ;
}
VrModel* VrBuilderConfig::createItem(VrGroup *pGroup) {
	return p_itemFactory->produce(pGroup, m_style) ;
}
VrGroup* VrBuilderConfig::createContainer(VrGroup *pGroup) {
	VrGroup* pContainer = NULL ;
	if(m_usesPlaces)
		pContainer = new VrPlace(pGroup) ;
	else
		pContainer = new VrGroup(pGroup) ;
	pContainer->create() ;
	return pContainer ;
}
////////////////////////////
template<> VrBuilder::singleton::pointer VrBuilder::singleton::g_singleton = 0 ;

VrBuilder::VrBuilder(BwPart *pPart) : BwKit(pPart) {
}
void VrBuilder::createFactory(VrModelFactory *pFactory) {
	pFactory->create() ;
	addFactory(pFactory) ;
}
void VrBuilder::addFactory(VrModelFactory *pFactory) {
	m_factories.push_back(pFactory) ;
	bwString name = pFactory->getName() ;
	VrModelFactory *pFound = m_factoryMap[name] ;
	bwAssert(pFound == NULL) ;
	m_factoryMap[name] = pFactory ;
}
void VrBuilder::addFactoryAlias(const bwString& name, const bwString& alias) {
	m_factoryMap[alias] = m_factoryMap[name] ;
}
VrModelFactory* VrBuilder::getFactory(const bwString& name) {
	return m_factoryMap[name] ;
}
VrModel* VrBuilder::build(const bwString& name, VrGroup *pGroup, bwPartStyle style) {
	VrModelFactory *pFactory = m_factoryMap[name] ;
	VrModel *pModel = pFactory->produce(pGroup, style) ;
	if(style & PS_CREATE_SLEEPING)
		pModel->doze() ;
	return pModel ;
}
VrModel* VrBuilder::buildEnabled(const bwString& name, VrGroup *pGroup, bwPartStyle style) {
	VrModel *pModel = build(name, pGroup) ;
	pModel->config() ;
	pModel->enable(style & PS_CREATE_SLEEPING) ;
	return pModel ;
}
VrGroup* VrBuilder::buildGrid(VrBuilderConfig *pConfig, VrGroup *pGroup) {
	VrGroup *pGrid = pConfig->createContainer(pGroup) ;
	VrGridLayout *pLayout = new VrGridLayout(pGrid) ;
	pLayout->create() ;

	bwSize3 spacing = pConfig->getSpacing() ;
	bwReal width = pConfig->getDimensions()[0] ;
	bwReal length = pConfig->getDimensions()[2] ;

	pLayout->setSpacing(spacing) ;
	for(int i = 0 ; i < length ; ++i) {
		pLayout->beginRow() ;
		for(int j = 0 ; j < width ; ++j) {
			pLayout->addModel(pConfig->createItem(pGrid)) ;
		}
		pLayout->endRow() ;
	}

	return pGrid ;
}
VrGroup* VrBuilder::buildStack(VrBuilderConfig *pConfig, VrGroup *pGroup){
	VrGroup *pStack = pConfig->createContainer(pGroup) ;
	VrStackLayout *pLayout = new VrStackLayout(pStack) ;
	pLayout->create() ;
	bwReal height = pConfig->getSpacing()[1] ;
	for(int i = 0 ; i < height ; ++i) {
		pLayout->addModel(pConfig->createItem(pStack)) ;
	}
	return pStack ;
}
VrGroup* VrBuilder::buildColumn(VrBuilderConfig *pConfig, VrGroup *pGroup){
	VrGroup *pColumn = pConfig->createContainer(pGroup) ;
	VrColumnLayout *pLayout = new VrColumnLayout(pColumn) ;
	pLayout->create() ;

	pLayout->setSpacing(pConfig->getSpacing()) ;

	bwReal length = pConfig->getDimensions()[2] ;
	for(int i = 0 ; i < length ; ++i) {
		pLayout->addModel(pConfig->createItem(pColumn)) ;
	}
	return pColumn ;
}
VrGroup* VrBuilder::buildRow(VrBuilderConfig *pConfig, VrGroup *pGroup){
	VrGroup *pRow = pConfig->createContainer(pGroup) ;
	VrRowLayout *pLayout = new VrRowLayout(pRow) ;
	pLayout->create() ;

	pLayout->setSpacing(pConfig->getSpacing()) ;

	bwReal width = pConfig->getDimensions()[0] ;
	for(int i = 0 ; i < width ; ++i) {
		pLayout->addModel(pConfig->createItem(pRow)) ;
	}
	return pRow ;
}
VrGroup* VrBuilder::buildWall(VrBuilderConfig *pConfig, VrGroup *pGroup){
	VrGroup *pRow = pConfig->createContainer(pGroup);
	VrRowLayout *pRowLayout = new VrRowLayout(pRow) ;
	pRowLayout->create() ;

	pRowLayout->setSpacing(pConfig->getSpacing()) ;

	bwReal width = pConfig->getDimensions()[0] ;
	bwReal height = pConfig->getDimensions()[1] ;
	for(int i = 0 ; i < width ; ++i) {
		VrGroup *pStack = pConfig->createContainer(pRow) ;
		VrLayout *pStackLayout = new VrStackLayout(pStack) ;
		pStackLayout->create() ;

		pStackLayout->setSpacing(pConfig->getSpacing()) ;

		for(int j = 0 ; j < height ; ++j) {
			pStackLayout->addModel(pConfig->createItem(pStack)) ;
		}
		pRowLayout->addModel(pStack) ;
	}
	return pRow ;
}
VrGroup* VrBuilder::buildMatrix(VrBuilderConfig *pConfig, VrGroup *pGroup){
	VrGroup *pMatrix = pConfig->createContainer(pGroup) ;
	VrMatrixLayout *pLayout = new VrMatrixLayout(pMatrix) ;
	pLayout->create() ;

	pLayout->setSpacing(pConfig->getSpacing()) ;

	bwSize3 dimensions = pConfig->getDimensions() ;
	bwReal width = dimensions[0] ;
	bwReal height = dimensions[1] ;
	bwReal length = dimensions[2] ;

	for(int i = 0 ; i < height ; ++i) {
		pLayout->beginGrid() ;
		for(int j = 0 ; j < length ; ++j) {
			pLayout->beginRow() ;
			for(int k = 0 ; k < width ; ++k) {
				pLayout->addModel(pConfig->createItem(pMatrix)) ;
			}
			pLayout->endRow() ;
		}
		pLayout->endGrid() ;
	}
	return pMatrix ;
}
