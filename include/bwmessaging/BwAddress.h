#ifndef _BwAddress_H
#define _BwAddress_H

class BwMailSlot ;
class BwPostOffice ;

class BwAddress {
public:
	BwAddress() ;
	BwAddress(const bwString& serverName, const bwString& serviceName) ;
	const bwString& getHostName() const { return m_hostName ; }
	const bwString& getServiceName() const { return m_serviceName ; }
	//Data Members
	bwString m_hostName ;
	bwString m_serviceName ;
	//Constants
	static const bwString DEFAULT_HOST ;
	static const bwString DEFAULT_SERVICE ;
};

#endif //_BwAddress_H
