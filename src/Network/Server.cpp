#include "Network/Server.hh"
#include "Network/Packet.hh"
#include "Network/ServerHandler.hh"

clientArray Server::_clients; //Static declaration

Server::Server(const std::string &name, const int port, const int slots) : _name(name), _port(port), _slots(slots), _receiver(_packetStack, _mutex, _signalMutex, _clients, _packetsWaiting), _handler(_clients, _packetStack, _mutex, _signalMutex, _packetsWaiting, _clientsReady, _receiver)
{
	_quit = false;
	_handler.start();
	_thisThread = std::make_shared<std::thread>(&Server::run, this);
}

Server::~Server()
{
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

void Server::sendClientsInfo(clientNode &client)
{
	for (int8_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].second.id == client.second.id)
			continue;
		Packet::send(*client.first, Packet::Describe::Player, _clients[i].second.id, _clients[i].second.uid, static_cast<int8_t>(_clients[i].second.state));
	}
	Packet::send(*client.first, Packet::Server::SOk);
}

void Server::handshake(clientNode &client)
{
	std::shared_ptr<Packet> packet = nullptr;

	client.first->setBlocking(false);
	_receiver.bindClient(*client.first);
	client.second.state = ClientState::Connecting;
	Packet::send(*client.first, Packet::Handshake::Welcome, client.second.id); //send id to client
	if ((packet = _handler.extractPacket(client.second.id, Packet::Client::CInfo, sf::milliseconds(50), DEFAULT_TIMEOUT)) == nullptr) //Wait for client info
	{
		std::cout << "Client info not received. aborting handshake.";
		_receiver.dropClient(client);
		return;
	}
	client.second.host = packet->getData<bool>();
	std::string version = packet->getData<std::string>();
	if (version != VERSION)
	{
		Packet::send(*client.first, Packet::Server::Mismatch, VERSION); //MISMATCH! send server version
		std::cout << "Version mismatch. aborting handshake.";
		_receiver.dropClient(client);
		return;
	}
	client.second.uid = packet->getData<int32_t>();
	Packet::send(*client.first, Packet::Server::SInfo, _name, _slots); //send server info
	if ((packet = _handler.extractPacket(client.second.id, Packet::Client::COk, sf::milliseconds(50), DEFAULT_TIMEOUT)) == nullptr) //Wait for client Acknowledge
	{
		std::cout << "Client is not ready. aborting handshake.";
		_receiver.dropClient(client);
		return;
	}
	sendClientsInfo(client);
	client.second.state = Connected; //DONE
	Packet::broadcast(_clients, Packet::Describe::Player, client.second.id, client.second.id, client.second.uid, static_cast<int8_t>(client.second.state));
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
				Packet::send(*client, Packet::Server::Full); //Server full
			}
			else
			{
				if (clientId > _clients.size())
					_clients.push_back(std::make_pair(client, ClientInfo(clientId))); //Extend container
				else
					getClient(clientId).first = client; //Insert client in list
				std::cout << ("Client connecting.");
				handshake(getClient(clientId)); //Handshake client
			}
			client = std::make_shared<sf::TcpSocket>(); //Reset for Next client
		}
		else if (status == sf::Socket::Disconnected)
		{
			DBWEngine::getInstance<DBWEngine>()->abortServer("Server error: Socket is not bound.");
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
		//DBWEngine::getInstance<DBWEngine>()->abortServer("Cannot run server: Socket binding failed. (Port already used ?)");
	}
	_listener.setBlocking(false);
	_listenThread = std::make_shared<std::thread>(&Server::listenLoop, this); //Start client negociation thread
	_receiver.start();
	std::unique_lock<std::mutex> lock(_signalMutex);

	while (!clientsReady() && !_quit) //lobby state
	{
		_clientsReady.wait(lock);
	}
	game(); //Game loop
}

//Add onShutdown method to cast clientsready
void Server::shutdown()
{
	_quit = true;
	_receiver.close();
	_handler.stop();
	if (!clientsReady()) //If server is blocking
	{
		_clientsReady.notify_one();
	}
	_listenThread->join();
	_thisThread->join();
	std::cout << "Server Shutted down.";
}