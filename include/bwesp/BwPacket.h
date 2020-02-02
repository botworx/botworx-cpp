#ifndef _BwPacket_H
#define _BwPacket_H

typedef std::bitset<sizeof(unsigned int)> BwPacketFlags ;
typedef unsigned int BwDataLength ;

#define ESP_MAXDATALENGTH 448

enum BwPacketFlagEnum
{
	ESP_EOS = 0, //End Of Stream
	ESP_EOT		//End Of Transmission
};

struct BwPacket {
	BwPacket() {
		reset() ;
	}
	void reset() {
		m_flags = 0 ;
		m_dataLength = 0 ;
	}
	void setEos(bool val) { 
		m_flags[ESP_EOS] = val ;
		m_flags[ESP_EOT] =	val ;
	}
	bool eos() { return m_flags[ESP_EOS] ;}
	void setEot(bool val) { m_flags[ESP_EOT] = val ; }
	bool eot() { return m_flags[ESP_EOT] ;}
	//
	char& getData() { return m_data[0] ; }
	//Data Members
	BwPacketFlags	m_flags ;
	BwDataLength	m_dataLength ;
	char			m_data[ESP_MAXDATALENGTH] ;
};

#endif //_BwPacket_H
