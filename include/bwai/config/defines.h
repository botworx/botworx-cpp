/*Botworx AI - An Artificial Intelligence Framework
Copyright (C) 2004  Kurtis Fields. See BotworxAI_License.txt for details.
*/
#ifndef _Ai_defines_H
#define _Ai_defines_H

class BwFileKit ;
class AiBufferKit ;

class AiNumberKit ;
class AiPairKit ;
class AiMultiKit ;
class AiSymbolKit ;
//class AiClassKit ;
//class AiObjectKit ;
class AiStringKit ;
class AiXStringKit ;
class AiNumberKit ;
class AiIntKit ;
class AiFloatKit ;
class AiBlobKit ;
class AiNumberKit ;
class AiPairKit ;
class AiMultiKit ;

class AiPrinter ;

class AiString ;
typedef boost::intrusive_ptr<AiString> AiStringPtr ;

class AiSymbol ;
typedef boost::intrusive_ptr<AiSymbol> AiSymbolPtr ;

class AiPair ;
typedef boost::intrusive_ptr<AiPair> AiPairPtr ;

//TODO:Do we really want ref counts on types?
class AiBlobType ;
typedef boost::intrusive_ptr<AiBlobType> AiBlobTypePtr ;

#endif //_Ai_defines_H