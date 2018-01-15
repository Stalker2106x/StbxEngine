#include "Engine.hpp"
#include "Network/Client.hh"
#include "Network/ClientHandler.hh"

using namespace stb;

Client::Client(const VersionInfo &version, bool self) : _receiver(_packetStack, _mutex, _signalMutex, _packetsWaiting), _handler(*_socket, _packetStack, _mutex, _signalMutex, _packetsWaiting), _version(version)
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


void Client::receiveClientList()
{
	sf::Clock clock;
	std::shared_ptr<Packet> packet = nullptr;

	while ((packet = _handler.extractPacket()) == nullptr || packet->code != Packet::Code::Server::SOk)
	{
		if (clock.getElapsedTime() > sf::seconds(60))
		{
			onServerTimeout();
			return;
		}
		else if (packet == nullptr) continue;
		receivePlayer(*packet);
	}
	//all done.
}

//onHandshake method should be added containing user defined handshake.
void Client::handshake()
{
	std::shared_ptr<Packet> packet = nullptr;

	packet = _handler.extractPacket(-1, -1, sf::milliseconds(50), DEFAULT_TIMEOUT);
	if (packet == nullptr)
	{
		onServerTimeout();
		return;
	}
	else if (packet->code == Packet::Code::Handshake::Welcome)
	{
		_id = packet->getData<int8_t>();
		Engine::profile->setClientId(_id);
	}
	else if (packet->code == Packet::Code::Server::Full)
	{
		onServerFull();
		return;
	}
	if (Packet::send(*_socket, Packet::Code::Client::CInfo, _id, _version.major, _version.minor, _version.build, Engine::profile->getUid()) != sf::Socket::Done)
	{
		onNetworkError();
	}
	packet = _handler.extractPacket(-1, -1, sf::milliseconds(50), DEFAULT_TIMEOUT);
	if (packet == nullptr)
	{
		onServerTimeout();
		return;
	}
	else if (packet->code == Packet::Code::Server::Mismatch)
	{
		onVersionMismatch();
		return;
	}
	else if (packet->code == Packet::Code::Server::SInfo)
	{
		receiveServerInfo(*packet);
	}
	if (Packet::send(*_socket, Packet::Code::Client::COk, _id) != sf::Socket::Done)
	{
		onNetworkError();
	}
	receiveClientList();
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
	Engine::profile->setState(ClientState::Connected);
	_handler.start();
	return (true);
}

