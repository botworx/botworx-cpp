#ifndef  _BwCBuffer_H
#define _BwCBuffer_H

#include "BwConnection.h"
#include "BwPacket.h"

typedef std::char_traits<char>::int_type espInt ;

class BwCBuffer : public std::stringbuf {
	//Type Defs
	typedef std::stringbuf super_t ;
public:
	BwCBuffer(BwConnection& connection);
	BwCBuffer();
	void init() ;
	void reset() ;
	void resetGet() ;
	void resetPut() ;
	virtual ~BwCBuffer();
	//std overrides
	virtual std::streamsize showmanyc();
	virtual espInt underflow();
	virtual espInt overflow(espInt ch);
	//
	espInt receivePacket();
	void sendPacket();
	int prime();
	virtual void setEot(bool val) ;
	virtual void setEos(bool val) ;
	bool eot() { return m_eot ; }
	bool eos() { return m_eos ; }
	//
	BwConnection& getConnection() { return m_connection ; }
	//Data Members
	BwConnection m_connection ;
	BwPacket m_packet ;
	bool m_primed ;
	bool m_eot ;
	bool m_eos ;
};

#endif //_BwCBuffer_H
