/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwmia/MiaPattern.h>
#include <bwmia/MiaIdentifier.h>
#include <bwmia/MiaMatcher.h>
#include <bwai/AiInt.h>

//TODO:this needs to be cleaned up!!!!
void MiaPattern::setExpr(AiPair* pExpr) {
	p_expr = pExpr ;
	//Subject
	BwCell *pSubjExpr = car(pExpr) ;
	pExpr = pairCdr(pExpr) ;
	if(isSymbol(pSubjExpr)) {
		AiSymbol *pSubjSymbol = asSymbol(pSubjExpr) ;
		if(pSubjSymbol->isLogic() || pSubjSymbol->isProperty())
			p_subject = NULL ;
		else {
			p_subject = internId(pSubjSymbol) ;
		}
	}
	else
		p_subject = NULL ;
	//Link
	AiSymbol* pLinkSymbol = asSymbol(car(pExpr)) ;
	pExpr = pairCdr(pExpr) ;
	if(pLinkSymbol->isLogic() || pLinkSymbol->isProperty())
		p_link = NULL ;
	else {
		p_link = internId(pLinkSymbol) ;
	}
	//Value
	BwCell *pValExpr = car(pExpr) ;
	pExpr = pairCdr(pExpr) ;
	if(isSymbol(pValExpr)) {
		AiSymbol *pValSymbol = asSymbol(pValExpr) ;
		if(pValSymbol->isLogic() || pValSymbol->isProperty())
			p_value = NULL ;
		else {
			p_value = internId(pValSymbol) ;
		}
	}
	else
		p_value = NULL ;
	//Truth
	if(pExpr == NULL)
		return ;
	//else
	BwCell* pTruth = car(pExpr) ;
	if(pTruth != NULL)
		m_truth = asInt(pTruth)->m_value ;
	else
		m_truth = 1 ;
}

bool MiaPattern::match(MiaBinder& binder, MiaFactoid& result) {
	MiaMatcher matcher(binder, result, *this) ;
	bool success = matcher.matchExpr(getExpr()) ;
	return success ;
}