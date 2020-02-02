#ifndef _AxlScope_h
#define _AxlScope_h

class AxlBx ;
//
//AxlScope
//
class AxlScope : public BwCell {
public:
	AxlBx *p_bx ;
	AxlScope *p_superScope ;
} ;
#define isAxlScope(C) (C->m_typeID == TT_SCOPE) //TODO: ... this is an abstract base!
#define ofAxlScope(X) (ofTT(X, TT_SCOPE))
#define asAxlScope(C) ((AxlScope*)C)

#endif//_AxlScope_h
