#include "stdafx.h"

#include <bwesp/BwConnection.h>
#include <bwesp/BwPacket.h>

#include <bwcore/config/boost_asio.h>
using boost::asio::ip::tcp;



class BwConnectionGroup {
public:
	BwConnectionGroup() {}
	//Singleton support
	struct singleton_alloc {
		static BwConnectionGroup* alloc() { return new BwConnectionGroup() ; }
	} ;
	boost::asio::io_service io_service ;
	//
	typedef BwAutoSingletonT<BwConnectionGroup, singleton_alloc> singleton ;
	singleton m_singleton ;
} ;
template<> BwConnectionGroup::singleton::pointer BwConnectionGroup::singleton::g_singleton = 0 ;
//
//
//
class BwConnectionData {
public:
	//
	typedef boost::asio::io_service io_service_t ;
	typedef boost::asio::ip::tcp::socket socket_t ;
	//
	BwConnectionData(io_service_t& io_service) :
		m_socket(io_service)
	{
	}
	~BwConnectionData() {
	}
	//
	socket_t m_socket ;
} ;
//
//
//
BwConnection::BwConnection() {
	p_group = BwConnectionGroup::singleton::getPtr() ;
	p_data = nullptr ;
}
BwConnection::~BwConnection() {
}
bool BwConnection::connect(const bwString& hostName, const bwString& serviceName) {
	boost::asio::io_service& io_service = p_group->io_service ;
    tcp::resolver resolver(io_service);
	tcp::resolver::query query(hostName, serviceName);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::resolver::iterator end;

	BwConnectionData& data = *new BwConnectionData(io_service) ;
	p_data = &data ;
	tcp::socket& socket = data.m_socket ;

    boost::system::error_code error = boost::asio::error::host_not_found;
    while (error && endpoint_iterator != end)
    {
      socket.close();
      socket.connect(*endpoint_iterator++, error);
    }
    if (error)
      //throw boost::system::system_error(error);
		return false ;
	else
		return true ;
}
BwConnectionData* BwConnection::listen(uint nSocketPort, int nConnectionBacklog) {
	boost::asio::io_service& io_service = p_group->io_service ;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), nSocketPort));
	BwConnectionData& data = *new BwConnectionData(io_service) ;
	acceptor.accept(data.m_socket);
	return &data ;
}
//
int BwConnection::send(BwPacket& packet) {
	tcp::socket& socket = p_data->m_socket ;
	size_t size = sizeof(BwPacket);
    boost::system::error_code error;
	size_t count = boost::asio::write( socket, boost::asio::buffer((void*)&packet, sizeof(BwPacket)), boost::asio::transfer_all(), error );
	return count ;
}

int BwConnection::receive(BwPacket& packet) {
	tcp::socket& socket = p_data->m_socket ;
	size_t size = sizeof(BwPacket) ;
    boost::system::error_code error;
	size_t count = boost::asio::read(socket, boost::asio::buffer((void*)&packet, sizeof(BwPacket)), boost::asio::transfer_all(), error );
	std::cout << error ;
	return count ;
}
