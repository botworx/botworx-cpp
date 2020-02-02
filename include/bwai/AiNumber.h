/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiNumber_H
#define _AiNumber_H

class AiNumber : public BwCell {
public:
	AiNumber(ThingTT typeID) : BwCell(typeID) {}
} ;
#define asNumber(C) ((AiNumber*)C)
#define ofNumber(X) (ofTT(X, TT_NUMBER))
#define isNumber(X) (ofNumber(getTT(X)))

#define getNumberTT(X) (ifTT(X, TT_INT) : ifTT(X, TT_FLOAT) :  TT_NIL )

#include "AiKit.h"

class AiNumberKit : public AiKit {
public:
	AiNumberKit(KitTT typeID, AiKit*  pSuperKit, AiKitInfo *pKitInfo) 
		: AiKit(typeID, pSuperKit, pKitInfo) {}
} ;

DECLARE_KITINFO(AiNumberKit) ;
/////
DECLARE_MBINFO(TT_NUMBER) ;
//Math
extern int AiNumber_compare(AiNumber *pThis, AiNumber *pThat) ;
extern BwCell* AiNumber_equal(AiNumber *pThis, AiNumber *pThat) ;
extern BwCell* AiNumber_notEqual(AiNumber *pThis, AiNumber *pThat) ;
extern bool AiNumber_zerop(AiNumber *pThis) ;
extern AiNumber* AiNumber_sub1(AiNumber *pThis) ;
extern AiNumber* AiNumber_sub(AiNumber *pThis, AiNumber *pThat) ;
extern AiNumber* AiNumber_add(AiNumber *pThis, AiNumber *pThat) ;


#endif //_AiNumber_H
