#include "Network/Packet.hh"

using namespace stb;

//Pack sf::Packet
Packet::Packet(int16_t packetCode, int8_t senderId, bool serverSide)
{
	code = packetCode;
	(*_data) << code;
	(*_data) << senderId;
}

//Extract sf::Packet
Packet::Packet(std::shared_ptr<sf::Packet> packet, bool serverSide)
{
	_data = packet;
	(*_data) >> code;
	clientId = -1;
	if (serverSide)
		(*_data) >> clientId;
}

Packet::~Packet()
{

}