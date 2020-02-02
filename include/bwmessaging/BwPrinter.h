#ifndef _BwPrinter_h
#define _BwPrinter_h

#include "BwMailSlot.h"

class BwSink ;
class BwPrinter ;

class BwSink {
public:
	BwSink(bool internal = false) : m_isInternal(internal), m_isEnabled(true), p_previous(nullptr) {}
	virtual void puts(const char *s) = 0 ;
	virtual void flush() = 0 ;
	bool isInternal() { return m_isInternal ; }
	bool isEnabled() { return m_isEnabled ; }
	bool isDisabled() { return !m_isEnabled ; }
	void setPrevious(BwSink* pPrevious) { p_previous = pPrevious ; }
	BwSink* getPrevious() { return p_previous ; }
	enum { FLUSH_THRESHOLD = 1024 } ; //was 4096 :)
	/*Data Members*/
public:
	bool m_isInternal ; //embedded within printer...
	bool m_isEnabled ;
	BwSink* p_previous ; //used for sink stack
} ;
inline BwSink& operator<<(BwSink &sink, const bwString& val) { sink.puts(val.c_str()) ; return sink ; }

class BwStreamSink : public BwSink {
public:
	BwStreamSink(bool internal = false) : BwSink(internal), p_stream(nullptr) {}
	void setStream(std::ostream& stream) { p_stream = &stream ; }
	std::ostream* getStream() { return p_stream ; }
	virtual void puts(const char *s) { stream() << s ; }
	virtual void flush() { stream().flush() ; }
	std::ostream& stream() { return *p_stream ; }
	//Data Members
	std::ostream *p_stream ;
} ;
class BwStringSink : public BwSink {
public:
	BwStringSink(bool internal = false) : BwSink(internal) {}
	void setString(bwString& string) { p_string = &string ; }
	bwString* getString() { return p_string ; }
	virtual void puts(const char *s) { string() += s ; }
	virtual void flush() { return ; }
	bwString& string() { return *p_string ; }
	//Data Members
	bwString *p_string ;
} ;
typedef std::vector<char> BwCharVector ;
class BwCharVectorSink : public BwSink {
public:
	BwCharVectorSink(bool internal = false) : BwSink(internal) {}
	void setVector(BwCharVector& vector) { p_vector = &vector ; }
	BwCharVector* getVector() { return p_vector ; }
	virtual void puts(const char *s) ;
	virtual void flush() { return ; }
	BwCharVector& vector() { return *p_vector ; }
	bwString string() { return bwString(&vector()[0]) ; }
	//Data Members
	BwCharVector *p_vector ;
} ;
class BwMailSlotSink : public BwSink {
public:
	BwMailSlotSink(bool internal = false) : BwSink(internal), p_slot(nullptr) {}
	void setMailslot(BwMailSlot *pSlot) { p_slot = pSlot ; }
	BwMailSlot* getMailslot() { return p_slot ; }
	virtual void puts(const char *s) {
		if(isDisabled())
			return ;
		m_buffer += s ;
		if(m_buffer.length() > FLUSH_THRESHOLD)
			flush() ;
	}
	virtual void flush() ;
	/*Data Members*/
public:
	BwMailSlot *p_slot ;
	bwString m_buffer ;
} ;
class BwPrinter {
public:
	BwPrinter() ;
	BwPrinter(std::ostream& out) ;
	BwPrinter(BwSink* pSink) ;
	~BwPrinter() ;

	void pushSink(BwSink* pSink) ;
	BwSink* popSink() ;
	BwSink* getSink() { return p_sink ; }

	void print(const bwString& val) { p_sink->puts(val.c_str()) ; }
	void printLn(const bwString& val) {	p_sink->puts(val.c_str()) ; p_sink->puts("\n") ; }
	void puts(const char *s) {	p_sink->puts(s) ; if(p_chain != nullptr) p_chain->puts(s) ; }
	void flush() {	p_sink->flush() ; if(p_chain != nullptr) p_chain->flush() ; }
	BwSink& sink() { return *p_sink ; }
	void chain(BwPrinter* pChain) { p_chain = pChain ; }
	void unchain() { p_chain = nullptr ; }
	BwPrinter& operator<<(BwPrinter& (__cdecl *_Pfn)(BwPrinter&))
	{	// manip caller
		return ((*_Pfn)(*this));
	}
protected:
	//Data Members
	BwStreamSink m_streamSink ;
	BwSink* p_sink ;
	BwPrinter* p_chain ;
} ;
inline BwPrinter& operator<<(BwPrinter &printer, const bwString& val) { printer.print(val) ; return printer ; }
//Manips
inline BwPrinter& endl(BwPrinter& printer) { printer << "\n" ; return printer ; }
inline BwPrinter& flush(BwPrinter& printer) { printer.flush() ; return printer ; }
//
BwPrinter& operator<<(BwPrinter &printer, long val) ;
BwPrinter& operator<<(BwPrinter &printer, int val) ;
BwPrinter& operator<<(BwPrinter &printer, double val) ;
BwPrinter& operator<<(BwPrinter &printer, float val) ;

#endif//_BwPrinter_h
