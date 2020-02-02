#ifndef _MiaFrame_H
#define _MiaFrame_H

#include "MiaMind.h"

class MiaFrame : public MiaMind {
public:
	MiaFrame (MiaMind* pParent, AiSymbol* pSymbol) ;
	virtual bool onCreate(const BwPartInfo& info) ;
	//Data Members
} ;

typedef boost::intrusive_ptr<MiaFrame> MiaFramePtr ;

#endif //_MiaFrame_H