#ifndef _BwConnection_H
#define _BwConnection_H

struct BwPacket ;
class BwConnectionData ;
class BwConnectionGroup ;

class BwConnection {
public:
	BwConnection();
	virtual ~BwConnection();
	bool connect(const bwString& hostName, const bwString& serviceName);
	BwConnectionData* listen(bwInt32U nSocketPort = 0, int nConnectionBacklog=5);
	int send(BwPacket& packet);
	int receive(BwPacket& packet);
	//
	BwConnectionGroup* p_group ;
	BwConnectionData* p_data ;
};
#endif //_BwConnection_H
