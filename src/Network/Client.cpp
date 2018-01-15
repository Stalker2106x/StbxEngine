#include "Network/Client.hh"
#include "Network/DBWEngine.hh"
#include "Network/ClientHandler.hh"

Client::Client(bool self) : _receiver(_packetStack, _mutex, _signalMutex, _packetsWaiting), _handler(*_socket, _packetStack, _mutex, _signalMutex, _packetsWaiting)
{
	_selfServer = self;
	_socket = std::make_shared<sf::TcpSocket>();
	_id = -1;
}

Client::~Client()
{

}

sf::TcpSocket &Client::getSocket()
{
	return (*_socket);
}

void Client::disconnect(bool unexpected)
{
	_receiver.close();
	_handler.stop();
	_socket->disconnect();
	if (unexpected)
	{
		//DBWEngine::getInstance<DBWEngine>()->menu.openDialog("Disconnected", "You were disconnected from server");
	}
	std::cout << "Client Shutted down.";
}

// Should be pure virtual
/*
void Client::receiveServerInfo()
{
	sf::Clock clock;
	std::shared_ptr<Packet> packet = nullptr;

	_game.addPlayer(DBWEngine::getInstance<DBWEngine>()->profile);
	while ((packet = _handler.extractPacket()) == nullptr || packet->code != Packet::Code::Server::SOk)
	{
		if (clock.getElapsedTime() > sf::seconds(60))
		{
			DBWEngine::getInstance<DBWEngine>()->abortClient("Server did not send player data.\nConnection aborted.");
			return;
		}
		else if (packet == nullptr) continue;
		_handler.getPlayer(packet);
	}
	//all done.
	std::cout << "Connected! :)";
}
*/

//onHandshake method should be added containing user defined handshake.
void Client::handshake()
{
	std::shared_ptr<Packet> packet = nullptr;

	packet = _handler.extractPacket(-1, -1, sf::milliseconds(50), DEFAULT_TIMEOUT);
	if (packet == nullptr)
	{
		//DBWEngine::getInstance<DBWEngine>()->abortClient("Server info not received.\nConnection aborted.");
		return;
	}
	else if (packet->code == Packet::Code::Handshake::Welcome)
	{
		_id = packet->getData<int8_t>();
		//DBWEngine::getInstance<DBWEngine>()->profile->setServerId(_id);
	}
	else if (packet->code == Packet::Code::Server::Full)
	{
		//DBWEngine::getInstance<DBWEngine>()->abortClient("Server full.\nConnection aborted.");
		return;
	}
	if (Packet::send(*_socket, Packet::Code::Client::CInfo, _id, _game.selfHost(), VERSION, DBWEngine::getInstance<DBWEngine>()->profile->getStabaxUid()) != sf::Socket::Done)
	{
		//throw(std::exception("Network error"));
	}
	packet = _handler.extractPacket(-1, -1, sf::milliseconds(50), DEFAULT_TIMEOUT);
	if (packet == nullptr)
	{
		//DBWEngine::getInstance<DBWEngine>()->abortClient("Server info not received.\nConnection aborted.");
		return;
	}
	else if (packet->code == Packet::Code::Server::Mismatch)
	{
		//DBWEngine::getInstance<DBWEngine>()->abortClient("Server version differs from yours.\nConnection aborted.");
		return;
	}
	else if (packet->code == Packet::Code::Server::SInfo) //Server info -> should be stored inside a struct.
	{
		std::string name = packet->getData<std::string>();
		int8_t slots = packet->getData<int8_t>();

		//Setup server info in game properties (packet has info)
	}
	if (Packet::send(*_socket, Packet::Code::Client::COk, _id) != sf::Socket::Done)
	{
		throw(std::exception("Network error"));
	}
	receiveServerInfo();
	//ALL DONE
}

bool Client::connectServer(std::string ip)
{
	int port = 27420;

	if (ip.find(":") != std::string::npos)
	{
		port = atoi(ip.substr(ip.find(":") + 1, ip.length() - ip.find(":")).c_str());
		ip = ip.substr(0, ip.find(":"));
	}
	if (_socket->connect(ip, port) != sf::Socket::Done)
	{
		return (false);
	}
	_receiver.start(_socket);
	handshake();
	//DBWEngine::getInstance<DBWEngine>()->profile->setState(ClientState::Connected);
	_handler.start();
	return (true);
}

