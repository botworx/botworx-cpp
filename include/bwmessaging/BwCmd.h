#ifndef _BwCmd_H
#define _BwCmd_H

class BwCmd {
public:
	BwCmd() : m_paramTtl(0) {}
	BwCmd(const bwString& cmd) : m_paramTtl(0) {
		m_cmd += cmd ;
		m_cmd += "( " ;
	}
	BwCmd(const BwCmd& cmd) {
		m_cmd = cmd.m_cmd ;
		m_paramTtl = cmd.m_paramTtl ;
	}
	void set(const bwString& cmd) { m_cmd = cmd ; }
	const bwString& str() const { return m_cmd ; }
	const char* c_str() const { return m_cmd.c_str() ; }
	BwCmd& addParam(const bwString& param) {
		if(m_paramTtl != 0)
			m_cmd += ", " ;
		m_cmd += param ;
		m_paramTtl++ ;
		return *this ;
	}
	BwCmd& addInt(const int val) {
	    const size_t bufferSize = 16;
		char buffer[bufferSize] ;
		//snprintf(buffer, bufferSize, "%d", val);
		//_itoa(val, buffer, 10) ;
		bwItoa(val, buffer, bufferSize, 10);
		return addParam(buffer) ;
	}
	BwCmd& quote() {
		m_cmd += "\"" ;
		return *this ;
	}
	BwCmd& endq() {
		m_cmd += "\"" ;
		return close() ;
	}
	BwCmd& close() {
		m_cmd += " )" ;
		return *this ;
	}
	BwCmd& operator<<(BwCmd& (__cdecl *_Pfn)(BwCmd&))
	{	// manip caller
		return ((*_Pfn)(*this));
	}
	//Data Members
	bwString m_cmd ;
	unsigned char m_paramTtl ;
} ;
inline BwCmd& operator<<(BwCmd &cmd, const bwString& param) { return cmd.addParam(param) ; }
inline BwCmd& operator<<(BwCmd &cmd, const int intParam) { return cmd.addInt(intParam) ; }
//Manips
inline BwCmd& end(BwCmd& cmd) { return cmd.close() ; }
inline BwCmd& quote(BwCmd& cmd) { return cmd.quote() ; }
inline BwCmd& endq(BwCmd& cmd) { return cmd.endq() ; }

#endif //_BwCmd_H
