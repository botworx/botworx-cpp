#include "stdafx.h"
#include <bwesp/BwCBuffer.h>
#include <bwesp/BwConnection.h>

BwCBuffer::BwCBuffer() {
	init() ;
}
BwCBuffer::~BwCBuffer(){
}
BwCBuffer::BwCBuffer(BwConnection& connection) : m_connection(connection) {
	init() ;
}
void BwCBuffer::init() {
	m_primed = false ;
	m_eot = false ;
	char& data = m_packet.getData() ;
	setbuf(&data, ESP_MAXDATALENGTH) ;
	reset() ;
}
void BwCBuffer::reset() {
	m_packet.reset() ;
	resetGet() ;
	resetPut() ;
}
void BwCBuffer::resetGet() {
	char *buf = &m_packet.getData() ;
	setg( buf, buf + ESP_MAXDATALENGTH, buf + ESP_MAXDATALENGTH);
}
void BwCBuffer::resetPut() {
	char *buf = &m_packet.getData() ;
	setp( buf, buf + ESP_MAXDATALENGTH);
}
void BwCBuffer::sendPacket() {
	m_packet.m_dataLength = pptr() - pbase() ;
	getConnection().send(m_packet) ;
	resetPut() ;
}
espInt BwCBuffer::receivePacket() {
	int count = getConnection().receive(m_packet) ;
	if(count == 0)
		return std::char_traits<char>::eof() ;
	if(m_packet.eot()) {
		m_eot = true ;
	}
	char& data = m_packet.getData() ;
	char *buf = &data ;
	setg( buf, buf, buf + m_packet.m_dataLength);
	return std::char_traits<char>::to_int_type(data) ;
}
espInt BwCBuffer::overflow(espInt ch) {
   sendPacket();
   return super_t::overflow( ch );
}
espInt BwCBuffer::underflow() {
	if(m_primed == false) {
		return prime() ;
	}
	//else
	if(m_eot == true) {
	//if(m_eos == true) {
		return std::char_traits<char>::eof() ;
	}
	//else
	return receivePacket();
}
int BwCBuffer::prime() {
	m_primed = true ;
	return	receivePacket();
}
std::streamsize BwCBuffer::showmanyc() {
	return 0 ;
}
void BwCBuffer::setEot(bool val) {
	m_packet.setEot(val) ;
	sendPacket() ;
}
void BwCBuffer::setEos(bool val) {
	m_packet.setEos(val) ;
	//sendPacket() ;
}
