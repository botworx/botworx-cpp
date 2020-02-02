/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _MiaStage_H
#define _MiaStage_H

#include <bwcore/BwStage.h>
class MiaState ;

class MiaStage ;

template<>
struct BwSigT<MiaStage> : BwSigT<BwStage> {
	typedef MiaState	T_Part ;
} ;
typedef BwStageT<MiaStage, BwStage> MiaStageBase ;

class MiaStage : public MiaStageBase {
public:
	MiaStage() ;
	virtual void doStep(BwStepper& stepper) ;
	virtual bool onPostStep(BwStepper& stepper) ;
	virtual void onActorStep(T_Part *pActor) ;
	MiaState* getOwner() ;
	MiaState& owner() ;
	//Data Members
	float m_maxValue ;
	MiaState* p_superiorState ;
};

#endif //_MiaStage_H
