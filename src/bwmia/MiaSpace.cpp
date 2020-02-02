/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaAgent.h>
#include <bwai/AiInt.h>

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaSpace.h>
#include <bwmia/MiaMatcher.h>
#include <bwmia/MiaBinder.h>
#include <bwmia/config/options.h>

//
#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;
#include <bwagency/_BwState.h>
using namespace _BwState ;

MiaSpace::MiaSpace(MiaSpace* pParent, AiSymbol* pSymbol) 
	: BwActor(pParent) {

	p_parent = pParent ;
	setSymbol(pSymbol) ;
//
	m_topicMap.reserve(TOPIC_RESERVE) ;
}
MiaSpace::~MiaSpace() {
}
void MiaSpace::copyTopics(MiaSpace* pSrc, bool deepCopy) {
	AiPair* pSrcTopics = pSrc->getTopics() ;
	MiaTopic *pSrcTopic = NULL ;
	MiaTopic *pDstTopic = NULL ;
	for(AiPair* pTopicPair = pSrcTopics ; pTopicPair != NULL ; pTopicPair = pairCdr(pTopicPair)) {
		pSrcTopic = asTopic(car(pTopicPair)) ;
		if(pSrcTopic->isCopyable())
			if(deepCopy)
				pSrcTopic->copyTo(*this) ;
			else
				addTopic(pSrcTopic) ;
	}
}
void MiaSpace::doCreate(const BwPartInfo& info) {
	BwActor::doCreate(info) ;
	//
	MiaIdentifier* pId = internId(getSymbol()) ;
	//
	pId->setIsCopyable(false) ;
	//
	p_id = pId ;
	p_idTopic = new MiaTopic(*this, pId) ;
	pId->setSpace(this) ;

	addTopic(getIdTopic()) ;

	if(hasParent()) {
		#if MIA_OPTION_COPYONWRITE
			copyTopics(p_parent, false) ; //shallow copy
		#else
			copyTopics(p_parent) ; //deep copy
		#endif
	}
}
MiaTopic* MiaSpace::lookup(MiaFact* pId) { 
	MiaTopic* pTopic = innerLookup(pId) ;

	if(pTopic == NULL)
		pTopic = outerLookup(pId) ;

	return pTopic ;
}
MiaTopic* MiaSpace::innerLookup(MiaFact* pId) {
	//MiaTopic* pTopic = m_topicMap[pId] ;
	MiaTopic* pTopic = NULL ;
	for(MiaTopicMapIter iter = m_topicMap.begin() ; iter != m_topicMap.end() ; ++iter) {
		if((*iter).first == pId) {
			pTopic = (*iter).second ;
			break ;
		}
	}
	return pTopic ;
}
//Theory 1 : Root as alias
MiaTopic* MiaSpace::outerLookup(MiaFact* pId) {
	MiaTopic* pTopic = NULL ;
	if(isRoot()) {
		if(pId->isIdentifier()) {
			MiaSpace* pSpace = asIdentifier(pId)->getSpace() ;
			if(pSpace != NULL && pSpace != this)
				pTopic = pSpace->innerLookup(pId) ; //break the cycle
			else
				return NULL ;
		}
	}
	else
		pTopic = getParent()->lookup(pId) ;

	return pTopic ;
}
void MiaSpace::addTopic(MiaTopic* pTopic) {
	//m_topicMap[pTopic->getId()] = pTopic ;
	MiaFact* pSubject = pTopic->getSubject() ;
	m_topicMap.push_back(MiaTopicMapPair(pSubject, pTopic)) ;
	m_topics.push_back(pTopic) ;
	addSubject(pSubject) ;
}
void MiaSpace::replaceTopic(MiaTopic* pTopic) {
	bool replace = false ;
	MiaFact* pSubject = pTopic->getSubject() ;
	for(MiaTopicMapIter iter = m_topicMap.begin() ; iter != m_topicMap.end() ; ++iter) {
		if((*iter).first == pSubject) {
			(*iter).second = pTopic ;
			replace = true ;
			break ;
		}
	}
	if(replace) {
		for(AiPair* pTopics = getTopics() ; pTopics != NIL ; pTopics = pairCdr(pTopics)) {
			if(asTopic(car(pTopics))->getSubject() == pSubject)
				pTopics->p_left = pTopic ;
		}
	}
	else
		addTopic(pTopic) ;
}
AiList MiaSpace::findSubjects(AiPair* pFacts) {
	MiaTopic* pExists = NULL ;
	AiList subjects ;
	for(AiPair* pTopics = getTopics() ; pTopics != NIL ; pTopics = pairCdr(pTopics)) {
		pExists = asTopic(car(pTopics)) ;
		if(pExists->identicalExists(pFacts))
			subjects.push_back(pExists->getSubject()) ;
	}
	return subjects ;
}
AiList MiaSpace::findSubjects(MiaPatterns& patterns) {
	MiaTopic* pExists = NULL ;
	AiList subjects ;
	for(AiPair* pTopics = getTopics() ; pTopics != NIL ; pTopics = pairCdr(pTopics)) {
		pExists = asTopic(car(pTopics)) ;
		if(pExists->match(patterns))
			subjects.push_back(pExists->getSubject()) ;
	}
	return subjects ;
}
MiaTopic* MiaSpace::lookup(AiPair* pFacts) {
	MiaTopic* pExists = NULL ;
	for(AiPair* pTopics = getTopics() ; pTopics != NIL ; pTopics = pairCdr(pTopics)) {
		pExists = asTopic(car(pTopics)) ;
		if(pExists->identicalExists(pFacts))
			return pExists ;
	}
	return NULL ;
}
bool MiaSpace::identicalExists(MiaTopic* pTopic) {
	MiaTopic* pExists = NULL ;
	for(AiPair* pTopics = getTopics() ; pTopics != NIL ; pTopics = pairCdr(pTopics)) {
		pExists = asTopic(car(pTopics)) ;
		if(pExists->identical(pTopic))
			return true ;
	}
	return false ;
}
//
inline char* slash_to_underscore(char *s) {
  while (*s) {
    if (*s == '/')
		*s = '_' ;
	s++ ;
  }
  return s ;
}
void MiaSpace::dump() {
	char nameString[64] ;
	strcpy(nameString, p_symbol->getCstring()) ;
	slash_to_underscore(nameString) ;
	std::string fileName = ("../BwMia/logs/" + bwString(nameString) + ".xml") ;
	std::ofstream out(fileName.c_str(), std::ios_base::out | std::ios_base::trunc );
	std::cout << "\nFile dump.\n\n" ;
	MiaPrinter dumper(out) ;
	print(dumper) ;
	dumper.flush() ;
	out.close() ;
}
void MiaSpace::printFacts(MiaPrinter& printer) const {
	MiaTopic* pTopic = NULL ;
	for(AiPair* pTopics = getTopics() ; pTopics != NIL ; pTopics = pairCdr(pTopics)) {
		pTopic = static_cast<MiaTopic*>(car(pTopics)) ;
		pTopic->printFacts(printer) ;
	}
}
void MiaSpace::printBranch(MiaPrinter& printer) {
	print(printer) ;
	if(hasParent())
		p_parent->printBranch(printer) ;
}
void MiaSpace::print(MiaPrinter& printer) const {
	MiaTopic* pTopic = NULL ;
	printer << "<space>\n" ;
	printFacts(printer) ;
	printer << "</space>\n" ;
}
MiaPrinter& operator<<(MiaPrinter& printer, const MiaSpace& space) {
	space.print(printer) ;
	return printer ;
}