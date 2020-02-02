/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaDirectory.h>

MiaEntry::MiaEntry(MiaEntry *pParent, const bwString& name, MiaMind* pMind) 
	: p_parent(pParent), m_name(name), p_mind(pMind) {
	m_path = makePath() ;
}
bwPath MiaEntry::makePath() {
	if(p_parent == NULL)
		return bwPath("/") ;
	//else
	return p_parent->getPath() /= m_name ;
}
MiaEntry* MiaEntry::findChild(const bwString& name) {
	return m_children[name] ;
}
MiaEntry* MiaEntry::findOrCreateDescendant(const bwPath& path) {
	MiaEntry *pNode = NULL ;

	if(!path.has_branch_path() && m_name == path.leaf())
		return this ;
	//else
	bwPath leafPath ;
	for(bwPath::iterator iter = ++path.begin() ; iter != path.end() ; ++iter) {
		leafPath /= *iter ;
	}
	pNode = findOrCreateChild((*path.begin()).string(), leafPath) ;
	//kind of a crappy way to return the last half of the path...
	if(leafPath == "")
		return pNode ;
	//else
	return pNode->findOrCreateDescendant(leafPath) ;
}
MiaEntry* MiaEntry::findDescendant(const bwPath& path) {
	MiaEntry *pNode = NULL ;

	if(!path.has_branch_path() && m_name == path.leaf())
		return this ;
	//else
	pNode = findChild((*path.begin()).string()) ;
	//kind of a crappy way to return the last half of the path...
	bwPath leafPath ;
	for(bwPath::iterator iter = ++path.begin() ; iter != path.end() ; ++iter) {
		leafPath /= *iter ;
	}
	if(leafPath == "")
		return pNode ;
	//else
	return pNode->findDescendant(leafPath) ;
}
///////////
void MiaEntry::print(int indent) {
	bwString out ;
	for(int i = 0 ; i < indent ; ++i)
		out += "\t" ;
	out += m_name + " : " ;
	out += "\n" ;
	//
	std::cout << out ;
}
void MiaEntry::printChildren(int indent) {
	for(MiaEntryMapIter iter = m_children.begin() ; iter != m_children.end() ; ++iter) {
		(*iter).second->printTree(indent) ;
	}
}
void MiaEntry::printTree(int indent) {
	print(indent) ;
	++indent ;
	printChildren(indent) ;
}