/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiList.h>

#include <bwmia/MiaTopic.h>
#include <bwmia/MiaState.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaPattern.h>
#include <bwmia/MiaPrinter.h>
#include <bwmia/config/options.h>

#include <bwagency/_BwAgent.h>
using namespace _BwAgent ;

void MiaTopic::purge() {
	MiaTopic::~MiaTopic() ;
#if AI_OPTION_POOLING
	k_topic().release(this) ;
#else
	BW_USERFREE(this, MIA_TT_TOPIC) ;
#endif
}
//////////////
MiaTopic::MiaTopic(MiaSpace& space, MiaFact* pSubject, ThingTT cellType)
	: BwCell(cellType){
	p_space = &space ;
	p_subject = pSubject ;
	//p_id = pId ;
	p_id = NULL ;
	setIsCopyable(pSubject->isCopyable()) ;
}
MiaTopic::~MiaTopic() {
}
bool MiaTopic::exists(MiaFact* pFact) {
	MiaFact* pExists = NULL ;
	for(AiPair* pFacts = getFacts() ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pExists = asFact(car(pFacts)) ;
		if(pExists->equal(pFact))
			return true ;
	}
	return false ;
}
bool MiaTopic::identicalExists(AiPair* pFacts) {
	MiaFact* pExists = NULL ;
	for( ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pExists = asFact(car(pFacts)) ;
		if(!identicalExists(pExists))
			return false ;
	}
	return true ;
}
bool MiaTopic::identicalExists(MiaFact* pFact) {
	MiaFact* pExists = NULL ;
	for(AiPair* pFacts = getFacts() ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pExists = asFact(car(pFacts)) ;
		if(pExists->identical(pFact))
			return true ;
	}
	return false ;
}
bool MiaTopic::equal(MiaTopic* pTopic) {
	MiaFact* pExists = NULL ;
	for(AiPair* pFacts = getFacts() ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pExists = asFact(car(pFacts)) ;
		if(!pTopic->exists(pExists))
			return false ;
	}
	return true ;
}
bool MiaTopic::identical(MiaTopic* pTopic) {
	MiaFact* pExists = NULL ;
	for(AiPair* pFacts = getFacts() ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pExists = asFact(car(pFacts)) ;
		if(!pTopic->identicalExists(pExists))
			return false ;
	}
	return true ;
}
//f6:note:override boolean is to force copying of noncopyable states. primarily to copy output.
//f6:note:replace is to tell state to replace existing topic with new : copy-on-write
MiaTopic* MiaTopic::copyTo(MiaSpace& space, bool override, bool replace) {
	if(!isCopyable() & !override)
		return NULL ;
	//else
	MiaTopic* pClone = new MiaTopic(space, getSubject()) ;
	AiPair* pSrcFacts = getFacts() ;
	MiaFact* pSrcFact = NULL ;
	//TODO:to clone or not to clone, that is the question.
	#if MIA_OPTION_TOPIC_DEEPCOPY
		MiaFact* pDstFact = NULL ;
		for(AiPair* pFactPair = pSrcFacts ; pFactPair != NULL ; pFactPair = pairCdr(pFactPair)) {
			pSrcFact = asFact(car(pFactPair)) ;
			if(pSrcFact->isCopyable()) {
				pDstFact = pSrcFact->clone() ;
				pClone->addFact(pDstFact) ;
			}
		}
	#else
	//just copy pointers ...
	for(AiPair* pFactPair = pSrcFacts ; pFactPair != NULL ; pFactPair = pairCdr(pFactPair)) {
		pSrcFact = asFact(car(pFactPair)) ;
		if(pSrcFact->isCopyable())
			pClone->addFact(pSrcFact) ;
	}
	#endif //MIA_OPTION_TOPIC_DEEPCOPY
	//f6:newstuff:copy-on-write
	if(replace)
		space.replaceTopic(pClone) ;
	else
		space.addTopic(pClone) ;
	return pClone ;
	//f6:newstuff:copy-on-write:end
}
void MiaTopic::assertFact(MiaSpace* pRequester, MiaFact* pFact) {
	//f6:newstuff:copy-on-write
	#if	MIA_OPTION_COPYONWRITE
	if(pRequester != getSpace()) {
		MiaTopic* pClone = copyTo(pRequester, true, true) ;
		pClone->assertFact(pRequester, pFact) ;
		return ;
	}
	#endif
	//f6:newstuff:copy-on-write:end
	if(pFact->getTruth() == 0)
		return ;
	//else
	if(pFact->getTruth() < 0) {
		retractFact(pFact) ;
		return ;
	}
	//else
	//we also don't wan't redundant facts...
	MiaFact* pRedundant = NULL ;
	for(AiPair* pFacts = getFacts() ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pRedundant = asFact(car(pFacts)) ;
		if(pRedundant == NULL)
			continue ;
		if( (pRedundant->getSubject() == pFact->getSubject()) &&
			(pRedundant->getLink() == pFact->getLink()) &&
			(pRedundant->getValue() == pFact->getValue()) ) {
			return ;
			}
	}
	//
	addFact(pFact) ;
}
void MiaTopic::addFact(MiaFact* pFact) {
	m_facts.push_back(pFact) ;
}
void MiaTopic::retractFact(MiaFact* pFact) {
	if(m_facts.empty())
		return ;
	//else
	AiPair* pMyFacts = getFacts() ;
	AiPair* pHead = pMyFacts ;
	MiaFact* pRetract = NULL ;
	for(AiPair* pFacts = pMyFacts ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pRetract = asFact(car(pFacts)) ;
		if( (pRetract->getSubject() == pFact->getSubject()) &&
			(pRetract->getLink() == pFact->getLink()) &&
			(pRetract->getValue() == pFact->getValue()) ) {
			if(pFacts == pMyFacts)
				pMyFacts = pairCdr(pFacts) ;
			else
				pHead->p_right = cdr(pFacts) ;
			break ;
		}
		pHead = pFacts ;
	}
	m_facts.set(pMyFacts) ;
}
bool MiaTopic::match(MiaPattern& pattern) {
	MiaFact* pMemFact = NULL ;
	for(AiPair* pFacts = getFacts() ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pMemFact = asFact(car(pFacts)) ;
		if(pattern.match(pMemFact))
			return true ;
	}
	return false ;
	//return outerMatch(pattern) ;
}
//TODO:reimplement
bool MiaTopic::outerMatch(MiaPattern& pattern) {
	MiaFact* pSubject = getSubject() ;
	if(pSubject->isIdentifier()) {
		MiaSpace* pSpace = asIdentifier(pSubject)->getSpace() ;
		if(pSpace != NULL && pSpace != p_space) {
			MiaTopic* pTopic = pSpace->lookup(pSubject) ;
			if(pTopic != NULL && pTopic->p_space != p_space)
				return pTopic->match(pattern) ;
		}
		//else
		return false ;
	}
	return false ;
}
bool MiaTopic::match(MiaPatterns& patterns) {
	for(MiaPatternIter iter = patterns.begin() ; iter != patterns.end() ; ++iter) {
		if(!match(*iter))
			return false ;
	}
	return true ;
}
void MiaTopic::seek(MiaSearch& search) {
	switch(search.getResultType()) {
		case SEARCHRESULT_VALUE :
			seekValues(search) ;
			break ;
		default :
			bwAssert(0) ;
	}
	//return outerSeek(search) ;
}
//TODO:reimplement
void MiaTopic::outerSeek(MiaSearch& search) {
	MiaFact* pSubject = getSubject() ;
	if(pSubject->isIdentifier()) {
		MiaSpace* pSpace = asIdentifier(pSubject)->getSpace() ;
		if(pSpace != NULL && pSpace != p_space) {
			MiaTopic* pTopic = pSpace->lookup(pSubject) ;
		if(pTopic != NULL && pTopic != this)
			return pTopic->seek(search) ;
		}
	}
}
void MiaTopic::seekValues(MiaSearch& search) {
	MiaFact* pMemFact = NULL ;
	for(AiPair* pFacts = getFacts() ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pMemFact = asFact(car(pFacts)) ;
		if(!search.match(pMemFact))
			continue ;
		//else
		search.addResult(pMemFact->getValue()) ;
	}
}
//
void MiaTopic::printFacts(MiaPrinter& printer) {
	MiaFact* pFact = NULL ;
	for(AiPair* pFacts = getFacts() ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pFact = static_cast<MiaFact*>(car(pFacts)) ;
		printer << *pFact << endl ;
	}
}
MiaPrinter& operator<<(MiaPrinter& printer, const MiaTopic& data) {
	MiaFact* pFact = NULL ;
	printer << "<topic>\n" ;
	for(AiPair* pFacts = data.getFacts() ; pFacts != NIL ; pFacts = pairCdr(pFacts)) {
		pFact = asFact(car(pFacts)) ;
		printer << "   " << *pFact ;
		printer << "\n" ;
	}
	printer << "</topic>\n" ;

	return printer ;
}

//
//MiaTopicKit
//
DEFINE_KITTYPE(MiaTopicKit) ;

TYPEINFO_NONE(MiaTopicKit) ;
NO_KITINFO(MiaTopicKit) ;

KITINFO("MiaTopicKit", MIA_KT_TOPIC, MiaTopicKit) ;
