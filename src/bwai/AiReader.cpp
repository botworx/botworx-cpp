/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#include "stdafx.h"

#include <bwai/AiXString.h>
#include <bwai/AiInt.h>
#include <bwai/AiFloat.h>

#include <bwai/AiReader.h>

//
//Forward Declarations
//
char *g_charMap ;

//
//AiReader
//
AiReader::AiReader(std::istream& in) {
	p_in = &in ;
	reset() ;
}
void AiReader::reset() {
	m_readNdx = 0 ;
	m_writeNdx = 0 ;
	m_lineBuffer[0] = 0 ;
	m_lineNumber = 0 ;
	m_copyBuffer[0] = 0 ;
	m_rdrEof = false ;
	f_allCaps = true ;
}
char AiReader::readChar() {
	return p_in->get() ;
}
void AiReader::copyChar() {
	if(f_allCaps == true) {
		m_copyBuffer[m_writeNdx++] 
			= toupper(m_lineBuffer[m_readNdx]) ;
	}
	else {
		m_copyBuffer[m_writeNdx++] 
			= m_lineBuffer[m_readNdx] ;
	}
}
void AiReader::startCopy() {
	m_writeNdx = 0 ; // reset
	m_readNdx-- ;	// backup the readNdx
}
void AiReader::endCopy() {
	m_copyBuffer[m_writeNdx] = 0 ; // terminate string
}
BwCell* AiReader::skipLine() {
	char c ;
	while(true) {
		c = readChar() ; //get next char
		if(c == '\n') break ;
	}
	m_lineNumber++ ;
	return NULL ;
}
int AiReader::absorbLine() {
	int count = 0 ;
	char c ;
	if( m_rdrEof == true )
		return count ; //TODO: ... set reason then return?
	while(true) {
		c = readChar() ; //get next char
		if(c == -1) {
			m_rdrEof = true ;
			break ;
		}
		if(c == '\n') break ;
		m_lineBuffer[count++] = c ;
	}
	m_lineBuffer[count] = 0 ;

	m_readNdx = 0 ;
	m_lineNumber++ ;
	return count ;
}
/* advance - skips white space in input file */
char AiReader::advance() {
	char c ;
	while(true) {
		c = readChar() ; //get next char
		if(c == ';') {
			skipLine() ;
			continue ;
		}
		if(strchr(" \t\n",c) != NULL) continue ;
		else {
			break ;
		}
	}
  return (c);
}
BwCell* AiReader::readNumber()
{
	bool copying = true, isfloat = false ;
	int chartype ;
	char charval ;
		
	startCopy() ;

	while(copying == true)
	{
		charval = m_lineBuffer[m_readNdx] ;
		chartype = g_charMap[charval] ;

		switch(chartype)
		{
		case ATT_NUMERIC :
			copyChar() ;
			m_readNdx++ ;
			break ;
		case ATT_PERIOD :
			isfloat = true ;
		case ATT_MINUS :
		case ATT_PLUS :
			copyChar() ;
			m_readNdx++ ;
			break ;
		default :
			copying = false ;
		}
	}

	endCopy() ;

	BwCell *rentaNum = NULL ;
	if(isfloat == false)
		rentaNum = new AiInt(atoi(m_copyBuffer)) ;
	else
		rentaNum = new AiFloat((float)atof(m_copyBuffer)) ;
	return rentaNum ;
}
BwCell* AiReader::readString()
{
	bool copying = true ;
	int chartype ;
	char charval ;
	m_readNdx++ ; //skip the leading quote
	f_allCaps = false ; //turn off case conversion
	startCopy() ;

	while(copying == true) {
		charval = m_lineBuffer[m_readNdx] ;
		chartype = g_charMap[charval] ;

		switch(chartype) {
		case ATT_DOUBLEQUOTE :
			copying = false ;
			break ;
		default :
			copyChar() ;
			break ;
		}
		m_readNdx++ ;
	}
	endCopy() ;
	AiString* pString = new AiString(m_copyBuffer) ;
	f_allCaps = true ; //turn on case conversion
	return pString ;
}
BwCell* AiReader::readXString()
{
	bool copying = true ;
	int chartype ;
	char charval ;
	m_readNdx++ ; //skip the leading quote
	f_allCaps = false ; //turn off case conversion
	startCopy() ;

	while(copying == true) {
		charval = m_lineBuffer[m_readNdx] ;
		chartype = g_charMap[charval] ;

		switch(chartype) {
		case ATT_BAR :
			copying = false ;
			break ;
		default :
			copyChar() ;
			break ;
		}
		m_readNdx++ ;
	}
	endCopy() ;
	AiXString* pString = new AiXString(m_copyBuffer) ;
	f_allCaps = true ; //turn on case conversion
	return pString ;
}
BwCell* AiReader::readSymbol()
{
	bool copying = true ;
	bool fPair = false ;
	AiSymbol* pSym = NULL ;
	BwCell* pVal = NULL ;
	int chartype ;
	char charval ;

	startCopy() ;

	while(copying == true) {
		charval = m_lineBuffer[m_readNdx] ;
		chartype = g_charMap[charval] ;

		switch(chartype) {
		case ATT_ALPHA :
		case ATT_UNDERSCORE :
		case ATT_PERIOD :
		case ATT_COLON :
		case ATT_QUESTION :
		case ATT_DOLLAR :
		case ATT_MINUS :
		case ATT_PLUS :
		case ATT_STAR :
		case ATT_SLASH :
		case ATT_GREATERTHAN :
		case ATT_LESSTHAN :
		case ATT_NUMERIC :
		case ATT_EQUAL :
			copyChar() ;
			m_readNdx++ ;
			break ;
		default :
			copying = false ;
		}
	}
	if(fPair == true)
		return new AiPair(pSym, pVal) ;
	//else
	endCopy() ;
	if(strcmp(m_copyBuffer, "NIL"))
		pSym = intern(m_copyBuffer) ;
	return pSym ;
}

BwCell* AiReader::readList()
{
	AiPair* pList = NULL ;
	AiPair* pPair = NULL ;
	AiPair* pPrevPair = NULL ;
	pPrevPair = NULL ;
	
	for(BwCell* pChild = readExpr() ; pChild != SYM_EOL ; pChild = readExpr())
	{
		pPair = cons(NIL, NIL) ;
		if(pPrevPair != NULL) {
			pPrevPair->p_right = pPair ;
			pPrevPair = pPair ;
		}
		else {
			pList = pPair ;
			pPrevPair = pPair ;
		}
		pPair->p_left = pChild ;
	}

	return pList ;
}
BwCell* AiReader::readQuoted() {
	BwCell* pQuoted = readExpr() ;
	return cons(SYM_QUOTE, consa(pQuoted)) ;
}
BwCell* AiReader::readExpr()
{
	char charval ;
	int chartype ;

	while(true)
	{
		charval = m_lineBuffer[m_readNdx++] ;
		if(charval == -1)
			return SYM_EOF ;
		chartype = g_charMap[charval] ;
	
		switch(chartype)
		{
		case ATT_DOUBLEQUOTE :
			return readString() ;
		case ATT_BAR :
			return readXString() ;
		case ATT_QUOTE :
			return readQuoted() ;
		case ATT_MINUS :
		case ATT_PLUS :
			charval = m_lineBuffer[m_readNdx] ;
			chartype = g_charMap[charval] ;
			switch(chartype) {
				case ATT_NUMERIC :
					return readNumber() ;
				default :
					return readSymbol() ;
			}
		case ATT_NUMERIC :
			return readNumber() ;

		case ATT_GREATERTHAN :
		case ATT_LESSTHAN :
		case ATT_EQUAL :
		case ATT_STAR :
		case ATT_SLASH :
		case ATT_PERIOD :
		case ATT_COLON :
		case ATT_QUESTION :
		case ATT_DOLLAR :
		case ATT_ALPHA :
			return readSymbol() ;
		case ATT_LEFTPAREN :
		case ATT_LEFTBRACE :
			return readList() ;
		case ATT_RIGHTPAREN :
		case ATT_RIGHTBRACE :
			return SYM_EOL ;
		case ATT_SEMICOLON :
		case ATT_EOL :
			if(absorbLine() == 0)
				return SYM_EOF ;
		}
	}
}
char AiReader::g_charMap[256] = {
	ATT_EOL,			//00
	ATT_ERROR,		//01
	ATT_ERROR,		//02
	ATT_ERROR,		//03
	ATT_ERROR,		//04
	ATT_ERROR,		//05
	ATT_ERROR,		//06
	ATT_ERROR,		//07
	ATT_ERROR,		//08
	ATT_WHITESPACE,	//09
	ATT_ERROR,		//10
	ATT_ERROR,		//11
	ATT_ERROR,		//12
	ATT_ERROR,		//13
	ATT_ERROR,		//14
	ATT_ERROR,		//15
	ATT_ERROR,		//16
	ATT_ERROR,		//17
	ATT_ERROR,		//18
	ATT_ERROR,		//19
	ATT_ERROR,		//20
	ATT_ERROR,		//21
	ATT_ERROR,		//22
	ATT_ERROR,		//23
	ATT_ERROR,		//24
	ATT_ERROR,		//25
	ATT_ERROR,		//26
	ATT_ERROR,		//27
	ATT_ERROR,		//28
	ATT_ERROR,		//29
	ATT_ERROR,		//30
	ATT_ERROR,		//31
	ATT_WHITESPACE,	//32
	ATT_NOT,			//33
	ATT_DOUBLEQUOTE,		//34
	ATT_POUND,		//35
	ATT_DOLLAR,		//36
	ATT_PERCENT,		//37
	ATT_AND,			//38
	ATT_QUOTE,		//39 '
	ATT_LEFTPAREN,	//40 (
	ATT_RIGHTPAREN,	//41 )
	ATT_STAR,		//42 *
	ATT_PLUS,		//43 +
	ATT_COMMA,		//44 ,
	ATT_MINUS,		//45 -
	ATT_PERIOD,		//46 .
	ATT_SLASH,		//47 /
	ATT_NUMERIC,		//48
	ATT_NUMERIC,		//49
	ATT_NUMERIC,		//50
	ATT_NUMERIC,		//51
	ATT_NUMERIC,		//52
	ATT_NUMERIC,		//53
	ATT_NUMERIC,		//54
	ATT_NUMERIC,		//55
	ATT_NUMERIC,		//56
	ATT_NUMERIC,		//57
	ATT_COLON,		//58 :
	ATT_SEMICOLON,	//59 ;
	ATT_LESSTHAN,	//60 <
	ATT_EQUAL,		//61 =
	ATT_GREATERTHAN,	//62 >
	ATT_QUESTION,	//63 ?
	ATT_AT,			//64 @
	ATT_ALPHA,		//65 A
	ATT_ALPHA,		//66 B
	ATT_ALPHA,		//67 C
	ATT_ALPHA,		//68 D
	ATT_ALPHA,		//69 E
	ATT_ALPHA,		//70 F
	ATT_ALPHA,		//71 G
	ATT_ALPHA,		//72 H
	ATT_ALPHA,		//73 I
	ATT_ALPHA,		//74 J
	ATT_ALPHA,		//75 K
	ATT_ALPHA,		//76 L
	ATT_ALPHA,		//77 M
	ATT_ALPHA,		//78 N
	ATT_ALPHA,		//79 O
	ATT_ALPHA,		//80 P
	ATT_ALPHA,		//81 Q
	ATT_ALPHA,		//82 R
	ATT_ALPHA,		//83 S
	ATT_ALPHA,		//84 T
	ATT_ALPHA,		//85 U
	ATT_ALPHA,		//86 V
	ATT_ALPHA,		//87 W
	ATT_ALPHA,		//88 X
	ATT_ALPHA,		//89 Y
	ATT_ALPHA,		//90 Z
	ATT_LEFTBRACKET,	//91 ]
	ATT_BACKSLASH,	//92
	ATT_RIGHTBRACKET,//93 [
	ATT_CARET,		//94 ^
	ATT_UNDERSCORE,	//95 _
	ATT_BACKQUOTE,	//96 `
	ATT_ALPHA,		//97 a
	ATT_ALPHA,		//98 b
	ATT_ALPHA,		//99 c
	ATT_ALPHA,		//100 d
	ATT_ALPHA,		//101 e
	ATT_ALPHA,		//102 f
	ATT_ALPHA,		//103 g
	ATT_ALPHA,		//104 h
	ATT_ALPHA,		//105 i
	ATT_ALPHA,		//106 j
	ATT_ALPHA,		//107 k
	ATT_ALPHA,		//108 l
	ATT_ALPHA,		//109 m
	ATT_ALPHA,		//110 n
	ATT_ALPHA,		//111 o
	ATT_ALPHA,		//112 p
	ATT_ALPHA,		//113 q
	ATT_ALPHA,		//114 r
	ATT_ALPHA,		//115 s
	ATT_ALPHA,		//116 t
	ATT_ALPHA,		//117 u
	ATT_ALPHA,		//118 v
	ATT_ALPHA,		//119 w
	ATT_ALPHA,		//120 x
	ATT_ALPHA,		//121 y
	ATT_ALPHA,		//122 z
	ATT_LEFTBRACE,	//123 {
	ATT_BAR,			//124 |
	ATT_RIGHTBRACE,	//125 }
	ATT_TILDE,		//126 ~
	ATT_ERROR,		//127
	ATT_ERROR,		//128
	ATT_ERROR,		//129
	ATT_ERROR,		//130
	ATT_ERROR,		//131
	ATT_ERROR,		//132
	ATT_ERROR,		//133
	ATT_ERROR,		//134
	ATT_ERROR,		//135
	ATT_ERROR,		//136
	ATT_ERROR,		//137
	ATT_ERROR,		//138
	ATT_ERROR,		//139
	ATT_ERROR,		//140
	ATT_ERROR,		//141
	ATT_ERROR,		//142
	ATT_ERROR,		//143
	ATT_ERROR,		//144
	ATT_ERROR,		//145
	ATT_ERROR,		//146
	ATT_ERROR,		//147
	ATT_ERROR,		//148
	ATT_ERROR,		//149
	ATT_ERROR,		//150
	ATT_ERROR,		//151
	ATT_ERROR,		//152
	ATT_ERROR,		//153
	ATT_ERROR,		//154
	ATT_ERROR,		//155
	ATT_ERROR,		//156
	ATT_ERROR,		//157
	ATT_ERROR,		//158
	ATT_ERROR,		//159
	ATT_ERROR,		//160
	ATT_ERROR,		//161
	ATT_ERROR,		//162
	ATT_ERROR,		//163
	ATT_ERROR,		//164
	ATT_ERROR,		//165
	ATT_ERROR,		//166
	ATT_ERROR,		//167
	ATT_ERROR,		//168
	ATT_ERROR,		//169
	ATT_ERROR,		//170
	ATT_ERROR,		//171
	ATT_ERROR,		//172
	ATT_ERROR,		//173
	ATT_ERROR,		//174
	ATT_ERROR,		//175
	ATT_ERROR,		//176
	ATT_ERROR,		//177
	ATT_ERROR,		//178
	ATT_ERROR,		//179
	ATT_ERROR,		//180
	ATT_ERROR,		//181
	ATT_ERROR,		//182
	ATT_ERROR,		//183
	ATT_ERROR,		//184
	ATT_ERROR,		//185
	ATT_ERROR,		//186
	ATT_ERROR,		//187
	ATT_ERROR,		//188
	ATT_ERROR,		//189
	ATT_ERROR,		//190
	ATT_ERROR,		//191
	ATT_ERROR,		//192
	ATT_ERROR,		//193
	ATT_ERROR,		//194
	ATT_ERROR,		//195
	ATT_ERROR,		//196
	ATT_ERROR,		//197
	ATT_ERROR,		//198
	ATT_ERROR,		//199
	ATT_ERROR,		//200
	ATT_ERROR,		//201
	ATT_ERROR,		//202
	ATT_ERROR,		//203
	ATT_ERROR,		//204
	ATT_ERROR,		//205
	ATT_ERROR,		//206
	ATT_ERROR,		//207
	ATT_ERROR,		//208
	ATT_ERROR,		//209
	ATT_ERROR,		//210
	ATT_ERROR,		//211
	ATT_ERROR,		//212
	ATT_ERROR,		//213
	ATT_ERROR,		//214
	ATT_ERROR,		//215
	ATT_ERROR,		//216
	ATT_ERROR,		//217
	ATT_ERROR,		//218
	ATT_ERROR,		//219
	ATT_ERROR,		//220
	ATT_ERROR,		//221
	ATT_ERROR,		//222
	ATT_ERROR,		//223
	ATT_ERROR,		//224
	ATT_ERROR,		//225
	ATT_ERROR,		//226
	ATT_ERROR,		//227
	ATT_ERROR,		//228
	ATT_ERROR,		//229
	ATT_ERROR,		//230
	ATT_ERROR,		//231
	ATT_ERROR,		//232
	ATT_ERROR,		//233
	ATT_ERROR,		//234
	ATT_ERROR,		//235
	ATT_ERROR,		//236
	ATT_ERROR,		//237
	ATT_ERROR,		//238
	ATT_ERROR,		//239
	ATT_ERROR,		//240
	ATT_ERROR,		//241
	ATT_ERROR,		//242
	ATT_ERROR,		//243
	ATT_ERROR,		//244
	ATT_ERROR,		//245
	ATT_ERROR,		//246
	ATT_ERROR,		//247
	ATT_ERROR,		//248
	ATT_ERROR,		//249
	ATT_ERROR,		//250
	ATT_ERROR,		//251
	ATT_ERROR,		//252
	ATT_ERROR,		//253
	ATT_ERROR,		//254
	ATT_ERROR			//255
};