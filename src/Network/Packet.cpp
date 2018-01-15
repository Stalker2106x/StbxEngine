#include "Network/Packet.hh"

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