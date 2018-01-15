#include "Network/ServerReceiver.hh"
#include "Network/Server.hh"

ServerReceiver::ServerReceiver(packetStack &packetStack, std::mutex &mutex, std::mutex &signalMutex, clientArray &clientList, std::condition_variable &packetsWaiting) : Receiver(packetStack, mutex, signalMutex, packetsWaiting), _clients(clientList)
{
	_selector = std::make_shared<sf::SocketSelector>();
}

ServerReceiver::~ServerReceiver()
{

}

void ServerReceiver::dropClient(clientNode &client, bool kick)
{
	_mutex.lock();
	_selector->remove(*client.first);
	client.first = nullptr;
	client.second = ClientInfo(client.second.id);
	if (!kick)
		Packet::broadcast(_clients, Packet::Code::Client::Drop, client.second.id, client.second.id);
	std::cout << "Client " << client.second.id << " disconnected.";
	_mutex.unlock();
}

void ServerReceiver::bindClient(sf::Socket &socket)
{
	_selector->add(socket);
}

void ServerReceiver::receiveLoop()
{
	std::shared_ptr<sf::Packet> data;
	sf::Socket::Status status;

	while (!_quit)
	{
		if (_selector->wait(sf::milliseconds(500)))
		{
			for (uint8_t i = 0; i < _clients.size(); i++)
			{
				if (_clients[i].first == nullptr) continue;
				if (_selector->isReady(*_clients[i].first))
				{
					data = std::make_shared<sf::Packet>();
					status = _clients[i].first->receive(*data);
					if (status == sf::Socket::Disconnected) //Client dropped
					{
						dropClient(_clients[i]);
					}
					if (status == sf::Socket::Done) //OK
					{
						std::shared_ptr<Packet> packet = std::make_shared<Packet>(data, true);
						insertPacket(packet);
					}
				}
			}
		}
	}
	_selector.reset();
}

void ServerReceiver::start()
{
	_quit = false;
	_thread = std::make_shared<std::thread>(&ServerReceiver::receiveLoop, this);
}

void ServerReceiver::close()
{
	Receiver::close();
}