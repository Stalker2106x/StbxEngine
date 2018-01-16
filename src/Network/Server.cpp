#include "Network/Server.hh"
#include "Network/Packet.hh"
#include "Network/ServerHandler.hh"

using namespace stb;

clientArray Server::_clients; //Static declaration

Server::Server(const VersionInfo &version, const VersionInfo &supportedVersion, const std::string &name, const int port, const int slots) : _name(name), _port(port), _slots(slots), _receiver(_packetStack, _mutex, _signalMutex, _clients, _packetsWaiting), _handler(_clients, _packetStack, _mutex, _signalMutex, _packetsWaiting, _clientsReady, _receiver), _version(version), _supportedVersion(supportedVersion)
{
	_quit = false;
	_handler.start();
	_thisThread = std::make_shared<std::thread>(&Server::run, this);
}

Server::~Server()
{
	if (_thisThread != nullptr)
	{
		//Call for abort
	}
}

void Server::addHandle(std::pair<int, packetFunctor> &functor)
{
	_handler.addHandle(functor);
}

void Server::addHandle(std::vector<std::pair<int, packetFunctor>> &functors)
{
	for (size_t i = 0; i < functors.size(); i++)
	{
		addHandle(functors[i]);
	}
}

clientNode &Server::getClient(int8_t clientId)
{
	for (int8_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].second.id == clientId)
			return (_clients[i]);
	}
	throw (std::exception("unknownclient"));
}

bool Server::isVersionSupported(const VersionInfo &version)
{
	if (version.major > _supportedVersion.major)
	{
		return (true);
	}
	else if (version.major == _supportedVersion.major)
	{
		if (version.minor > _supportedVersion.minor)
		{
			return (true);
		}
		else if (version.minor == _supportedVersion.minor)
		{
			if (version.build >= _supportedVersion.build)
			{
				return (true);
			}
		}
	}
	return (false);
}

void Server::sendClientsInfo(clientNode &client)
{
	for (int8_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].second.id == client.second.id)
			continue;
		Packet packet(Packet::Code::Describe::Player, -1, true);

		packet << _clients[i].second.id << _clients[i].second.uid << static_cast<int8_t>(_clients[i].second.state); //Inject protocol data
		setClientData(packet); //Inject user defined data
		Packet::send(*client.first, packet);
	}
	Packet::send(*client.first, Packet::Code::Server::SOk);
}

void Server::handshake(clientNode &client)
{
	std::shared_ptr<Packet> packet = nullptr;

	client.first->setBlocking(false);
	_receiver.bindClient(*client.first);
	client.second.state = ClientState::Connecting;
	Packet::send(*client.first, Packet::Code::Handshake::Welcome, client.second.id); //send id to client
	if ((packet = _handler.extractPacket(client.second.id, Packet::Code::Client::CInfo, sf::milliseconds(50), DEFAULT_TIMEOUT)) == nullptr) //Wait for client info
	{
		onClientTimeout();
		_receiver.dropClient(client);
		return;
	}
	client.second.host = packet->getData<bool>();
	VersionInfo version;
	version.major = packet->getData<int>();
	version.minor = packet->getData<int>();
	version.build = packet->getData<int>();
	if (!isVersionSupported(version))
	{
		Packet::send(*client.first, Packet::Code::Server::Mismatch, _version.major, _version.minor, _version.build); //MISMATCH! return server version
		return;
	}
	client.second.uid = packet->getData<int32_t>();
	Packet::send(*client.first, Packet::Code::Server::SInfo, _name, _slots); //send server info
	if ((packet = _handler.extractPacket(client.second.id, Packet::Code::Client::COk, sf::milliseconds(50), DEFAULT_TIMEOUT)) == nullptr) //Wait for client Acknowledge
	{
		onClientTimeout();
		_receiver.dropClient(client);
		return;
	}
	sendClientsInfo(client);
	sendServerData(client);
	client.second.state = Connected; //DONE
	Packet::broadcast(_clients, Packet::Code::Describe::Player, client.second.id, client.second.id, client.second.uid, static_cast<int8_t>(client.second.state));
	client.second.autoHandle = true; //DONE
}

uint8_t Server::reserveSlot()
{
	for (uint8_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].first == nullptr)
			return (_clients[i].second.id);
	}
	if (_clients.size() < _slots)
		return (static_cast<uint8_t>(_clients.size() + 1));
	return (-1); // No slot
}

void Server::listenLoop()
{
	std::shared_ptr<sf::TcpSocket> client = std::make_shared<sf::TcpSocket>();
	sf::Socket::Status status;
	int8_t clientId = 1;

	while (!_quit) //Accept loop
	{
		if ((status = _listener.accept(*client)) == sf::Socket::Done) 
		{
			if ((clientId = reserveSlot()) == -1)
			{
				Packet::send(*client, Packet::Code::Server::Full); //Server full
			}
			else
			{
				if (clientId > _clients.size())
					_clients.push_back(std::make_pair(client, ClientInfo(clientId))); //Extend container
				else
					getClient(clientId).first = client; //Insert client in list
				handshake(getClient(clientId)); //Handshake client
			}
			client = std::make_shared<sf::TcpSocket>(); //Reset for Next client
		}
		else if (status == sf::Socket::Disconnected && !_quit)
		{
			onNetworkError();
			break; //end loop
		}
	}
	_listener.close();
}

//Add overload for user
void Server::run()
{
	if (_listener.listen(_port) != sf::Socket::Done) //Binding
	{
		onBindError();
	}
	_listener.setBlocking(false);
	_listenThread = std::make_shared<std::thread>(&Server::listenLoop, this); //Start client negociation thread
	_receiver.start();
	loop();
}

//Add onShutdown method to cast clientsready
void Server::shutdown()
{
	_quit = true;
	_receiver.close();
	_handler.stop();
	_listenThread->join();
	_thisThread->join();
}