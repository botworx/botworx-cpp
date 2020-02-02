/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _AiReader_H
#define _AiReader_H

class AiReader {
public:
	AiReader(std::istream& in) ;
	void* operator new(size_t count) {
		return BW_USERMALLOC(count, TT_EXO_UNKNOWN) ;
	}
	void operator delete(void* object) {
		BW_USERFREE(object, TT_EXO_UNKNOWN) ;
	}
	BwCell* readExpr() ;
protected:
	char readChar() ;
	void reset() ;
	void copyChar() ;
	void startCopy() ;
	void endCopy() ;
	BwCell* skipLine() ;
	int absorbLine() ;
	char advance() ;
	BwCell* readNumber() ;
	BwCell* readString() ;
	BwCell* readXString() ;
	BwCell* readSymbol() ;
	BwCell* readList() ;
	BwCell* readQuoted() ;
	//Data
	std::istream* p_in ;

	bool	m_rdrEof ;
	char	m_lineBuffer[1024] ;
	int		m_lineNumber ;
	//
	int		m_readNdx ;
	char	m_copyBuffer[1024] ;
	int		m_writeNdx ;
	bool f_allCaps ;
	//
	static char g_charMap[] ;
} ;
#define asAiReader(X) ((AiReader*)X)
//
enum AiTokenTTs
{
	ATT_EOL,		//00
	ATT_ERROR,		//01
	ATT_WHITESPACE,	//02
	ATT_NOT,			//03
	ATT_POUND,		//05
	ATT_DOLLAR,		//06
	ATT_PERCENT,		//07
	ATT_AND,			//08
	ATT_QUOTE,		//'
	ATT_BACKQUOTE,	//`
	ATT_DOUBLEQUOTE,	//"
	ATT_LEFTPAREN,	//10
	ATT_RIGHTPAREN,	//11
	ATT_STAR,		//12
	ATT_PLUS,		//13
	ATT_COMMA,		//14
	ATT_MINUS,		//15
	ATT_PERIOD,		//16
	ATT_SLASH,		//17
	ATT_NUMERIC,		//18
	ATT_COLON,		//19
	ATT_SEMICOLON,	//20
	ATT_LESSTHAN,	//21
	ATT_EQUAL,		//22
	ATT_GREATERTHAN,	//23
	ATT_QUESTION,	//24
	ATT_AT,			//25
	ATT_ALPHA,		//26
	ATT_LEFTBRACKET,	//27
	ATT_BACKSLASH,	//28
	ATT_RIGHTBRACKET,//29
	ATT_CARET,		//30
	ATT_UNDERSCORE,	//31
	ATT_LEFTBRACE,	//33
	ATT_BAR,			//34
	ATT_RIGHTBRACE,	//35
	ATT_TILDE		//36
} ;

#endif //_AiReader_H
